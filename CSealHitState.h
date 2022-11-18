#pragma once
#include "CMonsterState.h"
class CSealHitState :
    public CMonsterState
{
private:
    float   m_DurationTime;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSealHitState);

public:
    CSealHitState();
    ~CSealHitState();
};

