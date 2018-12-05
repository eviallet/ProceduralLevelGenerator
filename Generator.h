#ifndef GENERATOR_H
#define GENERATOR_H

#include <math.h>
#include "Map.h"
#include "Tile.h"
#include "Perlin.h"

constexpr int Y = 0;
constexpr int X = 1;

enum MapType {
    OVERWORLD,
    UNDERGROUND
};

class Generator {
public:
	Generator(Map *map);
protected:
	virtual void generate() = 0;
    static double percent();
protected:
    static const int DIRECTIONS[][2];
	Perlin *p;
	Map *map;
};

#endif // GENERATOR_H
