#include "pch.h"
#include "CPReadyState.h"

#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CCollider.h"

#include "CPlayer.h"
#include "CBomb.h"
#include "CObstacle.h"

#include "CAnimator.h"
#include "CAnimation.h"

CPReadyState::CPReadyState() :
	m_DurationTime(0.f)
{
}

CPReadyState::~CPReadyState()
{
}

void CPReadyState::finaltick()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerPlayer());
	assert(pPlayer);

	m_DurationTime += DT;
	if (m_DurationTime > START_TIME)
	{
		pPlayer->ChangeState(L"Idle");
	}
}

void CPReadyState::Enter()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerPlayer());
	assert(pPlayer);
	pPlayer->GetAnimator()->Play(L"READY", true);
}

void CPReadyState::Exit()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerPlayer());
	assert(pPlayer);
	pPlayer->GetAnimator()->Play(L"IDLE_DOWN", true);
}


