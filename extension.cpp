/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod Sample Extension
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include "extension.h"
#include "..\Features\WeightSys.h"
 /**
  * @file extension.cpp
  * @brief Implement extension code here.
  */

Sample g_Sample;		/**< Global singleton for extension's main interface */
DWORD g_Pid = -1;
bool Sample::SDK_OnLoad(char* error, size_t maxlen, bool late)
{
	g_Pid = GetCurrentProcessId();
	for (int i = 0; i < 64; i++)
	{
		MaxCarryArr[i] = 1000.0f;
	}
	Weight::Init();
	
	return true;
}

cell_t SetPlayerWeightByIdx(IPluginContext* pCtx, const cell_t* params)
{
	cell_t idx = params[1];
	cell_t weights = params[2];
	if (idx > 0 && idx < 64)
	{
		MaxCarryArr[idx] = weights;
		return true;
	}
	return false;
}

const sp_nativeinfo_t MyNatives[] =
{
	{"SetPlayerWeightByIdx",SetPlayerWeightByIdx},
	{NULL,NULL},
};
void Sample::SDK_OnAllLoaded()
{
	sharesys->AddNatives(myself, MyNatives);
}
SMEXT_LINK(&g_Sample);
