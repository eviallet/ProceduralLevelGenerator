#include "generator.h"

const int Generator::DIRECTIONS[][2] = { 
	{0,-1}, // LEFT
	{0,1},	// RIGHT
	{-1,0},	// UP
	{1,0}	// DOWN
};


void Generator::randomize(Map *map, MapType type) {
    switch(type) {
    case OVERWORLD:
		generateOverworld(map);
        break;
    case UNDERGROUND:
		generateUnderground(map, 
			75, // nbTunnels
			9	// maxLength
		);
        break;
    }
}

void Generator::generateOverworld(Map *map) {
	// int levelLength = DEFAULT_WIDTH;
	
	for (int x = 0; x < map->getWidth(); x++)
		map->setTile(x, map->getHeight() - 1, Tiles::Ground::FLAT);
	
	map->setTile(2, map->getHeight() - 2, Tiles::Props::SIGN);
	map->setTile(map->getWidth() - 2, map->getHeight() - 2, Tiles::Props::FLAG);
}

void Generator::generateUnderground(Map *map, int nbTunnels, int maxLength) {
    // hold the current and previous direction index, ie 0 for LEFT, 1 for RIGHT...
    int curDirIndex, prevDirIndex = rand() % 4;
    // start from a random point on the map ; it must be included in [1;width-1]
    int curPoint[] = { 
		(int)floor(percent()*(map->getHeight()-2))+1,	// X
		(int)floor(percent()*(map->getWidth()-2))+1		// Y
	};

	map->fill(Tiles::Ground::CAVE_GND);
	
	// ensure that the map is long enough
	int leftMost, rightMost;
	do {
		// will draw %nbTunnels% tunnels.
		for (int i = 0; i < nbTunnels; i++) {
			// choose a random direction, not the same nor the opposite as the previous one (ie if previous was LEFT, we shall not go RIGHT)
			do {
				curDirIndex = rand() % 4;
			} while (
				(DIRECTIONS[curDirIndex][X] == DIRECTIONS[prevDirIndex][X] && DIRECTIONS[curDirIndex][Y] == DIRECTIONS[prevDirIndex][Y]) ||
				(DIRECTIONS[curDirIndex][X] == -DIRECTIONS[prevDirIndex][X] && DIRECTIONS[curDirIndex][Y] == -DIRECTIONS[prevDirIndex][Y]));
			prevDirIndex = curDirIndex;
			// choose a random size for this tunnel
			int tunnelSize = (int)ceil(percent()*maxLength);
			for (int j = 0; j < tunnelSize; j++) {
				// we first have to check if, going in our direction, we won't encounter any border of the map, stopping the drawing in that case.
				int futurePoint[2];
				futurePoint[X] = curPoint[X] + DIRECTIONS[curDirIndex][X];
				futurePoint[Y] = curPoint[Y] + DIRECTIONS[curDirIndex][Y];
				if (futurePoint[Y] < 1 || futurePoint[Y] > map->getHeight() - 2 || futurePoint[X] < 1 || futurePoint[X] > map->getWidth() - 2)
					break;
				// then draw this point
				curPoint[X] = futurePoint[X];
				curPoint[Y] = futurePoint[Y];
				map->setTile(curPoint[X], curPoint[Y], Tiles::Types::NONE);
			}
		}

		int x = 0, y = 0;
		while (x < map->getWidth()) {
			if (map->getTile(x, y).getType() == Tiles::Types::NONE) {
				leftMost = x;
				break;
			}
			else {
				y++;
				if (y == map->getHeight() - 1) {
					y = 0;
					x++;
				}
			}
		}

		x = map->getWidth(); y = 0;
		while (x >= 0) {
			if (map->getTile(x, y).getType() == Tiles::Types::NONE) {
				rightMost = x;
				break;
			}
			else {
				y++;
				if (y == map->getHeight()-1) {
					y = 0;
					x--;
				}
			}
		}

	} while (abs(leftMost - rightMost) < map->getWidth() / 1.75);


	// show the border of the blocks if they are connected with NONE or not-Ground types
	for (int y = 0; y < map->getHeight(); y++) {
		for (int x = 1; x < map->getWidth(); x++) {
			if (Tile::isGround(map->getTile(x, y).getType())) {
				if (map->getTile(x, y) != map->getTile(x - 1, y))
					map->setTile(x, y, Tiles::Ground::CAVE_GND_LEFT);
			}
		}
	}
	for (int y = 0; y < map->getHeight(); y++) {
		for (int x = 0; x < map->getWidth() - 1; x++) {
			if (Tile::isGround(map->getTile(x, y).getType())) {
				if (map->getTile(x, y) != map->getTile(x + 1, y))
					map->setTile(x, y, Tiles::Ground::CAVE_GND_RIGHT);
			}
		}
	}
	for (int y = 0; y < map->getHeight() - 1; y++) {
		for (int x = 0; x < map->getWidth(); x++) {
			if (Tile::isGround(map->getTile(x, y).getType())) {
				if (map->getTile(x, y) != map->getTile(x, y + 1))
					map->setTile(x, y, Tiles::Ground::CAVE_GND_DOWN);
			}
		}
	}
	for (int y = 1; y < map->getHeight(); y++) {
		for (int x = 0; x < map->getWidth(); x++) {
			if (Tile::isGround(map->getTile(x, y).getType())) {
				if (map->getTile(x, y) != map->getTile(x, y - 1))
					map->setTile(x, y, Tiles::Ground::CAVE_GND_UP);
			}
		}
	}
				
}

void Generator::placeStructures(Map *map) {}
void Generator::placeCollectibles(Map *map) {}
void Generator::populate(Map *map) {}
void Generator::placeProps(Map *map) {}

// Simply returns a percentage
double Generator::percent() {
	return (double)rand() / RAND_MAX;
}
