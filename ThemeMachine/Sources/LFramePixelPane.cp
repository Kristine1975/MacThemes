// ===========================================================================
//	LFramePixelPane.cp					PowerPlant 1.9.3	©1993-1998 Metrowerks Inc.
// ===========================================================================
//
//	Displays a 'PICT' resource
//
//	LFramePixelPane stores the ID of a PICT resource as a member variable, and
//	always calls GetPicture() to get a Handle to the picture. It purposely
//	does not release the PICT resource when deleted, since other LFramePixelPane
//	views may be using the same picture. For example, you might use the
//	same picture as a background or graphic element in multiple windows.
//
//	If you are concerned about the memory used by the PICT resource, mark
//	it as purgeable in your resource file.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "LFramePixelPane.h"
#include <LStream.h>
#include <UDrawingState.h>
#include "CTPxmResource.h"
#include <ToolUtils.h>
#include "TThemes.h"
#include "UTPixUtilities.h"
#include <UStandardDialogs.h>
#include <UCursor.h>
#include "UTPlutResource.h"
#include "TBrushTable.h"
#include "LFrameRectView.h"
#include "TPlutDragTask.h"
#include "LFrameView.h"

// ---------------------------------------------------------------------------
//	€ LFramePixelPane								Default Constructor		  [public]
// ---------------------------------------------------------------------------

LFramePixelPane::LFramePixelPane(LFrameRectView *inView) : LPane(), LDragAndDrop(inView->GetMacPort(),this)
{
	Init();
	mFrameRect = inView;
}





void LFramePixelPane::Init()
{
	mFrameRect = false;
	mPlutIndex = 32000;
	mRequiredPlutTable = -2;
	mHasPlut = false;
	mFrameOrigin = frameOriginRightTop;
}

LFramePixelPane::~LFramePixelPane()
{
}


void	LFramePixelPane::AdaptToNewSurroundings()
{
	LDropArea::RemoveDropArea(this,mDragWindow);
	mDragWindow = GetMacPort();
	LDropArea::AddDropArea(this,mDragWindow);
}

// ---------------------------------------------------------------------------
//	€ DrawSelf													   [protected]
// ---------------------------------------------------------------------------
//	Draw a Picture

void
LFramePixelPane::DrawSelf()
{
	// If Picture resource exists, draw it. Otherwise, fill the
	// Frame with a light gray pattern and a one-pixel border.
	FocusDraw();
	
	Rect	frame;
	CalcLocalFrameRect(frame);
	::PenNormal();
	
	if(mHasPlut && mFrameRect != NULL)
	{
		PlutDragRecord thePlut = mFrameRect->GetPlutDragRec(mPlutIndex,mRequiredPlutTable);
		if(thePlut.aPlut.brushPPAT.resID == 0)
		{
			RGBForeColor(&thePlut.aPlut.brushColor);
			PaintRect(&frame);
		}
		else
		{
			PixPatHandle thePattern = thePlut.aPlut.GetPlutPixPat();
			ImageAlignment theAlignment;
			switch(mFrameOrigin)
			{
				case frameOriginRightTop:
					theAlignment = kImageAlignTopRight;
				break;
				
				case frameOriginRightBottom:
					theAlignment = kImageAlignBottomRight;
				break;
				
				case frameOriginLeftBottom:
					theAlignment = kImageAlignBottomLeft;
				break;
				
				default:
					SignalString_("\pThis is a Frame Origin Constant that we don't know about!!!!");
					
				case frameOriginLeftTop:
					theAlignment = kImageAlignTopLeft;
				break;
			}
			
			Rect theFrameViewRect;
			mFrameRect->GetFrameRect(theFrameViewRect);
			UTPixUtilities::FillCRectAlignedToRect(frame,theFrameViewRect,thePattern,theAlignment);
			DisposePixPat(thePattern);
		}
	}
		
	Boolean doGridInColor;
	if(mFrameRect->ShowGrid(doGridInColor))
	{
		if(doGridInColor)
		{
			if(mFrameOrigin == frameOriginLeftTop)
			{
				RGBForeColor(&LFrameView::kUpperLeftCornerColor);
			}
			else if(mFrameOrigin == frameOriginLeftBottom)
			{
				RGBForeColor(&LFrameView::kLowerLeftCornerColor);
			}
			else if(mFrameOrigin == frameOriginRightBottom)
			{
				RGBForeColor(&LFrameView::kLowerRightCornerColor);
			}
			else if(mFrameOrigin == frameOriginRightTop)
			{
				RGBForeColor(&LFrameView::kUpperRightCornerColor);
			}
			else
			{
				SignalString_("\pThis is a Frame Origin Constant that we don't know about!!!!");
				RGBForeColor(&LFrameView::kUnknownCornerColor);
			}
		}
		else
		{
			ForeColor(blackColor);
		}
		FrameRect(&frame);
	}
}

// ---------------------------------------------------------------------------
//	€ ItemIsAcceptable
// ---------------------------------------------------------------------------
//	DragManager item is acceptable if it has data of PICT and we're not of type
// ImageMaskView

