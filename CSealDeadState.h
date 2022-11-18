#pragma once
#include "CMonsterState.h"
class CSealDeadState :
    public CMonsterState
{
private:
    float   m_DurationTime;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSealDeadState);

public:
    CSealDeadState();
    ~CSealDeadState();
};

