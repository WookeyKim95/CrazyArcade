#include "pch.h"
#include "COrange.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CResMgr.h"
#include "CLevelMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CMonsterAI.h"
#include "CMonsterState.h"
#include "COrangeIdleState.h"
#include "COrangeDeadState.h"
#include "CObstacle.h"
#include "CBomb.h"

#include "CLevel.h"
#include "CLevel01.h"

COrange::COrange() :
	m_fSpeed(45.f),
	m_mCurState(nullptr),
	m_dir(1), // �ϴ��� �Ʒ���
	m_pTex(nullptr),
	m_TileCenter(Vec2(0.f, 0.f)),
	m_bTurned(false),
	m_NowCenTileX(0),
	m_NowCenTileY(0)
{
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2((float)TILE_SIZE - 6.f, (float)TILE_SIZE - 6.f));

	m_pTex = CResMgr::GetInst()->LoadTexture(L"ORWD", L"Texture\\Monster\\Orange\\Orange_Down.bmp");

	CTexture* mWalk_Down = CResMgr::GetInst()->LoadTexture(L"ORWD", L"Texture\\Monster\\Orange\\Orange_Down.bmp");
	CTexture* mWalk_Left = CResMgr::GetInst()->LoadTexture(L"ORWL", L"Texture\\Monster\\Orange\\Orange_Left.bmp");
	CTexture* mWalk_Up = CResMgr::GetInst()->LoadTexture(L"ORWU", L"Texture\\Monster\\Orange\\Orange_Up.bmp");
	CTexture* mWalk_Right = CResMgr::GetInst()->LoadTexture(L"ORWR", L"Texture\\Monster\\Orange\\Orange_Right.bmp");
	CTexture* m_Dead = CResMgr::GetInst()->LoadTexture(L"ORDEAD", L"Texture\\Monster\\Orange\\Orange_Dead.bmp");

	GetAnimator()->CreateAnimation(L"Orange_WALK_DOWN", mWalk_Down, Vec2(0.f, 0.f), Vec2(30.f, 39.f), Vec2(0.f, 0.f), 2, 0.3f);
	GetAnimator()->CreateAnimation(L"Orange_WALK_LEFT", mWalk_Left, Vec2(0.f, 0.f), Vec2(30.f, 39.f), Vec2(0.f, 0.f), 2, 0.3f);
	GetAnimator()->CreateAnimation(L"Orange_WALK_UP", mWalk_Up, Vec2(0.f, 0.f), Vec2(30.f, 38.f), Vec2(0.f, 0.f), 2, 0.3f);
	GetAnimator()->CreateAnimation(L"Orange_WALK_RIGHT", mWalk_Right, Vec2(0.f, 0.f), Vec2(30.f, 39.f), Vec2(0.f, 0.f), 2, 0.3f);
	GetAnimator()->CreateAnimation(L"Orange_DEAD", m_Dead, Vec2(0.f, 0.f), Vec2(32.f, 37.f), Vec2(0.f, 0.f), 4, 0.3f);


	GetAnimator()->FindAnimation(L"Orange_WALK_DOWN")->Save(L"animation\\Orange_WALK_DOWN.anim");
	GetAnimator()->FindAnimation(L"Orange_WALK_LEFT")->Save(L"animation\\Orange_WALK_LEFT.anim");
	GetAnimator()->FindAnimation(L"Orange_WALK_UP")->Save(L"animation\\Orange_WALK_UP.anim");
	GetAnimator()->FindAnimation(L"Orange_WALK_RIGHT")->Save(L"animation\\Orange_WALK_RIGHT.anim");

	GetAnimator()->FindAnimation(L"Orange_DEAD")->Save(L"animation\\Orange_DEAD.anim");

	GetAnimator()->LoadAnimation(L"animation\\Orange_WALK_DOWN.anim");
	GetAnimator()->LoadAnimation(L"animation\\Orange_WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Orange_WALK_UP.anim");
	GetAnimator()->LoadAnimation(L"animation\\Orange_WALK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Orange_DEAD.anim");


	CreateMonsterAI();


	// AI ����
	GetMonsterAI()->AddState(L"Orange_Idle", new COrangeIdleState);
	GetMonsterAI()->AddState(L"Orange_Dead", new COrangeDeadState);

	GetMonsterAI()->ChangeState(L"Orange_Idle");

	// �ȴ� ���� ����
	m_dir = rand() % 4;
}

COrange::COrange(const COrange& _other)
	: CObj(_other)
	, m_fSpeed(_other.m_fSpeed)
	, m_dir(1)
	, m_mCurState(nullptr)
	, m_pTex(_other.m_pTex)
	, m_TileCenter(Vec2(0.f, 0.f))
	, m_bTurned(false)
	, m_NowCenTileX(0)
	, m_NowCenTileY(0)
{
	GetMonsterAI()->ChangeState(L"Orange_Idle");

	m_dir = rand() % 4;
}

COrange::~COrange()
{
	map<wstring, CMonsterState*>::iterator iter = m_mapState.begin();
	for (; iter != m_mapState.end(); ++iter)
	{
		DEL(iter->second);
	}
	m_mapState.clear();
}


