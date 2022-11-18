#include "pch.h"
#include "CStartPage.h"

#include "CEngine.h"
#include "CPathMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"

#include "CObj.h"
#include "CBackGroundUI.h"
#include "CNormalMode.h"
#include "CVsMode.h"

#include "CItemUI.h"
#include "CSound.h"


#include "CResMgr.h"
#include "CKeyMgr.h"

CStartPage::CStartPage()
{	
}

CStartPage::~CStartPage()
{
}

void CStartPage::init()
{
	CTexture* pStartBack = CResMgr::GetInst()->LoadTexture(L"STARTBACK", L"Texture\\Stage\\MainPage.bmp");

	CBackGroundUI* pPageUI = new CBackGroundUI;
	pPageUI->SetIdleTex(pStartBack);
	pPageUI->SetPos(Vec2(0.f, 0.f));
	AddObject(pPageUI, LAYER::UI);



	CTexture* pNormalModeUI = CResMgr::GetInst()->LoadTexture(L"NORMALMODE", L"Texture\\UI\\NormalMode.bmp");

	CNormalMode* pNormalMode = new CNormalMode;
	pNormalMode->SetIdleTex(pNormalModeUI);
	pNormalMode->SetDelegate(this, (DELEGATE)&CStartPage::ChangeToNormalMode);
	pNormalMode->SetPos(Vec2(160.f, 80.f));
	pPageUI->AddChildUI(pNormalMode);



	CTexture* pVSModeUI = CResMgr::GetInst()->LoadTexture(L"VSMODE", L"Texture\\UI\\vsMode.bmp");

	CVsMode* pVSMode = new CVsMode;
	pVSMode->SetIdleTex(pVSModeUI);
	pVSMode->SetPos(Vec2(460.f, 80.f));
	pVSMode->SetDelegate(this, (DELEGATE)&CStartPage::ChangeToVSMode);
	pPageUI->AddChildUI(pVSMode);


	BGM = CResMgr::GetInst()->FindSound(L"Main");

	BGM->SetPosition(0.f);
	BGM->SetVolume(50.f);
	BGM->Play(true);
}

void CStartPage::tick()
{
	CLevel::tick();

	if (IsTap(KEY::_1))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	else if (IsTap(KEY::_2))
	{
		ChangeToNormalMode();
	}
}

void CStartPage::Enter()
{
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);

	init();
}

void CStartPage::Exit()
{
	BGM->Stop();
}


