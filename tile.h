#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <qpixmap.h>

namespace Tiles {
	enum Types {
		NONE,
		GroundType=1000,
		PropType=2000
	};
	
	enum Ground {
		FIRST_GROUND = GroundType,
		FLAT = FIRST_GROUND,
		CAVE_GND,
		CAVE_GND_LEFT,
		CAVE_GND_RIGHT,
		CAVE_GND_UP,
		CAVE_GND_DOWN,
		INVALID_GROUND
	};
	
	enum Props {
		FIRST_PROP = PropType,
		FLAG = FIRST_PROP,
		BUSH,
		SIGN,
		INVALID_PROP
	};
};



class Tile {
public:
	Tile(int type = Tiles::Types::NONE);
	void setType(int type);
	int getType() const;
	QPixmap getIcon() const;
	static bool isGround(int type);
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
