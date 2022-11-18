#include "pch.h"
#include "CBox_Break.h"

#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CResMgr.h"
#include "CLevelMgr.h"

#include "CTexture.h"

CBox_Break::CBox_Break()
	: m_pAtlas(nullptr)
	, m_iImgIdx(-1)
{
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetOffsetPos(Vec2(15.f, 15.f));
	GetCollider()->SetScale(Vec2(TILE_SIZE - 10.f, TILE_SIZE - 10.f));
}

CBox_Break::~CBox_Break()
{
}

void CBox_Break::tick()
{

}

void CBox_Break::render(HDC _dc)
{
	if (m_pAtlas == nullptr)
		return;

	Vec2 vPos = GetPos();

	// �� ���Ͽ� ���� Ÿ���� �ִ� ���� �ƴ϶� �� ���� �� �� Ÿ�� �� �����Ƿ�
	// 0, 0 �������� TILESIZE��ŭ ����ؾ���.

	TransparentBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, TILE_SIZE, TILE_SIZE
		, m_pAtlas->GetDC()
		, 0
		, 0
		, TILE_SIZE, TILE_SIZE
		, RGB(255, 0, 255));

}


void CBox_Break::Save(FILE* _pFile)
{
	// ��ġ
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	// ��Ʋ�� �̹��� ����
	bool bAtlas = m_pAtlas;
	fwrite(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		// Ű�� ����,
		wstring strKey = m_pAtlas->GetKey();
		SaveWString(strKey, _pFile);

		// ����� ����,
		wstring strRelativePath = m_pAtlas->GetRelativePath();
		SaveWString(strRelativePath, _pFile);
	}

	// �̹��� �ε���
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CBox_Break::Load(FILE* _pFile)
{
	// ��ġ
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	// ��Ʋ�� �̹��� ����
	bool bAtlas = false;
	fread(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		wstring strKey, strRelativePath;
		LoadWString(strKey, _pFile);
		LoadWString(strRelativePath, _pFile);
		m_pAtlas = CResMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	// �̹��� �ε���
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CBox_Break::BeginOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::WAVE)
	{
		SetDead();
	}
}

void CBox_Break::OnOverlap(CCollider* _pOther)
{
}

void CBox_Break::EndOverlap(CCollider* _pOther)
{

}
