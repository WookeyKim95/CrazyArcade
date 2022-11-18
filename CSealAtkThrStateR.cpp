#include "pch.h"
#include "CSealAtkThrStateR.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CMonsterAI.h"
#include "CSeal.h"

CSealAtkThrStateR::CSealAtkThrStateR() :
	m_DurationTime(0.f),
	m_BAttacked(false)
{
}

CSealAtkThrStateR::~CSealAtkThrStateR()
{
}

void CSealAtkThrStateR::finaltick()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	Vec2 vPos = pMonster->GetPos();
	vPos.x += 200.f * DT;
	pMonster->SetPos(vPos);


	m_DurationTime += DT;
	if (m_DurationTime > (375.f / 200.f))
	{
		m_DurationTime = 0;
		GetOwnerMonsterAI()->ChangeState(L"Seal_Idle");
	}

}

void CSealAtkThrStateR::Enter()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	pMonster->GetAnimator()->Play(L"SEAL_ATTACK_RIGHT", true);
}

void CSealAtkThrStateR::Exit()
{

}


