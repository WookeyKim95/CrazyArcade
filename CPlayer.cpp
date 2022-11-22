#include "pch.h"
#include "CPlayer.h"

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

#include "CPReadyState.h"
#include "CPlayerState.h"
#include "CPTrappedState.h"
#include "CPIdleState.h"
#include "CPDeadState.h"
#include "CPReviveState.h"

#include "CTile.h"
#include "CLevel.h"
#include "CLevel01.h"
#include "CBomb.h"
#include "CObstacle.h"
#include "CItem.h"
#include "CNeedle.h"
#include "CItemUI.h"

CPlayer::CPlayer()
	: m_fSpeed(100.f)
	, m_pSpeed(100.f)
	, m_KickAccTime(0.f)
	, m_BombCount(1) // ���� ���� �� �ִ� ��ǳ���� ����
	, m_MaxBombCount(1) // ���� �� �ִ� ��ǳ���� �ִ� ���� (��ǳ�� ���������� ����)
	, m_TileCenter(Vec2(0.f, 0.f))
	, CanMove{ true, true, true, true }
	, m_WaveCount(1)
	, m_MaxWaveCount(7)
	, m_BombFirst(true)
	, m_CanSetBomb(true)
	, m_pCurState(nullptr)
	, m_BTrapped(false)
	, m_BKick(false)
	, m_Slot(ITEM::NONE)
	, m_Life(2)
	, m_PowerOverwhelming(false)
{
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(TILE_SIZE - 20.f, TILE_SIZE - 20.f));

	// Animator ���� ����� Image �ε�

	//CTexture* pReady = CResMgr::GetInst()->LoadTexture(L"PREADY", L"Texture\\Player\\Ready.bmp");
	//GetAnimator()->CreateAnimation(L"READY", pReady, Vec2(0.f, 0.f), Vec2(56.f, 56.f), Vec2(0.f, -10.f), 6, 0.33f);
	//GetAnimator()->FindAnimation(L"READY")->Save(L"animation\\READY.anim");

	//GetAnimator()->CreateAnimation(L"WALK_DOWN", pWalk_Down, Vec2(0.f, 0.f), Vec2(55.f, 58.f), Vec2(0.f, -10.f), 4, 0.1f);
	//GetAnimator()->CreateAnimation(L"WALK_LEFT", pWalk_Left, Vec2(0.f, 0.f), Vec2(49.f, 58.f), Vec2(0.f, -10.f), 4, 0.1f);
	//GetAnimator()->CreateAnimation(L"WALK_UP", pWalk_Up, Vec2(0.f, 0.f), Vec2(56.f, 60.f), Vec2(0.f, -10.f), 4, 0.1f);
	//GetAnimator()->CreateAnimation(L"WALK_RIGHT", pWalk_Right, Vec2(0.f, 0.f), Vec2(49.f, 58.f), Vec2(0.f, -10.f), 4, 0.1f);

	//GetAnimator()->CreateAnimation(L"IDLE_DOWN", pIdle_Down, Vec2(0.f, 0.f), Vec2(56.f, 56.f), Vec2(0.f, -10.f), 1, 0.1f);
	//GetAnimator()->CreateAnimation(L"IDLE_LEFT", pIdle_Left, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, -10.f), 1, 0.1f);
	//GetAnimator()->CreateAnimation(L"IDLE_UP", pIdle_Up, Vec2(0.f, 0.f), Vec2(56.f, 56.f), Vec2(0.f, -10.f), 1, 0.1f);
	//GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pIdle_Right, Vec2(0.f, 0.f), Vec2(47.f, 56.f), Vec2(0.f, -10.f), 1, 0.1f);

	//GetAnimator()->CreateAnimation(L"TRAPPED", pTrapped, Vec2(0.f, 0.f), Vec2(60.f, 60.f), Vec2(0.f, 0.f), 5, 0.5f);
	//GetAnimator()->CreateAnimation(L"REVIVAL", pRevival, Vec2(0.f, 0.f), Vec2(69.f, 70.f), Vec2(0.f, 0.f), 4, 0.125f);
	//GetAnimator()->CreateAnimation(L"DEAD", pDead, Vec2(0.f, 0.f), Vec2(68.f, 75.f), Vec2(0.f, 0.f), 5, 0.3f);

	//GetAnimator()->FindAnimation(L"WALK_DOWN")->Save(L"animation\\WALK_DOWN.anim");
	//GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\WALK_LEFT.anim");
	//GetAnimator()->FindAnimation(L"WALK_UP")->Save(L"animation\\WALK_UP.anim");
	//GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\WALK_RIGHT.anim");

	//GetAnimator()->FindAnimation(L"IDLE_DOWN")->Save(L"animation\\IDLE_DOWN.anim");
	//GetAnimator()->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\IDLE_LEFT.anim");
	//GetAnimator()->FindAnimation(L"IDLE_UP")->Save(L"animation\\IDLE_UP.anim");
	//GetAnimator()->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\IDLE_RIGHT.anim");

	//GetAnimator()->FindAnimation(L"TRAPPED")->Save(L"animation\\TRAPPED.anim");
	//GetAnimator()->FindAnimation(L"REVIVAL")->Save(L"animation\\REVIVAL.anim");
	//GetAnimator()->FindAnimation(L"DEAD")->Save(L"animation\\DEAD.anim");

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

	AddState(L"Ready", new CPReadyState);
	AddState(L"Idle", new CPIdleState);
	AddState(L"Trapped", new CPTrappedState);
	AddState(L"Dead", new CPDeadState);
	AddState(L"Revive", new CPReviveState);

	ChangeState(L"Ready");
}

