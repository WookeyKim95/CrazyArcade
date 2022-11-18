#include "pch.h"
#include "COrangeDeadState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CLevel.h"
#include "CLevelMgr.h"


#include "CMonsterAI.h"
#include "COrange.h"


COrangeDeadState::COrangeDeadState() :
	m_DurationTime(0.f)
{
}

COrangeDeadState::~COrangeDeadState()
{
}

void COrangeDeadState::finaltick()
{
	COrange* pMonster = dynamic_cast<COrange*>(GetOwnerObj());
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

void COrangeDeadState::Enter()
{
	COrange* pMonster = dynamic_cast<COrange*>(GetOwnerObj());
	assert(pMonster);

	pMonster->GetAnimator()->Play(L"Orange_DEAD", false);
	pMonster->GetCollider()->SetScale(Vec2(0.f, 0.f));
}

void COrangeDeadState::Exit()
{
}

