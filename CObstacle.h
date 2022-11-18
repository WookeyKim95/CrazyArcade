#pragma once
#include "CObj.h"
class CObstacle :
    public CObj
{
    // 장애물의 역할은? 못지나가게 하는 것.
private:
    bool    is_Obstacle;
    bool    is_AbsObstacle; //절대 부숴지지 않는 장애물인가?

public:
    void    SetObstacle(bool _is_Obstacle) { is_Obstacle = _is_Obstacle; }
    bool    GetObstacle() { return is_Obstacle; }

    void    SetAbsObstacle(bool _is_AbsObstacle) { is_AbsObstacle = _is_AbsObstacle; }
    bool    GetAbsObstacle() { return is_AbsObstacle; }

public:
    virtual void    tick();
    virtual void    render(HDC _dc);

    virtual LAYER ReturnLayer() override { return LAYER::OBSTACLE; }

public:
    CLONE(CObstacle);
    
public:
    void    Save(FILE* _pFile);
    void    Load(FILE* _pFile);

    void    BeginOverlap(CCollider* _pOther);
    void    OnOverlap(CCollider* _pOther);
    void    EndOverlap(CCollider* _pOther);

public:
    CObstacle();
    ~CObstacle();
};

