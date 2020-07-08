#include "pch.h"
#include "Bricks.h"

Bricks bricks[][4] = {
	{//l形
		Bricks(point(0, 1), point(0, 0), point(0, -1), point(0, -2)),
		Bricks(point(-2, 0), point(-1, 0), point(0, 0), point(1, 0)),
		Bricks(point(0, 2), point(0, 1), point(0, 0), point(0, -1)),
		Bricks(point(-1, 0), point(0, 0), point(1, 0), point(2, 0))
	},
	{//田形
		Bricks(point(0, 0), point(1, 0), point(0, 1), point(1, 1)),
		Bricks(point(0, 0), point(1, 0), point(0, 1), point(1, 1)),
		Bricks(point(0, 0), point(1, 0), point(0, 1), point(1, 1)),
		Bricks(point(0, 0), point(1, 0), point(0, 1), point(1, 1))
	},
	{//z形
		Bricks(point(-1, 0), point(0, 0), point(0, 1), point(1, 1)),
		Bricks(point(0, -1), point(0, 0), point(-1, 0), point(-1, 1)),
		Bricks(point(1, 0), point(0, 0), point(0, -1), point(-1, -1)),
		Bricks(point(0, 1), point(0, 0), point(1, 0), point(1, -1))
	},
	{//反z形
		Bricks(point(-1, 1), point(0, 1), point(0, 0), point(1, 0)),
		Bricks(point(0, 1), point(0, 0), point(-1, 0), point(-1, -1)),
		Bricks(point(-1, 0), point(0, 0), point(0, -1), point(1, -1)),
		Bricks(point(0, -1), point(0, 0), point(1, 0), point(1, 1))
	},
	{//T形
		Bricks(point(0, 0), point(-1, 1), point(0, 1), point(1, 1)),
		Bricks(point(0, 0), point(-1, 0), point(-1, -1), point(-1, 1)),
		Bricks(point(0, 0), point(0, -1), point(-1, -1), point(1, -1)),
		Bricks(point(0, 0), point(1, 0), point(1, -1), point(1, 1))
	},
	{//L形
		Bricks(point(0, -1), point(0, 0), point(0, 1), point(1, 1)),
		Bricks(point(-1, 1), point(-1, 0), point(0, 0), point(1, 0)),
		Bricks(point(0, 1), point(0, 0), point(0, -1), point(-1, -1)),
		Bricks(point(-1, 0), point(0, 0), point(1, 0), point(1, -1))	
	},
	{//反L形		
		Bricks(point(0, -1), point(0, 0), point(0, 1), point(-1, 1)),
		Bricks(point(-1, -1), point(-1, 0), point(0, 0), point(1, 0)),
		Bricks(point(0, 1), point(0, 0), point(0, -1), point(1, -1)),
		Bricks(point(-1, 0), point(0, 0), point(1, 0), point(1, 1))	
	}
};