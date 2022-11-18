#include "pch.h"
#include "CElliIdleState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CMonsterAI.h"
#include "CElli.h"

CElliIdleState::CElliIdleState():
	m_fSpeed(120.f)
{
}

CElliIdleState::~CElliIdleState()
{
}

void CElliIdleState::finaltick()
{
	CElli* pMonster = dynamic_cast<CElli*>(GetOwnerObj());
	assert(pMonster);

	Vec2 vPos = pMonster->GetPos();
	pMonster->SetPrevPos(vPos);

	// 상하좌우로 움직이기

	if (pMonster->GetDir() == 0 && pMonster->GetPos().y > 60.f)
	{
		vPos.y -= m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"Elli_WALK_UP", true);
			pMonster->m_bTurned = true;
		}

	}

	if (pMonster->GetDir() == 1 && pMonster->GetPos().y < 540.f)
	{
		vPos.y += m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"Elli_WALK_DOWN", true);
			pMonster->m_bTurned = true;
		}

	}

	if (pMonster->GetDir() == 2 && pMonster->GetPos().x > 40.f)
	{
		vPos.x -= m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"Elli_WALK_LEFT", true);
			pMonster->m_bTurned = true;
		}

	}

	if (pMonster->GetDir() == 3 && pMonster->GetPos().x < 620.f)
	{
		vPos.x += m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"Elli_WALK_RIGHT", true);
			pMonster->m_bTurned = true;
		}
	}

	if (vPos.x <= 40.f || vPos.x >= 620.f || vPos.y >= 540.f || vPos.y <= 60.f)
	{
		pMonster->SetPos(pMonster->m_TileCenter);
		pMonster->SetDir(rand() % 4);
		pMonster->m_bTurned = false;
	}

}

void CElliIdleState::Enter()
{
	CElli* pMonster = dynamic_cast<CElli*>(GetOwnerObj());
	assert(pMonster);

	if (pMonster->m_dir == 0)
	{
		pMonster->GetAnimator()->Play(L"Elli_WALK_UP", true);
	}

	else if (pMonster->m_dir == 1)
	{
		pMonster->GetAnimator()->Play(L"Elli_WALK_DOWN", true);
	}

	else if (pMonster->m_dir == 2)
	{
		pMonster->GetAnimator()->Play(L"Elli_WALK_LEFT", true);
	}

	else if (pMonster->m_dir == 3)
	{
		pMonster->GetAnimator()->Play(L"Elli_WALK_RIGHT", true);
	}
}

void CElliIdleState::Exit()
{
}


