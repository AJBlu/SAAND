#pragma once
#include <SDL3/SDL.h>

#include <random>
#include <fstream>

static const int SIM_WIDTH = 321;
static const int SIM_HEIGHT = 181;
static const int sand_types[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
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
				worldspace[i][j] = 0;
				priorworldspace[i][j] = 0;
			}
		}
		printf("Sim constructed\n");
	}

	void sim_update() {
		for (int i = 0; i < SIM_WIDTH - 1; i++) {
			for (int j = 0; j < SIM_HEIGHT - 1; j++) {
				switch (priorworldspace[i][j]) {
					case(1):
						{
							//printf("Updating Sand\n");
							if (priorworldspace[i][j + 1] == 0) {
								worldspace[i][j] = 0;
								worldspace[i][j + 1] = 1;
							}

							else if (priorworldspace[i - 1][j + 1] == 0 && priorworldspace[i + 1][j + 1] == 0) {
								bool dir = rand() % 2;
								if (dir == 0) {
									worldspace[i][j] = 0;
									worldspace[i - 1][j + 1] = 1;
								}
								if (dir == 1) {
									worldspace[i][j] = 0;
									worldspace[i - 1][j + 1] = 1;
								}
							}
							else if (priorworldspace[i - 1][j + 1] == 0) {
								worldspace[i][j] = 0;
								worldspace[i - 1][j + 1] = 1;

							}
							else if (priorworldspace[i + 1][j + 1] == 0) {
								worldspace[i][j] = 0;
								worldspace[i + 1][j + 1] = 1;

							}

							else {
								//printf("Sand has not moved.\n");
								worldspace[i][j] = 1;
							}
							break;

						}
					case (2):
						{
							if (priorworldspace[i][j + 1] == 0) {
								worldspace[i][j] = 0;
								worldspace[i][j + 1] = 2;
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
							else if (priorworldspace[i + 1][j] == 0 && priorworldspace[i - 1][j] == 0) {
								bool dir = rand() % 2;
								if (dir == 0) {
									worldspace[i][j] = 0;
									worldspace[i + 1][j] = 2;
								}
								if (dir == 1) {
									worldspace[i][j] = 0;
									worldspace[i - 1][j] = 2;
								}
							}
							else if (priorworldspace[i + 1][j] == 0) {
								worldspace[i][j] = 0;
								worldspace[i + 1][j] = 2;

							}
							else if (priorworldspace[i - 1][j] == 0) {
								worldspace[i][j] = 0;
								worldspace[i - 1][j] = 2;

							}

							else {
								//printf("Sand has not moved.\n");
								worldspace[i][j] = 2;
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
					case 0: 
					{
						break;
					}
					case 1:
					{
						//printf("Drawing sand at X: %d Y: %d \n", i, j);
						
						
						SDL_SetRenderDrawColor(renderer, 255, 153, 51, 255);
						SDL_RenderFillRect(renderer, &sand);

						break;
					}
					case 2:
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
		worldspace[(int)floor(x/4) + 4][(int)floor(y/4) + 4] = 1;
	}
	void placeWater(int x, int y) {
		printf("Placing sand at %d, %d\n", (int)floor(x / 4) + 4, (int)floor(y / 4) + 4);
		worldspace[(int)floor(x / 4) + 4][(int)floor(y / 4) + 4] = 2;
	}
};