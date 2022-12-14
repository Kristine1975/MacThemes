#include "CTPxmResource.h"
#include <UMemoryMgr.h>

#ifndef __QDOFFSCREEN__
#include <QDOffscreen.h>
#endif

#include <UException.h>
#include "UTPixUtilities.h"
#include "UDrawingState.h"

#pragma mark === Initializers
CTPxmResource::CTPxmResource(const Handle	inRawData)
{
	Init();
	CreateFromHandle( inRawData );
}

CTPxmResource::CTPxmResource(FullResourceSpec &inSpec)
{
	Init();
	UseResFile(inSpec.fileID);
	Handle theHand = GetResource(inSpec.resType,inSpec.resID);
	if(theHand != NULL)
	{
		CreateFromHandle(theHand);
		ReleaseResource(theHand);
	}
}

CTPxmResource::CTPxmResource()
{
	Init();
}

void CTPxmResource::Init()
{
	mMaskData = NULL;
	mImageData = NULL;
	mColorTable = NULL;
	mMaskGWorld = NULL;
	mImageGWorld = NULL;
	
	
	#ifdef AICDEBUG
		Rect theRect = {30,30,130,130};
		mDebugWindow = NewWindow(NULL,&theRect,"\pAICDebug",TRUE,0,(WindowPtr)(-1L),TRUE,NULL);
	#endif
	
	CreateDefaultOffscreenWorlds();
	
}

						
CTPxmResource::~CTPxmResource(void)
{
	if( mColorTable )
	{
		DisposeCTable(mColorTable);
	}
	
	DisposeHandle( mImageData );
	DisposeHandle( mMaskData );
	DeleteOffscreenWorlds();
	
	#ifdef AICDebug
		DisposeWindow(myWindow);
	#endif
}

#pragma mark -
#pragma mark === Debugging
#ifdef AICDEBUG
void CTPxmResource::DebugBlit()
{
	PixMapHandle pixels = GetGWorldPixMap(mImageGWorld);
	if(LockPixels(pixels))
	{
		CopyBits(&((GrafPtr)mImageGWorld)->portBits,&((GrafPtr)mDebugWindow)->portBits,&mHeader.mBounds,&mHeader.mBounds,srcCopy,NULL);
		UnlockPixels(pixels);
	}
	pixels = GetGWorldPixMap(mMaskGWorld);
	if(LockPixels(pixels))
	{
		CopyBits(&((GrafPtr)mMaskGWorld)->portBits,&((GrafPtr)mDebugWindow)->portBits,&mHeader.mBounds,&mHeader.mBounds,srcCopy,NULL);
		UnlockPixels(pixels);
	}
}
#endif

#pragma mark -
#pragma mark === Getters and Setters
SInt16	CTPxmResource::GetImageCount(void) const
{
	return mHeader.mImageCount;
}

SInt16	CTPxmResource::GetMaskCount(void) const
{
	return mHeader.mMaskCount;
}

void	CTPxmResource::SetImageCount(SInt16 inCount) 
{
	mHeader.mImageCount = inCount;
	if(mImageData == NULL)
	{
		mImageData = NewHandle(GetImageSize() * inCount);
	}
	else
	{
		SetHandleSize(mImageData,GetImageSize() * inCount);
	}
	ThrowIfMemError_();
	
	//ToDo: Clear out all the new Images
}

void	CTPxmResource::SetMaskCount(SInt16 inCount) 
{
	mHeader.mMaskCount = inCount;
	if(mMaskData == NULL)
	{
		mMaskData = NewHandle(GetMaskSize() * inCount);
	}
	else
	{
		SetHandleSize(mMaskData,GetMaskSize() * inCount);
	}
	ThrowIfMemError_();
	
	//ToDo: Clear out all the new Images
}

void CTPxmResource::GetBounds(Rect &outBounds) const
{	
	outBounds = mHeader.mBounds;
}

void CTPxmResource::SetBounds(const Rect &inBounds)
{
	UpdateDatas(inBounds,GetPixelDepth());
}

SInt16 CTPxmResource::GetCLUTID()
{
	return mHeader.mCTSeedValue;
}

