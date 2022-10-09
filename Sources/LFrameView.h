// ===========================================================================
//	LFrameView.h					PowerPlant 1.9.3	©1993-1998 Metrowerks Inc.
// ===========================================================================

#ifndef _H_LFrameView
#define _H_LFrameView
#pragma once

#include <LView.h>
#include <LDragAndDrop.h>
#include <TArray.h>
#include "UTPlutResource.h"
#include "TBrushTable.h"
#include "UTFrmeResource.h"
#include "LBroadcaster.h"

class LFrameRectView;
class TFrmeEditDialogBox;

// ---------------------------------------------------------------------------

class	LFrameView : public LView, public LDragAndDrop, public LBroadcaster {
public:
	
	static const RGBColor kUpperLeftCornerColor;
	static const RGBColor kUpperRightCornerColor;
	static const RGBColor kLowerLeftCornerColor;
	static const RGBColor kLowerRightCornerColor;
	static const RGBColor kUnknownCornerColor;

	enum { class_ID = FOUR_CHAR_CODE('FrVi') };
	enum { kEyeDropMessage = FOUR_CHAR_CODE('EddM') };
	
						LFrameView(TFrmeEditDialogBox* inDialog);
						LFrameView(
								LStream				*inStream);
	virtual				~LFrameView();

	virtual void		ClickSelf(
								const SMouseDownEvent &inMouseDown);
	void				SetEditDialog(TFrmeEditDialogBox *inDialog);	
	virtual void		AdjustCursorSelf(
								Point				inPortPt,
								const EventRecord	&inMacEvent);				
	
	virtual PlutDragRecord		GetPlutDragRec(SInt16 inIndex, bool isRequired);	
	Boolean 		GetCurrentSelectedPlutDragRec(PlutDragRecord &outRec);
	SInt32	GetMinimumInset();
	SInt32	GetMaximumInset();
	void	SetMinimumInset(SInt32 inInset);
	void	SetMaximumInset(SInt32 inInset);
	FrameOrigin GetPatternOrigin();
	void	SetPatternOrigin(FrameOrigin inOrigin);
	LFrameRectView*	AddFrame(SInt32 inInset, Boolean inRefresh);
	LFrameRectView* RemoveFrame(SInt32 inInset, Boolean inRefresh);
	LFrameRectView* GetFrame(SInt32 inInset);	
	void	SetFrmeResource(UTFrmeResource *inResource);
	OSStatus	BuildFrmeResource(UTFrmeResource &ioResource);
	void	SetCenterRectangle(const Rect &inRect);
	virtual Boolean		PointInDropArea(Point				inGlobalPt);
	virtual void		AdjustCursor(
								Point				inPortPt,
								const EventRecord	&inMacEvent);
	virtual void Click(SMouseDownEvent	&inMouseDown);
	Boolean GetEyeDropperMode();
	void	SetEyeDropperMode(Boolean inMode, Boolean doBroadcast = true);
	virtual void		AdaptToNewSurroundings();
	Boolean ShowGrid(Boolean &outDoItInColor);
	void SetShowGrid(Boolean inShowGrid, Boolean inDoItInColor);
	void				SetIsModified(Boolean inModified = true);
	bool				GetIsModified();
	Boolean 			GetMagnifyingMode();
	void				SetMagnifyingMode(Boolean inMode, Boolean doBroadcast = true);

	void				SetMagnification(float inMagnification, Boolean inRefresh = true);
	float				GetMagnification();
	void				DragAndDropFrame(const SMouseDownEvent &inMouseDown);
	
protected:
	virtual void		DrawSelf();
	virtual Boolean		ItemIsAcceptable(
								DragReference		inDragRef,
								ItemReference		inItemRef);
	virtual void		ReceiveDragItem(
								DragReference		inDragRef,
								DragAttributes		inDragAttrs,
								ItemReference		inItemRef,
								Rect&				inItemBounds);
	virtual void		HiliteDropArea(
								DragReference		inDragRef);
	void SetPixel(SInt32 inInset, PlutEntryIndex inIndex, UInt32 inPixelIndex,FrameOrigin inOrigin);
	#pragma warn_hidevirtual off							
	TArray<LFrameRectView*> mFrames;
	#pragma warn_hidevirtual reset
	Boolean				mHasPlut;
	SInt16				mPlutIndex;
	Boolean				mRequiredPlutTable;
	TFrmeEditDialogBox			*mEditDialog;
	FrameInset			mMaximumInset;
	FrameInset			mMinimumInset;
	FrameOrigin			mPatternOrigin;
	Rect				mCenterRect;
	Boolean				mEyeDropperMode;
	Boolean				mShowGrid;
	Boolean				mDoGridInColor;
	Boolean				mMagnifyingMode;
	UTFrmeResource		*mResource;
	float				mMagnification;
	private:
	void Init();
};


#endif