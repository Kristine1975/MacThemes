// ===========================================================================
//	UTResource.h			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating resources
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


#ifndef _H_UTResource
#define _H_UTResource
#pragma once

#include <PP_Prefix.h>
#include <UMemoryMgr.h>

#include "TThemes.h"

// ---------------------------------------------------------------------------

class	UTResource
{
	public:
	UTResource();
				
	virtual ~UTResource();
	
	void Init(	ResType			inResType,
					ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true); 			
	void				SetResName(ConstStringPtr	inNewName);
	void				SetResAttrs(SInt16			inResAttrs);

	virtual void				Write(Boolean			inUpdateResFile = true);
	//Inlines
	
	FullResourceSpec			GetResourceSpec()					{ return mSpec; }
	ConstStringPtr GetResName()			{ return mResName; }
	SInt16			GetResAttrs()			{ return mResAttrs; }
	void				Dirty()					{ mNeedToWrite = true; }
	Boolean			isDirty()				{ return mNeedToWrite; }
	operator Handle()	{ return mResourceH; }
				
	Handle	Get()		{ return mResourceH; }
	virtual Handle 	BuildBaseResource();
	Handle	GetHandleCopyOfResource();
	virtual void				Dispose();
	
private:						// Disallow copy and assignment
	UTResource(const UTResource&){}
	UTResource&	operator = (const UTResource&){ return *this; }			
	
	
protected:

	

	Boolean		mNeedToWrite;					// true if resource should be written
	Boolean		mWriteOutOnDelete;	// do we write ourself out when we're deleted
	FullResourceSpec	mSpec;				// ID of Resource File
	Handle		mResourceH;				// resource Handle
	SInt16		mResAttrs;				// resource attributes
	Str255		mResName;				// resource name
	Boolean		mResAttrsSet;			// true if caller set resource attributes
	Boolean		mResNameSet;			// true if caller set resource name
	Boolean		mResourceExisted;		// true if resource existed previously

};

class UTThemeResource : public UTResource
{
	public:
	UTThemeResource()
	{
		mAddToTdat = false;
	}
	
	void Init(	Boolean inAddToTdat,
					ResType			inResType,
					ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true)
	{
		UTResource::Init(inResType,inResID,inResFileID,inCreate,inThrowFail);
		mAddToTdat = inAddToTdat;
	}
	
	Boolean isAddToTdat() { return mAddToTdat; }
	void setAddToTdat(Boolean inAdd) { mAddToTdat = inAdd; }
	
	protected:
	Boolean mAddToTdat;
};

#endif