Boolean
LFramePixelPane::ItemIsAcceptable(
	DragReference	inDragRef,
	ItemReference	inItemRef)
{
	FlavorFlags		theFlags;
	return (GetFlavorFlags(inDragRef, inItemRef, kBrushDragFlavor, &theFlags) == noErr);
}

// ---------------------------------------------------------------------------
//	€ ReceiveDragItem
// ---------------------------------------------------------------------------
//	DragManager item is acceptable if it has data of kBrushDragFlavor

void	LFramePixelPane::ReceiveDragItem(
	DragReference	 inDragRef,
	DragAttributes	 /*inDragAttrs*/,
	ItemReference	 inItemRef,
	Rect&			 /*inItemBounds*/)	// In Local coordinates
{
	UInt16 flavorCount;
	::CountDragItemFlavors(inDragRef, inItemRef, &flavorCount);
	for(UInt32 i = 1; i <= flavorCount; i++)
	{
		OSType theType;
		if(::GetFlavorType(inDragRef, inItemRef, i, &theType) == noErr)
		{
			if(theType == kBrushDragFlavor)
			{
				PlutDragRecord theDragRec;
				SInt32 theSize = sizeof(theDragRec);
				if(GetFlavorData(inDragRef, inItemRef, theType, &theDragRec,&theSize , (UInt32)0) == noErr)
				{
					mRequiredPlutTable = theDragRec.aTable->isRequired();
					mPlutIndex = theDragRec.anIndex;
					mHasPlut = true;
					mFrameRect->SetIsModified();
				}
				break;
			}
		}
	}
	Refresh();
}

void		LFramePixelPane::ClickSelf(
								const SMouseDownEvent &inMouseDown)
{
	if (GetClickCount() == 1) 
	{
	
		FocusDraw();
		Rect	frame;
		CalcLocalFrameRect(frame);
		
		if (LDragAndDrop::DragAndDropIsPresent() &&
			::WaitMouseMoved(inMouseDown.macEvent.where) && mHasPlut) 
		{
			
			PlutDragRecord theDragRec = mFrameRect->GetPlutDragRec(mPlutIndex,mRequiredPlutTable);
			TPlutDragTask	theDragTask(inMouseDown.macEvent,theDragRec,frame);
			theDragTask.DoDrag();	
		}
		else
		{
			if(mFrameRect != NULL)
			{
				if(mHasPlut)
				{
					mHasPlut = false;
				}
				
				PlutDragRecord theDragRec;
				if(mFrameRect->GetCurrentSelectedPlutDragRec(theDragRec))
				{
					if(mRequiredPlutTable != theDragRec.aTable->isRequired() || mPlutIndex !=  theDragRec.anIndex)
					{
						mRequiredPlutTable = theDragRec.aTable->isRequired();
						mPlutIndex = theDragRec.anIndex;
						mHasPlut = true;
					}
					else
					{
						mRequiredPlutTable = -1;
						mPlutIndex = -1;
					}
				}
				mFrameRect->SetIsModified();
				LPane::sClickCount = 0;
			}
		}
		RefreshRect(frame);
	}
}


void		LFramePixelPane::AdjustCursorSelf(Point				/*inPortPt*/,const EventRecord	&/*inMacEvent*/)
{
	if(mFrameRect != NULL)
	{
		PlutDragRecord theRec;
		if(mFrameRect->GetCurrentSelectedPlutDragRec(theRec))
		{
			UCursor::SetTheCursor(kPencilCursor);
		}
	}
}

// ---------------------------------------------------------------------------
//	€ HiliteDropArea											   [protected]
// ---------------------------------------------------------------------------
//	Hilite a DropArea to indicate that it can accept the current Drag
//
//	For a DragAndDrop, the drop area is the Frame of its associated
//	Pane inset by one pixel to account for the border which usually
//	surrounds a Drop-capable Pane.

void
LFramePixelPane::HiliteDropArea(
	DragReference	inDragRef)
{
	ApplyForeAndBackColors();
	FocusDraw(this);	
	Rect	dropRect;
	CalcLocalFrameRect(dropRect);
	::MacInsetRect(&dropRect, 1, 1);
	StRegion	dropRgn(dropRect);
	
	::ShowDragHilite(inDragRef, dropRgn, true);
}



Boolean				LFramePixelPane::GetIsColoured()
{ 
	return mHasPlut;
}

PlutEntryIndex	LFramePixelPane::GetPlutEntryIndex() 
{
	PlutEntryIndex  theIndex = 0;
	if(mHasPlut)
	{
		theIndex = ConvertPlutDataToIndex(mRequiredPlutTable,mPlutIndex);
	}
	return theIndex;
}

void LFramePixelPane::SetPlutEntryIndex(PlutEntryIndex inIndex)
{
	mHasPlut = inIndex != 0;
	if(mHasPlut)
	{
		ConvertIndexToPlutData(inIndex,mRequiredPlutTable,mPlutIndex);
	}
}

FrameOrigin			LFramePixelPane::GetPatternOrigin()
{
	return mFrameOrigin;
}

void				LFramePixelPane::SetPatternOrigin(FrameOrigin inOrigin)
{
	mFrameOrigin = inOrigin;
}