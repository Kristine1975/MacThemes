/*
  Localize.h

*/

#ifndef __LOCALIZE_H__
#define __LOCALIZE_H__

#define APPNAME                 "Theme Machine"

#define	MAJORVERSION            0x00
#define MINORVERSION            0x40
#define STAGE                   development
#define RELEASE                 0x0
#define SHORTVERSIONSTRING      APPNAME
#define COPYRIGHTNOTICE         " © Mac Theme Project 1999-2000"

#define COUNTRYVERSION          verUS
#define LONGVERSIONSTRING       SHORTVERSIONSTRING ", " COPYRIGHTNOTICE

#define ABOUTITEM               "About " APPNAME "…"

#define FILEMENU                "File"
#define FILEOPENITEM            "Open…"
    #define FILEOPENKEY             "O"
#define FILECLOSEITEM           "Close"
   #define FILECLOSEKEY             "W"
#define FILESAVEITEM            "Save"
    #define FILESAVEKEY             "S"
#define FILESAVEASITEM          "Save As…"
    #define FILESAVEASKEY           nokey
#define FILEREVERTITEM          "Revert"
    #define FILEREVERTKEY           nokey
#define FILEQUITITEM            "Quit"
    #define FILEQUITKEY             "Q"
    
#define EDITMENU                "Edit"
#define EDITUNDOITEM            "Undo"
	  #define EDITUNDOKEY             "Z"
#define EDITCUTITEM             "Cut"
	  #define EDITCUTKEY              "X"
#define EDITCOPYITEM            "Copy"
	  #define EDITCOPYKEY             "C"
#define EDITPASTEITEM           "Paste"
	  #define EDITPASTEKEY            "V"
#define EDITCLEARITEM           "Clear"
	  #define EDITCLEARKEY            nokey
#define EDITSELECTALLITEM       "Select All"
	  #define EDITSELECTALLKEY        "A"
#define EDITTESTTHEMEITEM       "Test Theme"
    #define EDITTESTTHEMEKEY        "T"

#define LAYOUTMENU      "Layout"

#endif /* __LOCALIZE_H__ */