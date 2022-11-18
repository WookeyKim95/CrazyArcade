#pragma once
#include "CObj.h"

class CTexture;

class CTile :
    public CObj
{
private:
    CTexture*       m_pAtlas; // 타일이 사용할 이미지 파일 정보
    int             m_iImgIdx; // 타일 이미지 인덱스
    bool            m_Can_Walk; // 지나갈 수 있는 곳인지 여부

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

