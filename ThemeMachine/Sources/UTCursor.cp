// ===========================================================================
//	UTCursor.cp					PowerPlant 2.0		©1997-1999 Metrowerks Inc.
// ===========================================================================
//	Original Author: John C. Daub
//
//	A set of utility classes and routines for cursor manipulation and control.
//
//	Overlaps slightly in name/concept from the old, obsolete UTCursor class.
//	Do not mix these two classes (and their files). They are incompatable.


#include "UTCursor.h"
#include <UDrawingState.h>
#include <UDebugging.h>


#pragma mark -

// ===========================================================================
// € StCursor
// ===========================================================================
//	A class to temporarily change the cursor to something else.

// ---------------------------------------------------------------------------
//	€ StCursor								Constructor				  [public]
// ---------------------------------------------------------------------------
//	Upon entry, specify the ResIDT of the 'CURS' to change to. Upon exit,
//	we either restore the old cursor or default to the arrow.
//
//	By default, StCursor will set to the watch cursor, and restore the
//	original cursor.

StTCursor::StTCursor(
	ThemeCursor inCursor,
	bool inRestoreArrow /*= true*/)
{
	mRestoreArrow = inRestoreArrow;
	
	OSStatus theStatus = SetThemeCursor(inCursor);
	SignalIf_(theStatus);
}


// ---------------------------------------------------------------------------
//	€ ~StCursor								Destructor				  [public]
// ---------------------------------------------------------------------------
//	Pops back to our original cursor

StTCursor::~StTCursor()
{	
	if(mRestoreArrow)
	{
		OSStatus theStatus = SetThemeCursor(kThemeArrowCursor);
		SignalIf_(theStatus);
	}
}

