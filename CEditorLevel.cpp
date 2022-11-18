#include "pch.h"
#include "CEditorLevel.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEngine.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CBox_Break.h"
#include "CTile.h"
#include "CObstacle.h"

#include "CUI.h"
#include "CTileUI.h"
#include "CBoxUI.h"
#include "CStageUI.h"

#include "resource.h"


CEditorLevel::CEditorLevel()
	: m_hMenu(nullptr)
	, m_eMode(EDITOR_MODE::TILE)
	, m_AtlasNum(2)
	, m_Tilelist{}
	, m_Boxlist{}
	, m_curPalette(0)
{
}

CEditorLevel::~CEditorLevel()
{
	if (m_hMenu != nullptr)
		DestroyMenu(m_hMenu);
}


void CEditorLevel::tick()
{
	CLevel::tick();

	if (IsTap(KEY::ESC))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}

	if (IsTap(KEY::_1))
	{	
		// 이전 UI 지우고 새로 그리기

		DeleteObject(LAYER::UI);

		CTexture* pStageUITex = CResMgr::GetInst()->LoadTexture(L"Stage", L"Texture\\UI\\mapToolMap.bmp");

		CTexture* pInfo = CResMgr::GetInst()->LoadTexture(L"ButtonInfo", L"Texture\\UI\\KeyInfo.bmp");
		CTexture* pSave = CResMgr::GetInst()->LoadTexture(L"SaveButton", L"Texture\\UI\\Save.bmp");
		CTexture* pLoad = CResMgr::GetInst()->LoadTexture(L"LoadButton", L"Texture\\UI\\Load.bmp");

		CStageUI* pStageUI = new CStageUI;
		pStageUI->SetIdleTex(pStageUITex);
		pStageUI->SetPos({ 0.f,0.f });
		AddObject(pStageUI, LAYER::UI);

		CTileUI* But_Info = new CTileUI;
		But_Info->SetIdleTex(pInfo);
		But_Info->SetPos({ 400.f, 0.f });
		pStageUI->AddChildUI(But_Info);

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

		// 타일 텍스쳐 로딩
		CTexture* pTile0 = CResMgr::GetInst()->LoadTexture(L"Tile0", L"Texture\\Terrain\\Tile\\Tile0.bmp");
		CTexture* pTile1 = CResMgr::GetInst()->LoadTexture(L"Tile1", L"Texture\\Terrain\\Tile\\Tile1.bmp");
		CTexture* pTile2 = CResMgr::GetInst()->LoadTexture(L"Tile2", L"Texture\\Terrain\\Tile\\Tile2.bmp");
		CTexture* pTile3 = CResMgr::GetInst()->LoadTexture(L"Tile3", L"Texture\\Terrain\\Tile\\Tile3.bmp");
		CTexture* pTile4 = CResMgr::GetInst()->LoadTexture(L"Tile4", L"Texture\\Terrain\\Tile\\Tile4.bmp");
		CTexture* pTile5 = CResMgr::GetInst()->LoadTexture(L"Tile5", L"Texture\\Terrain\\Tile\\Tile5.bmp");
		CTexture* pTile6 = CResMgr::GetInst()->LoadTexture(L"Tile6", L"Texture\\Terrain\\Tile\\Tile6.bmp");


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

		m_eMode = EDITOR_MODE::TILE;
		// 팔레트 설정
		m_curPalette = 0;
		tile_update();
	}

	if (IsTap(KEY::_2))
	{
		//이전 UI 지우기
		DeleteObject(LAYER::UI);

		CTexture* pStageUITex = CResMgr::GetInst()->LoadTexture(L"Stage", L"Texture\\UI\\mapToolMap.bmp");

		CTexture* pSave = CResMgr::GetInst()->LoadTexture(L"SaveButton", L"Texture\\UI\\Save.bmp");
		CTexture* pLoad = CResMgr::GetInst()->LoadTexture(L"LoadButton", L"Texture\\UI\\Load.bmp");
		CTexture* pInfo = CResMgr::GetInst()->LoadTexture(L"ButtonInfo", L"Texture\\UI\\KeyInfo.bmp");

		CStageUI* pStageUI = new CStageUI;
		pStageUI->SetIdleTex(pStageUITex);
		pStageUI->SetPos({ 0.f,0.f });
		AddObject(pStageUI, LAYER::UI);

		CTileUI* But_Info = new CTileUI;
		But_Info->SetIdleTex(pInfo);
		But_Info->SetPos({ 400.f, 0.f });
		pStageUI->AddChildUI(But_Info);

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
		CTexture* pBox_delete = CResMgr::GetInst()->LoadTexture(L"Box_delete", L"Texture\\Terrain\\Box\\delete.bmp");

		// 박스 팔레트
		CBoxUI* pBoxUI0 = new CBoxUI;
		pBoxUI0->SetPos(Vec2(660.f, 50.f));
		pBoxUI0->SetIdleTex(pBox0);
		pBoxUI0->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum0);
		pStageUI->AddChildUI(pBoxUI0);

		CBoxUI* pBoxUI1 = new CBoxUI;
		pBoxUI1->SetPos(Vec2(660.f, 100.f));
		pBoxUI1->SetIdleTex(pBox1);
		pBoxUI1->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum1);
		pStageUI->AddChildUI(pBoxUI1);

		CBoxUI* pBoxUI2 = new CBoxUI;
		pBoxUI2->SetPos(Vec2(660.f, 150.f));
		pBoxUI2->SetIdleTex(pBox2);
		pBoxUI2->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum2);
		pStageUI->AddChildUI(pBoxUI2);

		CBoxUI* pBoxUI3 = new CBoxUI;
		pBoxUI3->SetPos(Vec2(660.f, 200.f));
		pBoxUI3->SetIdleTex(pBox3);
		pBoxUI3->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum3);
		pStageUI->AddChildUI(pBoxUI3);

		CBoxUI* pBoxUI4 = new CBoxUI;
		pBoxUI4->SetPos(Vec2(660.f, 250.f));
		pBoxUI4->SetIdleTex(pBox4);
		pBoxUI4->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum4);
		pStageUI->AddChildUI(pBoxUI4);

		CBoxUI* pBoxUI5 = new CBoxUI;
		pBoxUI5->SetPos(Vec2(660.f, 300.f));
		pBoxUI5->SetIdleTex(pBox5);
		pBoxUI5->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum5);
		pStageUI->AddChildUI(pBoxUI5);

		CBoxUI* pBoxUI6 = new CBoxUI;
		pBoxUI6->SetPos(Vec2(660.f, 350.f));
		pBoxUI6->SetIdleTex(pBox6);
		pBoxUI6->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum6);
		pStageUI->AddChildUI(pBoxUI6);

		CBoxUI* pBoxUI7 = new CBoxUI;
		pBoxUI7->SetPos(Vec2(710.f, 50.f));
		pBoxUI7->SetIdleTex(pBox7);
		pBoxUI7->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum7);
		pStageUI->AddChildUI(pBoxUI7);

		CBoxUI* pBoxUI8 = new CBoxUI;
		pBoxUI8->SetPos(Vec2(710.f, 100.f));
		pBoxUI8->SetIdleTex(pBox8);
		pBoxUI8->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum8);
		pStageUI->AddChildUI(pBoxUI8);

		CBoxUI* pBoxUI9 = new CBoxUI;
		pBoxUI9->SetPos(Vec2(710.f, 150.f));
		pBoxUI9->SetIdleTex(pBox9);
		pBoxUI9->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum9);
		pStageUI->AddChildUI(pBoxUI9);

		CBoxUI* pBoxUI10 = new CBoxUI;
		pBoxUI10->SetPos(Vec2(710.f, 200.f));
		pBoxUI10->SetIdleTex(pBox10);
		pBoxUI10->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum10);
		pStageUI->AddChildUI(pBoxUI10);

		CBoxUI* pBoxUI11 = new CBoxUI;
		pBoxUI11->SetPos(Vec2(710.f, 250.f));
		pBoxUI11->SetIdleTex(pBox11);
		pBoxUI11->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum11);
		pStageUI->AddChildUI(pBoxUI11);

		CBoxUI* pBoxUI12 = new CBoxUI;
		pBoxUI12->SetPos(Vec2(710.f, 300.f));
		pBoxUI12->SetIdleTex(pBox12);
		pBoxUI12->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum12);
		pStageUI->AddChildUI(pBoxUI12);

		CBoxUI* pBoxUI13 = new CBoxUI;
		pBoxUI13->SetPos(Vec2(710.f, 350.f));
		pBoxUI13->SetIdleTex(pBox13);
		pBoxUI13->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum13);
		pStageUI->AddChildUI(pBoxUI13);

		CBoxUI* pBoxUI15 = new CBoxUI;
		pBoxUI15->SetPos(Vec2(685.f, 400.f));
		pBoxUI15->SetIdleTex(pBox_delete);
		pBoxUI15->SetDelegate(this, (DELEGATE)&CEditorLevel::SetAtlasNum15);
		pStageUI->AddChildUI(pBoxUI15);

		m_eMode = EDITOR_MODE::BOX;
		// 팔레트 설정
		m_curPalette = 1;
		Box_update();
	}

	if (IsTap(KEY::_0))
	{
		m_eMode = EDITOR_MODE::NONE;
		m_curPalette = 2;
	}


	update();
}


