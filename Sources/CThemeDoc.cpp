// ===========================================================================
//	CThemeDoc.cp				   ©1994-1998 Metrowerks Inc. All rights reserved.
// ===========================================================================
//
//	A simple text document class. It can handle opening, saving, and
//	reverting TEXT files. It displays the text in a Window and can
//	print the text.
//
//	We also demonstrate a way to have a contextual menu bar (i.e. the
//	contents of the menu bar varies based upon the front window).
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


#include "CThemeDoc.h"

#include <LWindow.h>
#include <LFile.h>
#include <LPrintout.h>
#include <LPlaceHolder.h>
#include <LUndoer.h>
#include <LString.h>
#include <LMenu.h>
#include <LMenuBar.h>
#include <PP_Resources.h>
#include <UTEViewTextAction.h>
#include <UMemoryMgr.h>
#include <UQDOperators.h>
#include <UWindows.h>
#include "FileCopy.h"
#include <Fonts.h>
#include <LPopupButton.h>
#include <LGAColorSwatchControl.h>
#include <LEditText.h>
#include "TGAPPATEditControl.h"
#include <LImageWell.h>
#include "TTextClrListTable.h"
#include <UTableHelpers.h>
#include "TBrushTable.h"
#include <UModalDialogs.h>
#include <LMenuBar.h>
#include <LMenu.h>
#include "LPXmView.h"
#include "CTPxmResource.h"
#include "TPxmEditDialogBox.h"
#include <LPushButton.h>
#include "UTClut.h"
#include <UResourceMgr.h>
#include "UTFrmeResource.h"
#include "TFrmeEditDialogBox.h"
#include "LFrameView.h"
#include "UTLayoutResource.h"
#include "LLayoView.h"
#include "TLayoEditDialogBox.h"

// Constant declarations

const ResIDT	kMainWindowID		= 128;
const ResIDT	kTextColorListWindowID		= 129;

const ResIDT	kRequiredBrushWindowID = 131;
const ResIDT	kUserBrushWindowID = 132;
const ResIDT	kPxmWindowID = 134;
const ResIDT	kLayoWindowID = 138;
const ResIDT	kFrmeWindowID = 135;

const ResIDT	kUserBrushStrList 	= 1000;
const ResIDT	kUntitledStrList			= 300;
const ResIDT	kThemeMenuID			= 133;

const PaneIDT	kThemeInfoHorizontalSliderTickLeftEdit = 'hslt';
const PaneIDT	kThemeInfoVerticalSliderTickTopEdit = 'vslt';
const PaneIDT	kThemeInfoSliderHorizontalThumbWidthEdit = 'lhtw';
const PaneIDT	kThemeInfoSliderVerticalThumbHeightEdit = 'lvth';
const PaneIDT	kThemeInfoMenuSeparatorHeightEdit = 'msht';
const PaneIDT	kThemeInfoMenuBarHeightEdit = 'mbht';
const PaneIDT	kThemeInfoMenuTitleLeftEdit = 'mtlo';
const PaneIDT	kThemeInfoMenuTitleRightEdit = 'mtro';
const PaneIDT	kThemeInfoScrollHorizontalThumbWidthEdit = 'mhtw';
const PaneIDT	kThemeInfoScrollVerticalThumbHeightEdit = 'mvth';
const PaneIDT	kThemeInfoSmallScrollHorizontalThumbWidthEdit = 'shtw';
const PaneIDT	kThemeInfoSmallScrollVerticalThumbHeightEdit = 'svth';
const PaneIDT	kTextColorTableID = 'TCLT';
const PaneIDT	kBrushTableID = 'TBRT';

const PaneIDT	kIconMenuID = 'ipop';
const PaneIDT	kIcon48X48WellID = 'ic48';
const PaneIDT	kIcon32X32WellID = 'ic32';
const PaneIDT	kIcon16X16WellID = 'ic16';
const PaneIDT	kIcon16X12WellID = 'ic12';

const PaneIDT	kLayoViewID = 'LaVi';

const MessageT kEditTextColorMessage = 'ETCL';
const MessageT kEditRequiredBrushMessage = 'ERBT';
const MessageT kEditUserBrushMessage = 'EUBT';

const ResIDT	kPXMMenuID = 137;
const ResIDT	kLayoutMenuID = 135;

const ResIDT	kUserFramesMenuID = 170;
const ResIDT	kDeleteBrushAlertID = 129;



const ResIDT sRequiredFrames[] = {	kThemeFrmePrimaryGroupID, kThemeFrmeInactivePrimaryGroupID, 
									kThemeFrmeSceondaryGroupID, kThemeFrmeInactiveSecondaryGroupID,
									kThemeFrmeHorizontalSeparatorID, kThemeFrmeInactiveHorizontalSeparatorID,
									kThemeFrmeVerticalSeparatorID, kThemeFrmeInactiveVerticalSeparatorID,
									kThemeFrmeEditTextFrameID, kThemeFrmeInactiveEditTextFrameID,
									kThemeFrmeListBoxFrameID, kThemeFrmeInactiveListBoxFrameID,
									kThemeFrmeDialogContentEdgeID, kThemeFrmeInactiveDialogContentEdgeID,
									kThemeFrmeWindowHeaderID, kThemeFrmeInactiveWindowHeaderID,
									kThemeFrmeWindowPlacardID, kThemeFrmeInactiveWindowPlacardID,
									kThemeFrmePressedWindowPlacardID, kThemeFrmeFocusGenericRectID };
						
// ---------------------------------------------------------------------------
//	€ CThemeDoc								Constructor				  [public]
// ---------------------------------------------------------------------------
//	Construct a TextDoc associated with the specified file
//
//	If inFileSpec is nil, then create an empty, untitled document

