// ===========================================================================
//	TGAPLUTSwatchControl.cp					Allegro Theme Project
// ===========================================================================
//	Author: Dave MacLachlan
//	Based On LGAColorSwatchControl By Robin Mair
//
//	Control for displaying a pattern
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
#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "TGAPLUTSwatchControl.h"
#include <UGraphicUtils.h>
#include <UGAColorRamp.h>

#include <LStream.h>
#include <UDrawingUtils.h>
#include <UDesktop.h>
#include <UQDOperators.h>
#include <PP_Messages.h>
#include <UResourceMgr.h>
#include "UTPixUtilities.h"
#include <ColorPicker.h>

PP_Begin_Namespace_PowerPlant

#pragma mark === INITIALIZATION

// ---------------------------------------------------------------------------
//	€ TGAPLUTSwatchControl					Default Constructor		  [public]
// ---------------------------------------------------------------------------

TGAPLUTSwatchControl::TGAPLUTSwatchControl()
{
	Init();
}


// ---------------------------------------------------------------------------
//	€ TGAPLUTSwatchControl					Copy Constructor		  [public]
// ---------------------------------------------------------------------------

TGAPLUTSwatchControl::TGAPLUTSwatchControl(	
	const TGAPLUTSwatchControl&	inOriginal)
	
	: LControl(inOriginal)
{
	Init();
	mPlut = inOriginal.mPlut;
}


// ---------------------------------------------------------------------------
//	€ TGAPLUTSwatchControl					Stream Constructor		  [public]
// ---------------------------------------------------------------------------

TGAPLUTSwatchControl::TGAPLUTSwatchControl( 
	LStream*	inStream)
	
	: LControl(inStream)
{
	Init();
}


// ---------------------------------------------------------------------------
//	€ TGAPLUTSwatchControl					Parameterized Constructor [public]
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//	€ ~TGAPLUTSwatchControl				Destructor				  [public]
// ---------------------------------------------------------------------------

TGAPLUTSwatchControl::~TGAPLUTSwatchControl ()
{
}

void
TGAPLUTSwatchControl::Init()
{
}


#pragma mark -
#pragma mark === ACCESSORS


// ---------------------------------------------------------------------------
//	€ SetSwatchColor												  [public]
// ---------------------------------------------------------------------------

void			
TGAPLUTSwatchControl::SetSwatchPLUT(	
	const PlutEntry		inSwatchPLUT)
{
	mPlut = inSwatchPLUT;
					// The color changed so we have to redraw the swatch
	Draw(nil);
}

// ---------------------------------------------------------------------------
//	€ GetSwatchColor												  [public]
// ---------------------------------------------------------------------------

void	
TGAPLUTSwatchControl::GetSwatchPLUT(PlutEntry& outPLUT) const
{
	outPLUT = mPlut;
	
}


#pragma mark -
#pragma mark === ENABLING & DISABLING

// ---------------------------------------------------------------------------
//	€ EnableSelf													  [public]
// ---------------------------------------------------------------------------

void
TGAPLUTSwatchControl::EnableSelf()
{
	Draw(nil);
}


// ---------------------------------------------------------------------------
//	€ DisableSelf													  [public]
// ---------------------------------------------------------------------------
//

void
TGAPLUTSwatchControl::DisableSelf()
{
	Draw(nil);
}


#pragma mark -
#pragma mark === ACTIVATION

// ---------------------------------------------------------------------------
//	€ ActivateSelf													  [public]
// ---------------------------------------------------------------------------

void
TGAPLUTSwatchControl::ActivateSelf()
{
	if (IsActive()) {
		Refresh();
	}
}


// ---------------------------------------------------------------------------
//	€ DeactivateSelf												  [public]
// ---------------------------------------------------------------------------

void
TGAPLUTSwatchControl::DeactivateSelf()
{
	if (!IsActive()) {
		Refresh();
	}
}


#pragma mark -
#pragma mark === DRAWING

// ---------------------------------------------------------------------------
//	€ DrawSelf														  [public]
//	
//	ToDo: Davem
//	Must write code to handle disabled state as well as B&W.
// ---------------------------------------------------------------------------

void
TGAPLUTSwatchControl::DrawSelf ()
{	
	::PenNormal();
	ApplyForeAndBackColors ();
	
	Rect frame;
	CalcLocalFrameRect ( frame );
	
	::EraseRect ( &frame );						// Start out by erasing the whole control

	RGBColor	tempColor;
	SInt16		depth = GetBitDepth();
	bool		enabledAndActive = IsEnabled() && IsActive();
	
	Rect		localFrame = frame;

	::MacInsetRect ( &localFrame, 1, 1 );
	
											// First we are going to draw a little shadow
											// under the color swatch
	::MacOffsetRect ( &localFrame, 1, 1 );
	
	tempColor = Color_Black;
	if (depth >= 4) {
		tempColor = enabledAndActive ? UGAColorRamp::GetColor(6)
									 : UGAColorRamp::GetColor(4);
	}
	
	::RGBForeColor ( &tempColor );
	
	if ( depth < 4 ) {
		::PenPat ( &UQDGlobals::GetQDGlobals()->gray );
	}
	::PaintRect ( &localFrame );
	::MacOffsetRect ( &localFrame, -1, -1 );
	::PaintRect ( &localFrame );
	::MacOffsetRect ( &localFrame, -1, -1 );
	
											// Then we paint the swatch color, either hilited
											// if it is being pushed, normal or dimmed
	if ( depth >= 4 ) {				// COLOR
	
		::PenNormal ();
											// Setup the swatch color
		/*if ( IsEnabled () && IsPushed ()) {
			::MacOffsetRect ( &localFrame, 2, 2 );
			
			if ( mSwatchColor == Color_Black) {
				tempColor = Color_White;
				
			} else {
				tempColor = UGraphicUtils::Darken ( mSwatchColor );
			}
			
		} else {
			tempColor = mSwatchColor;
			if (!enabledAndActive) {
				UTextDrawing::DimTextColor(tempColor);
			}
		}*/
		if(mPlut.brushPPAT.resID == 0)
		{
			RGBForeColor(&mPlut.brushColor);
			PaintRect(&localFrame);
		}
		else
		{
			PixPatHandle thePattern = mPlut.GetPlutPixPat();
			FillCRect(&localFrame,thePattern);
			DisposePixPat(thePattern);
		}
		
											// Now we frame the color swatch
		tempColor = enabledAndActive ? Color_Black : UGAColorRamp::GetColor(7);
		::RGBForeColor ( &tempColor );
		::MacFrameRect ( &localFrame );

	} /*else {								// BLACK & WHITE

		::RGBForeColor ( &Color_Black );
		if (enabledAndActive) {
			::PenPat ( &UQDGlobals::GetQDGlobals()->gray );
		}
		::MacFrameRect ( &localFrame );
		
										// Paint the swatch color
		::MacInsetRect ( &localFrame, 2, 2 );
		::RGBForeColor ( &mSwatchColor );
		::PaintRect ( &localFrame );
	}*/
}


#pragma mark -
#pragma mark === BROADCASTING

// ---------------------------------------------------------------------------
//	€ BroadcastValueMessage										   [protected]
// ---------------------------------------------------------------------------

void
TGAPLUTSwatchControl::BroadcastValueMessage ()
{
	if (mValueMessage != msg_Nothing)  
	{
	}
}


PP_End_Namespace_PowerPlant