CPlayer::~CPlayer()
{
	map<wstring, CPlayerState*>::iterator iter = m_mapState.begin();
	for (; iter != m_mapState.end(); ++iter)
	{
		DEL(iter->second);
	}
	m_mapState.clear();
}

void CPlayer::tick()
{
	if (m_pCurState == nullptr)
		return;

	m_pCurState->finaltick();

	if (IsTap(KEY::_6)) // 6�� ������ �������.
	{
		if (!m_PowerOverwhelming)
		{
			m_PowerOverwhelming = true;
			m_WaveCount = m_MaxWaveCount;
		}

		else
			m_PowerOverwhelming = false;
	}

	// �θ� ������Ʈ�� Tick �� �����Ų��(Component Tick ȣ��)
	CObj::tick();
}

void CPlayer::render(HDC _dc)
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


void CPlayer::BeginOverlap(CCollider* _pOther)
{
	Vec2 vPos = GetPos();
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::OBSTACLE)
	{
		CObstacle* _pObstacle = (CObstacle*)(_pOther->GetOwner());
		Vec2 ObsPos = _pObstacle->GetPos();

		if (_pObstacle->GetObstacle() == true) // �̵� �Ұ����� ���� ���� ���� ��
		{
			if (vPos.y - ObsPos.y < (3.f * TILE_SIZE / 2.f) && IsPressed(KEY::UP)) // ���ʿ� ����� ���� ���
			{
				SetPos(GetPrevPos()); // ���� ��ġ�� ��� ������ ��ġ�� �ű�.

				// ĳ���Ͱ� ��Ϻ��� �����ʿ� �� ġ�����������
				if (vPos.x - ObsPos.x > TILE_SIZE)
				{
					vPos.x += m_fSpeed * DT; // �̲��� ������ �̵�
					SetPos(vPos);
				}
				// ĳ���Ͱ� ��Ϻ��� ���ʿ� �� ġ���� ���� ���
				if (ObsPos.x - vPos.x > 0.f)
				{
					vPos.x -= m_fSpeed * DT; // �̲��� ������ �̵�
					SetPos(vPos);
				}

			}

			else if (ObsPos.y - vPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::DOWN)) // �Ʒ��ʿ� ����� ���� ���
			{
				SetPos(GetPrevPos()); // ���� ��ġ�� ��� ������ ��ġ�� �ű�.

				// �����ʿ� �� ġ�����������
				if (vPos.x - ObsPos.x > TILE_SIZE)
				{
					vPos.x += m_fSpeed * DT;
					SetPos(vPos);
				}
				// ���ʿ� �� ġ���� ���� ���
				if (ObsPos.x - vPos.x > 0.f)
				{
					vPos.x -= m_fSpeed * DT;
					SetPos(vPos);
				}

			}
			else if (vPos.x - ObsPos.x < (3.f * TILE_SIZE / 2.f) && IsPressed(KEY::LEFT)) // ���ʿ� ����� ���� ���
			{
				SetPos(GetPrevPos());

				// ĳ���Ͱ� ��Ϻ��� ���� �� ġ�����������
				if (ObsPos.y - vPos.y > 0.f)
				{
					vPos.y -= m_fSpeed * DT; // �̲��� ������ �̵�
					SetPos(vPos);
				}
				// ĳ���Ͱ� ��Ϻ��� �Ʒ��� �� ġ���� ���� ���
				if (vPos.y - ObsPos.y > TILE_SIZE)
				{
					vPos.y += m_fSpeed * DT; // �̲��� ������ �̵�
					SetPos(vPos);
				}
			}

			else if (ObsPos.x - vPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::RIGHT)) // �����ʿ� ����� ���� ���
			{
				SetPos(GetPrevPos());


				// ĳ���Ͱ� ��Ϻ��� ���� �� ġ�����������
				if (ObsPos.y - vPos.y > 0.f)
				{
					vPos.y -= m_fSpeed * DT; // �̲��� ������ �̵�
					SetPos(vPos);
				}
				// ĳ���Ͱ� ��Ϻ��� �Ʒ��� �� ġ���� ���� ���
				if (vPos.y - ObsPos.y > TILE_SIZE)
				{
					vPos.y += m_fSpeed * DT; // �̲��� ������ �̵�
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
			if (vPos.y - BombPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::UP) && !m_BombFirst) // ���ʿ� ��ǳ���� ���� ���
			{
				CanMove[0] = false;
			}

			else if (BombPos.y - vPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::DOWN) && !m_BombFirst) // �Ʒ��ʿ� ��ǳ���� ���� ���
			{
				CanMove[1] = false;
			}
			else if (vPos.x - BombPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::LEFT) && !m_BombFirst) // ���ʿ� ��ǳ���� ���� ���
			{
				CanMove[2] = false;
			}

			else if (BombPos.x - vPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::RIGHT) && !m_BombFirst) // �����ʿ� ��ǳ���� ���� ���
			{
				CanMove[3] = false;
			}
		}
		
	}

	else if ((_pOther->GetOwner()->ReturnLayer() == LAYER::WAVE || _pOther->GetOwner()->ReturnLayer() == LAYER::WAVE_CENTER
	|| _pOther->GetOwner()->ReturnLayer() == LAYER::MONSTER_OBJECTILE && !m_BTrapped)
	&& !m_BTrapped && !m_PowerOverwhelming)
	{
		ChangeState(L"Trapped");
		m_BTrapped = true;
    }

	else if (_pOther->GetOwner()->ReturnLayer() == LAYER::PLAYER && m_BTrapped)
	{
		ChangeState(L"Dead");
		m_BTrapped = false;
	}
}

