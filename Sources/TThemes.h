// ===========================================================================
//	TThemes.h			   Allegro Themes Project
// ===========================================================================
//
//	All the definitions for themes resources
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

#pragma once

//Req'd Layo Resource IDs
const ResIDT kThemeLayoActiveDocumentWindowID = 128;
const ResIDT kThemeLayoInactiveDocumentWindowID = 129;
const ResIDT kThemeLayoActiveDialogWindowID = 130;
const ResIDT kThemeLayoInactiveDialogWindowID =131;
const ResIDT kThemeLayoActiveAlertWindowID = 132;
const ResIDT kThemeLayoInactiveAlertWindowID = 133;
const ResIDT kThemeLayoActiveMovableModalWindowID = 134;
const ResIDT kThemeLayoInactiveMovableModalWindowID = 135;
const ResIDT kThemeLayoActiveFloatingWindowID = 136;
const ResIDT kThemeLayoInactiveFloatingWindowID = 137;
const ResIDT kThemeLayoActiveSideFloatingWindowID = 138;
const ResIDT kThemeLayoInactiveSideFloatingWindowID = 139;
const ResIDT kThemeLayoActiveDrawerWindowID = 140;
const ResIDT kThemeLayoInactiveDrawerWindowID = 141;
const ResIDT kThemeLayoActiveMovableAlertWindowID = 142;
const ResIDT kThemeLayoInactiveMovableAlertWindowID = 143;
const ResIDT kThemeLayoRootMenuBackgroundID = 256;
const ResIDT kThemeLayoPullDownMenuBackgroundID = 257;
const ResIDT kThemeLayoPopUpMenuBackgroundID = 258;
const ResIDT kThemeLayoHierarchicalMenuBackgroundID = 259;
const ResIDT kThemeLayoRootMenuItemID = 260;
const ResIDT kThemeLayoTextMenuItemID = 261;
const ResIDT kThemeLayoProcessMenuHandleID = 262;
const ResIDT kThemeLayoMenuItemDividerID = 263;
const ResIDT kThemeLayoTabPaneID = 300;
const ResIDT kThemeLayoNorthTabID = 310;
const ResIDT kThemeLayoNorthSmallTabID = 315;
const ResIDT kThemeLayoSouthTabID = 320;
const ResIDT kThemeLayoSouthSmallTabID = 325;
const ResIDT kThemeLayoWestTabID = 330;
const ResIDT kThemeLayoWestSmallTabID = 335;
const ResIDT kThemeLayoEastTabID = 340;
const ResIDT kThemeLayoEastSmallTabID = 345;
const ResIDT kThemeLayoHorizontalScrollBarID = 400;
const ResIDT kThemeLayoVerticalScrollBarID = 405;
const ResIDT kThemeLayoSmallHorizontalScrollBarID = 410;
const ResIDT kThemeLayoSmallVerticalScrollBarID = 415;
const ResIDT kThemeLayoHorizontalSliderID = 420;
const ResIDT kThemeLayoNorthSliderID = 421;
const ResIDT kThemeLayoSouthSliderID = 422;
const ResIDT kThemeLayoVerticalSliderID = 425;
const ResIDT kThemeLayoEastSliderID = 426;
const ResIDT kThemeLayoWestSliderID = 427;
const ResIDT kThemeLayoProgressBarID = 430;
const ResIDT kThemeLayoIndeterminateProgressBarID = 440;
const ResIDT kThemeLayoPushButtonID = 500;
const ResIDT kThemeLayoDefaultPushButtonID = 501;
const ResIDT kThemeLayoCheckBoxLeftToRightID = 510;
const ResIDT kThemeLayoCheckBoxRightToLeftID = 511;
const ResIDT kThemeLayoRadioButtonLeftToRightID = 515;
const ResIDT kThemeLayoRadioButtonRightToLeftID = 516;
const ResIDT kThemeLayoPopupButtonLeftToRightID = 520;
const ResIDT kThemeLayoPopupButtonRightToLeftID = 521;
const ResIDT kThemeLayoArrowButtonID = 525;
const ResIDT kThemeLayoSmallBevelButtonID = 530;
const ResIDT kThemeLayoMediumBevelButtonID = 531;
const ResIDT kThemeLayoLargeBevelButtonID = 532;
const ResIDT kThemeLayoLittleArrowsButtonID = 540;
const ResIDT kThemeLayoDisclosureButtonID = 550;
const ResIDT kThemeLayoGenericImageWellID = 600;

