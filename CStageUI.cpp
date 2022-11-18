#include "pch.h"
#include "CStageUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"

CStageUI::CStageUI()
{
}

CStageUI::~CStageUI()
{
}

void CStageUI::tick()
{
	CUI::tick();
}

void CStageUI::render(HDC _dc)
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
