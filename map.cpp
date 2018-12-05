#include "map.h"

Map::Map(int w, int h) {
	_map = new Tile*[h];
	for (int i = 0; i < h; i++)
		_map[i] = new Tile[w];
	_width = w;
    _height = h;
}

void Map::fill(int type) {
    for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++)
			_map[y][x].setType(type);
}

void Map::setTile(int row, int col, int type) {
    _map[col][row].setType(type);
}

Tile Map::getTile(int row, int col) const {
    return _map[col][row];
}

int Map::getWidth() const {
	return _width;
}

int Map::getHeight() const {
    return _height;
}

int Map::getMapGroundHeight(int x) {
	for (int y = _height - 1; y >= 0; y--)
		if (!getTile(x, y).isGround())
			return y;
	return -1;
}