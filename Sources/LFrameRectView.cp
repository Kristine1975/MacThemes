// ===========================================================================
//	LFrameRectView.cp					PowerPlant 1.9.3	©1993-1998 Metrowerks Inc.
// ===========================================================================
//
//	Displays a 'PICT' resource
//
//	LFrameRectView stores the ID of a PICT resource as a member variable, and
//	always calls GetPicture() to get a Handle to the picture. It purposely
//	does not release the PICT resource when deleted, since other LFrameRectView
//	views may be using the same picture. For example, you might use the
//	same picture as a background or graphic element in multiple windows.
//
//	If you are concerned about the memory used by the PICT resource, mark
//	it as purgeable in your resource file.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "LFrameRectView.h"
#include <LStream.h>
#include <UDrawingState.h>
#include "CTPxmResource.h"
#include <ToolUtils.h>
#include "TThemes.h"
#include "UTPixUtilities.h"
#include <UStandardDialogs.h>
#include "LFrameView.h"
#include "UTFrmeResource.h"
#include <stdlib.h>


// ---------------------------------------------------------------------------
//	€ LFrameRectView								Default Constructor		  [public]
// ---------------------------------------------------------------------------

LFrameRectView::LFrameRectView(LFrameView *inView, SInt32 inInset)
{
	Init(inView);
	mFrameView = inView;
	mInset = inInset;
}



void LFrameRectView::Init(LFrameView *inView)
{
	mFrameView = inView;
	mFrameView->FocusDraw();
	mInset = 0;
}

LFrameRectView::~LFrameRectView()
{
}

PlutDragRecord		 LFrameRectView::GetPlutDragRec(SInt16 inIndex, bool isRequired)
{
	SignalIf_(mFrameView == NULL);
	return mFrameView->GetPlutDragRec(inIndex,isRequired);
}

void		LFrameRectView::FinishCreate()
{	
	LView::FinishCreate();
	for(UInt32 i = 1; i <= kPixelCount; i++)
	{
		LFramePixelPane *thePixel = new LFramePixelPane(this);
		thePixel->FinishCreate();
		thePixel->PutInside(this,true);
		mPixels.AddItem(thePixel);
	}
}

Boolean
LFrameRectView::IsHitBy(
	SInt32	inHorizPort,
	SInt32	inVertPort)
{
	for(UInt32 i = 1; i <= kPixelCount; i++)
	{
		if(mPixels[i]->IsHitBy(inHorizPort,inVertPort))
		{
			return true;
		}
	}
	return false;
}

Boolean
LFrameRectView::Contains(
	SInt32	inHorizPort,
	SInt32	inVertPort) const
{
	for(UInt32 i = 1; i <= kPixelCount; i++)
	{
		if(mPixels[i]->IsHitBy(inHorizPort,inVertPort))
		{
			return true;
		}
	}
	return false;
}

SInt32	LFrameRectView::GetInset()
{
	return mInset;
}

void	LFrameRectView::SetInset(SInt32 inInset)
{
	mInset = inInset;
}

Boolean 		LFrameRectView::GetCurrentSelectedPlutDragRec(PlutDragRecord &outRec)
{
	Boolean answer = false;
	if(mFrameView)
	{
		answer = mFrameView->GetCurrentSelectedPlutDragRec(outRec);
	}
	return answer;
}

UInt32	LFrameRectView::GetFrmeCount()
{
	UInt32 theFrameCount = 0;
	for(UInt32 i = 1; i <= kPixelCount; i++)
	{
		if(mPixels[i]->GetIsColoured())
		{
			if(theFrameCount == 0)
			{
				theFrameCount = 1;
			}
			UInt32 j;
			for(j = i + 1; j <= kPixelCount; j++)
			{
				LFramePixelPane *theIPixel, *theJPixel;
				mPixels.FetchItemAt(i,theIPixel);
				mPixels.FetchItemAt(j,theJPixel);
				if((theIPixel->GetIsColoured() == theJPixel->GetIsColoured() && theIPixel->GetPlutEntryIndex() == theJPixel->GetPlutEntryIndex()) && (theIPixel->GetPatternOrigin() == theJPixel->GetPatternOrigin()))
				{
					break;
				}
			}
			if(j == kPixelCount)
			{
				theFrameCount++;
			}
		}
	}
	return theFrameCount;
}

