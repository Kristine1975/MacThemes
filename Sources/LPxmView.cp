// ===========================================================================
//	LPxmView.cp					PowerPlant 1.9.3	©1993-1998 Metrowerks Inc.
// ===========================================================================
//
//	Displays a 'PICT' resource
//
//	LPxmView stores the ID of a PICT resource as a member variable, and
//	always calls GetPicture() to get a Handle to the picture. It purposely
//	does not release the PICT resource when deleted, since other LPxmView
//	views may be using the same picture. For example, you might use the
//	same picture as a background or graphic element in multiple windows.
//
//	If you are concerned about the memory used by the PICT resource, mark
//	it as purgeable in your resource file.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "LPxmView.h"
#include <LStream.h>
#include <UDrawingState.h>
#include "CTPxmResource.h"
#include <ToolUtils.h>
#include "TThemes.h"
#include "UTPixUtilities.h"
#include <UStandardDialogs.h>
#include "TPxmEditDialogBox.h"

// ---------------------------------------------------------------------------
//	€ LPxmView								Default Constructor		  [public]
// ---------------------------------------------------------------------------

LPxmView::LPxmView() : LDragAndDrop(GetMacPort(),this)
{
	Init();
}




// ---------------------------------------------------------------------------
//	€ LPxmView								Stream Constructor	 	 [public]
// ---------------------------------------------------------------------------

LPxmView::LPxmView(
	LStream*	inStream)
	
	: LView(inStream), LDragAndDrop(GetMacPort(),this)
{
	Init();
	
	SInt16 theViewType;
	*inStream >> theViewType;
	*inStream >> mMessage;
	mPxmViewType = (PxmViewType)theViewType;
	SignalIfNot_(mPxmViewType == kImageView || mPxmViewType == kMaskView || mPxmViewType == kImageMaskView);
}



void LPxmView::Init()
{
	mPxm = NULL;
	mIndex = 1;
	mMessage = 0;
	mPxmViewType = kImageMaskView;
	mFocusBox = new LFocusBox();
	mFocusBox->AttachPane(this,true);
	mFocusBox->Hide();
}

LPxmView::~LPxmView()
{
	//delete mFocusBox;
}

// ---------------------------------------------------------------------------
//	€ GetPictureID													  [public]
// ---------------------------------------------------------------------------
//	Return the PICT Resource ID associated with a Picture
//	Defined inline in header

#pragma mark LPxmView::GetPxmResource

void
LPxmView::GetPxmResourceSpec(FullResourceSpec &outSpec) const
{
	TPxmEditDialogBox* theDialog = dynamic_cast<TPxmEditDialogBox*>(mSuperView);
	SignalIf_(theDialog == NULL);
	theDialog->GetPxmResourceSpec(outSpec);
}

// ---------------------------------------------------------------------------
//	€ SetPictureID													  [public]
// ---------------------------------------------------------------------------
//	Set the PICT Resource ID associated with a Picture
//
//	This changes size of the Image to match the bounds of the PICT.

void
LPxmView::SetPxmResource(CTPxmResource *inPxm)
{
	mPxm = inPxm;
	if(mPxm != NULL)
	{
		Rect theBounds;
		mPxm->GetBounds(theBounds);
		ResizeImageTo(theBounds.right - theBounds.left,
					  theBounds.bottom - theBounds.top, false);
		Refresh();
	}
}

// ---------------------------------------------------------------------------
//	€ SetPxmViewType													  [public]
// ---------------------------------------------------------------------------
//	Set the PICT Resource ID associated with a Picture
//
//	This changes size of the Image to match the bounds of the PICT.

void
LPxmView::SetPxmViewType(
	PxmViewType inType)
{
	mPxmViewType = inType;
	Refresh();
}


// ---------------------------------------------------------------------------
//	€ DrawSelf													   [protected]
// ---------------------------------------------------------------------------
//	Draw a Picture

