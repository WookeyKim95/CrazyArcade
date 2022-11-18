#pragma once
#include "CEntity.h"

#include "CPlayer.h"
#include "CObj.h"

class CPlayerState :
    public CEntity
{
private:
    CPlayer* m_pOwnerP; // State 를 소유하고 있는 AIComponent

public:
    virtual void finaltick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    CPlayer* GetOwnerPlayer() { return m_pOwnerP; }

    void ChangeState(const wchar_t* _strStateName);


public:
    CPlayerState* Clone() = 0;

public:
    CPlayerState();
    ~CPlayerState();

    friend class CPlayer;
};

