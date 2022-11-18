#pragma once
#include "CUI.h"

class CTexture;
class CPlayer2;
enum class ITEM2;

class CItemUI2 :
    public CUI
{
private:
    ITEM2 m_Slot;
    CTexture* m_pAtlas;
    CTexture* m_ItemAtlas[8];
    CPlayer2* m_WhoUse;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CItemUI2(CPlayer2* _who);
    ~CItemUI2();
};

