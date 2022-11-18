#include "pch.h"
#include "CPTrappedState.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CPlayer.h"
#include "CBomb.h"
#include "CObstacle.h"
#include "CItem.h"
#include "CNeedle.h"

#include "CAnimator.h"
#include "CAnimation.h"


CPTrappedState::CPTrappedState()
	: m_DurationTime(0.f)
	, m_fSpeed(10.f)
	, m_ToRevive(false)
{
}

CPTrappedState::~CPTrappedState()
{
}

void CPTrappedState::finaltick()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerPlayer());
	assert(pPlayer);

	Vec2 vPos = pPlayer->GetPos();
	pPlayer->SetPrevPos(vPos);

	// 상하좌우 키로 움직이기
	if (IsPressed(KEY::RIGHT) && !(IsPressed(KEY::DOWN)) && !(IsPressed(KEY::UP)) && !(IsPressed(KEY::LEFT)))
	{
		vPos.x += m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (IsPressed(KEY::LEFT) && !(IsPressed(KEY::DOWN)) && !(IsPressed(KEY::UP)) && !(IsPressed(KEY::RIGHT)))
	{
		vPos.x -= m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (IsPressed(KEY::DOWN) && !(IsPressed(KEY::UP)) && !(IsPressed(KEY::RIGHT)) && !(IsPressed(KEY::LEFT)))
	{
		vPos.y += m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (IsPressed(KEY::UP) && !(IsPressed(KEY::RIGHT)) && !(IsPressed(KEY::DOWN)) && !(IsPressed(KEY::LEFT)))
	{
		vPos.y -= m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (vPos.x < 40.f || 600.f < vPos.x || vPos.y < 60.f || vPos.y > 540.f)
	{
		pPlayer->SetPos(pPlayer->GetPrevPos());
		vPos = pPlayer->GetPrevPos();
	}

	if (IsTap(KEY::LCTRL))
	{
		if (pPlayer->GetItemSlot() != ITEM::NONE)
		{
			if (pPlayer->GetItemSlot() == ITEM::NEEDLE)
			{
				pPlayer->SetItemSlot(ITEM::NONE);
				m_DurationTime = 0;
				pPlayer->ChangeState(L"Revive");
			}
		}
	}



	m_DurationTime += DT;

	if (m_DurationTime > 5)
	{
		pPlayer->ChangeState(L"Dead");
		m_DurationTime = 0;
	}


}

void CPTrappedState::Enter()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerPlayer());
	assert(pPlayer);

	pPlayer->GetAnimator()->Play(L"TRAPPED", false);
	m_ToRevive = false;
}

void CPTrappedState::Exit()
{
}