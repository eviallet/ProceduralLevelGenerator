#ifndef PERLIN_H
#define PERLIN_H

#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

constexpr double MAX_X = 100.0;
constexpr double MAX_Y = 100.0;
constexpr double MAX_Z = 1.0;

// Perlin noise implementation from
// https://github.com/sol-prog/Perlin_Noise

class Perlin {
public:
	Perlin(unsigned int seed);
	double noise(double x, double y, double z);
	double getAverage(double xMax, int yMax, double zMax);
	void noiseToFile(double xMax, double yMax, double zMax);
private:
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
	double computeAverage(double xMax, int yMax, double zMax);

private:
	std::vector<int> p;
	double average = -1;
	double avX, avY, avZ;
};

#endif // PERLIN_H