// ===========================================================================
//	LLayoView.h					PowerPlant 1.9.3	©1993-1998 Metrowerks Inc.
// ===========================================================================

#ifndef _H_LLayoView
#define _H_LLayoView
#pragma once

#include <LView.h>

class UTLayoutResource;
class CThemeDoc;

// ---------------------------------------------------------------------------

const UInt32 kPixelCount = 64;

class	LLayoView : public LView {
public:
	enum { class_ID = FOUR_CHAR_CODE('LaVi') };
						LLayoView();
						LLayoView(
								LStream				*inStream);
	virtual				~LLayoView();
	virtual void		FinishCreate();					
	
	void	SetLayoutResource(UTLayoutResource* inResource, Boolean inRefresh = true);			
	CThemeDoc*	GetThemeDocument();
	void	GetFlags(UInt32 &outVisibleFlags, UInt32 &outFeatureFlags);
	void 	SetFlags(UInt32 inVisibleFlags, UInt32 inFeatureFlags, Boolean inRefresh = true);
	void	SetShowLines(Boolean inShowLines, Boolean inRefresh = true);
	Boolean	GetShowLines();
protected:
	virtual void		DrawSelf();

private:
	void Init();
	UTLayoutResource *mResource;
	UInt32 mVisibleFlags, mFeatureFlags;
	Boolean mShowLines;
};


#endif