#include "cbase.h"

#include "tff_hero.h"
// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//Load our stats from a keyvalues file
bool CTFF_BaseHero::Load()
{
	const char * pHeroName = UTIL_TFF_HeroName( m_HeroType );
	CUtlString  * path = new CUtlString("scripts/hero/");
	path->Append( pHeroName );
	path->Append( ".txt" );

	m_pKeys = new KeyValues( pHeroName );

	return m_pKeys->LoadFromFile( (IBaseFileSystem *)filesystem, path->Get() );
}

//Precache our assets
void CTFF_BaseHero::Precache()
{
	if (m_pKeys == NULL )
	{
		if(!Load()) return;
	}

	char * pString;

	pString = (char *)m_pKeys->GetString("Weapon1","");
	if( strlen(pString) > 0 ) UTIL_PrecacheOther(pString);

	pString = (char *)m_pKeys->GetString("Weapon2","");
	if( strlen(pString) > 0 ) UTIL_PrecacheOther(pString);

	pString = (char *)m_pKeys->GetString("Weapon3","");
	if( strlen(pString) > 0 ) UTIL_PrecacheOther(pString);

	pString = (char *)m_pKeys->GetString("Weapon4","");
	if( strlen(pString) > 0 ) UTIL_PrecacheOther(pString);

	pString = (char *)m_pKeys->GetString("BlueModel","");
	if( strlen(pString) > 0 ) CBaseEntity::PrecacheModel(pString);
		
	pString = (char *)m_pKeys->GetString("RedModel","");
	if( strlen(pString) > 0 ) CBaseEntity::PrecacheModel(pString);

	pString = (char *)m_pKeys->GetString("FootstepSound","");
	if( strlen(pString) > 0 ) CBaseEntity::PrecacheScriptSound(pString);
		
	pString = (char *)m_pKeys->GetString("JumpSound","");
	if( strlen(pString) > 0 ) CBaseEntity::PrecacheScriptSound(pString);

	pString = (char *)m_pKeys->GetString("SpawnSound","");
	if( strlen(pString) > 0 ) CBaseEntity::PrecacheScriptSound(pString);
		
	pString = (char *)m_pKeys->GetString("SmallWoundSound","");
	if( strlen(pString) > 0 ) CBaseEntity::PrecacheScriptSound(pString);

	pString = (char *)m_pKeys->GetString("WoundedSound","");
	if( strlen(pString) > 0 ) CBaseEntity::PrecacheScriptSound(pString);
		
	pString = (char *)m_pKeys->GetString("BadWoundSound","");
	if( strlen(pString) > 0 ) CBaseEntity::PrecacheScriptSound(pString);

	pString = (char *)m_pKeys->GetString("DeathSound","");
	if( strlen(pString) > 0 ) CBaseEntity::PrecacheScriptSound(pString);
}

//Lookup stats in our keyvalues, missing stats are returned un-altered
float CTFF_BaseHero::Apply( TFF_STAT stat, float base )
{
	if( base == 0.0f  || stat == 0 || m_pKeys == NULL ) return base;

	return base * m_pKeys->GetFloat( UTIL_TFF_StatName(stat), 1.0f ); //multiply by our stat or pass-though un-modified
}

//Loookup strings in our keyvalues, missing strings return the base
char * CTFF_BaseHero::Apply( TFF_STAT stat, char * base )
{
	if( stat == 0 || m_pKeys == NULL  ) return base;

	return (char *)m_pKeys->GetString( UTIL_TFF_StatName(stat), base );  //use our stat or pass through un-modified
}

void CTFF_BaseHero::SwitchPlayerTo(CBasePlayer * pPlayer)
{
};

void CTFF_BaseHero::SwitchPlayerFrom(CBasePlayer * pPlayer)
{
};