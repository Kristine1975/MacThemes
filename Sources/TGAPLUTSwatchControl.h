// ===========================================================================
//	TGAPLUTSwatchControl.cpp			   Allegro Themes Project
// ===========================================================================
//
//	A Pane for displaying PLUT's.
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


#ifndef _H_TGAPLUTSwatchControl
#define _H_TGAPLUTSwatchControl
#pragma once

#include <LControl.h>
#include <LString.h>
#include "TThemes.h"
#include "UTPlutResource.h"

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------
	
class TGAPLUTSwatchControl : public LControl {
public:
	enum	{ class_ID = FOUR_CHAR_CODE('THPL') };
	
							TGAPLUTSwatchControl();
							
							TGAPLUTSwatchControl(	
									const TGAPLUTSwatchControl& inOriginal);

							TGAPLUTSwatchControl(	
									LStream*			inStream);		


	virtual					~TGAPLUTSwatchControl();
	
	void					GetSwatchPLUT(PlutEntry &outPLUT) const;
	
																								
										
	virtual	void			SetSwatchPLUT(const PlutEntry inSwatchPLUT);

	
	virtual	void			EnableSelf();		
	virtual	void			DisableSelf();

	virtual void			ActivateSelf();
	virtual void			DeactivateSelf();

	virtual	void			DrawSelf();
	
protected:
	PlutEntry mPlut;
	
			void			Init();	

	virtual	void			BroadcastValueMessage();
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
