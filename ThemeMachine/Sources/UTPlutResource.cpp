// ===========================================================================
//	UTPlutResource.cpp			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the plut resource
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


#include "UTPlutResource.h"
#include "TThemes.h"
#include "UTPixUtilities.h"
// ---------------------------------------------------------------------------

UTPlutResource::UTPlutResource()
{
}
			
UTPlutResource::~UTPlutResource()
{
}

void UTPlutResource::Init(ResIDT			inResID,
				ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/)
{
	UTResource::Init(kPlutResourceType, inResID, inResFileID, inCreate, inThrowFail);
}
			
Handle 	UTPlutResource::BuildBaseResource()
{
	Handle newRes = ::NewHandleClear(sizeof(PlutHeader));
	ThrowIfMemFail_(newRes);
	((PlutHeader*)(*newRes))->colorDepth = k256Colors;
	((PlutHeader*)(*newRes))->unknown = kPlutUnknownValue1;
	return newRes;
}

UInt16 UTPlutResource::Count()
{
	return ((PlutHeader*)(*mResourceH))->plutEntryCount;
}

void UTPlutResource::SetCount(UInt16 inCount)
{
	((PlutHeader*)(*mResourceH))->plutEntryCount = inCount;
}

void UTPlutResource::GetPlutEntry(UInt32 inIndex, PlutEntry &outPlut)
{
	Assert_(inIndex < Count());
	UInt32 offSet = sizeof(PlutHeader) + (sizeof(PlutInternalEntry) * inIndex);
	PlutInternalEntry *pPlut = ((PlutInternalEntry*)((*mResourceH) + offSet));
	InternalToExternal(*pPlut,outPlut);

}

void UTPlutResource::SetPlutEntry(UInt32 inIndex, const PlutEntry &inPlut)
{
	Assert_(inIndex <= Count());
	UInt32 offSet = sizeof(PlutHeader) + (sizeof(PlutInternalEntry) * inIndex);
	PlutInternalEntry *pPlut = ((PlutInternalEntry*)((*mResourceH) + offSet));
	ExternalToInternal(inPlut,*pPlut);
	Dirty();

}

void UTPlutResource::InsertPlutEntry(UInt32 inIndex, const PlutEntry &inPlut)
{
	::SetHandleSize(mResourceH,::GetHandleSize(mResourceH) + sizeof(PlutInternalEntry));
	ThrowIfMemError_();
	if(inIndex < Count())
	{
		UInt32 offSet1 = sizeof(PlutHeader) + (sizeof(PlutInternalEntry) * inIndex);
		UInt32 offSet2 = offSet1 + sizeof(PlutInternalEntry);
		BlockMove((*mResourceH) + offSet1, 
						(*mResourceH) + offSet2,
						(Count() - inIndex) * sizeof(PlutInternalEntry));
		ThrowIfMemError_();
	}
	else
	{
		inIndex = Count();
	}
	SetCount(Count() + 1);
	SetPlutEntry(inIndex,inPlut);
}

void UTPlutResource::AddPlutEntry(const PlutEntry &inPlut)
{
	InsertPlutEntry(Count(),inPlut);
}

void UTPlutResource::DeletePlutEntry(UInt32 inIndex)
{
	Assert_(Count() > 0 && inIndex >= 0);
	if(inIndex < Count() && inIndex >= 0)
	{
		UInt32 offSet1 = sizeof(PlutHeader) + (sizeof(PlutInternalEntry) * inIndex);
		UInt32 offSet2 = offSet1 + sizeof(PlutInternalEntry);
		BlockMove((*mResourceH) + offSet2,
						(*mResourceH) + offSet1, 
						(Count() - (inIndex + 1)) * sizeof(PlutInternalEntry));
		ThrowIfMemError_();
	}
	else
	{
		inIndex = Count();
	}
	::SetHandleSize(mResourceH,::GetHandleSize(mResourceH) - sizeof(PlutInternalEntry));
	ThrowIfMemError_();
	SetCount(Count() - 1);
	Dirty();

}

ColorDepth UTPlutResource::GetColorDepth()
{
	return (ColorDepth)(((PlutHeader*)(*mResourceH))->colorDepth);
}

void UTPlutResource::SetColorDepth(ColorDepth inDepth)
{
	((PlutHeader*)(*mResourceH))->colorDepth = inDepth;
	Dirty();
}

void UTPlutResource::InternalToExternal(const PlutInternalEntry &inEntry, PlutEntry &outEntry)
{
	outEntry.brushPPAT.resID = inEntry.brushppatID;
	outEntry.brushPPAT.resType = 'ppat';
	outEntry.brushPPAT.fileID = mSpec.fileID;
	outEntry.brushColor = inEntry.brushColor;
}

void UTPlutResource::ExternalToInternal(const PlutEntry &inEntry, PlutInternalEntry &outEntry)
{
	outEntry.brushppatID = inEntry.brushPPAT.resID;
	outEntry.brushColor = inEntry.brushColor;
}

//Some Utility functions
PlutEntryIndex ConvertPlutDataToIndex(Boolean isRequired, SInt32 inZeroBaseIndex)
{
	PlutEntryIndex  theIndex = 0;
	theIndex = inZeroBaseIndex + 1;
	if(!isRequired)
	{
		theIndex *= -1;
	}
	return theIndex;
}

void	ConvertIndexToPlutData(PlutEntryIndex inIndex, Boolean &outIsRequired, SInt32 &outZeroBaseIndex)
{
	outIsRequired = inIndex > 1;
	if(!outIsRequired)
	{
		inIndex *= -1;
	}
	outZeroBaseIndex = inIndex - 1;
}

#pragma mark -
void PlutEntry::PaintRect(const Rect &inRect, ImageAlignment inAlignment)
{
	if(brushPPAT.resID == 0)
	{
		RGBForeColor(&brushColor);
		::PaintRect(&inRect);
	}
	else
	{
		PixPatHandle thePattern = GetPlutPixPat();
		UTPixUtilities::FillCRectAligned(inRect,thePattern,inAlignment);
		DisposePixPat(thePattern);
	}
}