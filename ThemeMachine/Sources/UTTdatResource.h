// ===========================================================================
//	UTTdatResource.h			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the tdat resource
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Dec 22/98 Initial Implementation

#ifndef _H_UTTdatResource
#define _H_UTTdatResource
#pragma once

#include "UTResource.h"
const ResType kTdatResourceType = 'tdat';

// ---------------------------------------------------------------------------
//	TdatEntry
//	
//	A class for dealing with tdat entry. Each structure represents a single
// tdat field
// ---------------------------------------------------------------------------	

class TdatEntry
{
	public:
	
	OSType mResType;
	ResIDT mResID1;
	ResIDT mResID2;
	SInt16 mUnknown1;
	SInt16 mUnknown2;
	SInt16 mUnknown3;
	SInt16 mUnknown4;
	
	TdatEntry(const FullResourceSpec &inSpec)
	{
		mResType = inSpec.resType;
		mResID1 = mResID2 = inSpec.resID;
		mUnknown1 = mUnknown2 = mUnknown3 = mUnknown4 = 0;
	}
		
	TdatEntry(OSType inResType, 
				ResIDT inResID)
	{
		mResType = inResType;
		mResID1 = inResID;
		mResID2 = inResID;
		mUnknown1 = mUnknown2 = mUnknown3 = mUnknown4 = 0;
	}
	
	TdatEntry()
	{
		mResID1 = mResID2 = -1;
		mUnknown1 = mUnknown2 = mUnknown3 = mUnknown4 = 0;
		mResType = '????';
	}
};


// ---------------------------------------------------------------------------

class	UTTdatResource : public UTResource
{
	public:
	UTTdatResource();							
	virtual ~UTTdatResource();
	void Init(ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true);
			
	virtual Handle 	BuildBaseResource();	

	void GetTdatEntry(UInt32 inIndex, 
								TdatEntry &outTic);
	void SetTdatEntry(UInt32 inIndex, 
								const TdatEntry &inTic);
	void InsertTdatEntry(UInt32 inIndex, 
									const TdatEntry &inTic);
	void AddTdatEntry(const TdatEntry &inTic);
	void DeleteTdatEntry(UInt32 inIndex);
	UInt32 Count();
	UInt32 FindTdatEntry(OSType inType, 
									ResIDT inID, 
									TdatEntry &outTdatEntry);
	
};

#endif
