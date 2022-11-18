#include "pch.h"
#include "CMonsterAI.h"

#include "CObj.h"

#include "CMonsterState.h"

CMonsterAI::CMonsterAI(CObj* _pOwner)
	: CComponent(_pOwner),
	  m_mCurState(nullptr)
{
}

CMonsterAI::CMonsterAI(const CMonsterAI& _other) :
	CComponent(_other),
	m_mCurState(nullptr)
{
	map<wstring, CMonsterState*>::const_iterator iter = _other.m_mapState.begin();
	for (; iter != _other.m_mapState.end(); ++iter)
	{
		CMonsterState* pState = iter->second->Clone();;
		pState->m_pOwnerM = this;
		m_mapState.insert(make_pair(iter->first, pState));

		if (iter->second == _other.m_mCurState)
			m_mCurState = pState;
	}
}

CMonsterAI::~CMonsterAI()
{
	map<wstring, CMonsterState*>::iterator iter = m_mapState.begin();
	for (; iter != m_mapState.end(); ++iter)
	{
		DEL(iter->second);
	}
	m_mapState.clear();
}

void CMonsterAI::final_tick()
{
	if (m_mCurState == nullptr)
		return;

	m_mCurState->finaltick();
}

void CMonsterAI::AddState(const wstring& _strKey, CMonsterState* _pState)
{
	m_mapState.insert(make_pair(_strKey, _pState));
	_pState->m_pOwnerM = this;

}

void CMonsterAI::ChangeState(const wstring& _strStateName)
{
	CMonsterState* pNextState = FindState(_strStateName);
	assert(pNextState);

	if (nullptr != m_mCurState)
		m_mCurState->Exit();

	m_mCurState = pNextState;

	m_mCurState->Enter();
}


