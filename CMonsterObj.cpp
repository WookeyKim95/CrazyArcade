#include "pch.h"
#include "CMonsterObj.h"

#include "CCollisionMgr.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CLevelMgr.h"
#include "CResMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CWaveCenter.h"

CMonsterObj::CMonsterObj():
	m_DurationTime(0.f)
{
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(40.f, 40.f));
	
	GetAnimator()->LoadAnimation(L"animation\\WAVE_CENTER.anim");

	GetAnimator()->Play(L"WAVE_CENTER", false);
}

CMonsterObj::~CMonsterObj()
{
}

void CMonsterObj::tick()
{
	m_DurationTime += DT;


	if (m_DurationTime > 0.5f)
	{
		SetDead();
		m_DurationTime = 0;
	}
}

void CMonsterObj::render(HDC _dc)
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

void CMonsterObj::BeginOverlap(CCollider* _pOther)
{
}

void CMonsterObj::OnOverlap(CCollider* _pOther)
{
}

void CMonsterObj::EndOverlap(CCollider* _pOther)
{
}


