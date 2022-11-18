#pragma once
#include "CObj.h"
class CMonsterObj :
    public CObj
{
private:
    float   m_DurationTime;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

    virtual LAYER ReturnLayer() override { return LAYER::MONSTER_OBJECTILE; }

public:
    CLONE(CMonsterObj);

public:
    CMonsterObj();
    ~CMonsterObj();
};

