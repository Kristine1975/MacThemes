// ===========================================================================
//	TMagnifyPane.cp					PowerPlant 2.0		©1993-1999 Metrowerks Inc.
// ===========================================================================
//
//	Displays a 'PICT' resource
//
//	TMagnifyPane stores the ID of a PICT resource as a member variable, and
//	always calls GetPicture() to get a Handle to the picture. It purposely
//	does not release the PICT resource when deleted, since other TMagnifyPane
//	views may be using the same picture. For example, you might use the
//	same picture as a background or graphic element in multiple windows.
//
//	If you are concerned about the memory used by the PICT resource, mark
//	it as purgeable in your resource file.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "TMagnifyPane.h"
#include <LStream.h>
#include <UDrawingState.h>



// ---------------------------------------------------------------------------
//	€ TMagnifyPane								Default Constructor		  [public]
// ---------------------------------------------------------------------------

TMagnifyPane::TMagnifyPane()
{
}



// ---------------------------------------------------------------------------
//	€ TMagnifyPane								Stream Constructor	 	 [public]
// ---------------------------------------------------------------------------

TMagnifyPane::TMagnifyPane(
	LStream*	inStream)
	
	: LView(inStream)
{
}




// ---------------------------------------------------------------------------
//	€ DrawSelf													   [protected]
// ---------------------------------------------------------------------------
//	Draw a Picture

void
TMagnifyPane::DrawSelf()
{
	Rect	imageSize;
	CalcPortFrameRect(imageSize);
	
	SInt32 width = imageSize.right - imageSize.left;
	SInt32 height = imageSize.bottom - imageSize.top;
	Point thePoint;
	GetMouse(&thePoint);
	LocalToGlobal(&thePoint);
	
	Rect srcRect = { thePoint.v - height / 20, thePoint.h - width / 20,  thePoint.v + height / 20, thePoint.h + width / 20 };
	
	CopyBits(&UScreenPort::GetScreenPort()->portBits,&GetMacPort()->portBits,&srcRect,&imageSize,srcCopy,NULL);
	
}

void		TMagnifyPane::SpendTime(const EventRecord&	/*inMacEvent*/)
{
	Refresh();
}

