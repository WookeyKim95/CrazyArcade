#include "pch.h"
#include "CItemUI.h"

#include "CResMgr.h"
#include "CTexture.h"


#include "CItem.h"
#include "CPlayer.h"


CItemUI::CItemUI(CPlayer* _who)
	: m_ItemAtlas{nullptr}
{
	m_WhoUse = _who;

	CTexture* pNeedle = CResMgr::GetInst()->LoadTexture(L"NEEDLE", L"Texture\\Item\\Needle.bmp");
	m_ItemAtlas[1] = pNeedle;
	
}

CItemUI::~CItemUI()
{
}

void CItemUI::tick()
{
	if (m_WhoUse->GetItemSlot() == ITEM::NONE)
		m_pAtlas = nullptr;

	else if (m_WhoUse->GetItemSlot() == ITEM::NEEDLE)
	{
		m_pAtlas = m_ItemAtlas[(UINT)ITEM::NEEDLE];
	}
}

void CItemUI::render(HDC _dc)
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