void	LFrameRectView::GetFrmeEntries(TArray<FrameEntry*> &outEntries)
{
	UInt32 theFrameCount = 0;
	for(UInt32 i = 1; i <= kPixelCount; i++)
	{
		if(mPixels[i]->GetIsColoured())
		{
			UInt32 j;
			for(j = 1; j <= outEntries.GetCount(); j++)
			{
				
				PlutEntryIndex theIndex = mPixels[i]->GetPlutEntryIndex();
				FrameOrigin theOrigin = mPixels[i]->GetPatternOrigin();
				if((theIndex == outEntries[j]->mPlutIndex) && (theOrigin == outEntries[j]->mPatternOrigin))
				{
					break;
				}
			}
			if(j == outEntries.GetCount() + 1)
			{
				FrameEntry *theEntry = new FrameEntry;
				outEntries.AddItem(theEntry);
				outEntries[j]->mInset = mInset;
				outEntries[j]->mPlutIndex = mPixels[i]->GetPlutEntryIndex();
				outEntries[j]->mPatternOrigin = mPixels[i]->GetPatternOrigin();
				outEntries[j]->mType = kType3Frame;
				theFrameCount++;
				
			}
			outEntries[j]->mPixels[i -1] = true;	
		}
	}
}

void
LFrameRectView::DrawSelf()
{
	// If Picture resource exists, draw it. Otherwise, fill the
	// Frame with a light gray pattern and a one-pixel border.
	FocusDraw();
	
	Rect	frame;
	CalcLocalFrameRect(frame);
	::PenNormal();
	
	ForeColor(blackColor);
	FrameRect(&frame);
}


