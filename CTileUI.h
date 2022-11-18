#pragma once
#include "CUI.h"

class CEditorLevel;
class CTexture;

typedef void(*TestFuncType)(void);

typedef void(CEntity::*DELEGATE)(void);

class CTileUI :
    public CUI
{
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
    virtual void MouseLbtnClicked();


public:
    CLONE(CTileUI);

public:
    CTileUI();
    ~CTileUI();
};

