// ===========================================================================
//	UTPixUtilities.h	©1999 Allegro Themes Project
// ===========================================================================
//	Author: Avi Drissman
//
//	Takes a PixPat and turns it into a PPAT resource and vice versa
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

#ifndef _H_UTPixUtilities
#define _H_UTPixUtilities
#pragma once

#include "UTPlutResource.h"

class UTPixUtilities
{
	public:
	static OSErr PixPatToPPAT(const PixPatHandle inPixPat, Handle &outPPAT);
	static OSErr PPATToPixPat(const Handle inPPAT, PixPatHandle &outPixPat);
	
	static OSErr PictToGWorld(const PicHandle inPicHandle, GWorldPtr &outGWorld);
	static OSErr GWorldToPict(const GWorldPtr inGWorld, PicHandle &outPicHandle);
	
	static OSErr GWorldToPixPat(const GWorldPtr inGWorld, PixPatHandle &outPixPat);
	static OSErr PixPatToGWorld(const PixPatHandle inPixPat, GWorldPtr &outGWorld);
	
	static OSErr PictToPixPat(const PicHandle inPicHandle, PixPatHandle &outPixPat);
	static OSErr PixPatToPict(const PixPatHandle inPixPat, PicHandle &outPicHandle);
	
	static OSErr PictToPPAT(const PicHandle inPicHandle, Handle &outPPAT);
	static OSErr PPATToPict(const Handle inPPAT, PicHandle &outPicHandle);
	
	static OSErr PictToColor(const PicHandle inPicHandle, RGBColor &outColor);
	static OSErr ColorToPict(const RGBColor inColor, PicHandle &outPicHandle);
	
	static OSErr PictFileToPict(const FSSpec &inSpec, PicHandle &outPicHandle);
	static OSErr PlutEntryToPict(const PlutEntry &inEntry, PicHandle &outPict);

	static void FillCRectAligned(const Rect &inRect, const PixPatHandle inPattern, const ImageAlignment inAlignment);
	static void FillCRectAlignedToRect(const Rect &inPaintRect, const Rect &inAlignRect, const PixPatHandle inPattern, const ImageAlignment inAlignment);
	/*static OSErr Huge1BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Huge4BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Huge8BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Huge32BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Huge8BitIconMaskToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	
	static OSErr Large1BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Large4BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Large8BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Large32BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Large8BitIconMaskToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	
	static OSErr Small1BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Small4BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Small8BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Small32BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Small8BitIconMaskToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	
	static OSErr Mini1BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Mini4BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	static OSErr Mini8BitIconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle);
	
	static OSErr PictToHuge1BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToHuge4BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToHuge8BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToHuge32BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToHuge8BitIconMask(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	
	static OSErr PictToLarge1BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToLarge4BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToLarge8BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToLarge32BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToLarge8BitIconMask(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	
	static OSErr PictToSmall1BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToSmall4BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToSmall8BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToSmall32BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToSmall8BitIconMask(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	
	static OSErr PictToMini1BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToMini4BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	static OSErr PictToMini8BitIcon(const PicHandle inPicHandle, IconFamilyHandle &outIcon);
	
	private:
	static OSErr IconToPict(const IconFamilyHandle inIcon, PicHandle &outPicHandle, const IconSelectorValue inSelector, const SInt16 inDepth,const Rect &inBounds);*/
};

#endif