void
LPxmView::DrawSelf()
{
	// If Picture resource exists, draw it. Otherwise, fill the
	// Frame with a light gray pattern and a one-pixel border.
	FocusDraw();
	if (mPxm != nil) 
	{
		Rect theBounds;
		mPxm->GetBounds(theBounds);
		
		
		
		
		Rect theLocalRect;
		CalcLocalFrameRect(theLocalRect);
		EraseRect(&theLocalRect);
		FrameRect(&theLocalRect);
		GrafPtr thePort = GetMacPort();

		Rect placeRect;
		placeRect.left = theLocalRect.left + ((theLocalRect.right - theLocalRect.left) / 2) - ((theBounds.right - theBounds.left) / 2);
		placeRect.right = placeRect.left + (theBounds.right - theBounds.left);
		placeRect.top = theLocalRect.top + ((theLocalRect.bottom - theLocalRect.top) / 2) - ((theBounds.bottom - theBounds.top) / 2);
		placeRect.bottom = placeRect.top + (theBounds.bottom - theBounds.top);
		
		placeRect.right += ((theBounds.right - theBounds.left) % 2);
		placeRect.bottom += ((theBounds.bottom - theBounds.top) % 2);
		
		switch(mPxmViewType)
		{
			case kImageView:
			{
				mPxm->CopyFromImage((GWorldPtr)thePort,placeRect,mIndex);
			}
			break;
			
			case kMaskView:
			{
				mPxm->CopyFromMask((GWorldPtr)thePort,placeRect,mIndex);
			}
			break;
			
			case kImageMaskView:
			
			{
				mPxm->CopyFromMaskedImage((GWorldPtr)thePort,placeRect,mIndex);
			}
			break;
			
			default:
			{
				SignalIf_(true);
			}
			break;
		}
	} 
	else 
	{
		Rect	frame;
		CalcLocalFrameRect(frame);
		::PenNormal();
		::MacFillRect(&frame, &UQDGlobals::GetQDGlobals()->ltGray);
		::MacFrameRect(&frame);
	}
}

// ---------------------------------------------------------------------------
//	€ ItemIsAcceptable
// ---------------------------------------------------------------------------
//	DragManager item is acceptable if it has data of PICT and we're not of type
// ImageMaskView

Boolean
LPxmView::ItemIsAcceptable(
	DragReference	inDragRef,
	ItemReference	inItemRef)
{
	FlavorFlags		theFlags;
	return (mPxmViewType != kImageMaskView) && (GetFlavorFlags(inDragRef, inItemRef, kPictDragFlavor, &theFlags)
					== noErr);
}

// ---------------------------------------------------------------------------
//	€ ReceiveDragItem
// ---------------------------------------------------------------------------
//	DragManager item is acceptable if it has data of PICT

void	LPxmView::ReceiveDragItem(
	DragReference	 inDragRef,
	DragAttributes	 /*inDragAttrs*/,
	ItemReference	 inItemRef,
	Rect&			 /*inItemBounds*/)	// In Local coordinates
{
	UInt16 flavorCount;
	::CountDragItemFlavors(inDragRef, inItemRef, &flavorCount);
	for(UInt32 i = 1; i <= flavorCount; i++)
	{
		OSType theType;
		if(::GetFlavorType(inDragRef, inItemRef, i, &theType) == noErr)
		{
			if(theType == kPictDragFlavor)
			{
				Size theSize;
				if(GetFlavorDataSize(inDragRef, inItemRef, theType, &theSize) == noErr)
				{
					Handle thePic = NewHandle(theSize);
					if(MemError() == noErr)
					{
						HLock(thePic);
						if(GetFlavorData(inDragRef, inItemRef, theType, *thePic, &theSize, 0) == noErr)
						{
							PictToPxm((PicHandle)thePic);
							BroadcastMessage(mMessage,this);
							Refresh();
						}
						HUnlock(thePic);
						DisposeHandle(thePic);
					}
				}
				break;
			}
		}
	}
}

