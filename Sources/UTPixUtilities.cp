// ===========================================================================
//	UTPixUtilities.cp	©1999 Allegro Themes Project
// ===========================================================================
//	Author: Avi Drissman, Lars Grauland, Mikael Arctaedius, Dave MacLachlan
//
//	A collection of utilities for playing with pixmaps, pixpats, PPAT's, and Pict
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

#include <Types.h>
#include <Memory.h>
#include <Quickdraw.h>
#include <QDOffscreen.h>
#include <UDebugging.h>
#include "UTPixUtilities.h"
#include <PictUtils.h>
#include <math.h>


const SInt32	kHRes = 0x00480000;	// resolution for 72 dpi
const SInt32	kVRes = 0x00480000;	// resolution for 72 dpi
const SInt32	kDefaultDepth = 8;
const SInt32	kColorCount = 256; //Default color count for PixPats
const SInt32	kPicFileHeaderSize = 512;

#pragma mark -
#pragma mark === PIXPAT VS PPAT
//*******************
// PixPatToPPAT - Avi Drissman
//
// Turns a given PixPat into its 'ppat' resource format
// inPixPat: The given PixPat. Must be a valid PixPat.
// outPPAT: The resulting handle, ready to be added as a 'ppat' resource.
// Based on code written Edgar Lee, DTS, Apple in 1992. Unlike his code,
// though, this code doesn't leak handles and isn't buggy.

OSErr UTPixUtilities::PixPatToPPAT(const PixPatHandle inPixPat, Handle &outPPAT)
{
	SignalIfNot_(outPPAT == NULL);
	long		pixmapSize, pixpatSize, imageSize, ctableSize;
	OSErr		theError;

	pixmapSize	= sizeof( PixMap );
	pixpatSize	= sizeof( PixPat );
	imageSize	= ((**(**inPixPat).patMap).rowBytes & 0x3FFF) *
				((**(**inPixPat).patMap).bounds.bottom -
				(**(**inPixPat).patMap).bounds.top);
	ctableSize	= sizeof( ColorTable ) +
				(**(**(**inPixPat).patMap).pmTable).ctSize *
				sizeof( ColorSpec );

	// Set handle size
	outPPAT = NewHandle(pixpatSize + pixmapSize + imageSize + ctableSize);
	theError = MemError();
	if (theError != noErr)
	{
		return theError;
	}
	// Fill in the new PPAT

	BlockMove( *(**(**inPixPat).patMap).pmTable,
				*outPPAT + pixpatSize + pixmapSize + imageSize, ctableSize );
	CTabHandle oldpmTable = (**(**inPixPat).patMap).pmTable;
	(**(**inPixPat).patMap).pmTable = (CTabHandle)(pixpatSize + pixmapSize + imageSize);

	BlockMove( *(**inPixPat).patData, *outPPAT + sizeof( PixPat ) + sizeof( PixMap), imageSize );
	Handle oldPatData = (**inPixPat).patData;
	(**inPixPat).patData = (Handle)(pixpatSize + pixmapSize);

	BlockMove( *(**inPixPat).patMap, *outPPAT + sizeof( PixPat ),pixmapSize );
	PixMapHandle oldPatMap = (**inPixPat).patMap;
	(**inPixPat).patMap = (PixMapHandle)pixpatSize;

	BlockMove( *inPixPat, *outPPAT, pixpatSize );

	(**inPixPat).patMap = oldPatMap;
	(**inPixPat).patData = oldPatData;
	(**(**inPixPat).patMap).pmTable = oldpmTable;

	// Clean up the resource

	(*outPPAT)[10] = 0x00;
	(*outPPAT)[11] = 0x00;
	(*outPPAT)[12] = 0x00;
	(*outPPAT)[13] = 0x00;

	(*outPPAT)[16] = 0x00;
	(*outPPAT)[17] = 0x00;
	(*outPPAT)[18] = 0x00;
	(*outPPAT)[19] = 0x00;

	return noErr;
}

