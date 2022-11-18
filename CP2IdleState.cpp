#include "pch.h"
#include "CP2IdleState.h"

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

CP2IdleState::CP2IdleState()
{
}

CP2IdleState::~CP2IdleState()
{
}

void CP2IdleState::finaltick()
{
	CPlayer2* pPlayer = dynamic_cast<CPlayer2*>(GetOwnerPlayer());
	assert(pPlayer);

	Vec2 vPos = pPlayer->GetPos();
	pPlayer->SetPrevPos(vPos);

	// �����¿� Ű�� �����̱�
	if (IsPressed(KEY::D) && !(IsPressed(KEY::S)) && !(IsPressed(KEY::W)) && !(IsPressed(KEY::A)) && pPlayer->CanMove[3])
	{
		vPos.x += pPlayer->m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (IsPressed(KEY::A) && !(IsPressed(KEY::S)) && !(IsPressed(KEY::W)) && !(IsPressed(KEY::D)) && pPlayer->CanMove[2])
	{
		vPos.x -= pPlayer->m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (IsPressed(KEY::S) && !(IsPressed(KEY::W)) && !(IsPressed(KEY::D)) && !(IsPressed(KEY::A)) && pPlayer->CanMove[1])
	{
		vPos.y += pPlayer->m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (IsPressed(KEY::W) && !(IsPressed(KEY::D)) && !(IsPressed(KEY::S)) && !(IsPressed(KEY::A)) && pPlayer->CanMove[0])
	{
		vPos.y -= pPlayer->m_fSpeed * DT;
		pPlayer->SetPos(vPos);
	}

	if (vPos.x < 40.f || 600.f < vPos.x || vPos.y < 60.f || vPos.y > 540.f)
	{
		pPlayer->SetPos(pPlayer->GetPrevPos());
		vPos = pPlayer->GetPrevPos();
	}


	// ���ٰ� ���� �� �ִϸ��̼� ���
	if (IsRelease(KEY::D) && !(IsPressed(KEY::S)) && !(IsPressed(KEY::W)) && !(IsPressed(KEY::A)))
	{
		pPlayer->GetAnimator()->Play(L"IDLE_RIGHT", true);
	}

	if (IsRelease(KEY::A) && !(IsPressed(KEY::S)) && !(IsPressed(KEY::W)) && !(IsPressed(KEY::D)))
	{
		pPlayer->GetAnimator()->Play(L"IDLE_LEFT", true);
	}

	if (IsRelease(KEY::W) && !(IsPressed(KEY::S)) && !(IsPressed(KEY::D)) && !(IsPressed(KEY::A)))
	{
		pPlayer->GetAnimator()->Play(L"IDLE_UP", true);
	}

	if (IsRelease(KEY::S) && !(IsPressed(KEY::D)) && !(IsPressed(KEY::W)) && !(IsPressed(KEY::A)))
	{
		pPlayer->GetAnimator()->Play(L"IDLE_DOWN", true);
	}

	// �ȴ� �� �ִϸ��̼� ���
	if (IsTap(KEY::D))
	{
		pPlayer->GetAnimator()->Play(L"WALK_RIGHT", true);
	}

	if (IsTap(KEY::W))
	{
		pPlayer->GetAnimator()->Play(L"WALK_UP", true);
	}

	if (IsTap(KEY::A))
	{
		pPlayer->GetAnimator()->Play(L"WALK_LEFT", true);
	}

	if (IsTap(KEY::S))
	{
		pPlayer->GetAnimator()->Play(L"WALK_DOWN", true);
	}


	// ���� ����� Ÿ���� �߾ӿ� ��ǳ���� ���� �� �ֵ��� ��ó ������ǥ�� ������ �ϴ� ����


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




	if (IsTap(KEY::Q) && pPlayer->m_BombCount > 0 && pPlayer->m_CanSetBomb)
	{
		// ����ź ����
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		CBomb2* pBomb = new CBomb2(pPlayer, pPlayer->GetWaveCount()); // �� �÷��̾ ���Ҵٴ� ���� ǥ���ϱ� ����.

		// ��ǳ�� ��ǥ ����
		pBomb->SetScale(Vec2(40.f, 40.f));
		Instantiate(pBomb, pPlayer->m_TileCenter, LAYER::BOMB);
		--(pPlayer->m_BombCount);
		pPlayer->m_BombFirst = true;
	}
}

void CP2IdleState::Enter()
{
	CPlayer2* pPlayer = dynamic_cast<CPlayer2*>(GetOwnerPlayer());
	assert(pPlayer);

	pPlayer->m_BTrapped = false;
}

void CP2IdleState::Exit()
{
}


