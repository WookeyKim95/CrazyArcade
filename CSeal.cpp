#include "pch.h"
#include "CSeal.h"

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
#include "CSealIdleState.h"
#include "CSealTrappedState.h"
#include "CSealDeadState.h"
#include "CSealHitState.h"
#include "CSealAtkOneState.h"
#include "CSealAtkTwoState.h"
#include "CSealAtkThrStateL.h"
#include "CSealAtkThrStateR.h"

CSeal::CSeal() :
	m_HP(SEAL_FULL_HP),
	m_dir(1),
	m_bTurned(false),
	m_fSpeed(150.f),
	m_bHit(false),
	m_pTex(nullptr),
	m_mCurState(nullptr),
	m_BTrapped(false),
	m_TileCenter(Vec2(0.f, 0.f)),
	m_NowCenTileX(0),
	m_NowCenTileY(0),
	m_HPBar(nullptr),
	m_HPBack(nullptr)
{
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(80.f, 80.f));

	m_HPBar = CResMgr::GetInst()->LoadTexture(L"SEAL_HP", L"Texture\\Monster\\Seal\\HeartBar.bmp");
	m_HPBack = CResMgr::GetInst()->LoadTexture(L"SEAL_HPBACK", L"Texture\\Monster\\Seal\\HeartBar2.bmp");

	CTexture* Walk_Down = CResMgr::GetInst()->LoadTexture(L"SEAL_WD", L"Texture\\Monster\\Seal\\Walk_Down.bmp");
	CTexture* Walk_Left = CResMgr::GetInst()->LoadTexture(L"SEAL_WL", L"Texture\\Monster\\Seal\\Walk_Left.bmp");
	CTexture* Walk_Up = CResMgr::GetInst()->LoadTexture(L"SEAL_WU", L"Texture\\Monster\\Seal\\Walk_Up.bmp");
	CTexture* Walk_Right = CResMgr::GetInst()->LoadTexture(L"SEAL_WR", L"Texture\\Monster\\Seal\\Walk_Right.bmp");
	
	CTexture* Attack_Left = CResMgr::GetInst()->LoadTexture(L"SEAL_AL", L"Texture\\Monster\\Seal\\Attack_Left.bmp");
	CTexture* Attack_Right = CResMgr::GetInst()->LoadTexture(L"SEAL_AR", L"Texture\\Monster\\Seal\\Attack_Right.bmp");
	CTexture* Idle = CResMgr::GetInst()->LoadTexture(L"SEAL_IDLE", L"Texture\\Monster\\Seal\\Idle.bmp");
	CTexture* Shouting = CResMgr::GetInst()->LoadTexture(L"SEAL_SHOUTING", L"Texture\\Monster\\Seal\\Shouting.bmp");
	CTexture* Hitted = CResMgr::GetInst()->LoadTexture(L"SEAL_HITTED", L"Texture\\Monster\\Seal\\Hitted.bmp");
	
	CTexture* Trapped = CResMgr::GetInst()->LoadTexture(L"SEAL_TRAPPED", L"Texture\\Monster\\Seal\\Trapped.bmp");
	CTexture* Dead = CResMgr::GetInst()->LoadTexture(L"SEAL_DEAD", L"Texture\\Monster\\Seal\\Dead.bmp");

	m_pTex = CResMgr::GetInst()->LoadTexture(L"SEAL_WD", L"Texture\\Monster\\Seal\\Monster_Down.bmp");

	/*GetAnimator()->CreateAnimation(L"SEAL_WALK_DOWN", Walk_Down, Vec2(0.f, 0.f), Vec2(92.f, 100.f), Vec2(0.f, 0.f), 2, 0.4f);
	GetAnimator()->CreateAnimation(L"SEAL_WALK_LEFT", Walk_Left, Vec2(0.f, 0.f), Vec2(100.f, 92.f), Vec2(0.f, 0.f), 2, 0.4f);
	GetAnimator()->CreateAnimation(L"SEAL_WALK_UP", Walk_Up, Vec2(0.f, 0.f), Vec2(92.f, 100.f), Vec2(0.f, 0.f), 2, 0.4f);
	GetAnimator()->CreateAnimation(L"SEAL_WALK_RIGHT", Walk_Right, Vec2(0.f, 0.f), Vec2(100.f, 92.f), Vec2(0.f, 0.f), 2, 0.4f);
	
	GetAnimator()->CreateAnimation(L"SEAL_ATTACK_LEFT", Attack_Left, Vec2(0.f, 0.f), Vec2(87.f, 98.f), Vec2(0.f, 0.f), 4, 0.3f);
	GetAnimator()->CreateAnimation(L"SEAL_ATTACK_RIGHT", Attack_Right, Vec2(0.f, 0.f), Vec2(87.f, 98.f), Vec2(0.f, 0.f), 4, 0.3f);
	GetAnimator()->CreateAnimation(L"SEAL_IDLE", Idle, Vec2(0.f, 0.f), Vec2(68.f, 86.f), Vec2(0.f, 0.f), 2, 0.4f);
	GetAnimator()->CreateAnimation(L"SEAL_SHOUTING", Shouting, Vec2(0.f, 0.f), Vec2(110.f, 89.f), Vec2(0.f, 0.f), 2, 0.4f);

	GetAnimator()->CreateAnimation(L"SEAL_HITTED", Hitted, Vec2(0.f, 0.f), Vec2(75.f, 88.f), Vec2(0.f, 0.f), 1, 0.3f);
	GetAnimator()->CreateAnimation(L"SEAL_TRAPPED", Trapped, Vec2(0.f, 0.f), Vec2(96.f, 89.f), Vec2(0.f, 0.f), 2, 0.5f);
	GetAnimator()->CreateAnimation(L"SEAL_DEAD", Dead, Vec2(0.f, 0.f), Vec2(93.f, 84.f), Vec2(0.f, 0.f), 3, 0.4f);

	GetAnimator()->FindAnimation(L"SEAL_WALK_DOWN")->Save(L"animation\\SEAL_WALK_DOWN.anim");
	GetAnimator()->FindAnimation(L"SEAL_WALK_LEFT")->Save(L"animation\\SEAL_WALK_LEFT.anim");
	GetAnimator()->FindAnimation(L"SEAL_WALK_UP")->Save(L"animation\\SEAL_WALK_UP.anim");
	GetAnimator()->FindAnimation(L"SEAL_WALK_RIGHT")->Save(L"animation\\SEAL_WALK_RIGHT.anim");

	GetAnimator()->FindAnimation(L"SEAL_ATTACK_LEFT")->Save(L"animation\\SEAL_ATTACK_LEFT.anim");
	GetAnimator()->FindAnimation(L"SEAL_ATTACK_RIGHT")->Save(L"animation\\SEAL_ATTACK_RIGHT.anim");
	GetAnimator()->FindAnimation(L"SEAL_IDLE")->Save(L"animation\\SEAL_IDLE.anim");
	GetAnimator()->FindAnimation(L"SEAL_SHOUTING")->Save(L"animation\\SEAL_SHOUTING.anim");

	GetAnimator()->FindAnimation(L"SEAL_HITTED")->Save(L"animation\\SEAL_HITTED.anim");
	GetAnimator()->FindAnimation(L"SEAL_TRAPPED")->Save(L"animation\\SEAL_TRAPPED.anim");
	GetAnimator()->FindAnimation(L"SEAL_DEAD")->Save(L"animation\\SEAL_DEAD.anim");*/

	GetAnimator()->LoadAnimation(L"animation\\SEAL_WALK_DOWN.anim");
	GetAnimator()->LoadAnimation(L"animation\\SEAL_WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\SEAL_WALK_UP.anim");
	GetAnimator()->LoadAnimation(L"animation\\SEAL_WALK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\SEAL_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\SEAL_ATTACK_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\SEAL_IDLE.anim");
	GetAnimator()->LoadAnimation(L"animation\\SEAL_SHOUTING.anim");

	GetAnimator()->LoadAnimation(L"animation\\SEAL_HITTED.anim");
	GetAnimator()->LoadAnimation(L"animation\\SEAL_TRAPPED.anim");
	GetAnimator()->LoadAnimation(L"animation\\SEAL_DEAD.anim");


	CreateMonsterAI();


	// AI 설정
	GetMonsterAI()->AddState(L"Seal_Idle", new CSealIdleState);
	GetMonsterAI()->AddState(L"Seal_Trapped", new CSealTrappedState);
	GetMonsterAI()->AddState(L"Seal_Dead", new CSealDeadState);
	GetMonsterAI()->AddState(L"Seal_Hitted", new CSealHitState);
	GetMonsterAI()->AddState(L"Seal_AtkOne", new CSealAtkOneState);
	GetMonsterAI()->AddState(L"Seal_AtkTwo", new CSealAtkTwoState);
	GetMonsterAI()->AddState(L"Seal_AtkThrL", new CSealAtkThrStateL);
	GetMonsterAI()->AddState(L"Seal_AtkThrR", new CSealAtkThrStateR);

	GetMonsterAI()->ChangeState(L"Seal_Idle");

	// 걷는 방향 지정
	//m_dir = rand() % 4;
}

