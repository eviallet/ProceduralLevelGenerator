#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "Generator.h"
#include "map.h"

constexpr int SIGN_POS = 2;
constexpr int FLAG_POS = 2;
constexpr int GND_HEIGHT = 2;


class Overworld : public Generator {
public:
	Overworld(Map * map);
	void generate();
protected:
	void randomizeTerrainHoles();
	void randomizeTerrainPlatforms();
	void placeBlocks();
};


#endif // OVERWORLD_H