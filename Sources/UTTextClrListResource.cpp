// ===========================================================================
//	UTTextClrListResource.cpp			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the clr# 384 resource which is the text color
// resource for themes
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Dec 28/98 Initial Implementation
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



#include "UTTextClrListResource.h"
#include "TThemes.h"

// ---------------------------------------------------------------------------

UTTextClrListResource::UTTextClrListResource()
{
}
			
UTTextClrListResource::~UTTextClrListResource()
{
}

void UTTextClrListResource::Init(ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/)
{
	UTClrListResource::Init(kThemeTextColorResourceID, inResFileID, inCreate, inThrowFail);
}
			
Handle 	UTTextClrListResource::BuildBaseResource()
{
	Handle newRes = ::NewHandleClear(sizeof(UInt32) + (sizeof(RGBColor) * kThemeTextColorCount));
	ThrowIfMemFail_(newRes);
	*((UInt32*)(*newRes)) = kThemeTextColorCount;
	return newRes;
}

//UTTextClrListResource::Getters
void UTTextClrListResource::GetDialogActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorDialogActive - 1,outColor);
}

void UTTextClrListResource::GetDialogInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorDialogInactive - 1,outColor);
}

void UTTextClrListResource::GetAlertActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorAlertActive - 1,outColor);
}

void UTTextClrListResource::GetAlertInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorAlertInactive - 1,outColor);
}

void UTTextClrListResource::GetModelessDialogActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorModelessDialogActive - 1,outColor);
}

void UTTextClrListResource::GetModelessDialogInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorModelessDialogInactive - 1,outColor);
}

void UTTextClrListResource::GetWindowHeaderActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorWindowHeaderActive - 1,outColor);
}

void UTTextClrListResource::GetWindowHeaderInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorWindowHeaderInactive - 1,outColor);
}

void UTTextClrListResource::GetPlacardActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPlacardActive - 1,outColor);
}

void UTTextClrListResource::GetPlacardInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPlacardInactive - 1,outColor);
}

void UTTextClrListResource::GetPlacardPressedTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPlacardPressed - 1,outColor);
}

void UTTextClrListResource::GetPushButtonActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPushButtonActive - 1,outColor);
}

void UTTextClrListResource::GetPushButtonInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPushButtonInactive - 1,outColor);
}

void UTTextClrListResource::GetPushButtonPressedTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPushButtonPressed - 1,outColor);
}
	
void UTTextClrListResource::GetBevelButtonActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorBevelButtonActive - 1,outColor);
}

void UTTextClrListResource::GetBevelButtonInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorBevelButtonInactive - 1,outColor);
}

void UTTextClrListResource::GetBevelButtonPressedTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorBevelButtonPressed - 1,outColor);
}
	
void UTTextClrListResource::GetPopupButtonActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPopupButtonActive - 1,outColor);
}

void UTTextClrListResource::GetPopupButtonInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPopupButtonInactive - 1,outColor);
}

void UTTextClrListResource::GetPopupButtonPressedTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPopupButtonPressed - 1,outColor);
}
	
void UTTextClrListResource::GetIconLabelTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorIconLabel - 1,outColor);
}

void UTTextClrListResource::GetListViewTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorListView - 1,outColor);
}

void UTTextClrListResource::GetDocumentWindowTitleActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorDocumentWindowTitleActive - 1,outColor);
}

void UTTextClrListResource::GetDocumentWindowTitleInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorDocumentWindowTitleInactive - 1,outColor);
}

void UTTextClrListResource::GetMovableModalWindowTitleActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorMovableModalWindowTitleActive - 1,outColor);
}

void UTTextClrListResource::GetMovableModalWindowTitleInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorMovableModalWindowTitleInactive - 1,outColor);
}

void UTTextClrListResource::GetUtilityWindowTitleActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorUtilityWindowTitleActive - 1,outColor);
}

void UTTextClrListResource::GetUtilityWindowTitleInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorUtilityWindowTitleInactive - 1,outColor);
}

void UTTextClrListResource::GetPopupWindowTitleActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPopupWindowTitleActive - 1,outColor);
}

void UTTextClrListResource::GetPopupWindowTitleInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPopupWindowTitleInactive - 1,outColor);
}

void UTTextClrListResource::GetRootMenuActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorRootMenuActive - 1,outColor);
}

void UTTextClrListResource::GetRootMenuSelectedTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorRootMenuSelected - 1,outColor);
}

void UTTextClrListResource::GetRootMenuDisabledTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorRootMenuDisabled - 1,outColor);
}
	
void UTTextClrListResource::GetMenuItemActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorMenuItemActive - 1,outColor);
}

void UTTextClrListResource::GetMenuItemSelectedTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorMenuItemSelected - 1,outColor);
}

void UTTextClrListResource::GetMenuItemDisabledTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorMenuItemDisabled - 1,outColor);
}
	
void UTTextClrListResource::GetPopupLabelActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPopupLabelActive - 1,outColor);
}

void UTTextClrListResource::GetPopupLabelInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorPopupLabelInactive - 1,outColor);
}

void UTTextClrListResource::GetTabFrontActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorTabFrontActive - 1,outColor);
}

void UTTextClrListResource::GetTabNonFrontActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorTabNonFrontActive - 1,outColor);
}

void UTTextClrListResource::GetTabNonFrontPressedTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorTabNonFrontPressed - 1,outColor);
}

void UTTextClrListResource::GetTabFrontInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorTabFrontInactive - 1,outColor);
}

void UTTextClrListResource::GetTabNonFrontInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorTabNonFrontInactive - 1,outColor);
}

