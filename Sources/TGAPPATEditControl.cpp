// ===========================================================================
//	TGAPPATEditControl.cp	©1999 Allegro Themes Project
// ===========================================================================
//	Author: Dave MacLachlan
//	Based On LGAColorSwatchControl By Robin Mair
//
//	Control for displaying a pattern and editing it. It handles copy and pasting.
//
// ToDo: Add Drag support, and add support for pasting in PICT
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

#include "TGAPPATEditControl.h"
#include <UGraphicUtils.h>
#include <UGAColorRamp.h>

#include <LStream.h>
#include <UDrawingUtils.h>
#include <UDesktop.h>
#include <UQDOperators.h>
#include <PP_Messages.h>
#include <UResourceMgr.h>
#include <LFocusBox.h>
#include "UTPixUtilities.h"
#include <UStandardDialogs.h>

#pragma mark === INITIALIZATION

// ---------------------------------------------------------------------------
//	€ TGAPPATEditControl					Default Constructor		  [public]
// ---------------------------------------------------------------------------

TGAPPATEditControl::TGAPPATEditControl()
{
	Init();
}


// ---------------------------------------------------------------------------
//	€ TGAPPATEditControl					Copy Constructor		  [public]
// ---------------------------------------------------------------------------

TGAPPATEditControl::TGAPPATEditControl(	
	const TGAPPATEditControl&	inOriginal)
	
	: TGAPPATSwatchControl(inOriginal)
{
	Init();
}


// ---------------------------------------------------------------------------
//	€ TGAPPATEditControl					Stream Constructor		  [public]
// ---------------------------------------------------------------------------

TGAPPATEditControl::TGAPPATEditControl( 
	LStream*	inStream)
	
	: TGAPPATSwatchControl(inStream)
{
	Init();
}


// ---------------------------------------------------------------------------
//	€ TGAPPATEditControl					Parameterized Constructor [public]
// ---------------------------------------------------------------------------

TGAPPATEditControl::TGAPPATEditControl(	
	const SPaneInfo&	inPaneInfo,
	const SControlInfo&	inControlInfo,
	const FullResourceSpec&		inSpec,
	Str255				inPromptString)
	
	: TGAPPATSwatchControl(inPaneInfo,
				inControlInfo,inSpec,inPromptString)
{
	Init();
}


// ---------------------------------------------------------------------------
//	€ ~TGAPPATEditControl				Destructor				  [public]
// ---------------------------------------------------------------------------

TGAPPATEditControl::~TGAPPATEditControl ()
{
}

// ---------------------------------------------------------------------------
//	€ Init									Initializer				  [protected]
// ---------------------------------------------------------------------------

