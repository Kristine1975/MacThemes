// ===========================================================================
//	UTClut.h			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the CLUT's
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Jan 24/99 Initial Implementation
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
#include "UTClut.h"
#include "LFileStream.h"

const OSType kClutResourceType = 'clut';

const SInt32 kPHOTOSHOPCLUTCOUNT = 256;
const SInt32 kPHOTOSHOPCLUTSIZE = kPHOTOSHOPCLUTCOUNT * sizeof(SInt8) * 3;

typedef struct 
{
	UInt8 red;
	UInt8 green;
	UInt8 blue;
} PhotoShopColor;
	

UTClut::UTClut()
{
}


// ---------------------------------------------------------------------------
//	€ Init								Two Step Initialization		  [public]
// ---------------------------------------------------------------------------	
void 
UTClut::Init(ResIDT			inResID,
				ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/)
{
	UTResource::Init(kClutResourceType, inResID, inResFileID, inCreate, inThrowFail);
}


UTClut::~UTClut()
{
}

void UTClut::GetColor(UInt16 inIndex, RGBColor &outColor)
{
	CTabHandle theCTab = (CTabHandle)Get();
	Assert_(theCTab != NULL);
	Assert_(inIndex < Count());
	
	outColor = (**theCTab).ctTable[inIndex].rgb;
}

void UTClut::SetColor(UInt16 inIndex, const RGBColor &inColor)
{
	CTabHandle theCTab = (CTabHandle)Get();
	Assert_(theCTab != NULL);
	Assert_(inIndex < Count());
	(**theCTab).ctTable[inIndex].rgb = inColor;
	CTabChanged(theCTab);
	Dirty();
}

void UTClut::InsertColor(UInt16 inIndex, const RGBColor &inColor)
{
	UInt32 theCount = Count();
	::SetHandleSize(mResourceH,::GetHandleSize(mResourceH) + sizeof(ColorSpec));
	ThrowIfMemError_();
	if(inIndex < theCount)
	{
		//size of a color table includes 1 entry in it
		SInt32 negativeIndex = inIndex;
		UInt32 theOffset1 = (sizeof(ColorTable) + sizeof(ColorSpec) * (negativeIndex - 1));
		UInt32 theOffSet2 = theOffset1 + sizeof(ColorSpec);
		BlockMove((*mResourceH) + theOffset1, 
						(*mResourceH) + theOffSet2,
						(theCount - inIndex) * sizeof(ColorSpec));
						
		ThrowIfMemError_();
	}
	else
	{
		inIndex = theCount;
	}
	SetCount(theCount + 1);
	SetColor(inIndex,inColor);
	CTabChanged((CTabHandle)mResourceH);
}

void UTClut::AddColor(const RGBColor &inColor)
{
	InsertColor(Count(),inColor);
}

void UTClut::DeleteColor(UInt16 inIndex)
{
	CTabHandle theCTab = (CTabHandle)Get();
	SInt16 theCount = Count();
	Assert_(theCTab != NULL);
	Assert_(inIndex < theCount);
	Assert_(theCount > 0);
	if(inIndex < theCount)
	{
		SInt32 negativeIndex = inIndex;
		UInt32 theOffset1 = (sizeof(ColorTable) + (sizeof(ColorSpec) * (negativeIndex - 1)));
		UInt32 theOffSet2 = theOffset1 + sizeof(ColorSpec);
		BlockMove((*mResourceH) + theOffSet2,
						(*mResourceH) + theOffset1, 
						(Count() - (inIndex + 1)) * sizeof(ColorSpec));
		ThrowIfMemError_();
	}
	::SetHandleSize(mResourceH,::GetHandleSize(mResourceH) - sizeof(ColorSpec));
	ThrowIfMemError_();
	SetCount(theCount - 1);
	CTabChanged(theCTab);
	Dirty();

}

UInt16 UTClut::Count()
{
	CTabHandle theCTab = (CTabHandle)Get();
	Assert_(theCTab != NULL);
	
	return (**theCTab).ctSize + 1;	
}

