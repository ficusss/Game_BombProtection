#pragma once

class Vector_t {
	double x, y;
public:
	Vector_t(double _x = 0, double _y = 0) : x(_x), y(_y) {};
	void set(double _x, double _y) { x = _x; y = _y; };
	double getX() { return x; };
	double getY() { return y; };
	Vector_t& operator += (Vector_t& addVec) { x += addVec.getX(); y += addVec.getY(); return *this; };
	Vector_t& operator -= (Vector_t& subVec) { x -= subVec.getX(); y -= subVec.getY(); return *this; };
	Vector_t& operator = (Vector_t& vec) { x = vec.getX(); y = vec.getY(); return *this; };
	Vector_t operator * (double mul) { return Vector_t(x * mul, y * mul); };
	Vector_t operator / (double dev) { return Vector_t(x / dev, y / dev); };
};

static Vector_t operator + (Vector_t& vec1, Vector_t& vec2)
{ 
	return Vector_t(vec1.getX() + vec2.getX(), vec1.getY() + vec2.getY());
}

static Vector_t operator - (Vector_t& vec1, Vector_t& vec2)
{
	return Vector_t(vec1.getX() - vec2.getX(), vec1.getY() - vec2.getY());
}

static bool operator == (Vector_t& vec1, Vector_t& vec2)
{
	return (vec1.getX() == vec2.getX() && vec1.getY() == vec2.getY());
}