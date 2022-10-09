// ===========================================================================
//	LLayoView.cp					PowerPlant 1.9.3	©1993-1998 Metrowerks Inc.
// ===========================================================================
//
//	Displays a 'PICT' resource
//
//	LLayoView stores the ID of a PICT resource as a member variable, and
//	always calls GetPicture() to get a Handle to the picture. It purposely
//	does not release the PICT resource when deleted, since other LLayoView
//	views may be using the same picture. For example, you might use the
//	same picture as a background or graphic element in multiple windows.
//
//	If you are concerned about the memory used by the PICT resource, mark
//	it as purgeable in your resource file.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "LLayoView.h"
#include "UTLayoutResource.h"
#include "CThemeDoc.h"
#include "CTPxmResource.h"
#include "LLayoItemPane.h"
#include "TLayoEditDialogBox.h"

// ---------------------------------------------------------------------------
//	€ LLayoView								Default Constructor		  [public]
// ---------------------------------------------------------------------------

LLayoView::LLayoView()
{
	Init();
}

// ---------------------------------------------------------------------------
//	€ LFrameView								Stream Constructor	 	 [public]
// ---------------------------------------------------------------------------

LLayoView::LLayoView(
	LStream*	inStream)
	
	: LView(inStream)
{
	Init();
}

void LLayoView::Init()
{
	mResource = NULL;
	mVisibleFlags = 0;
	mFeatureFlags = 0;
	mShowLines = false;
}

LLayoView::~LLayoView()
{
}

void		LLayoView::FinishCreate()
{	
	LView::FinishCreate();
}

void		LLayoView::DrawSelf()
{
	Rect theRect;
	
	CalcLocalFrameRect(theRect);
	
	{
		StColorPenState theState;
		PixPatHandle thePixPat = GetPixPat(kTransparentPixPatID);
		SignalIf_(thePixPat == NULL);
		BackPixPat(thePixPat);
		EraseRect(&theRect);
		DisposePixPat(thePixPat);
	}
	FrameRect(&theRect);
	Rect theInnerRect = theRect;
	InsetRect(&theInnerRect,40,40);
	if(mShowLines)
	{
		PenNormal();
		for(UInt32 i = 0; i < mResource->CountCoordinates(); i++)
		{
			SInt32 theLoc = LayoutItem::ResolveCoordinate(mResource,theInnerRect,i+1);
			MoveTo(theLoc,theRect.top);
			LineTo(theLoc,theRect.bottom);
			MoveTo(theRect.left,theLoc);
			LineTo(theRect.right,theLoc);
		}
	}	
}

void	LLayoView::SetLayoutResource(UTLayoutResource* inResource, Boolean inRefresh)
{
	mResource = inResource;
	DeleteAllSubPanes();
	Rect theRect;
	CalcLocalFrameRect(theRect);
	InsetRect(&theRect,40,40);
	for(UInt32 i = 0; i < mResource->CountItems(); i++)
	{
		SPaneInfo theInfo;
		LayoutItem theItem;
		SBooleanRect theBindings = {0,0,0,0};
		Rect ourRect;
		mResource->GetLayoutItem(i+1,theItem);
		theItem.CalculateItemRect(mResource,theRect,ourRect);
		theInfo.paneID = 0;
		theInfo.width = ourRect.right - ourRect.left;
		theInfo.height = ourRect.bottom - ourRect.top;
		theInfo.visible = true;
		theInfo.enabled = true;
		theInfo.bindings = theBindings;
		theInfo.left = ourRect.left;
		theInfo.top = ourRect.top;
		theInfo.superView = this;
		
		LLayoItemPane *thePane = new LLayoItemPane(theInfo,i + 1,this,inResource,theItem);
	}
	Show();
	Enable();
	if(inRefresh)
	{
		Refresh();
	}
}

CThemeDoc*	LLayoView::GetThemeDocument()
{
	TLayoEditDialogBox* theDialog = dynamic_cast<TLayoEditDialogBox*>(mSuperView);
	SignalIf_(theDialog == NULL);
	return theDialog->GetThemeDocument();
}

void	LLayoView::GetFlags(UInt32 &outVisibleFlags, UInt32 &outFeatureFlags)
{
	outVisibleFlags = mVisibleFlags;
	outFeatureFlags = mFeatureFlags;
	
}

void LLayoView::SetFlags(UInt32 inVisibleFlags, UInt32 inFeatureFlags, Boolean inRefresh /*= true */)
{
	mVisibleFlags = inVisibleFlags;
	mFeatureFlags = inFeatureFlags;
	if(inRefresh)
	{
		Refresh();
	}
}

void	LLayoView::SetShowLines(Boolean inShowLines, Boolean inRefresh /*= true*/)
{
	mShowLines = inShowLines;
	if(inRefresh)
	{
		Refresh();
	}
}

Boolean	LLayoView::GetShowLines()
{
	return mShowLines;
}