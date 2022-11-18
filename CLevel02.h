#pragma once
#include "CLevel.h"

class CSound;

class CLevel02 :
    public CLevel
{
private:
    float    m_DurationTime;
    UINT     m_MonsterCount;
    bool     Started;
    bool     Finished;
    bool     PlayerSpawn;

    CSound*  BGM;

public:
    virtual void init() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual UINT GetMonsterCount() override { return m_MonsterCount; };
    virtual void SetMonsterCount(UINT _count) override { m_MonsterCount = _count; };

    virtual CSound* GetBGM() override { return BGM; }
    virtual void GetExit() override { ChangeLevel(LEVEL_TYPE::START); }

public:
    void LoadTile();

public:
    CLevel02();
    ~CLevel02();

    friend class CPDeadState;
};

