#pragma once

struct Vec
{
public:
	float x;
	float y;

public:

	Vec operator / (float _f)
	{
		assert(_f);

		return Vec(x / _f, y / _f);
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