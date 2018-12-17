#include "Overworld.h"

Overworld::Overworld(Map *map) : Generator(map) {
}

void Overworld::generate() {
	for (int x = 0; x < map->getWidth(); x++)
		map->setTile(x, map->getHeight() - 1, Tiles::Ground::UP);

	map->setTile(SIGN_POS, map->getHeight() - 2, Tiles::Props::SIGN);
	map->setTile(map->getWidth() - FLAG_POS, map->getHeight() - 2, Tiles::Objects::FLAG);

	randomizeTerrainHoles();
	p->randomize();
	randomizeTerrainPlatforms();
	p->randomize();
	placeBlocks();
}

void Overworld::randomizeTerrainHoles() {
	for (int x = 5; x < map->getWidth(); x++) {
		if (p->noise(x, Random::uniform(0, (int)MAX_Y), MAX_Z) > p->getStatsAt(90)) {
			int length = Random::uniform(1, 4);
			if (x + length < map->getWidth() + 1) {
				for (int i = 0; i < length; i++)
					map->setTile(x + i, map->getHeight() - 1, Tiles::NONE);
				x += length + 3;
			}
		}
	}
}

void Overworld::randomizeTerrainPlatforms() {
	// for all map length
	for (int x = 5; x < map->getWidth(); x++) {
		// if random noise at this point is greater than 90% other points
		if (p->noise(x, Random::uniform(0, (int)MAX_Y), MAX_Z) > p->getStatsAt(90) && x + 5 < map->getWidth()-1) {
			// then, for a random length
			int length = Random::uniform(3, 6);
			// at a random height
			int height = Random::uniform(2, 4);
			int y = map->getGroundHeight(x) - height;
			if (y != -1) {
				// place platforms
				for (int i = 0; i < length; i++) {
					map->setTile(x + i, y, Tiles::Terrain::PLATFORM);
					int distToGround = map->getGroundHeight(x + i) - y;
					// and link them to the ground
					for (int j = 1; j <= distToGround; j++)
						map->setTile(x + i, y + j, Tiles::Terrain::PLATFORM_GND);
				}
				x += length + 3;
			}
		}
	}
}


void Overworld::placeBlocks() {
	int y, blockHeight = 2;
	// for all map length
	for (int x = 4; x < map->getWidth(); x++) {
		// if random noise at this point is greater than 85% other points
		if (p->noise(x, Random::uniform(0, (int)MAX_Y), MAX_Z) > p->getStatsAt(85)) {
			// and if mapGroundHeight + blockHeight is still in bounds
			if ((y = map->getGroundHeight(x)) != -1 && y != map->getHeight()-1 && y >= blockHeight) {
				int lastI = 0;
				// then, for a random length 1<=5
				int length = Random::uniform(1, 5);
				for (int i = 0; i < length; i++)
					// if the next point is still in bounds and if there is nothing between the ground and the block
					if (x + i < map->getWidth() && [&]() { for (int i = 1; i <= blockHeight; i++) if (map->getTile(x + i, y) != Tiles::NONE) return false; return true; }()) {
						// place a question mark block (1/3 odd) or a brick
						Random::uniform(0,2) == 0 ? map->setTile(x + i, y - blockHeight, Tiles::Blocks::QUESTION) : map->setTile(x + i, y - blockHeight, Tiles::Blocks::BRICK);
						lastI = i;
					}
					else break;
				// and add 5 to the current position, +(0~4) for the next blocks to start from
				x += lastI + Random::uniform(5, 9);
			}
		}
	}
}