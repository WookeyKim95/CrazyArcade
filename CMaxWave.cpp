#include "pch.h"
#include "CMaxWave.h"

#include "CCollider.h"
#include "CCollisionMgr.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CSound.h"
#include "CTexture.h"
#include "CPlayer.h"

CMaxWave::CMaxWave() : 
	m_pAtlas(nullptr),
	m_AccTime(0.f)
{
	CreateCollider();

	GetCollider()->SetOffsetPos(Vec2(15.f, 15.f));
	GetCollider()->SetScale(Vec2(TILE_SIZE - 15.f, TILE_SIZE - 15.f));

	CTexture* pMaxWave = CResMgr::GetInst()->LoadTexture(L"MAXWAVE", L"Texture\\Item\\MaxWater.bmp");
	m_pAtlas = pMaxWave;
}

CMaxWave::~CMaxWave()
{
}

void CMaxWave::tick()
{
}

void CMaxWave::render(HDC _dc)
{
	if (m_pAtlas == nullptr)
		return;

	Vec2 vPos = GetPos();

	TransparentBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, 38, 38
		, m_pAtlas->GetDC()
		, 0
		, 0
		, 38, 38
		, RGB(255, 0, 255));
}

void CMaxWave::BeginOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::PLAYER)
	{
		CPlayer* pPlayer = (CPlayer*)_pOther->GetOwner();

		pPlayer->SetWaveCount(pPlayer->GetMaxWaveCount());

		CSound* pSound = CResMgr::GetInst()->FindSound(L"ItemGet");

		pSound->Play();

		SetDead();
	}
}

void CMaxWave::OnOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::WAVE || _pOther->GetOwner()->ReturnLayer() == LAYER::WAVE_CENTER)
	{
		if (m_AccTime > 0.1f)
			SetDead();
		m_AccTime += DT;
	}
}

void CMaxWave::EndOverlap(CCollider* _pOther)
{
}


