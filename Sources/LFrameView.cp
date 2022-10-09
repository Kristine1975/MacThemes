// ===========================================================================
//	LFrameView.cp					PowerPlant 1.9.3	©1993-1998 Metrowerks Inc.
// ===========================================================================
//
//	Displays a 'PICT' resource
//
//	LFrameView stores the ID of a PICT resource as a member variable, and
//	always calls GetPicture() to get a Handle to the picture. It purposely
//	does not release the PICT resource when deleted, since other LFrameView
//	views may be using the same picture. For example, you might use the
//	same picture as a background or graphic element in multiple windows.
//
//	If you are concerned about the memory used by the PICT resource, mark
//	it as purgeable in your resource file.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "LFrameView.h"
#include <LStream.h>
#include <UDrawingState.h>
#include "CTPxmResource.h"
#include <ToolUtils.h>
#include "TThemes.h"
#include "UTPixUtilities.h"
#include <UStandardDialogs.h>
#include "UTPlutResource.h"
#include "CThemeDoc.h"
#include "TBrushTable.h"
#include "LFrameRectView.h"
#include "TPlutDragTask.h"
#include "TFrmeEditDialogBox.h"

const float kMagnification = 1.25;

const RGBColor LFrameView::kUpperLeftCornerColor = { 0xFFFF, 0x0000, 0x0000 };
const RGBColor LFrameView::kUpperRightCornerColor = { 0x0000, 0x0000, 0x0000 };
const RGBColor LFrameView::kLowerLeftCornerColor = { 0x0000, 0xFFFF, 0x0000 };
const RGBColor LFrameView::kLowerRightCornerColor = {0x0000, 0x0000, 0xFFFF };
const RGBColor LFrameView::kUnknownCornerColor = {0x0000, 0x0000, 0x0000 };

// ---------------------------------------------------------------------------
//	€ LFrameView								Default Constructor		  [public]
// ---------------------------------------------------------------------------

LFrameView::LFrameView(TFrmeEditDialogBox* inDialog) : LDragAndDrop(GetMacPort(),this)
{
	Init();
	SetEditDialog(inDialog);
}




// ---------------------------------------------------------------------------
//	€ LFrameView								Stream Constructor	 	 [public]
// ---------------------------------------------------------------------------

LFrameView::LFrameView(
	LStream*	inStream)
	
	: LView(inStream), LDragAndDrop(GetMacPort(),this)
{
	Init();
}



void LFrameView::Init()
{
	mEditDialog = NULL;
	mHasPlut = false;
	mPlutIndex = 0;
	mRequiredPlutTable = false;
	mMaximumInset = 0;
	mMinimumInset = 0;
	mEyeDropperMode = false;
	mShowGrid = true;
	mDoGridInColor = true;
	mMagnifyingMode = false;
	mMagnification = 1.0;
	mPatternOrigin = frameOriginRightTop;
}

LFrameView::~LFrameView()
{
}


// ---------------------------------------------------------------------------
//	€ DrawSelf													   [protected]
// ---------------------------------------------------------------------------
//	Draw a Picture

