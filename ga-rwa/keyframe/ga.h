/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#ifndef _GA_H_
#define _GA_H_

#include "./mutation.h"
#include "./crossover.h"
#include "./evaluator.h"

// Classe que representa o algoritmo genetico.
class GA {
 private:
  // Funcao que ordena a populacao.
  void SortPopulation(double** population);

  // Tamanho do cromossomo.
  int chromosome_size_;

  // Tamanho do conjunto A.
  int set_a_size_;

  // Tamanho do conjunto B.
  int set_b_size_;

  // Tamanho do conjunto C.
  int set_c_size_;

  // Tamanho da populacao.
  int population_size_;

  // Contador do numero de geracoes.
  int generation_;

  // Populacao corrente.
  double **current_population_;

  // Populacao temporaria.
  double **new_population_;

  // Ponteiro para o algoritmo que faz a mutacao.
  Mutation* mutation_;

  // Ponteiro para o algoritmo que faz o crossover.
  Crossover* crossover_;

  // Ponteiro para a heuristica de fitness.
  Evaluator* evaluator_;

 public:
  // Construtor.
  GA(int chromoSize,
     int set_a_size,
     int set_b_size,
     int set_c_size,
     Mutation* mutation,
     Crossover* crossover,
     Evaluator* heuristic,
     int seed);

  // Executa por um certo numero de geracoes.
  double Execute(int maxGeneration, double target, int timeLimit);

  // Reinicia a populacao.
  double Reset(double target);

  // Retorna um certo cromossomo da populacao.
  void GetChromosome(int index, double* c);

  // Retorna o Fitness de um dado cromossomo da populacao.
  double GetFitness(int index);

  // Exibe um cromossomo.
  void ShowChromosome(int index);

  // Exibe o estado atual da Populacao.
  void ShowLog();

  // Destrutor.
  ~GA();
};

#endif  // _GA_H_
