// ===========================================================================
//	LCoordinateHierTable.h			PowerPlant 2.0		©1995-1999 Metrowerks Inc.
// ===========================================================================

#ifndef _H_LTextHierTable
#define _H_LTextHierTable
#pragma once

#include <LHierarchyTable.h>
#include <UTextTraits.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

class UTLayoutResource;
// ---------------------------------------------------------------------------


class	LCoordinateHierTable : public LHierarchyTable {
public:
	enum { class_ID = FOUR_CHAR_CODE('COHT') };
	
						LCoordinateHierTable(
								LStream				*inStream);
	virtual				~LCoordinateHierTable();
	
	void	SetLayoutResource(UTLayoutResource* inResource, Boolean inRefresh = true);
	UInt32	FindWidthOfWidestCell(TableIndexT	inCol);
protected:
	ResIDT				mLeafTextTraits;
	ResIDT				mParentTextTraits;
	UInt16				mFirstIndent;
	UInt16				mLevelIndent;

	virtual void		DrawCell(
								const STableCell	&inCell,
								const Rect			&inLocalRect);
								
	virtual void		HiliteCellActively(
								const STableCell	&inCell,
								Boolean				inHilite);
	virtual void		HiliteCellInactively(
								const STableCell	&inCell,
								Boolean				inHilite);
								
	void 	AddLayoutCoordinates(UTLayoutResource *inResource, SInt32 inCoordinate, UInt32 &ioWideOpenIndex);	
	void 	ConvertCoordinateToString(SInt16 inCoord, LStr255 &outString);				
	UTLayoutResource *mResource;
};


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
