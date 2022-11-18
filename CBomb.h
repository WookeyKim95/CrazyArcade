#pragma once
#include "CObj.h"

class CPlayer;

class CBomb :
    public CObj
{
private:
    float   m_DurationTime;
    float   m_fSpeed;
    CPlayer* m_WhoUsed;
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

    void SetBKicked(bool _Kicked, int _dir) { m_BKicked = _Kicked; m_dir = _dir; }

public:
    CLONE(CBomb);

public:
    CBomb(CPlayer* Player, int _WaveCount);
    ~CBomb();

};

