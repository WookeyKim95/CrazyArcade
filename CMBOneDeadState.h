#pragma once
#include "CMonsterState.h"

class CMBOneDeadState :
    public CMonsterState
{
private:
    float   m_DurationTime;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CMBOneDeadState);

public:
    CMBOneDeadState();
    ~CMBOneDeadState();
};

