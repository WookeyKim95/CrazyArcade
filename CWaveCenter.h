#pragma once
#include "CObj.h"
class CWaveCenter :
    public CObj
{
private:
    float   m_DurationTime;
    int     m_WaveCount;
    bool    m_BOOM;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

    virtual LAYER ReturnLayer() override { return LAYER::WAVE_CENTER; }

public:
    CLONE(CWaveCenter);

public:
    CWaveCenter(int _WaveCount);
    ~CWaveCenter();
};

