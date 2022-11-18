#pragma once
#include "CMonsterState.h"

class CMBOneIdleState :
	public CMonsterState
{
private:
    float   m_fSpeed;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CMBOneIdleState);

public:
    CMBOneIdleState();
    ~CMBOneIdleState();
};

