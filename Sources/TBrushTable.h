// ===========================================================================
//	TBrushTable.h	©1999 Allegro Themes Project
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

#ifndef _H_TBrushTable
#define _H_TBrushTable
#pragma once

#include "TThemeColumnTable.h"

#include "UTPlutResource.h"

class TBrushTable : public TThemeColumnTable
{
	public:
	enum				{ class_ID = FOUR_CHAR_CODE('TBRT') };
	
						TBrushTable(
								LStream*			inStream);
						
	virtual				~TBrushTable();
	
	virtual Boolean	isRequired() { return mIsRequired; }
	virtual void		SetPlutResource(UTPlutResource *inPlut);
	
	virtual void		ReceiveDragItem(
								DragReference		inDragRef,
								DragAttributes		inDragAttrs,
								ItemReference		inItemRef,
								Rect&				inItemBounds);
								
	virtual void		FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	protected:
	virtual void		DoubleClickCell(const STableCell&		inCell);
	virtual void		DrawCell(
								const STableCell		&inCell,
								const Rect				&inLocalRect);
	virtual OSErr		AddFlavors(const 	STableCell&		inCell, 
													LDragTask &inTask);
	virtual void		DoPictToPlutChangeRecordAndBroadcast(const PicHandle inPic, const STableCell inCell);

	virtual void		DoCopy();
	virtual void		DoPaste();
	Boolean mIsRequired;
	UTPlutResource *mPlutBrush;
};

class PlutChangeRecord
{
	public:
	
	TBrushTable *aTable;
	Handle aPPAT; //if aPPAT is null, aPlut.brushppatID contains the valid info
	PlutEntry aPlut;
	STableCell	aCell;
	
	PlutChangeRecord()
	{
		aTable = NULL;
		aPPAT = NULL;
		aCell.row = 0;
		aCell.col = 0;
	}
};

class PlutDragRecord
{
	public:
	TBrushTable *aTable;
	PlutEntry aPlut;
	SInt16	anIndex; //0 based
	
	PlutDragRecord()
	{
		aTable = NULL;
		anIndex = -1;
	}
};

#endif