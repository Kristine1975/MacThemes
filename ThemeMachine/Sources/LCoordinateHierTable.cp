// ===========================================================================
//	LCoordinateHierTable.cp			PowerPlant 2.0		©1995-1999 Metrowerks Inc.
// ===========================================================================

#ifdef PowerPlant_PCH
#include PowerPlant_PCH
#endif

#include "LCoordinateHierTable.h"
#include <LCollapsableTree.h>
#include <UDrawingUtils.h>
#include <UTextTraits.h>
#include "UTLayoutResource.h"
#include "LCoordTableGeometry.h"
#include <LTableSingleSelector.h>
#include <LTableArrayStorage.h>
#include <UAttachments.h>

const ResID kCoordinateStringsID = 308;
const UInt32 kCoordinateIndex = 1;
const UInt32 kDefaultTopIndex = 2;
const UInt32 kDefaultLeftIndex = 3;
const UInt32 kDefaultBottomIndex = 4;
const UInt32 kDefaultRightIndex = 5;
const UInt32 kNoCoordinateIndex = 6;


LCoordinateHierTable::LCoordinateHierTable(
	LStream	*inStream)
		: LHierarchyTable(inStream)
{
	mFirstIndent = 24;
	mLevelIndent = 12;
	mLeafTextTraits = 130;
	mParentTextTraits = 131;
	
		// Create the helpers for this LTableView.
	// Being a hierarchy table, it automatically gets LNodeArrayTree.
	
	TextTraitsRecord theTraits;
	UTextTraits::LoadTextTraits(mParentTextTraits,theTraits);
	mTableGeometry = new LCoordTableGeometry( this, mFrameSize.width, 14 );
	mTableSelector = new LTableSingleSelector( this );
	mTableStorage = new LTableArrayStorage( this, sizeof(Str255) );
	
	// Insert a single column.
	InsertCols( 1, 0, nil, nil, false );
	
	// Add a key scroll attachment.
	AddAttachment( new LKeyScrollAttachment( this ) );
}


LCoordinateHierTable::~LCoordinateHierTable()
{
}


void
LCoordinateHierTable::DrawCell(
	const STableCell	&inCell,
	const Rect			&inLocalRect)
{
	TableIndexT	woRow = mCollapsableTree->GetWideOpenIndex(inCell.row);
	
	DrawDropFlag(inCell, woRow);
	
	STableCell	woCell(woRow, inCell.col);
	SInt16		theCoordinate;
	UInt32		dataSize = sizeof(theCoordinate);
	GetCellData(woCell, &theCoordinate, dataSize);
	
	ResIDT	textTraitsID = mLeafTextTraits;
	if (mCollapsableTree->IsCollapsable(woRow)) {
		textTraitsID = mParentTextTraits;
	}
	UTextTraits::SetPortTextTraits(textTraitsID);
	
	UInt32	nestingLevel = mCollapsableTree->GetNestingLevel(woRow);
	
	::MoveTo((SInt16) (inLocalRect.left + mFirstIndent + nestingLevel * mLevelIndent),
			 (SInt16) (inLocalRect.bottom - 4));
			 
	LStr255 theString;
	ConvertCoordinateToString(theCoordinate,theString);
	::DrawString(theString);
}

UInt32	LCoordinateHierTable::FindWidthOfWidestCell(TableIndexT	inCol)
{
	UInt32 theWidth = 0;
	TableIndexT rowCount, colCount;
	GetTableSize(rowCount,colCount);
	for(UInt32 i = 1; i <= rowCount; i++)
	{
		STableCell theCell(i,inCol);
		Rect theLocalRect;
		CalcLocalFrameRect(theLocalRect);
		UInt32 tempWidth;
		TableIndexT wideOpen = GetWideOpenIndex(i);
		ResIDT	textTraitsID = mLeafTextTraits;
		if (mCollapsableTree->IsCollapsable(wideOpen)) {
			textTraitsID = mParentTextTraits;
		}
		UTextTraits::SetPortTextTraits(textTraitsID);
		SInt16		theCoordinate;
		UInt32		dataSize = sizeof(theCoordinate);
		GetCellData(theCell, &theCoordinate, dataSize);
		
		UInt32	nestingLevel = mCollapsableTree->GetNestingLevel(wideOpen);
		LStr255 theString;
		ConvertCoordinateToString(theCoordinate,theString);
		tempWidth = theLocalRect.left + mFirstIndent + nestingLevel * mLevelIndent;
		tempWidth += StringWidth(theString);
		if(tempWidth > theWidth)
		{
			theWidth = tempWidth;
		}
	}	
	return theWidth;
}