void
LFrameView::DrawSelf()
{
	// If Picture resource exists, draw it. Otherwise, fill the
	// Frame with a light gray pattern and a one-pixel border.
	FocusDraw();

	Rect	frame;
	CalcLocalFrameRect(frame);
	::PenNormal();
	
	{
		StColorPenState theState;
		PixPatHandle thePixPat = GetPixPat(kTransparentPixPatID);
		SignalIf_(thePixPat == NULL);
		BackPixPat(thePixPat);
		EraseRect(&frame);
		DisposePixPat(thePixPat);
	}
	
	if(mHasPlut && mEditDialog != NULL)
	{
		PlutDragRecord thePlut = GetPlutDragRec(mPlutIndex,mRequiredPlutTable);
		if(thePlut.aPlut.brushPPAT.resID == 0)
		{
			RGBForeColor(&thePlut.aPlut.brushColor);
			PaintRect(&mCenterRect);
		}
		else
		{
			PixPatHandle thePattern = thePlut.aPlut.GetPlutPixPat();
			FillCRect(&mCenterRect,thePattern);
			DisposePixPat(thePattern);
		}
		if(mShowGrid)
		{
			if(mDoGridInColor)
			{
				if(mPatternOrigin == frameOriginLeftTop)
				{
					RGBForeColor(&LFrameView::kUpperLeftCornerColor);
				}
				else if(mPatternOrigin == frameOriginLeftBottom)
				{
					RGBForeColor(&LFrameView::kLowerLeftCornerColor);
				}
				else if(mPatternOrigin == frameOriginRightBottom)
				{
					RGBForeColor(&LFrameView::kLowerRightCornerColor);
				}
				else if(mPatternOrigin == frameOriginRightTop)
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
}

PlutDragRecord		LFrameView::GetPlutDragRec(SInt16 inIndex, bool isRequired)
{
	SignalIf_(mEditDialog == NULL);
	CThemeDoc* theDoc = mEditDialog->GetThemeDocument();
	SignalIf_(theDoc == NULL);
	return theDoc->GetPlutDragRec(inIndex,isRequired);
}

// ---------------------------------------------------------------------------
//	€ ItemIsAcceptable
// ---------------------------------------------------------------------------
//	DragManager item is acceptable if it has data of PICT and we're not of type
// ImageMaskView

Boolean
LFrameView::ItemIsAcceptable(
	DragReference	inDragRef,
	ItemReference	inItemRef)
{
	FlavorFlags		theFlags;
	return (GetFlavorFlags(inDragRef, inItemRef, kBrushDragFlavor, &theFlags) == noErr);
}

// ---------------------------------------------------------------------------
//	€ ReceiveDragItem
// ---------------------------------------------------------------------------
//	DragManager item is acceptable if it has data of PICT

void	LFrameView::ReceiveDragItem(
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
				}
				break;
			}
		}
	}
	Refresh();

}

// ---------------------------------------------------------------------------
//	€ Click
// ---------------------------------------------------------------------------
//	Handle a click inside a View

void
LFrameView::Click(
	SMouseDownEvent	&inMouseDown)
{
	if(mEyeDropperMode)
	{
		LPane *thePane = FindDeepSubPaneContaining(inMouseDown.wherePort.h,inMouseDown.wherePort.v);
		LFramePixelPane *thePixelPane = dynamic_cast<LFramePixelPane*>(thePane);
		PlutEntryIndex theIndex;
		if(thePixelPane != NULL)
		{
			theIndex = thePixelPane->GetPlutEntryIndex();
		}
		else
		{	
			if(mHasPlut)
			{
				theIndex = mPlutIndex + 1;
				if(!mRequiredPlutTable)
				{
					theIndex *= -1;
				}
			}
			else
			{
				theIndex = 0;
			}
		}
		CThemeDoc* theDoc = mEditDialog->GetThemeDocument();
		SignalIf_(theDoc == NULL);
		theDoc->SetCurrentSelectedPlut(theIndex);
		SetEyeDropperMode(false);
		AdjustCursor(inMouseDown.wherePort,inMouseDown.macEvent);
	}
	else if(mMagnifyingMode)
	{
		float theMagnification = GetMagnification();
		if(inMouseDown.macEvent.modifiers & optionKey)
		{
			theMagnification /= kMagnification;
			
		}
		else
		{
			theMagnification *= kMagnification;
		}
		SetMagnification(theMagnification);
	}
	else
	{
		LView::Click(inMouseDown);
	}
}

