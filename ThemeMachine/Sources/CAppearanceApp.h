// ===========================================================================
//	CAppearanceApp.h			©1994-1998 Metrowerks Inc. All rights reserved.
// ===========================================================================

#ifndef _H_CAppearanceApp
#define _H_CAppearanceApp
#pragma once

#include <LDocApplication.h>
#include "TThemes.h"

class LClipboard;
class TMagnifyPane;
class CAppearanceApp : public LDocApplication {

public:
							CAppearanceApp();
		virtual 			~CAppearanceApp();
	
		virtual Boolean		ObeyCommand(
									CommandT			inCommand,
									void*				ioParam);	
		virtual Boolean		AllowSubRemoval(
								LCommander*		inSub);
		virtual void		FindCommandStatus(
									CommandT			inCommand,
									Boolean&			outEnabled,
									Boolean&			outUsesMark,
									UInt16&				outMark,
									Str255				outName);
		virtual void		ChooseDocument();
		virtual void		OpenDocument(FSSpec*		inMacFSSpec);
		ResFileID			GetAppResFile() { return mAppResFile; }
		
		virtual void		ShowAboutBox();
protected:

		virtual void		StartUp();
		ResFileID mAppResFile;
		LWindow *mMagnifyWindow;
		TMagnifyPane *mMagnifyPane;
};

#endif // _H_CAppearanceApp