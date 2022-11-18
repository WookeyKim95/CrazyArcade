#include "pch.h"
#include "CBackGroundUI.h"

#include "CTimeMgr.h"
#include "CTexture.h"

CBackGroundUI::CBackGroundUI()
{
}

CBackGroundUI::~CBackGroundUI()
{
}

void CBackGroundUI::tick()
{
	CUI::tick();
}

void CBackGroundUI::render(HDC _dc)
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

	render_childUI(_dc);
}