void  CTPxmResource::SetCLUTID(SInt16 /*inID*/)
{
	 /*mHeader.mCTSeedValue = inID;
	 CTabHandle oldTable = mColorTable;
	
	 mColorTable = GetAssociatedColorTable();
	 
	 for(int  i = 0; i < mHeader.mImageCount; i++)
	 {
	 	CopyImageToImageGWorld(i);
	 	UpdateGWorld( &mImageGWorld, mHeader.mPixelDepth, &mHeader.mBounds, mColorTable, 0, clipPix );
	 	CopyImageGWorldToImage(i);
	 	UpdateGWorld( &mImageGWorld, mHeader.mPixelDepth, &mHeader.mBounds, oldTable, 0, clipPix );
		ThrowIfQDError_();
	 }
	 UpdateGWorld( &mImageGWorld, mHeader.mPixelDepth, &mHeader.mBounds, mColorTable, 0, clipPix );
	 if(oldTable != NULL)
	 {
	 	DisposeCTable(mColorTable);
	 }*/
}

SInt16 CTPxmResource::GetPixelDepth()
{
	return mHeader.mPixelDepth;
}

void CTPxmResource::SetPixelDepth(SInt16 newPixDepth)
{
	Rect theBounds;
	GetBounds(theBounds);
	UpdateDatas(theBounds,newPixDepth);
}


OSErr CTPxmResource::CreateFromHandle(const Handle inRawData)
{
	StHandleLocker h(inRawData );
	UInt32 size = GetHandleSize( inRawData );
	UInt8 *thePtr = ((UInt8*)(*inRawData));
	
	
	if(size < sizeof(PXMHeader) )
	{
		return pictureDataErr;
	}

	mHeader = *((PXMHeader*)thePtr);
	thePtr += sizeof(PXMHeader);
	
	mHeader.mMaskCount = (mHeader.mMaskCount == kSameAsImageCounter) ? mHeader.mImageCount : mHeader.mMaskCount;
	
	mColorTable = GetAssociatedColorTable();	
	
	SetMaskCount(mHeader.mMaskCount);
	SetImageCount(mHeader.mImageCount);
	SInt32 theMaskSize = GetMaskSize();
	SInt32 theImageSize = GetImageSize();
		
	
	if( size < sizeof(PXMHeader) + (theMaskSize * GetMaskCount()) + (theImageSize * GetImageCount()))
	{
		return pictureDataErr;
	}
	
	{
		StHandleLocker h2( mMaskData );
		BlockMoveData( thePtr, *mMaskData, theMaskSize * GetMaskCount() );
	}
	
	thePtr += theMaskSize * GetMaskCount() ;
	
	{
		StHandleLocker h2( mImageData );
		BlockMoveData( thePtr, *mImageData, theImageSize * GetImageCount() );
	}
	UpdateDatas(mHeader.mBounds,16);
	return noErr;
}


void CTPxmResource::WriteToHandle(Handle ioRawData)
{
	SetHandleSize(ioRawData,sizeof(PXMHeader) + 
					(GetMaskSize() * GetMaskCount()) + 
					(GetImageSize() * GetImageCount()));
	ThrowIfMemError_();
	StHandleLocker h1( ioRawData );
	UInt8* theRawDataPtr = (UInt8*)(*ioRawData);
	
	*((PXMHeader*)theRawDataPtr) = mHeader;
	theRawDataPtr += sizeof(PXMHeader);
	StHandleLocker h2( mMaskData );
	BlockMove(*mMaskData,theRawDataPtr,GetMaskSize() * GetMaskCount());
	theRawDataPtr += GetMaskSize() * GetMaskCount();
	StHandleLocker h3( mImageData );
	BlockMove(*mImageData,theRawDataPtr, GetImageSize() * GetImageCount());	
}


