// ===========================================================================
//	UTTMDAResource.cpp			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the flac resource
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


#include "UTTMDAResource.h"
#include "TThemes.h"
// ---------------------------------------------------------------------------

const UInt32 kVersion1 = 100;

UTTMDAResource::UTTMDAResource()
{
}
			
UTTMDAResource::~UTTMDAResource()
{
}


void UTTMDAResource::Init(
				ResIDT			inResID,
				ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/,
				ResType			inResType /*= kTMDAResourceType*/)
{
	UTResource::Init(inResType, inResID, inResFileID, inCreate, inThrowFail);
}
			
Handle 	UTTMDAResource::BuildBaseResource()
{
	Handle newRes = ::NewHandleClear(sizeof(ThemeMachineDocPrefs));
	((ThemeMachineDocPrefs*)(*newRes))->version = kVersion1;
	((ThemeMachineDocPrefs*)(*newRes))->themeSettingsWindowPos.h = 50;
	((ThemeMachineDocPrefs*)(*newRes))->themeSettingsWindowPos.v = 50;
	((ThemeMachineDocPrefs*)(*newRes))->userBrushWindowPos.h = 60;
	((ThemeMachineDocPrefs*)(*newRes))->userBrushWindowPos.v = 60;
	((ThemeMachineDocPrefs*)(*newRes))->reqdBrushWindowPos.h = 90;
	((ThemeMachineDocPrefs*)(*newRes))->reqdBrushWindowPos.v = 90;
	((ThemeMachineDocPrefs*)(*newRes))->textColorWindowPos.h = 110;
	((ThemeMachineDocPrefs*)(*newRes))->textColorWindowPos.v = 110;
	((ThemeMachineDocPrefs*)(*newRes))->showThemeSettingsWindow = true;
	((ThemeMachineDocPrefs*)(*newRes))->showUserBrushWindow = true;
	((ThemeMachineDocPrefs*)(*newRes))->showReqdBrushWindow = true;
	((ThemeMachineDocPrefs*)(*newRes))->showTextColorWindow = true;
	return newRes;
}

UInt32 UTTMDAResource::GetVersion()
{
	return ((ThemeMachineDocPrefs*)(*mResourceH))->version;
}

Point UTTMDAResource::GetThemeSettingsWindowPos()
{
	return ((ThemeMachineDocPrefs*)(*mResourceH))->themeSettingsWindowPos;
}

Point UTTMDAResource::GetUserBrushWindowPos()
{
	return ((ThemeMachineDocPrefs*)(*mResourceH))->userBrushWindowPos;
}

Point UTTMDAResource::GetRequiredBrushWindowPos()
{
	return ((ThemeMachineDocPrefs*)(*mResourceH))->reqdBrushWindowPos;
}

Point UTTMDAResource::GetTextColorWindowPos()
{
	return ((ThemeMachineDocPrefs*)(*mResourceH))->textColorWindowPos;
}

Boolean UTTMDAResource::GetShowThemeSettingsWindow()
{
	return ((ThemeMachineDocPrefs*)(*mResourceH))->showThemeSettingsWindow;
}

Boolean UTTMDAResource::GetShowUserBrushWindow()
{
	return ((ThemeMachineDocPrefs*)(*mResourceH))->showUserBrushWindow;
}

Boolean UTTMDAResource::GetShowRequiredBrushWindow()
{
	return ((ThemeMachineDocPrefs*)(*mResourceH))->showReqdBrushWindow;
}

Boolean UTTMDAResource::GetShowTextColorWindow()
{
	return ((ThemeMachineDocPrefs*)(*mResourceH))->showTextColorWindow;
}


void UTTMDAResource::SetThemeSettingsWindowPos(Point inUpperLeft)
{
	((ThemeMachineDocPrefs*)(*mResourceH))->themeSettingsWindowPos = inUpperLeft;
	Dirty();
}

void UTTMDAResource::SetUserBrushWindowPos(Point inUpperLeft)
{
	((ThemeMachineDocPrefs*)(*mResourceH))->userBrushWindowPos = inUpperLeft;
	Dirty();
}

void UTTMDAResource::SetRequiredBrushWindowPos(Point inUpperLeft)
{
	((ThemeMachineDocPrefs*)(*mResourceH))->reqdBrushWindowPos = inUpperLeft;
	Dirty();
}

void UTTMDAResource::SetTextColorWindowPos(Point inUpperLeft)
{
	((ThemeMachineDocPrefs*)(*mResourceH))->textColorWindowPos = inUpperLeft;
	Dirty();
}

void UTTMDAResource::SetShowThemeSettingsWindow(Boolean inShow)
{
	((ThemeMachineDocPrefs*)(*mResourceH))->showThemeSettingsWindow = inShow;
	Dirty();
}

void UTTMDAResource::SetShowUserBrushWindow(Boolean inShow)
{
	((ThemeMachineDocPrefs*)(*mResourceH))->showUserBrushWindow = inShow;
	Dirty();
}

void UTTMDAResource::SetShowRequiredBrushWindow(Boolean inShow)
{
	((ThemeMachineDocPrefs*)(*mResourceH))->showReqdBrushWindow = inShow;
	Dirty();
}

void UTTMDAResource::SetShowTextColorWindow(Boolean inShow)
{
	((ThemeMachineDocPrefs*)(*mResourceH))->showTextColorWindow = inShow;
	Dirty();
}
