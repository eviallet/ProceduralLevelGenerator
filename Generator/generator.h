#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <iostream>
#include <qstringlist.h>
#include <math.h>
#include "mainwindow.h"
#include "map.h"
#include "tile.h"

constexpr int Y = 0;
constexpr int X = 1;

enum MapType {
    OVERWORLD,
    UNDERGROUND
};

class Generator {
public:
    static void randomize(Map *map, MapType type);
    static double percent();
private:
	static void generateOverworld(Map *map);
	static void generateUnderground(Map *map, int nbTunnels, int maxLength);
	static void placeStructures(Map *map);
	static void placeCollectibles(Map *map);
	static void populate(Map *map);
	static void placeProps(Map *map);
    static const int DIRECTIONS[][2];
};

#endif // MAPGENERATOR_H
