// ===========================================================================
//	UTClrListResource.cpp			   Allegro Themes Project
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


#include "UTClrListResource.h"

// ---------------------------------------------------------------------------

UTClrListResource::UTClrListResource()
{
}
			
UTClrListResource::~UTClrListResource()
{
}

void UTClrListResource::Init(ResIDT			inResID,
				ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/)
{
	UTResource::Init(kClrListResourceType, inResID, inResFileID, inCreate, inThrowFail);
}
			
Handle 	UTClrListResource::BuildBaseResource()
{
	Handle newRes = ::NewHandleClear(sizeof(UInt32));
	ThrowIfMemFail_(newRes);
	*((UInt32*)(*newRes)) = 0;
	return newRes;
}

void UTClrListResource::GetColor(UInt32 inIndex, RGBColor &outColor)
{
	Assert_(inIndex < Count());
	UInt32 offSet = sizeof(UInt32) + (sizeof(RGBColor) * inIndex);
	RGBColor *pRGB = ((RGBColor*)((*mResourceH) + offSet));
	outColor = *pRGB;
}

void UTClrListResource::SetColor(UInt32 inIndex, const RGBColor &inColor)
{
	Assert_(inIndex <= Count());
	UInt32 offSet = sizeof(UInt32) + (sizeof(RGBColor) * inIndex);
	RGBColor *pRGB = ((RGBColor*)((*mResourceH) + offSet));
	*pRGB = inColor;
	Dirty();
}
		
void UTClrListResource::InsertColor(UInt32 inIndex, const RGBColor &inColor)
{
	::SetHandleSize(mResourceH,::GetHandleSize(mResourceH) + sizeof(RGBColor));
	ThrowIfMemError_();
	if(inIndex < Count())
	{
		UInt32 offSet1 = sizeof(UInt32) + (sizeof(RGBColor) * inIndex);
		UInt32 offSet2 = offSet1 + sizeof(RGBColor);
		BlockMove((*mResourceH) + offSet1, 
						(*mResourceH) + offSet2,
						(Count() - inIndex) * sizeof(RGBColor));
		ThrowIfMemError_();
	}
	else
	{
		inIndex = Count();
	}
	SetCount(Count() + 1);
	SetColor(inIndex,inColor);
}

void UTClrListResource::AddColor(const RGBColor &inColor)
{
	InsertColor(Count(),inColor);
}

	
void UTClrListResource::DeleteColor(UInt32 inIndex)
{
	Assert_(Count() > 0 && inIndex > 0);
	if(inIndex < Count() && inIndex > 0)
	{
		UInt32 offSet1 = sizeof(UInt32) + (sizeof(RGBColor) * inIndex);
		UInt32 offSet2 = offSet1 + sizeof(RGBColor);
		BlockMove((*mResourceH) + offSet2,
						(*mResourceH) + offSet1, 
						(Count() - (inIndex + 1)) * sizeof(RGBColor));
		ThrowIfMemError_();
	}
	else
	{
		inIndex = Count();
	}
	::SetHandleSize(mResourceH,::GetHandleSize(mResourceH) - sizeof(RGBColor));
	ThrowIfMemError_();
	SetCount(Count() - 1);
	Dirty();
}

UInt32 UTClrListResource::Count()
{
	return *((UInt32*)(*mResourceH));
}

void UTClrListResource::SetCount(UInt32 inCount)
{
	*((UInt32*)(*mResourceH)) = inCount;
}
