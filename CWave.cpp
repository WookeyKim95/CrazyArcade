#include "pch.h"

#include "CCollisionMgr.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CLevelMgr.h"
#include "CResMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CWaveCenter.h"
#include "CWave.h"
#include "CObstacle.h"
#include "CBox_Break.h"

#include "CLevel01.h"

CWave::CWave(int _WaveCount, int _Dir) :
	m_DurationTime(0),
	m_WaveCount(_WaveCount),
	m_Dir(_Dir),
	m_BOOM(false),
	m_MoreBOOM(false),
	m_AniPlay(true)
{
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f)); // 충돌체 위치 조정
	GetCollider()->SetScale(Vec2((float)TILE_SIZE - 20.f, (float)TILE_SIZE - 20.f)); // 파도의 충돌체는 조금 더 작게

	SetWaveDir(_Dir);
	SetWaveCount(_WaveCount);

	// Animator 에서 사용할 Image 로딩

	//CTexture* pWaveUp = CResMgr::GetInst()->LoadTexture(L"WaveUp", L"Texture\\Flow\\Flow_Up.bmp");
	//GetAnimator()->CreateAnimation(L"WAVE_UP", pWaveUp, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 4, 0.125f);
	//GetAnimator()->FindAnimation(L"WAVE_UP")->Save(L"animation\\WAVE_UP.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_UP.anim");
	//CTexture* pWaveUpM = CResMgr::GetInst()->LoadTexture(L"WaveUpM", L"Texture\\Flow\\Flow_UpM.bmp");
	//GetAnimator()->CreateAnimation(L"WAVE_UPM", pWaveUpM, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 4, 0.125f);
	//GetAnimator()->FindAnimation(L"WAVE_UPM")->Save(L"animation\\WAVE_UPM.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_UPM.anim");

	//CTexture* pWaveDown = CResMgr::GetInst()->LoadTexture(L"WaveDown", L"Texture\\Flow\\Flow_Down.bmp");
	//GetAnimator()->CreateAnimation(L"WAVE_DOWN", pWaveDown, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 4, 0.125f);
	//GetAnimator()->FindAnimation(L"WAVE_DOWN")->Save(L"animation\\WAVE_DOWN.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_DOWN.anim");

	//CTexture* pWaveDownM = CResMgr::GetInst()->LoadTexture(L"WaveDownM", L"Texture\\Flow\\Flow_DownM.bmp");
	//GetAnimator()->CreateAnimation(L"WAVE_DOWNM", pWaveDownM, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 4, 0.125f);
	//GetAnimator()->FindAnimation(L"WAVE_DOWNM")->Save(L"animation\\WAVE_DOWNM.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_DOWNM.anim");

		
	//CTexture* pWaveLeft = CResMgr::GetInst()->LoadTexture(L"WaveLeft", L"Texture\\Flow\\Flow_Left.bmp");
	//GetAnimator()->CreateAnimation(L"WAVE_LEFT", pWaveLeft, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 4, 0.125f);
	//GetAnimator()->FindAnimation(L"WAVE_LEFT")->Save(L"animation\\WAVE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_LEFT.anim");

	//CTexture* pWaveLeftM = CResMgr::GetInst()->LoadTexture(L"WaveLeftM", L"Texture\\Flow\\Flow_LeftM.bmp");
	//GetAnimator()->CreateAnimation(L"WAVE_LEFTM", pWaveLeftM, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 4, 0.125f);
	//GetAnimator()->FindAnimation(L"WAVE_LEFTM")->Save(L"animation\\WAVE_LEFTM.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_LEFTM.anim");
		


	//CTexture* pWaveRight = CResMgr::GetInst()->LoadTexture(L"WaveRight", L"Texture\\Flow\\Flow_Right.bmp");
	//GetAnimator()->CreateAnimation(L"WAVE_RIGHT", pWaveRight, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 4, 0.125f);
	//GetAnimator()->FindAnimation(L"WAVE_RIGHT")->Save(L"animation\\WAVE_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_RIGHT.anim");
	//CTexture* pWaveRightM = CResMgr::GetInst()->LoadTexture(L"WaveRightM", L"Texture\\Flow\\Flow_RightM.bmp");
	//GetAnimator()->CreateAnimation(L"WAVE_RIGHTM", pWaveRightM, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 4, 0.125f);
	//GetAnimator()->FindAnimation(L"WAVE_RIGHTM")->Save(L"animation\\WAVE_RIGHTM.anim");
	GetAnimator()->LoadAnimation(L"animation\\WAVE_RIGHTM.anim");

}

