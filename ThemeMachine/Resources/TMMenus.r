/*
  ThemeMachine.r
  
  Resources
*/

#include <Menus.r>

#include "Localize.h"
#include "ThemeMachine.h"

resource 'MBAR' ( rMenuBar, preload) {
	{ mApple, mFile, mEdit, mLayout, mRequiredFrames, mUserFrames, mPXMs, mPalettes };
};

resource 'MENU' (mApple, "Apple", preload) {
	mApple,
	textMenuProc,
	allEnabled,
	enabled,
	apple,
	{	
		/* 1 */
		ABOUTITEM, noIcon, noKey, noMark, plain;
	}
};

resource 'MENU' (mFile, "File") {
	mFile,
	textMenuProc,
	allEnabled, // 0x7FFFFF80,
	enabled,
	FILEMENU,
	{	
		/* 1 */
		FILEOPENITEM, noIcon, FILEOPENKEY, noMark, plain;
		/* 2 */
		"-", noIcon, noKey, noMark, plain;
		/* 3 */
		FILECLOSEITEM, noIcon, FILECLOSEKEY, noMark, plain;
		/* 4 */
		FILESAVEITEM, noIcon, FILESAVEKEY, noMark, plain;
		/* 5 */
		FILESAVEASITEM, noIcon, FILESAVEASKEY, noMark, plain;
		/* 6 */
		FILEREVERTITEM, noIcon, FILEREVERTKEY, noMark, plain;
		/* 7 */
		"-", noIcon, noKey, noMark, plain;
		/* 8 */
		FILEQUITITEM, noIcon, FILEQUITKEY, noMark, plain;
	}
};

resource 'MENU' (mEdit, "Edit") {
	mEdit,
	textMenuProc,
	allEnabled, // 0x7FFFFF7D,
	enabled,
	EDITMENU,
	{	
		/* 1 */
		EDITUNDOITEM, noIcon, EDITUNDOKEY, noMark, plain;
		/* 2 */
		"-", noIcon, noKey, noMark, plain;
		/* 3 */
		EDITCUTITEM, noIcon, EDITCUTKEY, noMark, plain;
		/* 4 */
		EDITCOPYITEM, noIcon, EDITCOPYKEY, noMark, plain;
		/* 5 */
		EDITPASTEITEM, noIcon, EDITPASTEKEY, noMark, plain;
		/* 6 */
		EDITCLEARITEM, noIcon, EDITCLEARKEY, noMark, plain;
		/* 7 */
		EDITSELECTALLITEM, noIcon, EDITSELECTALLKEY, noMark, plain;
		/* 8 */
		"-", noIcon, noKey, noMark, plain;
		/* 9 */
		EDITTESTTHEMEITEM, noIcon, EDITTESTTHEMEKEY, noMark, plain;
	}
};


