#include "pch.h"
#include "CBombPlus.h"

#include "CCollider.h"
#include "CCollisionMgr.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CSound.h"
#include "CTexture.h"
#include "CPlayer.h"

CBombPlus::CBombPlus():
	m_pAtlas(nullptr),
	m_AccTime(0.f)
{
	CreateCollider();

	GetCollider()->SetOffsetPos(Vec2(15.f, 15.f));
	GetCollider()->SetScale(Vec2(TILE_SIZE - 15.f, TILE_SIZE - 15.f));

	CTexture* pBombPlus = CResMgr::GetInst()->LoadTexture(L"BOMBPLUS", L"Texture\\Item\\WaterBomb.bmp");
	m_pAtlas = pBombPlus;
}

CBombPlus::~CBombPlus()
{
}

void CBombPlus::tick()
{

}

void CBombPlus::render(HDC _dc)
{
	if (m_pAtlas == nullptr)
		return;

	Vec2 vPos = GetPos();

	// 한 파일에 여러 타일이 있는 것이 아니라 한 파일 당 한 타일 씩 있으므로
	// 0, 0 지점부터 TILESIZE만큼 출력해야함.

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

void CBombPlus::BeginOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::PLAYER)
	{
		CSound* pSound = CResMgr::GetInst()->FindSound(L"ItemGet");

		pSound->Play();

		CPlayer* pPlayer = (CPlayer*)_pOther->GetOwner();

		pPlayer->SetMaxBombCount(pPlayer->GetMaxBombCount() + 1);
		pPlayer->SetBombCount(pPlayer->GetBombCount() + 1);
		SetDead();
	}
}

void CBombPlus::OnOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::WAVE || _pOther->GetOwner()->ReturnLayer() == LAYER::WAVE_CENTER)
	{
		if (m_AccTime > 0.1f)
			SetDead();
		m_AccTime += DT;
	}
}

void CBombPlus::EndOverlap(CCollider* _pOther)
{

}
