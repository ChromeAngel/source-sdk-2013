#include "cbase.h"
#include "tff_game_rules.h"
#include "utlvector.h"

#ifdef CLIENT_DLL
	#include "c_team.h"
#else
	#include "team.h"
	#include "tff_func_spawn.h"
#endif

#include "tff_team_manager.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#define TFF_VERSION 0.01

#ifdef CLIENT_DLL
ConVar tff_version ("tff_version", "TFF_VERSION", FCVAR_CLIENTDLL );
#else
void CC_tff_Version( const CCommand& args )
{
	Msg("TFF_VERSION\n");
}
static ConCommand tff_version("tff_version", CC_tff_Version, "Usage:\n   tff_version\n");
#endif

REGISTER_GAMERULES_CLASS( CTFFRules );

CTFFRules::CTFFRules()
{
#ifdef GAME_DLL
	TFF_RegisterTeams();
#endif
};

 CTFFRules::~CTFFRules() 
 {
 };

#ifdef CLIENT_DLL

#else

void CTFFRules::Precache( void )
{
	BaseClass::Precache();
};

CBaseEntity * CTFFRules::GetPlayerSpawnSpot( CBasePlayer *pPlayer )
{
	if(pPlayer == NULL) return NULL;

	CUtlVector<CBaseEntity *> candidates;
	CBaseEntity * pEnt = gEntList.FindEntityByClassname(NULL, "tff_func_spawn");
	while(pEnt)
	{
		if(pEnt->GetTeamNumber() == pPlayer->GetTeamNumber())
		{
			candidates.AddToTail(pEnt);
		}
		pEnt = gEntList.FindEntityByClassname(pEnt, "tff_func_spawn");
	}

	while(candidates.Count() > 0)
	{
		pEnt = candidates.Random();
		CTffFuncSpawn * pSpawn = dynamic_cast<CTffFuncSpawn *>( pEnt );

		if( pSpawn )
		{
			pSpawn->SpawnPlayer(pPlayer);
			
			return pSpawn;
		} else {
			candidates.FindAndFastRemove( pEnt );
		}
	}

	Warning("No spawn rooms found for team %s\n", pPlayer->GetTeam()->GetName());

	return BaseClass::GetPlayerSpawnSpot(pPlayer);
};

bool CTFFRules::CanUseHero( CBasePlayer *pPlayer , TFF_HERO hero )
{
	//TODO check with the players team
	return true;
};

#endif //GAME_DLL