//*******************
// PPATToPixPat - Avi Drissman
//
// Turns a given handle in 'ppat' resource format into a PixPat
// inPPAT: The given handle in 'ppat' resource format. It can be a resource
//         handle, but if it is, you might as well call GetPixPat()...
// outPixPat: The resulting PixPat.
// Plan of action:
// - save all the handles in the pre-allocated PixPat
// - blast the data from the 'ppat' handle into the different handles
// - reconnect all the handles to the PixPat
// - let QuickDraw know that it's not the boss anymore
	
OSErr UTPixUtilities::PPATToPixPat(const Handle inPPAT, PixPatHandle &outPixPat)
{
	SignalIfNot_(outPixPat == NULL);

	OSErr theError;

	//Make the new PixPat
	outPixPat = NewPixPat();
	
	// Save the handles (save the whales?)
	CTabHandle		colorTable		= (**(**outPixPat).patMap).pmTable;
	PixMapHandle	patMap			= (**outPixPat).patMap;
	Handle			patData			= (**outPixPat).patData;
	Handle			patXData		= (**outPixPat).patXData;
	Handle			patXMap			= (**outPixPat).patXMap;

	// Re-size the handles

	long			pixmapOffset	= ((UInt16 *)(*inPPAT))[1] * 0x10000 + ((UInt16 *)(*inPPAT))[2];
	SignalIfNot_(pixmapOffset == 28);
	long			imageOffset		= ((UInt16*)(*inPPAT))[3] * 0x10000 + ((UInt16 *)(*inPPAT))[4];
	SignalIfNot_(imageOffset == 78);
	long			ctableOffset	= ((UInt16 *)(*inPPAT))[35]* 0x10000 + ((UInt16 *)(*inPPAT))[36];

	long			pixpatSize		= sizeof( PixPat );
	long			pixmapSize		= sizeof( PixMap );
	long			imageSize		= ctableOffset - imageOffset;
	long 			ctableSize		= sizeof(ColorTable ) +
										((UInt16 *)(*inPPAT))[ctableOffset * sizeof( char ) 
										/ sizeof(UInt16 ) + 3] * sizeof( ColorSpec );

	SetHandleSize( (Handle) colorTable, ctableSize );
	theError = MemError();
	if (theError != noErr)
	{
		return theError;
	}
	SetHandleSize( patData, imageSize );
	theError = MemError();
	if (theError != noErr)
	{
		return theError;
	}
	// Data blasting

	BlockMove( *inPPAT, *outPixPat, pixpatSize ); // move the PixPat record
	BlockMove( *inPPAT + pixmapOffset, *patMap, pixmapSize ); // move the "pixmap"
	BlockMove( *inPPAT + imageOffset, *patData, imageSize ); // move the image
	BlockMove( *inPPAT + ctableOffset, *colorTable, ctableSize ); //move the color table

	// Reconnect the handles

	(**outPixPat).patMap				= patMap;
	(**outPixPat).patData				= patData;
	(**outPixPat).patXData				= patXData;
	(**outPixPat).patXMap				= patXMap;
	(**(**outPixPat).patMap).pmTable	= colorTable;

	// Let QuickDraw know we've been here

	PixPatChanged(outPixPat);
	CTabChanged((**(**outPixPat).patMap).pmTable);

	return noErr;
}

#pragma mark -
#pragma mark === PICT VS GWORLD


OSErr UTPixUtilities::PictToGWorld(const PicHandle inPicHandle, GWorldPtr &outGWorld)
{
	OSErr theErr = noErr;
	SignalIfNot_(outGWorld == NULL);
	SignalIf_(inPicHandle == NULL);
	
	Rect		bounds;
	CGrafPtr	curgraf;
	GDHandle	curgdh;
	
	PictInfo thePictInfo;
	theErr = GetPictInfo(inPicHandle,&thePictInfo,returnColorTable,kColorCount,
         popularMethod,0);
	if(theErr != noErr)
	{
		return theErr;
	}
	bounds = ((Picture *)(*inPicHandle))->picFrame;
	OffsetRect (&bounds, -bounds.left, -bounds.top);
	//theErr = NewGWorld(&outGWorld, kDefaultDepth, &bounds, thePictInfo.theColorTable, NULL, 0);
	theErr = NewGWorld(&outGWorld, 32, &bounds, NULL, NULL, 0);

	if (theErr != noErr)
	{
		return theErr;
	}
	// Ok, now we have created an offscreen world (including a PixMapHandle!)
	// Lets draw the picture in it.

	GetGWorld(&curgraf, &curgdh);

	SetGWorld(CGrafPtr(outGWorld), NULL);
	if(LockPixels(GetGWorldPixMap(outGWorld)))
	{
		EraseRect(&bounds);
		DrawPicture(inPicHandle, &bounds);
		UnlockPixels(GetGWorldPixMap(outGWorld));
	}
	// Done drawing, restore the graphic environment.
	SetGWorld(curgraf, curgdh);
	
	return theErr;
}

