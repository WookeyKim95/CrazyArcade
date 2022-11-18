#include "pch.h"
#include "CVsMode.h"

#include "CKeyMgr.h"
#include "CTexture.h"

CVsMode::CVsMode() :
	  m_pFunc(nullptr)
	, m_pInst(nullptr)
	, m_pDelegateFunc(nullptr)
{
}

CVsMode::~CVsMode()
{
}
void CVsMode::tick()
{
	CUI::tick();
}

void CVsMode::render(HDC _dc)
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

void CVsMode::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
		m_pFunc();

	if (m_pInst && m_pDelegateFunc)
	{
		(m_pInst->*m_pDelegateFunc)();
	}
}

