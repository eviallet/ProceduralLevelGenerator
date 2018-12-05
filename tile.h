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
		ObjectType=4000
	};
	
	enum Ground {
		FIRST_GROUND = GroundType,
		GND = FIRST_GROUND,
		UP,
		LEFT,
		RIGHT,
		DOWN,
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
};



class Tile {
public:
	Tile(int type = Tiles::Types::NONE);
	void setType(int type);
	int getType() const;
	QPixmap getIcon(int mapType) const;
	bool isGround();
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
