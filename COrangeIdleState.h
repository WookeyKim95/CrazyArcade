#pragma once
#include "CMonsterState.h"
class COrangeIdleState :
    public CMonsterState
{
private:
    float   m_fSpeed;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(COrangeIdleState);

public:
    COrangeIdleState();
    ~COrangeIdleState();
};