void		LPxmView::ClickSelf(
								const SMouseDownEvent &inMouseDown)
{
	if (GetClickCount() == 1) 
	{
	
		if (LDragAndDrop::DragAndDropIsPresent() &&
			::WaitMouseMoved(inMouseDown.macEvent.where)) 
		{
			
			FocusDraw();
			
			Rect theBounds;
			mPxm->GetBounds(theBounds);

			Rect theLocalRect;
			CalcLocalFrameRect(theLocalRect);
			EraseRect(&theLocalRect);
			FrameRect(&theLocalRect);
			GrafPtr thePort = GetMacPort();

			Rect placeRect;
			placeRect.left = theLocalRect.left + ((theLocalRect.right - theLocalRect.left) / 2) - ((theBounds.right - theBounds.left) / 2);
			placeRect.right = placeRect.left + (theBounds.right - theBounds.left);
			placeRect.top = theLocalRect.top + ((theLocalRect.bottom - theLocalRect.top) / 2) - ((theBounds.bottom - theBounds.top) / 2);
			placeRect.bottom = placeRect.top + (theBounds.bottom - theBounds.top);
			
			placeRect.right += ((theBounds.right - theBounds.left) % 2);
			placeRect.bottom += ((theBounds.bottom - theBounds.top) % 2);
		
			::LocalToGlobal(&topLeft(placeRect));
			::LocalToGlobal(&botRight(placeRect));
			
			Handle thePic = NULL;
			PxmToPict((PicHandle)thePic);
			HLock(thePic);
			LDragTask	theDragTask(inMouseDown.macEvent);
			StRegion	outerRgn(placeRect);	// Make region containing item
	
			StRegion	innerRgn = outerRgn;	// Carve out interior of region so
			::InsetRgn(innerRgn, 1, 1);			//   that it's just a one-pixel thick
			outerRgn -= innerRgn;				//   outline of the item rectangle
			
			StRegion theRgn(theDragTask.GetDragRegion(),false);
			theRgn += outerRgn;			// Accumulate this item in our
																//   total drag region
			
												// Tell Drag Manager about this item
			::SetDragItemBounds(theDragTask.GetDragReference(), 1, &placeRect);
			::AddDragItemFlavor(theDragTask.GetDragReference(),  1, kPictDragFlavor,*thePic, GetHandleSize(thePic), 0);
			
			PxmDragRecord theDragRec;
			GetPxmResourceSpec (theDragRec.pxmSpec);
			theDragRec.index = mIndex - 1;
			SignalIf_(theDragRec.index < 0);
			::AddDragItemFlavor(theDragTask.GetDragReference(), 1,kPxmDragFlavor,&theDragRec, sizeof(PxmDragRecord),0);
			
			theDragTask.DoDrag();
			HUnlock(thePic);
			DisposeHandle(thePic);	
			Refresh();				
			OutOfFocus(nil);
		
		}
		else
		{
			SwitchTarget(this);
		}
	}
	else if(GetClickCount() == 2)
	{
		ImportPictFile();
	}
}

OSErr LPxmView::PictToPxm(PicHandle inPic)
{
	OSErr theErr = noErr;
	
	switch(mPxmViewType)
	{
		case kImageView:
		{
			theErr = mPxm->PictToImage(inPic,mIndex,UsePictRectAlert());
		}
		break;
		
		case kMaskView:
		{
			theErr = mPxm->PictToMask(inPic,mIndex,UsePictRectAlert());
		}
		break;
		
		default:
		{
			SignalIf_(true);
		}
		break;
	}
	
	return theErr;
}

OSErr LPxmView::PxmToPict(PicHandle &outPic)
{
	SignalIfNot_(outPic == NULL);
	
	OSErr theErr = noErr;
	switch(mPxmViewType)
	{
		case kImageView:
		{
			theErr = mPxm->PictFromImage((PicHandle)outPic,mIndex);
		}
		break;
		
		case kMaskView:
		{
			theErr = mPxm->PictFromMask((PicHandle)outPic,mIndex);
		}
		break;
		
		case kImageMaskView:
		{
			theErr = mPxm->PictFromMaskedImage((PicHandle)outPic,mIndex);
		}
		break;
		
		default:
		{
			SignalIf_(true);
		}
		break;
	}
	return theErr;
}