CThemeDoc::CThemeDoc(
	LCommander*		inSuper,
	FSSpec*				inFileSpec)
	
	: LSingleResourceDoc(inSuper)
{
									// Create window for our document
	mWindow = LWindow::CreateWindow(kMainWindowID, this);
	ThrowIfNil_(mWindow);

	mCurrentIconIndex = 0;
	
	mThemeInfoHorizontalSliderTickLeftEdit = (LEditText*)mWindow->FindPaneByID(kThemeInfoHorizontalSliderTickLeftEdit);
	mThemeInfoVerticalSliderTickTopEdit = (LEditText*)mWindow->FindPaneByID(kThemeInfoVerticalSliderTickTopEdit);
	mThemeInfoSliderHorizontalThumbWidthEdit = (LEditText*)mWindow->FindPaneByID(kThemeInfoSliderHorizontalThumbWidthEdit);
	mThemeInfoSliderVerticalThumbHeightEdit = (LEditText*)mWindow->FindPaneByID(kThemeInfoSliderVerticalThumbHeightEdit);
	mThemeInfoMenuSeparatorHeightEdit = (LEditText*)mWindow->FindPaneByID(kThemeInfoMenuSeparatorHeightEdit);
	mThemeInfoMenuBarHeightEdit = (LEditText*)mWindow->FindPaneByID(kThemeInfoMenuBarHeightEdit);
	mThemeInfoMenuTitleLeftEdit = (LEditText*)mWindow->FindPaneByID(kThemeInfoMenuTitleLeftEdit);
	mThemeInfoMenuTitleRightEdit = (LEditText*)mWindow->FindPaneByID(kThemeInfoMenuTitleRightEdit);
	mThemeInfoScrollHorizontalThumbWidthEdit = (LEditText*)mWindow->FindPaneByID(kThemeInfoScrollHorizontalThumbWidthEdit);
	mThemeInfoScrollVerticalThumbHeightEdit = (LEditText*)mWindow->FindPaneByID(kThemeInfoScrollVerticalThumbHeightEdit);
	mThemeInfoSmallScrollHorizontalThumbWidthEdit = (LEditText*)mWindow->FindPaneByID(kThemeInfoSmallScrollHorizontalThumbWidthEdit);
	mThemeInfoSmallScrollVerticalThumbHeightEdit = (LEditText*)mWindow->FindPaneByID(kThemeInfoSmallScrollVerticalThumbHeightEdit);

	mThemeInfoHorizontalSliderTickLeftEdit->AddListener(this);
	mThemeInfoVerticalSliderTickTopEdit->AddListener(this);
	mThemeInfoSliderHorizontalThumbWidthEdit->AddListener(this);
	mThemeInfoSliderVerticalThumbHeightEdit->AddListener(this);
	mThemeInfoMenuSeparatorHeightEdit->AddListener(this);
	mThemeInfoMenuBarHeightEdit->AddListener(this);
	mThemeInfoMenuTitleLeftEdit->AddListener(this);
	mThemeInfoMenuTitleRightEdit->AddListener(this);
	mThemeInfoScrollHorizontalThumbWidthEdit->AddListener(this);
	mThemeInfoScrollVerticalThumbHeightEdit->AddListener(this);
	mThemeInfoSmallScrollHorizontalThumbWidthEdit->AddListener(this);
	mThemeInfoSmallScrollVerticalThumbHeightEdit->AddListener(this);

	mIconMenu =  (LPopupButton*)mWindow->FindPaneByID(kIconMenuID);
	mIcon48X48Well = (LImageWell*)mWindow->FindPaneByID(kIcon48X48WellID);
	mIcon32X32Well = (LImageWell*)mWindow->FindPaneByID(kIcon32X32WellID);
	mIcon16X16Well = (LImageWell*)mWindow->FindPaneByID(kIcon16X16WellID);
	mIcon16X12Well = (LImageWell*)mWindow->FindPaneByID(kIcon16X12WellID);
	
	mIconMenu->AddListener(this);
	mIcon48X48Well->AddListener(this);
	mIcon32X32Well->AddListener(this);
	mIcon16X16Well->AddListener(this);
	mIcon16X12Well->AddListener(this);
	
	mTextColorWindow = LWindow::CreateWindow(kTextColorListWindowID, this);
	ThrowIfNil_(mTextColorWindow);
	mTextClrListTable = (TTextClrListTable *)mTextColorWindow->FindPaneByID(kTextColorTableID);
	ThrowIfNil_(mTextClrListTable);
	
	mRequiredBrushWindow = LWindow::CreateWindow(kRequiredBrushWindowID, this);
	ThrowIfNil_(mRequiredBrushWindow);
	mRequiredBrushTable = (TBrushTable *)mRequiredBrushWindow->FindPaneByID(kBrushTableID);
	ThrowIfNil_(mRequiredBrushTable);
	
	mUserBrushWindow = LWindow::CreateWindow(kUserBrushWindowID, this);
	ThrowIfNil_(mUserBrushWindow);
	mUserBrushTable = (TBrushTable *)mUserBrushWindow->FindPaneByID(kBrushTableID);
	ThrowIfNil_(mUserBrushTable);
	
	mUserBrushWindow->Activate();
	
	LButton *theButton = (LButton*)mUserBrushWindow->FindPaneByID(cmd_EditUserNewBrush);
	theButton->AddListener(this);
	
	theButton =  (LButton*)mUserBrushWindow->FindPaneByID(cmd_EditUserDeleteBrush);
	theButton->AddListener(this);
	
	if (inFileSpec == nil) {
		NameNewDoc();				// Set name of untitled window
		
	} else {
		OpenFile(*inFileSpec);		// Display contents of file in window
	}
	
	mSavedTheme = NewCollection();
	GetTheme(mSavedTheme);
}


// ---------------------------------------------------------------------------
//	€ ~CThemeDoc								Destructor				  [public]
// ---------------------------------------------------------------------------

CThemeDoc::~CThemeDoc()
{	
	for(UInt32 i = 0; i < mAddedResources.GetCount(); i++)
	{
		UTThemeResource *theResource;
		ThrowIfNot_(mAddedResources.FetchItemAt(i+1,theResource));
		delete theResource;
	}
	
	try {
		TakeOffDuty();
	
		//Close the file here, and delete our stuff
	}
		
	catch (...) { }
	SetTheme(mSavedTheme);
	DisposeCollection(mSavedTheme);
	FSSpec theTestSpec;
	//Must kill of both states
	
	if(MakeTestSpec(theTestSpec) == noErr)
	{
		::FSpDelete(&theTestSpec);
	}
	if(MakeTestSpec(theTestSpec) == noErr)
	{
		::FSpDelete(&theTestSpec);
	}
}


// ---------------------------------------------------------------------------
//	€ IsModified													  [public]
// ---------------------------------------------------------------------------
//	Return whether the Document is has changed since the last save

