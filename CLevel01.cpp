#include "pch.h"
#include "CLevel01.h"

#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CPathMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTimeMgr.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CBox_Break.h"
#include "CObstacle.h"
#include "CTile.h"
#include "CStageUI.h"
#include "CGameStart.h"
#include "CWIN.h"
#include "CWaveAni.h"
#include "CItemUI.h"
#include "CElli.h"
#include "CMiniBallOne.h"
#include "CMiniBallTwo.h"
#include "COrange.h"
#include "CSeal.h"
#include "CSound.h"
#include "CExitUI.h"

#include "CResMgr.h"
#include "CKeyMgr.h"


CLevel01::CLevel01():
	m_MonsterCount(0),
	m_DurationTime(0.f),
	Started(false),
	PlayerSpawn(false),
	Finished(false)
{
}

CLevel01::~CLevel01()
{
}

void CLevel01::init()
{
	// 애니메이션 로딩

	// 플레이어
	CTexture* pWalk_Down = CResMgr::GetInst()->LoadTexture(L"PWD", L"Texture\\Player\\Walk_Down.bmp");
	CTexture* pWalk_Left = CResMgr::GetInst()->LoadTexture(L"PWL", L"Texture\\Player\\Walk_Left.bmp");
	CTexture* pWalk_Up = CResMgr::GetInst()->LoadTexture(L"PWU", L"Texture\\Player\\Walk_Up.bmp");
	CTexture* pWalk_Right = CResMgr::GetInst()->LoadTexture(L"PWR", L"Texture\\Player\\Walk_Right.bmp");

	CTexture* pIdle_Down = CResMgr::GetInst()->LoadTexture(L"PID", L"Texture\\Player\\Idle_Down.bmp");
	CTexture* pIdle_Up = CResMgr::GetInst()->LoadTexture(L"PIU", L"Texture\\Player\\Idle_Up.bmp");
	CTexture* pIdle_Left = CResMgr::GetInst()->LoadTexture(L"PIL", L"Texture\\Player\\Idle_Left.bmp");
	CTexture* pIdle_Right = CResMgr::GetInst()->LoadTexture(L"PIR", L"Texture\\Player\\Idle_Right.bmp");

	CTexture* pTrapped = CResMgr::GetInst()->LoadTexture(L"PTR", L"Texture\\Player\\Trapped.bmp");
	CTexture* pRevival = CResMgr::GetInst()->LoadTexture(L"PREVIVE", L"Texture\\Player\\Revival.bmp");
	CTexture* pDead = CResMgr::GetInst()->LoadTexture(L"PDEAD", L"Texture\\Player\\Dead.bmp");



	// 몬스터(엘리)
	CTexture* eWalk_Down = CResMgr::GetInst()->LoadTexture(L"EWD", L"Texture\\Monster\\Elli\\Elli_Down.bmp");
	CTexture* eWalk_Left = CResMgr::GetInst()->LoadTexture(L"EWL", L"Texture\\Monster\\Elli\\Elli_Left.bmp");
	CTexture* eWalk_Up = CResMgr::GetInst()->LoadTexture(L"EWU", L"Texture\\Monster\\Elli\\Elli_Up.bmp");
	CTexture* eWalk_Right = CResMgr::GetInst()->LoadTexture(L"EWR", L"Texture\\Monster\\Elli\\Elli_Right.bmp");

	CTexture* eTrap_Down = CResMgr::GetInst()->LoadTexture(L"ETD", L"Texture\\Monster\\Elli\\ElliTrapped_Down.bmp");
	CTexture* eTrap_Up = CResMgr::GetInst()->LoadTexture(L"ETU", L"Texture\\Monster\\Elli\\ElliTrapped_Up.bmp");
	CTexture* eTrap_Left = CResMgr::GetInst()->LoadTexture(L"ETL", L"Texture\\Monster\\Elli\\ElliTrapped_Left.bmp");
	CTexture* eTrap_Right = CResMgr::GetInst()->LoadTexture(L"ETR", L"Texture\\Monster\\Elli\\ElliTrapped_Right.bmp");

	CTexture* eDead = CResMgr::GetInst()->LoadTexture(L"EDEAD", L"Texture\\Monster\\Elli\\Elli_Dead.bmp");

	
	// 몬스터(미니볼들)

	CTexture* m1Walk_Down = CResMgr::GetInst()->LoadTexture(L"M1WD", L"Texture\\Monster\\Monster_1\\Monster_Down.bmp");
	CTexture* m1Walk_Left = CResMgr::GetInst()->LoadTexture(L"M1WL", L"Texture\\Monster\\Monster_1\\Monster_Left.bmp");
	CTexture* m1Walk_Up = CResMgr::GetInst()->LoadTexture(L"M1WU", L"Texture\\Monster\\Monster_1\\Monster_Up.bmp");
	CTexture* m1Walk_Right = CResMgr::GetInst()->LoadTexture(L"M1WR", L"Texture\\Monster\\Monster_1\\Monster_Right.bmp");
	CTexture* m1_Dead = CResMgr::GetInst()->LoadTexture(L"M1DEAD", L"Texture\\Monster\\Monster_1\\Monster_Dead.bmp");

	CTexture* m2Walk_Down = CResMgr::GetInst()->LoadTexture(L"M2WD", L"Texture\\Monster\\Monster_2\\Monster2_Down.bmp");
	CTexture* m2Walk_Left = CResMgr::GetInst()->LoadTexture(L"M2WL", L"Texture\\Monster\\Monster_2\\Monster2_Left.bmp");
	CTexture* m2Walk_Up = CResMgr::GetInst()->LoadTexture(L"M2WU", L"Texture\\Monster\\Monster_2\\Monster2_Up.bmp");
	CTexture* m2Walk_Right = CResMgr::GetInst()->LoadTexture(L"M2WR", L"Texture\\Monster\\Monster_2\\Monster2_Right.bmp");
	CTexture* m2_Dead = CResMgr::GetInst()->LoadTexture(L"M2DEAD", L"Texture\\Monster\\Monster_2\\Monster2_Dead.bmp");

	CTexture* Orange_Down = CResMgr::GetInst()->LoadTexture(L"ORWD", L"Texture\\Monster\\Orange\\Orange_Down.bmp");
	CTexture* Orange_Left = CResMgr::GetInst()->LoadTexture(L"ORWL", L"Texture\\Monster\\Orange\\Orange_Left.bmp");
	CTexture* Orange_Up = CResMgr::GetInst()->LoadTexture(L"ORWU", L"Texture\\Monster\\Orange\\Orange_Up.bmp");
	CTexture* Orange_Right = CResMgr::GetInst()->LoadTexture(L"ORWR", L"Texture\\Monster\\Orange\\Orange_Right.bmp");
	CTexture* Orange_Dead = CResMgr::GetInst()->LoadTexture(L"ORDEAD", L"Texture\\Monster\\Orange\\Orange_Dead.bmp");







	// Monster 생성
	//CElli* pElli = new CElli;
	//pElli->SetPos(Vec2(480.f, 300.f));
	//pElli->SetScale(Vec2(40.f, 40.f));
	//AddObject(pElli, LAYER::MONSTER);
	//m_MonsterCount++;

	//CElli* pElli2 = pElli->Clone();
	//pElli2->SetPos(Vec2(40.f, 500.f));
	//pElli2->SetScale(Vec2(40.f, 40.f));
	//AddObject(pElli2, LAYER::MONSTER);
	//m_MonsterCount++;

	// Monster 생성
	CMiniBallOne* pMBOne1 = new CMiniBallOne;
	pMBOne1->SetPos(Vec2(480.f, 500.f));
	pMBOne1->SetScale(Vec2(40.f, 40.f));
	AddObject(pMBOne1, LAYER::MONSTER);
	m_MonsterCount++;

	CMiniBallOne* pMBOne2 = pMBOne1->Clone();
	pMBOne2->SetPos(Vec2(80.f, 500.f));
	pMBOne2->SetScale(Vec2(40.f, 40.f));
	AddObject(pMBOne2, LAYER::MONSTER);
	m_MonsterCount++;

	CMiniBallOne* pMBOne3 = pMBOne1->Clone();
	pMBOne3->SetPos(Vec2(80.f, 120.f));
	pMBOne3->SetScale(Vec2(40.f, 40.f));
	AddObject(pMBOne3, LAYER::MONSTER);
	m_MonsterCount++;

	CMiniBallOne* pMBOne4 = pMBOne1->Clone();
	pMBOne4->SetPos(Vec2(560.f, 100.f));
	pMBOne4->SetScale(Vec2(40.f, 40.f));
	AddObject(pMBOne4, LAYER::MONSTER);
	m_MonsterCount++;

	CMiniBallTwo* pMBTwo1 = new CMiniBallTwo;
	pMBTwo1->SetPos(Vec2(500.f, 520.f));
	pMBTwo1->SetScale(Vec2(40.f, 40.f));
	AddObject(pMBTwo1, LAYER::MONSTER);
	m_MonsterCount++;

	CMiniBallTwo* pMBTwo2 = pMBTwo1->Clone();
	pMBTwo2->SetPos(Vec2(80.f, 520.f));
	pMBTwo2->SetScale(Vec2(40.f, 40.f));
	AddObject(pMBTwo2, LAYER::MONSTER);
	m_MonsterCount++;

	CMiniBallTwo* pMBTwo3 = pMBTwo1->Clone();
	pMBTwo3->SetPos(Vec2(80.f, 100.f));
	pMBTwo3->SetScale(Vec2(40.f, 40.f));
	AddObject(pMBTwo3, LAYER::MONSTER);
	m_MonsterCount++;

	CMiniBallTwo* pMBTwo4 = pMBTwo1->Clone();
	pMBTwo4->SetPos(Vec2(560.f, 100.f));
	pMBTwo4->SetScale(Vec2(40.f, 40.f));
	AddObject(pMBTwo4, LAYER::MONSTER);
	m_MonsterCount++;

	//COrange* pOrange1 = new COrange;
	//pOrange1->SetPos(Vec2(40.f, 500.f));
	//pOrange1->SetScale(Vec2(40.f, 40.f));
	//AddObject(pOrange1, LAYER::MONSTER);
	//m_MonsterCount++;

	//COrange* pOrange2 = pOrange1->Clone();
	//pOrange2->SetPos(Vec2(480.f, 300.f));
	//pOrange2->SetScale(Vec2(40.f, 40.f));
	//AddObject(pOrange2, LAYER::MONSTER);
	//m_MonsterCount++;

	//CSeal* pSeal = new CSeal;
	//pSeal->SetPos(Vec2(310.f, 260.f));
	//pSeal->SetScale(Vec2(100.f, 100.f));
	//AddObject(pSeal, LAYER::MONSTER);
	//m_MonsterCount++;



	// Level 의 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::WAVE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::WAVE_CENTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::BOX_BREAK);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::BOX_NON_BREAK);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::OBSTACLE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::BOMB);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::ITEM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_OBJECTILE);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::WAVE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::WAVE_CENTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::BOX_BREAK);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::BOX_NON_BREAK);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::OBSTACLE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::BOMB);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::WAVE, LAYER::OBSTACLE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::WAVE, LAYER::BOX_BREAK);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::WAVE, LAYER::BOMB);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::WAVE, LAYER::WAVE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::WAVE, LAYER::ITEM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::WAVE_CENTER, LAYER::ITEM);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::BOMB, LAYER::OBSTACLE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::BOMB, LAYER::BOMB);

	BGM = CResMgr::GetInst()->FindSound(L"Stage_Patriot");

	BGM->SetPosition(0.f);
	BGM->SetVolume(50.f);
	BGM->PlayToBGM(true);

}