void LPxmView::ImportPictFile()
{
	if(mPxmViewType != kImageMaskView)
	{
		PP_StandardDialogs::LFileChooser	chooser;
		LFileTypeList theList(kPictDragFlavor);
		FSSpec theSpec;
		
		NavDialogOptions* theOptions = chooser.GetDialogOptions();
		theOptions->dialogOptionFlags = kNavNoTypePopup + kNavDontAddTranslateItems + kNavSelectAllReadableItem;
		if (chooser.AskChooseOneFile(theList,theSpec)) 
		{
			PicHandle thePic = NULL;
			if(UTPixUtilities::PictFileToPict(theSpec,thePic) == noErr)
			{
				PictToPxm(thePic);
				BroadcastMessage(mMessage,this);
				Refresh();
			}
			HUnlock((Handle)thePic);
			DisposeHandle((Handle)thePic);
		}
	}
}

void LPxmView::ExportPictFile()
{
}

void LPxmView::SetIndex(SInt16 inIndex)
{ 
	mIndex = inIndex; 
	if(mIndex < 1)
	{
		mIndex = 1;
	}
	else if(mIndex > mPxm->GetImageCount())
	{
		mIndex = mPxm->GetImageCount();
	}
	Refresh(); 
}

SInt16	LPxmView::GetMaxIndex()
{
	return mPxm->GetImageCount();
}

// ---------------------------------------------------------------------------
//	€ BeTarget												   	[protected]
// ---------------------------------------------------------------------------

void		
LPxmView::BeTarget()
{
	mFocusBox->Show();
}

// ---------------------------------------------------------------------------
//	€ DontBeTarget												   	[protected]
// ---------------------------------------------------------------------------

void		
LPxmView::DontBeTarget()
{
		mFocusBox->Hide();
}

#pragma mark -
#pragma mark === COMMANDS

// ---------------------------------------------------------------------------
//	€ FindCommandStatus												  [public]
// ---------------------------------------------------------------------------

void
LPxmView::FindCommandStatus(
	CommandT	inCommand,
	Boolean&		outEnabled,
	Boolean&		outUsesMark,
	UInt16&		outMark,
	Str255			outName)
{
			
	switch(inCommand)
	{
		case cmd_Copy:
			outEnabled = true;
			break;
			
		case cmd_Paste:
			LClipboard* theClip = LClipboard::GetClipboard();
			outEnabled = (theClip->GetData('PICT',NULL) > 0) && (mPxmViewType != kImageMaskView);
			break;
			
		default:
			LCommander::FindCommandStatus( inCommand,
			outEnabled, outUsesMark, outMark, outName );
	}
				
}


// ---------------------------------------------------------------------------
//	€ ObeyCommand												  [public]
// ---------------------------------------------------------------------------

Boolean
LPxmView::ObeyCommand(
	CommandT	inCommand,
	void			*ioParam )
{
	Boolean		cmdHandled = true;

		 
	switch (inCommand) {
		
		case cmd_Copy:
		{
			cmdHandled = true;
			
			PicHandle thePict = NULL;
			if(PxmToPict(thePict) == noErr)
			{
				LClipboard::GetClipboard()->SetData('PICT', (Handle)thePict,true);
				DisposeHandle((Handle)thePict);
			}
		}
		break;
		
		case cmd_Paste:
		{
			cmdHandled = true;
			
			if(LClipboard::GetClipboard()->GetData('PICT',NULL) > 0)
			{
				Handle thePicture = NewHandle(1);
				if(LClipboard::GetClipboard()->GetData('PICT',thePicture) > 0)
				{
					PictToPxm((PicHandle)thePicture);
					BroadcastMessage(mMessage,this);
					Refresh();
				}
				DisposeHandle(thePicture);
			}
		}
		break;
		
		default: {
			cmdHandled = LCommander::ObeyCommand(inCommand,ioParam);
			break;
		}
	}
	return cmdHandled;
}

Boolean
LPxmView::UsePictRectAlert()
{
	LStr255 theError(304,1);
	LStr255 theOKText(304,2);
	LStr255 theCancelText(304,3);
	AlertStdAlertParamRec theRec = {false,false,NULL,theOKText,theCancelText,NULL,kAlertStdAlertOKButton,kAlertStdAlertCancelButton,kWindowDefaultPosition};
	SInt16 itemHit;
	StandardAlert(kAlertPlainAlert,(ConstStringPtr)theError,"\p",&theRec,&itemHit);
	return itemHit = kAlertStdAlertOKButton;
}