Boolean
CThemeDoc::IsModified()
{
	return mIsModified;
}


// ---------------------------------------------------------------------------
//	€ DoAESave														  [public]
// ---------------------------------------------------------------------------
//	Save Document in the specified file with the specified file type
//
//	If file type is fileType_Default, use the normal file type for
//	this document

void
CThemeDoc::DoAESave(
	FSSpec&	inFileSpec,
	OSType	inFileType)
{
    FSSpec parDir;
    OSErr err = FSMakeFSSpec(inFileSpec.vRefNum, inFileSpec.parID,nil,&parDir);
    mResFSSpec = inFileSpec;
	
	OSType	fileType = 'thme';			// Find proper file type
	if (inFileType != fileType_Default) {
		fileType = inFileType;
	}
										// Make new file on disk
	FSpCreateResFile(&mResFSSpec,'THEM','thme',nil);
	ThrowIfResError_();
	DoSave();
	mWindow->SetDescriptor(mResFSSpec.name);
	mIsSpecified = true;				// Document now has a specified file*/
}


// ---------------------------------------------------------------------------
//	€ DoSave														  [public]
// ---------------------------------------------------------------------------
//	Save the entire Document to its associated File, which must already exist

void
CThemeDoc::DoSave()
{						
	UpdateTempFile();
	CloseResourceFork(true);
	OpenResourceFork(mResFSSpec);
	ReadyResourcesAndUI();
	mIsModified = false;
}

// ---------------------------------------------------------------------------
//	€ AskSaveAs														  [public]
// ---------------------------------------------------------------------------
//	Ask the user to save a Document and give it a name
//
//	Returns false if the user cancels the operation

Boolean
CThemeDoc::AskSaveACopyAs(
	FSSpec	&outFSSpec)
{
	Boolean		saveOK = false;

	PP_StandardDialogs::LFileDesignator*	designator =
								new PP_StandardDialogs::LFileDesignator;
								
	designator->SetFileType( GetFileType() );
	
	Str255	defaultName;
	if (designator->AskDesignateFile(GetDescriptor(defaultName))) {
		
		designator->GetFileSpec(outFSSpec);
		
		if (designator->IsReplacing() && UsesFileSpec(outFSSpec)) 
		{
			SysBeep(1);
			//Must be replaced with warning about saving file over original
			saveOK = false;
			
		} else 
		{
			
			if (designator->IsReplacing()) {
				ThrowIfOSErr_(::FSpDelete(&outFSSpec));
			}
			
			UpdateTempFile();
			FSSpec parentSpec = outFSSpec;
			parentSpec.name[0] = 0;
			OSErr theErr = FSpFileCopy(&mTempFSSpec,&parentSpec,outFSSpec.name,NULL,0,true);
			saveOK = theErr == noErr;
			ReadyResourcesAndUI();
		}
	}
	
	return saveOK;
}


void
CThemeDoc::UpdateTempFile()
{
	for(UInt32 i = 0; i < mAddedResources.GetCount(); i++)
	{
		UTThemeResource *theResource;
		ThrowIfNot_(mAddedResources.FetchItemAt(i+1,theResource));
		if(theResource->isAddToTdat())
		{
			TdatEntry e(theResource->GetResourceSpec());
			mTdatResource.AddTdatEntry(e);
		}
		theResource->Write();
	}
	
	for(UInt32 i = 0; i < mTdatResource.Count(); i++)
	{
		TdatEntry theTdat;
		mTdatResource.GetTdatEntry(i,theTdat);
		if(theTdat.mResType == 'ppat')
		{
			Boolean foundPPat = false;
			for(UInt32 j = 0; j < mRequiredBrushColorResource.Count() && !foundPPat; j++)
			{
				PlutEntry thePlut;
				mRequiredBrushColorResource.GetPlutEntry(j,thePlut);
				if(thePlut.brushPPAT.resType == 'ppat' && thePlut.brushPPAT.resID == theTdat.mResID1)
				{
					foundPPat = true;
				}
			}
			for(UInt32 j = 0; j < mUserBrushResource.Count() && !foundPPat; j++)
			{
				PlutEntry thePlut;
				mUserBrushResource.GetPlutEntry(j,thePlut);
				if(thePlut.brushPPAT.resType == 'ppat' && thePlut.brushPPAT.resID == theTdat.mResID1)
				{
					foundPPat = true;
				}
			}
			if(!foundPPat)
			{
				StCurResFile curFile;
				FullResourceSpec theSpec = mTdatResource.GetResourceSpec();
				UseResFile(theSpec.fileID);
				Handle theResource = Get1Resource(theTdat.mResType,theTdat.mResID1);
				RemoveResource(theResource);
				UpdateResFile(theSpec.fileID);
				mTdatResource.DeleteTdatEntry(i);
				i--;
			}
		}
	}
	
	mThemePreferences.SetShowTextColorWindow(mTextColorWindow->IsVisible());
	mThemePreferences.SetShowRequiredBrushWindow(mRequiredBrushWindow->IsVisible());
	mThemePreferences.SetShowUserBrushWindow(mUserBrushWindow->IsVisible());
	mThemePreferences.SetShowThemeSettingsWindow(mWindow->IsVisible());
	
	Rect theBounds;
	
	mTextColorWindow->GetGlobalBounds(theBounds);
	mThemePreferences.SetTextColorWindowPos(topLeft(theBounds));
	mRequiredBrushWindow->GetGlobalBounds(theBounds);
	mThemePreferences.SetRequiredBrushWindowPos(topLeft(theBounds));
	mUserBrushWindow->GetGlobalBounds(theBounds);
	mThemePreferences.SetUserBrushWindowPos(topLeft(theBounds));
	mWindow->GetGlobalBounds(theBounds);
	mThemePreferences.SetThemeSettingsWindowPos(topLeft(theBounds));
	
	mThemePreferences.Write();
	mTdatResource.Write();
	mTextColorResource.Write();
	mRequiredBrushColorResource.Write();
	mUserBrushResource.Write();
	mTinfResource.Write();
	
	mThemePreferences.Dispose();
	mTdatResource.Dispose();
	mTextColorResource.Dispose();
	mRequiredBrushColorResource.Dispose();
	mUserBrushResource.Dispose();
	mTinfResource.Dispose();
	mTicListResource.Dispose();
	
	LSingleResourceDoc::UpdateTempFile();
}

