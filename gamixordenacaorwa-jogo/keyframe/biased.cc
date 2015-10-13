/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#include "./biased.h"

#include "./bibrand.h"

Biased::Biased(int chromosome_size, double k)
  : Crossover(chromosome_size) {
  k_ = k;
}

void Biased::CrossChromosome(double *chromosome1,
                             double *chromosome2,
                             double *offspring) {
  Bibrand *gna = Bibrand::GetInstance();
  double omega;
  for (int j = 0; j < chromosome_size_; j++) {
    omega = gna->DoubleRand();
    offspring[j] = omega > k_ ? chromosome1[j] : chromosome2[j];
  }
}