void		LFrameView::DragAndDropFrame(const SMouseDownEvent &inMouseDown)
{
	Rect frame;
	CalcLocalFrameRect(frame);
	LDragTask	theDragTask(inMouseDown.macEvent);
	StRegion	outerRgn(frame);	// Make region containing item

	StRegion	innerRgn = outerRgn;	// Carve out interior of region so
	::InsetRgn(innerRgn, 1, 1);			//   that it's just a one-pixel thick
	outerRgn -= innerRgn;				//   outline of the item rectangle
	
	StRegion theRgn(theDragTask.GetDragRegion(),false);
	theRgn += outerRgn;			// Accumulate this item in our
														//   total drag region
	
										// Tell Drag Manager about this item
	::SetDragItemBounds(theDragTask.GetDragReference(), 1, &frame);
	
	FrmeDragRecord theDragRec;
	theDragRec.frmeSpec = mResource->GetResourceSpec();
	::AddDragItemFlavor(theDragTask.GetDragReference(), 1,kFrmeDragFlavor,&theDragRec, sizeof(FrmeDragRecord),0);
	theRgn.Release();	
	theDragTask.DoDrag();
}

void		LFrameView::ClickSelf(
								const SMouseDownEvent &inMouseDown)
{
	if (GetClickCount() == 1) 
	{
	
		if (LDragAndDrop::DragAndDropIsPresent() &&
			::WaitMouseMoved(inMouseDown.macEvent.where) && mHasPlut && mEditDialog != NULL) 
		{
			FocusDraw();
			DragAndDropFrame(inMouseDown);
										
			OutOfFocus(nil);
		
		}
		else if(mHasPlut)
		{
			mHasPlut = false;
			InitCursor();
			RefreshRect(mCenterRect);
			SetIsModified();
			LPane::sClickCount = 0;
		}
		else
		{
			if(mEditDialog != NULL)
			{
				if(mHasPlut)
				{
					mHasPlut = false;
				}
				
				PlutDragRecord theDragRec;
				if(GetCurrentSelectedPlutDragRec(theDragRec))
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
				SetIsModified();
				RefreshRect(mCenterRect);
				LPane::sClickCount = 0;
			}
		}
	}
}


void	LFrameView::SetEditDialog(TFrmeEditDialogBox *inDialog)
{
	mEditDialog = inDialog;
}

void		LFrameView::AdjustCursorSelf(Point				inPortPt,const EventRecord	&/*inMacEvent*/)
{
	if(PtInRect(inPortPt, &mCenterRect))
	{
		PlutDragRecord theDragRec;
		if(mHasPlut)
		{
			UCursor::SetTheCursor(kEraserCursor);
		}
		else if(GetCurrentSelectedPlutDragRec(theDragRec))
		{
			UCursor::SetTheCursor(kPaintBucketCursor);
		}
	}
}

void
LFrameView::AdjustCursor(
	Point				inPortPt,
	const EventRecord	&inMacEvent)
{
	if(mEyeDropperMode)
	{
		UCursor::SetTheCursor(kEyeDropperCursor);
	}
	else if(mMagnifyingMode)
	{
		UCursor::SetTheCursor(inMacEvent.modifiers & optionKey ? kZoomOutCursor : kZoomInCursor);
	}
	else
	{
		LView::AdjustCursor(inPortPt,inMacEvent);
	}
}

Boolean 		LFrameView::GetCurrentSelectedPlutDragRec(PlutDragRecord &outRec)
{
	Boolean answer = false;
	if(mEditDialog)
	{
		SignalIf_(mEditDialog == NULL);
		CThemeDoc* theDoc = mEditDialog->GetThemeDocument();
		SignalIf_(theDoc == NULL);
		answer = theDoc->GetCurrentSelectedPlutDragRec(outRec);
	}
	return answer;
}

SInt32	LFrameView::GetMinimumInset()
{
	return mMinimumInset;
}
SInt32	LFrameView::GetMaximumInset()
{
	return mMaximumInset;
}

void	LFrameView::SetMinimumInset(SInt32 inInset)
{
	mMinimumInset = inInset;
}

void	LFrameView::SetMaximumInset(SInt32 inInset)
{
	mMaximumInset = inInset;
}

