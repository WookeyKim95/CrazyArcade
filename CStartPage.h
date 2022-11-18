#pragma once
#include "CLevel.h"

class CSound;
class CUI;

class CStartPage :
    public CLevel
{
private:
    CSound* BGM;

public:
    virtual void init() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void ChangeToNormalMode() { ChangeLevel(LEVEL_TYPE::LEVEL_01); };
    void ChangeToVSMode() { ChangeLevel(LEVEL_TYPE::LEVEL_VS); };

public:
    CStartPage();
    ~CStartPage();

};

