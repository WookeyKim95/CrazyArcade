#pragma once

struct Vec2
{
	float x;
	float y;


public:
	bool IsZero()
	{
		return x == 0.f && y == 0.f;
	}

	void Normalize() // ����ȭ
	{
		float fDist = sqrtf(x * x + y * y);
		x /= fDist;
		y /= fDist;
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}



	Vec2 operator +(Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}

	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	Vec2 operator -(Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	void operator -= (Vec2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	Vec2 operator -()
	{
		return Vec2(-x, -y);
	}




	Vec2 operator / (float _f)
	{
		return Vec2(x / _f, y / _f);
	}

	void operator /= (float _f)
	{
		x /= _f;
		y /= _f;
	}



	Vec2 operator / (Vec2 _vOther)
	{
		return Vec2(x / _vOther.x, y / _vOther.y);
	}

	void operator /= (Vec2 _vOther)
	{
		x /= _vOther.x;
		y /= _vOther.y;
	}

	bool operator == (Vec2 _vOther)
	{
		return x == _vOther.x && y == _vOther.y;
	}

	bool operator <= (Vec2 _vOther)
	{
		return x <= _vOther.x && y <= _vOther.y;
	}

	bool operator >= (Vec2 _vOther)
	{
		return x >= _vOther.x && y >= _vOther.y;
	}

	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	Vec2 operator * (float _f)
	{
		return Vec2(x * _f, y * _f);
	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;
	}



public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x), y(_y)
	{}

	Vec2(UINT _x, UINT _y)
		: x((float)_x), y((float)_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{

	}

	~Vec2()
	{}
};

struct tEvent
{
	EVENT_TYPE	eType;
	DWORD_PTR	wParam;
	DWORD_PTR	lParam;
};

struct tAnimFrm
{
	Vec2	vLeftTop;	// �̹��� ������ �������� �»�� ��ġ
	Vec2	vSize;		// ������ ������
	Vec2	vOffset;	// �߰� �̵�
	float	fDuration;	// �ش� ������ ���� �ð�
};