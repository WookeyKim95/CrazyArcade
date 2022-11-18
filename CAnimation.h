#pragma once
#include "CEntity.h"

class CAnimator;
class CTexture;

class CAnimation :
    public CEntity
{
private:
    wstring             m_strName;
    CAnimator*          m_pAnimator;
    vector<tAnimFrm>    m_vecFrm;
    CTexture*           m_pAtlas;
    int                 m_iCurFrm;
    float               m_fAccTime;
    bool                m_bFinish;

private:
    void init(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, int _iMaxFrmCount, float _fDuration);

public:
    void tick();
    void render(HDC _dc);

public:
    bool IsFinish() { return m_bFinish; }
    void Reset()
    {
        m_bFinish = false;
        m_iCurFrm = 0;
        m_fAccTime = 0.f;
    }

    wstring GetName() { return m_strName; }
    void SetName(wstring _strName) { m_strName = _strName; }
    void Save(const wstring& _strRelativePath);
    void Load(const wstring& _strRelativePath);


public:
    CLONE(CAnimation);

public:
    CAnimation(CAnimator* _pAnimator);
    CAnimation(const CAnimation& _other);
    ~CAnimation();

    friend class CAnimator;
};

