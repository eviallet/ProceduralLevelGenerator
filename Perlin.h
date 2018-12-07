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
	Perlin(unsigned int seed, double xMax, double yMax, double zMax);
	double noise(double x, double y, double z);
	// Stats
	double getAverage();
	double getMedian();
	double getThirdQuartile();
	double getLastPercent();
	double getStatsAt(int percentage);
	// File
	void noiseToFile();
private:
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
	// Stats
	double computeAverage();
	void computeStats();

private:
	std::vector<int> p;
	std::vector<double> stats;
	double average = -1;
	double median = -1;
	double thirdQuartile = -1;
	double lastPercent = -1;
	double xMax, yMax, zMax;
};

#endif // PERLIN_H