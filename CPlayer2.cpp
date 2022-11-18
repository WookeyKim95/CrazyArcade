#include "pch.h"
#include "CPlayer2.h"

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

#include "CP2ReadyState.h"
#include "CPlayer2State.h"
#include "CP2TrappedState.h"
#include "CP2IdleState.h"
#include "CP2DeadState.h"
#include "CP2ReviveState.h"

#include "CTile.h"
#include "CLevel.h"
#include "CLevel01.h"
#include "CBomb.h"
#include "CObstacle.h"
#include "CItem.h"
#include "CNeedle.h"
#include "CItemUI2.h"

CPlayer2::CPlayer2()
	: m_fSpeed(100.f)
	, m_pSpeed(100.f)
	, m_KickAccTime(0.f)
	, m_BombCount(1) // 현재 놓을 수 있는 물풍선의 개수
	, m_MaxBombCount(1) // 놓을 수 있는 물풍선의 최대 개수 (물풍선 아이템으로 증가)
	, m_BKick(false)
	, m_TileCenter(Vec2(0.f, 0.f))
	, CanMove{ true, true, true, true }
	, m_WaveCount(1)
	, m_MaxWaveCount(7)
	, m_BombFirst(true)
	, m_CanSetBomb(true)
	, m_pCurState(nullptr)
	, m_BTrapped(false)
	, m_Slot(ITEM2::NONE)
	, m_Life(2)
	, m_PowerOverwhelming(false)
{
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(TILE_SIZE - 20.f, TILE_SIZE - 20.f));

	// Animator 에서 사용할 Image 로딩

	//CTexture* pReady = CResMgr::GetInst()->LoadTexture(L"P2READY", L"Texture\\Player2\\Player2_Ready.bmp");
	//GetAnimator()->CreateAnimation(L"P2READY", pReady, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, -10.f), 6, 0.33f);
	//GetAnimator()->FindAnimation(L"P2READY")->Save(L"animation\\P2READY.anim");

	//CTexture* pWalk_Down = CResMgr::GetInst()->LoadTexture(L"P2WD", L"Texture\\Player2\\Player2_Down.bmp");
	//CTexture* pWalk_Left = CResMgr::GetInst()->LoadTexture(L"P2WL", L"Texture\\Player2\\Player2_Left.bmp");
	//CTexture* pWalk_Up = CResMgr::GetInst()->LoadTexture(L"P2WU", L"Texture\\Player2\\Player2_Up.bmp");
	//CTexture* pWalk_Right = CResMgr::GetInst()->LoadTexture(L"P2WR", L"Texture\\Player2\\Player2_Right.bmp");

	//CTexture* pIdle_Down = CResMgr::GetInst()->LoadTexture(L"P2ID", L"Texture\\Player2\\Player2_Idle_Down.bmp");
	//CTexture* pIdle_Left = CResMgr::GetInst()->LoadTexture(L"P2IL", L"Texture\\Player2\\Player2_Idle_Left.bmp");
	//CTexture* pIdle_Up = CResMgr::GetInst()->LoadTexture(L"P2IU", L"Texture\\Player2\\Player2_Idle_Up.bmp");
	//CTexture* pIdle_Right = CResMgr::GetInst()->LoadTexture(L"P2IR", L"Texture\\Player2\\Player2_Idle_Right.bmp");

	//CTexture* pTrapped = CResMgr::GetInst()->LoadTexture(L"P2Trapped", L"Texture\\Player2\\Player2_Trapped.bmp");
	//CTexture* pRevival = CResMgr::GetInst()->LoadTexture(L"P2Revival", L"Texture\\Player2\\Player2_Revival.bmp");
	//CTexture* pDead = CResMgr::GetInst()->LoadTexture(L"P2Dead", L"Texture\\Player2\\Player2_Dead.bmp");

	//GetAnimator()->CreateAnimation(L"P2WALK_DOWN", pWalk_Down, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, -10.f), 4, 0.1f);
	//GetAnimator()->CreateAnimation(L"P2WALK_LEFT", pWalk_Left, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, -10.f), 4, 0.1f);
	//GetAnimator()->CreateAnimation(L"P2WALK_UP", pWalk_Up, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, -10.f), 4, 0.1f);
	//GetAnimator()->CreateAnimation(L"P2WALK_RIGHT", pWalk_Right, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, -10.f), 4, 0.1f);

	//GetAnimator()->CreateAnimation(L"P2IDLE_DOWN", pIdle_Down, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, -10.f), 1, 0.1f);
	//GetAnimator()->CreateAnimation(L"P2IDLE_LEFT", pIdle_Left, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, -10.f), 1, 0.1f);
	//GetAnimator()->CreateAnimation(L"P2IDLE_UP", pIdle_Up, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, -10.f), 1, 0.1f);
	//GetAnimator()->CreateAnimation(L"P2IDLE_RIGHT", pIdle_Right, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, -10.f), 1, 0.1f);

	//GetAnimator()->CreateAnimation(L"P2TRAPPED", pTrapped, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, 0.f), 4, 0.5f);
	//GetAnimator()->CreateAnimation(L"P2REVIVAL", pRevival, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, 0.f), 3, 0.125f);
	//GetAnimator()->CreateAnimation(L"P2DEAD", pDead, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, 0.f), 6, 0.3f);

	//GetAnimator()->FindAnimation(L"P2WALK_DOWN")->Save(L"animation\\WALK_DOWN2.anim");
	//GetAnimator()->FindAnimation(L"P2WALK_LEFT")->Save(L"animation\\WALK_LEFT2.anim");
	//GetAnimator()->FindAnimation(L"P2WALK_UP")->Save(L"animation\\WALK_UP2.anim");
	//GetAnimator()->FindAnimation(L"P2WALK_RIGHT")->Save(L"animation\\WALK_RIGHT2.anim");

	//GetAnimator()->FindAnimation(L"P2IDLE_DOWN")->Save(L"animation\\IDLE_DOWN2.anim");
	//GetAnimator()->FindAnimation(L"P2IDLE_LEFT")->Save(L"animation\\IDLE_LEFT2.anim");
	//GetAnimator()->FindAnimation(L"P2IDLE_UP")->Save(L"animation\\IDLE_UP2.anim");
	//GetAnimator()->FindAnimation(L"P2IDLE_RIGHT")->Save(L"animation\\IDLE_RIGHT2.anim");

	//GetAnimator()->FindAnimation(L"P2TRAPPED")->Save(L"animation\\TRAPPED2.anim");
	//GetAnimator()->FindAnimation(L"P2REVIVAL")->Save(L"animation\\REVIVAL2.anim");
	//GetAnimator()->FindAnimation(L"P2DEAD")->Save(L"animation\\DEAD2.anim");

	//GetAnimator()->LoadAnimation(L"animation\\P2READY.anim");

	//GetAnimator()->LoadAnimation(L"animation\\WALK_DOWN2.anim");
	//GetAnimator()->LoadAnimation(L"animation\\WALK_LEFT2.anim");
	//GetAnimator()->LoadAnimation(L"animation\\WALK_UP2.anim");
	//GetAnimator()->LoadAnimation(L"animation\\WALK_RIGHT2.anim");

	//GetAnimator()->LoadAnimation(L"animation\\IDLE_DOWN2.anim");
	//GetAnimator()->LoadAnimation(L"animation\\IDLE_LEFT2.anim");
	//GetAnimator()->LoadAnimation(L"animation\\IDLE_UP2.anim");
	//GetAnimator()->LoadAnimation(L"animation\\IDLE_RIGHT2.anim");

	//GetAnimator()->LoadAnimation(L"animation\\TRAPPED2.anim");
	//GetAnimator()->LoadAnimation(L"animation\\REVIVAL2.anim");
	//GetAnimator()->LoadAnimation(L"animation\\DEAD2.anim");

	GetAnimator()->LoadAnimation(L"animation\\READY.anim");

	GetAnimator()->LoadAnimation(L"animation\\WALK_DOWN.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_UP.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\IDLE_DOWN.anim");
	GetAnimator()->LoadAnimation(L"animation\\IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\IDLE_UP.anim");
	GetAnimator()->LoadAnimation(L"animation\\IDLE_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\TRAPPED.anim");
	GetAnimator()->LoadAnimation(L"animation\\REVIVAL.anim");
	GetAnimator()->LoadAnimation(L"animation\\DEAD.anim");

	AddState(L"Ready2", new CP2ReadyState);
	AddState(L"Idle2", new CP2IdleState);
	AddState(L"Trapped2", new CP2TrappedState);
	AddState(L"Dead2", new CP2DeadState);
	AddState(L"Revive2", new CP2ReviveState);

	ChangeState(L"Ready2");
}