void COrange::tick()
{
	Vec2 vPos = GetPos();

	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 13; ++j)
		{
			Vec2 Candi_TileCenter = { 20.f + TILE_SIZE / 2 + TILE_SIZE * i
									, 40.f + TILE_SIZE / 2 + TILE_SIZE * j };
			if ((abs(vPos.x - m_TileCenter.x) > abs(vPos.x - Candi_TileCenter.x)))
			{
				m_TileCenter.x = Candi_TileCenter.x;
				m_NowCenTileX = i;
			}

			if ((abs(vPos.y - m_TileCenter.y) > abs(vPos.y - Candi_TileCenter.y)))
			{
				m_TileCenter.y = Candi_TileCenter.y;
				m_NowCenTileY = j;
			}

		}
	}
}

void COrange::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetScale();

	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(0);

	AlphaBlend(_dc
		, (int)(vPos.x - m_pTex->Width() / 2.f)
		, (int)(vPos.y - m_pTex->Height() / 2.f)
		, m_pTex->Width()
		, m_pTex->Height()
		, m_pTex->GetDC()
		, 0, 0
		, m_pTex->Width()
		, m_pTex->Height()
		, tBlend);

	CObj::render(_dc);
}

void COrange::BeginOverlap(CCollider* _pOther)
{
	Vec2 vPos = GetPos();

	if (_pOther->GetOwner()->ReturnLayer() == LAYER::WAVE || _pOther->GetOwner()->ReturnLayer() == LAYER::WAVE_CENTER)
	{
		GetMonsterAI()->ChangeState(L"Orange_Dead");
	}

	else if (_pOther->GetOwner()->ReturnLayer() == LAYER::OBSTACLE)
	{
		CObstacle* pObstacle = (CObstacle*)_pOther->GetOwner();
		Vec2 ObsPos = pObstacle->GetPos();
		if (pObstacle->GetObstacle() || pObstacle->GetAbsObstacle()) // ��ֹ��� ������ ������ȯ
		{
			int dice = rand() % 3;

			if (0 < vPos.y - ObsPos.y && vPos.y - ObsPos.y < (3.f * TILE_SIZE / 2.f)) // ���ʿ� ����� ���� ��� m_dir = 0
			{
				if (dice == 0)
					m_dir = 2;
				else if (dice == 1)
					m_dir = 3;
				else
					m_dir = 1;
			}

			else if (0 < ObsPos.y - vPos.y && ObsPos.y - vPos.y < (TILE_SIZE / 2.f)) // �Ʒ��ʿ� ����� ���� ��� m_dir = 1
			{
				if (dice == 0)
					m_dir = 2;
				else if (dice == 1)
					m_dir = 3;
				else
					m_dir = 0;

			}
			else if (0 < vPos.x - ObsPos.x && vPos.x - ObsPos.x < (3.f * TILE_SIZE / 2.f)) // ���ʿ� ����� ���� ��� m_dir = 2
			{
				if (dice == 0)
					m_dir = 0;
				else if (dice == 1)
					m_dir = 1;
				else
					m_dir = 3;
			}

			else if (0 < ObsPos.x - vPos.x && ObsPos.x - vPos.x < (TILE_SIZE / 2.f)) // �����ʿ� ����� ���� ��� m_dir = 3
			{
				if (dice == 0)
					m_dir = 0;
				else if (dice == 1)
					m_dir = 1;
				else
					m_dir = 2;
			}
			SetPos(m_TileCenter);
			m_bTurned = false;
		}
	}

	else if (_pOther->GetOwner()->ReturnLayer() == LAYER::BOMB)
	{

/*		CBomb* pObstacle = (CBomb*)_pOther->GetOwner();
		Vec2 ObsPos = pObstacle->GetPos()*/;

		int dice = rand() % 3;

		if (m_dir == 0) // ���ʿ� ��ź�� ���� ��� m_dir = 0
		{
			if (dice == 0)
				m_dir = 2;
			else if (dice == 1)
				m_dir = 3;
			else
				m_dir = 1;
		}

		else if (m_dir == 1) // �Ʒ��ʿ� ��ź�� ���� ��� m_dir = 1
		{
			if (dice == 0)
				m_dir = 2;
			else if (dice == 1)
				m_dir = 3;
			else
				m_dir = 0;

		}
		else if (m_dir == 2) // ���ʿ� ��ź�� ���� ��� m_dir = 2
		{
			if (dice == 0)
				m_dir = 0;
			else if (dice == 1)
				m_dir = 1;
			else
				m_dir = 3;
		}

		else if (m_dir == 3) // �����ʿ� ��ź�� ���� ��� m_dir = 3
		{
			if (dice == 0)
				m_dir = 0;
			else if (dice == 1)
				m_dir = 1;
			else
				m_dir = 2;

		}
		SetPos(m_TileCenter);
		m_bTurned = false;
	}
}

void COrange::OnOverlap(CCollider* _pOther)
{
}

void COrange::EndOverlap(CCollider* _pOther)
{
}