void UTTextClrListResource::GetIconLabelSelectedTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorIconLabelSelected - 1,outColor);
}

void UTTextClrListResource::GetBevelButtonStickyActiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorBevelButtonStickyActive - 1,outColor);
}

void UTTextClrListResource::GetBevelButtonStickyInactiveTextColor(RGBColor &outColor)
{
	GetColor(kThemeTextColorBevelButtonStickyInactive - 1,outColor);
}


//UTTextClrListResource::Setters
void UTTextClrListResource::SetDialogActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorDialogActive - 1,inColor);
}

void UTTextClrListResource::SetDialogInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorDialogInactive - 1,inColor);
}

void UTTextClrListResource::SetAlertActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorAlertActive - 1,inColor);
}

void UTTextClrListResource::SetAlertInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorAlertInactive - 1,inColor);
}

void UTTextClrListResource::SetModelessDialogActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorModelessDialogActive - 1,inColor);
}

void UTTextClrListResource::SetModelessDialogInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorModelessDialogInactive - 1,inColor);
}

void UTTextClrListResource::SetWindowHeaderActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorWindowHeaderActive - 1,inColor);
}

void UTTextClrListResource::SetWindowHeaderInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorWindowHeaderInactive - 1,inColor);
}

void UTTextClrListResource::SetPlacardActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPlacardActive - 1,inColor);
}

void UTTextClrListResource::SetPlacardInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPlacardInactive - 1,inColor);
}

void UTTextClrListResource::SetPlacardPressedTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPlacardPressed - 1,inColor);
}

void UTTextClrListResource::SetPushButtonActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPushButtonActive - 1,inColor);
}

void UTTextClrListResource::SetPushButtonInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPushButtonInactive - 1,inColor);
}

void UTTextClrListResource::SetPushButtonPressedTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPushButtonPressed - 1,inColor);
}
	
void UTTextClrListResource::SetBevelButtonActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorBevelButtonActive - 1,inColor);
}

void UTTextClrListResource::SetBevelButtonInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorBevelButtonInactive - 1,inColor);
}

void UTTextClrListResource::SetBevelButtonPressedTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorBevelButtonPressed - 1,inColor);
}
	
void UTTextClrListResource::SetPopupButtonActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPopupButtonActive - 1,inColor);
}

void UTTextClrListResource::SetPopupButtonInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPopupButtonInactive - 1,inColor);
}

void UTTextClrListResource::SetPopupButtonPressedTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPopupButtonPressed - 1,inColor);
}
	
void UTTextClrListResource::SetIconLabelTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorIconLabel - 1,inColor);
}

void UTTextClrListResource::SetListViewTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorListView - 1,inColor);
}

void UTTextClrListResource::SetDocumentWindowTitleActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorDocumentWindowTitleActive - 1,inColor);
}

void UTTextClrListResource::SetDocumentWindowTitleInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorDocumentWindowTitleInactive - 1,inColor);
}

void UTTextClrListResource::SetMovableModalWindowTitleActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorMovableModalWindowTitleActive - 1,inColor);
}

void UTTextClrListResource::SetMovableModalWindowTitleInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorMovableModalWindowTitleInactive - 1,inColor);
}

void UTTextClrListResource::SetUtilityWindowTitleActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorUtilityWindowTitleActive - 1,inColor);
}

void UTTextClrListResource::SetUtilityWindowTitleInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorUtilityWindowTitleInactive - 1,inColor);
}

void UTTextClrListResource::SetPopupWindowTitleActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPopupWindowTitleActive - 1,inColor);
}

void UTTextClrListResource::SetPopupWindowTitleInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPopupWindowTitleInactive - 1,inColor);
}

void UTTextClrListResource::SetRootMenuActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorRootMenuActive - 1,inColor);
}

void UTTextClrListResource::SetRootMenuSelectedTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorRootMenuSelected - 1,inColor);
}

void UTTextClrListResource::SetRootMenuDisabledTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorRootMenuDisabled - 1,inColor);
}
	
void UTTextClrListResource::SetMenuItemActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorMenuItemActive - 1,inColor);
}

void UTTextClrListResource::SetMenuItemSelectedTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorMenuItemSelected - 1,inColor);
}

void UTTextClrListResource::SetMenuItemDisabledTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorMenuItemDisabled - 1,inColor);
}
	
void UTTextClrListResource::SetPopupLabelActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPopupLabelActive - 1,inColor);
}

void UTTextClrListResource::SetPopupLabelInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorPopupLabelInactive - 1,inColor);
}

void UTTextClrListResource::SetTabFrontActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorTabFrontActive - 1,inColor);
}

void UTTextClrListResource::SetTabNonFrontActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorTabNonFrontActive - 1,inColor);
}

void UTTextClrListResource::SetTabNonFrontPressedTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorTabNonFrontPressed - 1,inColor);
}

void UTTextClrListResource::SetTabFrontInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorTabFrontInactive - 1,inColor);
}

void UTTextClrListResource::SetTabNonFrontInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorTabNonFrontInactive - 1,inColor);
}

void UTTextClrListResource::SetIconLabelSelectedTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorIconLabelSelected - 1,inColor);
}

void UTTextClrListResource::SetBevelButtonStickyActiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorBevelButtonStickyActive - 1,inColor);
}

void UTTextClrListResource::SetBevelButtonStickyInactiveTextColor(RGBColor &inColor)
{
	SetColor(kThemeTextColorBevelButtonStickyInactive - 1,inColor);
}
