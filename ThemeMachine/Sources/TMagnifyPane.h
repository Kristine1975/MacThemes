// ===========================================================================
//	TMagnifyPane.h					PowerPlant 2.0		©1993-1999 Metrowerks Inc.
// ===========================================================================

#ifndef _H_TMagnifyPane
#define _H_TMagnifyPane
#pragma once

#include <LView.h>
#include <LPeriodical.h>


// ---------------------------------------------------------------------------

class	TMagnifyPane : public LView, public LPeriodical {
public:
	enum { class_ID = FOUR_CHAR_CODE('MVie') };
	
						TMagnifyPane();
						TMagnifyPane(
								LStream				*inStream);

						
	virtual	void		SpendTime(const EventRecord&	inMacEvent);

	
protected:

	virtual void		DrawSelf();

};

#endif
