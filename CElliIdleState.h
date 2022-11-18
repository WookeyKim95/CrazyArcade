#pragma once
#include "CMonsterState.h"

class CMonster;

class CElliIdleState :
    public CMonsterState
{
private:
    float   m_fSpeed;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CElliIdleState);

public:
    CElliIdleState();
    ~CElliIdleState();
};

