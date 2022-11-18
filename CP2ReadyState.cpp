#include "pch.h"
#include "CP2ReadyState.h"

#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CCollider.h"

#include "CPlayer2.h"
#include "CBomb2.h"
#include "CObstacle.h"

#include "CAnimator.h"
#include "CAnimation.h"

CP2ReadyState::CP2ReadyState() :
	m_DurationTime(0.f)
{
}

CP2ReadyState::~CP2ReadyState()
{
}


void CP2ReadyState::finaltick()
{
	CPlayer2* pPlayer = dynamic_cast<CPlayer2*>(GetOwnerPlayer());
	assert(pPlayer);

	m_DurationTime += DT;
	if (m_DurationTime > START_TIME)
	{
		pPlayer->ChangeState(L"Idle2");
	}
}

void CP2ReadyState::Enter()
{
	CPlayer2* pPlayer = dynamic_cast<CPlayer2*>(GetOwnerPlayer());
	assert(pPlayer);
	pPlayer->GetAnimator()->Play(L"READY", true);
}

void CP2ReadyState::Exit()
{
	CPlayer2* pPlayer = dynamic_cast<CPlayer2*>(GetOwnerPlayer());
	assert(pPlayer);
	pPlayer->GetAnimator()->Play(L"IDLE_DOWN", true);
}