LFrameRectView*	LFrameView::AddFrame(SInt32 inInset, Boolean inRefresh)
{
	LFrameRectView *theFrame = NULL;
	UInt32 i;
	for(i = 1; i <= mFrames.GetCount(); i++)
	{
		if(mFrames[i]->GetInset() == inInset)
		{
			break;
		}
	}
	if(i > mFrames.GetCount())
	{
		theFrame = new LFrameRectView(this,inInset);
		theFrame->FinishCreate();
		if(inInset < mMinimumInset)
		{
			mMinimumInset = inInset;
		}
		else if(inInset > mMaximumInset)
		{
			mMaximumInset = inInset;
		}
		theFrame->PutInside(this);
		mFrames.AddItem(theFrame);
		AdaptToNewSurroundings();
		if(inRefresh)
		{
			Refresh();
		}
	}
	return theFrame;
}

LFrameRectView* LFrameView::RemoveFrame(SInt32 inInset, Boolean inRefresh)
{
	LFrameRectView *theFrame = NULL;
	UInt32 i;
	for(i = 1; i <= mFrames.GetCount(); i++)
	{
		if(mFrames[i]->GetInset() == inInset)
		{
			break;
		}
	}
	
	if(i <= mFrames.GetCount())
	{
		theFrame = mFrames[i];
		theFrame->PutInside(NULL);
		mFrames.Remove(theFrame);
		if(inInset == mMinimumInset || inInset == mMaximumInset)
		{
			mMinimumInset = 32000;
			mMaximumInset = -32000;
			for(i = 1; i <= mFrames.GetCount(); i++)
			{
				SInt32 theInset = mFrames[i]->GetInset();
				if( theInset > mMaximumInset)
				{
					mMaximumInset = theInset;
				}
				if(theInset < mMinimumInset)
				{
					mMinimumInset = theInset;
				}
			}
		}
		AdaptToNewSurroundings();
		if(inRefresh)
		{
			Refresh();
		}
	}
	return theFrame;
}

// ---------------------------------------------------------------------------
//	€ AdaptToNewSurroundings
// ---------------------------------------------------------------------------
//	Adjust view when its SuperView changes identity or size

void
LFrameView::AdaptToNewSurroundings()
{
	CalcLocalFrameRect(mCenterRect);
	LView::AdaptToNewSurroundings();
}

LFrameRectView* LFrameView::GetFrame(SInt32 inInset)
{
	LFrameRectView *theFrame = NULL;
	UInt32 i;
	for(i = 1; i <= mFrames.GetCount(); i++)
	{
		if(mFrames[i]->GetInset() == inInset)
		{
			theFrame = mFrames[i];
			break;
		}
	}
	return theFrame;
}

void	LFrameView::SetFrmeResource(UTFrmeResource *inResource)
{
	mResource = inResource;
	while(mFrames.GetCount())
	{
		RemoveFrame(mFrames[1]->GetInset(),false);
	}
	mHasPlut = inResource->GetBackgroundPlutID() != 0;
	if(mHasPlut)
	{
		mPlutIndex = inResource->GetBackgroundPlutID();
		mRequiredPlutTable = inResource->GetBackgroundPlutID() > 0;
		if(!mRequiredPlutTable)
		{
			mPlutIndex *= -1;
		}
		mPlutIndex -= 1;
	}
	SetMaximumInset(inResource->GetMaximumInset());
	SetMinimumInset(inResource->GetMinimumInset());
	SetPatternOrigin(inResource->GetPatternOrigin());
	for(UInt32 i = 0; i < inResource->GetFrameCount(); i++)
	{
		FrameEntry *theFrameEntry;
		inResource->FetchFrameAt(i+1,theFrameEntry);
		AddFrame(theFrameEntry->mInset,false);
		for(UInt32 j = 0; j < 64; j++)
		{
			if(theFrameEntry->mPixels[j])
			{
				SetPixel(theFrameEntry->mInset,theFrameEntry->mPlutIndex,j,theFrameEntry->mPatternOrigin);
			}
		}
	}
	Refresh();
}

