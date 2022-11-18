#pragma once

// 개체마다 다른 속성을 부여하기 위한 장치.

class CEntity
{
private:
	static UINT	g_iNextID;

private:
	wstring		m_strName;
	const UINT	m_id;

public:
	void SetName(const wstring& _str) { m_strName = _str; }
	const wstring& GetName() { return m_strName; }
	UINT GetID() { return m_id; }

	virtual CEntity* Clone() = 0;

public:
	CEntity();
	CEntity(const CEntity& _Origin);
	virtual ~CEntity();
};

