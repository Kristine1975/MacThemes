// ===========================================================================
//	TBrushEditDialogBox.cp	©1999 Allegro Themes Project
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

#include "TBrushEditDialogBox.h"
#include <LControlPane.h>
#include <LGAColorSwatchControl.h>
#include <LEditText.h>
#include "TGAPPATEditControl.h"
#include "UTPixUtilities.h"

// ---------------------------------------------------------------------------

const PaneIDT	kBrushColorRedEditID = 'bred';
const PaneIDT	kBrushColorGreenEditID = 'bgre';
const PaneIDT	kBrushColorBlueEditID = 'bblu';
const PaneIDT	kBrushColorSwatchID = 'bcol';
const PaneIDT	kBrushPatternSwatchID = 'bpat';
const PaneIDT  kBrushNameTextID = 'name';
const PaneIDT TBrushEditDialogBox::kBrushEditOKID = 'OKOK';
const PaneIDT TBrushEditDialogBox::kBrushEditCancelID = 'CANC';
const MessageT TBrushEditDialogBox::kBrushEditOK = -77;
const MessageT TBrushEditDialogBox::kBrushEditCancel = -78;

TBrushEditDialogBox::TBrushEditDialogBox()
{
	mIsRequired = false;
	mPlutChange.aPPAT = NULL;
	mPlutChange.aTable = NULL;
	mPlutChange.aCell.row = 0;
	mPlutChange.aCell.col = 0;
}
				
TBrushEditDialogBox::TBrushEditDialogBox(LStream*		inStream) : LDialogBox(inStream)
{
	inStream->ReadData(&mIsRequired, sizeof(mIsRequired));
	mPlutChange.aPPAT = NULL;
	mPlutChange.aTable = NULL;
	mPlutChange.aCell.row = 0;
	mPlutChange.aCell.col = 0;
}


TBrushEditDialogBox::~TBrushEditDialogBox()
{
	if(mPlutChange.aPPAT != NULL)
	{
		DisposeHandle(mPlutChange.aPPAT);
		mPlutChange.aPPAT = NULL;
	}
}
								
void		TBrushEditDialogBox::ListenToMessage(MessageT		inMessage,void*			ioParam)
{
	RGBColor theColor;
	
	switch(inMessage)
	{
		case kBrushColorRedEditID:
		{
			mBrushColorSwatch->GetSwatchColor(theColor);
			theColor.red = ((LEditText*)ioParam)->GetValue();
			mBrushColorSwatch->StopBroadcasting();
			mBrushColorSwatch->SetSwatchColor(theColor);
			mBrushColorSwatch->StartBroadcasting();
			mPlutChange.aPlut.brushColor = theColor;
		}
		break;
		
		case kBrushColorGreenEditID:
		{
			mBrushColorSwatch->GetSwatchColor(theColor);
			theColor.green = ((LEditText*)ioParam)->GetValue();
			mBrushColorSwatch->StopBroadcasting();
			mBrushColorSwatch->SetSwatchColor(theColor);
			mBrushColorSwatch->StartBroadcasting();
			mPlutChange.aPlut.brushColor = theColor;
			
		}
		break;
		case kBrushColorBlueEditID:
		{
			mBrushColorSwatch->GetSwatchColor(theColor);
			theColor.blue = ((LEditText*)ioParam)->GetValue();
			mBrushColorSwatch->StopBroadcasting();
			mBrushColorSwatch->SetSwatchColor(theColor);
			mBrushColorSwatch->StartBroadcasting();
			mPlutChange.aPlut.brushColor = theColor;
		}
		break;
		case kBrushColorSwatchID:
		{
			mBrushColorSwatch->GetSwatchColor(theColor);
			mBrushColorRed->SetValue(theColor.red);
			mBrushColorGreen->SetValue(theColor.green);
			mBrushColorBlue->SetValue(theColor.blue);
			mPlutChange.aPlut.brushColor = theColor;
			
		}
		break;
		
		case kBrushPatternSwatchID:
		{
			//A new Pattern has been placed here. The handle being returned is a PPAT resource
			if(mPlutChange.aPPAT != NULL)
			{
				DisposeHandle(mPlutChange.aPPAT);
				mPlutChange.aPPAT = NULL;
			}
			mPlutChange.aPPAT = ((Handle)ioParam);
			if(ioParam != NULL)
			{
				HandToHand(&(mPlutChange.aPPAT));
			}
			else
			{
				mPlutChange.aPlut.brushPPAT.resID = 0;
				mPlutChange.aPlut.brushPPAT.fileID = 0;
			} 
		}		
		break;
		
		default:
		{
			LDialogBox::ListenToMessage(inMessage,ioParam);
			break;
		}
	}
}

void		TBrushEditDialogBox::FinishCreateSelf()
{
	LDialogBox::FinishCreateSelf();
	mBrushColorRed = (LEditText*)FindPaneByID(kBrushColorRedEditID);
	ThrowIfNil_(mBrushColorRed);
	mBrushColorGreen = (LEditText*)FindPaneByID(kBrushColorGreenEditID);
	ThrowIfNil_(mBrushColorGreen);
	mBrushColorBlue = (LEditText*)FindPaneByID(kBrushColorBlueEditID);
	ThrowIfNil_(mBrushColorBlue);
	mBrushColorSwatch = (LGAColorSwatchControl*)FindPaneByID(kBrushColorSwatchID);
	ThrowIfNil_(mBrushColorSwatch);
	mBrushPatternSwatch = (TGAPPATEditControl*)FindPaneByID(kBrushPatternSwatchID);
	ThrowIfNil_(mBrushPatternSwatch);
	mBrushTitle = (LControlPane*)FindPaneByID(kBrushNameTextID);
	ThrowIfNil_(mBrushTitle);
	
	mBrushColorRed->AddListener(this);
	mBrushColorGreen->AddListener(this);
	mBrushColorBlue->AddListener(this);
	mBrushColorSwatch->AddListener(this);
	mBrushPatternSwatch->AddListener(this);
}

void		TBrushEditDialogBox::SetPlutEntry(const PlutEntry &inPlut)
{
	if(mPlutChange.aPPAT != NULL)
	{
		DisposeHandle(mPlutChange.aPPAT);
		mPlutChange.aPPAT = NULL;
	}
	mPlutChange.aTable = NULL;
	mPlutChange.aCell.row = 0;
	mPlutChange.aCell.col = 0;
	mPlutChange.aPlut = inPlut;
	mBrushColorSwatch->StopBroadcasting();
	mBrushColorSwatch->SetSwatchColor(inPlut.brushColor);
	mBrushColorSwatch->StartBroadcasting();
	mBrushColorRed->SetValue(inPlut.brushColor.red);
	mBrushColorGreen->SetValue(inPlut.brushColor.green);
	mBrushColorBlue->SetValue(inPlut.brushColor.blue);

	mBrushPatternSwatch->SetSwatchPPAT(inPlut.brushPPAT);
}

void		TBrushEditDialogBox::GetPlutChangeRecord(PlutChangeRecord &outPlut)
{
	outPlut = mPlutChange;
}

void		TBrushEditDialogBox::SetTitle(LStr255 inTitle)
{
	mBrushTitle->SetDescriptor(inTitle);
}

void		TBrushEditDialogBox::GetTitle(LStr255 &outTitle)
{
	 mBrushTitle->GetDescriptor(outTitle);
}
