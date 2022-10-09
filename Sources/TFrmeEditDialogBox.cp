// ===========================================================================
//	TFrmeEditDialogBox.cp	©1999 Allegro Themes Project
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

#include "TFrmeEditDialogBox.h"
#include <LPushButton.h>
#include <LBevelButton.h>
#include "UTFrmeResource.h"
#include "LFrameView.h"
#include <LStaticText.h>
#include <LPopupButton.h>
#include <LCheckBoxGroupBox.h>
#include <LCheckBox.h>
#include <LRadioGroupView.h>
#include "CThemeDoc.h"
// ---------------------------------------------------------------------------

static const PaneIDT kAddFrameID = 'AddF';
static const PaneIDT kDeleteFrameID = 'DelF';
static const PaneIDT kFrameViewID = 'FrVi';
static const PaneIDT kEyeDropperButtonID = 'EYED';
static const PaneIDT kUpperLeftPencilButtonID = 'UPRL';
static const PaneIDT kUpperRightPencilButtonID = 'UPRR';
static const PaneIDT kLowerLeftPencilButtonID = 'LWRL';
static const PaneIDT kLowerRightPencilButtonID = 'LWRR';
static const PaneIDT kShowGridCheckBoxID = 'SHGR';
static const PaneIDT kShowColorsCheckBoxID = 'SHCO';
static const ResID	kAddDelFrameDlogID = 136;
static const PaneIDT kOKButtonID = 'OKOK';
static const PaneIDT kCancelButtonID = 'CANC';
static const PaneIDT kAddDelFrameStaticTextID = 'FrTe';
static const PaneIDT kAddDelFramePopupID = 'FrPo';
static const ResID kAddDelFrameStringID = 306;
static const UInt32 kAddFrameStringIndex = 2;
static const UInt32 kDelFrameStringIndex = 1;
static const PaneIDT kMagnifyingGlassButtonID = 'MAGG';
static const PaneIDT kPencilGroupID = 'PNCG';

TFrmeEditDialogBox::TFrmeEditDialogBox()
{
}
				
TFrmeEditDialogBox::TFrmeEditDialogBox(LStream*		inStream) : TEditorDialogBox(inStream)
{
}


TFrmeEditDialogBox::~TFrmeEditDialogBox()
{
}

void		TFrmeEditDialogBox::Init()
{
	mFrameView = NULL;
}
								
void		TFrmeEditDialogBox::ListenToMessage(MessageT		inMessage,void*			ioParam)
{
	
	switch(inMessage)
	{
		case kAddFrameID:
		{
			DeleteAddFrameDialog(true);
		}
		break;
		
		case kDeleteFrameID:
		{
			DeleteAddFrameDialog(false);
		}
		break;
		
		case kEyeDropperButtonID:
			mFrameView->SetEyeDropperMode(*((SInt32*)ioParam),false);
		break;
		
		case kMagnifyingGlassButtonID:
			mFrameView->SetMagnifyingMode(*((SInt32*)ioParam),false);
			mPencilRadioGroup->SetCurrentRadioID(0);
		break;
		
		case LFrameView::kEyeDropMessage:
		{
			LBevelButton *theBevelButton = (LBevelButton*)FindPaneByID(kEyeDropperButtonID);
			SignalIfNot_(theBevelButton);
			theBevelButton->SetValue(*((SInt32*)ioParam));
		}
		break;
		
		case kShowGridCheckBoxID:
		{
			LCheckBoxGroupBox* theGroupBox = (LCheckBoxGroupBox*)FindPaneByID(kShowGridCheckBoxID);
			SignalIfNot_(theGroupBox);
			theGroupBox->SetValue(*((SInt32*)ioParam));
			LCheckBox* theCheckBox = (LCheckBox*)FindPaneByID(kShowColorsCheckBoxID);
			SignalIfNot_(theCheckBox);
			mFrameView->SetShowGrid(*((SInt32*)ioParam),theCheckBox->GetValue());
			mFrameView->Draw(NULL);
		}
		break;
		
		case kShowColorsCheckBoxID:
		{
			LCheckBox* theCheckBox = (LCheckBox*)FindPaneByID(kShowColorsCheckBoxID);
			SignalIfNot_(theCheckBox);
			LCheckBoxGroupBox* theGroupBox = (LCheckBoxGroupBox*)FindPaneByID(kShowGridCheckBoxID);
			SignalIfNot_(theGroupBox);
			theCheckBox->SetValue(*((SInt32*)ioParam));
			mFrameView->SetShowGrid(theGroupBox->GetValue(),*((SInt32*)ioParam));
			mFrameView->Draw(NULL);
		}
		break;
		
		default:
		{
			LDialogBox::ListenToMessage(inMessage,ioParam);
			break;
		}
	}
}

void TFrmeEditDialogBox::DoSave()
{
	mFrameView->BuildFrmeResource(mFrmeResource);
	mFrmeResource.Write();
}