void
LCoordinateHierTable::HiliteCellActively(
	const STableCell	&inCell,
	Boolean				/* inHilite */)
{
	Rect	cellFrame;
	if (GetLocalCellRect(inCell, cellFrame) && FocusExposed()) {
		UDrawingUtils::SetHiliteModeOn();
		cellFrame.left += (SInt16) mFirstIndent;
		::MacInvertRect(&cellFrame);
	}
}


void
LCoordinateHierTable::HiliteCellInactively(
	const STableCell	&inCell,
	Boolean				/* inHilite */)
{
	Rect	cellFrame;
	if (GetLocalCellRect(inCell, cellFrame) && FocusExposed()) {
		cellFrame.left += (SInt16) mFirstIndent;
		UDrawingUtils::SetHiliteModeOn();
		::PenNormal();
		::PenMode(srcXor);
		::MacFrameRect(&cellFrame);
	}
}

void	LCoordinateHierTable::SetLayoutResource(UTLayoutResource* inResource, Boolean inRefresh)
{
	mResource = inResource;
	
	for(SInt16 i = 1; i <= inResource->CountCoordinates(); i++)
	{	
		InsertSiblingRows(1,i,&i,sizeof(SInt16),false,false);
	}
	UInt32 wideOpenIndex = 1;
	for(SInt16 i = 1; i <= inResource->CountCoordinates(); i++)
	{	
		mCollapsableTree->CollapseNode(wideOpenIndex);
		AddLayoutCoordinates(inResource,i,wideOpenIndex);
		wideOpenIndex++;
	}	
	if(inRefresh)
	{
		Refresh();
	}
}

void LCoordinateHierTable::AddLayoutCoordinates(UTLayoutResource *inResource, SInt32 inCoordinate, UInt32 &ioWideOpenIndex)
{
	LayoutCoordinate theCoordinate;
	inResource->GetLayoutCoordinate(inCoordinate,theCoordinate);
	
	switch(theCoordinate.coordinateReference1)
	{
		case kDefaultTopCoordinate:
		case kDefaultLeftCoordinate:
		case kDefaultBottomCoordinate:
		case kDefaultRightCoordinate:
		case kNoCoordinate:
		{
			InsertChildRows(1,ioWideOpenIndex,&theCoordinate.coordinateReference1,sizeof(SInt16),false,false);
			ioWideOpenIndex++;
		}
		break;
	
		default:
		{
			InsertChildRows(1,ioWideOpenIndex,&theCoordinate.coordinateReference1,sizeof(SInt16),false,false);
			ioWideOpenIndex++;
			AddLayoutCoordinates(inResource,theCoordinate.coordinateReference1,ioWideOpenIndex);
		}
		break;
	}
	
	switch(theCoordinate.coordinateReference2)
	{
		case kDefaultTopCoordinate:
		case kDefaultLeftCoordinate:
		case kDefaultBottomCoordinate:
		case kDefaultRightCoordinate:
		case kNoCoordinate:
		{
			InsertSiblingRows(1,ioWideOpenIndex,&theCoordinate.coordinateReference2,sizeof(SInt16),false,false);
			ioWideOpenIndex++;
		}
		break;
			
		default:
		{
			InsertSiblingRows(1,ioWideOpenIndex,&theCoordinate.coordinateReference2,sizeof(SInt16),false,false);
			ioWideOpenIndex++;
			AddLayoutCoordinates(inResource,theCoordinate.coordinateReference2,ioWideOpenIndex);
		}
		break;
	}
	
}


void LCoordinateHierTable::ConvertCoordinateToString(SInt16 inCoord, LStr255 &outString)
{
	switch(inCoord)
	{
		case kDefaultTopCoordinate:
		{
			LStr255 theCoordinateString(kCoordinateStringsID,kDefaultTopIndex);
			outString  = theCoordinateString;
		}
		break;
			
		case kDefaultLeftCoordinate:
		{
			LStr255 theCoordinateString(kCoordinateStringsID,kDefaultLeftIndex);
			outString  = theCoordinateString;
		}
		break;
			
		case kDefaultBottomCoordinate:
		{
			LStr255 theCoordinateString(kCoordinateStringsID,kDefaultBottomIndex);
			outString  = theCoordinateString;
		}
		break;
			
		case kDefaultRightCoordinate:
		{
			LStr255 theCoordinateString(kCoordinateStringsID,kDefaultRightIndex);
			outString  = theCoordinateString;
		}
		break;
	
		case kNoCoordinate:
		{
			LStr255 theCoordinateString(kCoordinateStringsID,kNoCoordinateIndex);
			outString  = theCoordinateString;
		}
		break;
		
		default:
		{
			LStr255 theCoordinateString(kCoordinateStringsID,kCoordinateIndex);
			LStr255 theNumberString(inCoord);
			outString = theCoordinateString + theNumberString;
		}
		break;
	}
}