#include "pch.h"
#include "CSealAtkOneState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CMonsterObj.h"

#include "CMonsterAI.h"
#include "CSeal.h"

CSealAtkOneState::CSealAtkOneState():
	m_DurationTime(0.f),
	m_BAttacked(false)
{
}

CSealAtkOneState::~CSealAtkOneState()
{
}

void CSealAtkOneState::finaltick()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	if (!m_BAttacked)
	{
		Vec2 vPos = pMonster->m_TileCenter;

		int vX = pMonster->m_NowCenTileX;
		int vY = pMonster->m_NowCenTileY;

		for (int i = vX - 3; i <= vX + 3; ++i)
		{
			for (int j = vY - 3; j <= vY + 3; ++j)
			{
				CMonsterObj* pSealAtk = new CMonsterObj;
				pSealAtk->SetScale(Vec2(40.f, 40.f));
				Instantiate(pSealAtk, Vec2(i * TILE_SIZE + 40.f, j * TILE_SIZE + 60.f), LAYER::MONSTER_OBJECTILE);
			}
		}

		m_BAttacked = true;
	}

	m_DurationTime += DT;
	if (m_DurationTime > 2.f)
	{
		m_DurationTime = 0;
		GetOwnerMonsterAI()->ChangeState(L"Seal_Idle");
	}

}

void CSealAtkOneState::Enter()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	pMonster->GetAnimator()->Play(L"SEAL_SHOUTING", true);
}

void CSealAtkOneState::Exit()
{
	m_BAttacked = false;
}


