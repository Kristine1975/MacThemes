// ===========================================================================
//	TFixedColumnView.cp				©1999 Allegro Themes Project
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

#ifdef PowerPlant_PCH
#include PowerPlant_PCH
#endif

#include "TFixedColumnView.h"
#include <LDragTask.h>
#include <LStream.h>
#include <LTableMonoGeometry.h>
#include <LTableSingleSelector.h>
#include <LTableMultiSelector.h>
#include <LTableArrayStorage.h>
#include <PP_Messages.h>
#include <UDrawingState.h>
#include <UMemoryMgr.h>
#include <URegions.h>
#include "UTCursor.h"

// ---------------------------------------------------------------------------
//	€ TFixedColumnView							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

TFixedColumnView::TFixedColumnView(
	LStream*	inStream)
	
	: LTableView(inStream),
	  LDragAndDrop(UQDGlobals::GetCurrentPort(), this)
{
	SFixedColumnViewInfo	info;
	
	inStream->ReadData(&info, sizeof(info));
	InitFixedColumnView(info);
}


// ---------------------------------------------------------------------------
//	€ InitColumnView						Initializer				 [private]
// ---------------------------------------------------------------------------

void
TFixedColumnView::InitFixedColumnView(
	SFixedColumnViewInfo&	inInfo)
{
	mUseFrameWidth = false;
	if (inInfo.colWidth == 0) {
		mUseFrameWidth = true;
		inInfo.colWidth = (UInt16) mFrameSize.width / inInfo.colCount;
	}

	SetTableGeometry(new LTableMonoGeometry(this, inInfo.colWidth, inInfo.rowHeight));

	if (inInfo.useSingleSelector) {
		SetTableSelector(new LTableSingleSelector(this));
	} else {
		SetTableSelector(new LTableMultiSelector(this));
	}
	
	SetTableStorage(new LTableArrayStorage(this, inInfo.dataSize));
	
	mUseDragSelect = inInfo.useDragSelect;
	
	mDoubleClickMsg = inInfo.doubleClickMsg;
	mSelectionMsg = inInfo.selectionMsg;
	
	LTableView::InsertCols(inInfo.colCount, 0, nil, 0, Refresh_No);
	
	
	mDragFlavor = FOUR_CHAR_CODE('TEXT');
	mFlavorFlags = 0;
}


// ---------------------------------------------------------------------------
//	€ ~TFixedColumnView							Destructor				  [public]
// ---------------------------------------------------------------------------

TFixedColumnView::~TFixedColumnView()
{
}


// ---------------------------------------------------------------------------
//	€ SelectionChanged
// ---------------------------------------------------------------------------
//	Broadcast message when selected cells change

void
TFixedColumnView::SelectionChanged()
{
	if (mSelectionMsg != msg_Nothing) {
		BroadcastMessage(mSelectionMsg, (void*) this);
	}
}


// ---------------------------------------------------------------------------
//	€ ResizeFrameBy
// ---------------------------------------------------------------------------
//	Make column same width as Frame (if that option is on)

void
TFixedColumnView::ResizeFrameBy(
	SInt16		inWidthDelta,
	SInt16		inHeightDelta,
	Boolean		inRefresh)
{
	LTableView::ResizeFrameBy(inWidthDelta, inHeightDelta, inRefresh);
	
	if (mUseFrameWidth) {
		SetColWidth((UInt16) mFrameSize.width, 1, 1);
	}
}


void
TFixedColumnView::Click(
	SMouseDownEvent	&inMouseDown)
{
	Boolean	saveDelaySelect = inMouseDown.delaySelect;
	inMouseDown.delaySelect = false;
	LTableView::Click(inMouseDown);
	inMouseDown.delaySelect = saveDelaySelect;
}


// ---------------------------------------------------------------------------
//	€ ClickCell
// ---------------------------------------------------------------------------
//	Broadcast message for a double-click on a cell

void
TFixedColumnView::ClickCell(
	const STableCell&		inCell,
	const SMouseDownEvent&	inMouseDown)
{
	if (GetClickCount() == 1) {
	
		if (LDragAndDrop::DragAndDropIsPresent() &&
			::WaitMouseMoved(inMouseDown.macEvent.where)) {

			UInt32	dataSize;
			GetCellData(inCell, nil, dataSize);
			StPointerBlock	buffer((SInt32) dataSize);
			GetCellData(inCell, buffer, dataSize);
			
			Rect	cellRect;
			GetLocalCellRect(inCell, cellRect);
		
			FocusDraw();
			StTCursor theCursor(kThemeClosedHandCursor);
			LDragTask	theDragTask(inMouseDown.macEvent, cellRect, 1, mDragFlavor,
										buffer, (SInt32) dataSize, mFlavorFlags);
										
			OutOfFocus(nil);
		
		}
	

	} else if (GetClickCount() == 2) {
		DoubleClickCell(inCell);
	}
}


// ---------------------------------------------------------------------------
//	€ HiliteDropArea
// ---------------------------------------------------------------------------
//	Hilite a DropArea to indicate that it can accept the current Drag

void
TFixedColumnView::HiliteDropArea(
	DragReference	inDragRef)
{
	Rect	dropRect;
	mPane->CalcLocalFrameRect(dropRect);
	StRegion	dropRgn(dropRect);
	::ShowDragHilite(inDragRef, dropRgn, true);
}


// ---------------------------------------------------------------------------
//	€ ItemIsAcceptable
// ---------------------------------------------------------------------------
//	DragManager item is acceptable if it has data of mDragFlavor

Boolean
TFixedColumnView::ItemIsAcceptable(
	DragReference	inDragRef,
	ItemReference	inItemRef)
{
	FlavorFlags		theFlags;
	return (GetFlavorFlags(inDragRef, inItemRef, mDragFlavor, &theFlags)
					== noErr);
}


// ---------------------------------------------------------------------------
//	€ InsertCols
// ---------------------------------------------------------------------------
//	Only one column allowed, so prevent insertion

void
TFixedColumnView::InsertCols(
	UInt32			/* inHowMany */,
	TableIndexT		/* inAfterCol */,
	const void*		/* inDataPtr */,
	UInt32			/* inDataSize	*/,
	Boolean			/* inRefresh */)
{
	SignalStringLiteral_("Inserting columns not allowed");
}


// ---------------------------------------------------------------------------
//	€ RemoveCols
// ---------------------------------------------------------------------------
//	Only one column allowed, so prevent removal

void
TFixedColumnView::RemoveCols(
	UInt32			/* inHowMany */,
	TableIndexT		/* inFromCol */,
	Boolean			/* inRefresh */)

{
	SignalStringLiteral_("Removing columns not allowed");
}

// ---------------------------------------------------------------------------
//	€ DoubleClickCell
// ---------------------------------------------------------------------------
//	Handle a DoubleClick

void	TFixedColumnView::DoubleClickCell(const STableCell&		/*inCell*/)
{
	//Subclasses override
}
