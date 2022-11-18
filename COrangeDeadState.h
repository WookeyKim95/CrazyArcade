#pragma once
#include "CMonsterState.h"
class COrangeDeadState :
    public CMonsterState
{
private:
    float   m_DurationTime;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(COrangeDeadState);

public:
    COrangeDeadState();
    ~COrangeDeadState();
};