OSStatus	LFrameView::BuildFrmeResource(UTFrmeResource &ioResource)
{
	ioResource.SetType(kType3Frame);
	ioResource.SetMinimumInset(mMinimumInset);
	ioResource.SetMaximumInset(mMaximumInset);
	ioResource.SetBackgroundPlutID(mHasPlut ? ConvertPlutDataToIndex(mRequiredPlutTable,mPlutIndex) : 0);
	while(ioResource.GetFrameCount())
	{
		ioResource.RemoveFrameAt(1);
	}
	for(UInt32 i = 1; i <= mFrames.GetCount(); i++)
	{
		UInt32 theCount = mFrames[i]->GetFrmeCount();
		TArray<FrameEntry*> theEntries;
		mFrames[i]->GetFrmeEntries(theEntries);
		for(UInt32 j=1; j <= theEntries.GetCount(); j++)
		{
			ioResource.AddFrame(theEntries[j]);
		}
	}
	return noErr;
}

Boolean	LFrameView::PointInDropArea(Point				inGlobalPt)
{
	FocusDraw();
	GlobalToPortPoint(inGlobalPt);
	PortToLocalPoint(inGlobalPt);
	return PtInRect(inGlobalPt,&mCenterRect);
}

void LFrameView::SetPixel(SInt32 inInset, PlutEntryIndex inIndex, UInt32 inPixelIndex, FrameOrigin inOrigin)
{
	UInt32 i;
	for(i = 1; i <= mFrames.GetCount(); i++)
	{
		if(mFrames[i]->GetInset() == inInset)
		{
			break;
		}
	}
	if(i <= mFrames.GetCount())
	{
		mFrames[i]->SetPixel(inIndex,inPixelIndex,inOrigin);
	}
	else
	{
		SignalString_("\pBad Inset!");
	}
}

void	LFrameView::SetCenterRectangle(const Rect &inRect)
{
	UInt32 width = inRect.right - inRect.left;
	UInt32 height = inRect.bottom - inRect.top;
	SignalIfNot_(width == height);
	if(width < mCenterRect.right - mCenterRect.left)
	{
		mCenterRect = inRect;
	}
	RefreshRect(mCenterRect);
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
LFrameView::HiliteDropArea(
	DragReference	inDragRef)
{
	mPane->ApplyForeAndBackColors();
	StRegion	dropRgn(mCenterRect);
	::ShowDragHilite(inDragRef, dropRgn, true);
}


Boolean LFrameView::GetEyeDropperMode()
{
	return mEyeDropperMode;
}

void	LFrameView::SetEyeDropperMode(Boolean inMode, Boolean doBroadcast /*= true*/)
{
	mEyeDropperMode = inMode;
	if(doBroadcast)
	{
		SInt32 theMessage = mEyeDropperMode;
		BroadcastMessage(kEyeDropMessage, &theMessage);
	}
}


Boolean LFrameView::GetMagnifyingMode()
{
	return mMagnifyingMode;
}

void	LFrameView::SetMagnifyingMode(Boolean inMode, Boolean doBroadcast /*= true*/)
{
	mMagnifyingMode = inMode;
	if(doBroadcast)
	{
		BroadcastMessage(kEyeDropMessage, &mEyeDropperMode);
	}
}

float	LFrameView::GetMagnification()
{
	return mMagnification;
}

void	LFrameView::SetMagnification(float inMagnification, Boolean inRefresh /*= true*/)
{
	mMagnification = inMagnification;
	if(inRefresh)
	{
		AdaptToNewSurroundings();
		Refresh();
	}
}

Boolean LFrameView::ShowGrid(Boolean &outDoItInColor)
{
	outDoItInColor = mDoGridInColor;
	return mShowGrid;
}

void LFrameView::SetShowGrid(Boolean inShowGrid, Boolean inDoItInColor)
{
	mShowGrid = inShowGrid;
	mDoGridInColor = inDoItInColor;
}


void LFrameView::SetIsModified(Boolean inModified /*= true*/)
{
	mEditDialog->SetIsModified(inModified);
}

bool LFrameView::GetIsModified()
{
	return mEditDialog->GetIsModified();
}

FrameOrigin LFrameView::GetPatternOrigin()
{
	return mPatternOrigin;
}

void	LFrameView::SetPatternOrigin(FrameOrigin inOrigin)
{
	mPatternOrigin = inOrigin;
}