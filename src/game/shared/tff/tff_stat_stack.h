#include "tff_stat.h"
#include "utlvector.h"

#ifndef TFF_STAT_STACK_H
#define TFF_STAT_STACK_H

class CTTF_StatStack:public CTTF_BaseState
{
public:
	//Apply our status to floating point stats
	virtual float Apply( TFF_STAT stat, float base );

	//Apply our status to string "stats"
	virtual char * Apply( TFF_STAT stat, char * base );

	//Some status effects  adjust over time, so every status effect needs a chance to think each frame
	virtual void Think();

	virtual void Add(CTTF_BaseState * state);
	virtual void Remove(CTTF_BaseState * state);
	virtual void Clear();
private:
	CUtlVector<CTTF_BaseState *> m_pStats;
};

#endif //TFF_STAT_STACK_H