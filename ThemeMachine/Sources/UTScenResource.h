// ===========================================================================
//	UTScenResource.h			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the scen resource
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Dec 22/98 Initial Implementation

#ifndef _H_UTScenResource
#define _H_UTScenResource
#pragma once

#include "UTResource.h"
#include <Collections.h>

#define kScenResourceType 'scen'

// ---------------------------------------------------------------------------

class	UTScenResource : public UTResource
{
	public:
	UTScenResource();							
	virtual ~UTScenResource();
	void Init(ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true);
			
	//Getters
	SInt32 GetHorizontalSliderTickLeftOffset();
	SInt32 GetSliderThumbWidth();
	SInt32 GetSliderThumbHeight();
	SInt32 GetMenuBarHeight();
	SInt32 GetHorizontalScrollBarThumbWidth();
	SInt32 GetMinimumColorDepth();
	SInt32 GetMenuSeperatorHeight();
	SInt32 GetMenuTitleLeftOffset();
	SInt32 GetMenuTitleRightOffset();
	SInt32 GetVerticalScrollBarThumbHeight();
	SInt32 GetSmallHorizontalScrollBarThumbWidth();
	SInt32 GetSmallVerticalScrollBarThumbHeight();
	SInt32 GetVersion();
	SInt32 GetVerticalSliderTickTopOffset();
	
	//Setters
	void SetHorizontalSliderTickLeftOffset(SInt32 inValue);
	void SetSliderThumbWidth(SInt32 inValue);
	void SetSliderThumbHeight(SInt32 inValue);
	void SetMenuBarHeight(SInt32 inValue);
	void SetHorizontalScrollBarThumbWidth(SInt32 inValue);
	void SetMinimumColorDepth(SInt32 inValue);
	void SetMenuSeperatorHeight(SInt32 inValue);
	void SetMenuTitleLeftOffset(SInt32 inValue);
	void SetMenuTitleRightOffset(SInt32 inValue);
	void SetVerticalScrollBarThumbHeight(SInt32 inValue);
	void SetSmallHorizontalScrollBarThumbWidth(SInt32 inValue);
	void SetSmallVerticalScrollBarThumbHeight(SInt32 inValue);
	void SetVersion(SInt32 inValue);
	void SetVerticalSliderTickTopOffset(SInt32 inValue);
};

#endif
