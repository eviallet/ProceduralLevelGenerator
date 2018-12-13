#include "Overworld.h"

Overworld::Overworld(Map *map) : Generator(map) {
}

void Overworld::generate() {
	// int levelLength = DEFAULT_WIDTH;

	for (int x = 0; x < map->getWidth(); x++)
		map->setTile(x, map->getHeight() - 1, Tiles::Ground::UP);

	map->setTile(2, map->getHeight() - 2, Tiles::Props::SIGN);
	map->setTile(map->getWidth() - 2, map->getHeight() - 2, Tiles::Objects::FLAG);

	randomizeTerrainPlatforms();
	p->randomize();
	randomizeTerrainHoles();
	p->randomize();
	placeBlocks();
}

void Overworld::randomizeTerrainPlatforms() {
	int y, length, height;
	for (int x = 5; x < map->getWidth(); x++) {
		if (p->noise(x, rand() % (int)MAX_Y, MAX_Z) > p->getStatsAt(90) && x + 5 < map->getWidth()-1) {
			length = rand() % 4 + 3;
			height = rand() % 3 + 2;
			y = map->getGroundHeight(x) - height;
			for (int i = 0; i < length; i ++) {
				map->setTile(x + i, y, Tiles::Terrain::PLATFORM);
				for (int j = 1; j <= height; j++)
					map->setTile(x + i, y + j, Tiles::Terrain::PLATFORM_GND);
			}
			x += length + 3;
		}
	}
}

void Overworld::randomizeTerrainHoles() {
}


void Overworld::placeBlocks() {
	int y, blockHeight = 2;
	// for all map length
	for (int x = 0; x < map->getWidth(); x++) {
		// if random noise at this point is greater than 85% other points (~1/4 odd)
		if (p->noise(x, rand() % (int)MAX_Y, MAX_Z) > p->getStatsAt(85)) {
			// and if mapGroundHeight + blockHeight is still in bounds
			if ((y = map->getGroundHeight(x)) != -1 && y != map->getHeight()-1 && y >= blockHeight) {
				int lastI = 0;
				// then, for a random length 1<=6
				for (int i = 0; i < rand() % 5 + 1; i++)
					// if the next point is still in bounds and if there is nothing between the ground and the block
					if (x + i < map->getWidth() && [&]() { for (int i = 1; i <= blockHeight; i++) if (map->getTile(x + i, y) != Tiles::Types::NONE) return false; return true; }()) {
						// place a question mark block (1/3) or a simple brick
						rand() % 3 == 0 ? map->setTile(x + i, y - blockHeight, Tiles::Blocks::QUESTION) : map->setTile(x + i, y - blockHeight, Tiles::Blocks::BRICK);
						lastI = i;
					}
					else break;
				// and add 5 to the current position, +(0~5) for the next blocks to start from
				x += lastI + rand() % 5 + 5;
			}
		}
	}
}