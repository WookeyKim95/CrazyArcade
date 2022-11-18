#pragma once
#include "CComponent.h"

class CMonsterState;

class CMonsterAI :
    public CComponent
{
private:
    map<wstring, CMonsterState*>   m_mapState; // 상태 여부
    CMonsterState* m_mCurState;

public:
    virtual void tick() override {};
    virtual void final_tick() override;
    virtual void render(HDC _dc) override {};

    void AddState(const wstring& _strKey, CMonsterState* _pState);
    CMonsterState* FindState(const wstring& _strKey)
    {
        map<wstring, CMonsterState*>::iterator iter = m_mapState.find(_strKey);
        if (iter != m_mapState.end())
            return iter->second;
        return nullptr;
    }

    void ChangeState(const wstring& _strStateName);


    CLONE(CMonsterAI);

public:
    CMonsterAI(CObj* _pObj);
    CMonsterAI(const CMonsterAI& _other);
    ~CMonsterAI();
};

