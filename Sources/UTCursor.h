// ===========================================================================
//	UTCursor.h			  		PowerPlant 2.0		©1997-1999 Metrowerks Inc.
// ===========================================================================
//	Original Author: John C. Daub

#ifndef _H_UTCursor
#define _H_UTCursor
#pragma once

#include <PP_Prefix.h>
#include <Quickdraw.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif


// ---------------------------------------------------------------------------

/*class StTColorCursor {
public:
						StTColorCursor(ResID inID,bool inRestoreArrow = true);

	virtual				~StTColorCursor();
	
	protected:
	Boolean	mRestoreArrow;

};*/

// ===========================================================================

class StTCursor {
public:
						StTCursor(ThemeCursor inCursor,bool inRestoreArrow = true);

	virtual				~StTCursor();
	
	protected:
	Boolean	mRestoreArrow;

};



#endif /* _H_UTCursor */
