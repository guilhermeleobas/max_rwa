/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#ifndef RANDOM_H
#define RANDOM_H

#include "./mutation.h"

// Classe que implementa uma mutacao que recria uma
// solucao aleatoriamente
class Random : public Mutation {
 public:
  // Construtor
  explicit Random(int chromosome_size);

  // Realiza uma mutacao num cromossomo.
  void MutateChromosome(double* chromosome);
};

#endif
