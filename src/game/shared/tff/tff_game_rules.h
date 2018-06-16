#ifndef TFF_GAMERULES_H
#define TFF_GAMERULES_H
#pragma once


#include "teamplay_gamerules.h"
#include "tff_hero.h"

#ifdef CLIENT_DLL
	#define CTFFRules C_TFFRules
#else
	#include "takedamageinfo.h"
#endif

//
// teamplay_gamerules.h
//

class CTFFRules : public CTeamplayRules
{
public:
	DECLARE_CLASS( CTFFRules, CTeamplayRules );

	CTFFRules();
	virtual ~CTFFRules();

#ifdef CLIENT_DLL

#else
	virtual void Precache( void );

	//virtual bool ClientCommand( CBaseEntity *pEdict, const CCommand &args );
	//virtual void ClientSettingsChanged( CBasePlayer *pPlayer );
	//virtual bool IsTeamplay( void );
	//virtual bool FPlayerCanTakeDamage( CBasePlayer *pPlayer, CBaseEntity *pAttacker, const CTakeDamageInfo &info );
	//virtual int PlayerRelationship( CBaseEntity *pPlayer, CBaseEntity *pTarget );
	//virtual bool PlayerCanHearChat( CBasePlayer *pListener, CBasePlayer *pSpeaker );
	//virtual bool ShouldAutoAim( CBasePlayer *pPlayer, edict_t *target );
	//virtual int IPointsForKill( CBasePlayer *pAttacker, CBasePlayer *pKilled );
	//virtual void InitHUD( CBasePlayer *pl );
	//virtual void DeathNotice( CBasePlayer *pVictim, const CTakeDamageInfo &info );
	//virtual const char *GetGameDescription( void ) { return "Teamplay"; }  // this is the game name that gets seen in the server browser
	//virtual void PlayerKilled( CBasePlayer *pVictim, const CTakeDamageInfo &info );
	//virtual void Think ( void );
	//virtual const char *SetDefaultPlayerTeam( CBasePlayer *pPlayer );
	//virtual void ChangePlayerTeam( CBasePlayer *pPlayer, const char *pTeamName, bool bKill, bool bGib );
	//virtual void ClientDisconnected( edict_t *pClient );

	virtual CBaseEntity *GetPlayerSpawnSpot( CBasePlayer *pPlayer );

//TFF Specific
	virtual bool CanUseHero( CBasePlayer *pPlayer , TFF_HERO hero );
#endif

private:

};

inline CTFFRules* TFFGameRules()
{
	return static_cast<CTFFRules*>(g_pGameRules);
}

#endif // TFF_GAMERULES_H


