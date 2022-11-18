#pragma once
#include "CPlayerState.h"

class CPTrappedState :
    public CPlayerState
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
    CLONE(CPTrappedState);

public:
    CPTrappedState();
    ~CPTrappedState();
};

