#pragma once
#include "CObj.h"

enum class ITEM
{
    NONE,
    NEEDLE,

    END = 8
};

class CTexture;
class CPlayerState;
class CItem;

class CPlayer :
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

    map<wstring, CPlayerState*>   m_mapState; // ���� ����
    CPlayerState* m_pCurState;

    ITEM m_Slot;

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

    ITEM GetItemSlot() { return m_Slot; }
    void SetItemSlot(ITEM _Slot) { m_Slot = _Slot; }

    void SetKick(bool _Kick) { m_BKick = _Kick; }

public:
    void AddState(const wstring& _strKey, CPlayerState* _pState);
    CPlayerState* FindState(const wstring& _strKey)
    {
        map<wstring, CPlayerState*>::iterator iter = m_mapState.find(_strKey);
        if (iter != m_mapState.end())
            return iter->second;
        return nullptr;
    }

    void ChangeState(const wstring& _strStateName);

public:
    CLONE(CPlayer);

public:
    CPlayer();
    // CPlayer(const CPlayer& _other);
    ~CPlayer();

    friend class CPReadyState;
    friend class CPIdleState;
    friend class CPDeadState;
};

