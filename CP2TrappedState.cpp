#include "pch.h"
#include "CP2TrappedState.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CPlayer2.h"
#include "CBomb2.h"
#include "CObstacle.h"
#include "CItem.h"
#include "CNeedle.h"

#include "CAnimator.h"
#include "CAnimation.h"

CP2TrappedState::CP2TrappedState() :
	  m_DurationTime(0.f)
	, m_fSpeed(10.f)
	, m_ToRevive(false)
{
}

CP2TrappedState::~CP2TrappedState()
{
}

void CP2TrappedState::finaltick()
{
	CPlayer2* pPlayer = dynamic_cast<CPlayer2*>(GetOwnerPlayer());
	assert(pPlayer);

	Vec2 vPos = pPlayer->GetPos();
	pPlayer->SetPrevPos(vPos);

	// 상하좌우 키로 움직이기
	if (IsPressed(KEY::D) && !(IsPressed(KEY::S)) && !(IsPressed(KEY::W)) && !(IsPressed(KEY::A)))
	{
		vPos.x += m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (IsPressed(KEY::A) && !(IsPressed(KEY::S)) && !(IsPressed(KEY::W)) && !(IsPressed(KEY::D)))
	{
		vPos.x -= m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (IsPressed(KEY::S) && !(IsPressed(KEY::W)) && !(IsPressed(KEY::D)) && !(IsPressed(KEY::A)))
	{
		vPos.y += m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (IsPressed(KEY::W) && !(IsPressed(KEY::D)) && !(IsPressed(KEY::S)) && !(IsPressed(KEY::A)))
	{
		vPos.y -= m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (vPos.x < 40.f || 600.f < vPos.x || vPos.y < 60.f || vPos.y > 540.f)
	{
		pPlayer->SetPos(pPlayer->GetPrevPos());
		vPos = pPlayer->GetPrevPos();
	}

	if (IsTap(KEY::E))
	{
		if (pPlayer->GetItemSlot() != ITEM2::NONE)
		{
			if (pPlayer->GetItemSlot() == ITEM2::NEEDLE)
			{
				pPlayer->SetItemSlot(ITEM2::NONE);
				m_DurationTime = 0;
				pPlayer->ChangeState(L"Revive2");
			}
		}
	}

	m_DurationTime += DT;

	if (m_DurationTime > 5.f)
	{
		pPlayer->ChangeState(L"Dead2");
		m_DurationTime = 0;
	}
}

void CP2TrappedState::Enter()
{
	CPlayer2* pPlayer = dynamic_cast<CPlayer2*>(GetOwnerPlayer());
	assert(pPlayer);

	pPlayer->GetAnimator()->Play(L"TRAPPED", false);
	m_ToRevive = false;
}

void CP2TrappedState::Exit()
{
}


