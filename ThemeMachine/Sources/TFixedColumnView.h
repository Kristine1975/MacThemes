// ===========================================================================
//	TFixedColumnView.h				©1999 Allegro Themes Project
// ===========================================================================
//	Author: Dave MacLachlan
//	Abstract class for a Table with fixed size columns
//
//	ColumnView broadcasts a message when the selection changes and
//	when a cell is double-clicked
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


#ifndef _H_TFixedColumnView
#define _H_TFixedColumnView
#pragma once

#include <LTableView.h>
#include <LDragAndDrop.h>
#include <LBroadcaster.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

#pragma options align=mac68k

struct	SFixedColumnViewInfo {
	UInt16		colCount;
	UInt16		colWidth;
	UInt16		rowHeight;
	Boolean		useSingleSelector;
	Boolean		useDragSelect;
	UInt32		dataSize;
	MessageT	doubleClickMsg;
	MessageT	selectionMsg;
};

#pragma options align=reset

// ---------------------------------------------------------------------------

class	TFixedColumnView : public LTableView,
					  public LDragAndDrop,
					  public LBroadcaster {
public:
	enum				{ class_ID = FOUR_CHAR_CODE('FCLV') };
	
						TFixedColumnView(
								LStream*			inStream);
						
	virtual				~TFixedColumnView();		
	
	void				SetDoubleClickMsg(
								MessageT			inMessage)
							{
								mDoubleClickMsg = inMessage;
							}
	
	MessageT			GetDoubleClickMsg()		{ return mDoubleClickMsg; }
	
	void				SetSelectionMsg(
								MessageT			inMessage)
							{
								mSelectionMsg = inMessage;
							}
						
	MessageT			GetSelectionMsg()		{ return mSelectionMsg; }
	
	virtual void		SelectionChanged();
								
	virtual void		ResizeFrameBy(
								SInt16				inWidthDelta,
								SInt16				inHeightDelta,
								Boolean				inRefresh);
								
	virtual void		Click(	SMouseDownEvent&	inMouseDown);
	
							// Column operations to disallow
						
	virtual void		InsertCols(
								UInt32				inHowMany,
								TableIndexT			inAfterCol,
								const void*			inDataPtr,
								UInt32				inDataSize,
								Boolean				inRefresh);
								
	virtual void		RemoveCols(
								UInt32				inHowMany,
								TableIndexT			inFromCol,
								Boolean				inRefresh);
	
protected:
	MessageT		mDoubleClickMsg;
	MessageT		mSelectionMsg;
	FlavorType		mDragFlavor;
	FlavorFlags		mFlavorFlags;
	Boolean			mUseFrameWidth;
	
	virtual void		DoubleClickCell(const STableCell&		inCell);
	virtual void		ClickCell(
								const STableCell&		inCell,
								const SMouseDownEvent&	inMouseDown);
								
	virtual void		HiliteDropArea(
								DragReference		inDragRef);
	
	virtual Boolean		ItemIsAcceptable(
								DragReference		inDragRef,
								ItemReference		inItemRef);
								
private:
	void				InitFixedColumnView(
								SFixedColumnViewInfo&	inInfo);
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif