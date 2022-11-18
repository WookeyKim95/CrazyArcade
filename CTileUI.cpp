#include "pch.h"
#include "CTileUI.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "CUI.h"

CTileUI::CTileUI()
	: m_pFunc(nullptr)
	, m_pInst(nullptr)
	, m_pDelegateFunc(nullptr)
{
}

CTileUI::~CTileUI()
{

}

void CTileUI::tick()
{
	CUI::tick();
}

void CTileUI::render(HDC _dc)
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

void CTileUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
		m_pFunc();

	if (m_pInst && m_pDelegateFunc)
	{
		(m_pInst->*m_pDelegateFunc)();
	}
}