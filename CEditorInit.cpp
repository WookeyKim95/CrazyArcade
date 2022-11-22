#include "pch.h"
#include "CEditorLevel.h"
#include "CLevel.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEngine.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CTile.h"
#include "CBox_Break.h"
#include "CObstacle.h"

#include "CUI.h"
#include "CStageUI.h"
#include "CTileUI.h"
#include "CBoxUI.h"
#include "CExitUI.h"

#include "resource.h"

void CEditorLevel::init()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	// UI 배치
	CreateUI();

	// 타일 텍스쳐 로딩
	CTexture* pTile0 = CResMgr::GetInst()->LoadTexture(L"Tile0", L"Texture\\Terrain\\Tile\\Tile0.bmp");

	// 타일 생성
	CreateTile(15, 13);

	// 박스 생성
	CreateBox(15, 13);

	// 장애물 여부 생성
	CreateObstacle(15, 13);

	// 각 타일에다가 사용할 아틀라스 이미지와, 이미지 인덱스를 세팅해준다.
	const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		// 타일 별 아틀라스 설정
		((CTile*)vecTile[i])->SetAtlas(m_Tilelist[0]);
	}



	// 각 타일에다가 사용할 아틀라스 이미지와, 이미지 인덱스를 세팅해준다.
	const vector<CObj*>& vecBox = GetLayer(LAYER::BOX_BREAK);
	for (size_t i = 0; i < vecBox.size(); ++i)
	{
		// 박스 별 아틀라스 설정
		((CBox_Break*)vecBox[i])->SetAtlas(nullptr);
	}

	const vector<CObj*>& vecObstacle = GetLayer(LAYER::OBSTACLE);
	for (size_t i = 0; i < vecObstacle.size(); ++i)
	{
		// 장애물 여부 true 설정
		((CObstacle*)vecObstacle[i])->SetObstacle(false);
	}

}


