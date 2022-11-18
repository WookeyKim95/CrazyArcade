#include "pch.h"
#include "CP2DeadState.h"

#include "CPlayer2.h"
#include "CAnimator.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CGameOver.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLevel01.h"
#include "CLevel02.h"
#include "CLevel03.h"
#include "CSound.h"

CP2DeadState::CP2DeadState() :
	m_DurationTime(0.f),
	m_Lost(false)
{
}

CP2DeadState::~CP2DeadState()
{
}

void CP2DeadState::finaltick()
{

	CPlayer2* pPlayer = dynamic_cast<CPlayer2*>(GetOwnerPlayer());
	assert(pPlayer);

	m_DurationTime += DT;

	if (!m_Lost)
	{
		// GAMEOVER 문구 출력
		CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"GameOver", L"Texture\\UI\\GameOver.bmp");

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		CGameOver* pOver = new CGameOver;
		pOver->SetIdleTex(pTex);
		pOver->SetPos(Vec2(260.f, 260.f));
		pCurLevel->AddObject(pOver, LAYER::UI_UP);
		m_Lost = true;


		CSound* pSOver = CResMgr::GetInst()->FindSound(L"Win");
		pSOver->Play();

		pCurLevel->GetBGM()->Stop();

	}

	if (m_DurationTime > 4.f)
	{
		m_DurationTime = 0;

		ChangeLevel(LEVEL_TYPE::START);
	}
}

void CP2DeadState::Enter()
{
	CPlayer2* pPlayer = dynamic_cast<CPlayer2*>(GetOwnerPlayer());
	assert(pPlayer);

	pPlayer->GetAnimator()->Play(L"DEAD", false);
}

void CP2DeadState::Exit()
{
}


