// ===========================================================================
//	TEditImageWell.cpp			   Allegro Themes Project
// ===========================================================================
//
//	A Pane for Editing PPAT's.
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Jan 1/99 Initial Implementation
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

#pragma mark === INITIALIZATION

#include "TEditImageWell.h"

// ---------------------------------------------------------------------------
//	€ TEditImageWell					Stream Constructor		  [public]
// ---------------------------------------------------------------------------

TEditImageWell::TEditImageWell( 
	LStream*	inStream)
	
	: LImageWell(inStream)
{
	Init();
}


// ---------------------------------------------------------------------------
//	€ TEditImageWell					Parameterized Constructor [public]
// ---------------------------------------------------------------------------

TEditImageWell::TEditImageWell(	
	const SPaneInfo&	inPaneInfo,
								const SViewInfo&	inViewInfo,
								MessageT			inValueMessage,
								SInt16				inContentType,
								SInt16				inContentResID)
	
	: LImageWell(inPaneInfo,
				inViewInfo,inValueMessage,inContentType,inContentResID)
{
	Init();
}


// ---------------------------------------------------------------------------
//	€ ~TEditImageWell				Destructor				  [public]
// ---------------------------------------------------------------------------

TEditImageWell::~TEditImageWell ()
{


}

// ---------------------------------------------------------------------------
//	€ Init									Initializer				  [protected]
// ---------------------------------------------------------------------------

void 
TEditImageWell::Init()
{
	mFocusBox = new LFocusBox();
	mFocusBox->AttachPane(this,true);
	mFocusBox->Hide();
}


#pragma mark -
#pragma mark === MOUSE TRACKING

// ---------------------------------------------------------------------------
//	€ DoneTracking												   [protected]
// ---------------------------------------------------------------------------

void
TEditImageWell::DoneTracking( 	
	SInt16		/*inHotSpot*/,
	Boolean		inGoodTrack)
{
	
	if ( inGoodTrack ) 
	{
		SwitchTarget(this);
	}
}



#pragma mark -
#pragma mark === TARGET

// ---------------------------------------------------------------------------
//	€ BeTarget												   	[protected]
// ---------------------------------------------------------------------------

void		
TEditImageWell::BeTarget()
{
	mFocusBox->Show();
}

// ---------------------------------------------------------------------------
//	€ DontBeTarget												   	[protected]
// ---------------------------------------------------------------------------

void		
TEditImageWell::DontBeTarget()
{
		mFocusBox->Hide();
}

#pragma mark -
#pragma mark === COMMANDS

// ---------------------------------------------------------------------------
//	€ FindCommandStatus												  [public]
// ---------------------------------------------------------------------------

void
TEditImageWell::FindCommandStatus(
	CommandT	inCommand,
	Boolean&		outEnabled,
	Boolean&		outUsesMark,
	UInt16&		outMark,
	Str255			outName)
{
			
	switch(inCommand)
	{
		case cmd_Copy:
			outEnabled = true;
			break;
			
		case cmd_Paste:
			LClipboard* theClip = LClipboard::GetClipboard();
			outEnabled = ((theClip->GetData('icns',NULL) > 0) || (theClip->GetData('PICT',NULL) > 0));
			break;
			
		default:
			LCommander::FindCommandStatus( inCommand,
			outEnabled, outUsesMark, outMark, outName );
	}
				
}


// ---------------------------------------------------------------------------
//	€ ObeyCommand												  [public]
// ---------------------------------------------------------------------------

Boolean
TEditImageWell::ObeyCommand(
	CommandT	inCommand,
	void			*ioParam )
{
	Boolean		cmdHandled = true;

		 
	switch (inCommand) {
		
		case cmd_Copy:
		{
			ControlButtonContentInfo theInfo;
			GetContentInfo(theInfo);
			IconFamilyHandle theFamily;
			ThrowIfOSErr_(IconSuiteToIconFamily(theInfo.u.iconSuite,svAllAvailableData,&theFamily));
			LClipboard::GetClipboard()->SetData('icns', (Handle)theFamily,true);
			Handle theHandle = NewHandle(1);
			ThrowIfOSErr_(GetIconFamilyData(theFamily,'PICT',theHandle));
			LClipboard::GetClipboard()->SetData('PICT', theHandle,false);
			DisposeHandle((Handle)theFamily);
			DisposeHandle(theHandle);
		}
		break;
		
		case cmd_Paste:
		{
			IconSuiteRef theNewSuite = NULL;
			UInt32 theSize;
			ControlButtonContentInfo theInfo;
			GetContentInfo(theInfo);
			if((theSize = LClipboard::GetClipboard()->GetData('icns',NULL)) > 0)
			{
				IconFamilyHandle theFamily = (IconFamilyHandle)NewHandle(theSize);
				LClipboard::GetClipboard()->GetData('icns',(Handle)theFamily);
				ThrowIfOSErr_(IconFamilyToIconSuite(theFamily,svAllAvailableData,&theNewSuite));
				DisposeHandle((Handle)theFamily);
			}
			else if((theSize = LClipboard::GetClipboard()->GetData('PICT',NULL)) > 0)
			{
				IconFamilyHandle theFamily;
				IconSuiteRef theBlankSuite;
				ThrowIfOSErr_(NewIconSuite(&theBlankSuite));
				ThrowIfOSErr_(IconSuiteToIconFamily(theBlankSuite,svAllAvailableData,&theFamily));
				Handle theHandle = NewHandle(theSize);
				LClipboard::GetClipboard()->GetData('PICT',theHandle);
				ThrowIfOSErr_(SetIconFamilyData(theFamily,'PICT',theHandle));
				DisposeIconSuite(theBlankSuite,true);
				ThrowIfOSErr_(IconFamilyToIconSuite(theFamily,svAllAvailableData,&theNewSuite));
				DisposeHandle((Handle)theFamily);
			}
			MessageT	message = mControlSubPane->GetValueMessage();
			if (message != msg_Nothing) 
			{
				BroadcastMessage(message, theNewSuite);
			}
		}
		break;
		
		default: {
			cmdHandled = LCommander::ObeyCommand(inCommand,ioParam);
			break;
		}
	}
	return cmdHandled;
}

// ---------------------------------------------------------------------------
//	€ HotSpotResult												  [public]
// ---------------------------------------------------------------------------
void
TEditImageWell::HotSpotResult(
	SInt16	/* inHotSpot */)
{
	SwitchTarget(this);
}
