// ===========================================================================
//	UTTdatResource.cpp			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the tdat resource
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
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

#include "UTTdatResource.h"

// ---------------------------------------------------------------------------

#pragma mark === INITIALIZATION
// ---------------------------------------------------------------------------
//	€ UTTdatResource					Default Constructor		  [public]
// ---------------------------------------------------------------------------
UTTdatResource::UTTdatResource()
{
}

// ---------------------------------------------------------------------------
//	€ ~UTTdatResource					Default Destructor		  [public]
// ---------------------------------------------------------------------------	
UTTdatResource::~UTTdatResource()
{
}

// ---------------------------------------------------------------------------
//	€ Init								Two Step Initialization		  [public]
// ---------------------------------------------------------------------------	
void 
UTTdatResource::Init(ResIDT			inResID,
				ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/)
{
	UTResource::Init(kTdatResourceType, inResID, inResFileID, inCreate, inThrowFail);
}
	
#pragma mark -
#pragma mark === BASE	

// ---------------------------------------------------------------------------
//	€ BuildBaseResource													  [public]
// ---------------------------------------------------------------------------	
Handle 	
UTTdatResource::BuildBaseResource()
{
	Handle newRes = ::NewHandleClear(0);
	ThrowIfMemFail_(newRes);
	return newRes;
}

#pragma mark -
#pragma mark === ACCESSORS

// ---------------------------------------------------------------------------
//	€ GetTdatEntry													  [public]
// ---------------------------------------------------------------------------	
void 
UTTdatResource::GetTdatEntry(
				UInt32 inIndex, 
				TdatEntry &outTdatEntry)
{
	Assert_(inIndex < Count());
	UInt32 offSet =(sizeof(TdatEntry) * inIndex);
	TdatEntry *pTic = ((TdatEntry*)((*mResourceH) + offSet));
	outTdatEntry = *pTic;
}

// ---------------------------------------------------------------------------
//	€ SetTdatEntry													  [public]
// ---------------------------------------------------------------------------	
void 
UTTdatResource::SetTdatEntry(
				UInt32 inIndex, 
				const TdatEntry &inTdatEntry)
{
	Assert_(inIndex <= Count());
	UInt32 offSet = (sizeof(TdatEntry) * inIndex);
	TdatEntry *pTic = ((TdatEntry*)((*mResourceH) + offSet));
	*pTic = inTdatEntry;
	Dirty();
}

// ---------------------------------------------------------------------------
//	€ FindTdatEntry													  [public]
// ---------------------------------------------------------------------------	
UInt32 
UTTdatResource::FindTdatEntry(
				OSType inType, 
				ResIDT inID, 
				TdatEntry &outTdatEntry)
{
	UInt32 i = 0;
	for(i = 0; i < Count(); i++)
	{
		TdatEntry theEntry;
		GetTdatEntry(i,theEntry);
		if(theEntry.mResType == inType && theEntry.mResID1 == inID)
		{
			outTdatEntry = theEntry;
			break;
		}
	}
	if(i == Count())
	{
		i = -1;
	}
	return i;
}

// ---------------------------------------------------------------------------
//	€ InsertTdatEntry													  [public]
// ---------------------------------------------------------------------------	
void 
UTTdatResource::InsertTdatEntry(
				UInt32 inIndex, 
				const TdatEntry &inTdatEntry)
{
	//count must be cached here, because the SetHandleSize will change the value of count
	UInt32 theCount = Count();
	::SetHandleSize(mResourceH,::GetHandleSize(mResourceH) + sizeof(TdatEntry));
	ThrowIfMemError_();
	if(inIndex < theCount)
	{
		UInt32 theOffset1 = (sizeof(TdatEntry) * inIndex);
		UInt32 theOffSet2 = theOffset1 + sizeof(TdatEntry);
		BlockMove((*mResourceH) + theOffset1, 
						(*mResourceH) + theOffSet2,
						(theCount - inIndex) * sizeof(TdatEntry));
		ThrowIfMemError_();
	}
	else
	{
		inIndex = theCount;
	}
	SetTdatEntry(inIndex,inTdatEntry);
}

// ---------------------------------------------------------------------------
//	€ AddTdatEntry													  [public]
// ---------------------------------------------------------------------------	
void 
UTTdatResource::AddTdatEntry(
				const TdatEntry &inTdatEntry)
{
	InsertTdatEntry(Count(),inTdatEntry);
}

// ---------------------------------------------------------------------------
//	€ DeleteTdatEntry													  [public]
// ---------------------------------------------------------------------------		
void 
UTTdatResource::DeleteTdatEntry(UInt32 inIndex)
{
	Assert_(Count() > 0 && inIndex >= 0);
	if(inIndex < Count() && inIndex >= 0)
	{
		UInt32 theOffset1 = (sizeof(TdatEntry) * inIndex);
		UInt32 theOffSet2 = theOffset1 + sizeof(TdatEntry);
		BlockMove((*mResourceH) + theOffSet2,
						(*mResourceH) + theOffset1, 
						(Count() - (inIndex + 1)) * sizeof(TdatEntry));
		ThrowIfMemError_();
	}
	::SetHandleSize(mResourceH,::GetHandleSize(mResourceH) - sizeof(TdatEntry));
	ThrowIfMemError_();
	Dirty();
}

// ---------------------------------------------------------------------------
//	€ Count													  [public]
// ---------------------------------------------------------------------------		
UInt32 
UTTdatResource::Count()
{
	return ::GetHandleSize(mResourceH) / sizeof(TdatEntry);
}

