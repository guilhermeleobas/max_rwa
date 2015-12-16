/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#include "./crossover.h"

#include "./bibrand.h"

Crossover::Crossover(int chromosome_size) {
  chromosome_size_ = chromosome_size;
}

void Crossover:: CrossPopulation(int aSize,
                                 int bSize,
                                 int cSize,
                                 double** current_population,
                                 double** new_population) {
  Bibrand *gna = Bibrand::GetInstance();
  int c1, c2;
  int population_size = aSize + bSize + cSize;
  for (int i = 0; i < bSize; i++) {
    c1 = gna->IntRand(0, aSize - 1);
    c2 = gna->IntRand(aSize, population_size - 1);
    CrossChromosome(current_population[c1],
                    current_population[c2],
                    new_population[i]);
  }
}

