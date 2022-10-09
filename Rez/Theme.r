/*

Allegro Themes Project
Rez header

Authors
	Dave MacLachlan (davem@paradigmdev.com)

Version 0.1.1
*/
	
/*----------------------------------- common macros ---------------------------------------*/

#define	PixMapHeight	( $$BitField(Bounds, 32, 16) /* bottom */			\
						- $$BitField(Bounds, 0, 16) /* top */ )
#define	PixMapWidth		( $$BitField(Bounds, 48, 16) /* right */			\
						- $$BitField(Bounds, 16, 16) /* left */ )
#define	PixMapBounds	integer = $$BitField(Bounds, 0, 16) /* top */;		\
						integer = $$BitField(Bounds, 16, 16) /* left */;	\
						integer = $$BitField(Bounds, 32, 16) /* bottom */;	\
						integer = $$BitField(Bounds, 48, 16) /* right */
#define	PixMapRowBytes	(((PixMapWidth * $$Word(PixelSize) + 15) / 16) * 2)
#define	BitMapRowBytes	(((PixMapWidth + 15) / 16) * 2)

#define	PixMapHeightIndexed		( $$BitField(Bounds[$$ArrayIndex(PixPatArray)], 32, 16) /* bottom */			\
								- $$BitField(Bounds[$$ArrayIndex(PixPatArray)], 0, 16) /* top */ )
#define	PixMapWidthIndexed		( $$BitField(Bounds[$$ArrayIndex(PixPatArray)], 48, 16) /* right */			\
								- $$BitField(Bounds[$$ArrayIndex(PixPatArray)], 16, 16) /* left */ )
#define	PixMapRowBytesIndexed	(((PixMapWidthIndexed * $$Word(PixelSize[$$ArrayIndex(PixPatArray)]) + 15) / 16) * 2)


//Color List
//
// author Davem
//
//	A list of RGB colors
//	Resorcerer template is found in Themes.tmpl

Type 'clr#'
{
	longint = $$Countof(ColorArray);
	array ColorArray 
	{
			unsigned integer;								/* RGB:	red				*/
			unsigned integer;								/*		green			*/
			unsigned integer;								/*		blue			*/
	};
};

//Theme Icon List
//
// author Davem
//
//	A list of file signatures, and the IDs of the icons to go with them under this theme
//	Resorcerer template is found in Themes.tmpl

Type 'tic#'
{
	longint = $$Countof(IconCount);
	array IconCount 
	{
			literal longint;	// Signature
			integer;			// ID
	};
};

//Theme Data
//
// author Davem
//
//	A list of resources in the theme
//	Resorcerer template is found in Themes.tmpl
Type 'tdat'
{
	array
	{
		literal longint;	// Resource Name
		integer;			// ID 1
		integer;			// ID 2
		integer;			// Unknown (resource flags?)
		integer;			// Unknown (resource flags?)
		integer;			// Unknown (resource flags?)
		integer;			// Unknown (resource flags?)
	};
};

// Frame?
//
// author Davem
//
//	A list of frames in the theme
//	Resorcerer template is found in Themes.tmpl
Type 'frme'
{
	integer;			// Unknown
	integer;			// Unknown
	integer;			// Unknown
	integer;			// Unknown
	integer;			// Unknown
	longint = $$Countof(rectCount);
	array rectCount 
	{
		rect;
	}
};

//Not Complete at all just piecing this one together
/*
//Pixmap List
Type 'pxm#'
{
	integer = $$Countof(PixMapCount);
	array PixMapCount 
	{
			integer;												//unknown
			unsigned bitstring[1] = 1;								// New pixMap flag	?	
			unsigned bitstring[2] = 0;								// Must be 0	?		
		pMapRowBytes:
			unsigned bitstring[13] = PixMapRowBytes;				// Offset to next row	?
		Bounds:	rect;												// Bitmap bounds?		
			integer;
		PixelSize:
			integer;												// # bits in pixel	?	
			integer;												//unknown
			integer;												//unknown
		ClutID:
			integer;												//ID of the CLUT?
			integer;												//unknown

		PixelData:
			hex string [PixMapRowBytes * PixMapHeight];				//data?
	};
};



//Theme Layout?
Type 'layo'
{
};

//Palette Look Up Table?
Type 'plut'
{
};

//Scene?
Type 'scen'
{
	//Looks like it may have some collection manager stuff in it, but doesn't conform to 'cltn' resource.
};


//Theme Info
Type 'tinf'
{
};

/************************
// Notes:
// 
// Nov 24/98 Davem - Added basic types tic#, clr#, and started work on pxm#
// Nov 24/98 Davem - Added basic frme and tdat

