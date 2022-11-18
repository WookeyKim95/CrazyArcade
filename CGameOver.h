#pragma once
#include "CUI.h"
class CGameOver :
    public CUI
{
private:
    float   m_DurationTime;

    Vec2    m_vLeftRightPadding;
    Vec2    m_vTopBottomPadding;
    Vec2    m_vInnerPadding;
    Vec2    m_vPressPos;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual LAYER ReturnLayer() override { return LAYER::UI; }

public:
    CLONE(CGameOver);

public:
    CGameOver();
    ~CGameOver();
};

