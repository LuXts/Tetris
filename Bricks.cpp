#include "pch.h"
#include "Bricks.h"

Bricks bricks[][4] = {
	{//l��
		Bricks(point(0, 1), point(0, 0), point(0, -1), point(0, -2)),
		Bricks(point(-2, 0), point(-1, 0), point(0, 0), point(1, 0)),
		Bricks(point(0, 2), point(0, 1), point(0, 0), point(0, -1)),
		Bricks(point(-1, 0), point(0, 0), point(1, 0), point(2, 0))
	},
	{//����
		Bricks(point(0, 0), point(1, 0), point(0, 1), point(1, 1)),
		Bricks(point(0, 0), point(1, 0), point(0, 1), point(1, 1)),
		Bricks(point(0, 0), point(1, 0), point(0, 1), point(1, 1)),
		Bricks(point(0, 0), point(1, 0), point(0, 1), point(1, 1))
	},
	{//z��
		Bricks(point(-1, 0), point(0, 0), point(0, 1), point(1, 1)),
		Bricks(point(0, -1), point(0, 0), point(-1, 0), point(-1, 1)),
		Bricks(point(1, 0), point(0, 0), point(0, -1), point(-1, -1)),
		Bricks(point(0, 1), point(0, 0), point(1, 0), point(1, -1))
	},
	{//��z��
		Bricks(point(-1, 1), point(0, 1), point(0, 0), point(1, 0)),
		Bricks(point(0, 1), point(0, 0), point(-1, 0), point(-1, -1)),
		Bricks(point(-1, 0), point(0, 0), point(0, -1), point(1, -1)),
		Bricks(point(0, -1), point(0, 0), point(1, 0), point(1, 1))
	},
	{//T��
		Bricks(point(0, 0), point(-1, 1), point(0, 1), point(1, 1)),
		Bricks(point(0, 0), point(-1, 0), point(-1, -1), point(-1, 1)),
		Bricks(point(0, 0), point(0, -1), point(-1, -1), point(1, -1)),
		Bricks(point(0, 0), point(1, 0), point(1, -1), point(1, 1))
	},
	{//L��
		Bricks(point(0, -1), point(0, 0), point(0, 1), point(1, 1)),
		Bricks(point(-1, 1), point(-1, 0), point(0, 0), point(1, 0)),
		Bricks(point(0, 1), point(0, 0), point(0, -1), point(-1, -1)),
		Bricks(point(-1, 0), point(0, 0), point(1, 0), point(1, -1))	
	},
	{//��L��		
		Bricks(point(0, -1), point(0, 0), point(0, 1), point(-1, 1)),
		Bricks(point(-1, -1), point(-1, 0), point(0, 0), point(1, 0)),
		Bricks(point(0, 1), point(0, 0), point(0, -1), point(1, -1)),
		Bricks(point(-1, 0), point(0, 0), point(1, 0), point(1, 1))	
	}
};