// ===========================================================================
//	UTPlutBrushResource.cpp			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the plut resource
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Dec 28/98 Initial Implementation
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


#include "UTPlutBrushResource.h"
#include "TThemes.h"
// ---------------------------------------------------------------------------

UTPlutBrushResource::UTPlutBrushResource()
{
}
			
UTPlutBrushResource::~UTPlutBrushResource()
{
}

void UTPlutBrushResource::Init(
				ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/)
{
	UTPlutResource::Init(kRequiredPlutBrushResourceID, inResFileID, inCreate, inThrowFail);
}
			
Handle 	UTPlutBrushResource::BuildBaseResource()
{
	Handle newRes = ::NewHandleClear(sizeof(PlutHeader) + (sizeof(PlutEntry) * kPlutBrushColorCount));
	ThrowIfMemFail_(newRes);
	((PlutHeader*)(*newRes))->colorDepth = k256Colors;
	((PlutHeader*)(*newRes))->unknown = kPlutUnknownValue1;
	((PlutHeader*)(*newRes))->plutEntryCount = kPlutBrushColorCount;
	return newRes;
}

void UTPlutBrushResource::GetDialogBackgroundActiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushDialogBackgroundActive - 1,outPlut);
}

void UTPlutBrushResource::GetDialogBackgroundInactiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushDialogBackgroundInactive - 1 ,outPlut);
}

void UTPlutBrushResource::GetAlertBackgroundActiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushAlertBackgroundActive - 1,outPlut);
}

void UTPlutBrushResource::GetAlertBackgroundInactiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushAlertBackgroundInactive - 1,outPlut);
}

void UTPlutBrushResource::GetModelessDialogBackgroundActiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushModelessDialogBackgroundActive - 1,outPlut);
}

void UTPlutBrushResource::GetModelessDialogBackgroundInactiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushModelessDialogBackgroundInactive - 1,outPlut);
}

void UTPlutBrushResource::GetUtilityWindowBackgroundActiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushUtilityWindowBackgroundActive - 1,outPlut);
}

void UTPlutBrushResource::GetUtilityWindowBackgroundInactiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushUtilityWindowBackgroundInactive - 1,outPlut);
}

void UTPlutBrushResource::GetListViewSortBackgroundActiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushListViewSortColumnBackground - 1,outPlut);
}

void UTPlutBrushResource::GetListViewBackgroundInactiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushListViewBackground - 1,outPlut);
}

void UTPlutBrushResource::GetIconLabelBackgroundBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushIconLabelBackground - 1,outPlut);
}

void UTPlutBrushResource::GetListViewSeperatorBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushListViewSeparator - 1,outPlut);
}

void UTPlutBrushResource::GetChasingArrowsBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushChasingArrows - 1,outPlut);
}

void UTPlutBrushResource::GetDragHiliteBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushDragHilite - 1,outPlut);
}

void UTPlutBrushResource::GetDocumentWindowBackgroundBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushDocumentWindowBackground - 1,outPlut);
}

void UTPlutBrushResource::GetFinderWindowBackgroundBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushFinderWindowBackground - 1,outPlut);
}

void UTPlutBrushResource::GetScrollBarDelimiterActiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushScrollBarDelimiterActive - 1,outPlut);
}

void UTPlutBrushResource::GetScrollBarDelimiterInactiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushScrollBarDelimiterInactive - 1,outPlut);
}

void UTPlutBrushResource::GetFocusHighlightBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushFocusHighlight - 1,outPlut);
}

void UTPlutBrushResource::GetPopupArrowActiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushPopupArrowActive - 1,outPlut);
}

void UTPlutBrushResource::GetPopupArrowPressedBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushPopupArrowPressed - 1,outPlut);
}

void UTPlutBrushResource::GetPopupArrowInactiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushPopupArrowInactive - 1,outPlut);
}

void UTPlutBrushResource::GetAppleGuideCoachMarkBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushAppleGuideCoachmark - 1,outPlut);
}

void UTPlutBrushResource::GetIconLabelBackgroundSelectedBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushIconLabelBackgroundSelected - 1,outPlut);
}

void UTPlutBrushResource::GetStaticAreaFillBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushStaticAreaFill - 1,outPlut);
}