void CLevel01::tick()
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
		CObj* pObj = new CPlayer;
		pObj->SetPos(Vec2(320.f, 140.f));
		pObj->SetScale(Vec2(40.f, 40.f));
		AddObject(pObj, LAYER::PLAYER);

		//Item UI
		CItemUI* pItemUI = new CItemUI((CPlayer*)pObj);
		pItemUI->SetPos(Vec2(670.f, 490.f));
		AddObject(pItemUI, LAYER::UI);

		PlayerSpawn = true;
	}

	if (!Started && m_DurationTime > START_TIME)
	{

		init();
		Started = true;
	}

	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::LEVEL_02);
	}

	if (m_MonsterCount == 0 && !Finished && Started)
	{
		m_DurationTime = 0;
		Finished = true;

		// WIN 문구 출력
		CTexture* pWinTex = CResMgr::GetInst()->LoadTexture(L"Win", L"Texture\\UI\\Win.bmp");

		CWIN* pWin = new CWIN;
		pWin->SetIdleTex(pWinTex);
		pWin->SetPos(Vec2(260.f, 260.f));
		AddObject(pWin, LAYER::UI_UP);

		CSound* Win_Sound = CResMgr::GetInst()->FindSound(L"Win");
		Win_Sound->Play(false);

		BGM->Stop();

	}

	if (Finished && m_DurationTime > START_TIME)
	{
		ChangeLevel(LEVEL_TYPE::LEVEL_02);
	}

}

void CLevel01::Enter()
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
	pExit->SetPos(Vec2(650.f, 565.f));
	pExit->SetScale(Vec2(135.f, 25.f));
	pStageUI->AddChildUI(pExit);

	LoadTile();

}

void CLevel01::Exit()
{
	DeleteAllObject();
	
	m_MonsterCount = 0;
	m_DurationTime = 0.f;
	Started = false;
	PlayerSpawn = false;
	Finished = false;

	if (BGM != nullptr)
		BGM->Stop();

}

void CLevel01::LoadTile()
{
	wstring strTilePath = CPathMgr::GetInst()->GetContentPath();
	strTilePath += L"tile\\stage1.tile";

	// 파일 입출력
	FILE* pFile = nullptr;
	errno_t iErrNum = _wfopen_s(&pFile, strTilePath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		wchar_t szStr[256] = {};
		wsprintf(szStr, L"FileOpen 실패, Error Number : %d", iErrNum);
		MessageBox(nullptr, szStr, L"파일 저장 실패", MB_OK);
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