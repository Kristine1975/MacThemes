// ===========================================================================
//	LFramePixelPane.h					PowerPlant 1.9.3	©1993-1998 Metrowerks Inc.
// ===========================================================================

#ifndef _H_LFramePixelPane
#define _H_LFramePixelPane
#pragma once

#include <LPane.h>
#include <LDragAndDrop.h>
#include "UTPlutResource.h"
#include "UTFrmeResource.h"

class LFrameRectView;

// ---------------------------------------------------------------------------

class	LFramePixelPane : public LPane, public LDragAndDrop {
public:
	
						LFramePixelPane(LFrameRectView *inView);

	virtual				~LFramePixelPane();
	virtual void		AdjustCursorSelf(
								Point				inPortPt,
								const EventRecord	&inMacEvent);				
	Boolean				GetIsColoured();
	PlutEntryIndex		GetPlutEntryIndex();
	void				SetPlutEntryIndex(PlutEntryIndex inIndex);
	FrameOrigin			GetPatternOrigin();
	void				SetPatternOrigin(FrameOrigin inOrigin);
	virtual void	AdaptToNewSurroundings();

protected:
	virtual void		ClickSelf(const SMouseDownEvent& inMouseDown);
	virtual void		DrawSelf();
	virtual Boolean		ItemIsAcceptable(
								DragReference		inDragRef,
								ItemReference		inItemRef);
	virtual void		ReceiveDragItem(
								DragReference		inDragRef,
								DragAttributes		inDragAttrs,
								ItemReference		inItemRef,
								Rect&				inItemBounds);
	virtual void		HiliteDropArea(DragReference	inDragRef);

	
	
	private:
	Boolean				mHasPlut;
	SInt32				mPlutIndex;
	Boolean				mRequiredPlutTable;
	FrameOrigin			mFrameOrigin;
	LFrameRectView			*mFrameRect;
	void Init();
};


#endif