/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#ifndef _BIASED_H_
#define _BIASED_H_

#include "./crossover.h"

// Classe que implementa crossover "Biased".
class Biased : public Crossover {
 protected:
  // Probabilidade de um gene ser herdado
  // do primeiro pai.
  double k_;

 public:
  // Costrutor.
  Biased(int _chromosomeSize, double _k);

  // Cruza dois cromossomos.
  void CrossChromosome(double *chromosome1,
                       double *chromosome2,
                       double *offspring);
};

#endif  // _BIASED_H_
