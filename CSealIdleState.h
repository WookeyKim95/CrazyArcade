#pragma once
#include "CMonsterState.h"

class CSealIdleState :
    public CMonsterState
{
private:
    float   m_fSpeed;
    float   m_DurationTime;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSealIdleState);

public:
    CSealIdleState();
    ~CSealIdleState();
};

