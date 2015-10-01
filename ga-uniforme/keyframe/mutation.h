/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#ifndef _MUTATION_H_
#define _MUTATION_H_

// Interface para o operador de mutacao.
class Mutation {
 protected:
  // Realiza uma mutacao num cromossomo.
  virtual void MutateChromosome(double* chromosome) = 0;

  // Tamanho da populacao.
  int chromosome_size_;

 public:
  // Construtor.
  explicit Mutation(int chromosome_size);

  // Executa mutacao em toda a populacao.
  void MutatePopulation(int population_size, double** population);

  // Destrutor virtual.
  virtual ~Mutation() {}
};

#endif  // _MUTATION_H_