// ---------------------------------------------------------------------------
//	€ DoRevert														  [public]
// ---------------------------------------------------------------------------
//	Revert the Document to the last saved version on disk

void
CThemeDoc::DoRevert()
{
   CloseResourceFork(false);
   OpenResourceFork(mResFSSpec);
	ReadyResourcesAndUI();
	mIsModified = false;
}


// ---------------------------------------------------------------------------
//	€ AskSaveAs														  [public]
// ---------------------------------------------------------------------------
//	Ask the user to save a Document and give it a name
//
//	Returns false if the user cancels the operation

Boolean
CThemeDoc::AskSaveAs(
	FSSpec	&outFSSpec,
	Boolean	inRecordIt)
{
	Boolean		saveOK = false;

	PP_StandardDialogs::LFileDesignator*	designator =
								new PP_StandardDialogs::LFileDesignator;
								
	designator->SetFileType( GetFileType() );
	
	Str255	defaultName;
	if (designator->AskDesignateFile(GetDescriptor(defaultName))) {
		
		designator->GetFileSpec(outFSSpec);
		
		if (designator->IsReplacing() && UsesFileSpec(outFSSpec)) {
									// User chose to replace the file with
									//   one of the same name. 
									
			if (inRecordIt) {		// This is the same as a save
				SendSelfAE(kAECoreSuite, kAESave, ExecuteAE_No);
			}
			
				// Same document is still open, so we don't need to complete
				// the save. However, user may have selected different
				// translation options, so we need to delete the original
				// designator and store the new one.
			
			/*delete mFileDesignator;
			mFileDesignator = designator;*/
				
			DoSave();				// Save data to disk
			saveOK = true;
			
		} else {
		
			if (inRecordIt) {		// Recording for AppleScript
				SendAESaveAs(outFSSpec, GetFileType(), ExecuteAE_No);
			}
			
			if (designator->IsReplacing()) {
				ThrowIfOSErr_(::FSpDelete(&outFSSpec));
			}
			
									// Save data to new file. This also
									//    closes the original file
			DoAESave(outFSSpec, fileType_Default);
			
			/*if (mFileDesignator != nil) {
									// Complete save of original designator
				mFileDesignator->CompleteSave();
				delete mFileDesignator;
			}
			
									// Store new designator so we can
									//   complete save when we close
									//   the document
			mFileDesignator = designator;*/
			
			saveOK = true;
		}
	}
	
	return saveOK;
}


// ---------------------------------------------------------------------------
//	€ GetFileType													  [public]
// ---------------------------------------------------------------------------

OSType
CThemeDoc::GetFileType() const
{
	return 'thme';					// We use Theme files
}


// ---------------------------------------------------------------------------
//	€ FindCommandStatus												  [public]
// ---------------------------------------------------------------------------

void
CThemeDoc::FindCommandStatus(
	CommandT	inCommand,
	Boolean&		outEnabled,
	Boolean&		outUsesMark,
	UInt16&		outMark,
	Str255			outName)
{
			
	SInt16 theID = HiWord(-inCommand);
	if(theID == kPXMMenuID)
	{
		outEnabled = true;
		outUsesMark = false;
	}
	else if(inCommand >= cmd_LayoutBase && inCommand <= cmd_LayoutGenericImageWell)
	{
		outEnabled =true;
		outUsesMark = false;
	}
	else if((inCommand >= 13999 && inCommand <= 14060) || (theID == kUserFramesMenuID))
	{
		outEnabled =true;
		outUsesMark = false;
	}
	else
	{
		switch(inCommand)
		{
			case cmd_Open:
				outEnabled = false;
			break;
			
			case cmd_ShowThemeSettings:
				outEnabled = true;
				outUsesMark = true;
				if(mWindow->IsVisible())
				{
					outMark = checkMark;
				}
				else
				{
					outMark = 0;
				}
			break;
			
			case cmd_ShowUserBrushes:
				outEnabled = true;
				outUsesMark = true;
				if(mUserBrushWindow->IsVisible())
				{
					outMark = checkMark;
				}
				else
				{
					outMark = 0;
				}
			break;
			
			case cmd_ShowReqdBrushes:
				outEnabled = true;
				outUsesMark = true;
				if(mRequiredBrushWindow->IsVisible())
				{
					outMark = checkMark;
				}
				else
				{
					outMark = 0;
				}
			break;
			
			case cmd_ShowTextColors:
				outEnabled = true;
				outUsesMark = true;
				if(mTextColorWindow->IsVisible())
				{
					outMark = checkMark;
				}
				else
				{
					outMark = 0;
				}
			break;
			
			case cmd_EditTestTheme:
				outEnabled = true;
				outUsesMark = false;
			break;
			
			default:

				LSingleResourceDoc::FindCommandStatus( inCommand,
					outEnabled, outUsesMark, outMark, outName );
			break;
		}
	}			
}


