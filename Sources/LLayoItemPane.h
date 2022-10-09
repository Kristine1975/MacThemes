// ===========================================================================
//	LLayoItemPane.h					PowerPlant 1.9.3	©1993-1998 Metrowerks Inc.
// ===========================================================================

#ifndef _H_LFramePixelPane
#define _H_LFramePixelPane
#pragma once

#include <LPane.h>
#include "LLayoView.h"
#include "UTLayoutResource.h"
#include <LDragAndDrop.h>

// ---------------------------------------------------------------------------

class	LLayoItemPane : public LPane, LDragAndDrop {
public:
	
						LLayoItemPane(const SPaneInfo	&inPaneInfo, UInt32 inNumber, LLayoView *inView, UTLayoutResource * inResource, LayoutItem &inItem);

	virtual				~LLayoItemPane();
	virtual Boolean		IsHitBy(SInt32		inHorizPort,
								SInt32		inVertPort);

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
	void Init();
	Boolean				IsItemVisible() const;
	LLayoView	*mView;
	UTLayoutResource *mResource;
	LayoutItem	mItem;
	UInt32 mNumber;
};


#endif