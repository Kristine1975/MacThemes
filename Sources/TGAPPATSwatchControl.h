// ===========================================================================
//	TGAPPATSwatchControl.cpp			   Allegro Themes Project
// ===========================================================================
//
//	A Pane for displaying PPAT's.
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


#ifndef _H_TGAPPATSwatchControl
#define _H_TGAPPATSwatchControl
#pragma once

#include <LControl.h>
#include <LString.h>
#include "TThemes.h"

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------
	
class TGAPPATSwatchControl : public LControl {
public:
	enum	{ class_ID = FOUR_CHAR_CODE('THPP') };
	
							TGAPPATSwatchControl();
							
							TGAPPATSwatchControl(	
									const TGAPPATSwatchControl& inOriginal);

							TGAPPATSwatchControl(	
									LStream*			inStream);		

							TGAPPATSwatchControl(	
									const SPaneInfo&	inPaneInfo,
									const SControlInfo&	inControlInfo,
									const FullResourceSpec& inSpec,
									Str255				inPromptString);

	virtual					~TGAPPATSwatchControl();
	
	void					GetSwatchPPAT(Handle& outPPAT) const;
	
																								
										
	virtual	void			SetSwatchPPAT(const Handle inSwatchPPAT);
	virtual void			SetSwatchPPAT(const FullResourceSpec &inSpec);

	
	virtual	void			EnableSelf();		
	virtual	void			DisableSelf();

	virtual void			ActivateSelf();
	virtual void			DeactivateSelf();

	virtual	void			DrawSelf();
	
protected:
	PixPatHandle mPattern;
	
			void			Init();	

	virtual	void			BroadcastValueMessage();
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
