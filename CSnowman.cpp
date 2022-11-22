#include "pch.h"
#include "CSnowman.h"

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
#include "CSmanDeadState.h"
#include "CSmanIdleState.h"
#include "CSmanTrappedState.h"
#include "CObstacle.h"
#include "CBomb.h"

#include "CLevel.h"
#include "CLevel03.h"

CSnowman::CSnowman():
	m_BTrapped(false),
	m_bTurned(false),
	m_dir(0),
	m_fSpeed(45.f),
	m_mCurState(nullptr),
	m_NowCenTileX(0),
	m_NowCenTileY(0),
	m_TileCenter(Vec2(0.f, 0.f)),
	m_pTex(nullptr)
{
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2((float)TILE_SIZE - 6.f, (float)TILE_SIZE - 6.f));

	m_pTex = CResMgr::GetInst()->LoadTexture(L"SMWD", L"Texture\\Monster\\SnowMan_1\\SnowMan_Down.bmp");

	CTexture* mWalk_Down = CResMgr::GetInst()->LoadTexture(L"SMWD", L"Texture\\Monster\\SnowMan_1\\SnowMan_Down.bmp");
	CTexture* mWalk_Left = CResMgr::GetInst()->LoadTexture(L"SMWL", L"Texture\\Monster\\SnowMan_1\\SnowMan_Left.bmp");
	CTexture* mWalk_Up = CResMgr::GetInst()->LoadTexture(L"SMWU", L"Texture\\Monster\\SnowMan_1\\SnowMan_Up.bmp");
	CTexture* mWalk_Right = CResMgr::GetInst()->LoadTexture(L"SMWR", L"Texture\\Monster\\SnowMan_1\\SnowMan_Right.bmp");
	CTexture* m_Dead = CResMgr::GetInst()->LoadTexture(L"SMDEAD", L"Texture\\Monster\\SnowMan_1\\SnowMan_Dead.bmp");
	CTexture* m_Trapped = CResMgr::GetInst()->LoadTexture(L"SMTRAPPED", L"Texture\\Monster\\SnowMan_1\\SnowMan_Trapped.bmp");

	GetAnimator()->CreateAnimation(L"SM_WALK_DOWN", mWalk_Down, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 2, 0.3f);
	GetAnimator()->CreateAnimation(L"SM_WALK_LEFT", mWalk_Left, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 2, 0.3f);
	GetAnimator()->CreateAnimation(L"SM_WALK_UP", mWalk_Up, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 2, 0.3f);
	GetAnimator()->CreateAnimation(L"SM_WALK_RIGHT", mWalk_Right, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 2, 0.3f);
	GetAnimator()->CreateAnimation(L"SM_DEAD", m_Dead, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 4, 0.3f);
	GetAnimator()->CreateAnimation(L"SM_TRAPPED", m_Trapped, Vec2(0.f, 0.f), Vec2(40.f, 40.f), Vec2(0.f, 0.f), 1, 0.3f);


	GetAnimator()->FindAnimation(L"SM_WALK_DOWN")->Save(L"animation\\SM_WALK_DOWN.anim");
	GetAnimator()->FindAnimation(L"SM_WALK_LEFT")->Save(L"animation\\SM_WALK_LEFT.anim");
	GetAnimator()->FindAnimation(L"SM_WALK_UP")->Save(L"animation\\SM_WALK_UP.anim");
	GetAnimator()->FindAnimation(L"SM_WALK_RIGHT")->Save(L"animation\\SM_WALK_RIGHT.anim");

	GetAnimator()->FindAnimation(L"SM_DEAD")->Save(L"animation\\SM_DEAD.anim");
	GetAnimator()->FindAnimation(L"SM_TRAPPED")->Save(L"animation\\SM_TRAPPED.anim");

	//GetAnimator()->LoadAnimation(L"animation\\SM_WALK_LEFT.anim");
	//GetAnimator()->LoadAnimation(L"animation\\SM_WALK_UP.anim");
	//GetAnimator()->LoadAnimation(L"animation\\SM_WALK_DOWN.anim");
	//GetAnimator()->LoadAnimation(L"animation\\SM_WALK_RIGHT.anim");

	//GetAnimator()->LoadAnimation(L"animation\\SM_DEAD.anim");
	//GetAnimator()->LoadAnimation(L"animation\\SM_TRAPPED.anim");

	CreateMonsterAI();


	// AI 설정
	GetMonsterAI()->AddState(L"Snowman_Idle", new CSmanIdleState);
	GetMonsterAI()->AddState(L"Snowman_Trapped", new CSmanTrappedState);
	GetMonsterAI()->AddState(L"Snowman_Dead", new CSmanDeadState);

	GetMonsterAI()->ChangeState(L"Snowman_Idle");

	// 걷는 방향 지정
	m_dir = rand() % 4;
}

