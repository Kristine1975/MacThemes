// ===========================================================================
//	UTFrmeResource.cpp			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the Frme resource
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Dec 22/98 Initial Implementation
//
// --------------------------------------------------------------
// Theme Machine - A Theme Editor For MacOS
//	Copyright (C) 1999  Allegro Themes Project

//	This program is free software; you can redistribute it and/or
//	modify it under the terms of the GNU General Public License
//	as published by the Free Software Foundation; either version 2
//	of the License, or (at your option) any later version.

//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.

//	You should have received a copy of the GNU General Public License
//	along with this program; if not, write to the Free Software
//	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// To contact the authors
// mail - macthemes@onelist.com
// --------------------------------------------------------------


#include "UTFrmeResource.h"
#include "TThemes.h"
#include "TBrushTable.h"
#include "CThemeDoc.h"
#include "UTPixUtilities.h"

const UInt32 kPixelCount = 64;
// ---------------------------------------------------------------------------

UTFrmeResource::UTFrmeResource()
{
}
			
UTFrmeResource::~UTFrmeResource()
{
}

void UTFrmeResource::Init(
				ResIDT			inResID,
				ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/,
				ResType			inResType /*= kFrmeResourceType*/)
{
	UTResource::Init(inResType, inResID, inResFileID, inCreate, inThrowFail);
	StHandleLocker theLock(mResourceH);
	mType = (FrameType)((FrameHeaderResourcePtr)(*mResourceH))->type;
	mUnknown1 = ((FrameHeaderResourcePtr)(*mResourceH))->unknown1;
	mPatternOrigin = ((FrameHeaderResourcePtr)(*mResourceH))->patternOrigin;
	mMinimumInset = ((FrameHeaderResourcePtr)(*mResourceH))->minimumInset;
	mUnknown2 = ((FrameHeaderResourcePtr)(*mResourceH))->unknown2;
	mMaximumInset = ((FrameHeaderResourcePtr)(*mResourceH))->maximumInset;
	mBackgroundPlutID = ((FrameHeaderResourcePtr)(*mResourceH))->backgroundPlutID;
	Ptr thePtr = *mResourceH + sizeof(FrameHeaderResource);
	for(UInt32 i = 0; i < ((FrameHeaderResourcePtr)(*mResourceH))->frameCount; i++)
	{
		FrameEntry* theFrame = new FrameEntry();
		theFrame->mType = mType;
		theFrame->Read(thePtr);
		AddFrame(theFrame);
	}
}
			
Handle 	UTFrmeResource::BuildBaseResource()
{
	Handle newRes = ::NewHandleClear(0);
	ThrowIfMemFail_(newRes);
	mType = kType3Frame;
	mUnknown1 = 0;
	mPatternOrigin = frameOriginRightTop;
	mMinimumInset = 0;
	mUnknown2 = 0;
	mMaximumInset = 0;
	mBackgroundPlutID = 0;
	return newRes;
}

void	UTFrmeResource::Write(Boolean inUpdateResFile)
{
	UInt32 frameSize = 0;
	if(GetFrameCount() > 0)
	{
		FrameEntry *theFrame;
		FetchFrameAt(1,theFrame);
		frameSize = theFrame->GetSize() * GetFrameCount();
	}
	SetHandleSize(mResourceH,sizeof(FrameHeaderResource) + frameSize);
	((FrameHeaderResourcePtr)(*mResourceH))->type = mType;
	((FrameHeaderResourcePtr)(*mResourceH))->unknown1 = mUnknown1;
	((FrameHeaderResourcePtr)(*mResourceH))->patternOrigin = mPatternOrigin;
	((FrameHeaderResourcePtr)(*mResourceH))->minimumInset = mMinimumInset;
	((FrameHeaderResourcePtr)(*mResourceH))->unknown2 = mUnknown2;
	((FrameHeaderResourcePtr)(*mResourceH))->maximumInset = mMaximumInset;
	((FrameHeaderResourcePtr)(*mResourceH))->backgroundPlutID = mBackgroundPlutID;
	((FrameHeaderResourcePtr)(*mResourceH))->frameCount = GetFrameCount();
	Ptr thePtr = *mResourceH + sizeof(FrameHeaderResource);
	for(UInt32 i = 0; i < ((FrameHeaderResourcePtr)(*mResourceH))->frameCount; i++)
	{
		FrameEntry* theFrame;
		FetchFrameAt(i+1,theFrame);
		theFrame->Write(thePtr);
	}
	UTResource::Write(inUpdateResFile);
}

