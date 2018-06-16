#include "cbase.h"

#include "tff_player.h"
// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

LINK_ENTITY_TO_CLASS( player, CTFF_Player );

CTFF_Player::CTFF_Player()
{
	m_pInventory = new CTTF_StatStack();
};

CTFF_Player::~CTFF_Player()
{
	m_pInventory->Clear();
	delete m_pInventory;
};

void CTFF_Player::InitialSpawn()
{
	SetModel("models/player.mdl");
	BaseClass::InitialSpawn();
};

float CTFF_Player::GetBaseFloatStat(TFF_STAT stat)
{
	//TODO add a switch here that returns sane defaults for all stats
	return 1.0f;
};

char* CTFF_Player::GetBaseStringStat(TFF_STAT stat)
{
	//TODO add a switch here that returns sane defaults for all stats
	return NULL;
};

float CTFF_Player::GetFloatStat(TFF_STAT stat)
{
	return m_pInventory->Apply(stat,GetBaseFloatStat(stat));
};

char* CTFF_Player::GetStringStat(TFF_STAT stat)
{
	return m_pInventory->Apply(stat,GetBaseStringStat(stat));
};

//TODO Client Commands : SetTeam, SetClass
bool CTFF_Player::ClientCommand( const CCommand &args )
{
	const char *cmd = args[0];
	if(FStrEq(cmd,"SetTeam"))
	{
		if(SetTeamCommand(args)) return true;
	}
	if(FStrEq(cmd,"SetHero"))
	{
		if(SetHeroCommand(args)) return true;
	}
	return BaseClass::ClientCommand( args );
}

bool CTFF_Player::SetTeamCommand( const CCommand &args )
{
	if(args.ArgC() < 2) return false;

	const char *param = args[1];
	int iTeam = atoi(param);
	if(iTeam < TEAM_ANY || iTeam >= TEAM_COUNT ) return false;
	if(iTeam == TEAM_INVALID || iTeam == TEAM_UNASSIGNED) return false;
	if(TEAM_ANY == iTeam)
	{
		iTeam = GetAutoBalanceTeam();
	}
	if(iTeam == GetTeamNumber()) return false;

	ChangeTeam(iTeam);

	return true;
};

bool CTFF_Player::SetHeroCommand( const CCommand &args )
{
	if(args.ArgC() < 2) return false;

	const char *param = args[1];
	int iHero = atoi(param);

	if(iHero < 1 || iHero >= TFF_LAST_HERO) return false;

	g_pTFF_Hero_Manager->SwitchPlayerFrom(this, m_HeroIndex);
	g_pTFF_Hero_Manager->SwitchPlayerTo(this,iHero);
	m_HeroIndex = iHero;

	return true;
};

int CTFF_Player::GetAutoBalanceTeam()
{
	//TODO count the players on each team and put this player on the smallest team
	//if teams are equal, put player on the opposite team to the one they were last on
	return TEAM_BLUE;
};