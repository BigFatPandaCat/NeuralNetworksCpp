/*
 * Random.cpp
 *
 *  Created on: Feb 4, 2017
 *      Random::randn is adapted from source here: https://phoxis.org/2013/05/04/generating-random-numbers-from-normal-distribution-in-c/
 *      Thanks Phoxis!
 *      Random::randshuffle is mine
 */
#include "Random.h"
#include <ctime>

double Random::randn (double mu, double sigma)
{
	double U1, U2, W, mult;
	static double X1, X2;
	static int call = 0;

	if (call == 1)
	{
		call = !call;
		return (mu + sigma * (double) X2);
	}
	do
	{
		U1 = -1 + ((double) rand () / RAND_MAX) * 2;
		U2 = -1 + ((double) rand () / RAND_MAX) * 2;
		W = pow (U1, 2) + pow (U2, 2);
	}
	while (W >= 1 || W == 0);

	mult = sqrt ((-2 * log (W)) / W);
	X1 = U1 * mult;
	X2 = U2 * mult;

	call = !call;
	return (mu + sigma * (double) X1);
}

void Random::randshuffle(arma::cube & x)
{
	arma::mat temp;
	unsigned int n;

	for(unsigned int i = 0; i<(x.n_rows); i++)
	{
		srand(time(0));
		n = rand()%(x.n_rows-1);
		temp = x(arma::span(n),arma::span::all,arma::span::all);
		x(arma::span(n),arma::span::all,arma::span::all) = x(arma::span(n+1),arma::span::all,arma::span::all);
		x(arma::span(n+1),arma::span::all,arma::span::all) = temp;
	}
}

