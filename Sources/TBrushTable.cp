// ===========================================================================
//	TBrushTable.cp	©1999 Allegro Themes Project
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

#include "TBrushTable.h"
#include "UTPlutResource.h"
#include "TThemes.h"
#include "UTPixUtilities.h"
#include "LClipboard.h"
#include <LGAColorSwatchControl.h>
#include <LEditText.h>
#include "TGAPPATEditControl.h"
#include <UModalDialogs.h>
#include "TBrushEditDialogBox.h"
#include <LPushButton.h>
const ResIDT	kEditRequiredBrushWindowID = 130;
const ResIDT	kEditUserBrushWindowID = 130;

TBrushTable::TBrushTable(LStream*			inStream) 
				: TThemeColumnTable(inStream)
{ 
	inStream->ReadData(&mIsRequired, sizeof(mIsRequired));
	mPossibleDragTypes = 2;
	mPossibleDragFlavors = (OSType*)NewPtr(sizeof(OSType) * 2);
	mPossibleDragFlavors[0] = kBrushDragFlavor;
	mPossibleDragFlavors[1] = kPictDragFlavor;
	mPlutBrush = NULL;

}

						
TBrushTable::~TBrushTable()
{
}
	
void TBrushTable::SetPlutResource(UTPlutResource *inPlut)
{
	RemoveAllRows(false);
	mPlutBrush = inPlut;
	InsertRows(mPlutBrush->Count(),32000,NULL,0,false);
		
	
}

void		TBrushTable::DrawCell(
								const STableCell		&inCell,
								const Rect				&inLocalRect)
{
	if(mPlutBrush != NULL)
	{
		Rect	colorRect = inLocalRect;
		Rect	textRect = inLocalRect;
		colorRect.right -= ((float)(colorRect.right - colorRect.left)) / 6.0 * 4.0;
		textRect.left += ((float)(textRect.right - textRect.left)) / 6.0 * 2.0;
		
		::MacInsetRect(&colorRect, 2, 2);
		::MacInsetRect(&textRect, 2, 2);
		
		PlutEntry plutEntry;
		mPlutBrush->GetPlutEntry(inCell.row - 1,plutEntry);
		
		Rect brushRect = colorRect;
		brushRect.right = brushRect.left + (brushRect.right -brushRect.left) / 2;
		colorRect.left = brushRect.right;
		
		
		
		RGBForeColor(&plutEntry.brushColor);
		PaintRect(&colorRect);
		
		if(plutEntry.brushPPAT.resID == 0)
		{
			EraseRect(&brushRect);
		}
		else
		{
			PixPatHandle thePattern = plutEntry.GetPlutPixPat();
			FillCRect(&brushRect,thePattern);
			DisposePixPat(thePattern);
		}
		
		PenNormal();
		ForeColor(blackColor);
		FrameRect(&brushRect);
		FrameRect(&colorRect);
		
		if(mIsRequired)
		{
			LStr255 theString(mStringListID,inCell.row);
			SInt16	just = UTextTraits::SetPortTextTraits(mTxtrID);
			UTextDrawing::DrawWithJustification(theString.ConstTextPtr(), theString.Length(), textRect, just);
		}
		else
		{
			LStr255 theString(305,1);
			LStr255 theString2((SInt16)inCell.row);
			LStr255 theWholeString = theString + theString2;
			SInt16	just = UTextTraits::SetPortTextTraits(mTxtrID);
			UTextDrawing::DrawWithJustification(theWholeString.ConstTextPtr(), theWholeString.Length(), textRect, just);
		}
	}
}

OSErr		TBrushTable::AddFlavors(const STableCell&		inCell, LDragTask &inTask)
{
	OSErr theErr = noErr;
	PlutEntry plutEntry;
	mPlutBrush->GetPlutEntry(inCell.row - 1,plutEntry);
	
	PlutDragRecord theDragRec;
	theDragRec.aTable = this;
	theDragRec.aPlut = plutEntry;
	theDragRec.anIndex = inCell.row - 1;
	
	theErr = ::AddDragItemFlavor(inTask.GetDragReference(), 1, kBrushDragFlavor,&theDragRec, sizeof(theDragRec),0);
	
	if(theErr == noErr)
	{
		PicHandle tempHandle = NULL;
		theErr = UTPixUtilities::PlutEntryToPict(plutEntry,tempHandle);
		if(theErr == noErr)
		{
			
			theErr = ::AddDragItemFlavor(inTask.GetDragReference(), 1, kPictDragFlavor, *tempHandle, GetHandleSize((Handle)tempHandle),
						0);
			DisposeHandle((Handle)tempHandle);
		}
	}
	return theErr;
}

