// ===========================================================================
//	CAppearanceApp.cp 		©1994-1998 Metrowerks Inc. All rights reserved.
// ===========================================================================
//	This file contains the starter code for an Appearance PowerPlant application

#include "CAppearanceApp.h"

#include <LGrowZone.h>
#include <PP_Messages.h>
#include <PP_Resources.h>
#include <UDrawingState.h>
#include <UMemoryMgr.h>
#include <URegistrar.h>
#include <UControlRegistry.h>
#include <UEnvironment.h>

#include <LWindow.h>
#include <LCaption.h>
#include "CThemeDoc.h"
#include <Appearance.h>
#include <UStandardDialogs.h>
#include "UTClrListResource.h"
#include "TGAPPATSwatchControl.h"
#include "TGAPPATEditControl.h"
#include <LTabGroup.h>
#include "TThemes.h"
#include <UResourceMgr.h>
#include <LCMAttachment.h>
#include <UCMMUtils.h>
#include "UTClut.h"
#include "TTextClrListTable.h"
#include <LActiveScroller.h>
#include "TBrushTable.h"
#include <LDialogBox.h>
#include "TBrushEditDialogBox.h"
#include <LPicture.h>
#include <LSeparatorLine.h>
#include "TFixedColumnView.h"
#include <UAttachments.h>
#include "LPxmView.h"
#include "TPxmEditDialogBox.h"
#include "TClutTable.h"
#include "TEditImageWell.h"
#include "TGAPLUTSwatchControl.h"
#include "TFrmeEditDialogBox.h"
#include "LFrameView.h"
#include "TMagnifyPane.h"
#include "LLayoView.h"
#include "TLayoEditDialogBox.h"
#include "LCoordinateHierTable.h"

const ResIDT	kMagnifyerWindowID			= 137;
const PaneIDT	kMagnifyingViewID			= 'MVie';

// ===========================================================================
//	€ main
// ===========================================================================
int main()
{
	
	
		// Set Debugging options
	SetDebugThrow_(debugAction_Alert);
	SetDebugSignal_(debugAction_Alert);

		// Initialize Memory Manager. Parameter is the number of
		// master pointer blocks to allocate
	InitializeHeap(3);
	
		// Initialize standard Toolbox managers
	UQDGlobals::InitializeToolbox(&qd);
	
		// Install a GrowZone to catch low-memory situations	
	new LGrowZone(20000);
	
		// Create the application object and run
	CAppearanceApp	theApp;
	theApp.Run();
	
	return 0;
}


// ---------------------------------------------------------------------------
//	€ CAppearanceApp								[public]
// ---------------------------------------------------------------------------
//	Application object constructor

CAppearanceApp::CAppearanceApp()
{
	mAppResFile = CurResFile();
	
		// Register ourselves with the Appearance Manager
	if (UEnvironment::HasFeature(env_HasAppearance)) {
		::RegisterAppearanceClient();
	}
	
		// Register Ourselves with the Contextual Menus
	UCMMUtils::Initialize();
	
		// Register PowerPlant classes used in the PPob(s)
	RegisterClass_(LWindow);
	RegisterClass_(LTabGroup);
	RegisterClass_(TGAPPATSwatchControl);
	RegisterClass_(TGAPPATEditControl);
	RegisterClass_(LCMAttachment);
	RegisterClass_(TTextClrListTable);
	RegisterClass_(LActiveScroller);
	RegisterClass_(TBrushTable);
	RegisterClass_(LDialogBox);
	RegisterClass_(TBrushEditDialogBox);
	RegisterClass_(LPicture);
	RegisterClass_(TFixedColumnView);
	RegisterClass_(LBorderAttachment);
	RegisterClass_(LPxmView);
	RegisterClass_(TPxmEditDialogBox);
	RegisterClass_(TClutTable);
	RegisterClass_(TEditImageWell);
	RegisterClass_(TGAPLUTSwatchControl);
	RegisterClass_(TFrmeEditDialogBox);
	RegisterClass_(LFrameView);
	RegisterClass_(TMagnifyPane);
	RegisterClass_(LLayoView);
	RegisterClass_(TLayoEditDialogBox);
	RegisterClass_(LCoordinateHierTable);
		// Register the Appearance Manager/GA classes
	UControlRegistry::RegisterClasses();
	
		//Give ourselves a clipboard
	LClipboard *theClip = new LClipboard();
	AddAttachment(theClip);
	
		//Enable ContextualMenus
	LCMAttachment *theContextualMenu = new LCMAttachment();
	AddAttachment(theContextualMenu);
	
	mMagnifyWindow = LWindow::CreateWindow(kMagnifyerWindowID, this);
	mMagnifyPane = (TMagnifyPane*)mMagnifyWindow->FindPaneByID(kMagnifyingViewID);
}


