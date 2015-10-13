/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#include "./random.h"

#include "./bibrand.h"
#include "./mutation.h"

Random::Random(int chromosome_size) : Mutation(chromosome_size) {
  // Nothing more to do.
}

void Random::MutateChromosome(double *chromosome) {
  Bibrand *gna = Bibrand::GetInstance();
  for (int j = 0; j < chromosome_size_; j++) {
    chromosome[j] = gna->DoubleRand();
  }
}

