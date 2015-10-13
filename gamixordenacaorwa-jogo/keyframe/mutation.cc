/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#include "./mutation.h"

Mutation::Mutation(int chromosome_size) {
  chromosome_size_ = chromosome_size;
}

void Mutation:: MutatePopulation(int population_size, double** population) {
  for (int i = 0; i < population_size; ++i) {
    MutateChromosome(population[i]);
  }
}