// ---------------------------------------------------------------------------
//	€ ~CAppearanceApp								[public, virtual]
// ---------------------------------------------------------------------------
//	Application object destructor

CAppearanceApp::~CAppearanceApp()
{
	// nothing
}


// ---------------------------------------------------------------------------
//	€ StartUp										[protected, virtual]
// ---------------------------------------------------------------------------
//	Perform an action in response to the Open Application AppleEvent.
//	Here, issue the New command to open a window.

void
CAppearanceApp::StartUp()
{
	ObeyCommand(PP_PowerPlant::cmd_Open, nil);	// EXAMPLE, create a new window
	
	
}


// ---------------------------------------------------------------------------
//	€ ObeyCommand									[public, virtual]
// ---------------------------------------------------------------------------
//	Respond to Commands. Returns true if the Command was handled, false if not.

Boolean
CAppearanceApp::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
		// Assume we'll handle the Command
	Boolean		cmdHandled = true;

	switch (inCommand) 
	{

		case cmd_ShowMagnifyer:
		{
			if(mMagnifyWindow->IsVisible())
			{
				mMagnifyWindow->Hide();
				mMagnifyPane->StopIdling();
			}
			else
			{
				mMagnifyWindow->Show();
				mMagnifyPane->StartIdling();
			}
		}
		break;
		
		default:
			cmdHandled = LDocApplication::ObeyCommand(inCommand, ioParam);
			break;
	}
	
	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	€ FindCommandStatus								[public, virtual]
// ---------------------------------------------------------------------------
//	Determine the status of a Command for the purposes of menu updating.

void
CAppearanceApp::FindCommandStatus(
	CommandT	inCommand,
	Boolean&	outEnabled,
	Boolean&	outUsesMark,
	UInt16&		outMark,
	Str255		outName)
{

	switch (inCommand) {

		case cmd_ShowMagnifyer:
		{
			outEnabled = true;
			outUsesMark = true;
			if(mMagnifyWindow->IsVisible())
			{
				outMark = checkMark;
			}
			else
			{
				outMark = 0;
			}
		}
		break;
		
		default:
			LDocApplication::FindCommandStatus(inCommand, outEnabled,
										outUsesMark, outMark, outName);
			break;
	}
}

// ---------------------------------------------------------------------------
//	€ OpenDocument													  [public]
// ---------------------------------------------------------------------------
//	Open a Document specified by an FSSpec

void
CAppearanceApp::OpenDocument(
	FSSpec*	inMacFSSpec)
{
	CThemeDoc* theDoc = new CThemeDoc(this,inMacFSSpec);
}


void
CAppearanceApp::ChooseDocument()
{
		// LFileChooser presents the standard dialog for asking
		// the user to open a file. It supports both StandardFile
		// and Navigation Services. The latter allows opening
		// multiple files.

	PP_StandardDialogs::LFileChooser	chooser;
	LFileTypeList theList('thme');
	
	NavDialogOptions* theOptions = chooser.GetDialogOptions();
	theOptions->dialogOptionFlags = kNavNoTypePopup + kNavDontAutoTranslate + kNavDontAddTranslateItems + kNavSelectAllReadableItem;
	if (chooser.AskOpenFile(theList)) {
		AEDescList		docList;
		chooser.GetFileDescList(docList);
		SendAEOpenDocList(docList);
	}
}

void		CAppearanceApp::ShowAboutBox()
{
	StCurResFile i;
	UseResFile(mAppResFile);
	LDocApplication::ShowAboutBox();
}

Boolean
CAppearanceApp::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mMagnifyWindow) 
	{
		mMagnifyWindow->Hide();
		mMagnifyPane->StopIdling();
		return false;

	}
	else
	{
		return LDocApplication::AllowSubRemoval(inSub);
	}
}