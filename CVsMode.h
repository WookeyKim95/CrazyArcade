#pragma once
#include "CUI.h"

class StartPage;

typedef void(*TestFuncType)(void);

typedef void(CEntity::* DELEGATE)(void);

class CVsMode :
    public CUI
{
private:
    Vec2    m_vLeftRightPadding;
    Vec2    m_vTopBottomPadding;
    Vec2    m_vInnerPadding;


    Vec2    m_vPressPos;

private:
    // Call Back
    TestFuncType    m_pFunc;

    // Delegate
    CEntity* m_pInst;
    DELEGATE    m_pDelegateFunc;

public:
    void SetCallBack(TestFuncType _pCallBack) { m_pFunc = _pCallBack; }
    void SetDelegate(CEntity* _pInst, DELEGATE _Func)
    {
        m_pInst = _pInst;
        m_pDelegateFunc = _Func;
    }


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual LAYER ReturnLayer() override { return LAYER::UI; }

public:
    virtual void MouseLbtnClicked();

public:
    CLONE(CVsMode);

public:
    CVsMode();
    ~CVsMode();
};

