#ifndef APPEARANCE_IMAGE_COMPONENT_H
#define APPEARANCE_IMAGE_COMPONENT_H

#if PRAGMA_ONCE
#pragma once
#endif

#include "TThemes.h"
/*
	CTPxmResource is the class equivalent of a "pxm#" resource.
	It provides methods for drawing the various pixmaps contained in the relvant resource.
*/

//#define AICDEBUG 1

class UTClut;
class PXMHeader
{
	public:
	SInt16 mUnknown1;
	SInt16 mMaskCount;
	Rect mBounds;
	SInt16 mPixelDepth;
	SInt16 mUnknown2;
	SInt16 mUnknown3;
	SInt16 mUnknown4;
	SInt16 mCTSeedValue;
	SInt16 mImageCount;	
	
	PXMHeader()
	{
		mUnknown1 = 1;
		mMaskCount = mUnknown2 = 0;
		mUnknown3 = mUnknown4 = mCTSeedValue = mImageCount = 0; 
		mPixelDepth = 1;
		mBounds.left = mBounds.top = 0;
		mBounds.right = mBounds.bottom = 32;
	}
}; 
	

class CTPxmResource
{											
	public:
	CTPxmResource(const Handle inRawData);
	CTPxmResource(FullResourceSpec &inSpec);
	CTPxmResource();
	virtual ~CTPxmResource(void);
	
	SInt16 GetImageCount(void) const;
	SInt16 GetMaskCount(void) const;
	void SetImageCount(SInt16 inImageCount);
	void SetMaskCount(SInt16 inMaskCount);
	
	void GetBounds(Rect &bounds) const;
	void SetBounds(const Rect &inBounds);
	
	SInt16 GetCLUTID();
	void SetCLUTID(SInt16 inID);
	
	SInt16 GetPixelDepth();
	void SetPixelDepth(SInt16 newPixDepth);
	
	void PaintRect(Rect &inRect, ImageAlignment inAlignment, SInt16 index);
	
	void CopyFromMask(GWorldPtr inGWorld, const Rect &where, SInt16 index);
	void CopyFromImage(GWorldPtr inGWorld,const Rect &where, SInt16 index);
	void CopyFromMaskedImage(GWorldPtr inGWorld,const Rect &where, SInt16 index);
	OSErr PictFromMask(PicHandle &outPic, SInt16 index);
	OSErr PictFromImage(PicHandle &outPic, SInt16 index);
	OSErr PictFromMaskedImage(PicHandle &outPic, SInt16 index);
	void CopyToMask(GWorldPtr inGWorld,const Rect &where, SInt16 index, Boolean inUseGWorldRect);
	void CopyToImage(GWorldPtr inGWorld,const Rect &where, SInt16 index, Boolean inUseGWorldRect);
	OSErr PictToMask(PicHandle inPic, SInt16 inIndex, Boolean inUseGWorldRect);
	OSErr PictToImage(PicHandle inPic, SInt16 inIndex, Boolean inUseGWorldRect);
	OSErr PixPatFromMaskedImage(PixPatHandle &outPixPat, SInt16 index);
	
	OSErr CreateFromHandle(const Handle inRawData);
	void WriteToHandle(Handle ioRawData);
 	CTabHandle GetAssociatedColorTable(void);

 	private:
	void Init();
	enum
	{
		kSameAsImageCounter = (SInt16)0
	};
	
	void UpdateGWorlds();
	void UpdateDatas(const Rect &inNewBounds, const SInt16 inNewPixDepth);
	
								
	bool CreateDefaultOffscreenWorlds();

	bool CreateOffscreenWorlds(GWorldPtr &outImageGWorld, 
					GWorldPtr &outMaskGWorld, 
					const Rect &inBounds,
					const SInt16 inDepth);
					
	void DeleteOffscreenWorlds(void);
							
	void CopyDataToGWorld(UInt8 *inBuffer, const GWorldPtr inGWorld, UInt32 inRowBytes, UInt32 inSize);
	void CopyIndexedHandleToGWorld(Handle inData, SInt16 inIndex, const GWorldPtr inGWorld, UInt32 inRowBytes, UInt32 inSize);
	void CopyMaskToMaskGWorld(SInt16 inIndex);
	void CopyImageToImageGWorld(SInt16 inIndex);
	
	void CopyGWorldToData(UInt8 *inBuffer, const GWorldPtr inGWorld, UInt32 inRowBytes, UInt32 inSize);
	void CopyGWorldToIndexedHandle(Handle inData, SInt16 inIndex, const GWorldPtr inGWorld, UInt32 inRowBytes, UInt32 inSize);
	void CopyMaskGWorldToMask(SInt16 inIndex);
	void CopyImageGWorldToImage(SInt16 inIndex);

	SInt32 GetPixMapRowBytes(const Rect &inRect, const SInt16 inPixelDepth);
	SInt32 GetPixMapSize(const Rect &inRect, const SInt16 inPixelDepth);

	
	
	
	void CalculateRowBytesAndSizes(SInt32 *outMaskRowBytes, SInt32 *outImageRowBytes, SInt32 *outMaskSize, SInt32 *outImageSize);
	SInt32 GetMaskRowBytes();
	SInt32 GetImageRowBytes();
	SInt32 GetMaskSize();
	SInt32 GetImageSize();
	SInt32 GetMaskGWorldRowBytes();
	SInt32 GetImageGWorldRowBytes();
	SInt32 GetMaskGWorldSize();
	SInt32 GetImageGWorldSize();
	
	PXMHeader					mHeader;
	CTabHandle					mColorTable;
	Handle						mMaskData;
	GWorldPtr					mMaskGWorld;	
	Handle						mImageData;
	GWorldPtr					mImageGWorld;	
	
	#ifdef AICDEBUG
	void DebugBlit();
	WindowPtr					mDebugWindow;
	#endif
};

typedef struct
{
	FullResourceSpec pxmSpec;
	UInt32 index;
} PxmDragRecord;

#endif APPEARANCE_IMAGE_COMPONENT_H