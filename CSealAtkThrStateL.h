#pragma once
#include "CMonsterState.h"
class CSealAtkThrStateL :
    public CMonsterState
{
private:
    float   m_DurationTime;
    bool    m_BAttacked;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CSealAtkThrStateL);

public:
    CSealAtkThrStateL();
    ~CSealAtkThrStateL();
};

