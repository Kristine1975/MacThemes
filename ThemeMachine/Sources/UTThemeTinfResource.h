// ===========================================================================
//	UTThemeTinfResource.h			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the scen resource
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Dec 22/98 Initial Implementation

#ifndef _H_UTThemeTinfResource
#define _H_UTThemeTinfResource
#pragma once

#include "UTTinfResource.h"


// ---------------------------------------------------------------------------

class	UTThemeTinfResource : public UTTinfResource
{
	public:
	UTThemeTinfResource() {}							
	virtual ~UTThemeTinfResource() {}
	void Init(ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true)
	{
		UTTinfResource::Init(kThemeInfoResourceID,inResFileID,inCreate,inThrowFail);
	}
			
};

#endif
