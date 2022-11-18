#include "pch.h"

#include "CCollisionMgr.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CLevelMgr.h"
#include "CResMgr.h"

#include "CSound.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CWaveCenter.h"
#include "CWave.h"


CWaveCenter::CWaveCenter(int _WaveCount) :
	m_DurationTime(0),
	m_WaveCount(_WaveCount),
	m_BOOM(false)
{
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(40.f, 40.f));

	// Animator 에서 사용할 Image 로딩
	CTexture* pWaveCenter = CResMgr::GetInst()->LoadTexture(L"WaveCenter", L"Texture\\Flow\\Flow_Center.bmp");
	GetAnimator()->CreateAnimation(L"WAVE_CENTER", pWaveCenter, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 4, 0.125f);
	GetAnimator()->Play(L"WAVE_CENTER", false);

	CSound* pBombSound = CResMgr::GetInst()->FindSound(L"Bomb");

	pBombSound->SetPosition(0.f);
	pBombSound->Play();
}

CWaveCenter::~CWaveCenter()
{
}

void CWaveCenter::tick()
{
	if (!m_BOOM)
	{
		CWave* pWave = new CWave(m_WaveCount, 0);
		CWave* pWave1 = new CWave(m_WaveCount, 1);
		CWave* pWave2 = new CWave(m_WaveCount, 2);
		CWave* pWave3 = new CWave(m_WaveCount, 3);

		pWave->SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
		Instantiate(pWave, Vec2(GetPos().x, GetPos().y - TILE_SIZE), LAYER::WAVE);
		pWave1->SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
		Instantiate(pWave1, Vec2(GetPos().x, GetPos().y + TILE_SIZE), LAYER::WAVE);
		pWave2->SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
		Instantiate(pWave2, Vec2(GetPos().x - TILE_SIZE, GetPos().y), LAYER::WAVE);
		pWave3->SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
		Instantiate(pWave3, Vec2(GetPos().x + TILE_SIZE, GetPos().y), LAYER::WAVE);
		m_BOOM = true;
	}

	m_DurationTime += DT;


	if (m_DurationTime > 0.5f)
	{
		SetDead();
		m_DurationTime = 0;
	}
}

void CWaveCenter::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetScale();

	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Rectangle(_dc, (int)(vPos.x - vSize.x / 2.f)
		, (int)(vPos.y - vSize.y / 2.f)
		, (int)(vPos.x + vSize.x / 2.f)
		, (int)(vPos.y + vSize.y / 2.f));

	SelectObject(_dc, hOriginBrush);

	CObj::render(_dc);
}

void CWaveCenter::BeginOverlap(CCollider* _pOther)
{
}

void CWaveCenter::OnOverlap(CCollider* _pOther)
{
}

void CWaveCenter::EndOverlap(CCollider* _pOther)
{
}


