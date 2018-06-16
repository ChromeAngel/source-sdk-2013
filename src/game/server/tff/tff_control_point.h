// Purpose: Header for tff_control_point
// Boilerplate generated by ModMaker on 23/05/2018 07:44:09
/* */

#include "tff_team_entity.h"

#ifndef TFF_CP
#define TFF_CP

class CTffControlPoint : public CBaseEntity, CTffTeamCore // Studiomodel, Targetname, Inputfilter
{
public:
    DECLARE_CLASS( CTffControlPoint, CBaseEntity );

	enum CP_State
	{
		UNKNOWN,
		IDLE,
		CONTESTED,
		CAPTURING
	};

    int      m_iSequence;
    int      m_iRadius;
    float    m_flCaptureTime;
	Vector   m_vecCameraOffset;
    string_t m_iStartCaptureSound;
    string_t m_iContestedCaptureSound;
    string_t m_iLoopCaptureSound;
    string_t m_iFinishCaptureSound;
    string_t m_iLockedSound;

    virtual void Precache();
    virtual void Spawn();

	virtual void CP_Think();

    // outputs
    COutputEvent m_OnCaptureStart; /* Fires when one team tries to capture this point */
    COutputEvent m_OnContested; /* Fires when both teams try to capture the point */
    COutputEvent m_OnCaptured; /* Fires when a team captures this point */

	TEAM_CORE();

    DECLARE_DATADESC();

private:
	virtual void InitNextAndPrevious();
	virtual void CPCheckPlayers();
	virtual void SetState(CP_State state, CBaseEntity * activator);


	int m_iAllies;
	int m_iEnemies;
	CBaseEntity * m_pEnemy;
	float m_fCaptureFinishTIme;
	EHANDLE m_hPrevCP;
	EHANDLE m_hNextCP;

	CP_State m_eState;
};

#endif // !TFF_CP
