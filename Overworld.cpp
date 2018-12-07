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
	int y = 0, blockHeight = 2;
	for (int x = 0; x < map->getWidth(); x++) {
		if (p->noise(x, rand() % (int)MAX_Y, MAX_Z) > p->getThirdQuartile()) {
			if ((y = map->getMapGroundHeight(x)) != -1 &&
					y >= blockHeight &&
					[&]() { for (int i = 1; i <= blockHeight; i++) if (map->getTile(x, y) != Tiles::Types::NONE) return false; return true; }()
					)
				rand() % 3 == 0 ? map->setTile(x, y - blockHeight, Tiles::Blocks::QUESTION) : map->setTile(x, y - blockHeight, Tiles::Blocks::BRICK);
		}
	}
}