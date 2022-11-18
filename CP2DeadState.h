#pragma once
#include "CPlayer2State.h"
class CP2DeadState :
    public CPlayer2State
{
private:
    float   m_DurationTime;
    bool    m_Lost;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CP2DeadState);

public:
    CP2DeadState();
    ~CP2DeadState();
};

