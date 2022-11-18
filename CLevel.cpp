#include "pch.h"
#include "CLevel.h"
#include "CObj.h"
#include "CResMgr.h"

#include "CTile.h"
#include "CBox_Break.h"
#include "CObstacle.h"

#include "CEngine.h"


CLevel::CLevel()
	: m_iTileXCount(0)
	, m_iTileYCount(0)
	, m_MonsterCount(0)
{
}

CLevel::~CLevel()
{
	// ������Ʈ ����
	DeleteAllObject();
}

void CLevel::tick()
{

	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			m_arrLayer[i][j]->tick();
		}
	}
}

void CLevel::final_tick()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			m_arrLayer[i][j]->final_tick();
		}
	}
}

void CLevel::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		vector<CObj*>::iterator iter = m_arrLayer[i].begin();

		for (; iter != m_arrLayer[i].end();)
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrLayer[i].erase(iter);
			}
			else
			{
				(*iter)->render(_dc);
				++iter;
			}
		}
	}
}


void CLevel::DeleteAllObject()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			if (m_arrLayer[i][j]->IsDead())
				continue;

			DEL(m_arrLayer[i][j]);
		}

		// �����Ҵ� ������Ų �ּҰ����� ���ͳ����� �������
		m_arrLayer[i].clear();
	}
}

void CLevel::DeleteObject(LAYER _eLayer)
{
	for (size_t i = 0; i < m_arrLayer[(UINT)_eLayer].size(); ++i)
	{
		delete m_arrLayer[(UINT)_eLayer][i];
	}
	m_arrLayer[(UINT)_eLayer].clear();
}

void CLevel::CreateTile(UINT _X, UINT _Y)
{
	// ������ ��� �� Ÿ�� ����
	DeleteObject(LAYER::TILE);

	m_iTileXCount = _X;
	m_iTileYCount = _Y;

	// ������ ���� ���� ���ڿ� ���߾� Ÿ�� ��ġ
	for (UINT iRow = 0; iRow < m_iTileYCount; ++iRow)
	{
		for (UINT iCol = 0; iCol < m_iTileXCount; ++iCol)
		{
			CTile* pTile = new CTile;
			// ���� ������ x = 20, y = 40 ������.
			// Ÿ�ϱ�� �۾��� ���⼭ ������.
			pTile->SetPos(Vec2((float)(TILE_SIZE * iCol) + 20.f, (float)(TILE_SIZE * iRow) + 40.f));
			AddObject(pTile, LAYER::TILE);
		}
	}
}

void CLevel::CreateBox(UINT _X, UINT _Y)
{
	// ������ ��� �� Ÿ�� ����
	DeleteObject(LAYER::BOX_BREAK);

	m_iTileXCount = _X;
	m_iTileYCount = _Y;

	// ������ ���� ���� ���ڿ� ���߾� Ÿ�� ��ġ
	for (UINT iRow = 0; iRow < m_iTileYCount; ++iRow)
	{
		for (UINT iCol = 0; iCol < m_iTileXCount; ++iCol)
		{
			CBox_Break* pBox = new CBox_Break;
			// ���� ������ x = 20, y = 40 ������.
			// �ڽ���� �۾��� ���⼭ ������.
			pBox->SetPos(Vec2((float)(TILE_SIZE * iCol) + 20.f, (float)(TILE_SIZE * iRow) + 40.f));
			AddObject(pBox, LAYER::BOX_BREAK);
		}
	}
}

void CLevel::CreateObstacle(UINT _X, UINT _Y)
{
	// ������ ��� �� Ÿ�� ����
	DeleteObject(LAYER::OBSTACLE);

	m_iTileXCount = _X;
	m_iTileYCount = _Y;

	// ������ ���� ���� ���ڿ� ���߾� Ÿ�� ��ġ
	for (UINT iRow = 0; iRow < m_iTileYCount; ++iRow)
	{
		for (UINT iCol = 0; iCol < m_iTileXCount; ++iCol)
		{
			CObstacle* pBox = new CObstacle;
			// ���� ������ x = 20, y = 40 ������.
			// �ڽ���� �۾��� ���⼭ ������.
			pBox->SetPos(Vec2((float)(TILE_SIZE * iCol) + 20.f, (float)(TILE_SIZE * iRow) + 40.f));
			AddObject(pBox, LAYER::OBSTACLE);
		}
	}
}

void CLevel::SetFocusedUI(CObj* _pUI)
{
	vector<CObj*>& vecUI = m_arrLayer[(UINT)LAYER::UI];

	if (vecUI.back() == _pUI)
		return;

	vector<CObj*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if ((*iter) == _pUI)
		{
			vecUI.erase(iter);
			vecUI.push_back(_pUI);
			return;
		}
	}

	// Focued ó���� UI �� ������ ������?!?!?!?
	assert(nullptr);
}
