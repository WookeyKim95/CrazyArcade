#include "pch.h"
#include "CSealDeadState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CLevelMgr.h"
#include "CLevel01.h"

#include "CMonsterAI.h"
#include "CSeal.h"

CSealDeadState::CSealDeadState():
	m_DurationTime(0.f)
{
}

CSealDeadState::~CSealDeadState()
{
}

void CSealDeadState::finaltick()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	m_DurationTime += DT;
	if (m_DurationTime > 3.f)
	{
		m_DurationTime = 0;
		pMonster->SetDead();

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
		assert(pCurLevel);

		pCurLevel->SetMonsterCount(pCurLevel->GetMonsterCount() - 1);
	}
}

void CSealDeadState::Enter()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	pMonster->GetAnimator()->Play(L"SEAL_DEAD", false);
}

void CSealDeadState::Exit()
{
}


