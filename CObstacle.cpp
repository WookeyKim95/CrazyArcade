#include "pch.h"
#include "CObstacle.h"

#include "CCollider.h"
#include "CItem.h"
#include "CBombPlus.h"
#include "CWavePlus.h"
#include "CMaxWave.h"
#include "CSpeedUp.h"
#include "CNeedle.h"
#include "CKick.h"

#include "CEngine.h"

CObstacle::CObstacle()
	: is_Obstacle(true)
	, is_AbsObstacle(false)
{
	CreateCollider();

	GetCollider()->SetOffsetPos(Vec2((float)(TILE_SIZE / 2), (float)(TILE_SIZE / 2)));
	GetCollider()->SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
}

CObstacle::~CObstacle()
{
}

void CObstacle::tick()
{
}

void CObstacle::render(HDC _dc)
{
	HPEN hPen = nullptr;

	//if (is_Obstacle)
	//{
	//	hPen = CEngine::GetInst()->GetPen(PEN_TYPE::RED);
	//}
	//else
	//{
	//	hPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
	//}


	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	// DC 의 기존 펜과 브러시를 새로 가져온 것들로 대체한다
	HPEN hOriginPen = (HPEN)SelectObject(_dc, (HPEN)NULL_PEN);
	HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

	Vec2 vPos = GetPos();

	// 사각형 그리기
	Rectangle(_dc, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + TILE_SIZE)
		, (int)(vPos.y + TILE_SIZE));

	// DC 의 GDI 오브젝트들을 기존의 펜과 브러시로 되돌린다.
	SelectObject(_dc, hOriginPen);
	SelectObject(_dc, hOriginBrush);

}

void CObstacle::Save(FILE* _pFile)
{
	// 위치
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	// 장애물 여부
	bool Obstacle = GetObstacle();
	fwrite(&Obstacle, sizeof(bool), 1, _pFile);

	// 절대 장애물 여부
	bool AbsObstacle = GetAbsObstacle();
	fwrite(&AbsObstacle, sizeof(bool), 1, _pFile);
}

void CObstacle::Load(FILE* _pFile)
{
	// 위치
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	// 장애물 여부
	bool Obstacle = true;
	fread(&Obstacle, sizeof(bool), 1, _pFile);
	SetObstacle(Obstacle);

	// 절대 장애물 여부
	bool AbsObstacle = false;
	fread(&AbsObstacle, sizeof(bool), 1, _pFile);
	SetAbsObstacle(AbsObstacle);
}


void CObstacle::BeginOverlap(CCollider* _pOther)
{
}

void CObstacle::OnOverlap(CCollider* _pOther)
{
}

void CObstacle::EndOverlap(CCollider* _pOther)
{
	if (_pOther->GetOwner()->ReturnLayer() == LAYER::WAVE && !is_AbsObstacle) // 절대 장애물이 아닌 경우에!
	{

		if (is_Obstacle) // is_Obstacle은 박스가 있는 곳.
		{
			// 박스가 부숴지고 확률적으로 아이템 생성
			int random_item = rand() % 100;

			if (0 <= random_item && random_item < 5)
			{
				CBombPlus* pBombPlus = new CBombPlus;
				pBombPlus->SetScale(Vec2(38.f, 38.f));
				Instantiate(pBombPlus, GetPos(), LAYER::ITEM);
			}

			else if (5 <= random_item && random_item < 10)
			{
				CWavePlus* pWavePlus = new CWavePlus;
				pWavePlus->SetScale(Vec2(38.f, 38.f));
				Instantiate(pWavePlus, GetPos(), LAYER::ITEM);
			}

			else if (10 <= random_item && random_item < 13)
			{
				CMaxWave* pMaxWave = new CMaxWave;
				pMaxWave->SetScale(Vec2(38.f, 38.f));
				Instantiate(pMaxWave, GetPos(), LAYER::ITEM);
			}

			else if (13 <= random_item && random_item < 18)
			{
				CSpeedUp* pSpeedUp = new CSpeedUp;
				pSpeedUp->SetScale(Vec2(38.f, 38.f));
				Instantiate(pSpeedUp, GetPos(), LAYER::ITEM);
			}
			else if (18 <= random_item && random_item < 20)
			{
				CNeedle* pNeedle = new CNeedle;
				pNeedle->SetScale(Vec2(38.f, 38.f));
				Instantiate(pNeedle, GetPos(), LAYER::ITEM);
			}

			else if (20 <= random_item && random_item < 23)
			{
				CKick* pKick = new CKick;
				pKick->SetScale(Vec2(38.f, 38.f));
				Instantiate(pKick, GetPos(), LAYER::ITEM);
			}
		}
		is_Obstacle = false;
	}
}
