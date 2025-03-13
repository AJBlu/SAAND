#pragma once
#include <SDL3/SDL.h>

#include <random>
#include <fstream>

static const int SIM_WIDTH = 1281;
static const int SIM_HEIGHT = 721;
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
				if(priorworldspace[i][j] == 1)
				{
					//printf("Updating Sand\n");
					if (priorworldspace[i][j + 1] == 0) {
						worldspace[i][j] = 0;
						worldspace[i][j + 1] = 1;
					}
					/*
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
					*/
					else {
						//printf("Sand has not moved.\n");
						worldspace[i][j] = 1;
					}

				}
			}
		}
	}
	void draw(SDL_Renderer* renderer) {
		for (int i = 0; i < SIM_WIDTH - 1; i++) {
			for (int j = 0; j < SIM_HEIGHT - 1; j++) {
				switch (worldspace[i][j])
				{
					case 0: 
					{
						break;
					}
					case 1:
					{
						//printf("Drawing sand at X: %d Y: %d \n", i, j);
						
						SDL_FRect sand = { i - 2, j - 2, 4, 4 };
						
						SDL_SetRenderDrawColor(renderer, 255, 153, 51, 255);
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
		printf("Placing sand at %d, %d", x, y);
		worldspace[x][y] = 1;
	}
};