CPlayer2::~CPlayer2()
{
	map<wstring, CPlayer2State*>::iterator iter = m_mapState.begin();
	for (; iter != m_mapState.end(); ++iter)
	{
		DEL(iter->second);
	}
	m_mapState.clear();
}

void CPlayer2::tick()
{
	if (m_pCurState == nullptr)
		return;

	m_pCurState->finaltick();

	if (IsTap(KEY::_6)) // 6번 누르면 무적모드.
	{
		if (!m_PowerOverwhelming)
			m_PowerOverwhelming = true;
		else
			m_PowerOverwhelming = false;
	}

	// 부모 오브젝트의 Tick 도 실행시킨다(Component Tick 호출)
	CObj::tick();
}

void CPlayer2::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetScale();

	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);
	SelectObject(_dc, (HPEN)GetStockObject(NULL_PEN));
	Rectangle(_dc, (int)(vPos.x - vSize.x / 2.f)
		, (int)(vPos.y - vSize.y / 2.f)
		, (int)(vPos.x + vSize.x / 2.f)
		, (int)(vPos.y + vSize.y / 2.f));

	SelectObject(_dc, hOriginBrush);

	CObj::render(_dc);
}

void CPlayer2::BeginOverlap(CCollider* _pOther)
{
	Vec2 vPos = GetPos();
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::OBSTACLE)
	{
		CObstacle* _pObstacle = (CObstacle*)(_pOther->GetOwner());
		Vec2 ObsPos = _pObstacle->GetPos();

		if (_pObstacle->GetObstacle() == true) // 이동 불가능한 곳에 접촉 했을 때
		{
			if (vPos.y - ObsPos.y < (3.f * TILE_SIZE / 2.f) && IsPressed(KEY::W)) // 위쪽에 블록이 있을 경우
			{
				SetPos(GetPrevPos()); // 현재 위치를 닿기 직전의 위치로 옮김.

				// 캐릭터가 블록보다 오른쪽에 더 치우쳐있을경우
				if (vPos.x - ObsPos.x > TILE_SIZE)
				{
					vPos.x += m_fSpeed * DT; // 미끄러 지듯이 이동
					SetPos(vPos);
				}
				// 캐릭터가 블록보다 왼쪽에 더 치우쳐 있을 경우
				if (ObsPos.x - vPos.x > 0.f)
				{
					vPos.x -= m_fSpeed * DT; // 미끄러 지듯이 이동
					SetPos(vPos);
				}

			}

			else if (ObsPos.y - vPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::S)) // 아래쪽에 블록이 있을 경우
			{
				SetPos(GetPrevPos()); // 현재 위치를 닿기 직전의 위치로 옮김.

				// 오른쪽에 더 치우쳐있을경우
				if (vPos.x - ObsPos.x > TILE_SIZE)
				{
					vPos.x += m_fSpeed * DT;
					SetPos(vPos);
				}
				// 왼쪽에 더 치우쳐 있을 경우
				if (ObsPos.x - vPos.x > 0.f)
				{
					vPos.x -= m_fSpeed * DT;
					SetPos(vPos);
				}

			}
			else if (vPos.x - ObsPos.x < (3.f * TILE_SIZE / 2.f) && IsPressed(KEY::A)) // 왼쪽에 블록이 있을 경우
			{
				SetPos(GetPrevPos());

				// 캐릭터가 블록보다 위에 더 치우쳐있을경우
				if (ObsPos.y - vPos.y > 0.f)
				{
					vPos.y -= m_fSpeed * DT; // 미끄러 지듯이 이동
					SetPos(vPos);
				}
				// 캐릭터가 블록보다 아래에 더 치우쳐 있을 경우
				if (vPos.y - ObsPos.y > TILE_SIZE)
				{
					vPos.y += m_fSpeed * DT; // 미끄러 지듯이 이동
					SetPos(vPos);
				}
			}

			else if (ObsPos.x - vPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::D)) // 오른쪽에 블록이 있을 경우
			{
				SetPos(GetPrevPos());


				// 캐릭터가 블록보다 위에 더 치우쳐있을경우
				if (ObsPos.y - vPos.y > 0.f)
				{
					vPos.y -= m_fSpeed * DT; // 미끄러 지듯이 이동
					SetPos(vPos);
				}
				// 캐릭터가 블록보다 아래에 더 치우쳐 있을 경우
				if (vPos.y - ObsPos.y > TILE_SIZE)
				{
					vPos.y += m_fSpeed * DT; // 미끄러 지듯이 이동
					SetPos(vPos);
				}
			}

		}
	}
	else if (_pOther->GetOwner()->ReturnLayer() == LAYER::BOMB)
	{
		CBomb* _pBomb = (CBomb*)(_pOther->GetOwner());
		Vec2 BombPos = _pBomb->GetPos();

		if (BombPos == m_TileCenter)
		{
			if (vPos.y - BombPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::W) && !m_BombFirst) // 위쪽에 물풍선이 있을 경우
			{
				CanMove[0] = false;
			}

			else if (BombPos.y - vPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::S) && !m_BombFirst) // 아래쪽에 물풍선이 있을 경우
			{
				CanMove[1] = false;
			}
			else if (vPos.x - BombPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::A) && !m_BombFirst) // 왼쪽에 물풍선이 있을 경우
			{
				CanMove[2] = false;
			}

			else if (BombPos.x - vPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::D) && !m_BombFirst) // 오른쪽에 물풍선이 있을 경우
			{
				CanMove[3] = false;
			}
		}
	}

	else if ((_pOther->GetOwner()->ReturnLayer() == LAYER::WAVE || _pOther->GetOwner()->ReturnLayer() == LAYER::WAVE_CENTER
		|| _pOther->GetOwner()->ReturnLayer() == LAYER::MONSTER_OBJECTILE || _pOther->GetOwner()->ReturnLayer() == LAYER::MONSTER)
		&& !m_BTrapped && !m_PowerOverwhelming)
	{
		ChangeState(L"Trapped2");
		m_BTrapped = true;
	}

	else if (_pOther->GetOwner()->ReturnLayer() == LAYER::PLAYER && m_BTrapped)
	{
		ChangeState(L"Dead2");
		m_BTrapped = false;
	}

}

