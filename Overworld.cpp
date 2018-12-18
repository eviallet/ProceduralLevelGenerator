#include "Overworld.h"

Overworld::Overworld(Map *map) : Generator(map) {
}

void Overworld::generate() {
	for (int x = 0; x < map->getWidth(); x++)
		map->setTile(x, 0, Tiles::Ground::UP);

	map->setTile(SIGN_POS, 1, Tiles::Props::SIGN);
	map->setTile(map->getWidth() - 1 - FLAG_POS, 1, Tiles::Objects::FLAG);
	
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
					map->setTile(x + i, 0, Tiles::NONE);
				map->setTile(x - 1, 0, Tiles::Ground::UP_RIGHT);
				map->setTile(x + length, 0, Tiles::Ground::UP_LEFT);
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
			int height = Random::uniform(1, 4);
			int y = map->getGroundHeight(x);
			if (y != -1) {
				y += height;
				// place platforms
				for (int i = 0; i < length; i++) {
					if(i == 0)
						map->setTile(x + i, y, Tiles::Terrain::PLATFORM_UP_LEFT);
					else if(i == length - 1)
						map->setTile(x + i, y, Tiles::Terrain::PLATFORM_UP_RIGHT);
					else
						map->setTile(x + i, y, Tiles::Terrain::PLATFORM);
					// and link them to the ground
					for (int j = 1; j <= y - map->getGroundHeight(x + i); j++) {
						if(i == 0)
							map->setTile(x + i, y - j, Tiles::Terrain::PLATFORM_LEFT);
						else if(i == length - 1)
							map->setTile(x + i, y - j, Tiles::Terrain::PLATFORM_RIGHT);
						else
							map->setTile(x + i, y - j, Tiles::Terrain::PLATFORM_GND);
					}
				}
				x += length + 3;
			}
		}
	}
}


void Overworld::placeBlocks() {
	int y, blockHeight = 2;
	// for all map length
	for (int x = 4; x < map->getWidth() - FLAG_POS - 7; x++) {
		// if random noise at this point is greater than 85% other points
		if (p->noise(x, Random::uniform(0, (int)MAX_Y), MAX_Z) > p->getStatsAt(85) && map->getTile(x, blockHeight) == Tiles::NONE) {
			// and if mapGroundHeight + blockHeight is still in bounds
			if ((y = map->getGroundHeight(x)) > 0 && y + blockHeight < map->getHeight()) {
				int lastI = 0;
				// then, for a random length 1<=5
				int length = Random::uniform(1, 5);
				for (int i = 0; i < length; i++) {
					// if the next point is still in bounds and if there is no ground in the future block spot
					if (map->getGroundHeight(x + i) && map->getTile(x, y + blockHeight).isStandable()) {
						// place a question mark block (1/3 odd) or a brick
						Random::uniform(0, 2) == 0 ? map->setTile(x + i, y + blockHeight, Tiles::Blocks::QUESTION) : map->setTile(x + i, y + blockHeight, Tiles::Blocks::BRICK);
						lastI = i;
					}
					else break;
				}
				// and add 5 to the current position, +(0~4) for the next blocks to start from
				x += lastI + Random::uniform(5, 9);
			}
		}
	}
}

// [&]() { for (int j = 0; j <= blockHeight; j++) if (map->getTile(x, y + j) != Tiles::NONE) return false; return true; }()