void CTPxmResource::CopyDataToGWorld(UInt8 *inBuffer, const GWorldPtr inGWorld, UInt32 inRowBytes, UInt32 inSize)
{
	PixMapHandle		pixels;
	UInt8*				pixelBuffer;
	UInt32				rowBytes, c, height;
	UInt32 				inHeight = inSize / inRowBytes;

	pixels = GetGWorldPixMap( inGWorld );
	
	if( LockPixels( pixels ) )
	{
		pixelBuffer = (UInt8*)GetPixBaseAddr( pixels );
		rowBytes = GetPixRowBytes( pixels );
		height = (*pixels)->bounds.bottom - (*pixels)->bounds.top;
		
		
		if( rowBytes == inRowBytes && inHeight == height)
		{
			BlockMoveData( inBuffer, pixelBuffer, inSize );
		}
		else
		{
			UInt32 theRowBytes = rowBytes < inRowBytes ? rowBytes : inRowBytes;
			UInt32 theHeight = height < inHeight ? height : inHeight;
			
			for( c = 0; c < theHeight; c++ )
			{
				BlockMoveData( inBuffer, pixelBuffer, theRowBytes );
				
				inBuffer += inRowBytes;
				pixelBuffer += rowBytes;
			}
		}
		
		UnlockPixels( pixels );
		
		#ifdef AICDEBUG
			PixMapHandle pixels = GetGWorldPixMap(inGWorld);
			if(LockPixels(pixels))
			{
				CopyBits(&((GrafPtr)inGWorld)->portBits,&((GrafPtr)mDebugWindow)->portBits,&mHeader.mBounds,&mHeader.mBounds,srcCopy,NULL);
				UnlockPixels(pixels);
			}
		#endif
	}
}

void CTPxmResource::CopyIndexedHandleToGWorld(Handle inData, SInt16 inIndex, const GWorldPtr inGWorld, UInt32 inRowBytes, UInt32 inSize)
{
	CopyDataToGWorld((UInt8*)((UInt32)(*inData) + ((UInt32)(inIndex) * inSize)),inGWorld,inRowBytes,inSize);
}

void CTPxmResource::CopyMaskToMaskGWorld(SInt16 inIndex)
{
	CopyIndexedHandleToGWorld(mMaskData,inIndex,mMaskGWorld,GetMaskRowBytes(),GetMaskSize());
}

void CTPxmResource::CopyImageToImageGWorld(SInt16 inIndex)
{
	CopyIndexedHandleToGWorld(mImageData,inIndex,mImageGWorld,GetImageRowBytes(),GetImageSize());
}
	
void CTPxmResource::CopyGWorldToData(UInt8 *inBuffer, const GWorldPtr inGWorld, UInt32 inRowBytes, UInt32 inSize)
{
	PixMapHandle		pixels;
	UInt8*				pixelBuffer;
	UInt32				rowBytes, c, height;
	UInt32 				inHeight = inSize / inRowBytes;

	pixels = GetGWorldPixMap( inGWorld );
	
	if( LockPixels( pixels ) )
	{
		pixelBuffer = (UInt8*)GetPixBaseAddr( pixels );
		rowBytes = GetPixRowBytes( pixels );
		height = (*pixels)->bounds.bottom - (*pixels)->bounds.top;
		
		
		if( rowBytes == inRowBytes && inHeight == height)
		{
			BlockMoveData( pixelBuffer, inBuffer, inSize );
		}
		else
		{
			UInt32 theRowBytes = rowBytes < inRowBytes ? rowBytes : inRowBytes;
			UInt32 theHeight = height < inHeight ? height : inHeight;
			
			for( c = 0; c < theHeight; c++ )
			{
				BlockMoveData( pixelBuffer, inBuffer, theRowBytes );
				
				inBuffer += inRowBytes;
				pixelBuffer += rowBytes;
			}
		}
		
		UnlockPixels( pixels );
	}

}

void CTPxmResource::CopyGWorldToIndexedHandle(Handle inData, SInt16 inIndex, const GWorldPtr inGWorld, UInt32 inRowBytes, UInt32 inSize)
{
	CopyGWorldToData((UInt8*)((UInt32)(*inData) + ((UInt32)(inIndex) * inSize)),inGWorld,inRowBytes,inSize);
}

void CTPxmResource::CopyMaskGWorldToMask(SInt16 inIndex)
{
	CopyGWorldToIndexedHandle(mMaskData,inIndex,mMaskGWorld,GetMaskGWorldRowBytes(),GetMaskGWorldSize());
}

void CTPxmResource::CopyImageGWorldToImage(SInt16 inIndex)
{
	CopyGWorldToIndexedHandle(mImageData,inIndex,mImageGWorld,GetImageGWorldRowBytes(),GetImageGWorldSize());
}

void CTPxmResource::UpdateGWorlds( void)
{
	UpdateGWorld( &mImageGWorld, 16, &mHeader.mBounds, mColorTable, 0, clipPix );
	ThrowIfQDError_();
	UpdateGWorld( &mMaskGWorld, 1, &mHeader.mBounds, NULL, 0, clipPix );
	ThrowIfQDError_();
}

