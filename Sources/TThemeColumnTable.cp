// ===========================================================================
//	TThemeColumnTable.cp	©1999 Allegro Themes Project
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
#include "UTTextClrListResource.h"
#include "TThemes.h"
#include "UTPixUtilities.h"
#include "LCommander.h"

//The TThemeColumnTable Needs a Supercommander Set for it.

TThemeColumnTable::TThemeColumnTable(LStream*			inStream) 
				: LColumnView(inStream), LCommander()
{
	inStream->ReadData(&mTxtrID, sizeof(mTxtrID));
	inStream->ReadData(&mStringListID, sizeof(mStringListID)); 
	mPossibleDragTypes = 0;
	mPossibleDragFlavors = NULL;
}

						
TThemeColumnTable::~TThemeColumnTable()
{
	if(mPossibleDragFlavors != NULL)
	{
		DisposePtr((Ptr)mPossibleDragFlavors);
	}
}
	
// ---------------------------------------------------------------------------
//	€ ReceiveDragItem												  [public]
// ---------------------------------------------------------------------------
//	Process an Item which has been dragged into a DropArea
//
//	This function gets called once for each Item contained in a completed
//	Drag. The Item will have returned true from ItemIsAcceptable().
//
//	The DropArea is focused upon entry and inItemBounds is specified
//	in the local coordinates of the DropArea.
//
//	Override this function if the DropArea can accept dropped Items.
//	You may want to call GetFlavorData and GetFlavorDataSize if there
//	is information associated with the dragged Item.

void	TThemeColumnTable::ReceiveDragItem(
	DragReference	 /*inDragRef*/,
	DragAttributes	 /*inDragAttrs*/,
	ItemReference	 /*inItemRef*/,
	Rect&			 /*inItemBounds*/)	// In Local coordinates
{
	
}


// ---------------------------------------------------------------------------
//	€ HiliteDropArea											   [protected]
// ---------------------------------------------------------------------------
//	Hilite a DropArea to indicate that it can accept the current Drag
//
//	For a DragAndDrop, the drop area is the Frame of its associated
//	Pane inset by one pixel to account for the border which usually
//	surrounds a Drop-capable Pane.

void
TThemeColumnTable::HiliteDropArea(
	DragReference	inDragRef)
{
	mPane->ApplyForeAndBackColors();

	Rect	dropRect;
	mPane->CalcLocalFrameRect(dropRect);
	::MacInsetRect(&dropRect, 1, 1);
	StRegion	dropRgn(dropRect);
	
	::ShowDragHilite(inDragRef, dropRgn, true);
}

// ---------------------------------------------------------------------------
//	€ InsideDropArea												  [public]
// ---------------------------------------------------------------------------
//	Track a Drag while it is inside a DropArea. This function is called
//	repeatedly while an acceptable Drag is inside a DropArea.
//
//	Subclasses may override to provide additional visual feedback during
//	a Drag, such as indicating an insertion point

void
TThemeColumnTable::InsideDropArea(
	DragReference	 inDragRef)
{
	Point theMouseLoc, thePinnedLoc;
	::GetDragMouse(inDragRef, &theMouseLoc, &thePinnedLoc);
	::GlobalToLocal(&theMouseLoc);
	
	STableCell theCell;
	SPoint32 theSMouseLoc;
	theSMouseLoc.v = theMouseLoc.v;
	theSMouseLoc.h = theMouseLoc.h;
	if(GetCellHitBy(theSMouseLoc,theCell))
	{
		Rect theFrame;
		GetLocalCellRect(theCell, theFrame);
		
		::MacInsetRect(&theFrame, 1, 1);
		StRegion	dropRgn(theFrame);
	
		::ShowDragHilite(inDragRef, dropRgn, true);
	}
}

// ---------------------------------------------------------------------------
//	€ ClickCell
// ---------------------------------------------------------------------------
//	Broadcast message for a double-click on a cell

void
TThemeColumnTable::ClickCell(
	const STableCell&		inCell,
	const SMouseDownEvent&	inMouseDown)
{
	SwitchTarget(this);
	if (GetClickCount() == 1) {
	
		if (LDragAndDrop::DragAndDropIsPresent() &&
			::WaitMouseMoved(inMouseDown.macEvent.where)) 
		{
		
			FocusDraw();
			LDragTask	theDragTask(inMouseDown.macEvent);
						
			//Add my Drag Flavors
			AddFlavors(inCell,theDragTask);
			AddDragRegion(inCell,theDragTask);
			
			theDragTask.DoDrag();
										
			OutOfFocus(nil);
		
		}
	

	} else if (GetClickCount() == 2) 
	{
		DoubleClickCell(inCell);
	}
}

