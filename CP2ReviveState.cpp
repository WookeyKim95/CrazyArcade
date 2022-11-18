#include "pch.h"
#include "CP2ReviveState.h"

#include "CPlayer2.h"
#include "CAnimator.h"
#include "CTimeMgr.h"

CP2ReviveState::CP2ReviveState() :
	m_DurationTime(0.f)
{
}

CP2ReviveState::~CP2ReviveState()
{
}

void CP2ReviveState::finaltick()
{
	CPlayer2* pPlayer = dynamic_cast<CPlayer2*>(GetOwnerPlayer());
	assert(pPlayer);

	m_DurationTime += DT;

	if (m_DurationTime > 0.5f)
	{
		m_DurationTime = 0;
		pPlayer->GetAnimator()->Play(L"IDLE_DOWN", false);
		pPlayer->ChangeState(L"Idle2");
	}
}

void CP2ReviveState::Enter()
{
	CPlayer2* pPlayer = dynamic_cast<CPlayer2*>(GetOwnerPlayer());
	assert(pPlayer);

	pPlayer->GetAnimator()->Play(L"REVIVAL", false);
}

void CP2ReviveState::Exit()
{
}