Boolean
CThemeDoc::ObeyCommand(
	CommandT	inCommand,
	void			*ioParam )
{
	Boolean		cmdHandled = true;

	SInt16 theID = HiWord(-inCommand);
	if(theID == kPXMMenuID)
	{
		SInt16 theCmd = LoWord(-inCommand);
		LMenu* theMenu = LMenuBar::GetCurrentMenuBar()->FetchMenu(kPXMMenuID);
		MenuHandle mh = theMenu->GetMacMenuH();
		LStr255 theName;
		GetMenuItemText(mh,theCmd,theName);
		UseResFile(GetResFileRefNum());
		Handle thePXMHandle = GetNamedResource('pxm#',theName);
		SignalIf_(thePXMHandle == NULL);
		
		TPxmEditDialogBox* theEditDialog = (TPxmEditDialogBox*)LWindow::CreateWindow(kPxmWindowID, this);
		
		ThrowIfNil_(theEditDialog);
		
		ResID theID;
		OSType theType;
		GetResInfo(thePXMHandle,&theID,&theType,theName);
		
		FullResourceSpec thePxmSpec = {theID,GetResFileRefNum(),theType};
		theEditDialog->SetThemeDocument(this);
		theEditDialog->SetPxmResource(thePxmSpec);
		theEditDialog->Show();
	}
	else if ((inCommand >= 14000 && inCommand <= 14060) || (theID == kUserFramesMenuID))
	{

		ResID theFrmeID;
		
		if(theID == kUserFramesMenuID)
		{
			SInt16 theCmd = LoWord(-inCommand);
			LMenu* theMenu = LMenuBar::GetCurrentMenuBar()->FetchMenu(kUserFramesMenuID);
			MenuHandle mh = theMenu->GetMacMenuH();
			LStr255 theName;
			GetMenuItemText(mh,theCmd,theName);
			UseResFile(GetResFileRefNum());
			LStr255 truncateName = theName.Remove(theName.Length(),1); //Get rid of the Š
			Handle theFrmeHandle = GetNamedResource('frme',truncateName);
			SignalIf_(theFrmeHandle == NULL);
			OSType theType;
			GetResInfo(theFrmeHandle,&theFrmeID,&theType,theName);
		}
		else
		{
			theFrmeID = inCommand - 14000 + 500;
		}
		
		TFrmeEditDialogBox* theEditDialog = (TFrmeEditDialogBox*)LWindow::CreateWindow(kFrmeWindowID, this);
		
		ThrowIfNil_(theEditDialog);
		theEditDialog->SetThemeDocument(this);
		FullResourceSpec theSpec = {theFrmeID,GetResFileRefNum(),'frme'};
		theEditDialog->SetFrmeResource(theSpec);
		
		
		theEditDialog->Show();
	}
	else if (inCommand >= cmd_LayoutBase && inCommand <= cmd_LayoutGenericImageWell)
	{
		TLayoEditDialogBox *theLayoEditWindow = (TLayoEditDialogBox*)LWindow::CreateWindow(kLayoWindowID,this);
		ThrowIfNil_(theLayoEditWindow);
		
		ResIDT theMenuID;
		MenuHandle theHandle;
		SInt16 theItem;
		
		LMenuBar::GetCurrentMenuBar()->FindMenuItem(inCommand,theMenuID,theHandle,theItem);
		LStr255 theName;
		GetMenuItemText(theHandle,theItem,theName);
		theLayoEditWindow->SetDescriptor(theName);
		FullResourceSpec theSpec = {inCommand - cmd_LayoutBase,GetResFileRefNum(),'layo'};
		theLayoEditWindow->SetLayoResource(theSpec);
		theLayoEditWindow->SetThemeDocument(this);
	}
	else
	{
		switch (inCommand) 
		{
			case cmd_ShowThemeSettings:
				mWindow->IsVisible() ? mWindow->Hide() : mWindow->Show();
			break;
			
			case cmd_ShowUserBrushes:
				mUserBrushWindow->IsVisible() ? mUserBrushWindow->Hide() : mUserBrushWindow->Show();
			break;
			
			case cmd_ShowReqdBrushes:
				mRequiredBrushWindow->IsVisible() ? mRequiredBrushWindow->Hide() : mRequiredBrushWindow->Show();
			break;	
			
			case cmd_ShowTextColors:
				mTextColorWindow->IsVisible() ? mTextColorWindow->Hide() : mTextColorWindow->Show();
			break;
			
			case cmd_EditTestTheme:
			{
				FSSpec theParentSpec;
				FSSpec theFileSpec;
				
				UpdateTempFile();
				OSStatus theErr = MakeTestSpec(theFileSpec);
				theParentSpec = theFileSpec;
				theParentSpec.name[0] = 0;
				theErr = ::FSpDelete(&theFileSpec);
				theErr = FSpFileCopy(&mTempFSSpec,&theParentSpec,theFileSpec.name,NULL,0,true);
				TryTheme(theFileSpec);
				ReadyResourcesAndUI();
			}
			break;
						
			default: 
			{
				cmdHandled = LSingleResourceDoc::ObeyCommand(inCommand,ioParam);
				break;
			}
		}
	}
	return cmdHandled;
}

OSStatus	CThemeDoc::MakeTestSpec(FSSpec &outSpec)
{
	OSStatus theErr = FindFolder(kOnSystemDisk,kThemesFolderType,false,&outSpec.vRefNum, &outSpec.parID);
	if(theErr == noErr)
	{
		LStr255 theName(307,1);
		if(mTestSpecFlipFlop)
		{
			theName.Append(1L);
			mTestSpecFlipFlop = !mTestSpecFlipFlop;
		}
		LString::CopyPStr(theName,outSpec.name);
	}
	return theErr;
}

// ---------------------------------------------------------------------------
//	€ NameNewDoc
// ---------------------------------------------------------------------------
//	Name a new, untitled document window
//
//	Untitled windows start with "untitled", then "untitled 1",
//	"untitled 2", etc. Old numbers are reused, so there won't be
//	gaps in the numbering.
//
//	This routine uses a STR# resource to store the "untitled" string,
//	which can be localized to different languages. The first string
//	is "untitled" and the second is "untitled " (trailing space),
//	which is used when appending a number to the name.

void
CThemeDoc::NameNewDoc()
{
								// Start with the default name ("untitled")
	LStr255		name(kUntitledStrList, 1);
	
		// Check if an existing window has this name. If so,
		// append a count ("untitled 1"). Keep incrementing the
		// count until we find a unique name.
		
	long	num = 0;
	while (UWindows::FindNamedWindow(name) != nil) {
		name.Assign(kUntitledStrList, 2);	// "untitled " (note trailing space)

		name += (++num);				// Increment and append count to name
	}		
	
	mWindow->SetDescriptor(name);		// Finally, set window title
}


// ---------------------------------------------------------------------------
//		€ OpenFile
// ---------------------------------------------------------------------------
//	Open a new document for the specified File

