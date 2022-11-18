#pragma once
#include "CEntity.h"


class CObj;
class CSound;

class CLevel :
    public CEntity
{
private:
    vector<CObj*>   m_arrLayer[(UINT)LAYER::END];

    vector<CObj*>   m_vecTile;  // ȭ��ȿ� ������ Ÿ��
    vector<CObj*>   m_TileTexture; // Ÿ�� �ؽ��ĸ� ������ ����

    UINT            m_iTileXCount;
    UINT            m_iTileYCount;

    UINT             m_MonsterCount;

    CSound* BGM;

public:
    UINT GetTileXCount() { return m_iTileXCount; }
    UINT GetTileYCount() { return m_iTileYCount; }

public:
    virtual void init() = 0;
    virtual void tick();
    virtual void final_tick();
    virtual void render(HDC _dc);

    virtual void Enter() = 0;   // ������ ������ �� ȣ�� ��
    virtual void Exit() = 0;    // ������ ��� �� ȣ�� ��

    virtual CSound* GetBGM() { return BGM; };

public:
    void AddObject(CObj* _pObj, LAYER _Layer) { m_arrLayer[(UINT)_Layer].push_back(_pObj); }
    const vector<CObj*>& GetLayer(LAYER _layer) { return m_arrLayer[(UINT)_layer]; }
    void DeleteAllObject();
    void DeleteObject(LAYER _eLayer);

    void CreateTile(UINT _X, UINT _Y);
    void CreateBox(UINT _X, UINT _Y);
    void CreateObstacle(UINT _X, UINT _Y);

    void SetFocusedUI(CObj* _pUI);

    virtual UINT GetMonsterCount() { return m_MonsterCount; };
    virtual void SetMonsterCount(UINT _count) { m_MonsterCount = _count; };
    virtual void GetExit() { ChangeLevel(LEVEL_TYPE::START); }

public:
    CLONE_DEACTIVATE(CLevel);

public:
    CLevel();
    virtual ~CLevel();
};

