#pragma once
#include "CEntity.h"

#include "CPlayer2.h"
#include "CObj.h"

class CPlayer2State :
    public CEntity
{
private:
    CPlayer2* m_pOwnerP; // State 를 소유하고 있는 AIComponent

public:
    virtual void finaltick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    CPlayer2* GetOwnerPlayer() { return m_pOwnerP; }

    void ChangeState(const wchar_t* _strStateName);


public:
    CPlayer2State* Clone() = 0;

public:
    CPlayer2State();
    ~CPlayer2State();

    friend class CPlayer2;
};

