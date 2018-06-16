// Purpose: Body for tff_func_spawn
// Boilerplate generated by ModMaker on 23/05/2018 07:43:29
/* Area to spawn team players in*/

#include "cbase.h"
#include "tff_func_spawn.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

LINK_ENTITY_TO_CLASS( tff_func_spawn, CTffFuncSpawn );

BEGIN_DATADESC( CTffFuncSpawn )
    DEFINE_OUTPUT( m_OnPlayerSpawn, "OnPlayerSpawn" ),
    DEFINE_OUTPUT( m_OnPlayerLeave, "OnPlayerLeave" ),
    DEFINE_OUTPUT( m_OnPlayerleave, "OnPlayerleave" ),
END_DATADESC()

bool CTffFuncSpawn::SpawnPlayer(CBasePlayer * pPlayer)
{
	if (pPlayer == NULL) return false;

	ICollideable * collides = CBaseTrigger::GetCollideable();

	if (collides == NULL) return false;

	//Get our bounding box
	Vector vecMins;
	Vector vecMaxs;
	collides->WorldSpaceTriggerBounds(&vecMins, &vecMaxs);

	float PLAYER_RADIUS = 29.0f;
	float PLAYER_DIAMITER = PLAYER_RADIUS * 2.0f;

	float width = vecMaxs.x - vecMins.x;
	float deapth = vecMaxs.y - vecMins.y;

	if (width < PLAYER_DIAMITER) return false;
	if (deapth < PLAYER_DIAMITER) return false;

	float dx = floor(width / PLAYER_DIAMITER); //number of player widths within the room
	float dy = floor(deapth / PLAYER_DIAMITER); //number of player widths within the room
	
	int ix;
	int iy; 
	int attempts = 0;
	Vector vSpawnPoint;
	bool isValidOffset = false;

	//TODO do this once on spawn and cache the valid results

	while ((!isValidOffset) && (attempts < MAX_PLAYERS) )
	{
		attempts++;
		ix = RandomInt(0, (int)dx);
		iy = RandomInt(0, (int)dy);

		vSpawnPoint = vecMins + Vector(PLAYER_RADIUS + (PLAYER_RADIUS * ix), PLAYER_RADIUS + (PLAYER_RADIUS * iy), 4);

		if (!PointIsWithin(vSpawnPoint)) continue; //try again with a new random combination

		trace_t trace;

		UTIL_TraceHull(vSpawnPoint, vSpawnPoint, pPlayer->GetPlayerMins(), pPlayer->GetPlayerMaxs(), NULL, NULL, &trace);

		if(trace.DidHit()) continue; //try again with a new random combination

		isValidOffset = true;
	}

	if (!isValidOffset) {
		Warning("func_spawn %s could not find a free space to spawn a player\n", GetEntityName());

		return false;
	}

	QAngle lookie = GetAbsAngles();

	pPlayer->Teleport(&vSpawnPoint, &lookie, NULL);
	//TODO apply the invulnerability status to pPlayer
	m_OnPlayerSpawn.FireOutput(pPlayer, this);

	return true;
};