void		TFrmeEditDialogBox::FinishCreateSelf()
{
	LDialogBox::FinishCreateSelf();
	
	
	LPushButton* theButton  = (LPushButton*)FindPaneByID(kAddFrameID);
	SignalIfNot_(theButton);
	theButton->AddListener(this);
	
	theButton  = (LPushButton*)FindPaneByID(kDeleteFrameID);
	SignalIfNot_(theButton);
	theButton->AddListener(this);
	
	LBevelButton *theBevelButton = (LBevelButton*)FindPaneByID(kEyeDropperButtonID);
	SignalIfNot_(theBevelButton);
	theBevelButton->AddListener(this);
	
	mPencilRadioGroup = (LRadioGroupView*)FindPaneByID(kPencilGroupID);
	SignalIfNot_(mPencilRadioGroup);
	mPencilRadioGroup->SetCurrentRadioID(kUpperRightPencilButtonID);

	theBevelButton = (LBevelButton*)FindPaneByID(kUpperRightPencilButtonID);
	SignalIfNot_(theBevelButton);
	theBevelButton->AddListener(this);
	
	theBevelButton = (LBevelButton*)FindPaneByID(kMagnifyingGlassButtonID);
	SignalIfNot_(theBevelButton);
	theBevelButton->AddListener(this);
	
	theBevelButton = (LBevelButton*)FindPaneByID(kEyeDropperButtonID);
	SignalIfNot_(theBevelButton);
	theBevelButton->AddListener(this);
	
	LCheckBoxGroupBox* theGroupBox = (LCheckBoxGroupBox*)FindPaneByID(kShowGridCheckBoxID);
	SignalIfNot_(theGroupBox);
	theGroupBox->SetValue(true);
	theGroupBox->AddListener(this);
	
	LCheckBox* theCheckBox = (LCheckBox*)FindPaneByID(kShowColorsCheckBoxID);
	SignalIfNot_(theCheckBox);
	theCheckBox->SetValue(true);
	theCheckBox->AddListener(this);
	
	mFrameView = (LFrameView*)FindPaneByID(kFrameViewID);
	SignalIfNot_(mFrameView);
	mFrameView->AddListener(this);
	mFrameView->SetEditDialog(this);

}


void		TFrmeEditDialogBox::SetFrmeResource(const FullResourceSpec &inSpec)
{
	mFrmeResource.Init(inSpec.resID,inSpec.fileID);
	mFrameView->SetFrmeResource(&mFrmeResource);
	SetDescriptor(mFrmeResource.GetResName());
}

void	TFrmeEditDialogBox::DeleteAddFrameDialog(Boolean addFrame)
{
	LDialogBox* theAddDialog = (LDialogBox*)LWindow::CreateWindow(kAddDelFrameDlogID, this);
	StDialogHandler theHandler(theAddDialog,this);
	
	LPushButton* theButton = (LPushButton*)theAddDialog->FindPaneByID(kOKButtonID);
	ThrowIfNil_(theButton);
	theButton->AddListener(&theHandler);
	theButton = (LPushButton*)theAddDialog->FindPaneByID(kCancelButtonID);
	SignalIfNot_(theButton);
	theButton->AddListener(&theHandler);
	
	LStaticText *theText = (LStaticText*)theAddDialog->FindPaneByID(kAddDelFrameStaticTextID);
	LStr255 theAddText(kAddDelFrameStringID, addFrame ? kAddFrameStringIndex : kDelFrameStringIndex);
	theText->SetDescriptor(theAddText);
	
	LPopupButton* thePopUp = (LPopupButton*)theAddDialog->FindPaneByID(kAddDelFramePopupID);
	SignalIfNot_(thePopUp);
	MenuHandle theHandle = thePopUp->GetMacMenuH();
	for(SInt32 i = -10; i <= 10; i++)
	{
		LFrameRectView* theRectView = mFrameView->GetFrame(i);
		if(addFrame)
		{
			if(theRectView == NULL)
			{
				EnableMenuItem(theHandle,i + 11);
			}
			else
			{
				DisableMenuItem(theHandle,i + 11);
			}
		}
		else
		{
			if(theRectView == NULL)
			{
				DisableMenuItem(theHandle,i + 11);
			}
			else
			{
				EnableMenuItem(theHandle,i + 11);
			}
		}
	}
	SInt32 i;
	for(SInt32 i = 0; i <= 10; i++)
	{
		if(IsMenuItemEnabled(theHandle,11 + i))
		{
			thePopUp->SetValue(11 + i);
			break;
		}
		else if(IsMenuItemEnabled(theHandle, 11 - i))
		{
			thePopUp->SetValue(11 - i);
			break;
		}
	}
	if(i > 10)
	{
		thePopUp->Disable();
	}	
	Boolean doDialog = true;
	while(doDialog)
	{
		MessageT theMessage = theHandler.DoDialog();
		if(theMessage == msg_OK)
		{
			doDialog = false;
			SInt32 theInset = thePopUp->GetCurrentMenuItem() - 11;
			if(addFrame)
			{
				mFrameView->AddFrame(theInset,true);
			}
			else
			{
				mFrameView->RemoveFrame(theInset,true);
			}
			mFrameView->SetIsModified();
		}
		else if(theMessage == msg_Cancel)
		{
			doDialog = false;
		}
	}
}

