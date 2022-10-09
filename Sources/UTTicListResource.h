// ===========================================================================
//	UTTicListResource.h			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the tic# resource
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


#ifndef _H_UTTicListResource
#define _H_UTTicListResource
#pragma once

#include "UTResource.h"
#define kTicListResourceType 'tic#'

// ---------------------------------------------------------------------------
// We have to mac68k align this because it's 6 bytes in size, and I use sizeof on
// it. If we didn't mac68k align it, we'd get 8 bytes, and that's just plain
// wrong.
// Davem

#if PRAGMA_STRUCT_ALIGN
	#pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
	#pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
	#pragma pack(2)
#endif

typedef struct
{
	OSType iconSignature;
	SInt16 icnsID;
} TicEntry;

#if PRAGMA_STRUCT_ALIGN
	#pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
	#pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
	#pragma pack()
#endif
// ---------------------------------------------------------------------------

class	UTTicListResource : public UTResource
{
	public:
	UTTicListResource();							
	virtual ~UTTicListResource();
	void Init(ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true);
			
	virtual Handle 	BuildBaseResource();	

	void GetTicEntry(UInt32 inIndex, TicEntry &outTic);
	void SetTicEntry(UInt32 inIndex, const TicEntry &inTic);
	void InsertTicEntry(UInt32 inIndex, const TicEntry &inTic);
	void AddTicEntry(const TicEntry &inTic);
	void DeleteTicEntry(UInt32 inIndex);
	UInt32 Count();
	UInt32 FindTicEntry(OSType inType, TicEntry &outTicEntry);
	void	FindEntryName(OSType inType, LStr255 &outString);
	protected:
	void SetCount(UInt32 inCount);
	
};



#endif
