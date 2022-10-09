// ===========================================================================
//	TGAPPATSwatchControl.cp					Allegro Theme Project
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

#include "TGAPPATSwatchControl.h"
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
//	€ TGAPPATSwatchControl					Default Constructor		  [public]
// ---------------------------------------------------------------------------

TGAPPATSwatchControl::TGAPPATSwatchControl()
{
	Init();
}


// ---------------------------------------------------------------------------
//	€ TGAPPATSwatchControl					Copy Constructor		  [public]
// ---------------------------------------------------------------------------

TGAPPATSwatchControl::TGAPPATSwatchControl(	
	const TGAPPATSwatchControl&	inOriginal)
	
	: LControl(inOriginal)
{
	Init();
	Handle thePPAT = NULL;
	if(UTPixUtilities::PixPatToPPAT(mPattern,thePPAT) == noErr)
	{
		SetSwatchPPAT(thePPAT);
		DisposeHandle(thePPAT);
	}
}


// ---------------------------------------------------------------------------
//	€ TGAPPATSwatchControl					Stream Constructor		  [public]
// ---------------------------------------------------------------------------

TGAPPATSwatchControl::TGAPPATSwatchControl( 
	LStream*	inStream)
	
	: LControl(inStream)
{
	Init();
}


// ---------------------------------------------------------------------------
//	€ TGAPPATSwatchControl					Parameterized Constructor [public]
// ---------------------------------------------------------------------------

TGAPPATSwatchControl::TGAPPATSwatchControl(	
	const SPaneInfo&	inPaneInfo,
	const SControlInfo&	inControlInfo,
	const FullResourceSpec&		inSpec,
	Str255				/*inPromptString*/)
	
	: LControl(inPaneInfo,
				inControlInfo.valueMessage,
				inControlInfo.value,
				inControlInfo.minValue,
				inControlInfo.maxValue)
	 
{

	Init();
	SetSwatchPPAT(inSpec);
}


// ---------------------------------------------------------------------------
//	€ ~TGAPPATSwatchControl				Destructor				  [public]
// ---------------------------------------------------------------------------

TGAPPATSwatchControl::~TGAPPATSwatchControl ()
{
	if(mPattern != nil)
	{
		DisposePixPat(mPattern);
	}
}

void
TGAPPATSwatchControl::Init()
{
	mPattern = nil;
}


#pragma mark -
#pragma mark === ACCESSORS


// ---------------------------------------------------------------------------
//	€ SetSwatchColor												  [public]
// ---------------------------------------------------------------------------

void			
TGAPPATSwatchControl::SetSwatchPPAT(	
	const Handle		inSwatchPPAT)
{
	if(mPattern != nil)
	{
		DisposePixPat(mPattern);
		mPattern = NULL;
	}
	if(inSwatchPPAT != NULL)
	{
		UTPixUtilities::PPATToPixPat(inSwatchPPAT,mPattern);
	}	
					// The color changed so we have to redraw the swatch
	Draw(nil);
}

void			
TGAPPATSwatchControl::SetSwatchPPAT(const FullResourceSpec &inSpec)
{
	Handle thePPAT;
	StCurResFile resFile;
	UseResFile(inSpec.fileID);
	thePPAT = GetResource(inSpec.resType,inSpec.resID);
	SetSwatchPPAT(thePPAT);
	if(thePPAT != NULL)
	{
		ReleaseResource(thePPAT);
	}
}

// ---------------------------------------------------------------------------
//	€ GetSwatchColor												  [public]
// ---------------------------------------------------------------------------

void	
TGAPPATSwatchControl::GetSwatchPPAT(Handle& outPPAT) const
{
	SignalIfNot_(outPPAT == NULL);
	
	UTPixUtilities::PixPatToPPAT(mPattern,outPPAT);
}


#pragma mark -
#pragma mark === ENABLING & DISABLING

// ---------------------------------------------------------------------------
//	€ EnableSelf													  [public]
// ---------------------------------------------------------------------------

void
TGAPPATSwatchControl::EnableSelf()
{
	Draw(nil);
}


// ---------------------------------------------------------------------------
//	€ DisableSelf													  [public]
// ---------------------------------------------------------------------------
//

void
TGAPPATSwatchControl::DisableSelf()
{
	Draw(nil);
}


#pragma mark -
#pragma mark === ACTIVATION

// ---------------------------------------------------------------------------
//	€ ActivateSelf													  [public]
// ---------------------------------------------------------------------------

void
TGAPPATSwatchControl::ActivateSelf()
{
	if (IsActive()) {
		Refresh();
	}
}


// ---------------------------------------------------------------------------
//	€ DeactivateSelf												  [public]
// ---------------------------------------------------------------------------

void
TGAPPATSwatchControl::DeactivateSelf()
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
TGAPPATSwatchControl::DrawSelf ()
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
		::RGBForeColor ( &Color_Black );
		
		if(mPattern != nil)
		{
			::PenPixPat ( mPattern );
		}
		else
		{
			::RGBForeColor ( &Color_White );
		}
		::PaintRect ( &localFrame );
		
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
TGAPPATSwatchControl::BroadcastValueMessage ()
{
	if (mValueMessage != msg_Nothing)  
	{
		Handle thePPAT = NULL;
		if(mPattern == NULL || UTPixUtilities::PixPatToPPAT(mPattern,thePPAT) == noErr)
		{
			BroadcastMessage(mValueMessage, (void*) thePPAT);
			DisposeHandle(thePPAT);
		}
	}
}


PP_End_Namespace_PowerPlant
