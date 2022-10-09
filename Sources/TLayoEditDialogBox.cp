// ===========================================================================
//	TLayoEditDialogBox.cp	©1999 Allegro Themes Project
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

#include "TLayoEditDialogBox.h"
#include <LPushButton.h>
#include <LBevelButton.h>
#include "LLayoView.h"
#include <LStaticText.h>
#include <LPopupButton.h>
#include <LCheckBoxGroupBox.h>
#include <LCheckBox.h>
#include <LRadioGroupView.h>
#include "CThemeDoc.h"
#include "LCoordinateHierTable.h"

// ---------------------------------------------------------------------------

static const PaneIDT kViewPane = 'LaVi';
static const PaneIDT kVisibleBase = 16000;
static const PaneIDT kInvisibleBase = 16100;
static const PaneIDT kFeatureBase = 16200;
static const PaneIDT kShowLinesCheckbox = 'ShLi';
static const UInt32 kVisibleFlagCount = 9;
static const UInt32 kInvisibleFlagCount = 9;
static const UInt32 kFeatureFlagCount = 10;
static const PaneIDT kCoordinateTable = 'COTA';

TLayoEditDialogBox::TLayoEditDialogBox()
{
}
				
TLayoEditDialogBox::TLayoEditDialogBox(LStream*		inStream) : TEditorDialogBox(inStream)
{
}


TLayoEditDialogBox::~TLayoEditDialogBox()
{
}

void		TLayoEditDialogBox::Init()
{
	mLayoView = NULL;
	mCoordinateTable = NULL;
}
								
void		TLayoEditDialogBox::ListenToMessage(MessageT		inMessage,void*			ioParam)
{
	UInt32 theVisibleFlags, theFeatureFlags;
	if(inMessage > kVisibleBase && inMessage <=  kVisibleBase + kVisibleFlagCount)
	{
		mLayoView->GetFlags(theVisibleFlags,theFeatureFlags);
		SInt32 theMessage = *((SInt32*)ioParam);
		if(theMessage)
		{
			theVisibleFlags |= 1 << (inMessage - kVisibleBase - 1);
		}
		else
		{
			theVisibleFlags ^= 1 << (inMessage - kVisibleBase - 1);
		}
		mLayoView->SetFlags(theVisibleFlags,theFeatureFlags);
	}
	else if(inMessage > kFeatureBase && inMessage <=  kFeatureBase + kFeatureFlagCount)
	{
		mLayoView->GetFlags(theVisibleFlags,theFeatureFlags);
		SInt32 theMessage = *((SInt32*)ioParam);
		if(theMessage)
		{
			theFeatureFlags |= 1 << (inMessage - kFeatureBase - 1);
		}
		else
		{
			theFeatureFlags ^= 1 << (inMessage - kFeatureBase - 1);
		}
		mLayoView->SetFlags(theVisibleFlags,theFeatureFlags);
	}
	else
	{
		switch(inMessage)
		{
			case kShowLinesCheckbox:
			{
				SInt32 theMessage = *((SInt32*)ioParam);
				mLayoView->SetShowLines(theMessage);
			}
			break;
			
			default:
			{
				LDialogBox::ListenToMessage(inMessage,ioParam);
				break;
			}
		}
	}
}

void		TLayoEditDialogBox::FinishCreateSelf()
{
	LDialogBox::FinishCreateSelf();
	
	mLayoView = (LLayoView*)FindPaneByID(kViewPane);
	SignalIfNot_(mLayoView);
	
	LCheckBox* theCheckBox;
	
	for(UInt32 i = 1; i<= kVisibleFlagCount; i++)
	{
		theCheckBox = (LCheckBox*)FindPaneByID(kVisibleBase + i);
		SignalIfNot_(theCheckBox);
		theCheckBox->AddListener(this);
	}
	
	/*for(UInt32 i = 1; i<= kInvisibleFlagCount; i++)
	{
		theCheckBox = (LCheckBox*)FindPaneByID(kInvisibleBase + i);
		SignalIfNot_(theCheckBox);
		theCheckBox->AddListener(this);
	}*/
	
	for(UInt32 i = 1; i<= kFeatureFlagCount; i++)
	{
		theCheckBox = (LCheckBox*)FindPaneByID(kFeatureBase + i);
		SignalIfNot_(theCheckBox);
		theCheckBox->AddListener(this);
	}
	
	theCheckBox = (LCheckBox*)FindPaneByID(kFeatureBase + 30);
	SignalIfNot_(theCheckBox);
	theCheckBox->AddListener(this);
	
	theCheckBox = (LCheckBox*)FindPaneByID(kShowLinesCheckbox);
	SignalIfNot_(theCheckBox);
	theCheckBox->AddListener(this);
	
	mCoordinateTable = (LCoordinateHierTable*)FindPaneByID(kCoordinateTable);
	SignalIfNot_(mCoordinateTable);
	
}

void		TLayoEditDialogBox::SetLayoResource(const FullResourceSpec &inSpec)
{
	mLayoResource.Init(inSpec.resID,inSpec.fileID);
	mLayoView->SetLayoutResource(&mLayoResource);
	mCoordinateTable->SetLayoutResource(&mLayoResource);
	SetDescriptor(mLayoResource.GetResName());
}

void TLayoEditDialogBox::DoSave()
{
	/*StCurResFile(mPxmSpec.fileID);
	SignalIf_(mPxmSpec.resType != 'pxm#');
	
	Handle thePxm = GetResource(mPxmSpec.resID, mPxmSpec.resType);
	SignalIf_(thePxm == NULL);
	mPxm.WriteToHandle(thePxm);
	ChangedResource(thePxm);
	WriteResource(thePxm);*/
}