void
CThemeDoc::OpenFile(
	const FSSpec&	inFileSpec)
{	
	OpenResourceFork(inFileSpec);
	
	ReadyResourcesAndUI();
	mWindow->SetDescriptor(mResFSSpec.name);
		
	mIsSpecified = true;
}


	
void	CThemeDoc::ListenToMessage(
							MessageT		inMessage,
							void*			ioParam)
{
	SInt32 newColor = *((SInt32*)ioParam);
	PlutEntry	thePlut;
	StCurResFile theFile(GetResFileRefNum());
	
	switch(inMessage)
	{		
		case kThemeInfoHorizontalSliderTickLeftEdit:
		{
			mTinfResource.SetHorizontalSliderTickLeftOffset(((LEditText*)ioParam)->GetValue());
			mIsModified = true;
		}
		break;

		case kThemeInfoVerticalSliderTickTopEdit:
		{
			mTinfResource.SetVerticalSliderTickTopOffset(((LEditText*)ioParam)->GetValue());
			mIsModified = true;
		}
		break;

		case kThemeInfoSliderHorizontalThumbWidthEdit:
		{
			mTinfResource.SetSliderThumbWidth(((LEditText*)ioParam)->GetValue());
			mIsModified = true;
		}
		break;

		case kThemeInfoSliderVerticalThumbHeightEdit:
		{
			mTinfResource.SetSliderThumbHeight(((LEditText*)ioParam)->GetValue());
			mIsModified = true;
		}
		break;

		case kThemeInfoMenuSeparatorHeightEdit:
		{
			mTinfResource.SetMenuSeperatorHeight(((LEditText*)ioParam)->GetValue());
			mIsModified = true;
		}
		break;

		case kThemeInfoMenuBarHeightEdit:
		{
			mTinfResource.SetMenuBarHeight(((LEditText*)ioParam)->GetValue());
			mIsModified = true;
		}
		break;

		case kThemeInfoMenuTitleLeftEdit:
		{
			mTinfResource.SetMenuTitleLeftOffset(((LEditText*)ioParam)->GetValue());
			mIsModified = true;
		}
		break;

		case kThemeInfoMenuTitleRightEdit:
		{
			mTinfResource.SetMenuTitleRightOffset(((LEditText*)ioParam)->GetValue());
			mIsModified = true;
		}
		break;

		case kThemeInfoScrollHorizontalThumbWidthEdit:
		{
			mTinfResource.SetHorizontalScrollBarThumbWidth(((LEditText*)ioParam)->GetValue());
			mIsModified = true;
		}
		break;

		case kThemeInfoScrollVerticalThumbHeightEdit:
		{
			mTinfResource.SetVerticalScrollBarThumbHeight(((LEditText*)ioParam)->GetValue());
			mIsModified = true;
		}
		break;

		case kThemeInfoSmallScrollHorizontalThumbWidthEdit:
		{
			mTinfResource.SetSmallHorizontalScrollBarThumbWidth(((LEditText*)ioParam)->GetValue());
			mIsModified = true;
		}
		break;

		case kThemeInfoSmallScrollVerticalThumbHeightEdit:
		{
			mTinfResource.SetSmallVerticalScrollBarThumbHeight(((LEditText*)ioParam)->GetValue());
			mIsModified = true;
		}
		break;

		case kIconMenuID:
		{
			ControlButtonContentInfo buttonInfo;
			TicEntry ticEntry;
			IconSuiteRef theSuite; 
			mCurrentIconIndex = newColor - 1;
			//When we reopen a document, we remove all items from the menu,
			//this will get us a message of 0, and an mCurrentIconIndex of -1.
			//-1 doesn't work for us ;-)
			
			if(mCurrentIconIndex >=0)
			{
				mTicListResource.GetTicEntry(mCurrentIconIndex,ticEntry);
				IconFamilyHandle theFamily = (IconFamilyHandle)GetResource('icns',ticEntry.icnsID);
				ThrowIfOSErr_(IconFamilyToIconSuite(theFamily,svAllAvailableData,&theSuite));
		
				mIcon48X48Well->GetContentInfo(buttonInfo);
				if(buttonInfo.u.iconSuite != NULL)
				{
					ThrowIfOSErr_(DisposeIconSuite(buttonInfo.u.iconSuite,true));
				}
				buttonInfo.u.iconSuite = (Handle)theSuite;
				mIcon48X48Well->SetContentInfo(buttonInfo);
				mIcon48X48Well->Refresh();
				
				mIcon32X32Well->GetContentInfo(buttonInfo);
				buttonInfo.u.iconSuite = (Handle)theSuite;
				mIcon32X32Well->SetContentInfo(buttonInfo);
				mIcon32X32Well->Refresh();
				mIcon16X16Well->GetContentInfo(buttonInfo);
				buttonInfo.u.iconSuite = (Handle)theSuite;
				mIcon16X16Well->SetContentInfo(buttonInfo);
				mIcon16X16Well->Refresh();
				mIcon16X12Well->GetContentInfo(buttonInfo);
				buttonInfo.u.iconSuite = (Handle)theSuite;
				mIcon16X12Well->SetContentInfo(buttonInfo);
				mIcon16X12Well->Refresh();
			}
		}
		break;
		
		case kIcon48X48WellID:
		case kIcon32X32WellID:
		case kIcon16X16WellID:
		case kIcon16X12WellID:
		{
			TicEntry ticEntry;
			IconSuiteRef theRef = (IconSuiteRef)ioParam;
			mTicListResource.GetTicEntry(mCurrentIconIndex,ticEntry);
			Handle theOldFamily = GetResource('icns',ticEntry.icnsID);
			if(theOldFamily != NULL)
			{
				IconFamilyHandle theFamily;
				ThrowIfOSErr_(IconSuiteToIconFamily(theRef,svAllAvailableData,&theFamily));
				SetHandleSize(theOldFamily,GetHandleSize((Handle)theFamily));
				BlockMove((Ptr)*theFamily,(Ptr)*theOldFamily,GetHandleSize((Handle)theFamily));
				ChangedResource(theOldFamily);
				WriteResource(theOldFamily);
				UInt32 newIndex = mCurrentIconIndex + 1;
				ListenToMessage(kIconMenuID,&newIndex);
			}
				
		}
		break;
		case kEditTextColorMessage:
		{
			TextColorChangeRecord *theRecord = (TextColorChangeRecord*) ioParam;
			
			mTextColorResource.SetColor(theRecord->aCell.row - 1,theRecord->aColor);
			theRecord->aTable->RefreshCell(theRecord->aCell);
			mIsModified = true;
		}
		break;
		
		case kEditRequiredBrushMessage:
		{
			PlutChangeRecord *theRecord = (PlutChangeRecord *)ioParam;
			
			if(theRecord->aPPAT != NULL)
			{
				theRecord->aPlut = CreateNewPlutWithPPATAndColor(theRecord->aPPAT,theRecord->aPlut.brushColor);
			}
			mRequiredBrushColorResource.SetPlutEntry(theRecord->aCell.row - 1,theRecord->aPlut);
			theRecord->aTable->RefreshCell(theRecord->aCell);
			mIsModified = true;
		}
		break;
		
		case kEditUserBrushMessage:
		{
			PlutChangeRecord *theRecord = (PlutChangeRecord *)ioParam;
			
			if(theRecord->aPPAT != NULL)
			{
				theRecord->aPlut = CreateNewPlutWithPPATAndColor(theRecord->aPPAT,theRecord->aPlut.brushColor);
			}
			mUserBrushResource.SetPlutEntry(theRecord->aCell.row - 1,theRecord->aPlut);
			theRecord->aTable->RefreshCell(theRecord->aCell);
			mIsModified = true;
		}
		break;
		
		case cmd_EditUserNewBrush:
		{
			PlutEntry theEntry;
			
			mUserBrushResource.AddPlutEntry(theEntry);
			mUserBrushTable->InsertRows(1,32000,NULL,0,false);
			STableCell theCell(mUserBrushResource.Count(),1);
			mUserBrushTable->SelectCell(theCell);
			mUserBrushTable->ScrollCellIntoFrame(theCell);
			mUserBrushResource.Dirty();
			mIsModified = true;
		}
		break;
		
		case cmd_EditUserDeleteBrush:
		{
			STableCell theCell = mUserBrushTable->GetFirstSelectedCell();
			if(theCell.row != 0 && theCell.col != 0)
			{
				if(StopAlert(kDeleteBrushAlertID,NULL) == 1)
				{
					mUserBrushTable->RemoveRows(1,theCell.row,true);
					mUserBrushResource.DeletePlutEntry(theCell.row - 1);
					mUserBrushResource.Dirty();
					mIsModified = true;
				}
			}
			else
			{
				SysBeep(1);
			}
		}
		break;
		
		case cmd_SelectUserBrushMessage:
		{
			StopListening();
			mRequiredBrushTable->UnselectAllCells();
			StartListening();
		}
		break;
		
		case cmd_SelectRequiredBrushMessage:
		{
			StopListening();
			mUserBrushTable->UnselectAllCells();
			StartListening();
		}
		break;
		
	}
}

