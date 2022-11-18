#include "pch.h"
#include "CItem.h"

#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollider.h"
#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CPlayer.h"


CItem::CItem()
	: m_WhoUsed(nullptr)
	, m_pAtlas(nullptr)
{
	CreateCollider();

	GetCollider()->SetOffsetPos(Vec2(15.f, 15.f));
	GetCollider()->SetScale(Vec2(TILE_SIZE - 10.f, TILE_SIZE - 10.f));
}

CItem::~CItem()
{
}

void CItem::tick()
{
}

void CItem::render(HDC _dc)
{
	if (m_pAtlas == nullptr)
		return;

	Vec2 vPos = GetPos();

	// 한 파일에 여러 타일이 있는 것이 아니라 한 파일 당 한 타일 씩 있으므로
	// 0, 0 지점부터 TILESIZE만큼 출력해야함.

	TransparentBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, TILE_SIZE, TILE_SIZE
		, m_pAtlas->GetDC()
		, 0
		, 0
		, TILE_SIZE, TILE_SIZE
		, RGB(255, 0, 255));
}

void CItem::BeginOverlap(CCollider* _pOther)
{
}

void CItem::OnOverlap(CCollider* _pOther)
{
}

void CItem::EndOverlap(CCollider* _pOther)
{

}


