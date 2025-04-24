#pragma once
#include <SDL3/SDL.h>
#include "particles.hpp"
#include <random>
#include <fstream>

static const int SIM_WIDTH = 321;
static const int SIM_HEIGHT = 181;
static const int SAND_SIZE = 4;
//static const int sand_types[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

enum directions {
	NORTH,
	SOUTH,
	EAST,
	WEST,
	NORTHWEST,
	NORTHEAST,
	SOUTHWEST,
	SOUTHEAST
};

enum sand_types {
	EMPTY,
	SAND,
	WATER,
	OIL,
	STONE,
	SMOKE,
	LAVA,
	VISITED,
};

enum radius_sizes {
	SMALL = 1,
	MEDIUM = 2,
	LARGE = 4,
};
class Sim {
private:
	int worldspace[SIM_WIDTH][SIM_HEIGHT];
	int priorworldspace[SIM_WIDTH][SIM_HEIGHT];
	//std::vector<Particle> particleList;
public:
	Sim();


	bool isEmpty(int x, int y);

	void setCell(int x, int y, sand_types sand);

	void swapCells(int x1, int y1, int x2, int y2, sand_types sand1, sand_types sand2);

	void sim_update();

	void draw(SDL_Renderer* renderer);
	
	int screenToWorld(int x);

	void placeSand(int x, int y, int r, sand_types MAT);

	void trace_points(int xcenter, int ycenter, int x, int y, sand_types MAT);

	void midPointCircle(int xcenter, int ycenter, int radius, sand_types MAT);
};