OSErr UTPixUtilities::GWorldToPict(const GWorldPtr inGWorld, PicHandle &outPicHandle)
{
	OSErr theErr = noErr;
	SignalIfNot_(outPicHandle == NULL);
	SignalIf_(inGWorld == NULL);
	
	CGrafPtr	curgraf;
	GDHandle	curgdh;
	
	GetGWorld(&curgraf, &curgdh);
	SetGWorld(CGrafPtr(inGWorld), NULL);
	outPicHandle = OpenPicture(&(inGWorld->portRect));
	if(LockPixels(GetGWorldPixMap(inGWorld)))
	{
		CopyBits(&((GrafPtr)inGWorld)->portBits, &((GrafPtr)inGWorld)->portBits,&inGWorld->portRect,&inGWorld->portRect,srcCopy,NULL);
		UnlockPixels(GetGWorldPixMap(inGWorld));
	}
	ClosePicture();
	SetGWorld(curgraf,curgdh);
	return QDError();
}

#pragma mark -
#pragma mark === PIXPAT VS GWORLD

OSErr UTPixUtilities::GWorldToPixPat(const GWorldPtr inGWorld, PixPatHandle &outPixPat)
{
	OSErr theErr = noErr;
	SignalIfNot_(outPixPat == NULL);
	SignalIf_(inGWorld == NULL);
	
	CGrafPtr	curgraf;
	GDHandle	curgdh;
	
	//We need to set the height and width
	//of our rect to the closest (bigger) power of two that we can.
	//PixPat's must be a power of 2 high and a power of 2 wide.
	Rect oldBounds, newBounds;
	
	oldBounds = inGWorld->portRect;
	newBounds = oldBounds;
	
	SInt16 width = newBounds.right - newBounds.left;
	SInt16 height = newBounds.bottom - newBounds.top;
	
	double logWidth = log2(width);
	double logHeight = log2(height);
	
	SInt16 roundWidth = logWidth;
	SInt16 roundHeight = logHeight;
	
	if(roundHeight < logHeight)
	{
		roundHeight++;
	}
	
	if(roundWidth < logWidth)
	{
		roundWidth++;
	}
	
	newBounds.right = newBounds.left + (1 << roundWidth);
	newBounds.bottom = newBounds.top + (1 << roundHeight);
	
	GetGWorld(&curgraf, &curgdh);
	SetGWorld(CGrafPtr(inGWorld), NULL);
	
	GWorldPtr tempGWorld;
	theErr = NewGWorld(&tempGWorld, 0, &newBounds, NULL, GetGDevice(), 0);
	if(theErr == noErr)
	{
		SetGWorld(CGrafPtr(tempGWorld), NULL);
		if(LockPixels(GetGWorldPixMap(tempGWorld)))
		{
			EraseRect(&newBounds);
			CopyBits(&((GrafPtr)inGWorld)->portBits,&((GrafPtr)tempGWorld)->portBits,&oldBounds,&oldBounds,srcCopy,NULL);
			outPixPat = NewPixPat();
			CopyPixMap(tempGWorld->portPixMap,(*outPixPat)->patMap);
			long imageSize	= ((**(tempGWorld->portPixMap)).rowBytes & 0x3FFF) *
					((**(tempGWorld->portPixMap)).bounds.bottom -
					(**(tempGWorld->portPixMap)).bounds.top);
			(**outPixPat).patData = NewHandleClear(imageSize);
			BlockMove(GetPixBaseAddr(GetGWorldPixMap(tempGWorld)), *((**outPixPat).patData), imageSize );
			theErr = MemError();
			PixPatChanged(outPixPat);
			UnlockPixels(GetGWorldPixMap(tempGWorld));
			DisposeGWorld(tempGWorld);
		}
	}
	SetGWorld(curgraf,curgdh);
	return theErr;
}

