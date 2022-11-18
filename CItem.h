#pragma once
#include "CObj.h"

class CPlayer;
class CTexture;

class CItem :
    public CObj
{
private:
    CPlayer* m_WhoUsed;
    CTexture* m_pAtlas; // �������� ����� �̹��� ���� ����
    int             m_iImgIdx; // Ÿ�� �̹��� �ε���
    float           m_AccTime;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;


public:
    CLONE(CItem);

public:
    CItem();
    ~CItem();

};

