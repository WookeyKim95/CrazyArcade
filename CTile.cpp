#include "pch.h"
#include "CTile.h"

#include "CResMgr.h"
#include "CTexture.h"

CTile::CTile()
	: m_pAtlas(nullptr)
	, m_iImgIdx(-1)
	, m_Can_Walk(true)
{

}

CTile::~CTile()
{
}

void CTile::tick()
{

}

void CTile::render(HDC _dc)
{
	if (m_pAtlas == nullptr)
		return;

	Vec2 vPos = GetPos();

	// �� ���Ͽ� ���� Ÿ���� �ִ� ���� �ƴ϶� �� ���� �� �� Ÿ�� �� �����Ƿ�
	// 0, 0 �������� TILESIZE��ŭ ����ؾ���.

	BitBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, TILE_SIZE, TILE_SIZE
		, m_pAtlas->GetDC()
		, 0
		, 0
		, SRCCOPY);

}


void CTile::Save(FILE* _pFile)
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

void CTile::Load(FILE* _pFile)
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