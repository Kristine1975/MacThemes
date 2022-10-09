// ===========================================================================
//	TThemeColumnTable.h	©1999 Allegro Themes Project
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

#ifndef _H_TThemeColumnTable
#define _H_TThemeColumnTable
#pragma once


#include <LColumnView.h>
#include <LCommander.h>

class TThemeColumnTable : public LColumnView, LCommander
{
	public:
	enum				{ class_ID = FOUR_CHAR_CODE('TCOT') };
	
						TThemeColumnTable(
								LStream*			inStream);
						
	virtual				~TThemeColumnTable();
	
	virtual void		ReceiveDragItem(
								DragReference		inDragRef,
								DragAttributes		inDragAttrs,
								ItemReference		inItemRef,
								Rect&				inItemBounds);
	
	virtual Boolean		ObeyCommand(
								CommandT			inCommand,
								void*				ioParam = nil);
								
	virtual void		FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);
	protected:
	virtual Boolean	ItemIsAcceptable(DragReference	inDragRef,ItemReference	inItemRef);

	virtual void		DoubleClickCell(const STableCell&		inCell);
	virtual void		HiliteDropArea(
								DragReference		inDragRef);
	virtual void		InsideDropArea(DragReference	inDragRef);
	virtual void		ClickCell(const STableCell&		inCell,const SMouseDownEvent&	inMouseDown);
	virtual OSErr		AddFlavors(const STableCell&		inCell, LDragTask &inTask) = 0;
	virtual OSErr		AddDragRegion(const STableCell&		inCell, LDragTask &inTask);
	
	virtual void		DoCopy();
	virtual void		DoPaste();
	virtual void		DoClear();
	virtual void		DoCut();
	
	ResIDT						mTxtrID;
	ResIDT						mStringListID;
	SInt16		mPossibleDragTypes;
	OSType*		mPossibleDragFlavors;
};

#endif