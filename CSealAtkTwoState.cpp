#include "pch.h"
#include "CSealAtkTwoState.h"

#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CLevel.h"
#include "CLevelMgr.h"

#include "CMiniBallOne.h"
#include "CMiniBallTwo.h"

#include "CMonsterAI.h"
#include "CSeal.h"

CSealAtkTwoState::CSealAtkTwoState() :
	m_DurationTime(0.f),
	m_BAttacked(false)
{
}

CSealAtkTwoState::~CSealAtkTwoState()
{
}

void CSealAtkTwoState::finaltick()
{
	
	if (!m_BAttacked)
	{
		for (int i = 0; i < 2; ++i)
		{
			int X = rand() % 15;
			int Y = rand() % 13;

			if (!(
				((0 <= X && X <= 2) && (3 <= Y && Y <= 9)) || 
				((12 <= X && X <= 14) && (3 <= Y && Y <= 9)) ||
				((3 <= X && X <= 11) && (0 <= Y && Y <= 1)) ||
				((3 <= X && X <= 11) && (11 <= Y && Y <= 12))))
			{
				--i;
				continue;
			}

			Vec2 Candi_TileCenter = { 20.f + TILE_SIZE / 2 + TILE_SIZE * X
									, 40.f + TILE_SIZE / 2 + TILE_SIZE * Y };

			int dice = rand() % 2;

			if (dice == 0)
			{
				CMiniBallOne* pMos = new CMiniBallOne;
				pMos->SetScale(Vec2(40.f, 40.f));
				Instantiate(pMos, Candi_TileCenter, LAYER::MONSTER);
			}

			else if (dice == 1)
			{
				CMiniBallTwo* pMos = new CMiniBallTwo;
				pMos->SetScale(Vec2(40.f, 40.f));
				Instantiate(pMos, Candi_TileCenter, LAYER::MONSTER);
			}

			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			assert(pCurLevel);

			pCurLevel->SetMonsterCount(pCurLevel->GetMonsterCount() + 1);

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

void CSealAtkTwoState::Enter()
{
	CSeal* pMonster = dynamic_cast<CSeal*>(GetOwnerObj());
	assert(pMonster);

	pMonster->GetAnimator()->Play(L"SEAL_SHOUTING", true);
}

void CSealAtkTwoState::Exit()
{
	m_BAttacked = false;
}


