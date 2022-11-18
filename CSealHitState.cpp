#include "pch.h"
#include "CSealHitState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CMonsterAI.h"
#include "CSeal.h"

CSealHitState::CSealHitState() :
	m_DurationTime(0.f)
{
}

CSealHitState::~CSealHitState()
{
}

void CSealHitState::finaltick()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	m_DurationTime += DT;
	if (m_DurationTime > 1.f)
	{
		m_DurationTime = 0;
		GetOwnerMonsterAI()->ChangeState(L"Seal_Idle");
		pMonster->m_bHit = false;
	}
}

void CSealHitState::Enter()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	pMonster->GetAnimator()->Play(L"SEAL_HITTED", false);
}

void CSealHitState::Exit()
{
}