void CPlayer::OnOverlap(CCollider* _pOther)
{
	Vec2 vPos = GetPos();
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::OBSTACLE)
	{
		CObstacle* _pObstacle = (CObstacle*)(_pOther->GetOwner());
		Vec2 ObsPos = _pObstacle->GetPos();

		if (_pObstacle->GetObstacle() == true) // �̵� �Ұ����� ���� ���� ���� ��
		{
			if (vPos.y - ObsPos.y < (3.f * TILE_SIZE / 2.f) && IsPressed(KEY::UP)) // ĳ���ͺ��� ���ʿ� ����� ���� ���
			{
				SetPos(GetPrevPos());
				// ĳ���Ͱ� ��Ϻ��� �����ʿ� �� ġ�����������
				if (vPos.x - ObsPos.x > TILE_SIZE)
				{
					SetPrevPos(GetPos());
					vPos.x += m_fSpeed * DT; // �̲��� ������ �̵�
					SetPos(vPos);
				}
				// ĳ���Ͱ� ��Ϻ��� ���ʿ� �� ġ���� ���� ���
				else if (ObsPos.x - vPos.x > 0.f)
				{
					vPos.x -= m_fSpeed * DT; // �̲��� ������ �̵�
					SetPrevPos(GetPos());
					SetPos(vPos);
				}
			}

			if (ObsPos.y - vPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::DOWN)) // �Ʒ��ʿ� ����� ���� ���
			{
				SetPos(GetPrevPos());
				// �����ʿ� �� ġ�����������
				if (vPos.x - ObsPos.x > TILE_SIZE)
				{
					SetPrevPos(GetPos());
					vPos.x += m_fSpeed * DT;
					SetPos(vPos);
				}
				// ���ʿ� �� ġ���� ���� ���
				else if (ObsPos.x - vPos.x > 0.f)
				{
					vPos.x -= m_fSpeed * DT;
					SetPrevPos(GetPos());
					SetPos(vPos);
				}

			}
			if (vPos.x - ObsPos.x < (3.f * TILE_SIZE / 2.f) && IsPressed(KEY::LEFT)) // ���ʿ� ����� ���� ���
			{
				SetPos(GetPrevPos());
				// ĳ���Ͱ� ��Ϻ��� ���� �� ġ�����������
				if (ObsPos.y - vPos.y > 0.f)
				{
					vPos.y -= m_fSpeed * DT; // �̲��� ������ �̵�
					SetPos(vPos);
				}
				// ĳ���Ͱ� ��Ϻ��� �Ʒ��� �� ġ���� ���� ���
				else if (vPos.y - ObsPos.y > TILE_SIZE)
				{
					vPos.y += m_fSpeed * DT; // �̲��� ������ �̵�
					SetPos(vPos);
				}

			}

			if (ObsPos.x - vPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::RIGHT)) // �����ʿ� ����� ���� ���
			{
				SetPos(GetPrevPos());
				// ĳ���Ͱ� ��Ϻ��� ���� �� ġ�����������
				if (ObsPos.y - vPos.y > 0.f)
				{
					vPos.y -= m_fSpeed * DT; // �̲��� ������ �̵�
					SetPos(vPos);
				}
				// ĳ���Ͱ� ��Ϻ��� �Ʒ��� �� ġ���� ���� ���
				else if (vPos.y - ObsPos.y > TILE_SIZE)
				{
					vPos.y += m_fSpeed * DT; // �̲��� ������ �̵�
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
				if (vPos.y - BombPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::UP) && !m_BombFirst) // ���ʿ� ��ǳ���� ���� ���
				{
					CanMove[0] = false;
				}

				else if (BombPos.y - vPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::DOWN) && !m_BombFirst) // �Ʒ��ʿ� ��ǳ���� ���� ���
				{
					CanMove[1] = false;
				}
				else if (vPos.x - BombPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::LEFT) && !m_BombFirst) // ���ʿ� ��ǳ���� ���� ���
				{
					CanMove[2] = false;
				}

				else if (BombPos.x - vPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::RIGHT) && !m_BombFirst) // �����ʿ� ��ǳ���� ���� ���
				{
					CanMove[3] = false;
				}
			}

			if (m_TileCenter == BombPos)
				m_CanSetBomb = false;
		}

		else //������ �������� ���� ���
		{

			if (m_KickAccTime > 0.6f)
			{
				m_KickAccTime = 0.f;

				if (BombPos == m_TileCenter)
				{
					if (vPos.y - BombPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::UP)) // ���ʿ� ��ǳ���� ���� ���
					{
						_pBomb->SetBKicked(true, 1);
						CanMove[0] = true;
					}

					else if (BombPos.y - vPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::DOWN)) // �Ʒ��ʿ� ��ǳ���� ���� ���
					{
						_pBomb->SetBKicked(true, 2);
						CanMove[1] = true;
					}
					else if (vPos.x - BombPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::LEFT)) // ���ʿ� ��ǳ���� ���� ���
					{
						_pBomb->SetBKicked(true, 3);
						CanMove[2] = true;
					}

					else if (BombPos.x - vPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::RIGHT)) // �����ʿ� ��ǳ���� ���� ���
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
					if (vPos.y - BombPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::UP) && !m_BombFirst) // ���ʿ� ��ǳ���� ���� ���
					{
						CanMove[0] = false;
						m_KickAccTime += DT;
					}

					else if (BombPos.y - vPos.y < (TILE_SIZE / 2.f) && IsPressed(KEY::DOWN) && !m_BombFirst) // �Ʒ��ʿ� ��ǳ���� ���� ���
					{
						CanMove[1] = false;
						m_KickAccTime += DT;
					}
					else if (vPos.x - BombPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::LEFT) && !m_BombFirst) // ���ʿ� ��ǳ���� ���� ���
					{
						CanMove[2] = false;
						m_KickAccTime += DT;
					}

					else if (BombPos.x - vPos.x < (TILE_SIZE / 2.f) && IsPressed(KEY::RIGHT) && !m_BombFirst) // �����ʿ� ��ǳ���� ���� ���
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

	else if (_pOther->GetOwner()->ReturnLayer() == LAYER::MONSTER && _pOther->GetOwner()->IsTrapped() == false && !m_PowerOverwhelming && !m_BTrapped)
	{
		ChangeState(L"Trapped");
		m_BTrapped = true;
	}

}

void CPlayer::EndOverlap(CCollider* _pOther)
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


void CPlayer::AddState(const wstring& _strKey, CPlayerState* _pState)
{
	m_mapState.insert(make_pair(_strKey, _pState));
	_pState->m_pOwnerP = this;
}

void CPlayer::ChangeState(const wstring& _strStateName)
{
	CPlayerState* pNextState = FindState(_strStateName);
	assert(pNextState);

	if (nullptr != m_pCurState)
		m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();
}
