#pragma once

struct Vec
{
public:
	float x;
	float y;

public:

	Vec operator + (float _f)
	{
		return Vec(x + _f, y + _f);
	}

	Vec operator - (float _f)
	{
		return Vec(x - _f, y - _f);
	}

	Vec operator * (float _f)
	{
		return Vec(x * _f, y * _f);
	}

	Vec operator / (float _f)
	{
		assert(_f);

		return Vec(x / _f, y / _f);
	}
	
	Vec operator + (const Vec& _other)
	{
		return Vec(x + _other.x, y + _other.y);
	}

	Vec operator - (const Vec& _other)
	{
		return Vec(x - _other.x, y - _other.y);
	}

	Vec operator * (const Vec& _other)
	{
		return Vec(x * _other.x, y * _other.y);
	}
	
	Vec operator / (const Vec& _other)
	{
		return Vec(x / _other.x, y / _other.y);
	}

	Vec operator += (const Vec& _other)
	{
		x = x + _other.x;
		y = y + _other.y;

		return *this;
	}
	
	Vec operator -= (const Vec& _other)
	{
		x -= _other.x;
		y -= _other.y;

		return *this;
	}

	Vec operator *= (const Vec& _other)
	{
		x = x * _other.x;
		y = y * _other.y;
		
		return *this;
	}

	Vec operator /= (const Vec& _other)
	{
		x = x / _other.x;
		y = y / _other.y;

		return *this;
	}

	Vec operator /= (float _other)
	{
		assert(_other);

		x /= _other;
		y /= _other;

		return *this;
	}

	bool operator < (const Vec& _other) const
	{
		if (y == _other.y)
			return x < _other.x;

		else
			return y < _other.y;
	}

	bool operator == (const Vec& _other) const
	{
		return (x == _other.x && y == _other.y);
	}

public:
	Vec()
		: x(0.0f), y(0.0f)
	{}

	Vec(float _x, float _y)
		: x(_x), y(_y)
	{}

	Vec(long _x, long _y)
		: x(float(_x)), y(float(_y))
	{}

	Vec(int _x, int _y)
		: x(float(_x)), y(float(_y))
	{}

	Vec(UINT _x, UINT _y)
		: x(float(_x)), y(float(_y))
	{}

	Vec(const POINT& _point)
		:x(float(_point.x)), y(float(_point.y))
	{}
};

struct tEventInfo
{
	EEVENT_TYPE eType;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
};