#pragma once
#include "CMonsterState.h"
class CMBTwoIdleState :
    public CMonsterState
{
private:
    float   m_fSpeed;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CMBTwoIdleState);

public:
    CMBTwoIdleState();
    ~CMBTwoIdleState();
};

