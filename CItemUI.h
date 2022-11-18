#pragma once
#include "CUI.h"

class CTexture;
class CPlayer;
enum class ITEM;


class CItemUI :
    public CUI
{
private:
    ITEM m_Slot;
    CTexture* m_pAtlas;
    CTexture* m_ItemAtlas[8];
    CPlayer* m_WhoUse;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CItemUI(CPlayer* _who);
    ~CItemUI();
};

