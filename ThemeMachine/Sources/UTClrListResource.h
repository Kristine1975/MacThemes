// ===========================================================================
//	UTClrListResource.h			   Allegro Themes Project
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


#ifndef _H_UTClrListResource
#define _H_UTClrListResource
#pragma once

#include "UTResource.h"

#define kClrListResourceType 'clr#'

// ---------------------------------------------------------------------------

class	UTClrListResource : public UTResource
{
	public:
	UTClrListResource();							
	virtual ~UTClrListResource();
	void Init(ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true);
			
	virtual Handle 	BuildBaseResource();	

	void GetColor(UInt32 inIndex, RGBColor &outColor);
	void SetColor(UInt32 inIndex, const RGBColor &inColor);
	void InsertColor(UInt32 inIndex, const RGBColor &inColor);
	void AddColor(const RGBColor &inColor);
	void DeleteColor(UInt32 inIndex);
	UInt32 Count();
	
	protected:
	void SetCount(UInt32 inCount);
	
};

#endif
