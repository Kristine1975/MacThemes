// ===========================================================================
//	TPxmEditDialogBox.cp	©1999 Allegro Themes Project
// ===========================================================================
//	Author: Dave MacLachlan
//
//	A single column table for showing and editing brush resources. 
//
// --------------------------------------------------------------
// Theme Machine - A Theme Editor For MacOS
//	Copyright (C) 1999  Allegro Themes Project

//	This program is free software; you can redistribute it and/or
//	modify it under the terms of the GNU General Public License
//	as published by the Free Software Foundation; either version 2
//	of the License, or (at your option) any later version.

//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.

//	You should have received a copy of the GNU General Public License
//	along with this program; if not, write to the Free Software
//	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// To contact the authors 
// mail - macthemes@onelist.com
// --------------------------------------------------------------

#include "TPxmEditDialogBox.h"
#include <LPushButton.h>
#include "UTPixUtilities.h"
#include "LPXMView.h"
#include "CTPxmResource.h"
#include "TClutTable.h"
#include "UTClut.h"
#include <UStandardDialogs.h>
#include <LFileStream.h>
#include <LStaticText.h>
#include <UResourceMgr.h>
// ---------------------------------------------------------------------------

const PaneIDT	kLoadImageButtonID = 'LOIM';
const PaneIDT	kSaveImageButtonID = 'SAIM';
const PaneIDT	kLoadMaskButtonID = 'LOMA';
const PaneIDT	kSaveMaskButtonID = 'SAMA';
const PaneIDT	kNextButtonID = 'NEXT';
const PaneIDT	kPrevButtonID = 'PREV';
const PaneIDT	kImportCLUTButtonID = 'IMCL';
const PaneIDT	kExportCLUTButtonID = 'EXCL';

const PaneIDT	kImageViewID = 'IMAG';
const PaneIDT	kMaskViewID = 'MASK';
const PaneIDT	kMaskedImageViewID = 'MAIM';
const PaneIDT	kColorTableID = 'CLTA';

const PaneIDT	kHeightStaticID = 'HGHT';
const PaneIDT	kWidthStaticID = 'WDTH';
const PaneIDT	kXofYStaticID = 'XOFY';
const PaneIDT	kYofYStaticID = 'YOFY';
const PaneIDT TPxmEditDialogBox::kPxmEditOKID = 'OKOK';
const PaneIDT TPxmEditDialogBox::kPxmEditCancelID = 'CANC';
const MessageT TPxmEditDialogBox::kPxmEditOK = -77;
const MessageT TPxmEditDialogBox::kPxmEditCancel = -78;


TPxmEditDialogBox::TPxmEditDialogBox()
{
}
				
TPxmEditDialogBox::TPxmEditDialogBox(LStream*		inStream) : TEditorDialogBox(inStream)
{
}


TPxmEditDialogBox::~TPxmEditDialogBox()
{
}
								
void		TPxmEditDialogBox::ListenToMessage(MessageT		inMessage,void*			ioParam)
{
	
	switch(inMessage)
	{
		case kLoadImageButtonID:
		{
			mImageView->ImportPictFile();
		}
		break;
		
		case kSaveImageButtonID:
		{
			mImageView->ExportPictFile();
		}
		break;
		case kLoadMaskButtonID:
		{
			mMaskView->ImportPictFile();
		}
		break;
		case kSaveMaskButtonID:
		{
			mMaskView->ExportPictFile();
		}
		break;
		
		case kNextButtonID:
		{
			SInt16 newIndex = mImageView->GetIndex() + 1;
			mImageView->SetIndex(newIndex);
			mMaskView->SetIndex(newIndex);
			mMaskedImageView->SetIndex(newIndex);
			UpdateIndexStatics();
			UpdateIndexButtons();
		}		
		break;
		
		case kPrevButtonID:
		{
			SInt16 newIndex = mImageView->GetIndex() - 1;
			mImageView->SetIndex(newIndex);
			mMaskView->SetIndex(newIndex);
			mMaskedImageView->SetIndex(newIndex);
			UpdateIndexStatics();
			UpdateIndexButtons();
		}		
		break;
		
		case kMaskViewID:
		case kImageViewID:
		{
			Refresh();
			UpdateSizeStatics();
			SetIsModified();
		}
		break;
	
		
		default:
		{
			LDialogBox::ListenToMessage(inMessage,ioParam);
			break;
		}
	}
}

