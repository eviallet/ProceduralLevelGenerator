#include "Overworld.h"

Overworld::Overworld(Map *map) : Generator(map) {
}

void Overworld::generate() {
	// int levelLength = DEFAULT_WIDTH;

	for (int x = 0; x < map->getWidth(); x++)
		map->setTile(x, map->getHeight() - 1, Tiles::Ground::UP);

	map->setTile(2, map->getHeight() - 2, Tiles::Props::SIGN);
	map->setTile(map->getWidth() - 2, map->getHeight() - 2, Tiles::Objects::FLAG);

	randomizeTerrainHeight();
}

void Overworld::randomizeTerrainHeight() {
	int y = 0;
	for (int x = 0; x < map->getWidth(); x++) {
		if (p->noise(x, rand() % (int)MAX_Y, MAX_Z) < p->getAverage(MAX_X, MAX_Y, MAX_Z)) {
			if ((y = map->getMapGroundHeight(x)) != -1 && map->getTile(x, y) == Tiles::Types::NONE)
				map->setTile(x, y, Tiles::Props::BUSH);
		}
	}
}