void CEditorLevel::Enter()
{

	// 초기 오브젝트 설정
	init();
}

void CEditorLevel::Exit()
{
	// 메뉴바 제거
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);

	// 메인 윈도우 크기 재조정
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
}

void CEditorLevel::update()
{
	switch (m_eMode)
	{
	case EDITOR_MODE::TILE:
	{

		tile_update();
		break;
	}

	case EDITOR_MODE::BOX:
	{
		Box_update();
		break;
	}

	case EDITOR_MODE::NONE:
		return;
	}
}

void CEditorLevel::tile_update()
{
	if (IsPressed(KEY::LBTN))
	{
		// 범위 내에서 마우스 좌클릭을 실행하였을 경우
		// 마우스 위치를 받아와서 실제좌표로 변환	
		Vec2 vMousePos = MOUSE_POS;

		int iCol = (int)(vMousePos.x - 20.f) / TILE_SIZE;
		int iRow = (int)(vMousePos.y - 40.f) / TILE_SIZE;

		if (0.f <= vMousePos.x && iCol < GetTileXCount()
			&& 0.f <= vMousePos.y && iRow < GetTileYCount())
		{
			int iIdx = iRow * GetTileXCount() + iCol;
			const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
			((CTile*)vecTile[iIdx])->SetAtlas(m_Tilelist[m_AtlasNum]);

			// 박스가 있는지 여부를 조사하기 위함.
			const vector<CObj*>& vecBox = GetLayer(LAYER::BOX_BREAK);

			// 장애물 설치여부 바꾸기 위함.
			const vector<CObj*>& vecObstacle = GetLayer(LAYER::OBSTACLE);

			if (((CBox_Break*)vecBox[iIdx])->GetAtlas() == nullptr)
			{
				((CObstacle*)vecObstacle[iIdx])->SetObstacle(false);
				((CObstacle*)vecObstacle[iIdx])->SetAbsObstacle(false);
			}

			// 3번 타일 텍스쳐가 장애물임.
			if (m_AtlasNum == 3)
			{
				((CObstacle*)vecObstacle[iIdx])->SetAbsObstacle(true);
				((CObstacle*)vecObstacle[iIdx])->SetObstacle(true);
			}

		}
	}
}

