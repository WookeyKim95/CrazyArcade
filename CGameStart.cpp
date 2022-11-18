#include "pch.h"
#include "CGameStart.h"

#include "CSound.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"

CGameStart::CGameStart() :
	m_DurationTime(0.f)
{
	CSound* GS_Sound = CResMgr::GetInst()->FindSound(L"GameStart");

	GS_Sound->SetVolume(50.f);
	GS_Sound->SetPosition(0.f);
	GS_Sound->Play();
}

CGameStart::~CGameStart()
{
}

void CGameStart::tick()
{
	m_DurationTime += DT;
	if (m_DurationTime > 2.f)
	{
		Vec2 vPos = GetPos();
		vPos.y -= 480.f * DT;
		SetPos(vPos);
	}

	if (m_DurationTime > START_TIME)
	{
		m_DurationTime = 0;
		SetDead();
	}
}

void CGameStart::render(HDC _dc)
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


