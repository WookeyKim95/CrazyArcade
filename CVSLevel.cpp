#include "pch.h"
#include "CVSLevel.h"

#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CPathMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTimeMgr.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CPlayer2.h"
#include "CBox_Break.h"
#include "CObstacle.h"
#include "CTile.h"
#include "CStageUI.h"
#include "CGameStart.h"
#include "CWIN.h"
#include "CWaveAni.h"
#include "CItemUI.h"
#include "CItemUI2.h"
#include "CSound.h"
#include "CExitUI.h"

#include "CResMgr.h"
#include "CKeyMgr.h"

CVSLevel::CVSLevel() :
	m_PlayerCount(2),
	m_DurationTime(0.f),
	Started(false),
	PlayerSpawn(false),
	Finished(false),
	BGM(nullptr)
{
}

CVSLevel::~CVSLevel()
{
}


void CVSLevel::init()
{
	// Level 의 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::WAVE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::WAVE_CENTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::BOX_BREAK);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::BOX_NON_BREAK);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::OBSTACLE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::BOMB);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::ITEM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::PLAYER);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::WAVE, LAYER::OBSTACLE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::WAVE, LAYER::BOX_BREAK);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::WAVE, LAYER::BOMB);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::WAVE, LAYER::WAVE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::WAVE, LAYER::ITEM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::WAVE_CENTER, LAYER::ITEM);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::BOMB, LAYER::OBSTACLE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::BOMB, LAYER::BOMB);

	BGM = CResMgr::GetInst()->FindSound(L"Stage_VS");

	BGM->SetPosition(0.f);
	BGM->SetVolume(50.f);
	BGM->PlayToBGM(true);
}

void CVSLevel::tick()
{
	CLevel::tick();

	if (IsTap(KEY::ESC))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}

	m_DurationTime += DT;

	if (!PlayerSpawn)
	{
		// Player 생성
		CPlayer* pObj = new CPlayer;
		pObj->SetPos(Vec2(80.f, 100.f));
		pObj->SetScale(Vec2(40.f, 40.f));
		AddObject(pObj, LAYER::PLAYER);

		CPlayer2* pObj2 = new CPlayer2;
		pObj2->SetPos(Vec2(560.f, 100.f));
		pObj2->SetScale(Vec2(40.f, 40.f));
		AddObject(pObj2, LAYER::PLAYER);

		//Item UI
		CItemUI* pItemUI = new CItemUI((CPlayer*)pObj);
		pItemUI->SetPos(Vec2(240.f, 560.f)); // 670 490
		AddObject(pItemUI, LAYER::UI);

		CItemUI2* pItemUI2 = new CItemUI2((CPlayer2*)pObj2);
		pItemUI2->SetPos(Vec2(280.f, 560.f)); // 725 490
		AddObject(pItemUI2, LAYER::UI);

		PlayerSpawn = true;
	}

	if (!Started && m_DurationTime > START_TIME)
	{

		init();
		Started = true;
	}

	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}


	if (Finished && m_DurationTime > START_TIME)
	{
		ChangeLevel(LEVEL_TYPE::START);
	}
}

void CVSLevel::Enter()
{
	CTexture* pGameStartTex = CResMgr::GetInst()->LoadTexture(L"GameStart", L"Texture\\UI\\GameStart.bmp");

	CGameStart* pStartUI = new CGameStart;
	pStartUI->SetIdleTex(pGameStartTex);
	pStartUI->SetPos(Vec2(260.f, 260.f));
	AddObject(pStartUI, LAYER::UI_UP);


	CTexture* pStageUITex = CResMgr::GetInst()->LoadTexture(L"Stage01", L"Texture\\Stage\\Stage1.bmp");
	// Panel UI
	CStageUI* pStageUI = new CStageUI;
	pStageUI->SetIdleTex(pStageUITex);
	pStageUI->SetPos(Vec2(0.f, 0.f));
	AddObject(pStageUI, LAYER::UI);

	CExitUI* pExit = new CExitUI;
	pExit->SetScale(Vec2(135.f, 25.f));
	pExit->SetPos(Vec2(650.f, 565.f));
	pStageUI->AddChildUI(pExit);

	LoadTile();
}

void CVSLevel::Exit()
{
	DeleteAllObject();

	m_PlayerCount = 2;
	m_DurationTime = 0.f;
	Started = false;
	PlayerSpawn = false;
	Finished = false;

	if (BGM != nullptr)
		BGM->Stop();
}

void CVSLevel::LoadTile()
{
	wstring strTilePath = CPathMgr::GetInst()->GetContentPath();
	strTilePath += L"tile\\stageVS.tile";

	// 파일 입출력
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strTilePath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"FileOpen 실패, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"파일 로드 실패", MB_OK);
		return;
	}

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

	// 각각의 장애물여부 정보 저장
	const vector<CObj*>& vecObstacle = GetLayer(LAYER::OBSTACLE);
	for (size_t i = 0; i < vecObstacle.size(); ++i)
	{
		((CObstacle*)vecObstacle[i])->Load(pFile);
	}

	fclose(pFile);
}

