#pragma once
#include "CItem.h"

class CTexture;

class CBombPlus :
    public CItem
{
private:
    CTexture* m_pAtlas; // 타일이 사용할 이미지 파일 정보
    int             m_iImgIdx; // 타일 이미지 인덱스
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
    CLONE(CBombPlus);

public:
    CBombPlus();
    ~CBombPlus();
};