void CPlayer2::OnOverlap(CCollider* _pOther)
{
	Vec2 vPos = GetPos();
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::OBSTACLE)
	{
		CObstacle* _pObstacle = (CObstacle*)(_pOther->GetOwner());
		Vec2 ObsPos = _pObstacle->GetPos();

		if (_pObstacle->GetObstacle() == true) // 이동 불가능한 곳에 접촉 했을 때
		{
			if (vPos.y - ObsPos.y < (3.f * TILE_SIZE / 2.f) && IsPressed(KEY::W)) // 캐릭터보다 위쪽에 블록이 있을 경우
			{
				SetPos(GetPrevPos());
				// 캐릭터가 블록보다 오른쪽에 더 치우쳐있을경우
				if (vPos.x - ObsPos.x > TILE_SIZE)
				{
					SetPrevPos(GetPos());
					vPos.x += m_fSpeed * DT; // 미끄러 지듯이 이동
					SetPos(vPos);
				}
				// 캐릭터가 블록보다 왼쪽에 더 치우쳐 있을 경우
				else if (ObsPos.x - vPos.x > 0.f)
				{
					vPos.x -= m_fSpeed * DT; // 미끄러 지듯이 이동
					SetPrevPos(GetPos());
					SetPos(vPos);
				}
			}

			if (ObsPos.y - vPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::S)) // 아래쪽에 블록이 있을 경우
			{
				SetPos(GetPrevPos());
				// 오른쪽에 더 치우쳐있을경우
				if (vPos.x - ObsPos.x > TILE_SIZE)
				{
					SetPrevPos(GetPos());
					vPos.x += m_fSpeed * DT;
					SetPos(vPos);
				}
				// 왼쪽에 더 치우쳐 있을 경우
				else if (ObsPos.x - vPos.x > 0.f)
				{
					vPos.x -= m_fSpeed * DT;
					SetPrevPos(GetPos());
					SetPos(vPos);
				}

			}
			if (vPos.x - ObsPos.x < (3.f * TILE_SIZE / 2.f) && IsPressed(KEY::A)) // 왼쪽에 블록이 있을 경우
			{
				SetPos(GetPrevPos());
				// 캐릭터가 블록보다 위에 더 치우쳐있을경우
				if (ObsPos.y - vPos.y > 0.f)
				{
					vPos.y -= m_fSpeed * DT; // 미끄러 지듯이 이동
					SetPos(vPos);
				}
				// 캐릭터가 블록보다 아래에 더 치우쳐 있을 경우
				else if (vPos.y - ObsPos.y > TILE_SIZE)
				{
					vPos.y += m_fSpeed * DT; // 미끄러 지듯이 이동
					SetPos(vPos);
				}

			}

			if (ObsPos.x - vPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::D)) // 오른쪽에 블록이 있을 경우
			{
				SetPos(GetPrevPos());
				// 캐릭터가 블록보다 위에 더 치우쳐있을경우
				if (ObsPos.y - vPos.y > 0.f)
				{
					vPos.y -= m_fSpeed * DT; // 미끄러 지듯이 이동
					SetPos(vPos);
				}
				// 캐릭터가 블록보다 아래에 더 치우쳐 있을 경우
				else if (vPos.y - ObsPos.y > TILE_SIZE)
				{
					vPos.y += m_fSpeed * DT; // 미끄러 지듯이 이동
					SetPos(vPos);
				}

			}
		}
	}

	else if (_pOther->GetOwner()->ReturnLayer() == LAYER::BOMB)
	{
		CBomb* _pBomb = (CBomb*)(_pOther->GetOwner());
		Vec2 BombPos = _pBomb->GetPos();

		if (!m_BKick)
		{
			if (BombPos == m_TileCenter)
			{
				if (vPos.y - BombPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::W) && !m_BombFirst) // 위쪽에 물풍선이 있을 경우
				{
					CanMove[0] = false;
				}

				else if (BombPos.y - vPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::S) && !m_BombFirst) // 아래쪽에 물풍선이 있을 경우
				{
					CanMove[1] = false;
				}
				else if (vPos.x - BombPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::A) && !m_BombFirst) // 왼쪽에 물풍선이 있을 경우
				{
					CanMove[2] = false;
				}

				else if (BombPos.x - vPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::D) && !m_BombFirst) // 오른쪽에 물풍선이 있을 경우
				{
					CanMove[3] = false;
				}
			}

			if (m_TileCenter == BombPos)
				m_CanSetBomb = false;
		}

		else //발차기 아이템을 먹은 경우
		{

			if (m_KickAccTime > 0.6f)
			{
				m_KickAccTime = 0.f;

				if (BombPos == m_TileCenter)
				{
					if (vPos.y - BombPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::W)) // 위쪽에 물풍선이 있을 경우
					{
						_pBomb->SetBKicked(true, 1);
						CanMove[0] = true;
					}

					else if (BombPos.y - vPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::S)) // 아래쪽에 물풍선이 있을 경우
					{
						_pBomb->SetBKicked(true, 2);
						CanMove[1] = true;
					}
					else if (vPos.x - BombPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::A)) // 왼쪽에 물풍선이 있을 경우
					{
						_pBomb->SetBKicked(true, 3);
						CanMove[2] = true;
					}

					else if (BombPos.x - vPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::D)) // 오른쪽에 물풍선이 있을 경우
					{
						_pBomb->SetBKicked(true, 4);
						CanMove[3] = true;
					}
				}
			}

			else
			{
				if (BombPos == m_TileCenter)
				{
					if (vPos.y - BombPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::W) && !m_BombFirst) // 위쪽에 물풍선이 있을 경우
					{
						CanMove[0] = false;
						m_KickAccTime += DT;
					}

					else if (BombPos.y - vPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::S) && !m_BombFirst) // 아래쪽에 물풍선이 있을 경우
					{
						CanMove[1] = false;
						m_KickAccTime += DT;
					}
					else if (vPos.x - BombPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::A) && !m_BombFirst) // 왼쪽에 물풍선이 있을 경우
					{
						CanMove[2] = false;
						m_KickAccTime += DT;
					}

					else if (BombPos.x - vPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::D) && !m_BombFirst) // 오른쪽에 물풍선이 있을 경우
					{
						CanMove[3] = false;
						m_KickAccTime += DT;
					}
				}
			}

			if (m_TileCenter == BombPos)
				m_CanSetBomb = false;
		}


	}
}

void CPlayer2::EndOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::BOMB)
	{
		if (!CanMove[0])
		{
			CanMove[0] = true;
		}

		if (!CanMove[1])
		{
			CanMove[1] = true;
		}

		if (!CanMove[2])
		{
			CanMove[2] = true;
		}

		if (!CanMove[3])
		{
			CanMove[3] = true;
		}
		m_BombFirst = false;

		if (!m_CanSetBomb)
			m_CanSetBomb = true;

	}
}

void CPlayer2::AddState(const wstring& _strKey, CPlayer2State* _pState)
{
	m_mapState.insert(make_pair(_strKey, _pState));
	_pState->m_pOwnerP = this;
}

void CPlayer2::ChangeState(const wstring& _strStateName)
{
	CPlayer2State* pNextState = FindState(_strStateName);
	assert(pNextState);

	if (nullptr != m_pCurState)
		m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();
}