// ===========================================================================
//	UTPlutResource.h			   Allegro Themes Project
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


#ifndef _H_UTPlutResource
#define _H_UTPlutResource
#pragma once

#include "UTResource.h"

#define kPlutResourceType 'plut'

// ---------------------------------------------------------------------------

typedef struct 
{
	ResIDT brushppatID;
	RGBColor brushColor;
} PlutInternalEntry;

class PlutEntry
{
	public:
	FullResourceSpec brushPPAT;
	RGBColor brushColor;
	
	PlutEntry()
	{
		brushPPAT.resID = 0;
		brushPPAT.fileID = 0;
		brushPPAT.resType = 'ppat';
		brushColor.red = brushColor.blue = brushColor.green = 0;
	}
	
	PixPatHandle GetPlutPixPat() const
	{
		PixPatHandle tempHandle;
		ResFileID oldID = CurResFile();
		UseResFile(brushPPAT.fileID);
		tempHandle = GetPixPat(brushPPAT.resID);
		UseResFile(oldID);
		return tempHandle;
	}
	
	void PaintRect(const Rect &inRect,ImageAlignment inAlignment);
};

typedef struct
{
	UInt32 colorDepth;
	UInt16 unknown;
	UInt16 plutEntryCount;
} PlutHeader;

enum ColorDepth
{
	kBlackAndWhite=1,
	k4Colors=2,
	k16Colors=4,
	k256Colors=8,
	kThousandsOfColors=16,
	kMillionsOfColors=32
};

class	UTPlutResource : public UTResource
{
	public:
	UTPlutResource();							
	virtual ~UTPlutResource();
	void Init(ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true);
			
	virtual Handle 	BuildBaseResource();	

	void GetPlutEntry(UInt32 inIndex, PlutEntry &outPlut);
	void SetPlutEntry(UInt32 inIndex, const PlutEntry &inPlut);
	void InsertPlutEntry(UInt32 inIndex, const PlutEntry &inPlut);
	void AddPlutEntry(const PlutEntry &inPlut);
	void DeletePlutEntry(UInt32 inIndex);
	
	ColorDepth GetColorDepth();
	void SetColorDepth(ColorDepth inDepth);
	
	UInt16 Count();
	
	protected:
	void InternalToExternal(const PlutInternalEntry &inEntry, PlutEntry &outEntry);
	void ExternalToInternal(const PlutEntry &inEntry, PlutInternalEntry &outEntry);
	
	void SetCount(UInt16 inCount);
	
};

PlutEntryIndex ConvertPlutDataToIndex(Boolean isRequired, SInt32 inZeroBaseIndex);
void	ConvertIndexToPlutData(PlutEntryIndex inIndex, Boolean &outIsRequired, SInt32 &outZeroBaseIndex);
#endif
