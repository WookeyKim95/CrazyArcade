#pragma once
#include "CMonsterState.h"
class CMBTwoDeadState :
    public CMonsterState
{
private:
    float   m_DurationTime;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CMBTwoDeadState);

public:
    CMBTwoDeadState();
    ~CMBTwoDeadState();
};

