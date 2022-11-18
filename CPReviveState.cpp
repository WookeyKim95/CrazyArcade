#include "pch.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CTimeMgr.h"
#include "CPReviveState.h"

CPReviveState::CPReviveState() :
	m_DurationTime(0.f)
{
}

CPReviveState::~CPReviveState()
{
}

void CPReviveState::finaltick()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerPlayer());
	assert(pPlayer);

	m_DurationTime += DT;

	if (m_DurationTime > 0.5f)
	{
		m_DurationTime = 0;
		pPlayer->GetAnimator()->Play(L"IDLE_DOWN", false);
		pPlayer->ChangeState(L"Idle");
	}
}

void CPReviveState::Enter()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerPlayer());
	assert(pPlayer);

	pPlayer->GetAnimator()->Play(L"REVIVAL", false);
}

void CPReviveState::Exit()
{
}