void UTPlutBrushResource::GetActiveAreaFillBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushActiveAreaFill - 1,outPlut);
}

void UTPlutBrushResource::GetButtonFrameActiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonFrameActive - 1,outPlut);
}

void UTPlutBrushResource::GetButtonFrameInactiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonFrameInactive - 1,outPlut);
}

void UTPlutBrushResource::GetButtonFaceActiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonFaceActive - 1,outPlut);
}

void UTPlutBrushResource::GetButtonFaceInactiveBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonFaceInactive - 1,outPlut);
}

void UTPlutBrushResource::GetButtonFacePressedBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonFacePressed - 1,outPlut);
}

void UTPlutBrushResource::GetButtonActiveDarkShadowBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonActiveDarkShadow - 1,outPlut);
}

void UTPlutBrushResource::GetButtonActiveDarkHighlightBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonActiveDarkHighlight - 1,outPlut);
}

void UTPlutBrushResource::GetButtonActiveLightShadowBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonActiveLightShadow - 1,outPlut);
}

void UTPlutBrushResource::GetButtonActiveLightHighlightBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonActiveLightHighlight - 1,outPlut);
}

void UTPlutBrushResource::GetButtonInactiveDarkShadowBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonInactiveDarkShadow - 1,outPlut);
}

void UTPlutBrushResource::GetButtonInactiveDarkHighlightBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonInactiveDarkHighlight - 1,outPlut);
}

void UTPlutBrushResource::GetButtonInactiveLightShadowBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonInactiveLightShadow - 1,outPlut);
}

void UTPlutBrushResource::GetButtonInactiveLightHighlightBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonInactiveLightHighlight - 1,outPlut);
}

void UTPlutBrushResource::GetButtonPressedDarkShadowBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonPressedDarkShadow - 1,outPlut);
}

void UTPlutBrushResource::GetButtonPressedDarkHighlightBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonPressedDarkHighlight - 1,outPlut);
}

void UTPlutBrushResource::GetButtonPressedLightShadowBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonPressedLightShadow - 1,outPlut);
}

void UTPlutBrushResource::GetButtonPressedLightHighlightBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushButtonPressedLightHighlight - 1,outPlut);
}

void UTPlutBrushResource::GetBevelActiveLightBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushBevelActiveLight - 1,outPlut);
}

void UTPlutBrushResource::GetBevelActiveDarkBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushBevelActiveDark - 1,outPlut);
}

void UTPlutBrushResource::GetBevelInactiveLightBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushBevelInactiveLight - 1,outPlut);
}

void UTPlutBrushResource::GetBevelInactiveDarkBrush(PlutEntry &outPlut)
{
	GetPlutEntry(kThemeBrushBevelInactiveDark - 1,outPlut);
}

void UTPlutBrushResource::SetDialogBackgroundActiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushDialogBackgroundActive - 1,inPlut);
}

void UTPlutBrushResource::SetDialogBackgroundInactiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushDialogBackgroundInactive - 1 ,inPlut);
}

void UTPlutBrushResource::SetAlertBackgroundActiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushAlertBackgroundActive - 1,inPlut);
}

void UTPlutBrushResource::SetAlertBackgroundInactiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushAlertBackgroundInactive - 1,inPlut);
}

void UTPlutBrushResource::SetModelessDialogBackgroundActiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushModelessDialogBackgroundActive - 1,inPlut);
}

void UTPlutBrushResource::SetModelessDialogBackgroundInactiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushModelessDialogBackgroundInactive - 1,inPlut);
}

void UTPlutBrushResource::SetUtilityWindowBackgroundActiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushUtilityWindowBackgroundActive - 1,inPlut);
}

void UTPlutBrushResource::SetUtilityWindowBackgroundInactiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushUtilityWindowBackgroundInactive - 1,inPlut);
}

void UTPlutBrushResource::SetListViewSortBackgroundActiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushListViewSortColumnBackground - 1,inPlut);
}

void UTPlutBrushResource::SetListViewBackgroundInactiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushListViewBackground - 1,inPlut);
}

void UTPlutBrushResource::SetIconLabelBackgroundBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushIconLabelBackground - 1,inPlut);
}

void UTPlutBrushResource::SetListViewSeperatorBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushListViewSeparator - 1,inPlut);
}

