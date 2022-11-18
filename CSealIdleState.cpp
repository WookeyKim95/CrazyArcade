#include "pch.h"
#include "CSealIdleState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CMonsterAI.h"
#include "CSeal.h"

CSealIdleState::CSealIdleState() :
	m_fSpeed(100.f)
{
}

CSealIdleState::~CSealIdleState()
{
}

void CSealIdleState::finaltick()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	Vec2 vPos = pMonster->GetPos();
	pMonster->SetPrevPos(vPos);

	// 상하좌우로 움직이기

	if (Vec2(abs(pMonster->GetPos().x - 520.f), abs(pMonster->GetPos().y - 300.f)) <= Vec2(0.5f, 0.5f))
	{
		int dice = rand() % 10;

		if (dice == 1)
		{
			pMonster->SetPos(pMonster->GetPrevPos());
			pMonster->GetMonsterAI()->ChangeState(L"Seal_AtkThrL");
		}

	}

	if (Vec2(abs(pMonster->GetPos().x - 140.f), abs(pMonster->GetPos().y - 300.f)) <= Vec2(0.5f, 0.5f))
	{
		int dice = rand() % 10;

		if (dice == 2)
		{
			pMonster->SetPos(pMonster->GetPrevPos());
			pMonster->GetMonsterAI()->ChangeState(L"Seal_AtkThrR");
		}

	}

	if (pMonster->GetDir() == 0 && pMonster->GetPos().y > 160.f)
	{
		vPos.y -= m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"SEAL_WALK_UP", true);
			pMonster->m_bTurned = true;
		}

	}

	if (pMonster->GetDir() == 1 && pMonster->GetPos().y < 440.f)
	{
		vPos.y += m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"SEAL_WALK_DOWN", true);
			pMonster->m_bTurned = true;
		}

	}

	if (pMonster->GetDir() == 2 && pMonster->GetPos().x > 140.f)
	{
		vPos.x -= m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"SEAL_WALK_LEFT", true);
			pMonster->m_bTurned = true;
		}

	}

	if (pMonster->GetDir() == 3 && pMonster->GetPos().x < 520.f)
	{
		vPos.x += m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"SEAL_WALK_RIGHT", true);
			pMonster->m_bTurned = true;
		}
	}

	if (vPos.x <= 140.f || vPos.x >= 520.f || vPos.y >= 440.f || vPos.y <= 160.f)
	{
		pMonster->SetPos(pMonster->GetPrevPos());
		pMonster->SetDir(rand() % 4);
		pMonster->m_bTurned = false;
	}

	m_DurationTime += DT;
	if (m_DurationTime > 15.f)
	{
		m_DurationTime = 0;

		int dice = rand() % 2;

		if (dice == 0)
		{
			GetOwnerMonsterAI()->ChangeState(L"Seal_AtkOne");
		}

		else if (dice == 1)
		{
			GetOwnerMonsterAI()->ChangeState(L"Seal_AtkTwo");
		}

	}



}

void CSealIdleState::Enter()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	pMonster->GetAnimator()->Play(L"SEAL_IDLE", true);

	if (pMonster->m_dir == 0)
	{
		pMonster->GetAnimator()->Play(L"SEAL_WALK_UP", true);
	}

	else if (pMonster->m_dir == 1)
	{
		pMonster->GetAnimator()->Play(L"SEAL_WALK_DOWN", true);
	}

	else if (pMonster->m_dir == 2)
	{
		pMonster->GetAnimator()->Play(L"SEAL_WALK_LEFT", true);
	}

	else if (pMonster->m_dir == 3)
	{
		pMonster->GetAnimator()->Play(L"SEAL_WALK_RIGHT", true);
	}

}

void CSealIdleState::Exit()
{
}