void UTFrmeResource::Dispose()
{
	while(GetFrameCount() > 0)
	{
		RemoveFrameAt(1);
	}
	UTResource::Dispose();
}

FrameType UTFrmeResource::GetType()
{
	return mType;
}

void UTFrmeResource::SetType(FrameType inType)
{
	mType = inType;
}

UInt32 		UTFrmeResource::GetFrameCount()
{
	return mFrames.GetCount();
}

ResID 		UTFrmeResource::GetBackgroundPlutID()
{
	return mBackgroundPlutID;
}

void 		UTFrmeResource::SetBackgroundPlutID(PlutEntryIndex inPlut)
{
	mBackgroundPlutID = inPlut;
	Dirty();
}

SInt8 		UTFrmeResource::GetMinimumInset()
{
	return mMinimumInset;
}

void 		UTFrmeResource::SetMinimumInset(SInt8 inInset)
{
	mMinimumInset = inInset;
	Dirty();
}

SInt8 		UTFrmeResource::GetMaximumInset()
{
	return mMaximumInset;
}

void 		UTFrmeResource::SetMaximumInset(SInt8 inInset)
{
	mMaximumInset = inInset;
	Dirty();
}

FrameOrigin	UTFrmeResource::GetPatternOrigin()
{
	return mPatternOrigin;
}

void		UTFrmeResource::SetPatternOrigin(FrameOrigin inOrigin)
{
	mPatternOrigin = inOrigin;
	Dirty();
}
	
void	UTFrmeResource::FetchFrameAt(ArrayIndexT inIndex, FrameEntry* &outEntry)
{
	mFrames.FetchItemAt(inIndex,outEntry);
}

void UTFrmeResource::RemoveFrameAt(ArrayIndexT inIndex)
{
	mFrames.RemoveItemsAt(1,inIndex);
}

void		UTFrmeResource::AddFrame(FrameEntry* inFrame)
{
	mFrames.AddItem(inFrame);
}

void		UTFrmeResource::InsertFrameAt(FrameEntry* inFrame,ArrayIndexT inIndex)
{
	mFrames.InsertItemsAt(1,inIndex,inFrame);
}

