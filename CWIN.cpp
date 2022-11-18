#include "pch.h"
#include "CWIN.h"

#include "CTimeMgr.h"
#include "CTexture.h"

CWIN::CWIN():
	m_DurationTime(0.f)
{
}

CWIN::~CWIN()
{
}


void CWIN::tick()
{
}

void CWIN::render(HDC _dc)
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

