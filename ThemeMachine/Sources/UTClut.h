// ===========================================================================
//	UTClut.h			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the CLUT's
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Jan 24/99 Initial Implementation
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


class LFileStream;
#include "TThemes.h"
#include <TArray.h>
#include "UTResource.h"

class UTClut : public UTResource
{
	//Constructors
	public:
	UTClut();	
	~UTClut();
	
	void Init(ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true);
	
	virtual Handle 	BuildBaseResource();			
	void GetColor(UInt16 inIndex, RGBColor &outColor);
	void SetColor(UInt16 inIndex, const RGBColor &inColor);
	void InsertColor(UInt16 inIndex, const RGBColor &inColor);
	void AddColor(const RGBColor &inColor);
	void DeleteColor(UInt16 inIndex);
	UInt16 Count();
	virtual void				Write(Boolean			inUpdateResFile = true);	
	void ExportCLUT(LFileStream* inStream);
	void ImportCLUT(LFileStream* inStream);
	
	private:
	void SetCount(UInt16 inCount);
};
	