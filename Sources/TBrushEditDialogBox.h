// ===========================================================================
//	TBrushEditDialogBox.h	©1999 Allegro Themes Project
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

#ifndef _H_TBrushEditDialogBox
#define _H_TBrushEditDialogBox
#pragma once

#include <LDialogBox.h>
#include "TBrushTable.h"

class LGAColorSwatchControl;
class LEditText;
class TGAPPATEditControl;
class LControlPane;
// ---------------------------------------------------------------------------

class	 TBrushEditDialogBox : public LDialogBox
					  {
public:
	enum { class_ID = FOUR_CHAR_CODE('TBDL') };
	static const MessageT kBrushEditOK;
	static const MessageT kBrushEditCancel;
	static const PaneIDT kBrushEditOKID;
	static const PaneIDT kBrushEditCancelID;
						TBrushEditDialogBox();
								
						TBrushEditDialogBox(
								LStream*		inStream);
								
	virtual				~TBrushEditDialogBox();

								
	virtual void		ListenToMessage(
								MessageT		inMessage,
								void*			ioParam);
	
	virtual void		SetPlutEntry(const PlutEntry &inPlut);
	virtual void		GetPlutChangeRecord(PlutChangeRecord &outPlut);
	virtual void		SetTitle(const LStr255 inTitle);
	virtual void		GetTitle(LStr255 &outTitle); 
	virtual Boolean	GetRequired() { return mIsRequired; }
protected:

	
	virtual void		FinishCreateSelf();
	Boolean	 mIsRequired;
	PlutChangeRecord mPlutChange;
	LEditText	 *mBrushColorGreen, *mBrushColorBlue, *mBrushColorRed;
	LGAColorSwatchControl *mBrushColorSwatch;
	TGAPPATEditControl *mBrushPatternSwatch;
	LControlPane *mBrushTitle;
	Handle mPattern;
};


#endif