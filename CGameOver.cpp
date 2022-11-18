#include "pch.h"
#include "CGameOver.h"

#include "CTimeMgr.h"
#include "CTexture.h"

CGameOver::CGameOver():
	m_DurationTime(0.f)
{
}

CGameOver::~CGameOver()
{
}

void CGameOver::tick()
{
}

void CGameOver::render(HDC _dc)
{
	if (GetIdleTex() == nullptr)
		return;

	Vec2 vPos = GetPos();

	TransparentBlt(_dc, vPos.x, vPos.y
		, GetIdleTex()->Width()
		, GetIdleTex()->Height()
		, GetIdleTex()->GetDC()
		, 0, 0
		, GetIdleTex()->Width()
		, GetIdleTex()->Height()
		, RGB(255, 0, 255));
}


