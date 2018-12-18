#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <qpixmap.h>

namespace Tiles {
	enum Types {
		NONE,
		GroundType=1000,
		PropType=2000,
		BlockType=3000,
		ObjectType=4000,
		TerrainType=5000
	};
	
	enum Ground {
		FIRST_GROUND = GroundType,
		GND = FIRST_GROUND,
		UP,
		LEFT,
		RIGHT,
		DOWN,
		UP_LEFT,
		UP_RIGHT,
		INVALID_GROUND
	};
	
	enum Props {
		FIRST_PROP = PropType,
		BUSH = FIRST_PROP,
		SIGN,
		INVALID_PROP
	};

	enum Blocks {
		FIRST_BLOCK = BlockType,
		QUESTION = FIRST_BLOCK,
		BRICK,
		INVALID_BLOCK
	};
	
	enum Objects {
		FIRST_OBJECT = ObjectType,
		COIN = FIRST_OBJECT,
		FLAG,
		PIPE,		
		INVALID_OBJECT
	};

	enum Terrain {
		FIRST_TERRAIN = TerrainType,
		PLATFORM = FIRST_TERRAIN,
		PLATFORM_GND,
		PLATFORM_LEFT,
		PLATFORM_RIGHT,
		PLATFORM_UP_LEFT,
		PLATFORM_UP_RIGHT,
		INVALID_TERRAIN
	};
};



class Tile {
public:
	Tile(int type = Tiles::NONE);
	void setType(int type);
	int getType() const;
	QPixmap getIcon(int mapType) const;
	bool isGround();
	static bool isGround(int type);
	bool isStandable();
private:
	int _type;
};

inline bool operator==(const Tile &left, const Tile &right) {
	return left.getType() == right.getType() || (Tile::isGround(left.getType()) && Tile::isGround(right.getType()));
}
inline bool operator!=(const Tile &left, const Tile &right) {
	return !operator==(left, right);
}

#endif // TILE_H
