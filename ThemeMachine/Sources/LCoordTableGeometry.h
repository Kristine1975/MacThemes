// ===========================================================================
//	LCoordTableGeometry.h	PowerPlant 2.0			©1995-1999 Metrowerks Inc.
// ===========================================================================
//
//	Manages geometry of a TableView that has the same width and height for
//	every cell

#ifndef _H_LCoordTableGeometry
#define _H_LCoordTableGeometry
#pragma once

#include <UTableHelpers.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

// ---------------------------------------------------------------------------

class	LCoordTableGeometry : public LTableGeometry {
public:
						LCoordTableGeometry(
								LTableView			*inTableView,
								UInt16				inColWidth,
								UInt16				inRowHeight);
	virtual				~LCoordTableGeometry() { }
	
	virtual void		GetImageCellBounds(
								const STableCell	&inCell,
								SInt32				&outLeft,
								SInt32				&outTop,
								SInt32				&outRight,
								SInt32				&outBottom) const;
								
	virtual TableIndexT	GetRowHitBy(
								const SPoint32		&inImagePt) const;
	virtual TableIndexT	GetColHitBy(
								const SPoint32		&inImagePt) const;
								
	virtual void		GetTableDimensions(
								UInt32				&outWidth,
								UInt32				&outHeight) const;
	
	virtual UInt16		GetRowHeight(
								TableIndexT			/* inRow */) const;
						
	virtual void		SetRowHeight(
								UInt16				inHeight,
								TableIndexT			inFromRow,
								TableIndexT			inToRow);
								
	virtual UInt16		GetColWidth(
								TableIndexT			/* inCol */) const;
						
	virtual void		SetColWidth(
								UInt16				inWidth,
								TableIndexT			inFromCol,
								TableIndexT			inToCol);
								
protected:
	virtual UInt32		FindWidthOfWidestCell(TableIndexT	inCol) const;
	SInt16	mRowHeight;

};



#endif
