// ===========================================================================
//	TEditorDialogBox.cp	©1999 Allegro Themes Project
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

#include "TEditorDialogBox.h"
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


TEditorDialogBox::TEditorDialogBox()
{
	Init();
}
				
TEditorDialogBox::TEditorDialogBox(LStream*		inStream) : LDialogBox(inStream)
{
	Init();
}


TEditorDialogBox::~TEditorDialogBox()
{
}

void		TEditorDialogBox::Init()
{
	mDoc = NULL;
	mIsModified = false;
}
								

void TEditorDialogBox::AttemptClose()
{
									// Get approval from SuperCommander
	if ((mSuperCommander == nil) || mSuperCommander->AllowSubRemoval(this)) 
	{
		 
		SInt16	answer = answer_Save;
		if(GetIsModified())
		{
			
		
			if (UAppleEventsMgr::InteractWithUser() == noErr) 
			{
				
				answer = AskSaveChanges(SaveWhen_Closing);
			}
			
			if (answer == answer_Save) 
			{
				DoSave();
				GetThemeDocument()->SetModified(true);
					
			} 
			
				
		}
		
		// Send Close AE for recording only
		if (answer != answer_Cancel)
		{
			SendSelfAE(kAECoreSuite, kAEClose, ExecuteAE_No);
			delete this;
		}
	}
}

// ---------------------------------------------------------------------------
//	€ AttemptQuitSelf
// ---------------------------------------------------------------------------

Boolean
TEditorDialogBox::AttemptQuitSelf(
	SInt32	inSaveOption)
{
	Boolean	allowQuit = true;
	
	if (GetIsModified()  &&  (inSaveOption != kAENo) ) {
	
		SInt16	answer = answer_Save;
		
		if (inSaveOption == kAEAsk) 
		{
			UAppleEventsMgr::InteractWithUser(Throw_Yes);
			answer = AskSaveChanges(SaveWhen_Quitting);
		}
		
		if (answer == answer_Save) 
		{
			DoSave();
			GetThemeDocument()->SetModified(true);
				
		} 
		else if (answer == answer_Cancel) 
		{
			allowQuit = false;
		}
	}
	return allowQuit;
}

void		TEditorDialogBox::SetThemeDocument(CThemeDoc *inDocument)
{
	mDoc = inDocument;
}

CThemeDoc*	TEditorDialogBox::GetThemeDocument()
{
	return mDoc;
}

Boolean		TEditorDialogBox::GetIsModified()
{
	return mIsModified;
}

void		TEditorDialogBox::SetIsModified(Boolean isModified/* = true*/)
{
	mIsModified = isModified;
}
	
// ---------------------------------------------------------------------------
//	€ AskSaveChanges											   [protected]
// ---------------------------------------------------------------------------
//	Ask user whether to save changes before closing the Document or
//	quitting the Application

SInt16
TEditorDialogBox::AskSaveChanges(
	bool	inQuitting)
{	
	Str255	theName;
	LStr255	appName(STRx_Standards, str_ProgramName);
	
	return PP_StandardDialogs::AskSaveChanges(GetDescriptor(theName),
										   appName, inQuitting);
}