void UTPlutBrushResource::SetChasingArrowsBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushChasingArrows - 1,inPlut);
}

void UTPlutBrushResource::SetDragHiliteBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushDragHilite - 1,inPlut);
}

void UTPlutBrushResource::SetDocumentWindowBackgroundBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushDocumentWindowBackground - 1,inPlut);
}

void UTPlutBrushResource::SetFinderWindowBackgroundBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushFinderWindowBackground - 1,inPlut);
}

void UTPlutBrushResource::SetScrollBarDelimiterActiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushScrollBarDelimiterActive - 1,inPlut);
}

void UTPlutBrushResource::SetScrollBarDelimiterInactiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushScrollBarDelimiterInactive - 1,inPlut);
}

void UTPlutBrushResource::SetFocusHighlightBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushFocusHighlight - 1,inPlut);
}

void UTPlutBrushResource::SetPopupArrowActiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushPopupArrowActive - 1,inPlut);
}

void UTPlutBrushResource::SetPopupArrowPressedBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushPopupArrowPressed - 1,inPlut);
}

void UTPlutBrushResource::SetPopupArrowInactiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushPopupArrowInactive - 1,inPlut);
}

void UTPlutBrushResource::SetAppleGuideCoachMarkBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushAppleGuideCoachmark - 1,inPlut);
}

void UTPlutBrushResource::SetIconLabelBackgroundSelectedBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushIconLabelBackgroundSelected - 1,inPlut);
}

void UTPlutBrushResource::SetStaticAreaFillBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushStaticAreaFill - 1,inPlut);
}

void UTPlutBrushResource::SetActiveAreaFillBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushActiveAreaFill - 1,inPlut);
}

void UTPlutBrushResource::SetButtonFrameActiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonFrameActive - 1,inPlut);
}

void UTPlutBrushResource::SetButtonFrameInactiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonFrameInactive - 1,inPlut);
}

void UTPlutBrushResource::SetButtonFaceActiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonFaceActive - 1,inPlut);
}

void UTPlutBrushResource::SetButtonFaceInactiveBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonFaceInactive - 1,inPlut);
}

void UTPlutBrushResource::SetButtonFacePressedBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonFacePressed - 1,inPlut);
}

void UTPlutBrushResource::SetButtonActiveDarkShadowBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonActiveDarkShadow - 1,inPlut);
}

void UTPlutBrushResource::SetButtonActiveDarkHighlightBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonActiveDarkHighlight - 1,inPlut);
}

void UTPlutBrushResource::SetButtonActiveLightShadowBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonActiveLightShadow - 1,inPlut);
}

void UTPlutBrushResource::SetButtonActiveLightHighlightBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonActiveLightHighlight - 1,inPlut);
}

void UTPlutBrushResource::SetButtonInactiveDarkShadowBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonInactiveDarkShadow - 1,inPlut);
}

void UTPlutBrushResource::SetButtonInactiveDarkHighlightBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonInactiveDarkHighlight - 1,inPlut);
}

void UTPlutBrushResource::SetButtonInactiveLightShadowBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonInactiveLightShadow - 1,inPlut);
}

void UTPlutBrushResource::SetButtonInactiveLightHighlightBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonInactiveLightHighlight - 1,inPlut);
}

void UTPlutBrushResource::SetButtonPressedDarkShadowBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonPressedDarkShadow - 1,inPlut);
}

void UTPlutBrushResource::SetButtonPressedDarkHighlightBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonPressedDarkHighlight - 1,inPlut);
}

void UTPlutBrushResource::SetButtonPressedLightShadowBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonPressedLightShadow - 1,inPlut);
}

void UTPlutBrushResource::SetButtonPressedLightHighlightBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushButtonPressedLightHighlight - 1,inPlut);
}

void UTPlutBrushResource::SetBevelActiveLightBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushBevelActiveLight - 1,inPlut);
}

void UTPlutBrushResource::SetBevelActiveDarkBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushBevelActiveDark - 1,inPlut);
}

void UTPlutBrushResource::SetBevelInactiveLightBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushBevelInactiveLight - 1,inPlut);
}

void UTPlutBrushResource::SetBevelInactiveDarkBrush(PlutEntry &inPlut)
{
	SetPlutEntry(kThemeBrushBevelInactiveDark - 1,inPlut);
}