void CTPxmResource::UpdateDatas(const Rect &inNewBounds, const SInt16 /*inNewPixDepth*/)
{
	if(GetMaskCount() > 0 || GetImageCount() > 0)
	{
		//Make a copy of all our old data
		Handle oldMasks = mMaskData;
		HandToHand(&oldMasks);
		ThrowIfMemError_();
		
		Handle oldImages = mImageData;
		HandToHand(&oldImages);
		ThrowIfMemError_();
		
		
		Rect oldBounds;
		GetBounds(oldBounds);

		SInt32 oldImageRowBytes = GetImageRowBytes();
		SInt32 oldMaskRowBytes = GetMaskRowBytes();
		SInt32 oldImageSize = GetImageSize();
		SInt32 oldMaskSize = GetMaskSize();
		SInt16 oldPixDepth = GetPixelDepth();
		
		GWorldPtr theOldImageWorld;
		GWorldPtr theOldMaskWorld;
		bool valid = CreateOffscreenWorlds(theOldImageWorld, 
					theOldMaskWorld, 
					oldBounds,
					oldPixDepth);
					
		//Set all the new data
		mHeader.mBounds = inNewBounds;
		mHeader.mPixelDepth = 16;
		mHeader.mCTSeedValue = 0;
		UInt32 newSize = GetImageSize() * GetImageCount();
		SetHandleSize(mImageData,newSize);
		ThrowIfMemError_();
		newSize = GetMaskSize() * GetMaskCount();
		SetHandleSize(mMaskData,newSize);
		ThrowIfMemError_();
					
		UpdateGWorlds();
		
		for(SInt16 i = 0; i < GetImageCount(); i++)
		{
			//Copy from the old image
			CopyIndexedHandleToGWorld(oldImages, i, theOldImageWorld, oldImageRowBytes, oldImageSize);
			
			CopyBits(&((GrafPtr)theOldImageWorld)->portBits, &((GrafPtr)mImageGWorld)->portBits,&oldBounds,&inNewBounds,srcCopy,NULL);
			ThrowIfQDError_();
			#ifdef AICDEBUG
			DebugBlit();
			#endif
			CopyGWorldToIndexedHandle(mImageData,i,mImageGWorld,GetImageRowBytes(),GetImageSize());
		}
		
		for(SInt16 i = 0; i < GetMaskCount(); i++)
		{
			CopyIndexedHandleToGWorld(oldMasks, i, theOldMaskWorld, oldMaskRowBytes, oldMaskSize);
			CopyBits(&((GrafPtr)theOldMaskWorld)->portBits, &((GrafPtr)mMaskGWorld)->portBits,&oldBounds,&inNewBounds,srcCopy,NULL);
			ThrowIfQDError_();
			#ifdef AICDEBUG
			DebugBlit();
			#endif			
			CopyGWorldToIndexedHandle(mMaskData,i,mMaskGWorld,GetMaskRowBytes(),GetMaskSize());
		}
		
		DisposeHandle(oldMasks);
		ThrowIfMemError_();
		DisposeHandle(oldImages);	
		ThrowIfMemError_();
		DisposeGWorld(theOldMaskWorld);
		ThrowIfQDError_();
		DisposeGWorld(theOldImageWorld);
		ThrowIfQDError_();
	}
}

CTabHandle CTPxmResource::GetAssociatedColorTable(void)
{
	CTabHandle				theTable = NULL;
	
	if( mHeader.mCTSeedValue != 0 )
	{
		theTable = (CTabHandle)GetResource( 'clut', mHeader.mCTSeedValue );
			
		//if( (**theTable).ctSeed == mHeader.mCTSeedValue )
		//{
			if(theTable != NULL)
			{
				HandToHand(&( (Handle)theTable) );
			}
		//}
		/*else
		{
			theTable = NULL;
		}*/
	}
	return theTable;
}

SInt32 CTPxmResource::GetImageSize()
{
	return GetPixMapSize(mHeader.mBounds,mHeader.mPixelDepth);
}

SInt32 CTPxmResource::GetMaskGWorldSize()
{
	PixMapHandle g = GetGWorldPixMap(mMaskGWorld);
	
	return GetPixMapSize((*g)->bounds,(*g)->pixelSize);
}

SInt32 CTPxmResource::GetImageGWorldSize()
{
	PixMapHandle g = GetGWorldPixMap(mImageGWorld);
	
	return GetPixMapSize((*g)->bounds,(*g)->pixelSize);

}