resource 'MENU' (mBrush, "Brush Menu") {
	mBrush,
	textMenuProc,
	allEnabled,
	enabled,
	"Brush Colors",
	{
		/* [1] */
		"Dialog Background Active", noIcon, noKey, noMark, plain,
		/* [2] */
		"Dialog Background Inactive", noIcon, noKey, noMark, plain,
		/* [3] */
		"Alert Background Active", noIcon, noKey, noMark, plain,
		/* [4] */
		"Alert Background Inactive", noIcon, noKey, noMark, plain,
		/* [5] */
		"Modeless Dialog Background Active", noIcon, noKey, noMark, plain,
		/* [6] */
		"Modeless Dialog Background Inactive", noIcon, noKey, noMark, plain,
		/* [7] */
		"Utility Window Background Active", noIcon, noKey, noMark, plain,
		/* [8] */
		"Utility Window Background Inactive", noIcon, noKey, noMark, plain,
		/* [9] */
		"List View Sort Column Background", noIcon, noKey, noMark, plain,
		/* [10] */
		"List View Background", noIcon, noKey, noMark, plain,
		/* [11] */
		"Icon Label Background", noIcon, noKey, noMark, plain,
		/* [12] */
		"List View Seperator", noIcon, noKey, noMark, plain,
		/* [13] */
		"Chasing Arrows", noIcon, noKey, noMark, plain,
		/* [14] */
		"Drag Hilite", noIcon, noKey, noMark, plain,
		/* [15] */
		"Document Window Background", noIcon, noKey, noMark, plain,
		/* [16] */
		"Finder Window Background", noIcon, noKey, noMark, plain,
		/* [17] */
		"Scroll Bar Delimiter Active", noIcon, noKey, noMark, plain,
		/* [18] */
		"Scroll Bar Delimiter Inactive", noIcon, noKey, noMark, plain,
		/* [19] */
		"Focus Highlight", noIcon, noKey, noMark, plain,
		/* [20] */
		"Popup Arrow Active", noIcon, noKey, noMark, plain,
		/* [21] */
		"Popup Arrow Pressed", noIcon, noKey, noMark, plain,
		/* [22] */
		"Popup Arrow Inactive", noIcon, noKey, noMark, plain,
		/* [23] */
		"Apple Guide Coachmark", noIcon, noKey, noMark, plain,
		/* [24] */
		"Icon Labal Selected Background", noIcon, noKey, noMark, plain,
		/* [25] */
		"Static Area Fill", noIcon, noKey, noMark, plain,
		/* [26] */
		"Active Area Fill", noIcon, noKey, noMark, plain,
		/* [27] */
		"Button Frame Active", noIcon, noKey, noMark, plain,
		/* [28] */
		"Button Frame Inactive", noIcon, noKey, noMark, plain,
		/* [29] */
		"Button Face Active", noIcon, noKey, noMark, plain,
		/* [30] */
		"Button Face Inactive", noIcon, noKey, noMark, plain,
		/* [31] */
		"Button Face Pressed", noIcon, noKey, noMark, plain,
		/* [32] */
		"Button Active Dark Shadow", noIcon, noKey, noMark, plain,
		/* [33] */
		"Button Active Dark Highlight", noIcon, noKey, noMark, plain,
		/* [34] */
		"Button Active Light Shadow", noIcon, noKey, noMark, plain,
		/* [35] */
		"Button Active Light Highlight", noIcon, noKey, noMark, plain,
		/* [36] */
		"Button Inactive Dark Shadow", noIcon, noKey, noMark, plain,
		/* [37] */
		"Button Inactive Dark Highlight", noIcon, noKey, noMark, plain,
		/* [38] */
		"Button Inactive Light Shadow", noIcon, noKey, noMark, plain,
		/* [39] */
		"Button Inactive Light Highlight", noIcon, noKey, noMark, plain,
		/* [40] */
		"Button Pressed Dark Shadow", noIcon, noKey, noMark, plain,
		/* [41] */
		"Button Pressed Dark Highlight", noIcon, noKey, noMark, plain,
		/* [42] */
		"Button Pressed Light Shadow", noIcon, noKey, noMark, plain,
		/* [43] */
		"Button Pressed Light Highlight", noIcon, noKey, noMark, plain,
		/* [44] */
		"Bevel Active Light Brush", noIcon, noKey, noMark, plain,
		/* [45] */
		"Bevel Active Dark Brush", noIcon, noKey, noMark, plain,
		/* [46] */
		"Bevel Inactive Light Brush", noIcon, noKey, noMark, plain,
		/* [47] */
		"Bevel Inactive Dark Brush", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mTextColor, "Text Color") {
	mTextColor,
	textMenuProc,
	allEnabled,
	enabled,
	"Text Color",
	{	/* array: 46 elements */
		/* [1] */
		"Dialog Active", noIcon, noKey, noMark, plain,
		/* [2] */
		"Dialog Inactive", noIcon, noKey, noMark, plain,
		/* [3] */
		"Alert Active", noIcon, noKey, noMark, plain,
		/* [4] */
		"Alert Inactive", noIcon, noKey, noMark, plain,
		/* [5] */
		"Modeless Dialog Active", noIcon, noKey, noMark, plain,
		/* [6] */
		"Modeless Dialog Inactive", noIcon, noKey, noMark, plain,
		/* [7] */
		"Window Header Active", noIcon, noKey, noMark, plain,
		/* [8] */
		"Window Header Inactive", noIcon, noKey, noMark, plain,
		/* [9] */
		"Placard Active", noIcon, noKey, noMark, plain,
		/* [10] */
		"Placard Inactive", noIcon, noKey, noMark, plain,
		/* [11] */
		"Placard Pressed", noIcon, noKey, noMark, plain,
		/* [12] */
		"Push Button Active", noIcon, noKey, noMark, plain,
		/* [13] */
		"Push Button Inactive", noIcon, noKey, noMark, plain,
		/* [14] */
		"Push Button Pressed", noIcon, noKey, noMark, plain,
		/* [15] */
		"Bevel Button Active", noIcon, noKey, noMark, plain,
		/* [16] */
		"Bevel Button Inactive", noIcon, noKey, noMark, plain,
		/* [17] */
		"Bevel Button Pressed", noIcon, noKey, noMark, plain,
		/* [18] */
		"Popup Button Active", noIcon, noKey, noMark, plain,
		/* [19] */
		"Popup Button Inactive", noIcon, noKey, noMark, plain,
		/* [20] */
		"Popup Button Pressed", noIcon, noKey, noMark, plain,
		/* [21] */
		"Icon Label", noIcon, noKey, noMark, plain,
		/* [22] */
		"List View", noIcon, noKey, noMark, plain,
		/* [23] */
		"Document Window Title Active", noIcon, noKey, noMark, plain,
		/* [24] */
		"Document Window Title Inactive", noIcon, noKey, noMark, plain,
		/* [25] */
		"Movable Modal Window Title Active", noIcon, noKey, noMark, plain,
		/* [26] */
		"Movable Modal Window Title Inactive", noIcon, noKey, noMark, plain,
		/* [27] */
		"Utility Window Title Active", noIcon, noKey, noMark, plain,
		/* [28] */
		"Utility Window Title Inactive", noIcon, noKey, noMark, plain,
		/* [29] */
		"Popup Window Title Active", noIcon, noKey, noMark, plain,
		/* [30] */
		"Popup Window Title Inactive", noIcon, noKey, noMark, plain,
		/* [31] */
		"Root Menu Active", noIcon, noKey, noMark, plain,
		/* [32] */
		"Root Menu Inactive", noIcon, noKey, noMark, plain,
		/* [33] */
		"Root Menu Disabled", noIcon, noKey, noMark, plain,
		/* [34] */
		"Menu Item Active", noIcon, noKey, noMark, plain,
		/* [35] */
		"Menu Item Inactive", noIcon, noKey, noMark, plain,
		/* [36] */
		"Menu Item Disabled", noIcon, noKey, noMark, plain,
		/* [37] */
		"Popup Label Active", noIcon, noKey, noMark, plain,
		/* [38] */
		"Popup Label Inactive", noIcon, noKey, noMark, plain,
		/* [39] */
		"Tab Front Active", noIcon, noKey, noMark, plain,
		/* [40] */
		"Tab Non Front Active", noIcon, noKey, noMark, plain,
		/* [41] */
		"Tab Non Front Pressed", noIcon, noKey, noMark, plain,
		/* [42] */
		"Tab Front Inactive", noIcon, noKey, noMark, plain,
		/* [43] */
		"Tab Non Front Inactive", noIcon, noKey, noMark, plain,
		/* [44] */
		"Icon Label Selected", noIcon, noKey, noMark, plain,
		/* [45] */
		"Bevel Button Sticky Active", noIcon, noKey, noMark, plain,
		/* [46] */
		"Bevel Button Sticky Inactive", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mTheme, "Theme Menu") {
	mTheme,
	textMenuProc,
	0x7FFFFFFB,
	enabled,
	"Theme",
	{	/* array: 3 elements */
		/* [1] */
		"New Theme…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Delete Theme…", noIcon, noKey, noMark, plain,
		/* [3] */
		"-", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mIcon, "Icon Menu") {
	mIcon,
	textMenuProc,
	allEnabled,
	enabled,
	"Icon Menu",
	{	/* array: 0 elements */
	}
};

resource 'MENU' (mLayout, "Layout Menu") {
	mLayout,
	textMenuProc,
	allEnabled,
	enabled,
	"Layout",
	{	/* array: 8 elements */
		/* [1] */
		"Windows", noIcon, hierarchicalMenu, "ä", plain,
		/* [2] */
		"Menus", noIcon, hierarchicalMenu, "ã", plain,
		/* [3] */
		"Tabs", noIcon, hierarchicalMenu, "å", plain,
		/* [4] */
		"Scroll Bars", noIcon, hierarchicalMenu, "ç", plain,
		/* [5] */
		"Sliders", noIcon, hierarchicalMenu, "é", plain,
		/* [6] */
		"Progress Bars", noIcon, hierarchicalMenu, "è", plain,
		/* [7] */
		"Controls", noIcon, hierarchicalMenu, "ê", plain,
		/* [8] */
		"Image Well…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mRequiredFrames, "Frame Menu") {
	mRequiredFrames,
	textMenuProc,
	allEnabled,
	enabled,
	"Required Frames",
	{	/* array: 10 elements */
		/* [1] */
		"Primary Group", noIcon, hierarchicalMenu, "†", plain,
		/* [2] */
		"Secondary Group", noIcon, hierarchicalMenu, "°", plain,
		/* [3] */
		"Horizontal Seperator", noIcon, hierarchicalMenu, "¢", plain,
		/* [4] */
		"Vertical Seperator", noIcon, hierarchicalMenu, "£", plain,
		/* [5] */
		"EditText Box", noIcon, hierarchicalMenu, "§", plain,
		/* [6] */
		"List Box", noIcon, hierarchicalMenu, "•", plain,
		/* [7] */
		"Dialog Content Edge", noIcon, hierarchicalMenu, "¶", plain,
		/* [8] */
		"Window Header", noIcon, hierarchicalMenu, "ß", plain,
		/* [9] */
		"Window Placard", noIcon, hierarchicalMenu, "®", plain,
		/* [10] */
		"Focus Generic…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mPXMs, "PXM Menu") {
	mPXMs,
	textMenuProc,
	allEnabled,
	enabled,
	"PXMs",
	{	/* array: 0 elements */
	}
};

resource 'MENU' (mWindows, "Windows") {
	mWindows,
	textMenuProc,
	allEnabled,
	enabled,
	"Windows",
	{	/* array: 4 elements */
		/* [1] */
		"Main", noIcon, hierarchicalMenu, "ñ", plain,
		/* [2] */
		"Floating", noIcon, hierarchicalMenu, "ó", plain,
		/* [3] */
		"Dialogs", noIcon, hierarchicalMenu, "ò", plain,
		/* [4] */
		"Alerts", noIcon, hierarchicalMenu, "ô", plain
	}
};

resource 'MENU' (mMenus, "Menus") {
	mMenus,
	textMenuProc,
	allEnabled,
	enabled,
	"Menus",
	{	/* array: 2 elements */
		/* [1] */
		"Backgrounds", noIcon, hierarchicalMenu, "ö", plain,
		/* [2] */
		"Items", noIcon, hierarchicalMenu, "õ", plain
	}
};

resource 'MENU' (mTabs, "Tabs") {
	mTabs,
	textMenuProc,
	allEnabled,
	enabled,
	"Tabs",
	{	/* array: 5 elements */
		/* [1] */
		"Pane…", noIcon, noKey, noMark, plain,
		/* [2] */
		"North Tab", noIcon, hierarchicalMenu, "ú", plain,
		/* [3] */
		"South Tab", noIcon, hierarchicalMenu, "ù", plain,
		/* [4] */
		"East Tab", noIcon, hierarchicalMenu, "û", plain,
		/* [5] */
		"West Tab", noIcon, hierarchicalMenu, "ü", plain
	}
};

resource 'MENU' (mScrollBars, "ScrollBars") {
	mScrollBars,
	textMenuProc,
	allEnabled,
	enabled,
	"Scroll Bars",
	{	/* array: 4 elements */
		/* [1] */
		"Horizontal Regular…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Horizontal Small…", noIcon, noKey, noMark, plain,
		/* [3] */
		"Vertical Regular…", noIcon, noKey, noMark, plain,
		/* [4] */
		"Vertical Small…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mSliders, "Sliders") {
	mSliders,
	textMenuProc,
	allEnabled,
	enabled,
	"Sliders",
	{	/* array: 6 elements */
		/* [1] */
		"Horizontal…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Vertical…", noIcon, noKey, noMark, plain,
		/* [3] */
		"North…", noIcon, noKey, noMark, plain,
		/* [4] */
		"South…", noIcon, noKey, noMark, plain,
		/* [5] */
		"East…", noIcon, noKey, noMark, plain,
		/* [6] */
		"West…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mProgressBars, "Progress Bars") {
	mProgressBars,
	textMenuProc,
	allEnabled,
	enabled,
	"Progress Bars",
	{	/* array: 2 elements */
		/* [1] */
		"Determinate…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Indeterminate…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mControls, "Controls") {
	mControls,
	textMenuProc,
	allEnabled,
	enabled,
	"Controls",
	{	/* array: 7 elements */
		/* [1] */
		"PushButtons", noIcon, hierarchicalMenu, "ë", plain,
		/* [2] */
		"CheckBoxes", noIcon, hierarchicalMenu, "í", plain,
		/* [3] */
		"RadioButtons", noIcon, hierarchicalMenu, "ì", plain,
		/* [4] */
		"PopupButtons", noIcon, hierarchicalMenu, "î", plain,
		/* [5] */
		"BevelButtons", noIcon, hierarchicalMenu, "ï", plain,
		/* [6] */
		"Little Arrows…", noIcon, noKey, noMark, plain,
		/* [7] */
		"Disclosure…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mPushButtons, "PushButtons") {
	mPushButtons,
	textMenuProc,
	allEnabled,
	enabled,
	"Push Buttons",
	{	/* array: 2 elements */
		/* [1] */
		"Regular…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Default…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mCheckBoxes, "CheckBoxes") {
	mCheckBoxes,
	textMenuProc,
	allEnabled,
	enabled,
	"Check Boxes",
	{	/* array: 2 elements */
		/* [1] */
		"Left To Right…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Right To Left…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mRadioButtons, "RadioButtons") {
	mRadioButtons,
	textMenuProc,
	allEnabled,
	enabled,
	"Radio Buttons",
	{	/* array: 2 elements */
		/* [1] */
		"Left To Right…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Right To Left…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mPopupButtons, "PopupButtons") {
	mPopupButtons,
	textMenuProc,
	allEnabled,
	enabled,
	"Popup Buttons",
	{	/* array: 2 elements */
		/* [1] */
		"Left To Right…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Right To Left…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mBevelButtons, "BevelButtons") {
	mBevelButtons,
	textMenuProc,
	allEnabled,
	enabled,
	"Bevel Buttons",
	{	/* array: 3 elements */
		/* [1] */
		"Small…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Medium…", noIcon, noKey, noMark, plain,
		/* [3] */
		"Large…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mMain, "Main") {
	mMain,
	textMenuProc,
	allEnabled,
	enabled,
	"Main",
	{	/* array: 4 elements */
		/* [1] */
		"Active Document…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive Document…", noIcon, noKey, noMark, plain,
		/* [3] */
		"Active Drawer…", noIcon, noKey, noMark, plain,
		/* [4] */
		"Inactive Drawer…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mFloating, "Floating") {
	mFloating,
	textMenuProc,
	allEnabled,
	enabled,
	"Floating",
	{	/* array: 4 elements */
		/* [1] */
		"Active Top…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive Top…", noIcon, noKey, noMark, plain,
		/* [3] */
		"Active Side…", noIcon, noKey, noMark, plain,
		/* [4] */
		"Inactive Side…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mDialogs, "Dialogs") {
	mDialogs,
	textMenuProc,
	allEnabled,
	enabled,
	"Dialogs",
	{	/* array: 4 elements */
		/* [1] */
		"Active Fixed…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive Fixed…", noIcon, noKey, noMark, plain,
		/* [3] */
		"Active Movable…", noIcon, noKey, noMark, plain,
		/* [4] */
		"Inactive Movable…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mAlerts, "Alerts") {
	mAlerts,
	textMenuProc,
	allEnabled,
	enabled,
	"Alerts",
	{	/* array: 4 elements */
		/* [1] */
		"Active Fixed…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive Fixed…", noIcon, noKey, noMark, plain,
		/* [3] */
		"Active Movable…", noIcon, noKey, noMark, plain,
		/* [4] */
		"Inactive Movable…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mBackgrounds, "Backgrounds") {
	mBackgrounds,
	textMenuProc,
	allEnabled,
	enabled,
	"Backgrounds",
	{	/* array: 4 elements */
		/* [1] */
		"Root…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Pulldown…", noIcon, noKey, noMark, plain,
		/* [3] */
		"Popup…", noIcon, noKey, noMark, plain,
		/* [4] */
		"Hierarchical…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mItems, "Items") {
	mItems,
	textMenuProc,
	allEnabled,
	enabled,
	"Items",
	{	/* array: 4 elements */
		/* [1] */
		"Root…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Text…", noIcon, noKey, noMark, plain,
		/* [3] */
		"Divider…", noIcon, noKey, noMark, plain,
		/* [4] */
		"Handle…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mNorthTab, "North Tab") {
	mNorthTab,
	textMenuProc,
	allEnabled,
	enabled,
	"North Tab",
	{	/* array: 2 elements */
		/* [1] */
		"Regular…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Small…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mSouthTab, "South Tab") {
	mSouthTab,
	textMenuProc,
	allEnabled,
	enabled,
	"South Tab",
	{	/* array: 2 elements */
		/* [1] */
		"Regular…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Small…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mEastTab, "East Tab") {
	mEastTab,
	textMenuProc,
	allEnabled,
	enabled,
	"East Tab",
	{	/* array: 2 elements */
		/* [1] */
		"Regular…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Small…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mWestTab, "West Tab") {
	mWestTab,
	textMenuProc,
	allEnabled,
	enabled,
	"West Tab",
	{	/* array: 2 elements */
		/* [1] */
		"Regular…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Small…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mPrimary, "Primary") {
	mPrimary,
	textMenuProc,
	allEnabled,
	enabled,
	"Primary Group",
	{	/* array: 2 elements */
		/* [1] */
		"Active…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mSecondary, "Secondary") {
	mSecondary,
	textMenuProc,
	allEnabled,
	enabled,
	"Secondary Group",
	{	/* array: 2 elements */
		/* [1] */
		"Active…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mHSeperator, "Horizontal Seperator") {
	mHSeperator,
	textMenuProc,
	allEnabled,
	enabled,
	"Horizontal Separator",
	{	/* array: 2 elements */
		/* [1] */
		"Active…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mVSeperator, "Vertical Seperator") {
	mVSeperator,
	textMenuProc,
	allEnabled,
	enabled,
	"Vertical Separator",
	{	/* array: 2 elements */
		/* [1] */
		"Active…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mEditText, "EditText") {
	mEditText,
	textMenuProc,
	allEnabled,
	enabled,
	"Edit Text Frame",
	{	/* array: 2 elements */
		/* [1] */
		"Active…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mListBox, "ListBox") {
	mListBox,
	textMenuProc,
	allEnabled,
	enabled,
	"Listbox Frame",
	{	/* array: 2 elements */
		/* [1] */
		"Active…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mDialogContent, "Dialog Content") {
	mDialogContent,
	textMenuProc,
	allEnabled,
	enabled,
	"Dialog Content Edge",
	{	/* array: 2 elements */
		/* [1] */
		"Active…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mWinHeader, "Window Header") {
	mWinHeader,
	textMenuProc,
	allEnabled,
	enabled,
	"Window Header",
	{	/* array: 2 elements */
		/* [1] */
		"Active…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mWinPlacard, "Window Placard") {
	mWinPlacard,
	textMenuProc,
	allEnabled,
	enabled,
	"Window Placard",
	{	/* array: 3 elements */
		/* [1] */
		"Active…", noIcon, noKey, noMark, plain,
		/* [2] */
		"Inactive…", noIcon, noKey, noMark, plain,
		/* [3] */
		"Pressed…", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mPalettes, "Palettes") {
	mPalettes,
	textMenuProc,
	0x7FFFFFFD,
	enabled,
	"Palettes",
	{	/* array: 5 elements */
		/* [1] */
		"Show Magnifyer", noIcon, noKey, noMark, plain,
		/* [2] */
		"-", noIcon, noKey, noMark, plain,
		/* [3] */
		"Show User Brushes", noIcon, noKey, noMark, plain,
		/* [4] */
		"Show Required Brushes", noIcon, noKey, noMark, plain,
		/* [5] */
		"Show Text Colors", noIcon, noKey, noMark, plain
	}
};

resource 'MENU' (mUserFrames, "User Frames") {
	mUserFrames,
	textMenuProc,
	allEnabled,
	enabled,
	"User Frames",
	{	/* array: 0 elements */
	}
};

resource 'MENU' (mFrameInset, "Frame Inset") {
	mFrameInset,
	textMenuProc,
	allEnabled,
	enabled,
	"Menu",
	{	/* array: 21 elements */
		/* [1] */
		"–10", noIcon, noKey, noMark, plain,
		/* [2] */
		"–9", noIcon, noKey, noMark, plain,
		/* [3] */
		"–8", noIcon, noKey, noMark, plain,
		/* [4] */
		"–7", noIcon, noKey, noMark, plain,
		/* [5] */
		"–6", noIcon, noKey, noMark, plain,
		/* [6] */
		"–5", noIcon, noKey, noMark, plain,
		/* [7] */
		"–4", noIcon, noKey, noMark, plain,
		/* [8] */
		"–3", noIcon, noKey, noMark, plain,
		/* [9] */
		"–2", noIcon, noKey, noMark, plain,
		/* [10] */
		"–1", noIcon, noKey, noMark, plain,
		/* [11] */
		"0", noIcon, noKey, noMark, plain,
		/* [12] */
		"1", noIcon, noKey, noMark, plain,
		/* [13] */
		"2", noIcon, noKey, noMark, plain,
		/* [14] */
		"3", noIcon, noKey, noMark, plain,
		/* [15] */
		"4", noIcon, noKey, noMark, plain,
		/* [16] */
		"5", noIcon, noKey, noMark, plain,
		/* [17] */
		"6", noIcon, noKey, noMark, plain,
		/* [18] */
		"7", noIcon, noKey, noMark, plain,
		/* [19] */
		"8", noIcon, noKey, noMark, plain,
		/* [20] */
		"9", noIcon, noKey, noMark, plain,
		/* [21] */
		"10", noIcon, noKey, noMark, plain
	}
};