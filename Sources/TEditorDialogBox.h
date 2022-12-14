// ===========================================================================
//	TEditorDialogBox.h	?1999 Allegro Themes Project
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

#ifndef _H_TEditorDialogBox
#define _H_TEditorDialogBox
#pragma once

#include <LDialogBox.h>

class CThemeDoc;


// ---------------------------------------------------------------------------

class	 TEditorDialogBox : public LDialogBox
					  {
public:
	enum { class_ID = FOUR_CHAR_CODE('TEDB') };
						TEditorDialogBox();
								
						TEditorDialogBox(
								LStream*		inStream);
								
	virtual				~TEditorDialogBox();

								
	virtual void		AttemptClose();
	
	virtual void		SetThemeDocument(CThemeDoc *inDocument);
	virtual CThemeDoc*	GetThemeDocument();
	virtual Boolean		GetIsModified();
	virtual void		SetIsModified(Boolean isModified = true);
protected:
	virtual Boolean		AttemptQuitSelf(
								SInt32				inSaveOption);
	virtual SInt16				AskSaveChanges(bool	inQuitting);
	virtual void				DoSave() = 0;
private:
	void Init();
	
	Boolean 			mIsModified;
	CThemeDoc			*mDoc;
};


#endif