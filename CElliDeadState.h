#pragma once
#include "CMonsterState.h"
class CElliDeadState :
    public CMonsterState
{
private:
    float   m_DurationTime;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CElliDeadState);

public:
    CElliDeadState();
    ~CElliDeadState();
};

