#pragma once
#include "CPlayerState.h"
class CPIdleState :
    public CPlayerState
{

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPIdleState);

public:
    CPIdleState();
    ~CPIdleState();
};

