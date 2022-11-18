#include "pch.h"
#include "CMBTwoDeadState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CLevel.h"
#include "CLevelMgr.h"


#include "CMonsterAI.h"
#include "CMiniBallTwo.h"

CMBTwoDeadState::CMBTwoDeadState() :
	m_DurationTime(0.f)
{
}


CMBTwoDeadState::~CMBTwoDeadState()
{
}

void CMBTwoDeadState::finaltick()
{
	CMiniBallTwo* pMonster = dynamic_cast<CMiniBallTwo*>(GetOwnerObj());
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

void CMBTwoDeadState::Enter()
{
	CMiniBallTwo* pMonster = dynamic_cast<CMiniBallTwo*>(GetOwnerObj());
	assert(pMonster);

	pMonster->GetAnimator()->Play(L"MBTwo_DEAD", false);
	pMonster->GetCollider()->SetScale(Vec2(0.f, 0.f));
}

void CMBTwoDeadState::Exit()
{
}



