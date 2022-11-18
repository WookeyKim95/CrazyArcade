#include "pch.h"
#include "CElliDeadState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

#include "CLevel.h"
#include "CLevelMgr.h"

#include "CMonsterAI.h"
#include "CElli.h"

CElliDeadState::CElliDeadState():
	m_DurationTime(0.f)
{
}

CElliDeadState::~CElliDeadState()
{
}

void CElliDeadState::finaltick()
{
	CElli* pMonster = dynamic_cast<CElli*>(GetOwnerObj());
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

void CElliDeadState::Enter()
{
	CElli* pMonster = dynamic_cast<CElli*>(GetOwnerObj());
	assert(pMonster);

	pMonster->GetAnimator()->Play(L"Elli_DEAD", false);
	pMonster->GetCollider()->SetScale(Vec2(0.f, 0.f));
	
}

void CElliDeadState::Exit()
{
}


