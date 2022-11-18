#include "pch.h"
#include "CNeedle.h"

#include "CCollider.h"
#include "CCollisionMgr.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CSound.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CPlayer2.h"

CNeedle::CNeedle()
	: m_pAtlas(nullptr),
	  m_AccTime(0.f)
{
	CreateCollider();

	GetCollider()->SetOffsetPos(Vec2(15.f, 15.f));
	GetCollider()->SetScale(Vec2(TILE_SIZE - 15.f, TILE_SIZE - 15.f));

	CTexture* pNeedle = CResMgr::GetInst()->LoadTexture(L"NEEDLE", L"Texture\\Item\\Needle.bmp");
	m_pAtlas = pNeedle;
}

CNeedle::~CNeedle()
{
}

void CNeedle::tick()
{
}

void CNeedle::render(HDC _dc)
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

void CNeedle::BeginOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::PLAYER)
	{
		CObj* Check = _pOther->GetOwner();

		if ((dynamic_cast<CPlayer*>(Check)) != nullptr)
		{
			CPlayer* pPlayer = (CPlayer*)_pOther->GetOwner();
			pPlayer->SetItemSlot(ITEM::NEEDLE);
		}

		else
		{
			CPlayer2* pPlayer = (CPlayer2*)_pOther->GetOwner();
			pPlayer->SetItemSlot(ITEM2::NEEDLE);
		}

		CSound* pSound = CResMgr::GetInst()->FindSound(L"ItemGet");

		pSound->Play();

		SetDead();
	}

}

void CNeedle::OnOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::WAVE || _pOther->GetOwner()->ReturnLayer() == LAYER::WAVE_CENTER)
	{
		if (m_AccTime > 0.1f)
			SetDead();
		m_AccTime += DT;
	}
}

void CNeedle::EndOverlap(CCollider* _pOther)
{
}



