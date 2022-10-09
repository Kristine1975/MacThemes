// ===========================================================================
//	UTTextClrListResource.h			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the clr# resource
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


#ifndef _H_UTTextClrListResource
#define _H_UTTextClrListResource
#pragma once

#include "UTClrListResource.h"

// ---------------------------------------------------------------------------

class	UTTextClrListResource : public UTClrListResource
{
	public:
	UTTextClrListResource();							
	virtual ~UTTextClrListResource();
	void Init(ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true);
			
	virtual Handle 	BuildBaseResource();	

	//Getters
	void GetDialogActiveTextColor(RGBColor &outColor);
	void GetDialogInactiveTextColor(RGBColor &outColor);
	void GetAlertActiveTextColor(RGBColor &outColor);
	void GetAlertInactiveTextColor(RGBColor &outColor);
	void GetModelessDialogActiveTextColor(RGBColor &outColor);
	void GetModelessDialogInactiveTextColor(RGBColor &outColor);
	void GetWindowHeaderActiveTextColor(RGBColor &outColor);
	void GetWindowHeaderInactiveTextColor(RGBColor &outColor);
	void GetPlacardActiveTextColor(RGBColor &outColor);
	void GetPlacardInactiveTextColor(RGBColor &outColor);
	void GetPlacardPressedTextColor(RGBColor &outColor);
	void GetPushButtonActiveTextColor(RGBColor &outColor);
	void GetPushButtonInactiveTextColor(RGBColor &outColor);
	void GetPushButtonPressedTextColor(RGBColor &outColor);
	void GetBevelButtonActiveTextColor(RGBColor &outColor);
	void GetBevelButtonInactiveTextColor(RGBColor &outColor);
	void GetBevelButtonPressedTextColor(RGBColor &outColor);	
	void GetPopupButtonActiveTextColor(RGBColor &outColor);
	void GetPopupButtonInactiveTextColor(RGBColor &outColor);
	void GetPopupButtonPressedTextColor(RGBColor &outColor);	
	void GetIconLabelTextColor(RGBColor &outColor);
	void GetListViewTextColor(RGBColor &outColor);
	void GetDocumentWindowTitleActiveTextColor(RGBColor &outColor);
	void GetDocumentWindowTitleInactiveTextColor(RGBColor &outColor);
	void GetMovableModalWindowTitleActiveTextColor(RGBColor &outColor);
	void GetMovableModalWindowTitleInactiveTextColor(RGBColor &outColor);
	void GetUtilityWindowTitleActiveTextColor(RGBColor &outColor);
	void GetUtilityWindowTitleInactiveTextColor(RGBColor &outColor);
	void GetPopupWindowTitleActiveTextColor(RGBColor &outColor);
	void GetPopupWindowTitleInactiveTextColor(RGBColor &outColor);
	void GetRootMenuActiveTextColor(RGBColor &outColor);
	void GetRootMenuSelectedTextColor(RGBColor &outColor);
	void GetRootMenuDisabledTextColor(RGBColor &outColor);	
	void GetMenuItemActiveTextColor(RGBColor &outColor);
	void GetMenuItemSelectedTextColor(RGBColor &outColor);
	void GetMenuItemDisabledTextColor(RGBColor &outColor);	
	void GetPopupLabelActiveTextColor(RGBColor &outColor);
	void GetPopupLabelInactiveTextColor(RGBColor &outColor);
	void GetTabFrontActiveTextColor(RGBColor &outColor);
	void GetTabNonFrontActiveTextColor(RGBColor &outColor);
	void GetTabNonFrontPressedTextColor(RGBColor &outColor);
	void GetTabFrontInactiveTextColor(RGBColor &outColor);
	void GetTabNonFrontInactiveTextColor(RGBColor &outColor);
	void GetIconLabelSelectedTextColor(RGBColor &outColor);
	void GetBevelButtonStickyActiveTextColor(RGBColor &outColor);
	void GetBevelButtonStickyInactiveTextColor(RGBColor &outColor);

	//Setters
	void SetDialogActiveTextColor(RGBColor &inColor);
	void SetDialogInactiveTextColor(RGBColor &inColor);
	void SetAlertActiveTextColor(RGBColor &inColor);
	void SetAlertInactiveTextColor(RGBColor &inColor);
	void SetModelessDialogActiveTextColor(RGBColor &inColor);
	void SetModelessDialogInactiveTextColor(RGBColor &inColor);
	void SetWindowHeaderActiveTextColor(RGBColor &inColor);
	void SetWindowHeaderInactiveTextColor(RGBColor &inColor);
	void SetPlacardActiveTextColor(RGBColor &inColor);
	void SetPlacardInactiveTextColor(RGBColor &inColor);
	void SetPlacardPressedTextColor(RGBColor &inColor);
	void SetPushButtonActiveTextColor(RGBColor &inColor);
	void SetPushButtonInactiveTextColor(RGBColor &inColor);
	void SetPushButtonPressedTextColor(RGBColor &inColor);
	void SetBevelButtonActiveTextColor(RGBColor &inColor);
	void SetBevelButtonInactiveTextColor(RGBColor &inColor);
	void SetBevelButtonPressedTextColor(RGBColor &inColor);	
	void SetPopupButtonActiveTextColor(RGBColor &inColor);
	void SetPopupButtonInactiveTextColor(RGBColor &inColor);
	void SetPopupButtonPressedTextColor(RGBColor &inColor);	
	void SetIconLabelTextColor(RGBColor &inColor);
	void SetListViewTextColor(RGBColor &inColor);
	void SetDocumentWindowTitleActiveTextColor(RGBColor &inColor);
	void SetDocumentWindowTitleInactiveTextColor(RGBColor &inColor);
	void SetMovableModalWindowTitleActiveTextColor(RGBColor &inColor);
	void SetMovableModalWindowTitleInactiveTextColor(RGBColor &inColor);
	void SetUtilityWindowTitleActiveTextColor(RGBColor &inColor);
	void SetUtilityWindowTitleInactiveTextColor(RGBColor &inColor);
	void SetPopupWindowTitleActiveTextColor(RGBColor &inColor);
	void SetPopupWindowTitleInactiveTextColor(RGBColor &inColor);
	void SetRootMenuActiveTextColor(RGBColor &inColor);
	void SetRootMenuSelectedTextColor(RGBColor &inColor);
	void SetRootMenuDisabledTextColor(RGBColor &inColor);	
	void SetMenuItemActiveTextColor(RGBColor &inColor);
	void SetMenuItemSelectedTextColor(RGBColor &inColor);
	void SetMenuItemDisabledTextColor(RGBColor &inColor);	
	void SetPopupLabelActiveTextColor(RGBColor &inColor);
	void SetPopupLabelInactiveTextColor(RGBColor &inColor);
	void SetTabFrontActiveTextColor(RGBColor &inColor);
	void SetTabNonFrontActiveTextColor(RGBColor &inColor);
	void SetTabNonFrontPressedTextColor(RGBColor &inColor);
	void SetTabFrontInactiveTextColor(RGBColor &inColor);
	void SetTabNonFrontInactiveTextColor(RGBColor &inColor);
	void SetIconLabelSelectedTextColor(RGBColor &inColor);
	void SetBevelButtonStickyActiveTextColor(RGBColor &inColor);
	void SetBevelButtonStickyInactiveTextColor(RGBColor &inColor);
	
	
	protected:
	//Not Supposed to use these
	void AddColor(const RGBColor &inColor);
	void DeleteColor(UInt32 inIndex);
	void InsertColor(UInt32 inIndex, const RGBColor &inColor);
};

#endif
