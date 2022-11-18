#pragma once
#include "CPlayerState.h"
class CPReadyState :
    public CPlayerState
{
private:
    float   m_DurationTime;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CPReadyState);

public:
    CPReadyState();
    ~CPReadyState();
};

