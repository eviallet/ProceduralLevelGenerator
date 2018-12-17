#include "Random.h"

std::default_random_engine Random::generator;

/*
uniform_int_distribution (0,9):
0: *********
1: *********
2: *********
3: *********
4: *********
5: *********
6: *********
7: *********
8: *********
9: *********
*/
int Random::uniform(int min, int max) {
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

/*
uniform_real_distribution (0.0,1.0):
0.0-0.1: *********
0.1-0.2: *********
0.2-0.3: *********
0.3-0.4: *********
0.4-0.5: *********
0.5-0.6: *********
0.6-0.7: *********
0.7-0.8: *********
0.8-0.9: *********
0.9-1.0: *********
*/
double Random::uniform(double min, double max) {
	std::uniform_real_distribution<double> distribution(min, max);
	return distribution(generator);
}

/*
binomial_distribution (9,0.5):
0:
1: *
2: ******
3: ****************
4: *************************
5: ************************
6: *****************
7: *****
8: *
9:
*/
int Random::binomial(int n, int p) {
	std::binomial_distribution<int> distribution(n, p);
	return distribution(generator);
}

/*
normal_distribution (5.0,2.0):
0-1: *
1-2: ****
2-3: *********
3-4: ***************
4-5: ******************
5-6: *******************
6-7: ***************
7-8: ********
8-9: ****
9-10:*
*/
double Random::gaussian(double variance) {
	std::normal_distribution<double> distribution(0, variance);
	return distribution(generator);
}
