// ===========================================================================
//	UTTicListResource.cpp			   Allegro Themes Project
// ===========================================================================
//
//	Class for manipulating the tic# resource
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


#include "UTTicListResource.h"

const static OSType kIcons[] =
{'CLIP',
	'clpu',
	'clpp',
	'clpt',
	'clps',
	'desk',
	'FNDR',
	'FFIL',
	'ftrh',
	'APPL',
	'cddr',
	'APPC',
	'sdev',
	'thng',
	'APPD',
	'docu',
	'edtf',
	'INIT',
	'srvr',
	'ffil',
	'sclr',
	'flpy',
	'hdsk',
	'rmov',
	'movr',
	'pcmc',
	'pref',
	'qery',
	'ramd',
	'shlb',
	'sdoc',
	'suit',
	'worm',
	'ifil',
	'kfil',
	'sfil',
	'zsys',
	'trsh',
	'tfil',
	'sfnt',
	'ttcf',
	'ilht',
	'ilft',
	'ilaf',
	'ilat',
	'ilfi',
	'ilma',
	'ilnw',
	'ilge',
	'fldr',
	'dbox',
	'mntd',
	'ofld',
	'ownd',
	'prvf',
	'shfl',
	'shna',
	'shro',
	'shrw',
	'shuk',
	'writ',
	'ufld',
	'wfld',
	'gusr',
	'user',
	'susr',
	'grup',
	'aexü',
	'amnu',
	'apps',
	'asup',
	'astü',
	'cmnu',
	'ctrD',
	'ctrl',
	'sdvü',
	'docs',
	'extD',
	'extn',
	'favs',
	'font',
	'ühlp',
	'intü',
	'ünet',
	'morü',
	'prfü',
	'ppdf',
	'üprd',
	'prnt',
	'rapp',
	'rdoc',
	'rsrv',
	'üscr',
	'ülib',
	'scrü',
	'shdD',
	'shdf',
	'spki',
	'strD',
	'strt',
	'macD',
	'macs',
	'ütex',
	'appr',
	'utiü',
	'fvoc',
	'prof',
	'issf',
	'scrp',
	'lbdg',
	'mbdg',
	'sbdg',
	'abdg',
	'note',
	'caut',
	'stop',
	'atlk',
	'atzn',
	'afps',
	'ftps',
	'isrv',
	'capl',
	'sapl',
	'baro',
	'favr',
	'faro',
	'grid',
	'help',
	'arng',
	'lock',
	'nfil',
	'nfld',
	'nwrt',
	'papp',
	'psys',
	'rcnt',
	'shrt',
	'asnd',
	'dsnd',
	'ulck',
	'cnct'
};
const static long kIconLength = sizeof(kIcons) / sizeof(OSType);
const static ResIDT kTicIconNamesID=301;
// ---------------------------------------------------------------------------

UTTicListResource::UTTicListResource()
{
}
			
UTTicListResource::~UTTicListResource()
{
}

void UTTicListResource::Init(ResIDT			inResID,
				ResFileID		inResFileID,
				Boolean			inCreate /*= true*/,
				Boolean			inThrowFail /*= true*/)
{
	UTResource::Init(kTicListResourceType, inResID, inResFileID, inCreate, inThrowFail);
}
			
Handle 	UTTicListResource::BuildBaseResource()
{
	Handle newRes = ::NewHandleClear(sizeof(UInt32));
	ThrowIfMemFail_(newRes);
	*((UInt32*)(*newRes)) = 0;
	return newRes;
}

void UTTicListResource::GetTicEntry(UInt32 inIndex, TicEntry &outTicEntry)
{
	Assert_(inIndex < Count());
	UInt32 offSet = sizeof(UInt32) + (sizeof(TicEntry) * inIndex);
	TicEntry *pTic = ((TicEntry*)((*mResourceH) + offSet));
	outTicEntry = *pTic;
}

void UTTicListResource::SetTicEntry(UInt32 inIndex, const TicEntry &inTicEntry)
{
	Assert_(inIndex <= Count());
	UInt32 offSet = sizeof(UInt32) + (sizeof(TicEntry) * inIndex);
	TicEntry *pTic = ((TicEntry*)((*mResourceH) + offSet));
	*pTic = inTicEntry;
	Dirty();
}

UInt32 UTTicListResource::FindTicEntry(OSType inType, TicEntry &outTicEntry)
{
	UInt32 i = 0;
	for(i = 0; i < Count(); i++)
	{
		TicEntry e;
		GetTicEntry(i,e);
		if(e.iconSignature == inType)
		{
			outTicEntry = e;
			break;
		}
	}
	if(i == Count())
	{
		i = -1;
	}
	return i;
}
		
void UTTicListResource::InsertTicEntry(UInt32 inIndex, const TicEntry &inTicEntry)
{
	::SetHandleSize(mResourceH,::GetHandleSize(mResourceH) + sizeof(TicEntry));
	ThrowIfMemError_();
	if(inIndex < Count())
	{
		UInt32 offSet1 = sizeof(UInt32) + (sizeof(TicEntry) * inIndex);
		UInt32 offSet2 = offSet1 + sizeof(TicEntry);
		BlockMove((*mResourceH) + offSet1, 
						(*mResourceH) + offSet2,
						(Count() - inIndex) * sizeof(TicEntry));
		ThrowIfMemError_();
	}
	else
	{
		inIndex = Count();
	}
	SetCount(Count() + 1);
	SetTicEntry(inIndex,inTicEntry);
}

void UTTicListResource::AddTicEntry(const TicEntry &inTicEntry)
{
	InsertTicEntry(Count(),inTicEntry);
}

	
void UTTicListResource::DeleteTicEntry(UInt32 inIndex)
{
	Assert_(Count() > 0 && inIndex > 0);
	if(inIndex < Count() && inIndex > 0)
	{
		UInt32 offSet1 = sizeof(UInt32) + (sizeof(TicEntry) * inIndex);
		UInt32 offSet2 = offSet1 + sizeof(TicEntry);
		BlockMove((*mResourceH) + offSet2,
						(*mResourceH) + offSet1, 
						(Count() - (inIndex + 1)) * sizeof(TicEntry));
		ThrowIfMemError_();
	}
	else
	{
		inIndex = Count();
	}
	::SetHandleSize(mResourceH,::GetHandleSize(mResourceH) - sizeof(TicEntry));
	ThrowIfMemError_();
	SetCount(Count() - 1);
	Dirty();
}

UInt32 UTTicListResource::Count()
{
	return *((UInt32*)(*mResourceH));
}

void UTTicListResource::SetCount(UInt32 inCount)
{
	*((UInt32*)(*mResourceH)) = inCount;
}

void	UTTicListResource::FindEntryName(OSType inType, LStr255 &outString)
{
	UInt32 i;
	for(i = 0; i < kIconLength; i++)
	{
		if(inType == kIcons[i])
		{
			outString.Assign(kTicIconNamesID,i+1);
			break;
		}
	}
	if(i == kIconLength)
	{
		outString.Assign((FourCharCode) inType);
	}
}

