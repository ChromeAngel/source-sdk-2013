#include "basemultiplayerplayer.h"
#include "tff_hero.h"
#include "tff_stat_stack.h"

#ifndef TFF_PLAYER_H
#define TFF_PLAYER_H

class CTFF_Player : public CBaseMultiplayerPlayer
{
public:
	DECLARE_CLASS( CTFF_Player, CBaseMultiplayerPlayer );

	CTFF_Player();
	~CTFF_Player();

	virtual void InitialSpawn();

	//Client commands
	virtual bool ClientCommand( const CCommand &args );
	virtual bool SetTeamCommand( const CCommand &args );
	virtual bool SetHeroCommand( const CCommand &args );
	virtual int GetAutoBalanceTeam();

	//Player stats without any modifiers
	virtual float GetBaseFloatStat(TFF_STAT stat);
	virtual char* GetBaseStringStat(TFF_STAT stat);

	//Player's current stats with all modifiers applied
	virtual float GetFloatStat(TFF_STAT stat);
	virtual char* GetStringStat(TFF_STAT stat);

private:
	TFF_HERO m_HeroIndex;
	CTTF_StatStack * m_pInventory;
};

inline CTFF_Player * ToTFFPlayer(CBaseEntity * pEntity)
{
	if ( !pEntity || !pEntity->IsPlayer() )
		return NULL;

	return dynamic_cast<CTFF_Player *>(pEntity);
}

#endif //TFF_PLAYER_H