#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

typedef void* population;

typedef struct GenAlg
{
    population current_generation;
    population next_generation;
    float crossover_rate;
    float mutation__rate;
    int population_size;
    int chromosome_size;
    float (*fitness)(void*);
    population (*new_pop)(float (*)(void*),int,int);
    population (*selection)(population);
    population (*crossover)(population,float);
    population (*mutation_)(population,float);
};

GenAlg new_genAL( population (*_selection)(population),population (*_crossover)(population,float),
                population (*_mutation)(population,float),population (*_init_gene)(float (*)(void*),int,int),
                float (*_fitness)(void*),float cross_s,float mut_s,int pop_size,int chrom_size)
{
    GenAlg temp_genetic;
    temp_genetic.crossover_rate=cross_s;
    temp_genetic.mutation__rate=mut_s;
    temp_genetic.population_size=pop_size;
    temp_genetic.chromosome_size=chrom_size;
    temp_genetic.new_pop=_init_gene;
    temp_genetic.selection=_selection;
    temp_genetic.crossover=_crossover;
    temp_genetic.mutation_=_mutation;
    return temp_genetic;
}

population Evolve(GenAlg _GA,int max_generations)
{
    int generation=0;
    _GA.current_generation = _GA.new_pop(_GA.fitness,_GA.population_size,_GA.chromosome_size);
    for(generation=0;generation<max_generations;generation++)
    {
        _GA.next_generation = _GA.selection(_GA.current_generation);
        _GA.next_generation = _GA.crossover(_GA.next_generation,_GA.crossover_rate);
        _GA.current_generation = _GA.mutation_(_GA.next_generation,_GA.mutation__rate);
    }
    return _GA.current_generation;
}

#endif