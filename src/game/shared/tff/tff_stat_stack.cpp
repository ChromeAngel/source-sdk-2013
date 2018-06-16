#include "cbase.h"

#include "tff_stat_stack.h"
// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//Apply our status to floating point stats
float CTTF_StatStack::Apply( TFF_STAT stat, float base )
{
	float result = base;

	FOR_EACH_VEC( m_pStats, index )
	{
		result = m_pStats[index]->Apply(stat,result);
	}

	return result;
};

//Apply our status to string "stats"
char * CTTF_StatStack::Apply( TFF_STAT stat, char * base )
{
	char * result = base;

	FOR_EACH_VEC( m_pStats, index )
	{
		result = m_pStats[index]->Apply(stat,result);
	}

	return result;
};

//Some status effects  adjust over time, so every status effect needs a chance to think each frame
void CTTF_StatStack::Think()
{
	FOR_EACH_VEC( m_pStats, index )
	{
		m_pStats[index]->Think();
	}
};

//Add a state to the stack
void CTTF_StatStack::Add(CTTF_BaseState * state)
{
	m_pStats.AddToTail(state);
};

//Remove a state from the stack
void CTTF_StatStack::Remove(CTTF_BaseState * state)
{
	m_pStats.FindAndFastRemove(state);
};

void CTTF_StatStack::Clear()
{
	m_pStats.RemoveAll();
};