void		TPxmEditDialogBox::FinishCreateSelf()
{
	LDialogBox::FinishCreateSelf();
	mImageView = (LPxmView*)FindPaneByID(kImageViewID);
	ThrowIfNil_(mImageView);
	mMaskView = (LPxmView*)FindPaneByID(kMaskViewID);
	ThrowIfNil_(mMaskView);
	mMaskedImageView = (LPxmView*)FindPaneByID(kMaskedImageViewID);
	ThrowIfNil_(mMaskedImageView);
	
	LPushButton* theButton  = (LPushButton*)FindPaneByID(kLoadImageButtonID);
	ThrowIfNil_(theButton);
	theButton->AddListener(this);
	
	theButton  = (LPushButton*)FindPaneByID(kSaveImageButtonID);
	ThrowIfNil_(theButton);
	theButton->AddListener(this);
	
	theButton  = (LPushButton*)FindPaneByID(kLoadMaskButtonID);
	ThrowIfNil_(theButton);
	theButton->AddListener(this);
	
	theButton  = (LPushButton*)FindPaneByID(kSaveMaskButtonID);
	ThrowIfNil_(theButton);
	theButton->AddListener(this);
	
	theButton  = (LPushButton*)FindPaneByID(kNextButtonID);
	ThrowIfNil_(theButton);
	theButton->AddListener(this);
	
	theButton  = (LPushButton*)FindPaneByID(kPrevButtonID);
	ThrowIfNil_(theButton);
	theButton->AddListener(this);
	
	mImageView->AddListener(this);
	mMaskView->AddListener(this);
	mMaskedImageView->AddListener(this);

}

void		TPxmEditDialogBox::SetPxmResource(const FullResourceSpec &inPxmSpec)
{
	mPxmSpec = inPxmSpec;
	
	StCurResFile(mPxmSpec.fileID);
	SignalIf_(mPxmSpec.resType != 'pxm#');
	
	Handle thePxm = GetResource(mPxmSpec.resType,mPxmSpec.resID);
	SignalIf_(thePxm == NULL);
	
	ResID theID;
	OSType theType;
	LStr255 theName;
	
	GetResInfo(thePxm, &theID, &theType, theName);
	SetDescriptor(theName);
	
	mPxm.CreateFromHandle(thePxm);
	ReleaseResource(thePxm);
	mImageView->SetPxmResource(&mPxm);
	mMaskView->SetPxmResource(&mPxm);
	mMaskedImageView->SetPxmResource(&mPxm);
	UpdateIndexStatics();
	UpdateSizeStatics();
	UpdateIndexButtons();
}

void	TPxmEditDialogBox::GetPxmResourceSpec(FullResourceSpec &outSpec)
{
	outSpec = mPxmSpec;
}

void		TPxmEditDialogBox::UpdateIndexStatics()
{
	LStaticText* theText = (LStaticText*)FindPaneByID(kXofYStaticID);
	theText->SetValue(mImageView->GetIndex());
	
	theText = (LStaticText*)FindPaneByID(kYofYStaticID);
	theText->SetValue(mPxm.GetImageCount());
}

void		TPxmEditDialogBox::UpdateSizeStatics()
{
	
	Rect theBounds;
	mPxm.GetBounds(theBounds);
	
	LStaticText* theText = (LStaticText*)FindPaneByID(kHeightStaticID);
	theText->SetValue(theBounds.bottom - theBounds.top);
	
	theText = (LStaticText*)FindPaneByID(kWidthStaticID);
	theText->SetValue(theBounds.right - theBounds.left);
}

void		TPxmEditDialogBox::UpdateIndexButtons()
{
	LPushButton *theButton  = (LPushButton*)FindPaneByID(kNextButtonID);
	ThrowIfNil_(theButton);
	if(mImageView->GetIndex() == mPxm.GetImageCount())
	{
		theButton->Disable();
	}
	else
	{
		theButton->Enable();
	}
	
	theButton  = (LPushButton*)FindPaneByID(kPrevButtonID);
	ThrowIfNil_(theButton);
	if(mImageView->GetIndex() == 1)
	{
		theButton->Disable();
	}
	else
	{
		theButton->Enable();
	}
}

void TPxmEditDialogBox::DoSave()
{
	StCurResFile(mPxmSpec.fileID);
	SignalIf_(mPxmSpec.resType != 'pxm#');
	
	Handle thePxm = GetResource( mPxmSpec.resType, mPxmSpec.resID);
	SignalIf_(thePxm == NULL);
	mPxm.WriteToHandle(thePxm);
	ChangedResource(thePxm);
	WriteResource(thePxm);
}

