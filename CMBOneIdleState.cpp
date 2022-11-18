#include "pch.h"
#include "CMBOneIdleState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CMonsterAI.h"
#include "CMiniBallOne.h"

CMBOneIdleState::CMBOneIdleState() :
	m_fSpeed(45.f)
{
}

CMBOneIdleState::~CMBOneIdleState()
{
}

void CMBOneIdleState::finaltick()
{
	CMiniBallOne* pMonster = dynamic_cast<CMiniBallOne*>(GetOwnerObj());
	assert(pMonster);

	Vec2 vPos = pMonster->GetPos();
	pMonster->SetPrevPos(vPos);

	// 상하좌우로 움직이기

	if (pMonster->GetDir() == 0 && pMonster->GetPos().y > 40.f)
	{
		vPos.y -= m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"MBOne_WALK_UP", true);
			pMonster->m_bTurned = true;
		}

	}

	if (pMonster->GetDir() == 1 && pMonster->GetPos().y < 540.f)
	{
		vPos.y += m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"MBOne_WALK_DOWN", true);
			pMonster->m_bTurned = true;
		}

	}

	if (pMonster->GetDir() == 2 && pMonster->GetPos().x > 20.f)
	{
		vPos.x -= m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"MBOne_WALK_LEFT", true);
			pMonster->m_bTurned = true;
		}

	}

	if (pMonster->GetDir() == 3 && pMonster->GetPos().x < 620.f)
	{
		vPos.x += m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"MBOne_WALK_RIGHT", true);
			pMonster->m_bTurned = true;
		}
	}

	if (vPos.x <= 40.f || vPos.x >= 600.f || vPos.y >= 540.f || vPos.y <= 60.f)
	{
		pMonster->SetPos(pMonster->m_TileCenter);
		pMonster->SetDir(rand() % 4);
		pMonster->m_bTurned = false;
	}
}

void CMBOneIdleState::Enter()
{
	CMiniBallOne* pMonster = dynamic_cast<CMiniBallOne*>(GetOwnerObj());
	assert(pMonster);

	if (pMonster->m_dir == 0)
	{
		pMonster->GetAnimator()->Play(L"MBOne_WALK_UP", true);
	}

	else if (pMonster->m_dir == 1)
	{
		pMonster->GetAnimator()->Play(L"MBOne_WALK_DOWN", true);
	}

	else if (pMonster->m_dir == 2)
	{
		pMonster->GetAnimator()->Play(L"MBOne_WALK_LEFT", true);
	}

	else if (pMonster->m_dir == 3)
	{
		pMonster->GetAnimator()->Play(L"MBOne_WALK_RIGHT", true);
	}
}

void CMBOneIdleState::Exit()
{
}


