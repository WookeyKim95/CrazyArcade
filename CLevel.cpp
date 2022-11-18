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
	// 오브젝트 삭제
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

		// 동적할당 해제시킨 주소값들을 벡터내에서 비워내기
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
	// 기존에 깔아 둔 타일 제거
	DeleteObject(LAYER::TILE);

	m_iTileXCount = _X;
	m_iTileYCount = _Y;

	// 지정된 가로 세로 숫자에 맞추어 타일 배치
	for (UINT iRow = 0; iRow < m_iTileYCount; ++iRow)
	{
		for (UINT iCol = 0; iCol < m_iTileXCount; ++iCol)
		{
			CTile* pTile = new CTile;
			// 시작 지점이 x = 20, y = 40 지점임.
			// 타일깔기 작업을 여기서 진행함.
			pTile->SetPos(Vec2((float)(TILE_SIZE * iCol) + 20.f, (float)(TILE_SIZE * iRow) + 40.f));
			AddObject(pTile, LAYER::TILE);
		}
	}
}

void CLevel::CreateBox(UINT _X, UINT _Y)
{
	// 기존에 깔아 둔 타일 제거
	DeleteObject(LAYER::BOX_BREAK);

	m_iTileXCount = _X;
	m_iTileYCount = _Y;

	// 지정된 가로 세로 숫자에 맞추어 타일 배치
	for (UINT iRow = 0; iRow < m_iTileYCount; ++iRow)
	{
		for (UINT iCol = 0; iCol < m_iTileXCount; ++iCol)
		{
			CBox_Break* pBox = new CBox_Break;
			// 시작 지점이 x = 20, y = 40 지점임.
			// 박스깔기 작업을 여기서 진행함.
			pBox->SetPos(Vec2((float)(TILE_SIZE * iCol) + 20.f, (float)(TILE_SIZE * iRow) + 40.f));
			AddObject(pBox, LAYER::BOX_BREAK);
		}
	}
}

void CLevel::CreateObstacle(UINT _X, UINT _Y)
{
	// 기존에 깔아 둔 타일 제거
	DeleteObject(LAYER::OBSTACLE);

	m_iTileXCount = _X;
	m_iTileYCount = _Y;

	// 지정된 가로 세로 숫자에 맞추어 타일 배치
	for (UINT iRow = 0; iRow < m_iTileYCount; ++iRow)
	{
		for (UINT iCol = 0; iCol < m_iTileXCount; ++iCol)
		{
			CObstacle* pBox = new CObstacle;
			// 시작 지점이 x = 20, y = 40 지점임.
			// 박스깔기 작업을 여기서 진행함.
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

	// Focued 처리할 UI 가 레벨에 없었다?!?!?!?
	assert(nullptr);
}
