// ===========================================================================
//	TTextClrListTable.cp	©1999 Allegro Themes Project
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

#include "TTextClrListTable.h"
#include "UTTextClrListResource.h"
#include "TThemes.h"
#include "UTPixUtilities.h"

TTextClrListTable::TTextClrListTable(LStream*			inStream) 
				: TThemeColumnTable(inStream)
{
	mPossibleDragTypes = 2;
	mPossibleDragFlavors = (OSType*)NewPtr(sizeof(OSType) * 2);
	mPossibleDragFlavors[0] = kTextColorDragFlavor;
	mPossibleDragFlavors[1] = kPictDragFlavor;
	mTextClrList = NULL;
}

						
TTextClrListTable::~TTextClrListTable()
{
}
	
void TTextClrListTable::SetTextClrList(UTTextClrListResource *inList)
{
	RemoveAllRows(false);
	mTextClrList = inList;
	for(UInt32 i = 0; i < mTextClrList->Count(); i++)
	{
		RGBColor theColor;
		mTextClrList->GetColor(i,theColor);
		InsertRows(1,32000,&theColor,sizeof(theColor),false);
	}
	STableCell	topLeftCell(1,1);
	STableCell	botRightCell(1,mTextClrList->Count());
	RefreshCellRange(topLeftCell,botRightCell);
}

void		TTextClrListTable::DrawCell(
								const STableCell		&inCell,
								const Rect				&inLocalRect)
{
	if(mTextClrList != NULL)
	{
		Rect	colorRect = inLocalRect;
		Rect	textRect = inLocalRect;
		colorRect.right -= ((float)(colorRect.right - colorRect.left)) / 6.0 * 5.0;
		textRect.left += ((float)(textRect.right - textRect.left)) / 6.0;
		
		::MacInsetRect(&colorRect, 2, 2);
		::MacInsetRect(&textRect, 2, 2);
		
		RGBColor theColor;
		mTextClrList->GetColor(inCell.row - 1,theColor);
		RGBForeColor(&theColor);
		PaintRect(&colorRect);
		
		LStr255 theString(mStringListID,inCell.row);
		SInt16	just = UTextTraits::SetPortTextTraits(mTxtrID);
		UTextDrawing::DrawWithJustification(theString.ConstTextPtr(), theString.Length(), textRect, just);
	}
}

OSErr		TTextClrListTable::AddFlavors(const STableCell&		inCell, LDragTask &inTask)
{
	OSErr theErr = noErr;
	RGBColor theColor;
	mTextClrList->GetColor(inCell.row - 1,theColor);
	PicHandle tempHandle = NULL;
	if((theErr = UTPixUtilities::ColorToPict(theColor,tempHandle)) == noErr)
	{
		
		theErr = ::AddDragItemFlavor(inTask.GetDragReference(), 1, 'PICT', *tempHandle, GetHandleSize((Handle)tempHandle),0);
	}
	
	if(theErr == noErr)
	{
		TextColorDragRecord theDragRec;
		theDragRec.aColor = theColor;
		theDragRec.anIndex = inCell.row - 1;
		theErr = ::AddDragItemFlavor(inTask.GetDragReference(), 1, kTextColorDragFlavor, &theDragRec, sizeof(theDragRec),0); 
	}
	return theErr;
}


void	TTextClrListTable::ReceiveDragItem(
	DragReference	 inDragRef,
	DragAttributes	 /*inDragAttrs*/,
	ItemReference	 inItemRef,
	Rect&			 inItemBounds)	// In Local coordinates
{
	SPoint32 theCenter;
	
	theCenter.v = inItemBounds.top + ((inItemBounds.bottom - inItemBounds.top) / 2);
	theCenter.h = inItemBounds.left + ((inItemBounds.right - inItemBounds.left) / 2);
	
	STableCell theCell;
	if(GetCellHitBy(theCenter,theCell))
	{
		UInt16 flavorCount;
		::CountDragItemFlavors(inDragRef, inItemRef, &flavorCount);
		for(UInt32 i = 1; i <= flavorCount; i++)
		{
			OSType theType;
			if(::GetFlavorType(inDragRef, inItemRef, i, &theType) == noErr)
			{
				if(theType == kTextColorDragFlavor)
				{
					TextColorDragRecord theDragRec;
					SInt32 theSize = sizeof(theDragRec);
					if(GetFlavorData(inDragRef, inItemRef, theType, &theDragRec,&theSize , (UInt32)0) == noErr)
					{
						TextColorChangeRecord theRecord;
						theRecord.aTable = this;
						theRecord.aColor = theDragRec.aColor;
						theRecord.aCell= theCell;
						BroadcastMessage(mDoubleClickMsg,&theRecord);
					}
					break;
				}
				else
				if(theType == 'PICT')
				{
					Size theSize;
					if(GetFlavorDataSize(inDragRef, inItemRef, theType, &theSize) == noErr)
					{
						Handle thePic = NewHandle(theSize);
						if(MemError() == noErr)
						{
							HLock(thePic);
							if(GetFlavorData(inDragRef, inItemRef, theType, *thePic, &theSize, 0) == noErr)
							{
								RGBColor theColor;
								if(UTPixUtilities::PictToColor((PicHandle) thePic,theColor) == noErr)
								{
									TextColorChangeRecord theRecord;
									theRecord.aTable = this;
									theRecord.aColor = theColor;
									theRecord.aCell= theCell;
									BroadcastMessage(mDoubleClickMsg,&theRecord);
								}
							}
							HUnlock(thePic);
							DisposeHandle(thePic);
						}
					}
					break;
				}
			}
		}
	}
}

void		TTextClrListTable::DoubleClickCell(const STableCell&		inCell)
{
	RGBColor theColor, theOutColor;
	mTextClrList->GetColor(inCell.row - 1,theColor);
	if(::GetColor ( Point_00, "\p", &theColor, &theOutColor ))
	{
		TextColorChangeRecord theRecord;
		theRecord.aTable = this;
		theRecord.aColor = theOutColor;
		theRecord.aCell= inCell;
		BroadcastMessage(mDoubleClickMsg,&theRecord);
	}
}


