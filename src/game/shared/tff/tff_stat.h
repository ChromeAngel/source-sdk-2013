#ifndef TFF_STAT_H
#define TFF_STAT_H
#pragma once

#define TFF_LAST_STAT 42
#define TFF_STAT int

struct TFF_STAT_NAME
{
	int     stat;
	const char * name;
};

static TFF_STAT_NAME g_TFF_StatNames[TFF_LAST_STAT] = {
	{0,  "UNKNOWN"},
	{1,  "MaxHealth"},
	{2,  "DefaultHealth"},
	{3,  "RegenHealth"},
	{4,  "WalkSpeed"},
	{5,  "RunSpeed"},
	{6,  "JumpHeight"},
	{7,  "EyeHeight"},
	{8,  "GenericDamage"},
	{9,  "GenericArmour"},
	{10, "SharpDamage"},
	{11, "SharpArmour"},
	{12, "BluntDamage"},
	{13, "BluntArmour"},
	{14, "IceDamage"},
	{15, "IceArmour"},
	{16, "FireDamage"},
	{17, "FireArmour"},
	{18, "ShockDamage"},
	{19, "ShockArmour"},
	{20, "PsychicDamage"},
	{21, "PsychicArmour"},
	{22, "DrugHealth"},
	{23, "DrugResist"},
	{24, "MeleeDamage"},
	{25, "MeleeArmour"},
	{26, "SplashDamage"},
	{27, "SplashArmour"},
	{28, "BlueModel"},
	{29, "RedModel"},
	{30, "FootstepSound"},
	{31, "JumpSound"},
	{32, "SpawnSound"},
	{33, "SmallWoundSound"},
	{34, "WoundedSound"},
	{35, "BadWoundSound"},
	{36, "DeathSound"},
	{37, "DrawRate"},
	{38, "FireRate"},
	{39, "ReloadRate"},
	{40, "HolsterRate"},
	{41, "AttackSpread"}
	/* TODO add "stats" for particle system names */
};

static const char * UTIL_TFF_StatName(TFF_STAT stat)
{
	if(stat > TFF_LAST_STAT) return "Invalid";
	if(stat < 0 ) return "Invalid";

	return g_TFF_StatNames[stat].name;
};

static TFF_STAT UTIL_TFF_ParseStatName(const char * pName)
{
	if(pName == NULL) return 0; //Unknown

	int result = 0;
	for(result =0;result < TFF_LAST_STAT;result++)
	{
		if( FStrEq(pName,g_TFF_StatNames[result].name) ) return result;
	}

	return 0; //Unknown
};

//This is the base of all status effects

class CTTF_BaseState
{
public:
	//Apply our status to floating point stats
	virtual float Apply( TFF_STAT stat, float base )
	{
		return base;
	}

	//Apply our status to string "stats"
	virtual char * Apply( TFF_STAT stat, char * base )
	{
		return base;
	}

	//Some status effects  adjust over time, so every status effect needs a chance to think each frame
	virtual void Think() {return; };
};

#endif //TFF_STAT_H