// ===========================================================================
//	UTPlutBrushResource.h			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the Themes Brush plut resource. Resource 386 is the
// defined brushes for themes
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Dec 22/98 Initial Implementation
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


#ifndef _H_UTBrushPlutResource
#define _H_UTBrushPlutResource
#pragma once

#include "UTPlutResource.h"

// ---------------------------------------------------------------------------


class	UTPlutBrushResource : public UTPlutResource
{
	public:
	UTPlutBrushResource();							
	virtual ~UTPlutBrushResource();
	void Init(ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true);
			
	virtual Handle 	BuildBaseResource();	

	
	//Getters
	void GetDialogBackgroundActiveBrush(PlutEntry &outPlut);
	void GetDialogBackgroundInactiveBrush(PlutEntry &outPlut);
	void GetAlertBackgroundActiveBrush(PlutEntry &outPlut);
	void GetAlertBackgroundInactiveBrush(PlutEntry &outPlut);
	void GetModelessDialogBackgroundActiveBrush(PlutEntry &outPlut);
	void GetModelessDialogBackgroundInactiveBrush(PlutEntry &outPlut);
	void GetUtilityWindowBackgroundActiveBrush(PlutEntry &outPlut);
	void GetUtilityWindowBackgroundInactiveBrush(PlutEntry &outPlut);
	void GetListViewSortBackgroundActiveBrush(PlutEntry &outPlut);
	void GetListViewBackgroundInactiveBrush(PlutEntry &outPlut);
	void GetIconLabelBackgroundBrush(PlutEntry &outPlut);
	void GetListViewSeperatorBrush(PlutEntry &outPlut);
	void GetChasingArrowsBrush(PlutEntry &outPlut);
	void GetDragHiliteBrush(PlutEntry &outPlut);
	void GetDocumentWindowBackgroundBrush(PlutEntry &outPlut);
	void GetFinderWindowBackgroundBrush(PlutEntry &outPlut);
	void GetScrollBarDelimiterActiveBrush(PlutEntry &outPlut);
	void GetScrollBarDelimiterInactiveBrush(PlutEntry &outPlut);
	void GetFocusHighlightBrush(PlutEntry &outPlut);
	void GetPopupArrowActiveBrush(PlutEntry &outPlut);
	void GetPopupArrowPressedBrush(PlutEntry &outPlut);
	void GetPopupArrowInactiveBrush(PlutEntry &outPlut);
	void GetAppleGuideCoachMarkBrush(PlutEntry &outPlut);
	void GetIconLabelBackgroundSelectedBrush(PlutEntry &outPlut);
	void GetStaticAreaFillBrush(PlutEntry &outPlut);
	void GetActiveAreaFillBrush(PlutEntry &outPlut);
	void GetButtonFrameActiveBrush(PlutEntry &outPlut);
	void GetButtonFrameInactiveBrush(PlutEntry &outPlut);
	void GetButtonFaceActiveBrush(PlutEntry &outPlut);
	void GetButtonFaceInactiveBrush(PlutEntry &outPlut);
	void GetButtonFacePressedBrush(PlutEntry &outPlut);
	void GetButtonActiveDarkShadowBrush(PlutEntry &outPlut);
	void GetButtonActiveDarkHighlightBrush(PlutEntry &outPlut);
	void GetButtonActiveLightShadowBrush(PlutEntry &outPlut);
	void GetButtonActiveLightHighlightBrush(PlutEntry &outPlut);
	void GetButtonInactiveDarkShadowBrush(PlutEntry &outPlut);
	void GetButtonInactiveDarkHighlightBrush(PlutEntry &outPlut);
	void GetButtonInactiveLightShadowBrush(PlutEntry &outPlut);
	void GetButtonInactiveLightHighlightBrush(PlutEntry &outPlut);
	void GetButtonPressedDarkShadowBrush(PlutEntry &outPlut);
	void GetButtonPressedDarkHighlightBrush(PlutEntry &outPlut);
	void GetButtonPressedLightShadowBrush(PlutEntry &outPlut);
	void GetButtonPressedLightHighlightBrush(PlutEntry &outPlut);
	void GetBevelActiveLightBrush(PlutEntry &outPlut);
	void GetBevelActiveDarkBrush(PlutEntry &outPlut);
	void GetBevelInactiveLightBrush(PlutEntry &outPlut);
	void GetBevelInactiveDarkBrush(PlutEntry &outPlut);

