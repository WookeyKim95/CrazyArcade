#pragma once
#include "CLevel.h"

class CTexture;
class CTileUI;
class CUI;

enum class EDITOR_MODE
{
    TILE,
    BOX,
    OBJECT,
    NONE,
};

class CEditorLevel :
    public CLevel
{
private:
    HMENU           m_hMenu;
    EDITOR_MODE     m_eMode;
    UINT            m_TileXCount = 15;
    UINT            m_TileYCount = 13;

    vector<CTexture*>   m_Tilelist; // 타일 텍스쳐 모음
    vector<CTexture*>   m_Boxlist; // 박스 텍스쳐 모음

    int             m_curPalette;

    UINT            m_AtlasNum; // 현재 선택한 타일의 아틀라스를 선택하기 위한 것.
                                // 팔레트 출력 목록

public:
    virtual void init() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    void update();
    void tile_update();
    void Box_update();
    void CreateUI();

public:
    void SaveTile();
    void LoadTile();

public:
    void SetAtlasNum0() { m_AtlasNum = 0; };
    void SetAtlasNum1() { m_AtlasNum = 1; };
    void SetAtlasNum2() { m_AtlasNum = 2; };
    void SetAtlasNum3() { m_AtlasNum = 3; };
    void SetAtlasNum4() { m_AtlasNum = 4; };
    void SetAtlasNum5() { m_AtlasNum = 5; };
    void SetAtlasNum6() { m_AtlasNum = 6; };
    void SetAtlasNum7() { m_AtlasNum = 7; };
    void SetAtlasNum8() { m_AtlasNum = 8; };
    void SetAtlasNum9() { m_AtlasNum = 9; };
    void SetAtlasNum10() { m_AtlasNum = 10; };
    void SetAtlasNum11() { m_AtlasNum = 11; };
    void SetAtlasNum12() { m_AtlasNum = 12; };
    void SetAtlasNum13() { m_AtlasNum = 13; };
    void SetAtlasNum14() { m_AtlasNum = 14; };
    void SetAtlasNum15() { m_AtlasNum = 15; };

public:
    CEditorLevel();
    ~CEditorLevel();
};

