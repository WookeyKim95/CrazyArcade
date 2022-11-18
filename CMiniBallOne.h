#pragma once
#include "CObj.h"

class CTexture;
class CMonsterState;

class CMiniBallOne :
    public CObj
{
private:
    float       m_fSpeed;   // 속력 ( scalar )
    int         m_dir; // 걷는 방향 저장
    bool        m_bTurned; // 방향 전환을 한 뒤인가 여부 (애니메이션 재생을 위해)

    Vec2        m_TileCenter;
    int         m_NowCenTileX;
    int         m_NowCenTileY;

    CTexture* m_pTex;

    map<wstring, CMonsterState*>   m_mapState; // 상태 여부
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
    CLONE(CMiniBallOne);

public:
    CMiniBallOne();
    CMiniBallOne(const CMiniBallOne& _other);
    ~CMiniBallOne();

    friend class CMBOneIdleState;
    friend class CMBOneDeadState;

};