void CEditorLevel::Box_update()
{
	if (IsPressed(KEY::LBTN))
	{
		// 범위 내에서 마우스 좌클릭을 실행하였을 경우
		// 마우스 위치를 받아와서 실제좌표로 변환	
		Vec2 vMousePos = MOUSE_POS;

		int iCol = (int)(vMousePos.x - 20.f) / TILE_SIZE;
		int iRow = (int)(vMousePos.y - 40.f) / TILE_SIZE;

		if (0.f <= vMousePos.x && iCol < GetTileXCount()
			&& 0.f <= vMousePos.y && iRow < GetTileYCount())
		{
			int iIdx = iRow * GetTileXCount() + iCol;
			const vector<CObj*>& vecBox = GetLayer(LAYER::BOX_BREAK);

			const vector<CObj*>& vecObstacle = GetLayer(LAYER::OBSTACLE);
			

			if (m_AtlasNum == 15) // 텍스쳐 삭제
			{
				((CBox_Break*)vecBox[iIdx])->SetAtlas(nullptr);
				((CObstacle*)vecObstacle[iIdx])->SetObstacle(false);
				((CObstacle*)vecObstacle[iIdx])->SetAbsObstacle(false);
			}


			else
			{
				((CBox_Break*)vecBox[iIdx])->SetAtlas(m_Boxlist[m_AtlasNum]);
				((CObstacle*)vecObstacle[iIdx])->SetObstacle(true);

			}

		}
	}
}

