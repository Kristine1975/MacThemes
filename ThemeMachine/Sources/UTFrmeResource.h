// ===========================================================================
//	UTFlacResource.h			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the clr# resource
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Dec 22/98 Initial Implementation
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


#ifndef _H_UTFrmeResource
#define _H_UTFrmeResource
#pragma once

#include "UTResource.h"
#include <Collections.h>

class CThemeDoc;

#define kFrmeResourceType 'frme'
enum
{
	frameOriginRightTop = 0x00,
	frameOriginLeftTop =  0x40,
	frameOriginRightBottom =  0x80,
	frameOriginLeftBottom =  0xC0
};	

typedef UInt8 FrameOrigin;
typedef SInt8 FrameInset;

enum FrameType
{
	kType2Frame = 2,
	kType3Frame = 3
};

enum FrameSide
{
	kLeftSide,
	kTopSide,
	kRightSide,
	kBottomSide
};

class FrameEntry
{
	public:
	FrameEntry();
	
	void Read(Ptr &inPtr);
	void Write(Ptr &outPtr);
	UInt32 GetSize();

	FrameType mType;	
	FrameOrigin mPatternOrigin;
	FrameInset mInset;
	PlutEntryIndex mPlutIndex;
	Boolean mPixels[64];
};

#if PRAGMA_STRUCT_ALIGN
	#pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
	#pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
	#pragma pack(2)
#endif

typedef struct
{
	SInt16 type;
	SInt16 unknown1;
	FrameOrigin  patternOrigin;
	FrameInset  minimumInset;
	SInt8  unknown2;
	FrameInset  maximumInset;
	ResID  backgroundPlutID;
	SInt16 frameCount;
} FrameHeaderResource, *FrameHeaderResourcePtr, **FrameHeaderResourceHandle;

typedef struct
{
	FrameOrigin  patternOrigin;
	SInt8  inset;
	ResID  plutIndex;
	UInt8 leftSide;
	UInt8 topSide;
	UInt8 rightSide;
	UInt8 bottomSide;
} FrameEntry2Resource, *FrameEntry2ResourcePtr, **FrameEntry2ResourceHandle;

typedef struct
{
	FrameOrigin  patternOrigin;
	FrameInset  inset;
	ResID  plutIndex;
	UInt16 leftSide;
	UInt16 topSide;
	UInt16 rightSide;
	UInt16 bottomSide;
} FrameEntry3Resource, *FrameEntry3ResourcePtr, **FrameEntry3ResourceHandle;


#if PRAGMA_STRUCT_ALIGN
	#pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
	#pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
	#pragma pack()
#endif

// ---------------------------------------------------------------------------

class	UTFrmeResource : public UTResource
{
public:
	UTFrmeResource();							
	virtual ~UTFrmeResource();
	void Init(ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true,
					ResType			inResType = kFrmeResourceType);
			
	virtual Handle 	BuildBaseResource();	
	virtual void	Write(Boolean			inUpdateResFile = true);
	virtual void	Dispose();
	
	FrameType 	GetType();
	void SetType(FrameType theType);
	UInt32 		GetFrameCount();
	void FetchFrameAt(ArrayIndexT inIndex, FrameEntry* &outEntry);
	void RemoveFrameAt(ArrayIndexT inIndex);
	void		AddFrame(FrameEntry* inFrame);
	void		InsertFrameAt(FrameEntry* inFrame,ArrayIndexT inIndex); 
	ResID 		GetBackgroundPlutID();
	void 		SetBackgroundPlutID(PlutEntryIndex inPlut);
	SInt8 		GetMinimumInset();
	void 		SetMinimumInset(SInt8 inInset);
	SInt8 		GetMaximumInset();
	void 		SetMaximumInset(SInt8 inInset);
	FrameOrigin	GetPatternOrigin();
	void		SetPatternOrigin(FrameOrigin inOrigin);
	
	void PaintRect(Rect &inRect, CThemeDoc *inDoc);
	
protected:
	
	operator Handle()	{ return mResourceH; }
				
	Handle	Get()		{ return mResourceH; }

	
	
private:
	FrameType mType;
	SInt16 mUnknown1;
	FrameOrigin  mPatternOrigin;
	SInt8  mMinimumInset;
	SInt8  mUnknown2;
	SInt8  mMaximumInset;
	PlutEntryIndex  mBackgroundPlutID;
	#pragma warn_hidevirtual off	
	TArray<FrameEntry*> mFrames;
	#pragma warn_hidevirtual reset
};

typedef struct
{
	FullResourceSpec frmeSpec;
} FrmeDragRecord;
#endif
