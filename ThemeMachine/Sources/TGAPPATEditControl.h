// ===========================================================================
//	TGAPPATEditControl.cpp			   Allegro Themes Project
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


#ifndef _H_TGAPPATEditControl
#define _H_TGAPPATEditControl
#pragma once

#include "TGAPPATSwatchControl.h"
#include "LCommander.h"
#include "LClipboard.h"

class LFocusBox;
class LClipboard;

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

// ---------------------------------------------------------------------------
	
class TGAPPATEditControl : public TGAPPATSwatchControl, LCommander {
public:
	enum	{ class_ID = FOUR_CHAR_CODE('THPE') };
	
							TGAPPATEditControl();
							
							TGAPPATEditControl(	
									const TGAPPATEditControl& inOriginal);

							TGAPPATEditControl(	
									LStream*			inStream);		

							TGAPPATEditControl(	
									const SPaneInfo&	inPaneInfo,
									const SControlInfo&	inControlInfo,
									const FullResourceSpec& inSpec,
									Str255				inPromptString);

	virtual					~TGAPPATEditControl();
	
	virtual Boolean		ObeyCommand(
								CommandT		inCommand,
								void*				ioParam = nil);
								
	virtual void		FindCommandStatus(
								CommandT		inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&			outMark,
								Str255				outName);
	virtual void		HotSpotResult(SInt16	inHotSpot);
	
	protected:
		void					Init();
		virtual	void		DoneTracking(	
										SInt16			inHotSpot,
										Boolean			inGoodTrack);
										
		
		virtual void		BeTarget();
		virtual void		DontBeTarget();
		
		LFocusBox *mFocusBox;
		
};

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
