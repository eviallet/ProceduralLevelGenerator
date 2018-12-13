#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "Generator.h"
#include "map.h"

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