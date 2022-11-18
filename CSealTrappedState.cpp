#include "pch.h"
#include "CSealTrappedState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CMonsterAI.h"
#include "CSeal.h"

CSealTrappedState::CSealTrappedState():
	m_DurationTime(0.f)
{
}

CSealTrappedState::~CSealTrappedState()
{
}

void CSealTrappedState::finaltick()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	m_DurationTime += DT;
	if (m_DurationTime > 10.f)
	{
		pMonster->m_HP = SEAL_FULL_HP;
		m_DurationTime = 0;
		GetOwnerMonsterAI()->ChangeState(L"Seal_Idle");
		pMonster->m_BTrapped = false;
		pMonster->m_bHit = false;
	}
}

void CSealTrappedState::Enter()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	pMonster->GetAnimator()->Play(L"SEAL_TRAPPED", false);
}

void CSealTrappedState::Exit()
{
}


