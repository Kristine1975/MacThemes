// ===========================================================================
//	UTFlacResource.cpp			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the flac resource
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


#include "UTFlacResource.h"
#include "TThemes.h"
// ---------------------------------------------------------------------------

UTFlacResource::UTFlacResource()
{
	mCollection = NULL;
}
			
UTFlacResource::~UTFlacResource()
{
}

void UTFlacResource::Dispose()
{
	if(mCollection != NULL)
	{
		DisposeCollection(mCollection);
	}
	mCollection = NULL;
	UTResource::Dispose();
}

void UTFlacResource::Init(
				ResIDT			inResID,
				ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/,
				ResType			inResType /*= kFlacResourceType*/)
{
	UTResource::Init(inResType, inResID, inResFileID, inCreate, inThrowFail);
	mCollection = NewCollection();
	UnflattenCollectionFromHdl(mCollection,mResourceH);
}
			
Handle 	UTFlacResource::BuildBaseResource()
{
	Handle newRes = ::NewHandleClear(0);
	ThrowIfMemFail_(newRes);
	mCollection = NewCollection();
	return newRes;
}

void		UTFlacResource::Write(Boolean			inUpdateResFile /*= true*/)
{
	ThrowIfOSErr_(FlattenCollectionToHdl(mCollection, mResourceH));
	UTResource::Write(inUpdateResFile);
}


