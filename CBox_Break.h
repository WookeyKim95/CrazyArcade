#pragma once
#include "CObj.h"
class CTexture;

class CBox_Break :
    public CObj
{
private:
    CTexture* m_pAtlas; // 타일이 사용할 이미지 파일 정보
    int             m_iImgIdx; // 타일 이미지 인덱스

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