void UTClut::ExportCLUT(LFileStream* inStream)
{
	UInt8 thePhotoShopBytes[kPHOTOSHOPCLUTSIZE];
	PhotoShopColor thePhotoShopClut[kPHOTOSHOPCLUTCOUNT];
	SInt32 theLength = kPHOTOSHOPCLUTSIZE;
	
	for(UInt32 i = 0; i < kPHOTOSHOPCLUTCOUNT; i++)
	{
		if(i < Count())
		{
			RGBColor theColor;
			GetColor(i,theColor);
			thePhotoShopClut[i].red = (((float)theColor.red) / 65535.0 * 255.0);
			thePhotoShopClut[i].green = (((float)theColor.green) / 65535.0 * 255.0);
			thePhotoShopClut[i].blue = (((float)theColor.blue) / 65535.0 * 255.0);
		}
		else
		{
			thePhotoShopClut[i].red = 0;
			thePhotoShopClut[i].green = 0;
			thePhotoShopClut[i].blue = 0;
		}
	}
	
	for(UInt32 i = 0, j = 0; i < kPHOTOSHOPCLUTCOUNT  && j < kPHOTOSHOPCLUTSIZE; i++, j+=3)
	{
		thePhotoShopBytes[j] = thePhotoShopClut[i].red;
		thePhotoShopBytes[j + 1] = thePhotoShopClut[i].green;
		thePhotoShopBytes[j + 2] = thePhotoShopClut[i].blue;
	}
	
	inStream->PutBytes(thePhotoShopBytes,theLength);
	Assert_(theLength == kPHOTOSHOPCLUTSIZE);
}

void UTClut::ImportCLUT(LFileStream* inStream)
{
	//Remove all the old colors
	while(Count() > 0)
	{
		DeleteColor(0);
	}
	
	UInt8 thePhotoShopBytes[kPHOTOSHOPCLUTSIZE];
	PhotoShopColor thePhotoShopClut[kPHOTOSHOPCLUTCOUNT];
	SInt32 theLength = kPHOTOSHOPCLUTSIZE;
	
	inStream->GetBytes(thePhotoShopBytes,theLength);
	Assert_(theLength == kPHOTOSHOPCLUTSIZE);
	
	for(UInt32 i = 0, j = 0; i < kPHOTOSHOPCLUTCOUNT  && j <kPHOTOSHOPCLUTSIZE ; i++, j+=3)
	{
		thePhotoShopClut[i].red = thePhotoShopBytes[j];
		thePhotoShopClut[i].green = thePhotoShopBytes[j + 1];
		thePhotoShopClut[i].blue = thePhotoShopBytes[j + 2];
	}
	
	SInt32 theColorCount = kPHOTOSHOPCLUTCOUNT;
	
	PhotoShopColor theLastColor = thePhotoShopClut[kPHOTOSHOPCLUTCOUNT - 1];
	UInt32 totalColorCount;
	for(totalColorCount = kPHOTOSHOPCLUTCOUNT; totalColorCount > 1; totalColorCount--)
	{
		if(thePhotoShopClut[totalColorCount-2].red != theLastColor.red
		 	&& thePhotoShopClut[totalColorCount-2].green != theLastColor.green
		 	&& thePhotoShopClut[totalColorCount-2].blue != theLastColor.blue)
		{
			break;
		}
	}
	
	for(UInt32 i = 0; i < totalColorCount + 1; i++)
	{
		RGBColor theColor;
		theColor.red = (thePhotoShopClut[i].red  & 0xff) * 0x101;
		theColor.green =(thePhotoShopClut[i].green  & 0xff) * 0x101;
		theColor.blue = (thePhotoShopClut[i].blue  & 0xff) * 0x101;
		AddColor(theColor);
	}
}

Handle UTClut::BuildBaseResource()
{
	CTabHandle newRes = (CTabHandle)::NewHandleClear(sizeof(ColorTable));
	ThrowIfMemFail_(newRes);
	(**newRes).ctSeed = mSpec.resID;
	(**newRes).ctFlags = 0;
	(**newRes).ctSize = 0;
	(**newRes).ctTable[0].value = 0;
	(**newRes).ctTable[0].rgb.red = (**newRes).ctTable[0].rgb.green = (**newRes).ctTable[0].rgb.blue = 0;
	return (Handle)newRes;
}

void UTClut::SetCount(UInt16 inCount)
{
	CTabHandle theCTab = (CTabHandle)Get();
	Assert_(theCTab != NULL);
	(**theCTab).ctSize = inCount - 1;
}

void				UTClut::Write(Boolean			inUpdateResFile/* = true*/)
{
	CTabHandle theCTab = (CTabHandle)Get();
	UInt32 tempSeed = 0;
	if(theCTab != NULL)
	{
		tempSeed = (**theCTab).ctSeed;
		(**theCTab).ctSeed = mSpec.resID;
	}
	UTResource::Write(inUpdateResFile);
	if(theCTab != NULL)
	{
		(**theCTab).ctSeed = tempSeed;
	}
}