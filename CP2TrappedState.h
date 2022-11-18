#pragma once
#include "CPlayer2State.h"
class CP2TrappedState :
    public CPlayer2State
{
private:
    float   m_DurationTime;
    bool    m_ToRevive;
    float   m_fSpeed;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CP2TrappedState);

public:
    CP2TrappedState();
    ~CP2TrappedState();
};

