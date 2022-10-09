// ===========================================================================
//	TTextClrListTable.h	©1999 Allegro Themes Project
// ===========================================================================
//	Author: Dave MacLachlan
//
//	A single column table for showing and editing text clr# resources. 
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

#include "TThemeColumnTable.h"

class UTTextClrListResource;

class TTextClrListTable : public TThemeColumnTable
{
	public:
	enum				{ class_ID = FOUR_CHAR_CODE('TCLT') };
	
						TTextClrListTable(
								LStream*			inStream);
						
	virtual				~TTextClrListTable();
	
	virtual void	SetTextClrList(UTTextClrListResource *inList);
	
	virtual void		ReceiveDragItem(
								DragReference		inDragRef,
								DragAttributes		inDragAttrs,
								ItemReference		inItemRef,
								Rect&				inItemBounds);


	protected:
	virtual void		DoubleClickCell(const STableCell&		inCell);
	virtual void		DrawCell(
								const STableCell		&inCell,
								const Rect				&inLocalRect);
	
	virtual OSErr		AddFlavors(const STableCell&		inCell, LDragTask &inTask);

	UTTextClrListResource *mTextClrList;
};

typedef struct
{
	TTextClrListTable *aTable;
	RGBColor aColor;
	STableCell	aCell;
} TextColorChangeRecord;

typedef struct
{
	RGBColor aColor;
	SInt16	anIndex; //0 based
} TextColorDragRecord;