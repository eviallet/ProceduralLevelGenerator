#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
public:
	static int uniform(int min, int max);
	static double uniform(double min, double max);
	static int binomial(int n, int p);
	static double gaussian(double variance);
private:
	Random() {};
	static std::default_random_engine generator;
};

#endif
