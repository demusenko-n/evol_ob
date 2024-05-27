#include <gen.hpp>

using namespace genetic_alg;

namespace
{

double random_double_0_1() { return static_cast<double>(rand()) / RAND_MAX; }

std::vector<double> initialize_population(double lower_bound, double upper_bound, size_t population_size)
{
	std::vector<double> population(population_size);
	for (double& p : population) p = lower_bound + random_double_0_1() * (upper_bound - lower_bound);

	return population;
}

std::vector<double> fitness(const std::vector<double>& population, const std::function<double(double)>& f)
{
	std::vector<double> fitness_scores(population);

	for (double& fs : fitness_scores) fs = f(fs);

	return fitness_scores;
}

std::vector<double> select_parents(const std::vector<double>& population, const std::vector<double>& fitness_scores)
{
	const size_t population_size = population.size();
	std::vector<double> parents(population_size);
	double min_fitness = *std::min_element(fitness_scores.begin(), fitness_scores.end());
	std::vector<double> adjusted_fitness(population_size);
	double sum_adjusted_fitness = 0.0;
	for (size_t i = 0; i < population_size; ++i)
	{
		adjusted_fitness[i] = fitness_scores[i] - min_fitness + 1e-5;
		sum_adjusted_fitness += adjusted_fitness[i];
	}
	for (size_t i = 0; i < population_size; ++i)
	{
		double r = random_double_0_1() * sum_adjusted_fitness;
		double cumulative_probability = 0.0;
		for (size_t j = 0; j < population_size; ++j)
		{
			cumulative_probability += adjusted_fitness[j];
			if (cumulative_probability >= r)
			{
				parents[i] = population[j];
				break;
			}
		}
	}
	return parents;
}

std::vector<double> crossover(const std::vector<double>& parents, double crossover_rate)
{
	std::vector<double> offspring(parents.size());
	for (size_t i = 0; i < parents.size(); i += 2)
	{
		if (random_double_0_1() < crossover_rate && i + 1 < parents.size())
		{
			double crossover_point = random_double_0_1();
			offspring[i] = crossover_point * parents[i] + (1 - crossover_point) * parents[i + 1];
			offspring[i + 1] = crossover_point * parents[i + 1] + (1 - crossover_point) * parents[i];
		}
		else
		{
			offspring[i] = parents[i];
			if (i + 1 < parents.size())
			{
				offspring[i + 1] = parents[i + 1];
			}
		}
	}
	return offspring;
}

void mutate(std::vector<double>& offspring, double lower_bound, double upper_bound, double mutation_rate)
{
	for (double& o : offspring)
	{
		if (random_double_0_1() < mutation_rate)
		{
			o = lower_bound + random_double_0_1() * (upper_bound - lower_bound);
		}
	}

	for (size_t i = 0; i < offspring.size(); ++i)
	{
		if (random_double_0_1() < mutation_rate)
		{
			offspring[i] = lower_bound + random_double_0_1() * (upper_bound - lower_bound);
		}
	}
}

}  // namespace

std::pair<double, double> genetic_alg::gen_alg_get_max(const fun_params& fun_params, const gen_params& gen_params)
{
	std::vector<double> population =
	    initialize_population(fun_params.lower_bound, fun_params.upper_bound, gen_params.population_size);
	for (size_t generation = 0; generation < gen_params.num_generations; ++generation)
	{
		std::vector<double> fitness_scores = fitness(population, fun_params.f);
		std::vector<double> parents = select_parents(population, fitness_scores);
		std::vector<double> offspring = crossover(parents, gen_params.crossover_rate);
		mutate(offspring, fun_params.lower_bound, fun_params.upper_bound, gen_params.mutation_rate);
		population = offspring;
	}

	std::vector<double> fitness_scores = fitness(population, fun_params.f);
	auto max_it = std::max_element(fitness_scores.begin(), fitness_scores.end());

	double best_solution = population[std::distance(fitness_scores.begin(), max_it)];
	double best_solution_value = *max_it;

	return std::pair(best_solution, best_solution_value);
}