SInt32 CTPxmResource::GetMaskSize()
{
	return GetPixMapSize(mHeader.mBounds, 1);
}

SInt32 CTPxmResource::GetImageRowBytes()
{
	return GetPixMapRowBytes(mHeader.mBounds,mHeader.mPixelDepth);
}

SInt32 CTPxmResource::GetMaskRowBytes()
{
	 return GetPixMapRowBytes(mHeader.mBounds, 1);
}

SInt32 CTPxmResource::GetMaskGWorldRowBytes()
{
	PixMapHandle g = GetGWorldPixMap(mMaskGWorld);
	
	return GetPixMapRowBytes((*g)->bounds,(*g)->pixelSize);
}

SInt32 CTPxmResource::GetImageGWorldRowBytes()
{
	PixMapHandle g = GetGWorldPixMap(mImageGWorld);
	
	return GetPixMapRowBytes((*g)->bounds,(*g)->pixelSize);
}




SInt32 CTPxmResource::GetPixMapRowBytes(const Rect &inRect, const SInt16 inPixelDepth)
{
	SInt16 width = inRect.right - inRect.left;
	return (((width * inPixelDepth + 15) / 16) * 2);
}

SInt32 CTPxmResource::GetPixMapSize(const Rect &inRect, const SInt16 inPixelDepth)
{
	SInt16 height = inRect.bottom - inRect.top;
	return GetPixMapRowBytes(inRect,inPixelDepth) * height;
}


#pragma mark -
#pragma mark === OffScreen World Creation
bool CTPxmResource::CreateDefaultOffscreenWorlds()
{
	Rect theDefaultBounds = {0,0,32,32};
	bool answer = CreateOffscreenWorlds(mImageGWorld, mMaskGWorld, theDefaultBounds, 16);
	#ifdef AICDEBUG
		DebugBlit();
	#endif

	return answer;
}

bool CTPxmResource::CreateOffscreenWorlds(GWorldPtr &outImageGWorld, 
					GWorldPtr &outMaskGWorld, 
					const Rect &inBounds,
					const SInt16 inDepth)
{
	QDErr				myErr;
	
	myErr = NewGWorld( &outMaskGWorld, 1, &inBounds, NULL, 0, 0 );
	if( !outMaskGWorld || myErr )
	{
		
		return false;
	}
	
	myErr = NewGWorld( &outImageGWorld, inDepth, &inBounds, mColorTable, 0, 0 );
	
	if( !outImageGWorld || myErr )
	{
		DisposeGWorld( outMaskGWorld );
		return false;
	}
	
	
	CGrafPtr			thePort;
	GDHandle			theDevice;
	PixMapHandle		pixels;
		
	GetGWorld( &thePort, &theDevice );
	
	
	SetGWorld( outMaskGWorld, 0 );
	
	pixels = GetGWorldPixMap( outMaskGWorld );
	
	if( LockPixels( pixels ) )
	{
		EraseRect( &inBounds );
		UnlockPixels( pixels );
	}
	
	#ifdef AICDEBUG
	pixels = GetGWorldPixMap(outMaskGWorld);
	if(LockPixels(pixels))
	{
		CopyBits(&((GrafPtr)outMaskGWorld)->portBits,&((GrafPtr)mDebugWindow)->portBits,&mHeader.mBounds,&mHeader.mBounds,srcCopy,NULL);
		UnlockPixels(pixels);
	}
	#endif
	
	SetGWorld( outImageGWorld, 0 );
	
	pixels = GetGWorldPixMap( outImageGWorld );
	
	if( LockPixels( pixels ) )
	{
		EraseRect( &inBounds );
		UnlockPixels( pixels );
	}
	
	#ifdef AICDEBUG
	pixels = GetGWorldPixMap(outImageGWorld);
	if(LockPixels(pixels))
	{
		CopyBits(&((GrafPtr)outImageGWorld)->portBits,&((GrafPtr)mDebugWindow)->portBits,&mHeader.mBounds,&mHeader.mBounds,srcCopy,NULL);
		UnlockPixels(pixels);
	}
	#endif
	
	SetGWorld( thePort, theDevice );
	return true;
}

						


void CTPxmResource::DeleteOffscreenWorlds(void)
{
	DisposeGWorld( mImageGWorld );
	DisposeGWorld( mMaskGWorld );
	mMaskGWorld = mImageGWorld = NULL;
}

