// Purpose: Body for tff_team
// Boilerplate generated by ModMaker on 15/06/2018 06:42:51
/* Team configuration, feedback and control*/

#include "cbase.h"
#include "tff_team.h"
#include "tff_team_manager.h"
#include "teamplay_gamerules.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_DATADESC( CTffTeam )
    DEFINE_KEYFIELD( m_iSpawnEntity, FIELD_STRING, "spawn_entity" ),
    DEFINE_KEYFIELD( m_iSpawnTime, FIELD_INTEGER, "spawn_time" ),
    DEFINE_KEYFIELD( m_iRole, FIELD_INTEGER, "role" ),
    DEFINE_KEYFIELD( m_iMission, FIELD_STRING, "mission" ),
    DEFINE_KEYFIELD( m_iMissionEntity, FIELD_STRING, "mission_entity" ),
    DEFINE_KEYFIELD( m_iTargetScore, FIELD_INTEGER, "target_score" ),
    DEFINE_KEYFIELD( m_iHologramModel, FIELD_MODELNAME, "hologram_model" ),
    DEFINE_KEYFIELD( m_iColor, FIELD_COLOR32, "color" ),
    DEFINE_KEYFIELD( m_iMaxHeros[1], FIELD_INTEGER, "max_soldiers" ),
    DEFINE_KEYFIELD( m_iMaxHeros[2], FIELD_INTEGER, "max_demoman" ),
    DEFINE_KEYFIELD( m_iMaxHeros[3], FIELD_INTEGER, "max_heavies" ),
    DEFINE_KEYFIELD( m_iMaxHeros[4], FIELD_INTEGER, "max_medics" ),
    DEFINE_KEYFIELD( m_iMaxHeros[5], FIELD_INTEGER, "max_engineers" ),
    DEFINE_KEYFIELD( m_iMaxHeros[9], FIELD_INTEGER, "max_pyros" ),
    DEFINE_KEYFIELD( m_iMaxHeros[6], FIELD_INTEGER, "max_snipers" ),
    DEFINE_KEYFIELD( m_iMaxHeros[8], FIELD_INTEGER, "max_spies" ),
    DEFINE_KEYFIELD( m_iMaxHeros[7], FIELD_INTEGER, "max_scouts" ),
    DEFINE_INPUTFUNC( FIELD_INPUT, "AddScore", InputAddScore ),
    DEFINE_INPUTFUNC( FIELD_INPUT, "RemoveScore", RemoveScore ),
    DEFINE_INPUTFUNC( FIELD_INPUT, "ResetScore", ResetScore ),
    DEFINE_INPUTFUNC( FIELD_INPUT, "Victory", Victory ),
END_DATADESC()

LINK_ENTITY_TO_CLASS( tff_team, CTffTeam );

void CTffTeam ::Precache()
{
    PrecacheModel( STRING(m_iHologramModel) );
}

void CTffTeam ::Spawn()
{
    BaseClass::Spawn();

    Precache();
	Init( GetName(), m_iTeamNum );

	TFF_RegisterTeam( this, true );
}

/* Add points */
void CTffTeam :: InputAddScore(inputdata_t & inputdata)
{
	m_iScore = m_iScore + 1;

	if (m_iScore >= m_iTargetScore)
	{
		Victory(inputdata);
	}
}
/* Remove points */
void CTffTeam :: RemoveScore(inputdata_t & inputdata)
{
	AddScore(1);
}
/* Reset points to zero */
void CTffTeam :: ResetScore(inputdata_t & inputdata)
{
	SetScore(0);
}
/* Awards victory to this team */
void CTffTeam :: Victory(inputdata_t & inputdata)
{
	TeamplayGameRules()->SetWinningTeam(GetTeamNumber(), 1);
}

void CTffTeam :: AddScore( int iScore )
{
	BaseClass::AddScore( iScore );

	if (GetScore() >= m_iTargetScore)
	{
		TeamplayGameRules()->SetWinningTeam(GetTeamNumber(), 1);
	}
};

void CTffTeam :: SetScore( int iScore )
{
	BaseClass::SetScore( iScore );

	if (GetScore() >= m_iTargetScore)
	{
		TeamplayGameRules()->SetWinningTeam(GetTeamNumber(), 1);
	}
};

bool CTffTeam :: CanUseHero( CBasePlayer *pPlayer , TFF_HERO hero )
{
	if( pPlayer == NULL ) return false;
	if( !IsAlly( pPlayer ) ) return false;
	if( m_iMaxHeros[hero] == 0 ) return false;

	//TODO count allies playing as hero
	//if( count > m_iMaxHeros[hero] ) return false;

	return true;
}