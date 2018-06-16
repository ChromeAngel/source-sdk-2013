#ifdef CLIENT_DLL
	#include "c_team.h"
#else
	#include "team.h"
#endif

#include "UtlVector.h"

#ifndef TFF_TEAM_MAN_H
#define TFF_TEAM_MAN_H
#pragma once

struct TFF_TEAM_NAME
{
	int number;
	const char * name;
};

static TFF_TEAM_NAME g_TFFTeams[4] =
{
	{ TEAM_UNASSIGNED , "Unassigned" },
	{ TEAM_SPECTATOR  , "Spectator" },
	{ TEAM_RED        , "Red" },
	{ TEAM_BLUE       , "Blue" }
};

static const char * UTIL_TFF_TeamName(int team)
{
	if(team >= TEAM_COUNT) return "Invalid";
	if(team < 0 ) return "Invalid";

	return g_TFFTeams[team].name;
};

static int UTIL_TFF_ParseTeamName(const char * pName)
{
	if(pName == NULL) return TEAM_INVALID; //Unknown

	int result = TEAM_INVALID;
	for(result =0;result < TEAM_COUNT;result++)
	{
		if( FStrEq(pName,g_TFFTeams[result].name) ) return result;
	}

	return TEAM_INVALID; //Unknown
};

#ifdef GAME_DLL
static void TFF_RegisterTeam(CTeam * pTeam, bool replace)
{
	if( pTeam == NULL ) return;

	if(g_Teams.Count() > 0 )
	{
		//replace any previous teams with the same number
		CTeam * pPrevMatch = NULL;

		FOR_EACH_VEC( g_Teams, index )
		{
			CTeam * pCurrentTeam = g_Teams[index];

			if(pCurrentTeam->GetTeamNumber() == pTeam->GetTeamNumber())
			{
				pPrevMatch = pCurrentTeam;
				break;
			}
		}

		if ( pPrevMatch )
		{
			if( replace) 
			{
				g_Teams.FindAndFastRemove( pPrevMatch );
			} else {
				return;
			}
		}
	}

	g_Teams.AddToTail( pTeam );
}

static void TFF_RegisterTeams()
{
	for ( int i = 0; i < TEAM_COUNT; i++ )
	{
		CTeam *pTeam = static_cast<CTeam*>(CreateEntityByName( "team_manager" ));
		pTeam->Init( g_TFFTeams[i].name , i );

		TFF_RegisterTeam( pTeam, false );
	}
}
#endif

#endif //TFF_TEAM_MAN_H