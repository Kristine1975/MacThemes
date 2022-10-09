// ===========================================================================
//	LSingleResourceDoc.h		PowerPlant 1.9.3	©1994-1998 Metrowerks Inc.
// ===========================================================================
//
//	Document which associates one file with one window

#ifndef _H_LSingleResourceDoc
#define _H_LSingleResourceDoc
#pragma once

#include <LDocument.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	LWindow;

// ---------------------------------------------------------------------------

class LSingleResourceDoc : public LDocument {
public:
						LSingleResourceDoc();
						
						LSingleResourceDoc(
								LCommander*		inSuper);
								
	virtual				~LSingleResourceDoc();
	
	virtual Boolean		AllowSubRemoval(
								LCommander*		inSub);
	
	virtual StringPtr	GetDescriptor(
								Str255			outDescriptor) const;
								
	virtual Boolean		UsesFileSpec(
								const FSSpec&	inFileSpec) const;
								
	virtual void		MakeCurrent();
	virtual void		UpdateTempFile();
	
	LWindow*			GetWindow() const	{ return mWindow; }
	
	ResFileRefNum		GetResFileRefNum() const		{ return mTempFileRefNum; }
	
	void				OpenResourceFork(const FSSpec&	inFileSpec);
	void				CloseResourceFork(bool inSave);
							  
protected:
	LWindow*		mWindow;
	ResFileRefNum	mTempFileRefNum;
	FSSpec			mResFSSpec;
	FSSpec			mTempFSSpec;
	
	void CopyOrigFileToTempFile();
	void DeleteTempFile();

};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif