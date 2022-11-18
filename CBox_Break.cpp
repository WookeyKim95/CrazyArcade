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

	// 한 파일에 여러 타일이 있는 것이 아니라 한 파일 당 한 타일 씩 있으므로
	// 0, 0 지점부터 TILESIZE만큼 출력해야함.

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
	// 위치
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	// 아틀라스 이미지 정보
	bool bAtlas = m_pAtlas;
	fwrite(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		// 키값 저장,
		wstring strKey = m_pAtlas->GetKey();
		SaveWString(strKey, _pFile);

		// 상대경로 저장,
		wstring strRelativePath = m_pAtlas->GetRelativePath();
		SaveWString(strRelativePath, _pFile);
	}

	// 이미지 인덱스
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CBox_Break::Load(FILE* _pFile)
{
	// 위치
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	// 아틀라스 이미지 정보
	bool bAtlas = false;
	fread(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		wstring strKey, strRelativePath;
		LoadWString(strKey, _pFile);
		LoadWString(strRelativePath, _pFile);
		m_pAtlas = CResMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	// 이미지 인덱스
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
