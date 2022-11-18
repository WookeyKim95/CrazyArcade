#include "pch.h"
#include "CCollider.h"

#include "CEngine.h"
#include "CObj.h"


CCollider::CCollider(CObj* _pOwner)
	: CComponent(_pOwner)
	, m_iOverlapCount(0)
{
}

CCollider::CCollider(const CCollider& _other)
	: CComponent(nullptr)
	, m_vOffsetPos(_other.m_vOffsetPos)
	, m_vScale(_other.m_vScale)
	, m_iOverlapCount(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::tick()
{
	// ��ø���� ������ ���
	assert(!(m_iOverlapCount < 0));
}

void CCollider::final_tick()
{
	// �浹ü�� ���� ��ġ���� �����Ѵ�.
	m_vFinalPos = GetOwner()->GetPos() + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	// �浹ü�� �׸���.
	// �ʿ��� ��� �귯�ø� �����(�Ǵ� �����´�)	
	HPEN hPen = nullptr;

	//if (0 < m_iOverlapCount)
	//{
	//	hPen = CEngine::GetInst()->GetPen(PEN_TYPE::RED);
	//}
	//else
	//{
	//	hPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	//}

	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	// DC �� ���� ��� �귯�ø� ���� ������ �͵�� ��ü�Ѵ�
	HPEN hOriginPen = (HPEN)SelectObject(_dc, (HPEN)NULL_PEN);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Vec2 vPos = GetOwner()->GetPos();

	// �簢�� �׸���
	Rectangle(_dc, (int)(vPos.x - m_vScale.x / 2.f)
		, (int)(vPos.y - m_vScale.y / 2.f)
		, (int)(vPos.x + m_vScale.x / 2.f)
		, (int)(vPos.y + m_vScale.y / 2.f));

	// DC �� GDI ������Ʈ���� ������ ��� �귯�÷� �ǵ�����.
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);
}

void CCollider::BeginOverlap(CCollider* _pOther)
{
	++m_iOverlapCount;

	GetOwner()->BeginOverlap(_pOther);
}

void CCollider::OnOverlap(CCollider* _pOther)
{
	GetOwner()->OnOverlap(_pOther);
}

void CCollider::EndOverlap(CCollider* _pOther)
{
	--m_iOverlapCount;

	GetOwner()->EndOverlap(_pOther);
}
