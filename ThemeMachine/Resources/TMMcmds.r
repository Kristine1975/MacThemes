/*
  ThemeMachine.r
  
  Resources
*/

#include "Mcmd.r"

#include "PP_Commands.h"
#include "Commands.h"
#include "ThemeMachine.h"

resource 'Mcmd' (mApple, "Apple", purgeable) {
	{
		/* 1 */
	  cmd_About;
	}
};

resource 'Mcmd' (mFile, "File") {
	{
		/* 1 */
		cmd_Open;
		/* 2 */
		cmd_Nothing;
		/* 3 */
		cmd_Close;
		/* 4 */
		cmd_Save;
		/* 5 */
		cmd_SaveAs;
		/* 6 */
		cmd_Revert;
		/* 7 */
		cmd_Nothing;
		/* 8 */
		cmd_Quit;
	}
};

resource 'Mcmd' (mEdit, "Edit") {
	{	
		/* 1 */
		cmd_Undo;
		/* 2 */
		cmd_Nothing;
		/* 3 */
		cmd_Cut;
		/* 4 */
		cmd_Copy;
		/* 5 */
		cmd_Paste;
		/* 6 */
		cmd_Clear;
		/* 7 */
		cmd_SelectAll;
		/* 8 */
		cmd_Nothing;
		/* 9 */
		cmd_TestTheme;
	}
};
