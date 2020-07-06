#pragma once

class point
{
public:
	int x, y;
	point(int x = 0, int y = 0) : x(x), y(y) {};
	void set(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

class Bricks
{
public:
	point p[4];
	Bricks(point p1, point p2, point p3, point p4) {
		p[0] = p1;
		p[1] = p2;
		p[2] = p3;
		p[3] = p4;
	}
};

extern Bricks bricks[][4];