void	LFrameRectView::AdaptToNewSurroundings()
{
	Rect theSuperFrame;
	mSuperView->CalcLocalFrameRect(theSuperFrame);
	
	SInt32	theMinimumInset = mFrameView->GetMinimumInset();
	SInt32	theMaximumInset = mFrameView->GetMaximumInset();
	SInt32 theInsetDelta = theMaximumInset - theMinimumInset;
	theInsetDelta = theInsetDelta < 0 ? theInsetDelta * -1 : theInsetDelta;
	SInt32 theSquareCount = (theInsetDelta + 1) * 2 + (kPixelCount / 4);
	
	
	SInt32 theSuperFrameHeight = theSuperFrame.bottom - theSuperFrame.top;
	SInt32 theSuperFrameWidth = theSuperFrame.right - theSuperFrame.left;
	ResizeFrameTo(theSuperFrameHeight,theSuperFrameWidth,false);
	PlaceInSuperFrameAt(0,0,false);
	
	SignalIfNot_(theSuperFrameHeight == theSuperFrameWidth);
	SInt32 theDimension = ((float)theSuperFrameHeight / theSquareCount) * mFrameView->GetMagnification();
	if(theDimension == 0)
	{
		theDimension = 1;
	}
	
	SInt32 theLongSide = (((theInsetDelta - labs(mInset - theMinimumInset))) + 1) * theDimension * 2;
	
	for(UInt32 i = 0; i < kPixelCount; i++)
	{
		if(i == (kPixelCount / 8) || i == (kPixelCount / 8 + kPixelCount / 2))
		{
			mPixels[i + 1]->ResizeFrameTo(theDimension,theLongSide ,false);
		}
		else if(i == (kPixelCount / 8 + kPixelCount / 4) || i == (kPixelCount / 8 + (kPixelCount / 4) * 3))
		{
			mPixels[i + 1]->ResizeFrameTo(theLongSide ,theDimension,false);
		}
		else
		{
			mPixels[i + 1]->ResizeFrameTo(theDimension,theDimension,false);
		}
		
	}
	
	SInt32 theCenteringOffset = (theSuperFrameHeight / 2) - (theDimension * theSquareCount / 2);
	SInt32 theCloseSideInset = theSuperFrame.left + ((labs(mInset - theMinimumInset)) * theDimension) + theCenteringOffset;
	SInt32 theFarSideInset = theSuperFrame.right - ((labs(mInset - theMinimumInset)) * theDimension) - theCenteringOffset;
	
	Rect theCenterRect;
	for(UInt32 i = 0; i < kPixelCount / 4; i++)
	{
		if(i == 0)
		{
			mPixels[i + 1]->PlaceInSuperFrameAt(theCloseSideInset,theFarSideInset - theDimension,true);
		}
		else
		{
			Rect theRect;
			SDimension16 theSize;
			mPixels[i + 1]->GetFrameSize(theSize);
			mPixels[i]->CalcLocalFrameRect(theRect);
			mPixels[i + 1]->PlaceInSuperFrameAt(theCloseSideInset,theRect.top - theSize.height,true);
			theCenterRect.left = theRect.right;
		}
	}
	
	for(UInt32 i = kPixelCount / 4 , j = 0; i < kPixelCount / 2; i++, j++)
	{
		Rect theRect;
		mPixels[i]->CalcLocalFrameRect(theRect);
		if(i == kPixelCount / 4)
		{
			SDimension16 theSize;
			mPixels[i + 1]->GetFrameSize(theSize);
			mPixels[i + 1]->PlaceInSuperFrameAt(theRect.left,theRect.top - theSize.height,true);
			
		}
		else
		{
			mPixels[i + 1]->PlaceInSuperFrameAt(theRect.right,theRect.top,true);
			theCenterRect.top = theRect.bottom;
		}
	}
	
	for(UInt32 i = kPixelCount / 2, j = 0; i < kPixelCount / 4 * 3; i++, j++)
	{
		Rect theRect;
		mPixels[i]->CalcLocalFrameRect(theRect);
		if(i == kPixelCount / 2)
		{
			mPixels[i + 1]->PlaceInSuperFrameAt(theRect.right,theRect.top,true);
			
		}
		else
		{
			mPixels[i + 1]->PlaceInSuperFrameAt(theRect.left,theRect.bottom,true);
			theCenterRect.right = theRect.left;
		}
	}
	
	for(UInt32 i = kPixelCount / 4 * 3, j = 0; i < kPixelCount; i++, j++)
	{
		Rect theRect;
		mPixels[i]->CalcLocalFrameRect(theRect);
		if(i == kPixelCount / 4 * 3)
		{
			mPixels[i + 1]->PlaceInSuperFrameAt(theRect.left,theRect.bottom,true);
			
		}
		else
		{
			SDimension16 theSize;
			mPixels[i + 1]->GetFrameSize(theSize);
			mPixels[i + 1]->PlaceInSuperFrameAt(theRect.left - theSize.width,theRect.top,true);
			theCenterRect.bottom = theRect.top;
		}
	}
	mFrameView->SetCenterRectangle(theCenterRect);
	LView::AdaptToNewSurroundings();
}

void LFrameRectView::SetPixel(PlutEntryIndex inIndex, UInt32 inPixelIndex,FrameOrigin inOrigin)
{
	mPixels[inPixelIndex + 1]->SetPlutEntryIndex(inIndex);
	mPixels[inPixelIndex + 1]->SetPatternOrigin(inOrigin);
}

Boolean LFrameRectView::ShowGrid(Boolean &outDoItInColor)
{
	return mFrameView->ShowGrid(outDoItInColor);
}

void LFrameRectView::SetIsModified(Boolean inModified /*= true*/)
{
	mFrameView->SetIsModified(inModified);
}

void LFrameRectView::GetFrameRect(Rect &inRect)
{
	mFrameView->CalcLocalFrameRect(inRect);
}