OSErr
TThemeColumnTable::AddDragRegion(const STableCell&		inCell, LDragTask &inTask)
{
	Rect	cellRect;
	GetLocalCellRect(inCell, cellRect);
	::LocalToGlobal(&topLeft(cellRect));
	::LocalToGlobal(&botRight(cellRect));
		
	StRegion	outerRgn(cellRect);	// Make region containing item
	StRegion theRgn(inTask.GetDragRegion(),false);
	StRegion	innerRgn = outerRgn;	// Carve out interior of region so
	::InsetRgn(innerRgn, 1, 1);			//   that it's just a one-pixel thick
	outerRgn -= innerRgn;				//   outline of the item rectangle
	
	theRgn += outerRgn;			// Accumulate this item in our
										//   total drag region
	
										// Tell Drag Manager about this item
	theRgn.Release();				// So it doesn't get deletedw
	return ::SetDragItemBounds(inTask.GetDragReference(), 1, &cellRect);
}

void		TThemeColumnTable::DoubleClickCell(const STableCell&		/*inCell*/)
{
}

// ---------------------------------------------------------------------------
//	€ ItemIsAcceptable
// ---------------------------------------------------------------------------
//	DragManager item is acceptable if it has data of mDragFlavor

Boolean
TThemeColumnTable::ItemIsAcceptable(
	DragReference	inDragRef,
	ItemReference	inItemRef)
{
	FlavorFlags		theFlags;
	Boolean isAcceptable = false;
	for(UInt32 i =0; i < mPossibleDragTypes && !isAcceptable; i++)
	{
		isAcceptable = (GetFlavorFlags(inDragRef, inItemRef, mPossibleDragFlavors[i], &theFlags)
					== noErr);
	}
	return isAcceptable;
}


// ---------------------------------------------------------------------------
//	€ ObeyCommand
// ---------------------------------------------------------------------------
//	Issue a Command to a Commander
//
//	Returns whether or not the command was handled
//
//	Subclasses must override this method in order to respond to commands.

Boolean
TThemeColumnTable::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean	cmdHandled = false;
	switch(inCommand)
	{
		case cmd_Copy:
		{
			DoCopy();
			cmdHandled = true;
		}
		break;
		
		case cmd_Paste:
		{
			DoPaste();
			cmdHandled = true;
		}
		break;
		
		case cmd_Cut:
		{
			DoCut();
			cmdHandled = true;
		}
		
		case cmd_Clear:
		{
			DoClear();
			cmdHandled = true;
		}
		default:
		{
			cmdHandled = LCommander::ObeyCommand(inCommand,ioParam);
		}
		break;
	}
	return cmdHandled;
}

// ---------------------------------------------------------------------------
//	€ FindCommandStatus
// ---------------------------------------------------------------------------
//	Pass back the status of a Command
//
//	Subclasses must override to enable/disable and mark commands
//
//	PowerPlant uses the enabling and marking information to set the
//	appearance of Menu items.

void
TThemeColumnTable::FindCommandStatus(
	CommandT	inCommand,
	Boolean&	outEnabled,
	Boolean&	outUsesMark,
	UInt16&		outMark,
	Str255		outName)
{
	STableCell theCell = GetFirstSelectedCell();
	Boolean haveACell = (theCell.row != 0 || theCell.col != 0);
	
	switch(inCommand)
	{
		case cmd_Copy:
		case cmd_Paste:
		case cmd_Cut:
		case cmd_Clear:
		{
			outEnabled = haveACell;
			outUsesMark = false;
		}
		break;
		
		default:
		{
			LCommander::FindCommandStatus(inCommand,outEnabled,outUsesMark,outMark,outName);
		}
		break;
	}
}


void		TThemeColumnTable::DoCopy()
{
}

void		TThemeColumnTable::DoPaste()
{
}

void		TThemeColumnTable::DoClear()
{
}

void		TThemeColumnTable::DoCut()
{
}
