// ===========================================================================
//	LSingleResourceDoc.cp				PowerPlant 1.9.3	©1994-1998 Metrowerks Inc.
// ===========================================================================
//
//	Document which associates one file with one window

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "LSingleResourceDoc.h"
#include <LWindow.h>
#include <LFile.h>

#include <LString.h>
#include <PP_Messages.h>

#include <AERegistry.h>
#include <AEObjects.h>
#include <AEPackObject.h>
#include "FileCopy.h"
#include <UResourceMgr.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	€ LSingleResourceDoc							Default Constructor		  [public]
// ---------------------------------------------------------------------------
//

LSingleResourceDoc::LSingleResourceDoc()
{
	mWindow = nil;
	mTempFileRefNum   = -1;
}


// ---------------------------------------------------------------------------
//	€ LSingleResourceDoc(LCommander*)				Constructor				  [public]
// ---------------------------------------------------------------------------

LSingleResourceDoc::LSingleResourceDoc(
	LCommander*		inSuper)
	
	: LDocument(inSuper)
{
	mWindow = nil;
	mTempFileRefNum   = -1;
}


// ---------------------------------------------------------------------------
//	€ ~LSingleResourceDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

LSingleResourceDoc::~LSingleResourceDoc()
{
	CloseResourceFork(false);
	delete mWindow;
}


// ---------------------------------------------------------------------------
//	€ AllowSubRemoval												  [public]
// ---------------------------------------------------------------------------

Boolean
LSingleResourceDoc::AllowSubRemoval(
	LCommander*		inSub)
{
	if (inSub == mWindow) {
	
			// Check if the current AppleEvent is a "close" event
			// sent to the Window. If so, we handle it as if the
			// "close" event were sent to the Document
			 
		AppleEvent	currentEvent;
		DescType	theType;
		DescType	theAttr = typeNull;
		Size		theSize;
		::AEGetTheCurrentEvent(&currentEvent);
		if (currentEvent.descriptorType != typeNull) {
			::AEGetAttributePtr(&currentEvent, keyEventClassAttr,
				typeType, &theType, &theAttr, sizeof(DescType),
				&theSize);
			if (theAttr == kAECoreSuite) {
				::AEGetAttributePtr(&currentEvent, keyEventIDAttr,
					typeType, &theType, &theAttr, sizeof(DescType),
					&theSize);
				if (theAttr == kAEClose) {
					DoAEClose(currentEvent);
					return false;
				}
			}
		}
		
		AttemptClose(true);			// A non-AppleEvent close
		return false;

	} else {
		return true;
	}
}


// ---------------------------------------------------------------------------
//	€ GetDescriptor													  [public]
// ---------------------------------------------------------------------------
//	Pass back the name of a Document

StringPtr
LSingleResourceDoc::GetDescriptor(
	Str255	outDescriptor) const
{
	if (mIsSpecified) {
		LString::CopyPStr(mResFSSpec.name, outDescriptor);
	} else if (mWindow != nil) {	// No File, use name of its Window
		mWindow->GetDescriptor(outDescriptor);
	
	} else {						// No File and No Window
		outDescriptor[0] = 0;		//   Document name is empty string
	}
	
	return outDescriptor;
}


// ---------------------------------------------------------------------------
//	€ UsesFileSpec													  [public]
// ---------------------------------------------------------------------------
//	Returns whether the Document's File has the given FSSpec

Boolean
LSingleResourceDoc::UsesFileSpec(
	const FSSpec&	inFileSpec) const
{
	return LFile::EqualFileSpec(mResFSSpec, inFileSpec);
}

// ---------------------------------------------------------------------------
//	€ OpenResourceFork
// ---------------------------------------------------------------------------
//	Open the resource fork of a File with the specified permissions and
//	return the reference number for the opened fork
//
//	A resource fork must be Open before you can read or write resources

void
LSingleResourceDoc::OpenResourceFork(const FSSpec&	inFileSpec)
{
	StCurResFile i;
	mResFSSpec = inFileSpec;
	CopyOrigFileToTempFile();
	mTempFileRefNum = ::FSpOpenResFile(&mTempFSSpec, fsRdWrPerm);
		
    if (mTempFileRefNum == -1) {	// Open failed
		ThrowIfResError_();
	}
}

// ---------------------------------------------------------------------------
//	€ CloseResourceFork
// ---------------------------------------------------------------------------
//	Close the resource fork of a File

void
LSingleResourceDoc::CloseResourceFork(bool inSave)
{
	if (mTempFileRefNum != -1) {
		::CloseResFile(mTempFileRefNum);
		mTempFileRefNum = -1;
		::FlushVol(nil, mTempFSSpec.vRefNum);
		if(inSave)
		{
			ThrowIfOSErr_(FSpExchangeFiles(&mResFSSpec,&mTempFSSpec));
		}
		DeleteTempFile();
	}
	
}

void
LSingleResourceDoc::UpdateTempFile()
{
	if (mTempFileRefNum != -1) 
	{
		::CloseResFile(mTempFileRefNum);
		::FlushVol(nil, mTempFSSpec.vRefNum);
		mTempFileRefNum = ::FSpOpenResFile(&mTempFSSpec, fsRdWrPerm);
		
    	if (mTempFileRefNum == -1) 
    	{	// Open failed
			ThrowIfResError_();
		}
	}
}

// ---------------------------------------------------------------------------
//	€ MakeCurrent													  [public]
// ---------------------------------------------------------------------------
//	Make this Document the current one by selecting its Window

void
LSingleResourceDoc::MakeCurrent()
{
	if (mWindow != nil) {
		mWindow->Select();
	}
}

void LSingleResourceDoc::CopyOrigFileToTempFile()
{
	SInt16 theVRef;
	SInt32 theDirID;
	LStr255 theUniqueName;
	theUniqueName.Assign((SInt32)TickCount());
	OSErr err = FindFolder(kOnSystemDisk, kTemporaryFolderType,true,&theVRef,&theDirID);
	err = FSMakeFSSpec(theVRef,theDirID,nil, &mTempFSSpec);
	ThrowIfOSErr_(FSpFileCopy(&mResFSSpec,&mTempFSSpec,theUniqueName,nil,0L,true));
	err = FSMakeFSSpec(theVRef,theDirID,theUniqueName, &mTempFSSpec);
}

void LSingleResourceDoc::DeleteTempFile()
{
	ThrowIfOSErr_(FSpDelete(&mTempFSSpec));
}

PP_End_Namespace_PowerPlant
