/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

// Interface para o operador de cruzamento.
class Crossover {
 protected:
  // Recombina dois cromossomos.
  virtual void CrossChromosome(double *chromosome1,
                               double *chromosome2,
                               double *offspring) = 0;

  // Tamanho do cromossomo.
  int chromosome_size_;

 public:
  // Cosntrutor.
  explicit Crossover(int chromosome_size);

  // Executa o cruzamento em toda a populacao.
  void CrossPopulation(int aSize,
                       int bSize,
                       int cSize,
                       double** current_population,
                       double** new_population);

  // Destrutor virtual.
  virtual ~Crossover() {}
};

#endif  // _CROSSOVER_H_
