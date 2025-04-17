#pragma once
#include <SDL3/SDL.h>

#include <random>
#include <fstream>

static const int SIM_WIDTH = 321;
static const int SIM_HEIGHT = 181;
static const int SAND_SIZE = 4;
//static const int sand_types[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };


struct Particle {
	/// <summary>
	/// Liquid will move to the direct left and direct right if free, or straight down.
	/// </summary>
	bool isLiquid;
	/// <summary>
	/// Sand will move to diagonally left and right, or straight down.
	/// </summary>
	bool isSand;
	/// <summary>
	/// Solid objects will not move.
	/// </summary>
	bool isSolid;
	/// <summary>
	/// Flammable objects can be ignited, emitting smoke and decaying over time.
	/// </summary>
	bool isFlammable;

	/// <summary>
	/// Every time this particle is checked, its survival chance is rolled.
	/// If it rolls under the survival chance, it stays. If it doesn't, it is removed.
	/// </summary>
	float survivalChance;

	/// <summary>
	/// If material is liquid or sand, it will move down like it's under empty space.
	/// </summary>
	int density;

	/// <summary>
	/// Current spot on the grid for this particle.
	/// </summary>
	int currentSpot[2];

	/// <summary>
	/// When this particle can make a valid move, mark this spot as filled.
	/// </summary>
	int nextSpot[2];
};


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
	Sim() {
		for (int i = 0; i < SIM_WIDTH - 1; i++) {
			for (int j = 0; j < SIM_HEIGHT - 1; j++) {
				worldspace[i][j] = EMPTY;
				priorworldspace[i][j] = EMPTY;
				//setCell(i, j, EMPTY);
			}
		}

		printf("Sim constructed\n");
	}


	bool isEmpty(int x, int y) {
		if (priorworldspace[x][y] == EMPTY)
			return true;
		return false;
	}

	void setCell(int x, int y, sand_types sand) {
			worldspace[x][y] = sand;
			priorworldspace[x][y] = worldspace[x][y];
	}

	void swapCells(int x1, int y1, int x2, int y2, sand_types sand1, sand_types sand2) {
		setCell(x1, y1, sand2);
		setCell(x2, y2, sand1);
	}
	void sim_update() {
		for (int j = SIM_HEIGHT - 1; j >= 0; j--) {
			for (int i = 0; i < SIM_WIDTH - 1; i++) {
				switch (priorworldspace[i][j]) {
					case(SAND):
						{
							//printf("Updating Sand\n");
							if (isEmpty(i, j + 1) ){
								swapCells(i, j, i, j + 1, SAND, VISITED);
								//setCell(i, j, EMPTY);
								//setCell(i, j + 1, SAND);
							}

							else if (isEmpty(i - 1, j + 1) && isEmpty(i + 1, j + 1) ){
								bool dir = rand() % 2;
								if (dir == 0) {
									swapCells(i, j, i - 1, j + 1, SAND, VISITED);
									//setCell(i, j, EMPTY);
									//setCell(i - 1, j + 1, SAND);
								}
								if (dir == 1) {
									swapCells(i, j, i + 1, j + 1, SAND, VISITED);
									//setCell(i, j, EMPTY);
									//setCell(i - 1, j + 1, SAND);
								}
							}
							else if (isEmpty(i - 1, j + 1)){
								swapCells(i, j, i - 1, j + 1, SAND, VISITED);
								//worldspace[i][j] = 0;
								//worldspace[i - 1][j + 1] = 1;

							}
							else if (isEmpty(i + 1, j + 1)) {
								swapCells(i, j, i + 1, j + 1, SAND, VISITED);
								//worldspace[i][j] = 0;
								//worldspace[i + 1][j + 1] = 1;

							}

							else {
								//printf("Sand has not moved.\n");
								//setCell(i, j, SAND);
							}
							break;

						}
					case (WATER):
						{
							if (isEmpty(i, j + 1)){
								swapCells(i, j, i, j + 1, WATER, VISITED);
								//worldspace[i][j] = 0;
								//worldspace[i][j + 1] = 2;
							}
							else if (isEmpty(i + 1, j) && isEmpty(i - 1, j) ){
								//bool dir = rand() % 2;
								bool dir = rand() % 2;
								if (dir == 0) {
									swapCells(i, j, i - 1, j, WATER, VISITED);
									//worldspace[i][j] = 0;
									//worldspace[i - 1][j] = 2;
								}
								if (dir == 1) {
									swapCells(i, j, i + 1, j, WATER, VISITED);
									//worldspace[i][j] = 0;
									//worldspace[i + 1][j] = 2;
								}
							}
							else if (isEmpty(i + 1, j) ){
								swapCells(i, j, i + 1, j, WATER, VISITED);
								//worldspace[i][j] = 0;
								//worldspace[i + 1][j] = 2;
							}
							else if (isEmpty(i - 1, j )) {
								swapCells(i, j, i  - 1, j, WATER, VISITED);
								//worldspace[i][j] = 0;
								//worldspace[i - 1][j] = 2;

							}

							else {
								//printf("Sand has not moved.\n");
								setCell(i, j, WATER);
							}
							break;
						}
					case(VISITED): 
					{
							setCell(i, j, EMPTY);
							break;
					}
				}
			}
		}
	}
	void draw(SDL_Renderer* renderer) {
		for (int i = 0; i < SIM_WIDTH - 1; i++) {
			for (int j = 0; j < SIM_HEIGHT - 1; j++) {
				SDL_FRect sand = { (i - 4) * 4, (j - 4) * 4, 4, 4 };
				switch (worldspace[i][j])
				{
					case EMPTY: 
					{
						break;
					}
					case SAND:
					{
						//printf("Drawing sand at X: %d Y: %d \n", i, j);


						SDL_SetRenderDrawColor(renderer, 255, 153, 51, 255);
						SDL_RenderFillRect(renderer, &sand);

						break;
					}
					case WATER:
					{
						//printf("Drawing sand at X: %d Y: %d \n", i, j);
						SDL_SetRenderDrawColor(renderer, 51, 153, 255, 255);
						SDL_RenderFillRect(renderer, &sand);

						break;
					}
					default:

						break;
				}
				priorworldspace[i][j] = worldspace[i][j];

			}
		}
	}
	
	int screenToWorld(int x) {
		return (int)floor(x / SAND_SIZE) + SAND_SIZE;
	}

	void placeSand(int x, int y, int r, sand_types MAT) {
		printf("Placing sand at %d, %d\n", screenToWorld(x), screenToWorld(y));
		midPointCircle(screenToWorld(x), screenToWorld(y), r, MAT);
		
	}
	void placeWater(int x, int y) {
		printf("Placing sand at %d, %d\n", (int)floor(x / 4) + 4, (int)floor(y / 4) + 4);
		setCell((int)floor(x / 4) + 4, (int)floor(y / 4) + 4, WATER);

	}

	void trace_points(int xcenter, int ycenter, int x, int y, sand_types MAT) {
		setCell(xcenter + x, ycenter + y, MAT);
		setCell(xcenter - x, ycenter + y, MAT);
		setCell(xcenter + x, ycenter - y, MAT);
		setCell(xcenter - x, ycenter - y, MAT);
		setCell(xcenter + y, ycenter + x, MAT);
		setCell(xcenter - y, ycenter + x, MAT);
		setCell(xcenter + y, ycenter - x, MAT);
		setCell(xcenter - y, ycenter - x, MAT);

	}
	void midPointCircle(int xcenter, int ycenter, int radius, sand_types MAT) {
		if (radius == 1) {
			setCell(xcenter, ycenter, MAT);
		}else{
			int x = 0;
			int y = radius;
			int p = 1 - radius;
			trace_points(xcenter, ycenter, x, y, MAT);
			while (x < y) {
				x++;
				if (p < 0) {
					p = p + 2 * x + 1;
				}
				else {
					y--;
					p = p + 2 * (x - y) + 1;
				}
				trace_points(xcenter, ycenter, x, y, MAT);
			}
		}
	}

};