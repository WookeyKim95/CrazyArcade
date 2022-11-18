#include "pch.h"
#include "CLOSE.h"

#include "CTimeMgr.h"
#include "CTexture.h"

CLOSE::CLOSE():
	m_DurationTime(0.f)
{
}

CLOSE::~CLOSE()
{
}


void CLOSE::tick()
{
}

void CLOSE::render(HDC _dc)
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