void CEditorLevel::CreateUI()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	CTexture* pStageUITex = CResMgr::GetInst()->LoadTexture(L"Stage", L"Texture\\UI\\mapToolMap.bmp");

	CTexture* pSave = CResMgr::GetInst()->LoadTexture(L"SaveButton", L"Texture\\UI\\Save.bmp");
	CTexture* pLoad = CResMgr::GetInst()->LoadTexture(L"LoadButton", L"Texture\\UI\\Load.bmp");
	CTexture* pInfo = CResMgr::GetInst()->LoadTexture(L"ButtonInfo", L"Texture\\UI\\KeyInfo.bmp");

	// Panel UI
	CStageUI* pStageUI = new CStageUI;
	pStageUI->SetIdleTex(pStageUITex);
	pStageUI->SetPos({ 0.f,0.f });
	AddObject(pStageUI, LAYER::UI);

	CExitUI* pExit = new CExitUI;
	pExit->SetPos(Vec2(650.f, 565.f));
	pExit->SetScale(Vec2(135.f, 25.f));
	pExit->SetDelegate(this, (DELEGATE)&CLevel::GetExit);
	pStageUI->AddChildUI(pExit);

	CTileUI* But_Save = new CTileUI;
	But_Save->SetIdleTex(pSave);
	But_Save->SetDelegate(this, (DELEGATE)&CEditorLevel::SaveTile);
	But_Save->SetPos({ 660.f, 450.f });
	pStageUI->AddChildUI(But_Save);

	CTileUI* But_Load = new CTileUI;
	But_Load->SetIdleTex(pLoad);
	But_Load->SetDelegate(this, (DELEGATE)&CEditorLevel::LoadTile);
	But_Load->SetPos({ 660.f, 500.f });
	pStageUI->AddChildUI(But_Load);

	CTileUI* But_Info = new CTileUI;
	But_Info->SetIdleTex(pInfo);
	But_Info->SetPos({ 400.f, 0.f });
	pStageUI->AddChildUI(But_Info);

	// 타일 텍스쳐 로딩
	CTexture* pTile0 = CResMgr::GetInst()->LoadTexture(L"Tile0", L"Texture\\Terrain\\Tile\\Tile0.bmp");
	CTexture* pTile1 = CResMgr::GetInst()->LoadTexture(L"Tile1", L"Texture\\Terrain\\Tile\\Tile1.bmp");
	CTexture* pTile2 = CResMgr::GetInst()->LoadTexture(L"Tile2", L"Texture\\Terrain\\Tile\\Tile2.bmp");
	CTexture* pTile3 = CResMgr::GetInst()->LoadTexture(L"Tile3", L"Texture\\Terrain\\Tile\\Tile3.bmp");
	CTexture* pTile4 = CResMgr::GetInst()->LoadTexture(L"Tile4", L"Texture\\Terrain\\Tile\\Tile4.bmp");
	CTexture* pTile5 = CResMgr::GetInst()->LoadTexture(L"Tile5", L"Texture\\Terrain\\Tile\\Tile5.bmp");
	CTexture* pTile6 = CResMgr::GetInst()->LoadTexture(L"Tile6", L"Texture\\Terrain\\Tile\\Tile6.bmp");

	// 타일 리스트에 삽입
	m_Tilelist.push_back(pTile0);
	m_Tilelist.push_back(pTile1);
	m_Tilelist.push_back(pTile2);
	m_Tilelist.push_back(pTile3);
	m_Tilelist.push_back(pTile4);
	m_Tilelist.push_back(pTile5);
	m_Tilelist.push_back(pTile6);

	


	// 타일 팔레트
	CTileUI* pTileUI0 = new CTileUI;
	pTileUI0->SetPos(Vec2(660.f, 50.f));
	pTileUI0->SetIdleTex(pTile0);
	pTileUI0->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum0);
	pStageUI->AddChildUI(pTileUI0);


	CTileUI* pTileUI1 = new CTileUI;
	pTileUI1->SetPos(Vec2(660.f, 100.f));
	pTileUI1->SetIdleTex(pTile1);
	pTileUI1->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum1);
	pStageUI->AddChildUI(pTileUI1);


	CTileUI* pTileUI2 = new CTileUI;
	pTileUI2->SetPos(Vec2(660.f, 150.f));
	pTileUI2->SetIdleTex(pTile2);
	pTileUI2->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum2);
	pStageUI->AddChildUI(pTileUI2);


	CTileUI* pTileUI3 = new CTileUI;
	pTileUI3->SetPos(Vec2(660.f, 200.f));
	pTileUI3->SetIdleTex(pTile3);
	pTileUI3->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum3);
	pStageUI->AddChildUI(pTileUI3);

	CTileUI* pTileUI4 = new CTileUI;
	pTileUI4->SetPos(Vec2(660.f, 250.f));
	pTileUI4->SetIdleTex(pTile4);
	pTileUI4->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum4);
	pStageUI->AddChildUI(pTileUI4);

	CTileUI* pTileUI5 = new CTileUI;
	pTileUI5->SetPos(Vec2(660.f, 300.f));
	pTileUI5->SetIdleTex(pTile5);
	pTileUI5->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum5);
	pStageUI->AddChildUI(pTileUI5);

	CTileUI* pTileUI6 = new CTileUI;
	pTileUI6->SetPos(Vec2(660.f, 350.f));
	pTileUI6->SetIdleTex(pTile6);
	pTileUI6->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum6);
	pStageUI->AddChildUI(pTileUI6);

	
	// 블록 텍스쳐 로딩
	CTexture* pBox0 = CResMgr::GetInst()->LoadTexture(L"Box0", L"Texture\\Terrain\\Box\\Box0.bmp");
	CTexture* pBox1 = CResMgr::GetInst()->LoadTexture(L"Box1", L"Texture\\Terrain\\Box\\Box1.bmp");
	CTexture* pBox2 = CResMgr::GetInst()->LoadTexture(L"Box2", L"Texture\\Terrain\\Box\\Box2.bmp");
	CTexture* pBox3 = CResMgr::GetInst()->LoadTexture(L"Box3", L"Texture\\Terrain\\Box\\Box3.bmp");
	CTexture* pBox4 = CResMgr::GetInst()->LoadTexture(L"Box4", L"Texture\\Terrain\\Box\\Box4.bmp");
	CTexture* pBox5 = CResMgr::GetInst()->LoadTexture(L"Box5", L"Texture\\Terrain\\Box\\Box5.bmp");
	CTexture* pBox6 = CResMgr::GetInst()->LoadTexture(L"Box6", L"Texture\\Terrain\\Box\\Box6.bmp");
	CTexture* pBox7 = CResMgr::GetInst()->LoadTexture(L"Box7", L"Texture\\Terrain\\Box\\Box7.bmp");
	CTexture* pBox8 = CResMgr::GetInst()->LoadTexture(L"Box8", L"Texture\\Terrain\\Box\\Box8.bmp");
	CTexture* pBox9 = CResMgr::GetInst()->LoadTexture(L"Box9", L"Texture\\Terrain\\Box\\Box9.bmp");
	CTexture* pBox10 = CResMgr::GetInst()->LoadTexture(L"Box10", L"Texture\\Terrain\\Box\\Box10.bmp");
	CTexture* pBox11 = CResMgr::GetInst()->LoadTexture(L"Box11", L"Texture\\Terrain\\Box\\Box11.bmp");
	CTexture* pBox12 = CResMgr::GetInst()->LoadTexture(L"Box12", L"Texture\\Terrain\\Box\\Box12.bmp");
	CTexture* pBox13 = CResMgr::GetInst()->LoadTexture(L"Box13", L"Texture\\Terrain\\Box\\Box13.bmp");
	CTexture* pBox14 = CResMgr::GetInst()->LoadTexture(L"Box14", L"Texture\\Terrain\\Box\\Box14.bmp");
	CTexture* pBox_delete = CResMgr::GetInst()->LoadTexture(L"Box_delete", L"Texture\\Terrain\\Box\\delete.bmp");


	// 박스 리스트에 삽입
	m_Boxlist.push_back(pBox0);
	m_Boxlist.push_back(pBox1);
	m_Boxlist.push_back(pBox2);
	m_Boxlist.push_back(pBox3);
	m_Boxlist.push_back(pBox4);
	m_Boxlist.push_back(pBox5);
	m_Boxlist.push_back(pBox6);
	m_Boxlist.push_back(pBox7);
	m_Boxlist.push_back(pBox8);
	m_Boxlist.push_back(pBox9);
	m_Boxlist.push_back(pBox10);
	m_Boxlist.push_back(pBox11);
	m_Boxlist.push_back(pBox12);
	m_Boxlist.push_back(pBox13);
	m_Boxlist.push_back(pBox14);

}