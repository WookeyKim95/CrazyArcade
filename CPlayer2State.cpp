#include "pch.h"
#include "CPlayer2State.h"

#include "CEventMgr.h"

CPlayer2State::CPlayer2State()
	: m_pOwnerP(nullptr)
{
}

CPlayer2State::~CPlayer2State()
{
}

void CPlayer2State::ChangeState(const wchar_t* _strStateName)
{
	tEvent evn = {};

	evn.eType = EVENT_TYPE::CHANGE_PLAYER_STATE;
	evn.wParam = (DWORD_PTR)GetOwnerPlayer();
	evn.lParam = (DWORD_PTR)_strStateName;

	CEventMgr::GetInst()->AddEvent(evn);
}