//Req'd Frme Resource IDs
const ResIDT kThemeFrmePrimaryGroupID = 500;
const ResIDT kThemeFrmeInactivePrimaryGroupID = 501;
const ResIDT kThemeFrmeSceondaryGroupID = 502;
const ResIDT kThemeFrmeInactiveSecondaryGroupID = 503;
const ResIDT kThemeFrmeHorizontalSeparatorID = 510;
const ResIDT kThemeFrmeInactiveHorizontalSeparatorID = 511;
const ResIDT kThemeFrmeVerticalSeparatorID = 512;
const ResIDT kThemeFrmeInactiveVerticalSeparatorID = 513;
const ResIDT kThemeFrmeEditTextFrameID = 520;
const ResIDT kThemeFrmeInactiveEditTextFrameID = 521;
const ResIDT kThemeFrmeListBoxFrameID = 530;
const ResIDT kThemeFrmeInactiveListBoxFrameID = 531;
const ResIDT kThemeFrmeDialogContentEdgeID = 540;
const ResIDT kThemeFrmeInactiveDialogContentEdgeID = 541;
const ResIDT kThemeFrmeWindowHeaderID = 542;
const ResIDT kThemeFrmeInactiveWindowHeaderID = 543;
const ResIDT kThemeFrmeWindowPlacardID = 544;
const ResIDT kThemeFrmeInactiveWindowPlacardID = 545;
const ResIDT kThemeFrmePressedWindowPlacardID = 546;
const ResIDT kThemeFrmeFocusGenericRectID = 560;

//Other Stuff
const UInt32 kThemeTextColorCount = 46;
const UInt16 kPlutUnknownValue1 = 42;
const UInt32 kPlutBrushColorCount = 47;

const ResID kTransparentPixPatID = 128;

const ResIDT kRequiredPlutBrushResourceID = 386;
const ResIDT kUserPlutBrushResourceID = 387;

const ResIDT kThemeTextColorResourceID = 384;
const ResIDT kThemeInfoResourceID = 128;
const ResIDT kThemeTicResourceID	= 384;
const ResIDT kThemeTdatResourceID = 1;
const ResIDT kThemePreferencesID = 128;

const FourCharCode kTinfHorizontalSliderTickLeft = 'hslt'; 
const FourCharCode kTinfVerticalSliderTickTop = 'vslt'; 
const FourCharCode kTinfSliderHorizontalThumbWidth = 'lhtw'; 
const FourCharCode kTinfSliderVerticalThumbHeight = 'lvth'; 
const FourCharCode kTinfMenuSeparatorHeight = 'msht'; 
const FourCharCode kTinfMenuBarHeight = 'mbht'; 
const FourCharCode kTinfMenuTitleLeftOffset = 'mtlo'; 
const FourCharCode kTinfMenuTitleRightOffset = 'mtro'; 
const FourCharCode kTinfScrollHorizontalThumbWidth = 'mhtw'; 
const FourCharCode kTinfScrollVerticalThumbHeight = 'mvth'; 
const FourCharCode kTinfSmallScrollHorizontalThumbWidth = 'shtw'; 
const FourCharCode kTinfSmallScrollVerticalThumbHeight = 'svth'; 
const FourCharCode kTinfMinimumColorDepth = 'mind'; 
const FourCharCode kTinfVersion = 'vers'; 

const CommandT cmd_SelectUserBrushMessage = 'SUBM';
const CommandT cmd_SelectRequiredBrushMessage = 'SRBM';
const CommandT cmd_EditTestTheme = 'TETH';
const CommandT cmd_ShowThemeSettings = 13000;
const CommandT cmd_ShowUserBrushes = 13001;
const CommandT cmd_ShowReqdBrushes = 13002;
const CommandT cmd_ShowTextColors = 13003;
const CommandT cmd_ShowMagnifyer = 13004;
const CommandT cmd_FocusGenericFrame = 14000;

const CommandT cmd_LayoutBase = 15000;
const CommandT cmd_LayoutActiveDocument = cmd_LayoutBase + kThemeLayoActiveDocumentWindowID;
const CommandT cmd_LayoutGenericImageWell = cmd_LayoutBase + kThemeLayoGenericImageWellID;
const CommandT cmd_EditUserNewBrush = 'NEBR';
const CommandT cmd_EditUserDeleteBrush = 'DEBR';

typedef SInt16 							ResFileID;
typedef SInt32							PlutEntryIndex;

typedef struct
{
	ResIDT resID;
	ResFileID fileID;
	ResType resType;
} FullResourceSpec;

const FourCharCode kTextColorDragFlavor = 'TCDR';
const FourCharCode kBrushDragFlavor = 'BRDR';
const FourCharCode kPictDragFlavor = 'PICT';
const FourCharCode kPxmDragFlavor = 'pxm#';
const FourCharCode kFrmeDragFlavor = 'frme';

const ResID kPencilCursor = 128;
const ResID kEraserCursor = 129;
const ResID kPaintBucketCursor = 130;
const ResID kEyeDropperCursor = 131;
const ResID kZoomInCursor = 136;
const ResID kZoomOutCursor = 137;


//Used for laying out Pxm's with layos
enum
{
	kImageAlignTopLeft = 1,
	kImageAlignTopRight = 2,
	kImageAlignBottomLeft = 3,
	kImageAlignBottomRight =4
};
typedef UInt16 ImageAlignment;