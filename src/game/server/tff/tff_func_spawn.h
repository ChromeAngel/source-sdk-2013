// Purpose: Header for tff_func_spawn
// Boilerplate generated by ModMaker on 23/05/2018 07:43:29
/* Area to spawn team players in*/

#include "tff_team_entity.h"
#include "triggers.h"

class CTffFuncSpawn : public CBaseTrigger, CTffTeamCore // tff_team_entity, EnableDisable, Angles, Targetname, BaseBrush
{
public:
    DECLARE_CLASS( CTffFuncSpawn, CBaseTrigger);

    // outputs
    COutputEvent m_OnPlayerSpawn;
    COutputEvent m_OnPlayerLeave;
    COutputEvent m_OnPlayerleave;

	TEAM_CORE();

    DECLARE_DATADESC();

	virtual bool SpawnPlayer(CBasePlayer * pPlayer);
};
