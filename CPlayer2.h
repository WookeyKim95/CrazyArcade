#pragma once
#include "CObj.h"

enum class ITEM2
{
    NONE,
    NEEDLE,

    END = 8
};

class CTexture;
class CPlayer2State;
class CItem;

class CPlayer2 :
    public CObj
{
private:
    float       m_fSpeed;   // �ӷ� ( scalar )
    float       m_pSpeed;   // �ӷ� �����صα�
    float       m_KickAccTime; // ������ ���ؼ� �ʿ��� �ð� ����

    bool        m_BTrapped; // ���� �����ΰ� ���� ����
    bool        m_BKick; // ��ǳ���� �߷� �� �� �ִ°�?

    int         m_BombCount;
    int         m_MaxBombCount;
    int         m_WaveCount;
    int         m_MaxWaveCount = 7;

    UINT        m_Life;

    Vec2        m_TileCenter;
    int         m_NowCenTileX;
    int         m_NowCenTileY;

    bool        CanMove[4]; // �����¿� �̵� ���� ����
    bool        m_BombFirst; // ��ź�� ���� �������� ����
    bool        m_CanSetBomb; // ��ź�� ��ġ�� �� �ִ��� ����

    bool        m_PowerOverwhelming;

    map<wstring, CPlayer2State*>   m_mapState; // ���� ����
    CPlayer2State* m_pCurState;

    ITEM2 m_Slot;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

    virtual LAYER ReturnLayer() override { return LAYER::PLAYER; }

public:
    void SetSpeed(float _f) { m_fSpeed = _f; }
    float GetSpeed() { return m_fSpeed; }

    void SetPSpeed(float _f) { m_pSpeed = _f; }
    float GetPSpeed() { return m_pSpeed; }

    int GetBombCount() { return m_BombCount; }
    void SetBombCount(int _BombCount) { m_BombCount = _BombCount; }

    int GetMaxBombCount() { return m_MaxBombCount; }
    void SetMaxBombCount(int _MaxBombCount) { m_MaxBombCount = _MaxBombCount; }

    int GetWaveCount() { return m_WaveCount; }
    int GetMaxWaveCount() { return m_MaxWaveCount; }
    void SetWaveCount(int _WaveCount) { m_WaveCount = _WaveCount; }

    ITEM2 GetItemSlot() { return m_Slot; }
    void SetItemSlot(ITEM2 _Slot) { m_Slot = _Slot; }

    void SetKick(bool _Kick) { m_BKick = _Kick; }

public:
    void AddState(const wstring& _strKey, CPlayer2State* _pState);
    CPlayer2State* FindState(const wstring& _strKey)
    {
        map<wstring, CPlayer2State*>::iterator iter = m_mapState.find(_strKey);
        if (iter != m_mapState.end())
            return iter->second;
        return nullptr;
    }

    void ChangeState(const wstring& _strStateName);

public:
    CLONE(CPlayer2);

public:
    CPlayer2();
    // CPlayer(const CPlayer& _other);
    ~CPlayer2();

    friend class CP2ReadyState;
    friend class CP2IdleState;
    friend class CP2DeadState;
};

