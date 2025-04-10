#pragma once
#include <SDL3/SDL.h>

#include <random>
#include <fstream>

static const int SIM_WIDTH = 321;
static const int SIM_HEIGHT = 181;
//static const int sand_types[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

/*
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
	b2Vec2 currentSpot;

	/// <summary>
	/// When this particle can make a valid move, mark this spot as filled.
	/// </summary>
	b2Vec2 nextSpot;
};
*/

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
};
class Sim {
private:
	int worldspace[SIM_WIDTH][SIM_HEIGHT];
	int priorworldspace[SIM_WIDTH][SIM_HEIGHT];

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
	}

	void swapCells(int x1, int y1, int x2, int y2, sand_types sand1, sand_types sand2) {
		setCell(x1, y1, sand2);
		setCell(x2, y2, sand1);
	}
	void sim_update() {
		for (int i = 0; i < SIM_WIDTH - 1; i++) {
			for (int j = 0; j < SIM_HEIGHT - 1; j++) {
				switch (priorworldspace[i][j]) {
					case(SAND):
						{
							//printf("Updating Sand\n");
							if (isEmpty(i, j + 1) ){
								swapCells(i, j, i, j + 1, SAND, EMPTY);
								//setCell(i, j, EMPTY);
								//setCell(i, j + 1, SAND);
							}

							else if (isEmpty(i - 1, j + 1) && isEmpty(i + 1, j + 1) ){
								bool dir = rand() % 2;
								if (dir == 0) {
									swapCells(i, j, i - 1, j + 1, SAND, EMPTY);
									//setCell(i, j, EMPTY);
									//setCell(i - 1, j + 1, SAND);
								}
								if (dir == 1) {
									swapCells(i, j, i + 1, j + 1, SAND, EMPTY);
									//setCell(i, j, EMPTY);
									//setCell(i - 1, j + 1, SAND);
								}
							}
							else if (isEmpty(i - 1, j + 1)){
								swapCells(i, j, i - 1, j + 1, SAND, EMPTY);
								//worldspace[i][j] = 0;
								//worldspace[i - 1][j + 1] = 1;

							}
							else if (isEmpty(i + 1, j + 1)) {
								swapCells(i, j, i + 1, j + 1, SAND, EMPTY);
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
								swapCells(i, j, i, j + 1, WATER, EMPTY);
								//worldspace[i][j] = 0;
								//worldspace[i][j + 1] = 2;
							}

							/*
							else if (priorworldspace[i - 1][j] == 0 && priorworldspace[i + 1][j] == 0) {
								worldspace[i][j] = 0;
								bool dir = rand() % 2;
								if (dir == 0) {
									worldspace[i][j] = 0;
									worldspace[i - 1][j] = 2;
								}
								if (dir == 1) {
									worldspace[i][j] = 0;
									worldspace[i + 1][j] = 2;
								}
							}
							else if (priorworldspace[i - 1][j] == 0) {
								worldspace[i][j] = 0;
								worldspace[i - 1][j] = 2;
							}
							else if (priorworldspace[i + 1][j] == 0) {
								worldspace[i][j] = 0;
								worldspace[i + 1][j] = 2;
							}
							else {
								worldspace[i][j] = 2;
							}
							break;
							*/
							else if (isEmpty(i + 1, j) && isEmpty(i - 1, j) ){
								//bool dir = rand() % 2;
								bool dir = rand() % 2;
								if (dir == 0) {
									swapCells(i, j, i - 1, j, WATER, EMPTY);
									//worldspace[i][j] = 0;
									//worldspace[i - 1][j] = 2;
								}
								if (dir == 1) {
									swapCells(i, j, i + 1, j, WATER, EMPTY);
									//worldspace[i][j] = 0;
									//worldspace[i + 1][j] = 2;
								}
							}
							else if (isEmpty(i + 1, j) ){
								swapCells(i, j, i + 1, j, WATER, EMPTY);
								//worldspace[i][j] = 0;
								//worldspace[i + 1][j] = 2;
							}
							else if (isEmpty(i - 1, j )) {
								swapCells(i, j, i  - 1, j, WATER, EMPTY);
								//worldspace[i][j] = 0;
								//worldspace[i - 1][j] = 2;

							}

							else {
								//printf("Sand has not moved.\n");
								//setCell(i, j, WATER);
							}
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

	void placeSand(int x, int y) {
		printf("Placing sand at %d, %d\n", (int)floor(x / 4) + 4, (int)floor(y / 4) + 4);
		setCell((int)floor(x/4) + 4, (int)floor(y/4) + 4, SAND);
	}
	void placeWater(int x, int y) {
		printf("Placing sand at %d, %d\n", (int)floor(x / 4) + 4, (int)floor(y / 4) + 4);
		setCell((int)floor(x / 4) + 4, (int)floor(y / 4) + 4, WATER);

	}
};