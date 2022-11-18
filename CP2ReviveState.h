#pragma once
#include "CPlayer2State.h"
class CP2ReviveState :
    public CPlayer2State
{
private:
    float   m_DurationTime;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CP2ReviveState);

public:
    CP2ReviveState();
    ~CP2ReviveState();
};

