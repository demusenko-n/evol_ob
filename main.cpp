#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

#include "gen.hpp"

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));

	genetic_alg::fun_params fparams{.f = [](double x) { return 12 - 2 * x - 8 * std::pow(x, 2) + 2 * std::pow(x, 3); },
	                                .lower_bound = -5.0,
	                                .upper_bound = 58.0};

	genetic_alg::gen_params gparams{
	    .population_size = 20, .num_generations = 100, .mutation_rate = 0.01, .crossover_rate = 50};
	const auto [x, value] = genetic_alg::gen_alg_get_max(fparams, gparams);
	std::cout << "fmax = f(" << x << ") = " << value << '\n';

	return 0;
}