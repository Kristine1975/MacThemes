// ===========================================================================
//	LLayoItemPane.cp					PowerPlant 1.9.3	©1993-1998 Metrowerks Inc.
// ===========================================================================
//
//	Displays a 'PICT' resource
//
//	LLayoItemPane stores the ID of a PICT resource as a member variable, and
//	always calls GetPicture() to get a Handle to the picture. It purposely
//	does not release the PICT resource when deleted, since other LLayoItemPane
//	views may be using the same picture. For example, you might use the
//	same picture as a background or graphic element in multiple windows.
//
//	If you are concerned about the memory used by the PICT resource, mark
//	it as purgeable in your resource file.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "LLayoItemPane.h"
#include "CThemeDoc.h"
#include "TBrushTable.h"
#include "CTPxmResource.h"
#include "UTFrmeResource.h"

static const RGBColor kFeatureFrameColor = {0x0,0xFFFF,0x0};

// ---------------------------------------------------------------------------
//	€ LLayoItemPane								Default Constructor		  [public]
// ---------------------------------------------------------------------------

LLayoItemPane::LLayoItemPane(const SPaneInfo	&inPaneInfo, UInt32 inNumber, LLayoView *inView, UTLayoutResource * inResource, LayoutItem &inItem) 
			: LPane(inPaneInfo),
			LDragAndDrop(inPaneInfo.superView->GetMacPort(),this)
{
	Init();
	mItem = inItem;
	mResource = inResource;
	mView = inView;
	mNumber = inNumber;
}





void LLayoItemPane::Init()
{
	mView = NULL;
	mResource = NULL;
	mNumber = 0;
}

LLayoItemPane::~LLayoItemPane()
{
}



// ---------------------------------------------------------------------------
//	€ DrawSelf													   [protected]
// ---------------------------------------------------------------------------
//	Draw a Picture

void
LLayoItemPane::DrawSelf()
{
	if(IsItemVisible())
	{
		FocusDraw();
		//Rect ourRect;
		Rect theRect;
		CalcLocalFrameRect(theRect);
		//mItem.CalculateItemRect(mResource,theRect,ourRect);
		CThemeDoc *theDoc = mView->GetThemeDocument();
		if(theDoc)
		{
			switch(mItem.type)
			{
				case 'plut':
				{
					PlutDragRecord theRec = theDoc->GetPlutDragRec(mItem.itemID);
					theRec.aPlut.PaintRect(theRect,mItem.alignment);
				}
				break;
				
				case 'pxm#':
				{
					FullResourceSpec theSpec = {mItem.itemID,theDoc->GetResFileRefNum(),'pxm#'};	
					CTPxmResource thePxm(theSpec);
					thePxm.PaintRect(theRect,mItem.alignment,mItem.itemIndex + 1);
				}
				break;
				
				case 'fram':
				{
					UTFrmeResource theFrame;
					theFrame.Init(mItem.itemID,theDoc->GetResFileRefNum());
					theFrame.PaintRect(theRect,theDoc);
				}
				break;
				
				default:
				{
					ForeColor(blackColor);
					FrameRect(&theRect);
				}
				break;
			}
		}
		else
		{
			FrameRect(&theRect);
		}
		UInt32 theVisibleFlags,theFeatureFlags;
		mView->GetFlags(theVisibleFlags,theFeatureFlags);
		if(theFeatureFlags & mItem.featureFlags)
		{
			RGBForeColor(&kFeatureFrameColor);
			FrameRect(&theRect);
		}
	}
}



void		LLayoItemPane::ClickSelf(
								const SMouseDownEvent &/*inMouseDown*/)
{
	if (GetClickCount() == 2) 
	{
		Str255 theString;
		NumToString(mNumber,theString);
		SignalString_(theString);
	}
}

