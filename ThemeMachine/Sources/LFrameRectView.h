// ===========================================================================
//	LFrameRectView.h					PowerPlant 1.9.3	©1993-1998 Metrowerks Inc.
// ===========================================================================

#ifndef _H_LFrameRectView
#define _H_LFrameRectView
#pragma once

#include <LView.h>
#include <LDragAndDrop.h>
#include <LBroadcaster.h>
#include "UTPlutResource.h"
#include "LFramePixelPane.h"
#include "TBrushTable.h"
#include <TArray.h>
class LFrameView;
class FrameEntry;

// ---------------------------------------------------------------------------

const UInt32 kPixelCount = 64;

class	LFrameRectView : public LView {
public:
	
						LFrameRectView(LFrameView *inView, SInt32 inInset);
	virtual				~LFrameRectView();
	virtual void		FinishCreate();					

	virtual PlutDragRecord		GetPlutDragRec(SInt16 inIndex, bool isRequired);	
	
	virtual Boolean		IsHitBy(SInt32		inHorizPort,
								SInt32		inVertPort);
	virtual Boolean		Contains(
								SInt32		inHorizPort,
								SInt32		inVertPort) const;
	SInt32	GetInset();
	void	SetInset(SInt32 inInset);
	Boolean 		GetCurrentSelectedPlutDragRec(PlutDragRecord &outRec);
	UInt32	GetFrmeCount();
	void	GetFrmeEntries(TArray<FrameEntry*> &outEntries);
	virtual void	AdaptToNewSurroundings();
	void SetPixel(PlutEntryIndex inIndex, UInt32 inPixelIndex,FrameOrigin inOrigin);
	Boolean ShowGrid(Boolean &outDoItInColor);
	void SetIsModified(Boolean inModified = true);	
	void GetFrameRect(Rect &inRect);			
protected:
	virtual void		DrawSelf();
	
	LFrameView 			*mFrameView;
	#pragma warn_hidevirtual off
	TArray<LFramePixelPane*> mPixels;
	#pragma warn_hidevirtual reset
	SInt32				mInset;
	private:
	void Init(LFrameView *inView);
};


#endif