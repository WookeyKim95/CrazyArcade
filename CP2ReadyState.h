#pragma once
#include "CPlayer2State.h"
class CP2ReadyState :
    public CPlayer2State
{
private:
    float   m_DurationTime;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CP2ReadyState);

public:
    CP2ReadyState();
    ~CP2ReadyState();
};

