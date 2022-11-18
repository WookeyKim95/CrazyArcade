#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"

#include "CStartPage.h"
#include "CEditorLevel.h"
#include "CLevel01.h"
#include "CLevel02.h"
#include "CLevel03.h"
#include "CVSLevel.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		DEL(m_arrLevel[i]);
	}
}

void CLevelMgr::init()
{
	// Level 생성
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new CStartPage;
	m_arrLevel[(UINT)LEVEL_TYPE::LEVEL_01] = new CLevel01;
	m_arrLevel[(UINT)LEVEL_TYPE::LEVEL_02] = new CLevel02;
	m_arrLevel[(UINT)LEVEL_TYPE::LEVEL_03] = new CLevel03;
	m_arrLevel[(UINT)LEVEL_TYPE::LEVEL_VS] = new CVSLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CEditorLevel;

	// 초기 레벨 설정
	ChangeLevel(LEVEL_TYPE::START);
}

void CLevelMgr::tick()
{
	m_pCurLevel->tick();
	m_pCurLevel->final_tick();
}

void CLevelMgr::render(HDC _dc)
{
	m_pCurLevel->render(_dc);
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _eNext)
{
	// 현재 레벨과 변경하려는 레벨이 동일 한 경우
	assert(m_pCurLevel != m_arrLevel[(UINT)_eNext]);

	// 현재 레벨을 벗어남
	if (nullptr != m_pCurLevel)
		m_pCurLevel->Exit();

	m_pCurLevel = m_arrLevel[(UINT)_eNext];

	m_pCurLevel->Enter();
}
