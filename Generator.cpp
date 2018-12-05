#include "generator.h"

const int Generator::DIRECTIONS[][2] = { 
	{0,-1}, // LEFT
	{0,1},	// RIGHT
	{-1,0},	// UP
	{1,0}	// DOWN
};

Generator::Generator(Map *map) {
	this->map = map;
	p = new Perlin(rand());
}

// Returns a random percentage
double Generator::percent() {
	return (double)rand() / RAND_MAX;
}

