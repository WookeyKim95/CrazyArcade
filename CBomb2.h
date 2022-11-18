#pragma once
#include "CObj.h"

class CPlayer2;

class CBomb2 :
    public CObj
{
    float   m_DurationTime;
    float   m_fSpeed;
    CPlayer2* m_WhoUsed;
    int     m_WaveCount;
    bool    m_BKicked;
    int     m_dir;

    Vec2        m_TileCenter;
    int         m_NowCenTileX;
    int         m_NowCenTileY;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

    virtual LAYER ReturnLayer() override { return LAYER::BOMB; }

public:
    void BOOM();

public:
    CLONE(CBomb2);

public:
    CBomb2(CPlayer2* Player, int _WaveCount);
    ~CBomb2();
};

