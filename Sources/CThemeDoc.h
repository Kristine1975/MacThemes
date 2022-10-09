// ===========================================================================
//	CThemeDoc.h				  ©1999 Allegro Theme Project All rights reserved.
// ===========================================================================
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


#ifndef _H_CThemeDoc
#define _H_CThemeDoc
#pragma once

#include "LSingleResourceDoc.h"
#include <UStandardDialogs.h>
#include "LListener.h"


#include "UTTextClrListResource.h"
#include "UTPlutBrushResource.h"
#include "UTThemeTinfResource.h"
#include "UTTicListResource.h"
#include "UTTdatResource.h"
#include "UTTMDAResource.h"
#include <TArray.h>
#include "TBrushTable.h"

class LPopupButton;
class LGAColorSwatchControl;
class LEditText;
class TGAPPATEditControl;
class LImageWell;
class TTextClrListTable;

class	CThemeDoc : public LSingleResourceDoc, LListener {
public:
						CThemeDoc(
								LCommander*		inSuper,
								FSSpec*				inFileSpec);
								
						~CThemeDoc();
						
	virtual Boolean		IsModified();
	virtual Boolean		AllowSubRemoval(
								LCommander*		inSub);
	virtual void		DoAESave(
								FSSpec&				inFileSpec,
								OSType				inFileType);
								
	virtual void		DoSave();
	virtual void		DoRevert();
	
	virtual Boolean		AskSaveAs(
								FSSpec&				outFSSpec,
								Boolean				inRecordIt);
	virtual Boolean		AskSaveACopyAs(FSSpec	&outFSSpec);						
	virtual OSType		GetFileType() const;

	virtual Boolean		ObeyCommand(
								CommandT		inCommand,
								void*				ioParam = nil);
								
	virtual void		FindCommandStatus(
								CommandT		inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&			outMark,
								Str255				outName);					
	virtual void	ListenToMessage(
							MessageT		inMessage,
							void*			ioParam);
	virtual void		UpdateTempFile();						
	PlutDragRecord	GetPlutDragRec(PlutEntryIndex inIndex);
	PlutDragRecord	GetPlutDragRec(SInt32 inIndex, bool inIsRequired);
	Boolean 		GetCurrentSelectedPlutDragRec(PlutDragRecord &outRec);
	void			SetCurrentSelectedPlut(PlutEntryIndex inIndex);
protected:
	void				NameNewDoc();
	
	void				OpenFile(
								const FSSpec&		inFileSpec);
	void				ReadyResourcesAndUI();
	
	PlutEntry			CreateNewPlutWithPPATAndColor(Handle inPPAT, const RGBColor &inColor);
	OSStatus			TryTheme(FSSpec &inThemeSpec);
	//Panes
	LWindow *mTextColorWindow;
	LWindow *mRequiredBrushWindow;
	LWindow *mUserBrushWindow;
	LPopupButton *mIconMenu;
	LEditText	*mThemeInfoHorizontalSliderTickLeftEdit;
	LEditText	*mThemeInfoVerticalSliderTickTopEdit;
	LEditText	*mThemeInfoSliderHorizontalThumbWidthEdit;
	LEditText	*mThemeInfoSliderVerticalThumbHeightEdit;
	LEditText	*mThemeInfoMenuSeparatorHeightEdit;
	LEditText	*mThemeInfoMenuBarHeightEdit;
	LEditText	*mThemeInfoMenuTitleLeftEdit;
	LEditText	*mThemeInfoMenuTitleRightEdit;
	LEditText	*mThemeInfoScrollHorizontalThumbWidthEdit;
	LEditText	*mThemeInfoScrollVerticalThumbHeightEdit;
	LEditText	*mThemeInfoSmallScrollHorizontalThumbWidthEdit;
	LEditText	*mThemeInfoSmallScrollVerticalThumbHeightEdit;
	LImageWell	 		  *mIcon48X48Well, *mIcon32X32Well, *mIcon16X16Well, *mIcon16X12Well;
	TTextClrListTable	*mTextClrListTable;
	TBrushTable			*mRequiredBrushTable, *mUserBrushTable;
	UTTextClrListResource	mTextColorResource;
	UTPlutBrushResource 	mRequiredBrushColorResource;
	UTPlutResource			mUserBrushResource;
	UTThemeTinfResource		mTinfResource;
	UTTicListResource		mTicListResource;
	UTTdatResource			mTdatResource;
	UTTMDAResource			mThemePreferences;
	Collection				mSavedTheme;
	Boolean					mTestSpecFlipFlop;
	OSStatus				MakeTestSpec(FSSpec &outSpec);
	#pragma warn_hidevirtual off
	TArray<UTThemeResource*>		mAddedResources;
	#pragma warn_hidevirtual reset
	SInt16 mCurrentIconIndex;
	
};

#endif