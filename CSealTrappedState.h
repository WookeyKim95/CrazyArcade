#pragma once
#include "CMonsterState.h"
class CSealTrappedState :
    public CMonsterState
{
private:
    float   m_DurationTime;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSealTrappedState);

public:
    CSealTrappedState();
    ~CSealTrappedState();
};

