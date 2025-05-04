#include <sandsim.hpp>

Sim::Sim() {
	for (int i = 0; i < SIM_WIDTH - 1; i++) {
		for (int j = 0; j < SIM_HEIGHT - 1; j++) {
			worldspace[i][j] = EMPTY;
			priorworldspace[i][j] = EMPTY;
			//setCell(i, j, EMPTY);
		}
	}

	//mt(rd());

	_p_sand.density = 2;
	_p_water.density = 0;
	_p_oil.density = 1;
	_p_smoke.density = -1;
	_p_empty.density = -100;

	printf("Sim constructed\n");
}

void Sim::sim_update() {
	for (int j = SIM_HEIGHT; j >= 0; j--) {
		for (int i = 0; i < SIM_WIDTH - 1; i++) {
			switch (priorworldspace[i][j]) {
			case(SAND):
			{
				//printf("Updating Sand\n");
				if (isEmpty(i, j + 1)) {
					swapCells(i, j, i, j + 1, SAND, VISITED);
				}

				else if (isEmpty(i - 1, j + 1) && isEmpty(i + 1, j + 1)) {
					bool dir = rand() % 2;
					if (dir == 0) {
						swapCells(i, j, i - 1, j + 1, SAND, VISITED);
					}
					if (dir == 1) {
						swapCells(i, j, i + 1, j + 1, SAND, VISITED);
					}
				}
				else if (isEmpty(i - 1, j + 1)) {
					swapCells(i, j, i - 1, j + 1, SAND, VISITED);

				}
				else if (isEmpty(i + 1, j + 1)) {
					swapCells(i, j, i + 1, j + 1, SAND, VISITED);

				}

				else {
					setCell(i, j, SAND);
				}
				break;

			}
			case (WATER):
			{
				if (isEmpty(i, j + 1)) {
					swapCells(i, j, i, j + 1, WATER, VISITED);
				}
				else if (isEmpty(i + 1, j) && isEmpty(i - 1, j)) {
					bool dir = rand() % 2;
					if (dir == 0) {
						swapCells(i, j, i - 1, j, WATER, VISITED);

					}
					if (dir == 1) {
						swapCells(i, j, i + 1, j, WATER, VISITED);
					}
				}
				else if (isEmpty(i + 1, j)) {
					swapCells(i, j, i + 1, j, WATER, VISITED);
				}
				else if (isEmpty(i - 1, j)) {
					swapCells(i, j, i - 1, j, WATER, VISITED);
				}

				else {
					setCell(i, j, WATER);
				}
				break;
			}
			case (SMOKE):
			{
				//like sand but up + chance to decay
				//printf("Updating Sand\n");
				if (isEmpty(i, j - 1)) {
					swapCells(i, j, i, j - 1, SMOKE, VISITED);
				}

				else if (isEmpty(i - 1, j - 1) && isEmpty(i + 1, j - 1)) {
					bool dir = rand() % 2;
					if (dir == 0) {
						swapCells(i, j, i - 1, j - 1, SMOKE, VISITED);
					}
					if (dir == 1) {
						swapCells(i, j, i + 1, j - 1, SMOKE, VISITED);
					}
				}
				else if (isEmpty(i - 1, j - 1)) {
					swapCells(i, j, i - 1, j - 1, SMOKE, VISITED);

				}
				else if (isEmpty(i + 1, j - 1)) {
					swapCells(i, j, i + 1, j - 1, SMOKE, VISITED);

				}

				else {
					setCell(i, j, SMOKE);
				}
				break;
			}
			case (OIL):
			{
				//check all possibly empty routes first
				if (isEmpty(i, j + 1)) {
					swapCells(i, j, i, j + 1, OIL, VISITED);
				}
				else if (isEmpty(i + 1, j) && isEmpty(i - 1, j)) {
					bool dir = rand() % 2;
					if (dir == 0) {
						swapCells(i, j, i - 1, j, OIL, VISITED);

					}
					if (dir == 1) {
						swapCells(i, j, i + 1, j, OIL, VISITED);
					}
				}
				else if (isEmpty(i + 1, j)) {
					swapCells(i, j, i + 1, j, OIL, VISITED);
				}
				else if (isEmpty(i - 1, j)) {
					swapCells(i, j, i - 1, j, OIL, VISITED);
				}
				//then check density
				else if (densityCheck(getCell(i, j), getCell(i, j + 1))) {
					swapCells(i, j, i, j + 1, priorworldspace[i][j], priorworldspace[i][j + 1]);
				}
				else if (densityCheck(getCell(i, j), getCell(i + 1, j)) && densityCheck(getCell(i, j), getCell(i - 1, j))){
					bool dir = rand() % 2;
					if (dir == 0) {
						swapCells(i, j, i - 1, j, priorworldspace[i][j], priorworldspace[i - 1][j]);

					}
					if (dir == 1) {
						swapCells(i, j, i + 1, j, priorworldspace[i][j], priorworldspace[i + 1][j]);
					}
				}
				else if (densityCheck(getCell(i, j), getCell(i + 1, j))) {
					swapCells(i, j, i + 1, j, priorworldspace[i][j], priorworldspace[i + 1][j]);
				}
				else if (densityCheck(getCell(i, j), getCell(i - 1, j))) {
					swapCells(i, j, i - 1, j, priorworldspace[i][j], priorworldspace[i - 1][j]);

				}
				else {
					setCell(i, j, OIL);
				}
				break;

			}
			case(WOOD):
			{
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

void Sim::draw(SDL_Renderer* renderer) {
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
			case SMOKE:
			{
				SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
				SDL_RenderFillRect(renderer, &sand);
				break;
			}
			case OIL:
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 42, 255);
				SDL_RenderFillRect(renderer, &sand);
				break;
			}
			case WOOD:
			{
				SDL_SetRenderDrawColor(renderer, 88, 57, 39, 255);
				SDL_RenderFillRect(renderer, &sand);
			}
			default:

				break;
			}
			priorworldspace[i][j] = worldspace[i][j];

		}
	}
}


