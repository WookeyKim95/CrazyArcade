#pragma once
#include "CItem.h"

class CTexture;

class CSpeedUp :
    public CItem
{
private:
    CTexture* m_pAtlas; // Ÿ���� ����� �̹��� ���� ����
    int             m_iImgIdx; // Ÿ�� �̹��� �ε���
    float           m_AccTime;

public:
    void SetAtlas(CTexture* _pAtlas) { m_pAtlas = _pAtlas; }

    CTexture* GetAtlas() { return m_pAtlas; }

    virtual void tick();
    virtual void render(HDC _dc);

    void    BeginOverlap(CCollider* _pOther);
    void    OnOverlap(CCollider* _pOther);
    void    EndOverlap(CCollider* _pOther);

public:
    CLONE(CSpeedUp);

public:
    CSpeedUp();
    ~CSpeedUp();
};