OSErr UTPixUtilities::PixPatToGWorld(const PixPatHandle inPixPat, GWorldPtr &outGWorld)
{
	OSErr theErr = noErr;
	SignalIfNot_(outGWorld == NULL);
	SignalIf_(inPixPat == NULL);
	
	SInt16 theDepth = (*((*inPixPat)->patMap))->pixelSize;
	Rect theBounds = (*((*inPixPat)->patMap))->bounds;
	CTabHandle theCTabHandle = (*((*inPixPat)->patMap))->pmTable;
	theErr = NewGWorld(&outGWorld,theDepth, &theBounds, theCTabHandle, NULL, 0);
	if (theErr != noErr)
	{
		return theErr;
	}
	
	CGrafPtr	curgraf;
	GDHandle	curgdh;
	
	GetGWorld(&curgraf, &curgdh);
	SetGWorld(CGrafPtr(outGWorld), NULL);
	if(LockPixels(GetGWorldPixMap(outGWorld)))
	{
		FillCRect( &theBounds, inPixPat );
		UnlockPixels(GetGWorldPixMap(outGWorld));
	}
	SetGWorld(curgraf,curgdh);
	return theErr;
}

OSErr UTPixUtilities::PictToPixPat(const PicHandle inPicHandle, PixPatHandle &outPixPat)
{
	OSErr theErr = noErr;
	SignalIfNot_(outPixPat == NULL);
	SignalIf_(inPicHandle == NULL);
	
	GWorldPtr tempPtr = NULL;
	if((theErr = UTPixUtilities::PictToGWorld(inPicHandle,tempPtr)) == noErr)
	{
		if((theErr = UTPixUtilities::GWorldToPixPat(tempPtr,outPixPat)) == noErr)
		{
			DisposeGWorld(tempPtr);
		}
	}
	return theErr;
}

OSErr UTPixUtilities::PixPatToPict(const PixPatHandle inPixPat, PicHandle &outPicHandle)
{
	OSErr theErr = noErr;
	SignalIfNot_(outPicHandle == NULL);
	SignalIf_(inPixPat == NULL);
	
	GWorldPtr tempPtr = NULL;
	if((theErr = UTPixUtilities::PixPatToGWorld(inPixPat,tempPtr)) == noErr)
	{
		if((theErr = UTPixUtilities::GWorldToPict(tempPtr,outPicHandle)) == noErr)
		{
			DisposeGWorld(tempPtr);
		}
	}
	return theErr;
}
	
OSErr UTPixUtilities::PictToPPAT(const PicHandle inPicHandle, Handle &outPPAT)
{
	OSErr theErr = noErr;
	SignalIfNot_(outPPAT == NULL);
	SignalIf_(inPicHandle == NULL);
	
	PixPatHandle tempHandle = NULL;
	if((theErr = UTPixUtilities::PictToPixPat(inPicHandle,tempHandle)) == noErr)
	{
		if((theErr = UTPixUtilities::PixPatToPPAT(tempHandle,outPPAT)) == noErr)
		{
			DisposePixPat(tempHandle);
		}
	}
	return theErr;
}

OSErr UTPixUtilities::PPATToPict(const Handle inPPAT, PicHandle &outPicHandle)
{
	OSErr theErr = noErr;
	SignalIfNot_(outPicHandle == NULL);
	SignalIf_(inPPAT == NULL);
	
	PixPatHandle tempHandle = NULL;
	if((theErr = UTPixUtilities::PPATToPixPat(inPPAT,tempHandle)) == noErr)
	{
		if((theErr = UTPixUtilities::PixPatToPict(tempHandle,outPicHandle)) == noErr)
		{
			DisposePixPat(tempHandle);
		}
	}
	return theErr;
}

