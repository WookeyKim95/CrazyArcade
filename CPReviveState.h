#pragma once
#include "CPlayerState.h"
class CPReviveState :
    public CPlayerState
{
private:
    float   m_DurationTime;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPReviveState);

public:
    CPReviveState();
    ~CPReviveState();
};