#pragma mark -
#pragma mark === Copying Out

void CTPxmResource::CopyFromMask(GWorldPtr inGWorld, const Rect &where, SInt16 index)
{
	PixMapHandle		srcPixels;
	if(index < 1)
	{
		index = 1;
	}
	index = (index > mHeader.mMaskCount) ? mHeader.mMaskCount : index;

	CopyMaskToMaskGWorld(index - 1);

	srcPixels = GetGWorldPixMap( mMaskGWorld );

	if( LockPixels( srcPixels ) )
	{
		CopyBits( &((GrafPtr)mMaskGWorld)->portBits,  &((GrafPtr)inGWorld)->portBits, 
				  &((GrafPtr)mMaskGWorld)->portRect, &where,
				  srcCopy, 0 );
		#ifdef AICDEBUG
			DebugBlit();
		#endif
		ThrowIfQDError_();
		UnlockPixels( srcPixels );
	}
}

void CTPxmResource::CopyFromImage(GWorldPtr inGWorld,const Rect &where, SInt16 index)
{
	PixMapHandle		srcPixels;
	if(index < 1)
	{
		index = 1;
	}
	index = (index > mHeader.mImageCount) ?  mHeader.mImageCount : index;

	CopyImageToImageGWorld(index - 1);

	srcPixels = GetGWorldPixMap( mImageGWorld );
	
	if( LockPixels( srcPixels ) )
	{
		CopyBits( &((GrafPtr)mImageGWorld)->portBits, &((GrafPtr)inGWorld)->portBits, 
				  &((GrafPtr)mImageGWorld)->portRect, &where,
				  srcCopy, 0 );
		#ifdef AICDEBUG
			DebugBlit();
		#endif
		ThrowIfQDError_();
		UnlockPixels( srcPixels );
	}
}

void CTPxmResource::CopyFromMaskedImage(GWorldPtr inGWorld,const Rect &where, SInt16 index)
{
	PixMapHandle		mMaskPixels, mImagePixels;
	SInt16					mMaskIndex;
	if(index < 1)
	{
		index = 1;
	}
	index = (index >  mHeader.mImageCount) ?  mHeader.mImageCount : index;
	
	mMaskIndex = (index > mHeader.mMaskCount) ? mHeader.mMaskCount : index;

	CopyMaskToMaskGWorld(mMaskIndex - 1);
	CopyImageToImageGWorld(index - 1);

	mMaskPixels = GetGWorldPixMap( mMaskGWorld );
	mImagePixels = GetGWorldPixMap( mImageGWorld );
	
	if( LockPixels( mMaskPixels ) )
	{
		if( LockPixels( mImagePixels ) )
		{
			CopyMask( &((GrafPtr)mImageGWorld)->portBits, &((GrafPtr)mMaskGWorld)->portBits,
					 &((GrafPtr)inGWorld)->portBits, 
					  &((GrafPtr)mImageGWorld)->portRect, &((GrafPtr)mMaskGWorld)->portRect,
					  &where );
		
			UnlockPixels( mImagePixels );
		}
	
		UnlockPixels( mMaskPixels );
	}
}


void CTPxmResource::PaintRect(Rect &inRect, ImageAlignment inAlignment, SInt16 index)
{
	StClipRgnState theClip;
	ClipRect(&inRect);
	
	Rect thePxmRect;
	GetBounds(thePxmRect);
	
	UInt32 thePxmWidth = thePxmRect.right - thePxmRect.left;
	UInt32 theRectWidth = inRect.right - inRect.left;
	UInt32 thePxmHeight = thePxmRect.bottom - thePxmRect.top;
	UInt32 theRectHeight = inRect.bottom - inRect.top;
	
	for(UInt32 i = 0; i < theRectWidth / thePxmWidth + 1; i++)
	{
		for(UInt32 j = 0; j < theRectHeight / thePxmHeight + 1; j++)
		{
			Rect theCopyRect;
			switch(inAlignment)
			{
				
				
				case kImageAlignTopRight:
				{
					theCopyRect.right = inRect.right - thePxmWidth * i;
					theCopyRect.left = theCopyRect.right - thePxmWidth;
					
					theCopyRect.top = inRect.top + thePxmHeight * j;
					theCopyRect.bottom = theCopyRect.top + thePxmHeight;	
				}
				break;
				
				case kImageAlignBottomLeft:
				{
					theCopyRect.left = inRect.left + thePxmWidth * i;
					theCopyRect.right = theCopyRect.left + thePxmWidth;
					
					theCopyRect.bottom = inRect.bottom - thePxmHeight * j;
					theCopyRect.top = theCopyRect.bottom - thePxmHeight;
				}
				break;
				
				case kImageAlignBottomRight:
				{
					theCopyRect.right = inRect.right - thePxmWidth * i;
					theCopyRect.left = theCopyRect.right - thePxmWidth;
					
					theCopyRect.bottom = inRect.bottom - thePxmHeight * j;
					theCopyRect.top = theCopyRect.bottom - thePxmHeight;
				}
				break;
				
				default:
				SignalString_("\pUnknown Alignment!");
				
				case kImageAlignTopLeft:
				{
					theCopyRect.left = inRect.left + thePxmWidth * i;
					theCopyRect.right = theCopyRect.left + thePxmWidth;
					theCopyRect.top = inRect.top + thePxmHeight * j;
					theCopyRect.bottom = theCopyRect.top + thePxmHeight;	
				}	
				break;
			}
			CopyFromMaskedImage((CGrafPort*)qd.thePort,theCopyRect,index);
		}
	}
}

