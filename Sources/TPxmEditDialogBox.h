// ===========================================================================
//	TPxmEditDialogBox.h	©1999 Allegro Themes Project
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

#ifndef _H_TPxmEditDialogBox
#define _H_TPxmEditDialogBox
#pragma once

#include "TEditorDialogBox.h"
#include "TThemes.h"
#include "CTPxmResource.h"
class LPxmView;
class TClutTable;
class UTClut;
// ---------------------------------------------------------------------------

class	 TPxmEditDialogBox : public TEditorDialogBox
					  {
public:
	enum { class_ID = FOUR_CHAR_CODE('PEDL') };
	static const MessageT kPxmEditOK;
	static const MessageT kPxmEditCancel;
	static const PaneIDT kPxmEditOKID;
	static const PaneIDT kPxmEditCancelID;
						TPxmEditDialogBox();
								
						TPxmEditDialogBox(
								LStream*		inStream);
								
	virtual				~TPxmEditDialogBox();

								
	virtual void		ListenToMessage(
								MessageT		inMessage,
								void*			ioParam);
	
	virtual void		SetPxmResource(const FullResourceSpec &inPxmSpec);
	virtual CTPxmResource *GetPxmResource() { return &mPxm; }
	virtual	void	GetPxmResourceSpec(FullResourceSpec &outSpec);
	
protected:
	void				UpdateIndexStatics();
	void				UpdateSizeStatics();
	void				UpdateIndexButtons();
	virtual void		FinishCreateSelf();
	virtual void		DoSave();
	LPxmView *mImageView, *mMaskView, *mMaskedImageView;
	CTPxmResource mPxm;
	FullResourceSpec mPxmSpec;
};


#endif