void CEditorLevel::SaveTile()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"tile\\";


	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileName(&ofn) == false)
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");

	// 타일 가로 세로 개수 저장 (15개, 13개)
	int iTileXCount = 15; 
	int iTileYCount = 13;

	fwrite(&iTileXCount, sizeof(UINT), 1, pFile);
	fwrite(&iTileYCount, sizeof(UINT), 1, pFile);



	// 각각의 타일 정보 저장
	const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	// 각각의 박스(파괴가능) 정보 저장
	const vector<CObj*>& vecBox = GetLayer(LAYER::BOX_BREAK);
	for (size_t i = 0; i < vecBox.size(); ++i)
	{
		((CBox_Break*)vecBox[i])->Save(pFile);
	}

	// 각각의 장애물여부 정보 저장
	const vector<CObj*>& vecObstacle = GetLayer(LAYER::OBSTACLE);
	for (size_t i = 0; i < vecObstacle.size(); ++i)
	{
		((CObstacle*)vecObstacle[i])->Save(pFile);
	}

	fclose(pFile);
}

void CEditorLevel::LoadTile()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"tile\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == false)
		return;


	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");

	// 타일 개로 세로 개수 읽기
	UINT iTileXCount = 0, iTileYCount = 0;

	fread(&iTileXCount, sizeof(UINT), 1, pFile);
	fread(&iTileYCount, sizeof(UINT), 1, pFile);

	// 읽은 개수에 맞게 다시 타일 배치
	CreateTile(iTileXCount, iTileYCount);
	CreateBox(iTileXCount, iTileYCount);
	CreateObstacle(iTileXCount, iTileYCount);

	// 배치한 각각의 타일들을 데이터 읽도록
	const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	// 각각의 박스(파괴가능) 정보 로드
	const vector<CObj*>& vecBox = GetLayer(LAYER::BOX_BREAK);
	for (size_t i = 0; i < vecBox.size(); ++i)
	{
		((CBox_Break*)vecBox[i])->Load(pFile);
	}

	// 각각의 장애물여부 정보 로드
	const vector<CObj*>& vecObstacle = GetLayer(LAYER::OBSTACLE);
	for (size_t i = 0; i < vecObstacle.size(); ++i)
	{
		((CObstacle*)vecObstacle[i])->Load(pFile);
	}

	fclose(pFile);
}