void	TBrushTable::ReceiveDragItem(
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
				if(theType == kBrushDragFlavor)
				{
					PlutDragRecord theDragRec;
					SInt32 theSize = sizeof(theDragRec);
					if(GetFlavorData(inDragRef, inItemRef, theType, &theDragRec,&theSize , (UInt32)0) == noErr)
					{
						PlutChangeRecord theRecord;
						theRecord.aTable = this;
						theRecord.aPPAT = NULL;
						theRecord.aPlut = theDragRec.aPlut;
						theRecord.aCell= theCell;
						BroadcastMessage(mDoubleClickMsg,&theRecord);
					}
					break;
				}
				else
				if(theType == kPictDragFlavor)
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
								DoPictToPlutChangeRecordAndBroadcast((PicHandle)thePic,theCell);
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

void		TBrushTable::DoubleClickCell(const STableCell&		inCell)
{
	TBrushEditDialogBox *theDialog;
	LPushButton *theButton;
	
	PlutEntry plutEntry;
	mPlutBrush->GetPlutEntry(inCell.row - 1,plutEntry);
	
	if(mIsRequired)
	{
		theDialog = (TBrushEditDialogBox*) LWindow::CreateWindow(kEditRequiredBrushWindowID, this);
	}
	else
	{
		theDialog = (TBrushEditDialogBox*) LWindow::CreateWindow(kEditUserBrushWindowID, this);
	}
	theDialog->SetPlutEntry(plutEntry);
	StDialogHandler theHandler(theDialog,this);
	theButton = (LPushButton*)theDialog->FindPaneByID(TBrushEditDialogBox::kBrushEditOKID);
	ThrowIfNil_(theButton);
	theButton->AddListener(&theHandler);
	theButton = (LPushButton*)theDialog->FindPaneByID(TBrushEditDialogBox::kBrushEditCancelID);
	ThrowIfNil_(theButton);
	theButton->AddListener(&theHandler);
	
	Boolean doDialog = true;
	while(doDialog)
	{
		MessageT theMessage = theHandler.DoDialog();
		if(theMessage == TBrushEditDialogBox::kBrushEditOK)
		{
			PlutChangeRecord theRecord;
			doDialog = false;
			theDialog->GetPlutChangeRecord(theRecord);
			theRecord.aCell = inCell;
			theRecord.aTable = this;
			BroadcastMessage(mDoubleClickMsg,&theRecord);
		}
		else if(theMessage == TBrushEditDialogBox::kBrushEditCancel)
		{
			doDialog = false;
		}
	}
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
TBrushTable::FindCommandStatus(
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
		
		{
			outEnabled = haveACell;
			outUsesMark = false;
		}
		break;
		
		case cmd_Cut:
		case cmd_Clear:
		{
			outEnabled = false;
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


void		TBrushTable::DoCopy()
{
	STableCell theCell = GetFirstSelectedCell();
	PlutEntry plutEntry;
	mPlutBrush->GetPlutEntry(theCell.row - 1,plutEntry);
	
	PlutDragRecord theDragRec;
	theDragRec.aTable = this;
	theDragRec.aPlut = plutEntry;
	theDragRec.anIndex = theCell.row - 1;
	LClipboard* theClipboard = LClipboard::GetClipboard();
	theClipboard->SetData(kBrushDragFlavor,(char*)&theDragRec,sizeof(theDragRec),true);
	
	PicHandle thePict = NULL;
	OSErr theErr = UTPixUtilities::PlutEntryToPict(plutEntry,thePict);
	if(theErr == noErr)
	{
		theClipboard->SetData(kPictDragFlavor,(Handle)thePict,false);
		DisposeHandle((Handle)thePict);
	}
}

void		TBrushTable::DoPaste()
{
	STableCell theCell = GetFirstSelectedCell();
	PlutEntry plutEntry;
	
	LClipboard* theClipboard = LClipboard::GetClipboard();
	Handle theHandle = NewHandle(1);
	if(theClipboard->GetData(kBrushDragFlavor,theHandle) > 0)
	{
		PlutDragRecord *theDragRecPtr = (PlutDragRecord *)*theHandle;
		PlutChangeRecord theRecord;
		theRecord.aTable = this;
		theRecord.aPPAT = NULL;
		theRecord.aPlut = theDragRecPtr->aPlut;
		theRecord.aCell= theCell;
		BroadcastMessage(mDoubleClickMsg,&theRecord);
	}
	else if(theClipboard->GetData(kPictDragFlavor,theHandle) > 0)
	{
		DoPictToPlutChangeRecordAndBroadcast((PicHandle)theHandle,theCell);
	}
	DisposeHandle(theHandle);
}




void TBrushTable::DoPictToPlutChangeRecordAndBroadcast(const PicHandle inPic, const STableCell inCell)
{
	Handle thePPAT = NULL;
	if(UTPixUtilities::PictToPPAT((PicHandle) inPic,thePPAT) == noErr)
	{
		RGBColor theColor;
		if(UTPixUtilities::PictToColor((PicHandle) inPic,theColor) == noErr)
		{
			PlutChangeRecord theRecord;
			theRecord.aTable = this;
			theRecord.aPlut.brushColor = theColor;
			theRecord.aPPAT = thePPAT;
			theRecord.aCell= inCell;
			BroadcastMessage(mDoubleClickMsg,&theRecord);
			
		}
		DisposeHandle(thePPAT);
	}
}