CWave::CWave(const CWave& _other, int _WaveCount, int _Dir) :
	m_DurationTime(0),
	m_AniPlay(_other.m_AniPlay),
	m_BOOM(false),
	m_MoreBOOM(false),
	m_WaveCount(_other.m_WaveCount),
	m_Dir(_other.m_Dir)
{
}

CWave::~CWave()
{
}

void CWave::tick()
{
	
	m_DurationTime += DT;

	if (m_DurationTime > 0.5f)
	{
		SetDead();
		m_DurationTime = 0;
	}
}

void CWave::render(HDC _dc)
{

	CObj::render(_dc);
}

void CWave::BeginOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::OBSTACLE)
	{
		CObstacle* pObstacle = (CObstacle*)_pOther->GetOwner();
		if (pObstacle->GetObstacle() == false)
		{
			m_MoreBOOM = true;
		}

		if (pObstacle->GetAbsObstacle() == true)
		{
			m_MoreBOOM = false;
		}

		if (!m_BOOM) // 터지는 작업은 0.5초 중 1번만 일어나야 하므로 m_BOOM으로 검사.
		{
			if (m_WaveCount > 1 && m_MoreBOOM)
			{
				CWave* pWave = Clone();
				pWave->SetWaveCount(GetWaveCount() - 1);
				pWave->SetWaveDir(GetWaveDir());
				pWave->SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
				pWave->SetMoreBOOM(false); // 우선 false로 설정

				if (m_Dir == 0) // 상
					Instantiate(pWave, Vec2(GetPos().x, GetPos().y - TILE_SIZE), LAYER::WAVE);
				else if (m_Dir == 1) // 하
					Instantiate(pWave, Vec2(GetPos().x, GetPos().y + TILE_SIZE), LAYER::WAVE);
				else if (m_Dir == 2) // 좌
					Instantiate(pWave, Vec2(GetPos().x - TILE_SIZE, GetPos().y), LAYER::WAVE);
				else if (m_Dir == 3) // 우
					Instantiate(pWave, Vec2(GetPos().x + TILE_SIZE, GetPos().y), LAYER::WAVE);
				m_BOOM = true;

			}
		}

		Vec2 ObsPos = pObstacle->GetPos();
		if (pObstacle->GetAbsObstacle() == true ||!(20.f <= ObsPos.x && ObsPos.x <= 620.f && 40.f <= ObsPos.y && ObsPos.y <= 560.f))
		{
			m_AniPlay = false;
		}

		if (m_AniPlay == true)
		{
			int _Dir = GetWaveDir();
			int _WaveCount = GetWaveCount();
			// Animator 에서 사용할 Image 로딩
			if (_Dir == 0) // 상
			{
				if (_WaveCount == 1)
				{
					GetAnimator()->Play(L"WAVE_UP", false);
				}
				else if (_WaveCount > 1)
				{
					GetAnimator()->Play(L"WAVE_UPM", false);
				}
			}

			else if (_Dir == 1) // 하
			{
				if (_WaveCount == 1)
				{
					GetAnimator()->Play(L"WAVE_DOWN", false);
				}
				else if (_WaveCount > 1)
				{
					GetAnimator()->Play(L"WAVE_DOWNM", false);
				}
			}

			else if (_Dir == 2) // 좌
			{
				if (_WaveCount == 1)
				{
					GetAnimator()->Play(L"WAVE_LEFT", false);
				}
				else if (_WaveCount > 1)
				{
					GetAnimator()->Play(L"WAVE_LEFTM", false);
				}
			}

			else if (_Dir == 3) // 우
			{
				if (_WaveCount == 1)
				{
					GetAnimator()->Play(L"WAVE_RIGHT", false);
				}
				else if (_WaveCount > 1)
				{
					GetAnimator()->Play(L"WAVE_RIGHTM", false);
				}
			}
		}
	}

	

}

void CWave::OnOverlap(CCollider* _pOther)
{

}

void CWave::EndOverlap(CCollider* _pOther)
{
}


