#pragma once
#include "CObj.h"
class CObstacle :
    public CObj
{
    // ��ֹ��� ������? ���������� �ϴ� ��.
private:
    bool    is_Obstacle;
    bool    is_AbsObstacle; //���� �ν����� �ʴ� ��ֹ��ΰ�?

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