#pragma mark -
#pragma mark == PICT VS COLOR
OSErr UTPixUtilities::PictToColor(const PicHandle inPicHandle, RGBColor &outColor)
{
	OSErr theErr = noErr;
	SignalIf_(inPicHandle == NULL);
	PictInfo tempInfo;
	
	theErr = GetPictInfo (inPicHandle, &tempInfo, returnColorTable, 1, popularMethod, 0);
	if(theErr == noErr)
	{
		if(tempInfo.theColorTable != NULL)
		{
			outColor = (**(tempInfo.theColorTable)).ctTable[0].rgb;
		}
		DisposeCTable(tempInfo.theColorTable);
	}
	return theErr;
}

OSErr UTPixUtilities::ColorToPict(const RGBColor inColor, PicHandle &outPicHandle)
{
	OSErr theErr = noErr;
	SignalIfNot_(outPicHandle == NULL);
	Rect theBounds = {0,0,32,32};
	GWorldPtr tempGWorld;
	theErr = NewGWorld(&tempGWorld,16, &theBounds, NULL, NULL, 0);
	if(theErr == noErr)
	{
		CGrafPtr	curgraf;
		GDHandle	curgdh;
		
		GetGWorld(&curgraf, &curgdh);
		SetGWorld(CGrafPtr(tempGWorld), NULL);
		if(LockPixels(GetGWorldPixMap(tempGWorld)))
		{
			RGBForeColor(&inColor);
			PaintRect(&theBounds);
			UnlockPixels(GetGWorldPixMap(tempGWorld));
			theErr = GWorldToPict(tempGWorld,outPicHandle);
		}
		SetGWorld(curgraf,curgdh);
	}
	return theErr;
}

#pragma mark -
#pragma mark === PICT FILE

OSErr UTPixUtilities::PictFileToPict(const FSSpec &inSpec, PicHandle &outPicHandle)
{
	OSErr theErr = noErr;
	SignalIfNot_(outPicHandle == NULL);
	
	LFileStream theStream(inSpec);
	
	theStream.OpenDataFork(fsRdPerm);
	
	SInt32 theLength = theStream.GetLength();
	theStream.SetMarker(kPicFileHeaderSize,streamFrom_Start);
	theLength -= kPicFileHeaderSize;
	
	outPicHandle = (PicHandle)NewHandle(theLength);
	theErr = MemError();
	if(theErr == noErr)
	{
		HLock((Handle)outPicHandle);
		theErr = theStream.GetBytes(*outPicHandle,theLength);
		HUnlock((Handle)outPicHandle);
	}
	
	theStream.CloseDataFork();
	return theErr;
}

OSErr		UTPixUtilities::PlutEntryToPict(const PlutEntry &inEntry, PicHandle &outPict)
{
	SignalIf_(outPict != NULL);
	OSErr theErr = noErr;
	
	if(inEntry.brushPPAT.resID == 0)
	{
		theErr = UTPixUtilities::ColorToPict(inEntry.brushColor,outPict);
	}
	else
	{
		PixPatHandle thePattern = inEntry.GetPlutPixPat();
		theErr = UTPixUtilities::PixPatToPict(thePattern,outPict);
		DisposePixPat(thePattern);
	}
	return theErr;
}

void UTPixUtilities::FillCRectAligned(const Rect &inRect, const PixPatHandle inPattern, const ImageAlignment inAlignment)
{
	FillCRectAlignedToRect(inRect,inRect,inPattern,inAlignment);
}

