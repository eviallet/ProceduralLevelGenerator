#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "Generator.h"
#include "map.h"

class Overworld : public Generator {
public:
	Overworld(Map * map);
	void generate();
protected:
	void randomizeTerrainHeight();
};


#endif // OVERWORLD_H