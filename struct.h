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
	}
	
	Vec operator -= (const Vec& _other)
	{
		x = x - _other.x;
		y = y - _other.y;
	}

	Vec operator *= (const Vec& _other)
	{
		x = x * _other.x;
		y = y * _other.y;
	}

	Vec operator /= (const Vec& _other)
	{
		x = x / _other.x;
		y = y / _other.y;
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
};

struct tEventInfo
{
	EEVENT_TYPE eType;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
};