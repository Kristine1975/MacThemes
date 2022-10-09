// ===========================================================================
//	UTLayoutResource.cpp			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the clr# resource
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


#include "UTLayoutResource.h"

// ---------------------------------------------------------------------------

UTLayoutResource::UTLayoutResource()
{
}
			
UTLayoutResource::~UTLayoutResource()
{
}

void UTLayoutResource::Init(ResIDT			inResID,
				ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/)
{
	UTResource::Init(kLayoResourceType, inResID, inResFileID, inCreate, inThrowFail);
	StHandleLocker theLock(mResourceH);
	mHeader = *((LayoutHeader*)(*mResourceH));
	char *theCoordPtr = (*mResourceH + sizeof(LayoutHeader));
	for(UInt32 i = 0; i < mHeader.coordinateCount; i++)
	{
		mLayoutCoordinates.AddItem(*((LayoutCoordinate*)theCoordPtr));
		theCoordPtr += sizeof(LayoutCoordinate);
	}
	LayoutItemCount theItemCount = *((LayoutItemCount*)theCoordPtr);
	theCoordPtr += sizeof(LayoutItemCount);
	LayoutItem *theItemPtr = (LayoutItem *)theCoordPtr;
	for(UInt32 i = 0; i < theItemCount; i++)
	{
		mLayoutItems.AddItem(theItemPtr[i]);
	}	
}
			
Handle 	UTLayoutResource::BuildBaseResource()
{
	Handle newRes = ::NewHandleClear(sizeof(LayoutHeader) + sizeof(LayoutItemCount));
	ThrowIfMemFail_(newRes);
	return newRes;
}

void	UTLayoutResource::Write(Boolean inUpdateResFile)
{
	
	SetHandleSize(mResourceH,sizeof(LayoutHeader) + sizeof(LayoutCoordinate) * CountCoordinates() 
							+ sizeof(LayoutItemCount) + sizeof(LayoutItem) * CountItems());
	StHandleLocker theLock(mResourceH);
	mHeader.coordinateCount = CountCoordinates();
	*((LayoutHeader*)(*mResourceH)) = mHeader;
	char *theCoordPtr = (char *)(*mResourceH + sizeof(LayoutHeader));	
	for(UInt32 i = 0; i < mHeader.coordinateCount; i++)
	{
		LayoutCoordinate theCoordinate;
		GetLayoutCoordinate(i+1,theCoordinate);
		*((LayoutCoordinate*)theCoordPtr) = theCoordinate;
		theCoordPtr += sizeof(LayoutCoordinate);
	}
	*((LayoutItemCount*)theCoordPtr) = CountItems();
	theCoordPtr += sizeof(LayoutItemCount);
	LayoutItem *theItemPtr = (LayoutItem *)theCoordPtr;
	for(UInt32 i = 0; i < CountItems(); i++)
	{
		LayoutItem theItem;
		GetLayoutItem(i+1,theItem);
		theItemPtr[i] = theItem;
	}
		
	UTResource::Write(inUpdateResFile);
}

void UTLayoutResource::GetLayoutItem(UInt32 inIndex, LayoutItem &outItem)
{
	mLayoutItems.FetchItemAt(inIndex,outItem);
}

void UTLayoutResource::SetLayoutItem(UInt32 inIndex, LayoutItem &inItem)
{
	mLayoutItems.AssignItemsAt(1,inIndex,inItem);
}

void UTLayoutResource::GetLayoutCoordinate(UInt32 inIndex, LayoutCoordinate &outCoordinate)

{
	mLayoutCoordinates.FetchItemAt(inIndex,outCoordinate);
}

void UTLayoutResource::SetLayoutCoordinate(UInt32 inIndex, LayoutCoordinate &inCoordinate)
{
	mLayoutCoordinates.AssignItemsAt(1,inIndex,inCoordinate);
}

UInt32 UTLayoutResource::CountItems()
{
	return mLayoutItems.GetCount();
}

UInt32 UTLayoutResource::CountCoordinates()
{
	return mLayoutCoordinates.GetCount();
}


#pragma mark  -

void LayoutItem::CalculateItemRect(UTLayoutResource *inResource, Rect &inRect, Rect &outRect)
{
	outRect.top = ResolveCoordinate(inResource,inRect,topCoordinate);
	outRect.left = ResolveCoordinate(inResource,inRect,leftCoordinate);
	outRect.bottom = ResolveCoordinate(inResource,inRect,bottomCoordinate);
	outRect.right = ResolveCoordinate(inResource,inRect,rightCoordinate);
}

SInt32 LayoutItem::ResolveCoordinate(UTLayoutResource *inResource,Rect &inDefaultRect, SInt16 inCoordinate)
{
	SInt32 theCoordinate = 0;
	switch(inCoordinate)
	{
		case kDefaultTopCoordinate:
		{
			theCoordinate = inDefaultRect.top;
		}
		break;
		
		case kDefaultLeftCoordinate:
		{
			theCoordinate = inDefaultRect.left;
		}
		break;
		
		case kDefaultBottomCoordinate:
		{
			theCoordinate = inDefaultRect.bottom;
		}
		break;
		
		case kDefaultRightCoordinate:
		{
			theCoordinate = inDefaultRect.right;
		}
		break;
		
		case 0:
		{
			SysBeep(1);
		}
		break;
		
		default:
		{
			LayoutCoordinate *theLayoutCoordinate = new LayoutCoordinate; //Doing this to cut down on recursive stack space.
			inResource->GetLayoutCoordinate(inCoordinate,*theLayoutCoordinate);
			if(theLayoutCoordinate->alignmentCoordinate1 == kStandardCoordinate)
			{
				theCoordinate = theLayoutCoordinate->offset1 + ResolveCoordinate(inResource,inDefaultRect,theLayoutCoordinate->coordinateReference1);
			}
			else if(theLayoutCoordinate->alignmentCoordinate1 == kCenterBetweenCoordinateRefs)
			{
				SInt32 coordinate1 = ResolveCoordinate(inResource,inDefaultRect,theLayoutCoordinate->coordinateReference1);
				SInt32 coordinate2 = ResolveCoordinate(inResource,inDefaultRect,theLayoutCoordinate->coordinateReference2);
				theCoordinate = theLayoutCoordinate->offset1 + coordinate1 + (coordinate2 - coordinate1) / 2;
			}
			else if(theLayoutCoordinate->alignmentCoordinate1 == kVariableCoordinate)
			{
				theCoordinate = theLayoutCoordinate->offset1 + ResolveCoordinate(inResource,inDefaultRect,theLayoutCoordinate->coordinateReference1);
			}
			else
			{
				SignalString_("\pUnknown Coordinate Alignment 1");
			}
			if(theLayoutCoordinate->alignmentCoordinate2 != kIgnoreCoordinate)
			{
				SInt32 coordinate2 = theLayoutCoordinate->offset2 + ResolveCoordinate(inResource,inDefaultRect,theLayoutCoordinate->coordinateReference2);
				if(theLayoutCoordinate->alignmentCoordinate2 == kConstrainTo)
				{
					if(theLayoutCoordinate->offset1 < 0)
					{
						theCoordinate = theCoordinate > coordinate2 ? theCoordinate : coordinate2;
					}
					else
					{
						theCoordinate = theCoordinate < coordinate2 ? theCoordinate : coordinate2;
					}
				}
			}
			delete theLayoutCoordinate;
		}
		break;
	}
	return theCoordinate;
}