CSeal::~CSeal()
{
	map<wstring, CMonsterState*>::iterator iter = m_mapState.begin();
	for (; iter != m_mapState.end(); ++iter)
	{
		DEL(iter->second);
	}
	m_mapState.clear();
}


void CSeal::tick()
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

void CSeal::render(HDC _dc)
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



	TransparentBlt(_dc
		, (int)(vPos.x - m_HPBack->Width() / 2.f)
		, (int)(vPos.y - 48.f)
		, m_HPBack->Width()
		, m_HPBack->Height()
		, m_HPBack->GetDC()
		, 0
		, 0
		, m_HPBack->Width() / 2
		, m_HPBack->Height() / 2
		, RGB(255, 0, 255));


	TransparentBlt(_dc
		, (int)(vPos.x - m_HPBar->Width() / 2.f)
		, (int)(vPos.y - 50.f)
		, m_HPBar->Width() * m_HP / SEAL_FULL_HP
		, m_HPBar->Height()
		, m_HPBar->GetDC()
		, 0
		, 0
		, m_HPBar->Width() / 2
		, m_HPBar->Height() / 2
		, RGB(255, 0, 255));





	CObj::render(_dc);
}

void CSeal::BeginOverlap(CCollider* _pOther)
{
	Vec2 vPos = GetPos();

	if (_pOther->GetOwner()->ReturnLayer() == LAYER::WAVE || _pOther->GetOwner()->ReturnLayer() == LAYER::WAVE_CENTER)
	{
		if (!m_bHit && m_HP > 0)
		{
			--m_HP;
			m_bHit = true;
			GetMonsterAI()->ChangeState(L"Seal_Hitted");
		}
		

		if (m_HP == 0)
		{
			GetMonsterAI()->ChangeState(L"Seal_Trapped");
			m_BTrapped = true;
		}
	}

	else if (_pOther->GetOwner()->ReturnLayer() == LAYER::PLAYER)
	{
		if (m_BTrapped)
		{
			GetMonsterAI()->ChangeState(L"Seal_Dead");
		}
	}

}

void CSeal::OnOverlap(CCollider* _pOther)
{
}

void CSeal::EndOverlap(CCollider* _pOther)
{

}

