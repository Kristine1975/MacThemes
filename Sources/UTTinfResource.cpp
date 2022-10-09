// ===========================================================================
//	UTTinfResource.cpp			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the Tinf resource
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
#include "UTTinfResource.h"
#include "TThemes.h"
// ---------------------------------------------------------------------------

#pragma mark ===INITIALIZERS
UTTinfResource::UTTinfResource()
{
}
			
UTTinfResource::~UTTinfResource()
{
}

void 
UTTinfResource::Init(
				ResIDT			inResID,
				ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/)
{
	UTFlacResource::Init(inResID, inResFileID, inCreate, inThrowFail,kTinfResourceType);
}
			
#pragma mark -
#pragma mark === GETTERS
SInt16 
UTTinfResource::GetHorizontalSliderTickLeftOffset()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);
	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfHorizontalSliderTickLeft,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetSliderThumbWidth()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfSliderHorizontalThumbWidth,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetSliderThumbHeight()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfSliderVerticalThumbHeight,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetMenuBarHeight()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfMenuBarHeight,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetHorizontalScrollBarThumbWidth()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfScrollHorizontalThumbWidth,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetMinimumColorDepth()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfMinimumColorDepth,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetMenuSeperatorHeight()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfMenuSeparatorHeight,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetMenuTitleLeftOffset()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfMenuTitleLeftOffset,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetMenuTitleRightOffset()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfMenuTitleRightOffset,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetVerticalScrollBarThumbHeight()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfScrollVerticalThumbHeight,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetSmallHorizontalScrollBarThumbWidth()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfSmallScrollHorizontalThumbWidth,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetSmallVerticalScrollBarThumbHeight()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfSmallScrollVerticalThumbHeight,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetVersion()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfVersion,0,&theSize,&theValue));
	return theValue;
}

SInt16 
UTTinfResource::GetVerticalSliderTickTopOffset()
{
	SInt16 theValue = 0;
	SInt32 theSize = sizeof(SInt16);

	ThrowIfOSErr_(GetCollectionItem(mCollection,kTinfVerticalSliderTickTop,0,&theSize,&theValue));
	return theValue;
}

#pragma mark -
#pragma mark === SETTERS
void 
UTTinfResource::SetHorizontalSliderTickLeftOffset(
			
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfVerticalSliderTickTop,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetSliderThumbWidth(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfSliderHorizontalThumbWidth,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetSliderThumbHeight(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfSliderVerticalThumbHeight,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetMenuBarHeight(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfMenuBarHeight,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetHorizontalScrollBarThumbWidth(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfScrollHorizontalThumbWidth,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetMinimumColorDepth(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfMinimumColorDepth,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetMenuSeperatorHeight(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfMenuSeparatorHeight,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetMenuTitleLeftOffset(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfMenuTitleLeftOffset,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetMenuTitleRightOffset(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfMenuTitleRightOffset,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetVerticalScrollBarThumbHeight(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfScrollVerticalThumbHeight,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetSmallHorizontalScrollBarThumbWidth(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfSmallScrollHorizontalThumbWidth,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetSmallVerticalScrollBarThumbHeight(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfSmallScrollVerticalThumbHeight,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetVersion(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfVersion,0,sizeof(SInt16),&inValue));
	Dirty();
}

void 
UTTinfResource::SetVerticalSliderTickTopOffset(
			SInt16 inValue)
{
	ThrowIfOSErr_(AddCollectionItem(mCollection,kTinfVerticalSliderTickTop,0,sizeof(SInt16),&inValue));
	Dirty();
}




