// ===========================================================================
//	UTResource.cpp			   ©1995-1998 Metrowerks Inc. All rights reserved.
// ===========================================================================
//
//	Class for manipulating resources
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



#include "UTResource.h"
#include <UResourceMgr.h>

UTResource::UTResource()
{
	mResourceH = NULL;
	mResAttrsSet = mResNameSet = mResourceExisted = false;
	mNeedToWrite = false;
	mWriteOutOnDelete = false;
	mSpec.fileID = -1;
	mResName[0]	 = 0;
	mSpec.resType	 = '????';
	mSpec.resID		 = 0;
}

void UTResource::Init(	ResType			inResType,
				ResIDT			inResID,
				ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/)
{
	mSpec.fileID = inResFileID;
	mResName[0]	 = 0;
	mSpec.resType	 = inResType;
	mSpec.resID			 = inResID;
	mResAttrs	 = 0;
	mResAttrsSet = mResNameSet = mResourceExisted = false;
	mNeedToWrite = false;
	mWriteOutOnDelete = false;
	
	Dispose();
	
	StCurResFile stack1(mSpec.fileID);
	mResourceH = ::GetResource(mSpec.resType, mSpec.resID);
	if(mResourceH)
	{
		ResIDT foo;
		ResType foo1;
		
		mResourceExisted = true;
		mResAttrs = ::GetResAttrs(mResourceH);
		::GetResInfo(mResourceH, &foo, &foo1, mResName);
	}
	else if(mResourceH == nil && inCreate)
	{
		mResourceH = BuildBaseResource();
		::AddResource(mResourceH, mSpec.resType, mSpec.resID, mResName);
		Dirty();
	}
	else if (inThrowFail) {
		ThrowIfResFail_(mResourceH);
	}
}		
	
Handle 	UTResource::BuildBaseResource()
{
	Handle h = ::NewHandleClear(1);
	ThrowIfMemFail_(h);
	return h;
}

UTResource::~UTResource()
{
	Dispose();
}
			
void				UTResource::Dispose()
{
		if (mResourceH != nil) {
	
			// Resource could have been detached, in which case it
			// is a regular Handle, which we must dispose of in a
			// different way. GetResAttrs() returns the attributes for
			// a Resource, or sets ResError() to resNotFound if the
			// Handle isn't a Resource

		SInt16	resAttrs = ::GetResAttrs(mResourceH);
		
		if (!::ResError()) 
		{	// No error, so it must be a Resource
		
			if(!mResourceExisted)
			{
				::RemoveResource(mResourceH);
				::UpdateResFile(mSpec.fileID);
			}
			else
			{
					// If the changed bit is set for this Resource,
					// we are in trouble. ReleaseResource won't dispose of
					// a changed Resource, and we don't know whether to
					// save or discard the changes. This is a programmer
					// error, so we Signal.
													
				SignalIf_(resAttrs & (1 << resChangedBit));
				
				::ReleaseResource(mResourceH);
			}
		} 
		else 
		{				// It's not a Resource, so it must
								//   be a regular Handle
			::DisposeHandle(mResourceH);
		}

		mResourceH = nil;
	}
}

void UTResource::SetResName(
	ConstStringPtr	inNewName)			// new name for resource
{
	LString::CopyPStr(inNewName, mResName);
	mResNameSet = true;
	Dirty();
}


void UTResource::SetResAttrs(
	SInt16 inResAttrs)					// set resource attributes
{
	mResAttrs = inResAttrs;
	mResAttrsSet = true;
	Dirty();
}


void UTResource::Write(Boolean			inUpdateResFile /* =true*/)
{
	if(mNeedToWrite)
	{
		StCurResFile i;
		UseResFile(mSpec.fileID);
		// sanity check: make sure we have a resource
		
		ThrowIfNil_(mResourceH);

		// if the resource was there, update it; else add it
		
		if (::GetResAttrs(mResourceH) & resProtected) {
			::SetResAttrs(mResourceH, 0);
			mResAttrsSet = true;
		}

		::ChangedResource(mResourceH);
		if (mResNameSet) {
		
			// change name:
			//	SetResInfo is a slow operation, so we want to bypass it
			//	unless the given name actually is different
		
			Str255 tempName;
			SInt16 foo;
			ResType foo1;
			::GetResInfo(mResourceH, &foo, &foo1, tempName);
			if (!::EqualString(tempName, mResName, true, true))
				::SetResInfo(mResourceH, mSpec.resID, mResName);
		}
		mResourceExisted = true;		// Resource now exists

		ThrowIfResError_();
		

		// make sure it gets into the file... must be done before SetResAttrs
		// in case the resource is marked protected or purgeable
		
		::WriteResource(mResourceH);
		ThrowIfResError_();
		
		// now set the attributes
		
		if (mResAttrsSet) {
			::SetResAttrs(mResourceH, mResAttrs);
			ThrowIfResError_();
		}
		
		// update the resource map
		
		if (inUpdateResFile) {
			::UpdateResFile(mSpec.fileID);
			ThrowIfResError_();
		}
	
		mNeedToWrite = false;
	}
}

Handle	UTResource::GetHandleCopyOfResource()
{
	Handle theHand = mResourceH;
	if(theHand != NULL)
	{
		HandToHand(&theHand);
	}
	return theHand;
}