void 	UTFrmeResource::PaintRect(Rect &inRect, CThemeDoc *inDoc)
{
	Rect bigRect = inRect;
	InsetRect(&bigRect,GetMinimumInset(),GetMinimumInset());
	
	StClipRgnState theState(bigRect);
	for(UInt32 j = 0; j < GetFrameCount(); j++)
	{
		FrameEntry *theEntry;
		FetchFrameAt(j + 1,theEntry);
		StRegion theClipRgn;
		OpenRgn();
		for(UInt32 i = 0; i < kPixelCount / 4; i++)
		{
			if(theEntry->mPixels[i])
			{
				Rect thePixRect;
				if(i == (kPixelCount / 8))
				{
					thePixRect.left = inRect.left + theEntry->mInset;
					thePixRect.right = thePixRect.left + 1;
					thePixRect.bottom = inRect.bottom - 8 - theEntry->mInset;
					thePixRect.top = inRect.top + 8 + theEntry->mInset;
				}
				else
				{
					thePixRect.left = inRect.left + theEntry->mInset;
					thePixRect.right = thePixRect.left + 1;
					if(i < (kPixelCount / 8))
					{
						thePixRect.bottom = inRect.bottom - i - theEntry->mInset;
						thePixRect.top = thePixRect.bottom - 1;
					}
					else
					{
						thePixRect.top = inRect.top + theEntry->mInset + (8 - (i - kPixelCount / 8));
						thePixRect.bottom = thePixRect.top + 1;
					}
				}
				FrameRect(&thePixRect);
			}
		}
		
		for(UInt32 i = kPixelCount / 4 , j = 0; i < kPixelCount / 2; i++, j++)
		{	
			if(theEntry->mPixels[i])
			{
				Rect thePixRect;
				if(i == (kPixelCount / 8 + kPixelCount / 4))
				{
					thePixRect.left = inRect.left + 8 + theEntry->mInset;
					thePixRect.right = inRect.right - 8 - theEntry->mInset;
					thePixRect.top = inRect.top  + theEntry->mInset;
					thePixRect.bottom = thePixRect.top + 1;
				}
				else
				{
					thePixRect.top = inRect.top  + theEntry->mInset;
					thePixRect.bottom = thePixRect.top + 1;
					if(i < (kPixelCount / 8 + kPixelCount / 4))
					{
						thePixRect.left = inRect.left + j + theEntry->mInset;
						thePixRect.right = thePixRect.left + 1;
					}
					else
					{
						thePixRect.right = inRect.right - theEntry->mInset - (8 - (j - kPixelCount / 8));
						thePixRect.left = thePixRect.right - 1;
					}
				}
				FrameRect(&thePixRect);
			}
			
		}
		
		for(UInt32 i = kPixelCount / 2, j = 0; i < kPixelCount / 4 * 3; i++, j++)
		{
			if(theEntry->mPixels[i])
			{
				Rect thePixRect;
				if(i == (kPixelCount / 8 + kPixelCount / 2))
				{
					thePixRect.right = inRect.right - theEntry->mInset;
					thePixRect.left = thePixRect.right - 1;
					thePixRect.bottom = inRect.bottom - 8 - theEntry->mInset;
					thePixRect.top = inRect.top + 8 + theEntry->mInset;
				}
				else
				{
					thePixRect.right = inRect.right - theEntry->mInset;
					thePixRect.left = thePixRect.right - 1;
					if(i < (kPixelCount / 8 + kPixelCount / 2))
					{
						thePixRect.top = inRect.top + j + theEntry->mInset;
						thePixRect.bottom = thePixRect.top + 1;
					}
					else
					{
						thePixRect.bottom = inRect.bottom - theEntry->mInset - (8 - (j - kPixelCount / 8));
						thePixRect.top = thePixRect.bottom - 1;
					}
				}
				FrameRect(&thePixRect);
			}
		}
		
		for(UInt32 i = kPixelCount / 4 * 3, j = 0; i < kPixelCount; i++, j++)
		{
			if(theEntry->mPixels[i])
			{
				Rect thePixRect;
				if(i == (kPixelCount / 8 + (kPixelCount / 4) * 3))
				{
					thePixRect.right = inRect.right - 8 - theEntry->mInset;
					thePixRect.left = inRect.left + 8 + theEntry->mInset;
					thePixRect.bottom = inRect.bottom - theEntry->mInset;
					thePixRect.top = thePixRect.bottom  - 1;
					
				}
				else
				{
					thePixRect.bottom = inRect.bottom - theEntry->mInset;
					thePixRect.top = thePixRect.bottom  - 1;
					if(i < (kPixelCount / 8 + (kPixelCount / 4) * 3))
					{
						thePixRect.right = inRect.right - j - theEntry->mInset;
						thePixRect.left = thePixRect.right - 1;
					}
					else
					{
						thePixRect.left = inRect.left + theEntry->mInset + (8 - (j - kPixelCount / 8));
						thePixRect.right = thePixRect.left +1;
					}
				}
				FrameRect(&thePixRect);
			}
		}
		CloseRgn(theClipRgn);
		SetClip(theClipRgn);
		
		PlutDragRecord thePlutDragEntry = inDoc->GetPlutDragRec(theEntry->mPlutIndex);
		if(thePlutDragEntry.aPlut.brushPPAT.resID == 0)
		{
			RGBForeColor(&thePlutDragEntry.aPlut.brushColor);
			::PaintRect(&bigRect);
		}
		else
		{
			PixPatHandle thePattern = thePlutDragEntry.aPlut.GetPlutPixPat();
			ImageAlignment theAlignment;
			switch(theEntry->mPatternOrigin)
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
			
			UTPixUtilities::FillCRectAligned(bigRect,thePattern,theAlignment);
			DisposePixPat(thePattern);
		}
	}	
	Rect theSmallRect = inRect;
	InsetRect(&theSmallRect,GetMaximumInset(),GetMaximumInset());
	ClipRect(&theSmallRect);
	if(mBackgroundPlutID)
	{
		PlutDragRecord thePlutDragEntry = inDoc->GetPlutDragRec(mBackgroundPlutID);
		if(thePlutDragEntry.aPlut.brushPPAT.resID == 0)
		{
			RGBForeColor(&thePlutDragEntry.aPlut.brushColor);
			::PaintRect(&bigRect);
		}
		else
		{
			PixPatHandle thePattern = thePlutDragEntry.aPlut.GetPlutPixPat();
			ImageAlignment theAlignment;
			switch(mPatternOrigin)
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
			
			UTPixUtilities::FillCRectAligned(bigRect,thePattern,theAlignment);
			DisposePixPat(thePattern);
		}
	}
}

