#include "pch.h"
#include "CMonsterState.h"

#include "CEventMgr.h"

CMonsterState::CMonsterState()
	: m_pOwnerM(nullptr)
{
}

CMonsterState::~CMonsterState()
{
}

void CMonsterState::ChangeState(const wchar_t* _strStateName)
{
	tEvent evn = {};

	evn.eType = EVENT_TYPE::CHANGE_MONSTER_STATE;
	evn.wParam = (DWORD_PTR)GetOwnerMonsterAI();
	evn.lParam = (DWORD_PTR)_strStateName;

	CEventMgr::GetInst()->AddEvent(evn);
}


