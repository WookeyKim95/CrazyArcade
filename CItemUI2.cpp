#include "pch.h"
#include "CItemUI2.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CItem.h"
#include "CPlayer2.h"


CItemUI2::CItemUI2(CPlayer2* _who)
	: m_ItemAtlas{ nullptr }
{
	m_WhoUse = _who;

	CTexture* pNeedle = CResMgr::GetInst()->LoadTexture(L"NEEDLE", L"Texture\\Item\\Needle.bmp");
	m_ItemAtlas[1] = pNeedle;
}

CItemUI2::~CItemUI2()
{
}

void CItemUI2::tick()
{
	if (m_WhoUse->GetItemSlot() == ITEM2::NONE)
		m_pAtlas = nullptr;

	else if (m_WhoUse->GetItemSlot() == ITEM2::NEEDLE)
	{
		m_pAtlas = m_ItemAtlas[(UINT)ITEM2::NEEDLE];
	}
}

void CItemUI2::render(HDC _dc)
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