Boolean	LLayoItemPane::IsItemVisible() const
{
	UInt32 theVisibleFlags,theFeatureFlags;
	mView->GetFlags(theVisibleFlags,theFeatureFlags);
	Boolean show = false;
	if(mItem.visibleFlags & mItem.invisibleFlags)
	{
		SignalString_("\pBad Item State Visible and Invisible Flags");
	}
	if(mItem.visibleFlags == 0 && mItem.invisibleFlags == 0)
	{
		show = true;
	}
	else
	{
		show = true;
		for(UInt32 i = 0; i < 32 && show; i++)
		{
			UInt32 maskVisFlag = (mItem.visibleFlags >> i) & 1;
			UInt32 maskInvFlag = (mItem.invisibleFlags >> i) & 1;
			UInt32 maskUserFlag = (theVisibleFlags >> i) & 1;
			
			if(maskVisFlag == 1 && maskInvFlag == 0 && maskUserFlag == 0)
			{
				show = false;
			}
			else if(maskVisFlag == 0 && maskInvFlag == 1 && maskUserFlag == 1)
			{
				show = false;
			}
		}
	}
	return show;
}

Boolean
LLayoItemPane::IsHitBy(
	SInt32	inHorizPort,
	SInt32	inVertPort)
{
	Boolean isHit = false;
	if(IsItemVisible())
	{
		if(mItem.type == 'fram')
		{
			CThemeDoc *theDoc = mView->GetThemeDocument();
			UTFrmeResource theFrame;
			theFrame.Init(mItem.itemID,theDoc->GetResFileRefNum());
			Rect thePortFrameRect;
			CalcPortFrameRect(thePortFrameRect);
			Rect theMaximumRect = thePortFrameRect;
			Rect theMinimumRect = thePortFrameRect;
			InsetRect(&theMaximumRect,theFrame.GetMaximumInset(),theFrame.GetMaximumInset());
			InsetRect(&theMinimumRect,theFrame.GetMinimumInset(),theFrame.GetMinimumInset());
			StRegion theOuterRegion,theInnerRegion;
			OpenRgn();
			FrameRect(&theMinimumRect);
			CloseRgn(theOuterRegion);
			OpenRgn();
			FrameRect(&theMaximumRect);
			CloseRgn(theInnerRegion);
			theOuterRegion -= theInnerRegion;
			Point thePoint;
			thePoint.h = inHorizPort;
			thePoint.v = inVertPort;
			isHit = theOuterRegion.Contains(thePoint);
					
		}
		else
		{
			isHit = LPane::IsHitBy(inHorizPort,inVertPort);
		}
	}
	return isHit;
}

// ---------------------------------------------------------------------------
//	€ ItemIsAcceptable
// ---------------------------------------------------------------------------
//	DragManager item is acceptable if it has data of PICT and we're not of type
// ImageMaskView

Boolean
LLayoItemPane::ItemIsAcceptable(
	DragReference	inDragRef,
	ItemReference	inItemRef)
{
	FlavorFlags		theFlags;
	return (GetFlavorFlags(inDragRef, inItemRef, kPxmDragFlavor, &theFlags) == noErr 
		|| GetFlavorFlags(inDragRef, inItemRef, kBrushDragFlavor, &theFlags) == noErr
		|| GetFlavorFlags(inDragRef, inItemRef, kFrmeDragFlavor, &theFlags) == noErr);
}

// ---------------------------------------------------------------------------
//	€ ReceiveDragItem
// ---------------------------------------------------------------------------
//	DragManager item is acceptable if it has data of kBrushDragFlavor

void	LLayoItemPane::ReceiveDragItem(
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
					mItem.type = 'plut';
					mItem.itemID = (theDragRec.anIndex + 1) * (theDragRec.aTable->isRequired() ? 1 : -1);
					Refresh();
				}
				break;
			} 
			else if(theType == kPxmDragFlavor)
			{
				PxmDragRecord theDragRec;
				SInt32 theSize = sizeof(theDragRec);
				if(GetFlavorData(inDragRef, inItemRef, theType, &theDragRec,&theSize , (UInt32)0) == noErr)
				{
					mItem.type = 'pxm#';
					mItem.itemID = theDragRec.pxmSpec.resID;
					mItem.itemIndex = theDragRec.index;
					Refresh();
				}
				break;
			}
			else if(theType == kFrmeDragFlavor)
			{
				FrmeDragRecord theDragRec;
				SInt32 theSize = sizeof(theDragRec);
				if(GetFlavorData(inDragRef, inItemRef, theType, &theDragRec,&theSize , (UInt32)0) == noErr)
				{
					mItem.type = 'fram';
					mItem.itemID = theDragRec.frmeSpec.resID;
					mItem.itemIndex = 0;
					Refresh();
				}
				break;
			}
		}
	}
	Refresh();
}