CSnowman::CSnowman(const CSnowman& _other) :
	m_BTrapped(false),
	m_bTurned(false),
	m_dir(0),
	m_fSpeed(45.f),
	m_mCurState(nullptr),
	m_NowCenTileX(0),
	m_NowCenTileY(0),
	m_TileCenter(Vec2(0.f, 0.f)),
	m_pTex(nullptr)
{
	GetMonsterAI()->ChangeState(L"Snowman_Idle");

	m_dir = rand() % 4;
}

CSnowman::~CSnowman()
{
	map<wstring, CMonsterState*>::iterator iter = m_mapState.begin();
	for (; iter != m_mapState.end(); ++iter)
	{
		DEL(iter->second);
	}
	m_mapState.clear();
}
void CSnowman::tick()
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

	CObj::tick();
}

void CSnowman::render(HDC _dc)
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

void CSnowman::BeginOverlap(CCollider* _pOther)
{
	Vec2 vPos = GetPos();

	if (_pOther->GetOwner()->ReturnLayer() == LAYER::WAVE || _pOther->GetOwner()->ReturnLayer() == LAYER::WAVE_CENTER)
	{
		m_BTrapped = true;
		GetMonsterAI()->ChangeState(L"Snowman_Trapped");
	}

	if (_pOther->GetOwner()->ReturnLayer() == LAYER::PLAYER && m_BTrapped == true)
	{
		GetMonsterAI()->ChangeState(L"Snowman_Dead");
	}

	else if (_pOther->GetOwner()->ReturnLayer() == LAYER::OBSTACLE)
	{
		CObstacle* pObstacle = (CObstacle*)_pOther->GetOwner();
		Vec2 ObsPos = pObstacle->GetPos();
		if (pObstacle->GetObstacle() || pObstacle->GetAbsObstacle()) // 장애물을 만나면 방향전환
		{
			int dice = rand() % 3;

			if (0 < vPos.y - ObsPos.y && vPos.y - ObsPos.y < (3.f * TILE_SIZE / 2.f)) // 위쪽에 블록이 있을 경우 m_dir = 0
			{
				if (dice == 0)
					m_dir = 2;
				else if (dice == 1)
					m_dir = 3;
				else
					m_dir = 1;
			}

			else if (0 < ObsPos.y - vPos.y && ObsPos.y - vPos.y < (TILE_SIZE / 2.f)) // 아래쪽에 블록이 있을 경우 m_dir = 1
			{
				if (dice == 0)
					m_dir = 2;
				else if (dice == 1)
					m_dir = 3;
				else
					m_dir = 0;

			}
			else if (0 < vPos.x - ObsPos.x && vPos.x - ObsPos.x < (3.f * TILE_SIZE / 2.f)) // 왼쪽에 블록이 있을 경우 m_dir = 2
			{
				if (dice == 0)
					m_dir = 0;
				else if (dice == 1)
					m_dir = 1;
				else
					m_dir = 3;
			}

			else if (0 < ObsPos.x - vPos.x && ObsPos.x - vPos.x < (TILE_SIZE / 2.f)) // 오른쪽에 블록이 있을 경우 m_dir = 3
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

		CBomb* pObstacle = (CBomb*)_pOther->GetOwner();
		Vec2 ObsPos = pObstacle->GetPos();

		int dice = rand() % 3;

		if (m_dir == 0) // 위쪽에 블록이 있을 경우 m_dir = 0
		{
			if (dice == 0)
				m_dir = 2;
			else if (dice == 1)
				m_dir = 3;
			else
				m_dir = 1;
		}

		else if (m_dir == 1) // 아래쪽에 블록이 있을 경우 m_dir = 1
		{
			if (dice == 0)
				m_dir = 2;
			else if (dice == 1)
				m_dir = 3;
			else
				m_dir = 0;

		}
		else if (m_dir == 2) // 왼쪽에 블록이 있을 경우 m_dir = 2
		{
			if (dice == 0)
				m_dir = 0;
			else if (dice == 1)
				m_dir = 1;
			else
				m_dir = 3;
		}

		else if (m_dir == 3) // 오른쪽에 블록이 있을 경우 m_dir = 3
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

void CSnowman::OnOverlap(CCollider* _pOther)
{
}

void CSnowman::EndOverlap(CCollider* _pOther)
{
}

