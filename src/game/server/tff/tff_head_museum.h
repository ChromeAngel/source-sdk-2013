// Purpose: Header for tff_head_museum
// Boilerplate generated by ModMaker on 23/05/2018 07:50:03

#include "tff_team_entity.h"

enum capture_reason
{
	NULL_ENT,
	NO_FLAG,
	NO_RANGE,
	NO_TEAM,
	OK
};


class CTffHeadMuseum : public CBaseEntity, CTffTeamCore // tff_team_entity, Studiomodel, Targetname
{
public:
    DECLARE_CLASS( CTffHeadMuseum, CBaseEntity );

    int      m_iRadius;
    string_t m_iCaptureSound;
    string_t m_iFailedCaptureSound;

    virtual void Precache();
    virtual void Spawn();

    // outputs
    COutputEvent m_OnCapture; /* Fires when a head is captured here */
    COutputEvent m_OnFailedCapture; /* Fires when an enemy player tries to capture here */

	TEAM_CORE();

	virtual capture_reason CanCapture(CBaseEntity * pFlag);
	virtual void FlagTouch(CBaseEntity *pOther);

    DECLARE_DATADESC();
};