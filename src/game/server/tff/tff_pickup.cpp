// Purpose: Body for tff_pickup
// Boilerplate generated by ModMaker on 23/05/2018 07:52:08
/* pickup a random item*/

#include "cbase.h"
#include "tff_pickup.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

LINK_ENTITY_TO_CLASS( tff_pickup, CTffPickup );

BEGIN_DATADESC( CTffPickup )
    DEFINE_KEYFIELD( m_iSpawnRate, FIELD_INTEGER, "spawn_rate" ),
    DEFINE_KEYFIELD( m_iSpawnSound, FIELD_SOUNDNAME, "spawn_sound" ),
    DEFINE_OUTPUT( m_OnSpawnItem, "OnSpawnItem" ),
    DEFINE_OUTPUT( m_OnItemPickup, "OnItemPickup" ),
END_DATADESC()

void CTffPickup ::Precache()
{
    PrecacheScriptSound( STRING(m_iSpawnSound) );
	// UTIL_PrecacheOther(); // TODO cache things we're going to spawn here
}

void CTffPickup ::Spawn()
{
    BaseClass::Spawn();

    Precache();

	SetContextThink(&CTffPickup::RespawnItemThink, RandomFloat(0.01f, (float)m_iSpawnRate), "spawn_item");
}

void CTffPickup::RespawnItemThink()
{
	/*
	if m_spawned_item is valid
		if m_spawned_item is not null
			if m_spawned_item is near by
				schedule us to try again later
				return
	if there is no free space
			schedule us to try again later
			return
	
	use the spawnflags to choose what to spawn
	create an instance of the spawnable class
	store the ehandle of the instance in m_spawned_item
	connect an output from m_spawned_item to CTffPickup::OnItemPickup

	EmitSound(STRING(m_iSpawnSound)); //play the spawn sound
	m_OnSpawnItem.FireOutput(this, this); //fire the spawn output

	schedule us to try again later
	*/
}

void CTffPickup::OnItemPickup(inputdata_t& inputdata)
{
	m_OnItemPickup.FireOutput(inputdata.pActivator, this);
}