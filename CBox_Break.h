#pragma once
#include "CObj.h"
class CTexture;

class CBox_Break :
    public CObj
{
private:
    CTexture* m_pAtlas; // Ÿ���� ����� �̹��� ���� ����
    int             m_iImgIdx; // Ÿ�� �̹��� �ε���

public:
    void SetAtlas(CTexture* _pAtlas) { m_pAtlas = _pAtlas; }

    CTexture* GetAtlas() { return m_pAtlas; }

    virtual void tick();
    virtual void render(HDC _dc);

    void Save(FILE* _pFile);
    void Load(FILE* _pFile);

    void    BeginOverlap(CCollider* _pOther);
    void    OnOverlap(CCollider* _pOther);
    void    EndOverlap(CCollider* _pOther);

public:
    CLONE(CBox_Break);

public:
    CBox_Break();
    ~CBox_Break();
};

