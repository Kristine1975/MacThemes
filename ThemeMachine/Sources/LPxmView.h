// ===========================================================================
//	LPxmView.h					PowerPlant 1.9.3	©1993-1998 Metrowerks Inc.
// ===========================================================================

#ifndef _H_LPxmView
#define _H_LPxmView
#pragma once

#include <LView.h>
#include <LDragAndDrop.h>
#include <LBroadcaster.h>
#include "TThemes.h"
class CTPxmResource;
class LFocusBox;

// ---------------------------------------------------------------------------

class	LPxmView : public LView, public LCommander, public LDragAndDrop, public LBroadcaster {
public:
	
	enum { class_ID = FOUR_CHAR_CODE('PXMV') };
	enum PxmViewType { kImageView = 1, kMaskView = 2, kImageMaskView = 3 };
						LPxmView();
						LPxmView(
								LStream				*inStream);
	virtual				~LPxmView();
						
	CTPxmResource*		GetPxmResource() const	{ return mPxm; }
	void GetPxmResourceSpec(FullResourceSpec &outSpec) const;
	void				SetPxmResource(CTPxmResource *inPxm);
	PxmViewType			GetPxmViewType() const { return mPxmViewType; }
	void				SetPxmViewType(PxmViewType inType);
	
	SInt16 				GetIndex() { return mIndex; }
	SInt16				GetMaxIndex();
	void				SetIndex(SInt16 inIndex);
	virtual void		ClickSelf(
								const SMouseDownEvent &inMouseDown);
								
	void 				ImportPictFile();
	void 				ExportPictFile();
	
	virtual Boolean		ObeyCommand(
								CommandT		inCommand,
								void*				ioParam = nil);
								
	virtual void		FindCommandStatus(
								CommandT		inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&			outMark,
								Str255				outName);
protected:
	CTPxmResource				*mPxm;
	
	PxmViewType					mPxmViewType;
	MessageT					mMessage;
	SInt16						mIndex;
	LFocusBox 					*mFocusBox;
	virtual void		DrawSelf();
	virtual Boolean		ItemIsAcceptable(
								DragReference		inDragRef,
								ItemReference		inItemRef);
	virtual void		ReceiveDragItem(
								DragReference		inDragRef,
								DragAttributes		inDragAttrs,
								ItemReference		inItemRef,
								Rect&				inItemBounds);
	OSErr PictToPxm(PicHandle inPic);
	OSErr PxmToPict(PicHandle &outPic);
	Boolean UsePictRectAlert();
	virtual void		BeTarget();
	virtual void		DontBeTarget();
	
	private:
	void Init();
};


#endif