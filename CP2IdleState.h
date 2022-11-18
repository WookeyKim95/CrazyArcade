#pragma once
#include "CPlayer2State.h"
class CP2IdleState :
    public CPlayer2State
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CP2IdleState);

public:
    CP2IdleState();
    ~CP2IdleState();
};