void 
TGAPPATEditControl::Init()
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
TGAPPATEditControl::DoneTracking( 	
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
TGAPPATEditControl::BeTarget()
{
	mFocusBox->Show();
}

// ---------------------------------------------------------------------------
//	€ DontBeTarget												   	[protected]
// ---------------------------------------------------------------------------

void		
TGAPPATEditControl::DontBeTarget()
{
		mFocusBox->Hide();
}

#pragma mark -
#pragma mark === COMMANDS

// ---------------------------------------------------------------------------
//	€ FindCommandStatus												  [public]
// ---------------------------------------------------------------------------

void
TGAPPATEditControl::FindCommandStatus(
	CommandT	inCommand,
	Boolean&		outEnabled,
	Boolean&		outUsesMark,
	UInt16&		outMark,
	Str255			outName)
{
			
	switch(inCommand)
	{
		case cmd_Copy:
		case cmd_Cut:
		case cmd_Clear:
			outEnabled = (mPattern != NULL);
			break;
			
		case cmd_Paste:
			LClipboard* theClip = LClipboard::GetClipboard();
			outEnabled = ((theClip->GetData('ppat',NULL) > 0) || (theClip->GetData('PICT',NULL) > 0));
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
TGAPPATEditControl::ObeyCommand(
	CommandT	inCommand,
	void			*ioParam )
{
	Boolean		cmdHandled = true;

		 
	switch (inCommand) {
		
		case cmd_Copy:
		{
			cmdHandled = true;
			if(mPattern != NULL)
			{
				Handle thePPAT = NULL;
				if(UTPixUtilities::PixPatToPPAT(mPattern, thePPAT) == noErr)
				{
					LClipboard::GetClipboard()->SetData('ppat', thePPAT);
					DisposeHandle(thePPAT);
				}
				PicHandle thePict = NULL;
				if(UTPixUtilities::PixPatToPict(mPattern, thePict) == noErr)
				{
					LClipboard::GetClipboard()->SetData('PICT', (Handle)thePict,false);
					DisposeHandle((Handle)thePict);
				}
			}
		}
		break;
		
		case cmd_Paste:
		{
			cmdHandled = true;
			
			if(LClipboard::GetClipboard()->GetData('ppat',NULL) > 0)
			{
				
				Handle thePPAT = NewHandle(1);
				
				if(LClipboard::GetClipboard()->GetData('ppat',thePPAT) > 0)
				{
					if(mPattern != NULL)
					{
						DisposePixPat(mPattern);
						mPattern = NULL;
					}
					if(UTPixUtilities::PPATToPixPat(thePPAT,mPattern) == noErr)
					{
						BroadcastValueMessage();
						Draw(nil);
					}
				}
			}
			else if(LClipboard::GetClipboard()->GetData('PICT',NULL) > 0)
			{
				Handle thePicture = NewHandle(1);
				if(LClipboard::GetClipboard()->GetData('PICT',thePicture) > 0)
				{
					
					if(mPattern != NULL)
					{
						DisposePixPat(mPattern);
						mPattern = NULL;
					}
					if(UTPixUtilities::PictToPixPat((PicHandle)thePicture, mPattern) == noErr)
					{
						BroadcastValueMessage();
						Draw(nil);					
					}
				}
				DisposeHandle(thePicture);
			}
		}
		break;
		
		case cmd_Clear:
		{
			cmdHandled = true;
			if(mPattern != NULL)
			{
				DisposePixPat(mPattern);
				mPattern = NULL;
				BroadcastValueMessage();
				Draw(nil);
			}
		}
		break;
		
		case cmd_Cut:
		{
			cmdHandled = true;
			if(mPattern != NULL)
			{
				Handle thePPAT = NULL;
				if(UTPixUtilities::PixPatToPPAT(mPattern, thePPAT) == noErr)
				{
					LClipboard::GetClipboard()->SetData('ppat', thePPAT);
					DisposeHandle(thePPAT);
				}
				PicHandle thePict = NULL;
				if(UTPixUtilities::PixPatToPict(mPattern, thePict) == noErr)
				{
					LClipboard::GetClipboard()->SetData('PICT', (Handle)thePict,false);
					DisposeHandle((Handle)thePict);
				}
				DisposePixPat(mPattern);
				mPattern = NULL;
				BroadcastValueMessage();
				Draw(nil);
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
TGAPPATEditControl::HotSpotResult(
	SInt16	/* inHotSpot */)
{
		// LFileChooser presents the standard dialog for asking
		// the user to open a file. It supports both StandardFile
		// and Navigation Services. The latter allows opening
		// multiple files.
	if(GetClickCount() == 2)
	{
		PP_StandardDialogs::LFileChooser	chooser;
		LFileTypeList theList('PICT');
		FSSpec theSpec;
		
		NavDialogOptions* theOptions = chooser.GetDialogOptions();
		theOptions->dialogOptionFlags = kNavNoTypePopup + kNavDontAddTranslateItems + kNavSelectAllReadableItem;
		if (chooser.AskChooseOneFile(theList,theSpec)) 
		{
			PicHandle thePic = NULL;
			if(UTPixUtilities::PictFileToPict(theSpec,thePic) == noErr)
			{
				if(mPattern != NULL)
				{
					DisposePixPat(mPattern);
					mPattern = NULL;
				}
				if(UTPixUtilities::PictToPixPat((PicHandle)thePic, mPattern) == noErr)
				{
					BroadcastValueMessage();
					Draw(nil);
				}
			}
		}	
	}
}
