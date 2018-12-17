#include "map.h"

Map::Map(int w, int h) 
	: _height(h), _width(w) {
	_map = new Tile*[_height];
	for (int i = 0; i < _height; i++)
		_map[i] = new Tile[_width];
}

void Map::fill(int type) {
    for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++)
			_map[y][x].setType(type);
}

void Map::setTile(int x, int y, int type) {
    _map[_height - 1 - y][x].setType(type);
}

Tile Map::getTile(int x, int y) const {
    return _map[y][x];
}

int Map::getWidth() const {
	return _width;
}

int Map::getHeight() const {
    return _height;
}

int Map::getGroundHeight(int x) {
	for (int y = 0; y < _height; y++)
		if (!getTile(x, y).isGround())
			return y;
	return -1;
}