// ===========================================================================
//	UTTinfResource.h			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the Tinf resource
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Dec 22/98 Initial Implementation

#ifndef _H_UTTinfResource
#define _H_UTTinfResource
#pragma once

#include "UTFlacResource.h"

const ResType kTinfResourceType ='tinf';

// ---------------------------------------------------------------------------

class	UTTinfResource : public UTFlacResource
{
	public:
	UTTinfResource();							
	virtual ~UTTinfResource();
	void Init(ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true);
			
	//Getters
	SInt16 GetHorizontalSliderTickLeftOffset();
	SInt16 GetSliderThumbWidth();
	SInt16 GetSliderThumbHeight();
	SInt16 GetMenuBarHeight();
	SInt16 GetHorizontalScrollBarThumbWidth();
	SInt16 GetMinimumColorDepth();
	SInt16 GetMenuSeperatorHeight();
	SInt16 GetMenuTitleLeftOffset();
	SInt16 GetMenuTitleRightOffset();
	SInt16 GetVerticalScrollBarThumbHeight();
	SInt16 GetSmallHorizontalScrollBarThumbWidth();
	SInt16 GetSmallVerticalScrollBarThumbHeight();
	SInt16 GetVersion();
	SInt16 GetVerticalSliderTickTopOffset();
	
	//Setters
	void SetHorizontalSliderTickLeftOffset(SInt16 inValue);
	void SetSliderThumbWidth(SInt16 inValue);
	void SetSliderThumbHeight(SInt16 inValue);
	void SetMenuBarHeight(SInt16 inValue);
	void SetHorizontalScrollBarThumbWidth(SInt16 inValue);
	void SetMinimumColorDepth(SInt16 inValue);
	void SetMenuSeperatorHeight(SInt16 inValue);
	void SetMenuTitleLeftOffset(SInt16 inValue);
	void SetMenuTitleRightOffset(SInt16 inValue);
	void SetVerticalScrollBarThumbHeight(SInt16 inValue);
	void SetSmallHorizontalScrollBarThumbWidth(SInt16 inValue);
	void SetSmallVerticalScrollBarThumbHeight(SInt16 inValue);
	void SetVersion(SInt16 inValue);
	void SetVerticalSliderTickTopOffset(SInt16 inValue);
};

#endif
