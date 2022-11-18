#pragma once
#include "CUI.h"

class CLevel01;
class CLevel02;
class CLevel03;
class EditorLevel;
class CVSLevel;

typedef void(*TestFuncType)(void);

typedef void(CEntity::* DELEGATE)(void);

class CExitUI :
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

private:
    virtual void MouseLbtnClicked() override;

public:
    CLONE(CExitUI);

public:
    CExitUI();
    ~CExitUI();
};

