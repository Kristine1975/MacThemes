// ===========================================================================
//	UTFlacResource.h			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the clr# resource
//
//	Authors
//	Dave MacLachlan <davem@paradigmdev.com>
//
// Notes:
//	Dec 22/98 Initial Implementation
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


#ifndef _H_UTFlacResource
#define _H_UTFlacResource
#pragma once

#include "UTResource.h"
#include <Collections.h>

#define kFlacResourceType 'flac'

// ---------------------------------------------------------------------------

class	UTFlacResource : public UTResource
{
	public:
	UTFlacResource();							
	virtual ~UTFlacResource();
	void Init(ResIDT			inResID,
					ResFileID		inResFileID,
					Boolean			inCreate = true,
					Boolean			inThrowFail = true,
					ResType			inResType = kFlacResourceType);
			
	virtual Handle 	BuildBaseResource();	
	virtual void				Write(Boolean			inUpdateResFile = true);
	virtual void	Dispose();
	Collection GetCollection() { return mCollection; }
	
	protected:
	Collection mCollection;
	
	private:
	operator Handle()	{ return mResourceH; }
				
	Handle	Get()		{ return mResourceH; }
	
	

	
};

#endif
