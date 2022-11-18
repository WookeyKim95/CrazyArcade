#include "pch.h"
#include "CPIdleState.h"

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

CPIdleState::CPIdleState()
{
}

CPIdleState::~CPIdleState()
{
}

void CPIdleState::finaltick()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerPlayer());
	assert(pPlayer);

	Vec2 vPos = pPlayer->GetPos();
	pPlayer->SetPrevPos(vPos);

	// 상하좌우 키로 움직이기
	if (IsPressed(KEY::RIGHT) && !(IsPressed(KEY::DOWN)) && !(IsPressed(KEY::UP)) && !(IsPressed(KEY::LEFT)) && pPlayer->CanMove[3])
	{
		vPos.x += pPlayer->m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (IsPressed(KEY::LEFT) && !(IsPressed(KEY::DOWN)) && !(IsPressed(KEY::UP)) && !(IsPressed(KEY::RIGHT)) && pPlayer->CanMove[2])
	{
		vPos.x -= pPlayer->m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (IsPressed(KEY::DOWN) && !(IsPressed(KEY::UP)) && !(IsPressed(KEY::RIGHT)) && !(IsPressed(KEY::LEFT)) && pPlayer->CanMove[1])
	{
		vPos.y += pPlayer->m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (IsPressed(KEY::UP) && !(IsPressed(KEY::RIGHT)) && !(IsPressed(KEY::DOWN)) && !(IsPressed(KEY::LEFT)) && pPlayer->CanMove[0])
	{
		vPos.y -= pPlayer->m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (vPos.x < 40.f || 600.f < vPos.x || vPos.y < 60.f || vPos.y > 540.f)
	{
		pPlayer->SetPos(pPlayer->GetPrevPos());
		vPos = pPlayer->GetPrevPos();
	}


	// 가다가 섰을 때 애니메이션 재생
	if (IsRelease(KEY::RIGHT) && !(IsPressed(KEY::DOWN)) && !(IsPressed(KEY::UP)) && !(IsPressed(KEY::LEFT)))
	{
		pPlayer->GetAnimator()->Play(L"IDLE_RIGHT", true);
	}

	if (IsRelease(KEY::LEFT) && !(IsPressed(KEY::DOWN)) && !(IsPressed(KEY::UP)) && !(IsPressed(KEY::RIGHT)))
	{
		pPlayer->GetAnimator()->Play(L"IDLE_LEFT", true);
	}

	if (IsRelease(KEY::UP) && !(IsPressed(KEY::DOWN)) && !(IsPressed(KEY::RIGHT)) && !(IsPressed(KEY::LEFT)))
	{
		pPlayer->GetAnimator()->Play(L"IDLE_UP", true);
	}

	if (IsRelease(KEY::DOWN) && !(IsPressed(KEY::RIGHT)) && !(IsPressed(KEY::UP)) && !(IsPressed(KEY::LEFT)))
	{
		pPlayer->GetAnimator()->Play(L"IDLE_DOWN", true);
	}

	// 걷는 중 애니메이션 재생
	if (IsTap(KEY::RIGHT))
	{
		pPlayer->GetAnimator()->Play(L"WALK_RIGHT", true);
	}

	if (IsTap(KEY::UP))
	{
		pPlayer->GetAnimator()->Play(L"WALK_UP", true);
	}

	if (IsTap(KEY::LEFT))
	{
		pPlayer->GetAnimator()->Play(L"WALK_LEFT", true);
	}

	if (IsTap(KEY::DOWN))
	{
		pPlayer->GetAnimator()->Play(L"WALK_DOWN", true);
	}


	// 가장 가까운 타일의 중앙에 물풍선을 놓을 수 있도록 근처 센터좌표를 재정의 하는 구간


	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 13; ++j)
		{
			Vec2 Candi_TileCenter = { 20.f + TILE_SIZE / 2 + TILE_SIZE * i
									, 40.f + TILE_SIZE / 2 + TILE_SIZE * j };
			if ((abs(vPos.x - pPlayer->m_TileCenter.x) > abs(vPos.x - Candi_TileCenter.x)))
			{
				pPlayer->m_TileCenter.x = Candi_TileCenter.x;
				pPlayer->m_NowCenTileX = i;
			}

			if ((abs(vPos.y - pPlayer->m_TileCenter.y) > abs(vPos.y - Candi_TileCenter.y)))
			{
				pPlayer->m_TileCenter.y = Candi_TileCenter.y;
				pPlayer->m_NowCenTileY = j;
			}

		}
	}




	if (IsTap(KEY::SPACE) && pPlayer->m_BombCount > 0 && pPlayer->m_CanSetBomb)
	{
		// 물폭탄 생성
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		CBomb* pBomb = new CBomb(pPlayer, pPlayer->GetWaveCount()); // 이 플레이어가 놓았다는 것을 표시하기 위함.

		// 물풍선 좌표 설정
		pBomb->SetScale(Vec2(40.f, 40.f));
		Instantiate(pBomb, pPlayer->m_TileCenter, LAYER::BOMB);
		--(pPlayer->m_BombCount);
		pPlayer->m_BombFirst = true;
	}
}

void CPIdleState::Enter()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerPlayer());
	assert(pPlayer);

	pPlayer->m_BTrapped = false;
}

void CPIdleState::Exit()
{
}


