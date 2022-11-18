#include "pch.h"
#include "CPlayerState.h"

#include "CEventMgr.h"

CPlayerState::CPlayerState()
	: m_pOwnerP(nullptr)
{
}

CPlayerState::~CPlayerState()
{
}

void CPlayerState::ChangeState(const wchar_t* _strStateName)
{
	tEvent evn = {};

	evn.eType = EVENT_TYPE::CHANGE_PLAYER_STATE;
	evn.wParam = (DWORD_PTR)GetOwnerPlayer();
	evn.lParam = (DWORD_PTR)_strStateName;

	CEventMgr::GetInst()->AddEvent(evn);
}