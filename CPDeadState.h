#pragma once
#include "CPlayerState.h"
class CPDeadState :
    public CPlayerState
{
private:
    float   m_DurationTime;
    bool    m_Lost;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPDeadState);

public:
    CPDeadState();
    ~CPDeadState();
};