#pragma mark -
FrameEntry::FrameEntry()
{
	mType = kType3Frame;
	for(UInt32 i = 0; i < 64; i++)
	{
		mPixels[i] = false;
	}
	mInset = 0;
	mPatternOrigin = frameOriginRightTop;
	mPlutIndex = 0;
}

void FrameEntry::Read(Ptr &inPtr)
{
	if(mType == kType2Frame)
	{
		mPatternOrigin = ((FrameEntry2ResourcePtr)inPtr)->patternOrigin;
		mInset = ((FrameEntry2ResourcePtr)inPtr)->inset;
		mPlutIndex = ((FrameEntry2ResourcePtr)inPtr)->plutIndex;
		
		for(UInt32 j = 0; j < 4; j++)
		{
			UInt8 *thePtr = &(((FrameEntry2ResourcePtr)inPtr)->leftSide) + (sizeof(UInt8) * j);
			UInt8 mask = 0x80;
			
			for(UInt32 i = 0; i < 8; i++)
			{
				mPixels[((j * 8) + i) * 2] = ((*thePtr) & mask) != 0;
				mPixels[((j * 8) + i) * 2 + 1] = ((*thePtr) & mask) != 0;
				mask = mask / 2;
			}
		}
	}
	else if(mType == kType3Frame)
	{
		mPatternOrigin = ((FrameEntry2ResourcePtr)inPtr)->patternOrigin;
		mInset = ((FrameEntry2ResourcePtr)inPtr)->inset;
		mPlutIndex = ((FrameEntry2ResourcePtr)inPtr)->plutIndex;
		
		for(UInt32 j = 0; j < 4; j++)
		{
			UInt16 *thePtr = (UInt16*) (((char*)&(((FrameEntry3ResourcePtr)inPtr)->leftSide)) + (sizeof(UInt16) * j));
			UInt16 mask = 0x8000;
			
			for(UInt32 i = 0; i < 16; i++)
			{
				mPixels[(j * 16) + i] = ((*thePtr) & mask) != 0;
				mask = mask / 2;
			}
		}
	}
	else
	{
		SignalIf_(true);
	}
	inPtr += GetSize();
}

void FrameEntry::Write(Ptr &outPtr)
{
	if(mType == kType2Frame)
	{
		/*((FrameEntry2ResourcePtr)outPtr)->unknown = mUnknown;
		((FrameEntry2ResourcePtr)outPtr)->inset = mInset;
		((FrameEntry2ResourcePtr)outPtr)->plutIndex = mPlutIndex;
		((FrameEntry2ResourcePtr)outPtr)->leftSide = mLeftSide;
		((FrameEntry2ResourcePtr)outPtr)->topSide = mTopSide;
		((FrameEntry2ResourcePtr)outPtr)->rightSide = mRightSide;
		((FrameEntry2ResourcePtr)outPtr)->bottomSide = mBottomSide;*/
		
	}
	else if(mType == kType3Frame)
	{
		((FrameEntry3ResourcePtr)outPtr)->patternOrigin = mPatternOrigin;
		((FrameEntry3ResourcePtr)outPtr)->inset = mInset;
		((FrameEntry3ResourcePtr)outPtr)->plutIndex = mPlutIndex;
		for(UInt32 j = 0; j < 4; j++)
		{
			UInt32 offset = sizeof(UInt16) * j;
			UInt16 *thePtr = (UInt16*) (((char*)&(((FrameEntry3ResourcePtr)outPtr)->leftSide)) + offset);
			*thePtr = 0;
			UInt16 mask = 0x8000;
			for(UInt32 i = 0; i < 16; i++)
			{
				if(mPixels[(j * 16) + i])
				{
					(*thePtr) |= mask;
				}
				mask = mask / 2;
			}
		}
	}
	else
	{
		SignalIf_(true);
	}
	outPtr += GetSize();
}

UInt32 FrameEntry::GetSize()
{
	UInt32 size;
	if(mType == kType2Frame)
	{
		size = sizeof(FrameEntry2Resource);
	}
	else if(mType == kType3Frame)
	{
		size = sizeof(FrameEntry3Resource);
	}
	else
	{
		SignalIf_(true);
	}
	return size;
}