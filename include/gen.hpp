#pragma once
#include <functional>
#include <string>

namespace genetic_alg
{

struct gen_params
{
	size_t population_size;
	size_t num_generations;
	double mutation_rate;
	double crossover_rate;
};

struct fun_params
{
	std::function<double(double)> f;
	double lower_bound;
	double upper_bound;
};

std::pair<double, double> gen_alg_get_max(const fun_params& fun_params, const gen_params& gen_params);

};  // namespace genetic_alg