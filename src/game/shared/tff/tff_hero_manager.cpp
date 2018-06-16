/* Manager for all the type of Hero in the mod */
/* a static instance of this class g_pTFF_Hero_Manager  */

#include "cbase.h"

#include "tff_hero.h"
// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

CTFF_HeroManager::CTFF_HeroManager()
{
	int i;
	for(i=1;i<TFF_LAST_HERO;i++)
	{
		    m_pHero[i] = new CTFF_BaseHero(i);
		m_HeroCount[i] = 0;
	}
};

CTFF_HeroManager::~CTFF_HeroManager()
{
	int i;
	for(i=1;i<TFF_LAST_HERO;i++)
	{
		delete m_pHero[i];
	}
};

void CTFF_HeroManager::Precache()
{
	int i;
	for(i=1;i<TFF_LAST_HERO;i++)
	{
		m_pHero[i]->Precache();
	}
};

CTFF_BaseHero * CTFF_HeroManager::Get(TFF_HERO hero)
{
	if(hero > TFF_LAST_HERO) return NULL;
	if(hero < 1) return NULL;

	return m_pHero[hero];
};

void CTFF_HeroManager::SwitchPlayerTo(CBasePlayer * pPlayer, TFF_HERO hero)
{
	if(pPlayer == NULL) return;

	CTFF_BaseHero * pHero = Get(hero);

	if(pHero == NULL) return;

	pHero->SwitchPlayerTo(pPlayer);
	m_HeroCount[hero]++;
};

void CTFF_HeroManager::SwitchPlayerFrom(CBasePlayer * pPlayer, TFF_HERO hero)
{
	if(pPlayer == NULL) return;

	CTFF_BaseHero * pHero = Get(hero);

	if(pHero == NULL) return;

	pHero->SwitchPlayerTo(pPlayer);
	m_HeroCount[hero]--;
};
