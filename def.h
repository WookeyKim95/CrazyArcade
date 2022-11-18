#pragma once


#define SINGLE(type) public:\
					 static type* GetInst()\
					 {\
						 static type inst;\
						 return &inst;\
					 }\
					 private:\
						type();\
						~type();

#define DT CTimeMgr::GetInst()->GetDeltaTime()


#define IsTap(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::TAP
#define IsPressed(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::PRESSED
#define IsRelease(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::RELEASE
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define DEL(p) if(nullptr != p) delete p;
#define PI 3.1415926535f

#define CLONE(type) virtual type* Clone() { return new type(*this); }
#define CLONE_DEACTIVATE(type) virtual type* Clone() { assert(nullptr); return nullptr; }

#define TILE_SIZE 40
#define SEAL_FULL_HP 5
#define START_TIME 4.f

enum class LEVEL_TYPE
{
	START,
	LEVEL_01,
	LEVEL_02,
	LEVEL_03,
	LEVEL_VS,
	EDITOR,

	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END,
};


enum class LAYER
{
	BACKGROUND,
	TILE,
	ITEM,
	WAVE,
	WAVE_CENTER,
	BOX_BREAK,
	BOX_NON_BREAK,
	DEFAULT,
	OBSTACLE,
	BOMB,
	MONSTER_OBJECTILE,



	UI,
	PLAYER,
	MONSTER,
	UI_UP,
	END = 32
};


enum class EVENT_TYPE
{
	CREATE_OBJECT,	//	wParam : Object Adress   lParam : Layer Type
	DELETE_OBJECT,	//  wParam : Object Adress
	LEVEL_CHANGE,	//  wParam : LEVEL_TYPE(Next Level Type)
	CHANGE_PLAYER_STATE, // wParam: Player 컴포넌트 주소
	CHANGE_MONSTER_STATE, // wParam: Monster 컴포넌트 주소
	CHANGE_AI_STATE, // wParam : AI 컴포넌트 주소, lParam : Next State Name
};

enum class CAMERA_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};