#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

typedef struct chromosome { float fitness; void* data; };
typedef void* population;

typedef struct genetic_algorithm
{
    population current_generation;
    population next_generation;
    float (*fitness)(void*);
    population (*selection)(population);
    population (*crossover)(population);
    population (*mutation_)(population);
    int population_size;
    int chromosome_size;
};



#endif