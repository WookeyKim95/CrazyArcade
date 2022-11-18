#pragma once
#include "CObj.h"
#include "CMonsterAI.h"

class CMonsterState :
    public CEntity
{
private:
    CMonsterAI* m_pOwnerM; // State 를 소유하고 있는 AIComponent

public:
    virtual void finaltick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    CMonsterAI* GetOwnerMonsterAI() { return m_pOwnerM; }
    CObj* GetOwnerObj() { return m_pOwnerM->GetOwner(); }

    void ChangeState(const wchar_t* _strStateName);


public:
    CMonsterState* Clone() = 0;

public:
    CMonsterState();
    ~CMonsterState();

    friend class CMonsterAI;
};

