#include "pch.h"
#include "CExitUI.h"
#include "CEngine.h"
#include "CLevel01.h"
#include "CLevel02.h"
#include "CLevel03.h"
#include "CEditorLevel.h"

#include "CLevelMgr.h"
#include "CLevel.h"


CExitUI::CExitUI() :
	m_pFunc(nullptr)
	, m_pInst(nullptr)
	, m_pDelegateFunc(nullptr)
{
}

CExitUI::~CExitUI()
{
}
void CExitUI::tick()
{
	CUI::tick();
}

void CExitUI::render(HDC _dc)
{
	//HPEN hPen = nullptr;

	//hPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	
	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	// DC 의 기존 펜과 브러시를 새로 가져온 것들로 대체한다
	HPEN hOriginPen = (HPEN)SelectObject(_dc, (HPEN)NULL_PEN);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Vec2 vPos = GetPos();

	// 사각형 그리기
	Rectangle(_dc, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + 135.f)
		, (int)(vPos.y + 25.f));


	// DC 의 GDI 오브젝트들을 기존의 펜과 브러시로 되돌린다.
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);
}

void CExitUI::MouseLbtnClicked()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	pCurLevel->GetExit();
}

