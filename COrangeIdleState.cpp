#include "pch.h"
#include "COrangeIdleState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CMonsterAI.h"
#include "COrange.h"

COrangeIdleState::COrangeIdleState() :
	m_fSpeed(45.f)
{
}

COrangeIdleState::~COrangeIdleState()
{
}

void COrangeIdleState::finaltick()
{
	COrange* pMonster = dynamic_cast<COrange*>(GetOwnerObj());
	assert(pMonster);

	Vec2 vPos = pMonster->GetPos();
	pMonster->SetPrevPos(vPos);

	// �����¿�� �����̱�

	if (pMonster->GetDir() == 0 && pMonster->GetPos().y > 40.f)
	{
		vPos.y -= m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"Orange_WALK_UP", true);
			pMonster->m_bTurned = true;
		}

	}

	if (pMonster->GetDir() == 1 && pMonster->GetPos().y < 540.f)
	{
		vPos.y += m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"Orange_WALK_DOWN", true);
			pMonster->m_bTurned = true;
		}

	}

	if (pMonster->GetDir() == 2 && pMonster->GetPos().x > 20.f)
	{
		vPos.x -= m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"Orange_WALK_LEFT", true);
			pMonster->m_bTurned = true;
		}

	}

	if (pMonster->GetDir() == 3 && pMonster->GetPos().x < 620.f)
	{
		vPos.x += m_fSpeed * DT;
		pMonster->SetPos(vPos);
		if (!pMonster->m_bTurned)
		{
			pMonster->GetAnimator()->Play(L"Orange_WALK_RIGHT", true);
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

void COrangeIdleState::Enter()
{
	COrange* pMonster = dynamic_cast<COrange*>(GetOwnerObj());
	assert(pMonster);

	if (pMonster->m_dir == 0)
	{
		pMonster->GetAnimator()->Play(L"Orange_WALK_UP", true);
	}

	else if (pMonster->m_dir == 1)
	{
		pMonster->GetAnimator()->Play(L"Orange_WALK_DOWN", true);
	}

	else if (pMonster->m_dir == 2)
	{
		pMonster->GetAnimator()->Play(L"Orange_WALK_LEFT", true);
	}

	else if (pMonster->m_dir == 3)
	{
		pMonster->GetAnimator()->Play(L"Orange_WALK_RIGHT", true);
	}
}

void COrangeIdleState::Exit()
{
}