void UTPixUtilities::FillCRectAlignedToRect(const Rect &inPaintRect, const Rect &inAlignRect, const PixPatHandle inPattern, const ImageAlignment inAlignment)
{
	GWorldPtr theGWorld = NULL;
	
	if(UTPixUtilities::PixPatToGWorld(inPattern,theGWorld) == noErr)
	{
		StClipRgnState theClip;
		StRegion theNewClip(inPaintRect);
		theClip.SectWithCurrent(theNewClip);
		
		StColorPenState theState;
		theState.Normalize();
		
		PixMapHandle theGWorldPix = GetGWorldPixMap( theGWorld );
		LockPixels(theGWorldPix);
		ThrowIfQDError_();
		
		Rect theGWorldRect;
		theGWorldRect= theGWorld->portRect;
		
		UInt32 theGWorldWidth = theGWorldRect.right - theGWorldRect.left;
		UInt32 theRectWidth = inAlignRect.right - inAlignRect.left;
		UInt32 theGWorldHeight = theGWorldRect.bottom - theGWorldRect.top;
		UInt32 theRectHeight = inAlignRect.bottom - inAlignRect.top;
		
		for(UInt32 i = 0; i < theRectWidth / theGWorldWidth + 1; i++)
		{
			for(UInt32 j = 0; j < theRectHeight / theGWorldHeight + 1; j++)
			{
				Rect theCopyRect;
				switch(inAlignment)
				{
					
					
					case kImageAlignTopRight:
					{
						theCopyRect.right = inAlignRect.right - theGWorldWidth * i;
						theCopyRect.left = theCopyRect.right - theGWorldWidth;
						
						theCopyRect.top = inAlignRect.top + theGWorldHeight * j;
						theCopyRect.bottom = theCopyRect.top + theGWorldHeight;	
					}
					break;
					
					case kImageAlignBottomLeft:
					{
						theCopyRect.left = inAlignRect.left + theGWorldWidth * i;
						theCopyRect.right = theCopyRect.left + theGWorldWidth;
						
						theCopyRect.bottom = inAlignRect.bottom - theGWorldHeight * j;
						theCopyRect.top = theCopyRect.bottom - theGWorldHeight;
					}
					break;
					
					case kImageAlignBottomRight:
					{
						theCopyRect.right = inAlignRect.right - theGWorldWidth * i;
						theCopyRect.left = theCopyRect.right - theGWorldWidth;
						
						theCopyRect.bottom = inAlignRect.bottom - theGWorldHeight * j;
						theCopyRect.top = theCopyRect.bottom - theGWorldHeight;
					}
					break;
					
					default:
					SignalString_("\pUnknown Alignment!");
					
					case kImageAlignTopLeft:
					{
						theCopyRect.left = inAlignRect.left + theGWorldWidth * i;
						theCopyRect.right = theCopyRect.left + theGWorldWidth;
						theCopyRect.top = inAlignRect.top + theGWorldHeight * j;
						theCopyRect.bottom = theCopyRect.top + theGWorldHeight;	
					}	
					break;
				}
				CopyBits( &((GrafPtr)theGWorld)->portBits, &((GrafPtr)qd.thePort)->portBits, 
			  &theGWorldRect, &theCopyRect,srcCopy, 0 );
			}
		}
		UnlockPixels( theGWorldPix );
		DisposeGWorld(theGWorld);
	}
	else
	{
		FillCRect(&inPaintRect,inPattern);
	}
}
/*
#pragma mark -
#pragma mark ICON UTILITIES
OSErr UTPixUtilities::Huge1BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,48,48};
	return IconToPict(inIcon, outPicHandle, kSelectorHuge1Bit, 1,theBounds);
}

OSErr UTPixUtilities::Huge4BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,48,48};
	return IconToPict(inIcon, outPicHandle, kSelectorHuge4Bit, 1,theBounds);
}

OSErr UTPixUtilities::Huge8BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,48,48};
	return IconToPict(inIcon, outPicHandle, kSelectorHuge8Bit, 1,theBounds);
}

OSErr UTPixUtilities::Huge32BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,48,48};
	return IconToPict(inIcon, outPicHandle, kSelectorHuge32Bit, 1,theBounds);
}


OSErr UTPixUtilities::Huge8BitIconMaskToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,48,48};
	return IconToPict(inIcon, outPicHandle, kSelectorHuge8BitMask, 1,theBounds);
}

	
OSErr UTPixUtilities::Large1BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,32,32};
	return IconToPict(inIcon, outPicHandle, kSelectorLarge1Bit, 1,theBounds);
}

OSErr UTPixUtilities::Large4BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,32,32};
	return IconToPict(inIcon, outPicHandle, kSelectorLarge4Bit, 1,theBounds);
}

OSErr UTPixUtilities::Large8BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,32,32};
	return IconToPict(inIcon, outPicHandle, kSelectorLarge8Bit, 1,theBounds);
}

OSErr UTPixUtilities::Large32BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,32,32};
	return IconToPict(inIcon, outPicHandle, kSelectorLarge32Bit, 1,theBounds);
}

OSErr UTPixUtilities::Large8BitIconMaskToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,32,32};
	return IconToPict(inIcon, outPicHandle, kSelectorLarge8BitMask, 1,theBounds);
}

	
OSErr UTPixUtilities::Small1BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,16,16};
	return IconToPict(inIcon, outPicHandle, kSelectorSmall1Bit, 1,theBounds);
}

OSErr UTPixUtilities::Small4BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,16,16};
	return IconToPict(inIcon, outPicHandle, kSelectorSmall4Bit, 1,theBounds);
}

OSErr UTPixUtilities::Small8BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,16,16};
	return IconToPict(inIcon, outPicHandle, kSelectorSmall8Bit, 1,theBounds);
}

OSErr UTPixUtilities::Small32BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,16,16};
	return IconToPict(inIcon, outPicHandle, kSelectorSmall32Bit, 1,theBounds);
}

OSErr UTPixUtilities::Small8BitIconMaskToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,16,16};
	return IconToPict(inIcon, outPicHandle, kSelectorSmall8BitMask, 1,theBounds);
}

	
OSErr UTPixUtilities::Mini1BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,12,16};
	return IconToPict(inIcon, outPicHandle, kSelectorMini1Bit, 1,theBounds);
}

OSErr UTPixUtilities::Mini4BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,12,16};
	return IconToPict(inIcon, outPicHandle, kSelectorMini4Bit, 1,theBounds);
}

OSErr UTPixUtilities::Mini8BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle)
{
	Rect theBounds = {0,0,12,16};
	return IconToPict(inIcon, outPicHandle, kSelectorMini8Bit, 1,theBounds);
}

	
OSErr UTPixUtilities::PictToHuge1BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToHuge4BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToHuge8BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToHuge32BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToHuge8BitIconMask(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

	
OSErr UTPixUtilities::PictToLarge1BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToLarge4BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToLarge8BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToLarge32BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToLarge8BitIconMask(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

	
OSErr UTPixUtilities::PictToSmall1BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToSmall4BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToSmall8BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToSmall32BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToSmall8BitIconMask(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

	
OSErr UTPixUtilities::PictToMini1BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToMini4BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::PictToMini8BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon)
{
	OSErr theErr = noErr;
	SignalIfNot_(outIcon == NULL);
	SignalIf_(inPicHandle == NULL);
	
	return theErr;
}

OSErr UTPixUtilities::IconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle, const IconSelectorValue inSelector, const SInt16 inDepth,const Rect &inBounds)
{
	OSErr theErr = noErr;
	SignalIfNot_(outPicHandle == NULL);
	SignalIf_(inIcon == NULL);
	
	IconSuiteRef	theSuiteRef = NULL;
	
	theErr = IconFamilyToIconSuite(inIcon,inSelector,&theSuiteRef);
	if(theErr == noErr)
	{
		GWorldPtr theGWorld = NULL;
		theErr = NewGWorld(&theGWorld,inDepth, &inBounds, NULL, NULL, 0);
		if(theErr == noErr)
		{
			CGrafPtr	curgraf;
			GDHandle	curgdh;
			
			GetGWorld(&curgraf, &curgdh);
			SetGWorld(CGrafPtr(theGWorld), NULL);
			if(LockPixels(GetGWorldPixMap(theGWorld)))
			{
				theErr = PlotIconSuite(&inBounds,kAlignNone,kTransformNone,theSuiteRef);
				if(theErr == noErr)
				{
					GWorldToPict(theGWorld,outPicHandle);
				}
				UnlockPixels(GetGWorldPixMap(theGWorld));
			}
			SetGWorld(curgraf,curgdh);
			DisposeGWorld(theGWorld);
		}
	}
	return theErr;
}

*/