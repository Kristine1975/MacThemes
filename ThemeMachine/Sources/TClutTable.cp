// ===========================================================================
//	TClutTable.cp	©1999 Allegro Themes Project
// ===========================================================================
//	Author: Dave MacLachlan
//
//	A single column table for showing and editing brush resources. 
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

#include "TClutTable.h"
#include "UTPlutResource.h"
#include "TThemes.h"
#include "UTPixUtilities.h"
#include "LClipboard.h"
#include "UTClut.h"


TClutTable::TClutTable(LStream*			inStream) 
				: TFixedColumnView(inStream)
{ 
	mClut = NULL;
}

						
TClutTable::~TClutTable()
{
}
	
void TClutTable::SetClutResource(UTClut *inClut)
{
	RemoveAllRows(false);
	mClut = inClut;
	if(mClut != NULL)
	{
		TableIndexT rowCount;
		TableIndexT colCount;
		GetTableSize(rowCount,colCount);
		UInt16 newRowCount = (mClut->Count() / colCount) + (mClut->Count() % colCount) ? 1 : 0;
		InsertRows(newRowCount,32000,NULL,0,false);
	}
	Draw(NULL);	
}

void		TClutTable::DrawCell(
								const STableCell		&inCell,
								const Rect				&inLocalRect)
{
	Rect	colorRect = inLocalRect;
	::MacInsetRect(&colorRect, 2, 2);	
	TableIndexT rowCount;
	TableIndexT colCount;
	GetTableSize(rowCount,colCount);
	TableIndexT cellIndex = ((inCell.row - 1) * colCount) + (inCell.col - 1);
	if(mClut != NULL && cellIndex < mClut->Count())
	{
		RGBColor theColor;
		mClut->GetColor((inCell.row * inCell.col) - 1,theColor);	
		::RGBForeColor(&theColor);
		::PaintRect(&colorRect);

	}
	else
	{
		EraseRect(&colorRect);
	}
}

void		TClutTable::DoubleClickCell(const STableCell&		inCell)
{
	TableIndexT rowCount;
	TableIndexT colCount;
	GetTableSize(rowCount,colCount);
	TableIndexT cellIndex = ((inCell.row - 1) * colCount) + (inCell.col - 1);
	if(mClut != NULL && cellIndex < mClut->Count())
	{
		RGBColor theColor, theOutColor;
		mClut->GetColor(cellIndex,theColor);
		if(::GetColor ( Point_00, "\p", &theColor, &theOutColor ))
		{
			mClut->SetColor(cellIndex,theOutColor);
			Draw(NULL);
			BroadcastMessage(mDoubleClickMsg,NULL);
			
		}
	}
}