void				CThemeDoc::ReadyResourcesAndUI()
{
	mTextColorResource.Init(GetResFileRefNum());
	mTextClrListTable->SetTextClrList(&mTextColorResource);
	mTextClrListTable->AddListener(this);
	
	mRequiredBrushColorResource.Init(GetResFileRefNum());
	mRequiredBrushTable->SetPlutResource(&mRequiredBrushColorResource);
	mRequiredBrushTable->AddListener(this);
	
	mUserBrushResource.Init(kUserPlutBrushResourceID,GetResFileRefNum());
	mUserBrushTable->SetPlutResource(&mUserBrushResource);
	mUserBrushTable->AddListener(this);

	mTinfResource.Init(GetResFileRefNum());
	mTicListResource.Init(kThemeTicResourceID,GetResFileRefNum());
	mTdatResource.Init(kThemeTdatResourceID,GetResFileRefNum());
	
	mThemePreferences.Init(kThemePreferencesID,GetResFileRefNum());
	Point thePoint = mThemePreferences.GetThemeSettingsWindowPos();
	mWindow->MoveWindowTo(thePoint.h,thePoint.v);
	thePoint = mThemePreferences.GetTextColorWindowPos();
	mTextColorWindow->MoveWindowTo(thePoint.h,thePoint.v);
	thePoint = mThemePreferences.GetRequiredBrushWindowPos();
	mRequiredBrushWindow->MoveWindowTo(thePoint.h,thePoint.v);
	thePoint = mThemePreferences.GetUserBrushWindowPos();
	mUserBrushWindow->MoveWindowTo(thePoint.h,thePoint.v);
	if(mThemePreferences.GetShowThemeSettingsWindow())
	{
		mWindow->Show();
	}
	else
	{
		mWindow->Hide();
	}
	
	if(mThemePreferences.GetShowTextColorWindow())
	{
		mTextColorWindow->Show();
	}
	else
	{
		mTextColorWindow->Hide();
	}
	if(mThemePreferences.GetShowRequiredBrushWindow())
	{
		mRequiredBrushWindow->Show();
	}
	else
	{
		mRequiredBrushWindow->Hide();
	}
	if(mThemePreferences.GetShowUserBrushWindow())
	{
		mUserBrushWindow->Show();
	}
	else
	{
		mUserBrushWindow->Hide();
	}
	
	//move all our Windows about
	
	mThemeInfoHorizontalSliderTickLeftEdit->SetValue(mTinfResource.GetHorizontalSliderTickLeftOffset());
	mThemeInfoVerticalSliderTickTopEdit->SetValue(mTinfResource.GetVerticalSliderTickTopOffset());
	mThemeInfoSliderHorizontalThumbWidthEdit->SetValue(mTinfResource.GetSliderThumbWidth());
	mThemeInfoSliderVerticalThumbHeightEdit->SetValue(mTinfResource.GetSliderThumbHeight());
	mThemeInfoMenuSeparatorHeightEdit->SetValue(mTinfResource.GetMenuSeperatorHeight());
	mThemeInfoMenuBarHeightEdit->SetValue(mTinfResource.GetMenuBarHeight());
	mThemeInfoMenuTitleLeftEdit->SetValue(mTinfResource.GetMenuTitleLeftOffset());
	mThemeInfoMenuTitleRightEdit->SetValue(mTinfResource.GetMenuTitleRightOffset());
	mThemeInfoScrollHorizontalThumbWidthEdit->SetValue(mTinfResource.GetHorizontalScrollBarThumbWidth());
	mThemeInfoScrollVerticalThumbHeightEdit->SetValue(mTinfResource.GetVerticalScrollBarThumbHeight());
	mThemeInfoSmallScrollHorizontalThumbWidthEdit->SetValue(mTinfResource.GetSmallHorizontalScrollBarThumbWidth());
	mThemeInfoSmallScrollVerticalThumbHeightEdit->SetValue(mTinfResource.GetSmallVerticalScrollBarThumbHeight());

	mIconMenu->DeleteAllMenuItems();
	for(UInt32 i=0; i<mTicListResource.Count(); i++)
	{
		TicEntry e;
		LStr255 name;
		mTicListResource.GetTicEntry(i,e);
		mTicListResource.FindEntryName(e.iconSignature,name);
		mIconMenu->AppendMenu(name);
	}
	
	LMenu* theMenu = LMenuBar::GetCurrentMenuBar()->FetchMenu(kPXMMenuID);
	MenuHandle theMenuHandle = theMenu->GetMacMenuH();
	while(CountMItems(theMenuHandle) > 0)
	{
		DeleteMenuItem(theMenuHandle,1);
	}
	InsertResMenu(theMenuHandle,'pxm#',0);
	
	theMenu = LMenuBar::GetCurrentMenuBar()->FetchMenu(kUserFramesMenuID);
	theMenuHandle = theMenu->GetMacMenuH();
	while(CountMItems(theMenuHandle) > 0)
	{
		DeleteMenuItem(theMenuHandle,1);
	}
	InsertResMenu(theMenuHandle,'frme',0);
	
	
	for(UInt32 i = 1; i <= CountMItems(theMenuHandle); i++)
	{
		LStr255 theName;
		GetMenuItemText(theMenuHandle,i,theName);
		UseResFile(GetResFileRefNum());
		Handle theFrmeHandle = GetNamedResource('frme',theName);
		ResID theNumber;
		OSType theType;
		GetResInfo(theFrmeHandle,&theNumber,&theType,theName);
		UInt32 j;
		for(j = 0; j < sizeof(sRequiredFrames) / sizeof(ResID); j++)
		{
			if(sRequiredFrames[j] == theNumber)
			{
				DeleteMenuItem(theMenuHandle,i);
				i--;
				break;
			}
		}
		if(j == sizeof(sRequiredFrames) / sizeof(ResID))
		{
			theName += 'Š';
			SetMenuItemText(theMenuHandle,i,theName);
			EnableMenuItem(theMenuHandle,i);
		}
	}
}

