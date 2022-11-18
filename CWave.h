#pragma once
#include "CObj.h"

class CWave :
    public CObj
{
private:
    float   m_DurationTime;
    int     m_Dir;
    int     m_WaveCount;
    bool    m_BOOM;
    bool    m_MoreBOOM;
    bool    m_AniPlay;

public:
    void SetWaveDir(int _Dir) { m_Dir = _Dir; };
    int GetWaveDir() { return m_Dir; }

    void SetWaveCount(int _WaveCount) { m_WaveCount = _WaveCount; }
    int GetWaveCount() { return m_WaveCount; }

    void SetMoreBOOM(bool _MoreBOOM) { m_MoreBOOM = _MoreBOOM; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

    virtual LAYER ReturnLayer() override { return LAYER::WAVE; }

public:
    CLONE(CWave);

public:
    CWave(int _WaveCount, int _Dir);
    CWave(const CWave& _other, int _WaveCount, int _Dir);
    ~CWave();
};

