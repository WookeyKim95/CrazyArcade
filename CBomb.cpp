#include "pch.h"
#include "CBomb.h"

#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollider.h"
#include "CResMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CPlayer.h"
#include "CObstacle.h"
#include "CWaveCenter.h"

CBomb::CBomb(CPlayer* Player, int _WaveCount)
	: m_DurationTime(0),
	  m_fSpeed(700.f),
	  m_WhoUsed(Player),
	  m_WaveCount(_WaveCount),
	  m_BKicked(false),
      m_dir(0),
	  m_NowCenTileX(0),
	  m_NowCenTileY(0),
	  m_TileCenter(Vec2(0.f, 0.f))
{
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(TILE_SIZE - 10.f, TILE_SIZE - 10.f));

	// Animator 에서 사용할 Image 로딩
	CTexture* pBomb = CResMgr::GetInst()->LoadTexture(L"PBOMB", L"Texture\\Bomb\\Idle.bmp");

	GetAnimator()->CreateAnimation(L"PBomb", pBomb, Vec2(0.f, 0.f), Vec2(44.f, 41.f), Vec2(0.f, 0.f), 4, 0.2f);
	GetAnimator()->Play(L"PBomb", true);
}

CBomb::~CBomb()
{
}

void CBomb::tick()
{
	Vec2 vPos = GetPos();

	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 13; ++j)
		{
			Vec2 Candi_TileCenter = { 20.f + TILE_SIZE / 2 + TILE_SIZE * i
									, 40.f + TILE_SIZE / 2 + TILE_SIZE * j };
			if ((abs(vPos.x - m_TileCenter.x) > abs(vPos.x - Candi_TileCenter.x)))
			{
				m_TileCenter.x = Candi_TileCenter.x;
				m_NowCenTileX = i;
			}

			if ((abs(vPos.y - m_TileCenter.y) > abs(vPos.y - Candi_TileCenter.y)))
			{
				m_TileCenter.y = Candi_TileCenter.y;
				m_NowCenTileY = j;
			}

		}
	}

	if (m_BKicked)
	{
		if (m_dir != 0)
		{


			if (m_dir == 1) // 상
			{
				vPos.y -= m_fSpeed * DT;
				SetPos(vPos);
				m_DurationTime = 0.f;
			}

			else if (m_dir == 2) // 하
			{
				vPos.y += m_fSpeed * DT;
				SetPos(vPos);
				m_DurationTime = 0.f;
			}

			else if (m_dir == 3) // 좌
			{
				vPos.x -= m_fSpeed * DT;
				SetPos(vPos);
				m_DurationTime = 0.f;
			}

			else if (m_dir == 4) // 우
			{
				vPos.x += m_fSpeed * DT;
				SetPos(vPos);
				m_DurationTime = 0.f;
			}

			if (vPos.x < 40.f || 600.f < vPos.x || vPos.y < 60.f || vPos.y > 540.f)
			{
				m_dir = 0;
				m_BKicked = false;
				SetPos(m_TileCenter);
			}
		}
	
	}

	m_DurationTime += DT;

	if (m_DurationTime > 2)
	{
		BOOM();
	}

}

void CBomb::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetScale();

	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	SelectObject(_dc, (HPEN)GetStockObject(NULL_PEN));

	Rectangle(_dc, (int)(vPos.x - vSize.x / 2.f)
		, (int)(vPos.y - vSize.y / 2.f)
		, (int)(vPos.x + vSize.x / 2.f)
		, (int)(vPos.y + vSize.y / 2.f));

	SelectObject(_dc, hOriginBrush);

	CObj::render(_dc);
}

void CBomb::BeginOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::WAVE)
	{
		BOOM();
	}
}

void CBomb::OnOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::OBSTACLE)
	{
		CObstacle* _pObstacle = (CObstacle*)(_pOther->GetOwner());
		Vec2 ObsPos = _pObstacle->GetPos();

		if (_pObstacle->GetObstacle() == true && m_BKicked) // 이동 불가능한 곳에 접촉 했을 때
		{
			m_BKicked = false;
			m_dir = 0;
			SetPos(m_TileCenter);
		}
	}

	else if (_pOther->GetOwner()->ReturnLayer() == LAYER::BOMB)
	{
		CBomb* _pBomb = (CBomb*)(_pOther->GetOwner());
		Vec2 ObsPos = _pBomb->GetPos();

		if (m_BKicked) // 이동 불가능한 곳에 접촉 했을 때
		{
			m_BKicked = false;
			m_dir = 0;
			SetPos(m_TileCenter);
		}
	}
}

void CBomb::EndOverlap(CCollider* _pOther)
{
}

void CBomb::BOOM()
{
	CWaveCenter* pWaveCenter = new CWaveCenter(m_WaveCount);
	pWaveCenter->SetScale(Vec2(40.f, 40.f));
	Instantiate(pWaveCenter, GetPos(), LAYER::WAVE_CENTER);

	SetDead();
	int BombCount = m_WhoUsed->GetBombCount();
	if (m_WhoUsed->GetBombCount() < m_WhoUsed->GetMaxBombCount())
		m_WhoUsed->SetBombCount(++BombCount);
	m_DurationTime = 0;
}