PlutEntry			CThemeDoc::CreateNewPlutWithPPATAndColor(Handle inPPAT, const RGBColor &inColor)
{
	PlutEntry theEntry;
	UTThemeResource *newPPat = new UTThemeResource;
	ResIDT newID = UniqueID('ppat');
	newPPat->Init(true,'ppat',newID,GetResFileRefNum());
	
	UInt32 theSize = GetHandleSize(inPPAT);
	SetHandleSize(newPPat->Get(),theSize);
	ThrowIfMemError_();
	HLock(inPPAT);
	HLock(newPPat->Get());
	BlockMove(*(inPPAT),*(newPPat->Get()),theSize);
	HUnlock(inPPAT);
	HUnlock(newPPat->Get());
	
	ThrowIfMemError_();
	newPPat->Dirty();
	
	theEntry.brushPPAT = newPPat->GetResourceSpec();
	theEntry.brushColor = inColor;
	mAddedResources.AddItem(newPPat);
	
	PixPatHandle thePixPat = theEntry.GetPlutPixPat();
	ThrowIfNil_(thePixPat);
	DisposePixPat(thePixPat);
	return theEntry;
}

Boolean
CThemeDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mTextColorWindow || inSub == mRequiredBrushWindow || inSub == mUserBrushWindow) 
	{
		((LWindow*)inSub)->Hide();
		return false;

	}
	else
	{
		return LSingleResourceDoc::AllowSubRemoval(inSub);
	}
}

PlutDragRecord CThemeDoc::GetPlutDragRec(PlutEntryIndex inIndex)
{
	PlutDragRecord theRec;
	if(inIndex < 0)
	{
		inIndex *= -1;
		mUserBrushResource.GetPlutEntry(inIndex - 1, theRec.aPlut);
		theRec.aTable = mUserBrushTable;
	}
	else
	{
		mRequiredBrushColorResource.GetPlutEntry(inIndex - 1,theRec.aPlut);
		theRec.aTable = mRequiredBrushTable;
	}
	theRec.anIndex = inIndex - 1;
	return theRec;
}

PlutDragRecord	CThemeDoc::GetPlutDragRec(SInt32 inIndex, bool inIsRequired)
{
	inIndex += 1;
	if(!inIsRequired)
	{
		inIndex *= -1;
	}
	return GetPlutDragRec(inIndex);
}

Boolean 		CThemeDoc::GetCurrentSelectedPlutDragRec(PlutDragRecord &outRec)
{
	STableCell theCell = mRequiredBrushTable->GetFirstSelectedCell();
	SInt32 index = theCell.row - 1;
	if(index != -1)
	{
		outRec.anIndex = index;
		outRec.aTable = mRequiredBrushTable;
		mRequiredBrushColorResource.GetPlutEntry(index,outRec.aPlut);
		
	}
	else
	{
		theCell = mUserBrushTable->GetFirstSelectedCell();
		index = theCell.row - 1;
		if(index != -1)
		{
			mUserBrushResource.GetPlutEntry(index, outRec.aPlut);
			outRec.aTable = mUserBrushTable;
			outRec.anIndex = index;
		}
	}
	return index != -1;
}

void	CThemeDoc::SetCurrentSelectedPlut(PlutEntryIndex inIndex)
{
	STableCell theCell;
	theCell.col = 1;
	if(inIndex < 0)
	{
		inIndex *= -1;
		theCell.row = inIndex;
		mUserBrushTable->ScrollCellIntoFrame(theCell);
		mUserBrushTable->SelectCell(theCell);
	}
	else
	{
		theCell.row = inIndex;
		mRequiredBrushTable->ScrollCellIntoFrame(theCell);
		mRequiredBrushTable->SelectCell(theCell);
	}
}	

OSStatus	CThemeDoc::TryTheme(FSSpec &inThemeSpec)
{
	Collection theTheme = NewCollection();
	OSStatus theStatus = GetTheme(theTheme);
	if(theStatus == noErr)
	{
		LStr255 theThemeName(inThemeSpec.name);
		theStatus = AddCollectionItem(theTheme,kThemeAppearanceFileNameTag,0,sizeof(Str255),theThemeName);
		if(theStatus == noErr)
		{
			theStatus = SetTheme(theTheme);
			DisposeCollection(theTheme);
		}
	}
	return theStatus;
}