	//Setters
	void SetDialogBackgroundActiveBrush(PlutEntry &inPlut);
	void SetDialogBackgroundInactiveBrush(PlutEntry &inPlut);
	void SetAlertBackgroundActiveBrush(PlutEntry &inPlut);
	void SetAlertBackgroundInactiveBrush(PlutEntry &inPlut);
	void SetModelessDialogBackgroundActiveBrush(PlutEntry &inPlut);
	void SetModelessDialogBackgroundInactiveBrush(PlutEntry &inPlut);
	void SetUtilityWindowBackgroundActiveBrush(PlutEntry &inPlut);
	void SetUtilityWindowBackgroundInactiveBrush(PlutEntry &inPlut);
	void SetListViewSortBackgroundActiveBrush(PlutEntry &inPlut);
	void SetListViewBackgroundInactiveBrush(PlutEntry &inPlut);
	void SetIconLabelBackgroundBrush(PlutEntry &inPlut);
	void SetListViewSeperatorBrush(PlutEntry &inPlut);
	void SetChasingArrowsBrush(PlutEntry &inPlut);
	void SetDragHiliteBrush(PlutEntry &inPlut);
	void SetDocumentWindowBackgroundBrush(PlutEntry &inPlut);
	void SetFinderWindowBackgroundBrush(PlutEntry &inPlut);
	void SetScrollBarDelimiterActiveBrush(PlutEntry &inPlut);
	void SetScrollBarDelimiterInactiveBrush(PlutEntry &inPlut);
	void SetFocusHighlightBrush(PlutEntry &inPlut);
	void SetPopupArrowActiveBrush(PlutEntry &inPlut);
	void SetPopupArrowPressedBrush(PlutEntry &inPlut);
	void SetPopupArrowInactiveBrush(PlutEntry &inPlut);
	void SetAppleGuideCoachMarkBrush(PlutEntry &inPlut);
	void SetIconLabelBackgroundSelectedBrush(PlutEntry &inPlut);
	void SetStaticAreaFillBrush(PlutEntry &inPlut);
	void SetActiveAreaFillBrush(PlutEntry &inPlut);
	void SetButtonFrameActiveBrush(PlutEntry &inPlut);
	void SetButtonFrameInactiveBrush(PlutEntry &inPlut);
	void SetButtonFaceActiveBrush(PlutEntry &inPlut);
	void SetButtonFaceInactiveBrush(PlutEntry &inPlut);
	void SetButtonFacePressedBrush(PlutEntry &inPlut);
	void SetButtonActiveDarkShadowBrush(PlutEntry &inPlut);
	void SetButtonActiveDarkHighlightBrush(PlutEntry &inPlut);
	void SetButtonActiveLightShadowBrush(PlutEntry &inPlut);
	void SetButtonActiveLightHighlightBrush(PlutEntry &inPlut);
	void SetButtonInactiveDarkShadowBrush(PlutEntry &inPlut);
	void SetButtonInactiveDarkHighlightBrush(PlutEntry &inPlut);
	void SetButtonInactiveLightShadowBrush(PlutEntry &inPlut);
	void SetButtonInactiveLightHighlightBrush(PlutEntry &inPlut);
	void SetButtonPressedDarkShadowBrush(PlutEntry &inPlut);
	void SetButtonPressedDarkHighlightBrush(PlutEntry &inPlut);
	void SetButtonPressedLightShadowBrush(PlutEntry &inPlut);
	void SetButtonPressedLightHighlightBrush(PlutEntry &inPlut);
	void SetBevelActiveLightBrush(PlutEntry &inPlut);
	void SetBevelActiveDarkBrush(PlutEntry &inPlut);
	void SetBevelInactiveLightBrush(PlutEntry &inPlut);
	void SetBevelInactiveDarkBrush(PlutEntry &inPlut);
	
	protected:
	//Not supposed to use these
	void InsertPlutEntry(UInt32 inIndex, const PlutEntry &inPlut);
	void AddPlutEntry(const PlutEntry &inPlut);
	void DeletePlutEntry(UInt32 inIndex);
};

#endif
