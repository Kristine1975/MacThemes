// ===========================================================================
//	UTLayoutResource.h			   Allegro Themes Project
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


#ifndef _H_UTLayoutResource
#define _H_UTLayoutResource
#pragma once

#include "UTResource.h"
#include <TArray.h>
#define kLayoResourceType 'layo'

class UTLayoutResource;
// ---------------------------------------------------------------------------

enum
{
	kNoCoordinate = 0,
	kDefaultTopCoordinate = -1,
	kDefaultLeftCoordinate = -2,
	kDefaultBottomCoordinate = -3,
	kDefaultRightCoordinate = -4
};



enum
{
	kStandardCoordinate = 0,
	kVariableCoordinate = 1,
	kCenterBetweenCoordinateRefs = 2,
	kIgnoreCoordinate = 0,
	kConstrainTo = 1
};

typedef UInt16 LayoutItemCount;

class LayoutHeader
{
	public:
	UInt32 version;
	UInt16 unknown1;
	UInt16 coordinateCount;
};

class LayoutCoordinate
{
	public:
	SInt16 alignmentCoordinate1;
	SInt16 offset1;
	SInt16 coordinateReference1;
	SInt16 alignmentCoordinate2;
	SInt16 offset2;
	SInt16 coordinateReference2;
	UInt32 unknown1;
};

class LayoutItem
{
	public:
	UInt32 visibleFlags;
	UInt32 invisibleFlags;
	UInt32 featureFlags;
	SInt16 topCoordinate;
	SInt16 leftCoordinate;
	SInt16 bottomCoordinate;
	SInt16 rightCoordinate;
	UInt32 refcon;
	ResType type;
	ResID itemID;
	ImageAlignment alignment;
	SInt16 itemIndex;
	SInt16 unknown1;
	UInt32 unknown2;
	
	void CalculateItemRect(UTLayoutResource *inResource, Rect &inRect, Rect &outRect);
	static SInt32 ResolveCoordinate(UTLayoutResource *inResource,Rect &inDefaultRect, SInt16 inCoordinate);

};

class	UTLayoutResource : public UTResource
{
	public:
	UTLayoutResource();							
	virtual ~UTLayoutResource();
	void Init(ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true);
			
	virtual Handle 	BuildBaseResource();	
	virtual void	Write(Boolean			inUpdateResFile = true);
	void GetLayoutItem(UInt32 inIndex, LayoutItem &outItem);
	void SetLayoutItem(UInt32 inIndex, LayoutItem &inItem);
	void GetLayoutCoordinate(UInt32 inIndex, LayoutCoordinate &outCoordinate);
	void SetLayoutCoordinate(UInt32 inIndex, LayoutCoordinate &inCoordinate);
	UInt32 CountItems();
	UInt32 CountCoordinates();
	
	protected:
	
	operator Handle()	{ return mResourceH; }
				
	Handle	Get()		{ return mResourceH; }
	
	#pragma warn_hidevirtual off
	TArray<LayoutItem> mLayoutItems;
	TArray<LayoutCoordinate> mLayoutCoordinates;
	#pragma warn_hidevirtual reset
	LayoutHeader mHeader;
};

#endif
