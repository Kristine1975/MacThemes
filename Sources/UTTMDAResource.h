// ===========================================================================
//	UTTMDAResource.h			   Allegro Themes Project
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


#ifndef _H_UTTMDAResource
#define _H_UTTMDAResource
#pragma once

#include "UTResource.h"
#include <Collections.h>

#define kTMDAResourceType 'TMDA'

// ---------------------------------------------------------------------------

typedef struct
{
	UInt32 version;
	Point themeSettingsWindowPos;
	Point userBrushWindowPos;
	Point reqdBrushWindowPos;
	Point textColorWindowPos;
	Boolean showThemeSettingsWindow;
	Boolean showUserBrushWindow;
	Boolean showReqdBrushWindow;
	Boolean showTextColorWindow;
} ThemeMachineDocPrefs;

class	UTTMDAResource : public UTResource
{
	public:
	UTTMDAResource();							
	virtual ~UTTMDAResource();
	void Init(ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true,
					ResType			inResType = kTMDAResourceType);
			
	virtual Handle 	BuildBaseResource();	
	
	UInt32 GetVersion();
	Point GetThemeSettingsWindowPos();
	Point GetUserBrushWindowPos();
	Point GetRequiredBrushWindowPos();
	Point GetTextColorWindowPos();
	Boolean GetShowThemeSettingsWindow();
	Boolean GetShowUserBrushWindow();
	Boolean GetShowRequiredBrushWindow();
	Boolean GetShowTextColorWindow();
	
	void SetThemeSettingsWindowPos(Point inUpperLeft);
	void SetUserBrushWindowPos(Point inUpperLeft);
	void SetRequiredBrushWindowPos(Point inUpperLeft);
	void SetTextColorWindowPos(Point inUpperLeft);
	void SetShowThemeSettingsWindow(Boolean inShow);
	void SetShowUserBrushWindow(Boolean inShow);
	void SetShowRequiredBrushWindow(Boolean inShow);
	void SetShowTextColorWindow(Boolean inShow);
	
	
	protected:
	
};

#endif
