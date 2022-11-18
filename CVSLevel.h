#pragma once
#include "CLevel.h"
class CVSLevel :
    public CLevel
{
private:
    UINT     m_PlayerCount;
    float    m_DurationTime;
    bool     Started;
    bool     Finished;
    bool     PlayerSpawn;

    CSound* BGM;

public:
    virtual void init() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual CSound* GetBGM() override { return BGM; }
    virtual void GetExit() override { ChangeLevel(LEVEL_TYPE::START); }

public:
    void LoadTile();

public:
    CVSLevel();
    ~CVSLevel();
};

