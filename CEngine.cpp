#include "pch.h"
#include "CEngine.h"

#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CResMgr.h"
#include "CUIMgr.h"
#include "CSoundMgr.h"

#include "CSound.h"
#include "CTexture.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_hDC(nullptr)
	, m_ptResolution{}
	, m_arrPen{}
	, m_pMemTex(nullptr)
{

}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hDC);

	for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}



void CEngine::init(HWND _hwnd, UINT _iWidth, UINT _iHeight)
{
	m_hMainWnd = _hwnd;
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	// HDC �ʱ�ȭ
	m_hDC = GetDC(m_hMainWnd);

	// ������ ũ�� ����
	ChangeWindowSize(_iWidth, _iHeight);




	// ���� ����ϴ� Pen �� Brush �����ص�
	CreatePenBrush();

	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	// Sound �ε�
	CSoundMgr::GetInst()->init();
	
	CResMgr::GetInst()->LoadSound(L"GameStart", L"Sound\\GameStart.wav");
	CResMgr::GetInst()->LoadSound(L"Bomb", L"Sound\\waterbomb.wav");
	CResMgr::GetInst()->LoadSound(L"ItemGet", L"Sound\\ItemGet.wav");
	CResMgr::GetInst()->LoadSound(L"Main", L"Sound\\MainBGM.wav");
	CResMgr::GetInst()->LoadSound(L"Stage_Patriot", L"Sound\\Stage(Patriot).wav");
	CResMgr::GetInst()->LoadSound(L"Stage_Forest", L"Sound\\Stage(forest).wav");
	CResMgr::GetInst()->LoadSound(L"Stage_Boss", L"Sound\\Boss_Rage1.wav");
	CResMgr::GetInst()->LoadSound(L"Stage_VS", L"Sound\\Stage(VS).wav");
	CResMgr::GetInst()->LoadSound(L"Win", L"Sound\\Win.wav");
	CResMgr::GetInst()->LoadSound(L"Lose1", L"Sound\\Losebgm.wav");
	CResMgr::GetInst()->LoadSound(L"Lose2", L"Sound\\Lose.wav");


	// Level ���۽� Sound�� �������Ͱ� �Ǵ� ���� �����ϱ� ���� LevelMgr�� ���߿� Ȱ��ȭ
	CLevelMgr::GetInst()->init();


}

void CEngine::progress()
{
	// ������ ����
	tick();

	// ȭ�� ������ ����
	render();

	// ���� �����ӿ� ����� �̺�Ʈ ó��
	CEventMgr::GetInst()->tick();
}

void CEngine::tick()
{
	// FPS, DeltaTime ���
	CTimeMgr::GetInst()->tick();

	// Key Event üũ
	CKeyMgr::GetInst()->tick();

	// Level �� ������Ʈ
	CLevelMgr::GetInst()->tick();

	// ������ ���, �浹üũ
	CCollisionMgr::GetInst()->tick();

	// UI �̺�Ʈ üũ
	CUIMgr::GetInst()->tick();
}

void CEngine::render()
{
	// ȭ�� Ŭ����
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// ���� ����
	CLevelMgr::GetInst()->render(m_pMemTex->GetDC());

	// MemBitMap -> MainWindowBitmap
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	// TimeMgr ������
	// CTimeMgr::GetInst()->render();
}

void CEngine::CreatePenBrush()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}


void CEngine::ChangeWindowSize(UINT _iWidth, UINT _iHeight)
{
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;


	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };

	HMENU hMenu = nullptr;
	//HMENU hMenu = GetMenu(m_hMainWnd);

	if (nullptr != hMenu)
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	else
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);


	// ����۰� ������ ����
	if (nullptr == m_pMemTex)
	{
		// ����� �� ��Ʈ�� ����
		m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);
	}

	// ����۰� ������, ����� �ػ󵵿� ���߾� ũ�� ������
	else
	{
		m_pMemTex->Resize(m_ptResolution.x, m_ptResolution.y);
	}
}