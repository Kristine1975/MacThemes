// ===========================================================================
//	LCoordTableGeometry.cp		PowerPlant 2.0		©1995-1999 Metrowerks Inc.
// ===========================================================================
//
//	Manages geometry of a TableView that has the same width and height for
//	every cell

#ifdef PowerPlant_PCH
#include PowerPlant_PCH
#endif

#include "LCoordTableGeometry.h"
#include "LCoordinateHierTable.h"

// ---------------------------------------------------------------------------
//	€ LCoordTableGeometry
// ---------------------------------------------------------------------------
//	Construct from input parameters

LCoordTableGeometry::LCoordTableGeometry(
	LTableView		*inTableView,
	UInt16			/*inColWidth*/,
	UInt16			inRowHeight)
		: LTableGeometry(inTableView)
{
	SignalIf_(mTableView == nil);
	
	mRowHeight = 0;

	SetRowHeight(inRowHeight, 0, 0);
}


// ---------------------------------------------------------------------------
//	€ GetImageCellBounds
// ---------------------------------------------------------------------------
//	Pass back the location in Image coords of the specified Cell

void
LCoordTableGeometry::GetImageCellBounds(
	const STableCell	&inCell,
	SInt32				&outLeft,
	SInt32				&outTop,
	SInt32				&outRight,
	SInt32				&outBottom) const
{
	if (mTableView->IsValidCell(inCell)) {
		outRight = (SInt32) inCell.col * GetColWidth(1);
		outLeft = outRight - GetColWidth(1);
		outBottom = (SInt32) inCell.row * mRowHeight;
		outTop = outBottom - mRowHeight;
		
	} else {
		outLeft = 0;
		outRight = 0;
		outTop = 0;
		outBottom = 0;
	}
}


// ---------------------------------------------------------------------------
//	€ GetRowHitBy
// ---------------------------------------------------------------------------
//	Return the index number of the Row containing the specified point

TableIndexT
LCoordTableGeometry::GetRowHitBy(
	const SPoint32	&inImagePt) const
{
	return (TableIndexT) (inImagePt.v / mRowHeight + 1);
}


// ---------------------------------------------------------------------------
//	€ GetColHitBy
// ---------------------------------------------------------------------------
//	Return the index number of the Column containing the specified point

TableIndexT
LCoordTableGeometry::GetColHitBy(
	const SPoint32	&inImagePt) const
{
	return (TableIndexT) (inImagePt.h / GetColWidth(1) + 1);
}


// ---------------------------------------------------------------------------
//	€ GetTableDimensions
// ---------------------------------------------------------------------------
//	Pass back size of the Table based on the number and size of the rows
//	and columns

void
LCoordTableGeometry::GetTableDimensions(
	UInt32	&outWidth,
	UInt32	&outHeight) const
{
	UInt32	rows, columns;
	mTableView->GetTableSize(rows, columns);
	outWidth = columns * GetColWidth(1);
	outHeight = rows * GetRowHeight(1);
}


// ---------------------------------------------------------------------------
//	€ SetRowHeight
// ---------------------------------------------------------------------------
//	Set the height of the specified rows
//
//	For LCoordTableGeometry, all rows have the same height, so inFromRow
//	and inToRow are ignored.

void
LCoordTableGeometry::SetRowHeight(
	UInt16		inHeight,
	TableIndexT	/* inFromRow */,
	TableIndexT	/* inToRow */)
{
	if (inHeight != mRowHeight) {
		mRowHeight = inHeight;
		
		SPoint32	theScrollUnit;
		mTableView->GetScrollUnit(theScrollUnit);
		theScrollUnit.v = inHeight;
		mTableView->SetScrollUnit(theScrollUnit);
		
		mTableView->Refresh();
	}
}


// ---------------------------------------------------------------------------
//	€ SetColWidth
// ---------------------------------------------------------------------------
//	Set the width of the specified columns
//
//	For LCoordTableGeometry, all columns have the same width, so inFromCol
//	and inToCol are ignored.

void
LCoordTableGeometry::SetColWidth(
	UInt16		/*inWidth*/,
	TableIndexT	/* inFromCol */,
	TableIndexT	/* inToCol */)
{
}

UInt16		LCoordTableGeometry::GetRowHeight(
								TableIndexT			/* inRow */) const
{
	return mRowHeight;
}



UInt32
LCoordTableGeometry::FindWidthOfWidestCell(TableIndexT	inCol) const
{
	LCoordinateHierTable *theTable = dynamic_cast<LCoordinateHierTable*>(mTableView);
	SignalIfNot_(theTable);
	return theTable->FindWidthOfWidestCell(inCol);
}

UInt16	LCoordTableGeometry::GetColWidth(TableIndexT	inCol) const
{
	return FindWidthOfWidestCell(inCol);
}
