#pragma once
#include "CObj.h"

class CMonsterState;
class CTexture;

class CSeal :
    public CObj
{
private:
    float       m_fSpeed;   // �ӷ� ( scalar )
    int         m_dir; // �ȴ� ���� ����
    bool        m_bTurned; // ���� ��ȯ�� �� ���ΰ� ���� (�ִϸ��̼� ����� ����)
    int         m_HP;
    bool        m_bHit;
    bool        m_BTrapped;

    Vec2        m_TileCenter;
    int         m_NowCenTileX;
    int         m_NowCenTileY;

    CTexture* m_pTex;
    CTexture* m_HPBar;
    CTexture* m_HPBack;

    map<wstring, CMonsterState*>   m_mapState; // ���� ����
    CMonsterState* m_mCurState;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

    virtual LAYER ReturnLayer() override { return LAYER::MONSTER; }

public:
    int     GetDir() { return m_dir; }
    void    SetDir(int _dir) { m_dir = _dir; }

    float   GetSpeed() { return m_fSpeed; }
    void    SetSpeed(float _Speed) { m_fSpeed = _Speed; }

public:
    CLONE(CSeal);

public:
    CSeal();
    //CSeal(const CSeal& _other);
    ~CSeal();

    friend class CSealIdleState;
    friend class CSealDeadState;
    friend class CSealTrappedState;
    friend class CSealHitState;
    friend class CSealAtkOneState;
    friend class CSealAtkTwoState;
    friend class CSealAtkThrStateL;
    friend class CSealAtkThrStateR;
};