#pragma mark -
#pragma mark === Copying In
void CTPxmResource::CopyToImage(GWorldPtr inGWorld,const Rect &where, SInt16 index, Boolean inUseGWorldRect)
{
	PixMapHandle		pixels;
	if(index < 1)
	{
		index = 1;
	}
	index = (index > mHeader.mImageCount) ?  mHeader.mImageCount : index;
	if(inUseGWorldRect)
	{
		SetBounds(where);
	}
	pixels = GetGWorldPixMap( mImageGWorld );
	
	if( LockPixels( pixels ) )
	{
		CopyBits( &((GrafPtr)inGWorld)->portBits,&((GrafPtr)mImageGWorld)->portBits, 
				  &where,&((GrafPtr)mImageGWorld)->portRect,
				  srcCopy, 0 );
		ThrowIfQDError_();
		#ifdef AICDEBUG
			DebugBlit();
		#endif
		UnlockPixels( pixels );
	}
	CopyImageGWorldToImage(index - 1);
}

void CTPxmResource::CopyToMask(GWorldPtr inGWorld,const Rect &where, SInt16 index, Boolean inUseGWorldRect)
{
	PixMapHandle		pixels;
	if(index < 1)
	{
		index = 1;
	}
	index = (index > mHeader.mMaskCount) ?  mHeader.mMaskCount : index;
	if(inUseGWorldRect)
	{
		SetBounds(where);
	}
	

	pixels = GetGWorldPixMap( mMaskGWorld );
	
	if( LockPixels( pixels ) )
	{
		CopyBits(  &((GrafPtr)inGWorld)->portBits, &((GrafPtr)mMaskGWorld)->portBits, 
				  &where,&((GrafPtr)mMaskGWorld)->portRect, 
				  srcCopy, 0 );
		ThrowIfQDError_();
		#ifdef AICDEBUG
			DebugBlit();
			#endif
		UnlockPixels( pixels );
	}
	CopyMaskGWorldToMask(index - 1);
}

#pragma mark -
#pragma mark == PICT OUT
OSErr CTPxmResource::PictFromMask(PicHandle &outPic, SInt16 index)
{
	SignalIfNot_(outPic == NULL);
	if(index < 1)
	{
		index = 1;
	}
	index = (index > mHeader.mImageCount) ?  mHeader.mImageCount : index;

	CopyMaskToMaskGWorld(index - 1);
	return UTPixUtilities::GWorldToPict(mMaskGWorld,outPic);
}

OSErr CTPxmResource::PictFromImage(PicHandle &outPic, SInt16 index)
{
	SignalIfNot_(outPic == NULL);
	if(index < 1)
	{
		index = 1;
	}
	index = (index > mHeader.mImageCount) ?  mHeader.mImageCount : index;

	CopyImageToImageGWorld(index - 1);
	return UTPixUtilities::GWorldToPict(mImageGWorld,outPic);
}

