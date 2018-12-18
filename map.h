#ifndef MAP_H
#define MAP_H

#include "tile.h"

class Map {
public:
	Map(int w, int h);
	void fill(int type);
	void setTile(int row, int col, int type);
    Tile getTile(int row, int col) const;
    int getWidth() const;
    int getHeight() const;
	int getGroundHeight(int x);
private:
	Tile** _map;
    int _width, _height;
};


#endif //MAP_H
