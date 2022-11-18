#pragma once
#include "CObj.h"

class CTexture;

class CTile :
    public CObj
{
private:
    CTexture*       m_pAtlas; // Ÿ���� ����� �̹��� ���� ����
    int             m_iImgIdx; // Ÿ�� �̹��� �ε���
    bool            m_Can_Walk; // ������ �� �ִ� ������ ����

public:
    void SetAtlas(CTexture* _pAtlas) { m_pAtlas = _pAtlas; }
    void SetCanWalk(bool _pWalk) { m_Can_Walk = _pWalk; }

    CTexture* GetAtlas() { return m_pAtlas; }
    bool GetCanWalk() { return m_Can_Walk; }

    virtual void tick();
    virtual void render(HDC _dc);

    void Save(FILE* _pFile);
    void Load(FILE* _pFile);

public:
    CLONE(CTile);

public:
    CTile();
    ~CTile();
};

