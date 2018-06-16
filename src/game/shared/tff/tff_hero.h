#include "tff_stat.h"

#ifndef TFF_HERO_H
#define TFF_HERO_H
#pragma once

#define TFF_LAST_HERO 10
#define TFF_HERO int

struct TFF_HERO_NAME
{
	TFF_HERO     hero;
	const char * name;
};

static TFF_HERO_NAME g_TFF_HeroNames[TFF_LAST_HERO] = 
{
	{0,  "UNKNOWN"},
	{1,  "Soldier"},
	{2,  "Demo"},
	{3,  "Heavy"},
	{4,  "Medic"},
	{5,  "Engineer"},
	{6,  "Sniper"},
	{7,  "Scout"},
	{8,  "Spy"},
	{9,  "Pyro"},
};

static const char * UTIL_TFF_HeroName(TFF_HERO stat)
{
	if(stat > TFF_LAST_HERO) return "Invalid";
	if(stat < 0 ) return "Invalid";

	return g_TFF_StatNames[stat].name;
};

static TFF_HERO UTIL_TFF_ParseHeroName(const char * pName)
{
	if(pName == NULL) return 0; //Unknown

	int result = 0;
	for(result =0;result < TFF_LAST_HERO;result++)
	{
		if( FStrEq(pName,g_TFF_StatNames[result].name) ) return result;
	}

	return 0; //Unknown
};

class CTFF_BaseHero : public CTTF_BaseState
{
public:
	CTFF_BaseHero(TFF_HERO heroType)
	{
		m_HeroType = heroType;
	}

	//Status effect implmentation
	virtual float Apply( TFF_STAT stat, float base );
	virtual char * Apply( TFF_STAT stat, char * base );

	//Load stats from a keyvalues file (may need to cache them in arrays, as doing string comparisosn for very call could be a performance bottleneck)
	bool Load();
	//Prechache assets based on our stats
	void Precache();

	virtual void SwitchPlayerTo(CBasePlayer * pPlayer);
	virtual void SwitchPlayerFrom(CBasePlayer * pPlayer);
private:
	KeyValues * m_pKeys;
	TFF_HERO    m_HeroType;
};

class CTFF_HeroManager
{
public:
	CTFF_HeroManager();
	~CTFF_HeroManager();

	void Precache();

	CTFF_BaseHero * Get(TFF_HERO hero);
	void SwitchPlayerTo(CBasePlayer * pPlayer, TFF_HERO hero);
	void SwitchPlayerFrom(CBasePlayer * pPlayer, TFF_HERO hero);
private:
	CTFF_BaseHero * m_pHero[TFF_LAST_HERO];
	int m_HeroCount[TFF_LAST_HERO];
};

static CTFF_HeroManager * g_pTFF_Hero_Manager = new CTFF_HeroManager();

#endif //TFF_HERO_H