OSErr CTPxmResource::PictFromMaskedImage(PicHandle &outPic, SInt16 index)
{
	SignalIfNot_(outPic == NULL);
		PixMapHandle		mMaskPixels, mImagePixels;
	SInt16					mMaskIndex;
	OSErr theErr = noErr;
	if(index < 1)
	{
		index = 1;
	}
	index = (index >  mHeader.mImageCount) ?  mHeader.mImageCount : index;
	
	mMaskIndex = (index > mHeader.mMaskCount) ? mHeader.mMaskCount : index;

	CopyMaskToMaskGWorld(mMaskIndex - 1);
	CopyImageToImageGWorld(index - 1);

	mMaskPixels = GetGWorldPixMap( mMaskGWorld );
	mImagePixels = GetGWorldPixMap( mImageGWorld );
	
	if( LockPixels( mMaskPixels ) )
	{
		if( LockPixels( mImagePixels ) )
		{
			CopyMask( &((GrafPtr)mImageGWorld)->portBits, &((GrafPtr)mMaskGWorld)->portBits,
					 &((GrafPtr)mImageGWorld)->portBits, 
					  &((GrafPtr)mImageGWorld)->portRect, &((GrafPtr)mMaskGWorld)->portRect,
					  &((GrafPtr)mImageGWorld)->portRect );
		
			theErr = UTPixUtilities::GWorldToPict(mImageGWorld,outPic);
			UnlockPixels( mImagePixels );
		}
	
		UnlockPixels( mMaskPixels );
	}
	return theErr;
}

#pragma mark -
#pragma mark == PICT IN
OSErr CTPxmResource::PictToMask(PicHandle inPic, SInt16 inIndex, Boolean inUseGWorldRect)
{
	GWorldPtr theGWorld = NULL;
	OSErr theErr = noErr;
	if((theErr = UTPixUtilities::PictToGWorld(inPic,theGWorld)) == noErr)
	{
		CopyToMask(theGWorld,theGWorld->portRect,inIndex,inUseGWorldRect);
	}
	DisposeGWorld(theGWorld);
	return theErr;
}

OSErr CTPxmResource::PictToImage(PicHandle inPic, SInt16 inIndex, Boolean inUseGWorldRect)
{
	GWorldPtr theGWorld = NULL;
	OSErr theErr = noErr;
	if((theErr = UTPixUtilities::PictToGWorld(inPic,theGWorld)) == noErr)
	{
		#ifdef AICDEBUG
			PixMapHandle pixels = GetGWorldPixMap(theGWorld);
			if(LockPixels(pixels))
			{
				CopyBits(&((GrafPtr)theGWorld)->portBits,&((GrafPtr)mDebugWindow)->portBits,&mHeader.mBounds,&mHeader.mBounds,srcCopy,NULL);
				UnlockPixels(pixels);
			}
		#endif
		CopyToImage(theGWorld,theGWorld->portRect,inIndex,inUseGWorldRect);
	}
	DisposeGWorld(theGWorld);
	return theErr;
}

#pragma mark -
#pragma mark == PixPat Out

OSErr CTPxmResource::PixPatFromMaskedImage(PixPatHandle &outPixPat, SInt16 index)
{
	{
	SignalIfNot_(outPixPat == NULL);
		PixMapHandle		mMaskPixels, mImagePixels;
	SInt16					mMaskIndex;
	OSErr theErr = noErr;
	if(index < 1)
	{
		index = 1;
	}
	index = (index >  mHeader.mImageCount) ?  mHeader.mImageCount : index;
	
	mMaskIndex = (index > mHeader.mMaskCount) ? mHeader.mMaskCount : index;

	CopyMaskToMaskGWorld(mMaskIndex - 1);
	CopyImageToImageGWorld(index - 1);

	mMaskPixels = GetGWorldPixMap( mMaskGWorld );
	mImagePixels = GetGWorldPixMap( mImageGWorld );
	
	if( LockPixels( mMaskPixels ) )
	{
		if( LockPixels( mImagePixels ) )
		{
			CopyMask( &((GrafPtr)mImageGWorld)->portBits, &((GrafPtr)mMaskGWorld)->portBits,
					 &((GrafPtr)mImageGWorld)->portBits, 
					  &((GrafPtr)mImageGWorld)->portRect, &((GrafPtr)mMaskGWorld)->portRect,
					  &((GrafPtr)mImageGWorld)->portRect );
		
			theErr = UTPixUtilities::GWorldToPixPat(mImageGWorld,outPixPat);
			UnlockPixels( mImagePixels );
		}
	
		UnlockPixels( mMaskPixels );
	}
	return theErr;
}
}


				