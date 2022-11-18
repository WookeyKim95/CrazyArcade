#include "pch.h"
#include "CMBOneDeadState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CLevel.h"
#include "CLevelMgr.h"

#include "CMonsterAI.h"
#include "CMiniBallOne.h"

CMBOneDeadState::CMBOneDeadState() :
	m_DurationTime(0.f)
{
}

CMBOneDeadState::~CMBOneDeadState()
{
}

void CMBOneDeadState::finaltick()
{
	CMiniBallOne* pMonster = dynamic_cast<CMiniBallOne*>(GetOwnerObj());
	assert(pMonster);

	m_DurationTime += DT;
	if (m_DurationTime > 1.2f)
	{
		m_DurationTime = 0;
		pMonster->SetDead();

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
		assert(pCurLevel);

		pCurLevel->SetMonsterCount(pCurLevel->GetMonsterCount() - 1);
	}
}

void CMBOneDeadState::Enter()
{
	CMiniBallOne* pMonster = dynamic_cast<CMiniBallOne*>(GetOwnerObj());
	assert(pMonster);

	pMonster->GetAnimator()->Play(L"MBOne_DEAD", false);
	pMonster->GetCollider()->SetScale(Vec2(0.f, 0.f));
}

void CMBOneDeadState::Exit()
{
}


