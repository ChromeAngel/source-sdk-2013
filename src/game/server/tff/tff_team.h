// Purpose: Header for tff_team
// Boilerplate generated by ModMaker on 15/06/2018 06:42:51
/* Team configuration, feedback and control*/

#include "tff_team_entity.h"
#include "tff_hero.h"
#include "team.h"

class CTffTeam : public CTeam, CTffTeamCore //Targetname
{
public:
    DECLARE_CLASS( CTffTeam, CTeam );

    string_t m_iSpawnEntity;
    int      m_iSpawnTime;
    string_t m_iRole;
    string_t m_iMission;
    string_t m_iMissionEntity;
    int      m_iTargetScore;
    string_t m_iHologramModel;
    int      m_iColor;
    //int      m_iMaxSoldiers;
    //int      m_iMaxDemoman;
    //int      m_iMaxHeavies;
    //int      m_iMaxMedics;
    //int      m_iMaxEngineers;
    //int      m_iMaxPyros;
    //int      m_iMaxSnipers;
    //int      m_iMaxSpies;
    //int      m_iMaxScouts;
	int      m_iMaxHeros[TFF_LAST_HERO];

    virtual void Precache();
    virtual void Spawn();

    // input handlers
    void InputAddScore( inputdata_t &inputdata ); /* Add points */
    void RemoveScore( inputdata_t &inputdata ); /* Remove points */
    void ResetScore( inputdata_t &inputdata ); /* Reset points to zero */
    void Victory( inputdata_t &inputdata ); /* Awards victory to this team */

	//CTeam overrides
	virtual void AddScore( int iScore );
	virtual void SetScore( int iScore );

	//TFF custom functions
	virtual bool CanUseHero( CBasePlayer *pPlayer , TFF_HERO hero );

	TEAM_CORE();

    DECLARE_DATADESC();
};