bool Sim::isEmpty(int x, int y) {
	if (priorworldspace[x][y] == EMPTY)
		return true;
	return false;
}

void Sim::setCell(int x, int y, sand_types sand) {
	worldspace[x][y] = sand;
	priorworldspace[x][y] = worldspace[x][y];
}

void Sim::swapCells(int x1, int y1, int x2, int y2, sand_types sand1, sand_types sand2) {
	setCell(x1, y1, sand2);
	setCell(x2, y2, sand1);
}

int Sim::screenToWorld(int x) {
	return (int)floor(x / SAND_SIZE) + SAND_SIZE;
}


void Sim::placeSand(int x, int y, int r, sand_types MAT) {
	printf("Placing sand at %d, %d\n", screenToWorld(x), screenToWorld(y));
	midPointCircle(screenToWorld(x), screenToWorld(y), r, MAT);

}


void Sim::trace_points(int xcenter, int ycenter, int x, int y, sand_types MAT) {
		setCell(xcenter + x, ycenter + y, MAT);
		setCell(xcenter - x, ycenter + y, MAT);
		setCell(xcenter + x, ycenter - y, MAT);
		setCell(xcenter - x, ycenter - y, MAT);
		setCell(xcenter + y, ycenter + x, MAT);
		setCell(xcenter - y, ycenter + x, MAT);
		setCell(xcenter + y, ycenter - x, MAT);
		setCell(xcenter - y, ycenter - x, MAT);
}

void Sim::midPointCircle(int xcenter, int ycenter, int radius, sand_types MAT) {
	if (radius == 1) {
		setCell(xcenter, ycenter, MAT);
	}
	else {
		int x = radius;
		int y = 0;
		int p = 1 - radius;
		trace_points(xcenter, ycenter, x, y, MAT);
		while (x > y) {
			y++;
			if (p < 0) {
				p = p + 2 * y + 1;
			}
			else {
				x--;
				p = p + 2 * (y - x) + 1;
			}

			if (x < y)
				break;

			trace_points(xcenter, ycenter, x, y, MAT);
		}
	}
}

void Sim::waterMovement(int x, int y) {
	if (isEmpty(x, y + 1)) {
		swapCells(x, y, x, y + 1, WATER, VISITED);

	}
	else if (isEmpty(x + 1, y) && isEmpty(x - 1, y)) {
		//bool dir = rand() % 2;
		bool dir = rand() % 2;
		if (dir == 0) {
			swapCells(x, y, x - 1, y, WATER, VISITED);
		}
		if (dir == 1) {
			swapCells(x, y, x + 1, y, WATER, VISITED);

		}
	}
	else if (isEmpty(x + 1, y)) {
		swapCells(x, y, x + 1, y, WATER, VISITED);
	}
	else if (isEmpty(x - 1, y)) {
		swapCells(x, y, x - 1, y, WATER, VISITED);

	}
	else {
		setCell(x, y, WATER);
	}
}

void Sim::particleMovement(int x, int y) {


}

void Sim::smokeMovement(int x, int y) {


}

Particle Sim::getCell(int x, int y) {
	switch (priorworldspace[x][y]) {
		case SAND:
			return _p_sand;
			break;
		case OIL:
			return _p_oil;
			break;
		case WATER:
			return _p_water;
			break;
		case SMOKE:
			return _p_smoke;
			break;
		default:
			return _p_empty;
			break;
	}
}

bool Sim::densityCheck(Particle moving_cell, Particle checking_cell) {
	if (moving_cell.density > checking_cell.density)
		return true;
	return false;
}