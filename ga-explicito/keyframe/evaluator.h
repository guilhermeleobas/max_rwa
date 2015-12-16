/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

// Classe virtual que abstrai os dados do problema.
class Evaluator {
 protected:
  // Tamanho da Populacao.
  int chromosome_size_;

 public:
  // Funcao virtual que calcula o fitness de um cromossomo.
  virtual double Fitness(double* chromosome) = 0;

  // Destrutor virtual.
  virtual ~Evaluator() {}
};

#endif  // _EVALUATOR_H_
