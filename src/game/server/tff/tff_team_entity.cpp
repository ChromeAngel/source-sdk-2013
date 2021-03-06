// Purpose: Body for tff_team_entity
// Boilerplate generated by ModMaker on 23/05/2018 08:03:45
/* base for team allied entities*/

#include "cbase.h"
#include "tff_team_entity.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

BEGIN_DATADESC( CTffTeamEntity )
    DEFINE_KEYFIELD( m_iTeamNum, FIELD_INTEGER, "team_number" ),
	DEFINE_INPUTFUNC( FIELD_INPUT, "SetTeamNumber", SetTeamNumber ),
    DEFINE_OUTPUT( m_OnTeamSet, "OnTeamSet" ),
END_DATADESC()

LINK_ENTITY_TO_CLASS(tff_team_entity, CTffTeamEntity);

/* Specify the team number to change to */
void CTffTeamCore::SetTeamNumber(inputdata_t& inputdata)
{
	GetBaseEntity()->ChangeTeam(inputdata.value.Int());
	m_OnTeamSet.FireOutput(inputdata.pActivator, GetBaseEntity());
}

void CTffTeamCore::ChangeTeam(int teamNumber)
{
	GetBaseEntity()->ChangeTeam(teamNumber);
	m_OnTeamSet.FireOutput(GetBaseEntity(), GetBaseEntity());
};

bool CTffTeamCore::IsAlly(CBaseEntity * pOther)
{
	if (pOther == NULL) return false;

	return (pOther->GetTeamNumber() == GetBaseEntity()->GetTeamNumber());
};

bool CTffTeamCore::IsEnemy(CBaseEntity * pOther)
{
	if (pOther == NULL) return false;

	int myTeam = GetBaseEntity()->GetTeamNumber();
	
	if (myTeam == TEAM_RED && pOther->GetTeamNumber() == TEAM_BLUE) return true;

	if (myTeam == TEAM_BLUE && pOther->GetTeamNumber() == TEAM_RED) return true;

	return false;
};

bool CTffTeamCore::IsOnRealTeam(CBaseEntity * pOther)
{
	if (pOther == NULL) return false;

	return (pOther->GetTeamNumber() == TEAM_RED || pOther->GetTeamNumber() == TEAM_BLUE);
};