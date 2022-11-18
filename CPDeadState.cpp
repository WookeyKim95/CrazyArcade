#include "pch.h"
#include "CPDeadState.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CLOSE.h"
#include "CGameOver.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLevel01.h"
#include "CLevel02.h"
#include "CLevel03.h"
#include "CSound.h"
#include "CVSLevel.h"

CPDeadState::CPDeadState() :
	m_DurationTime(0.f),
	m_Lost(false)
{
}

CPDeadState::~CPDeadState()
{
}

void CPDeadState::finaltick()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerPlayer());
	assert(pPlayer);

	m_DurationTime += DT;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	if ((dynamic_cast<CVSLevel*>(pCurLevel)) == nullptr)
	{
		if (pPlayer->m_Life == 0 && !m_Lost)
		{
			// LOSE 문구 출력
			CTexture* pWinTex = CResMgr::GetInst()->LoadTexture(L"Win", L"Texture\\UI\\Lose.bmp");

			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

			CLOSE* pLose = new CLOSE;
			pLose->SetIdleTex(pWinTex);
			pLose->SetPos(Vec2(260.f, 260.f));
			pCurLevel->AddObject(pLose, LAYER::UI_UP);
			m_Lost = true;


			CSound* pSLose = CResMgr::GetInst()->FindSound(L"Lose1");
			pSLose->Play();

			pSLose = CResMgr::GetInst()->FindSound(L"Lose2");
			pSLose->Play();

			pCurLevel->GetBGM()->Stop();

		}

		if (m_DurationTime > 4.f)
		{
			m_DurationTime = 0;

			if (pPlayer->m_Life > 0)
			{
				pPlayer->ChangeState(L"Ready");
				pPlayer->m_Life -= 1;
			}

			else
			{
				ChangeLevel(LEVEL_TYPE::START);
			}

		}
	}

	else
	{
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
	
}

void CPDeadState::Enter()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerPlayer());
	assert(pPlayer);

	pPlayer->GetAnimator()->Play(L"DEAD", false);

}

void CPDeadState::Exit()
{
}


