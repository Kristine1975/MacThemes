// ===========================================================================
//	TLayoEditDialogBox.h	©1999 Allegro Themes Project
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

#ifndef _H_TLayoEditDialogBox
#define _H_TLayoEditDialogBox
#pragma once

#include "TEditorDialogBox.h"
#include "UTLayoutResource.h"
class LLayoView;
class CThemeDoc;
class LCoordinateHierTable;
// ---------------------------------------------------------------------------

class	 TLayoEditDialogBox : public TEditorDialogBox
					  {
public:
	enum { class_ID = FOUR_CHAR_CODE('TLDL') };
						TLayoEditDialogBox();
								
						TLayoEditDialogBox(
								LStream*		inStream);
								
	virtual				~TLayoEditDialogBox();

								
	virtual void		ListenToMessage(
								MessageT		inMessage,
								void*			ioParam);
	void				SetLayoResource(const FullResourceSpec &inSpec);

protected:
	LLayoView			*mLayoView;
	UTLayoutResource		mLayoResource;
	LCoordinateHierTable	*mCoordinateTable;
	virtual void		FinishCreateSelf();
	virtual void		DoSave();
	
private:
	void Init();
};


#endif