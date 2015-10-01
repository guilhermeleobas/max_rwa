/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#include "./ga.h"

#include <iostream>

#include "./bibrand.h"
#include "./chronometer.h"
#include "./evaluator.h"
#include <math.h>

#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

using std::cout;
using std::endl;

GA::GA(int chromosome_size,
       int set_a_size,
       int set_b_size,
       int set_c_size,
       Mutation* mutation,
       Crossover* crossover,
       Evaluator* heuristic,
       int seed) {
  chromosome_size_ = chromosome_size;
  set_a_size_ = set_a_size;
  set_b_size_ = set_b_size;
  set_c_size_ = set_c_size;
  population_size_ = set_a_size_+set_b_size_+set_c_size_;
  mutation_ = mutation;
  crossover_ = crossover;
  evaluator_ = heuristic;

  current_population_ = new double*[population_size_];
  for (int i = 0; i < population_size_; i++)
    current_population_[i] = new double[chromosome_size_+2];

  new_population_ = new double*[population_size_];
  for (int i = 0; i < population_size_; i++)
    new_population_[i] = new double[chromosome_size_+2];
}


double GA:: Execute(int maxGeneration, double target, int timeLimit) {
  double** aux;
  double* tmp;
//  double best = Reset(target);
  generation_ = 0;
  Chronometer chrono;
  chrono.Start();

  double oldutime = 0.0, oldstime = 0.0, oldcputime =0.0, newutime = 0.0, newstime = 0.0, user_time = 0.0, sys_time  = 0.0, cpu_time = 0.0, cpu_timet = 0.0;
  struct rusage r;

/*  if (best <= target) return fabs(best);
  while (generation_ < maxGeneration &&
         current_population_[0][chromosome_size_] > target &&
         chrono.Time() < timeLimit) {
*/
//  while (generation_ < maxGeneration) { //&&
 // while (chrono.Time() < timeLimit) { //&&

  while (cpu_timet < timeLimit) { //&&

    getrusage(RUSAGE_SELF, &r); 
    oldutime = (double)(r.ru_utime).tv_sec+(r.ru_utime).tv_usec/1000000.0;
    oldstime = (double)(r.ru_stime).tv_sec+(r.ru_stime).tv_usec/1000000.0;
    oldcputime = oldutime + oldcputime;
 
    // Crossover, Mutacao e Ordenacao da nova populacao
    crossover_->CrossPopulation(set_a_size_,
                                set_b_size_,
                                set_c_size_,
                                current_population_,
                                new_population_ + set_a_size_);
    mutation_->MutatePopulation(set_c_size_,
                                new_population_ + (set_a_size_ + set_b_size_));

    // Copia todos os elementos de A na nova popucalco
    for (int i = 0; i < set_a_size_; i++) {
      tmp = current_population_[i];
      current_population_[i] = new_population_[i];
      new_population_[i] = tmp;
    }

    // Avalia os novos elementos da populcao
    for (int i = set_a_size_; i < population_size_; i++) {
      new_population_[i][chromosome_size_] =
        evaluator_->Fitness(new_population_[i]);
      current_population_[i][chromosome_size_+1] =
        i < (set_a_size_+set_b_size_) ? 1 : 0;
     /* if (new_population_[i][chromosome_size_] <= target) {
        return fabs(new_population_[i][chromosome_size_]);
      }*/
    }

    //  Ordena a nova populacao
    SortPopulation(new_population_);

    // Atualiza a populacao corrente
    aux = current_population_;
    current_population_ = new_population_;
    new_population_ = aux;

    // Incrementa o contador de geracoes
    generation_++; 

   getrusage(RUSAGE_SELF, &r);

   newutime = (double)(r.ru_utime).tv_sec+(r.ru_utime).tv_usec/1000000.0;
   newstime = (double)(r.ru_stime).tv_sec+(r.ru_stime).tv_usec/1000000.0;

    user_time = newutime - oldutime;
    sys_time = newstime - oldstime;
    cpu_time = user_time + sys_time;

    cpu_timet += cpu_time;
  }


//  ShowLog();
  return fabs(current_population_[0][chromosome_size_]); // comentei o Showlog e coloquei fabs para a execucao dos testes 06/10/2013
}

double GA::Reset(double target) {

  mutation_->MutatePopulation(population_size_, current_population_);

  for (int i = 0; i < population_size_; i++) {
    current_population_[i][chromosome_size_] =
      evaluator_->Fitness(current_population_[i]);
    current_population_[i][chromosome_size_ + 1] = 0;
    if (current_population_[i][chromosome_size_] <= target) {
      return current_population_[i][chromosome_size_];
    }
  }
  SortPopulation(current_population_);

  generation_ = 0;
  return current_population_[0][chromosome_size_];
}


void GA::GetChromosome(int index, double* c) {
  for (int i = 0; i < chromosome_size_ + 1; i++) {
    c[i] = current_population_[index][i];
  }
}


double GA::GetFitness(int index) {
  return current_population_[index][chromosome_size_];
}


void GA::ShowChromosome(int index) {
  cout << "[";
  for (int i = 1;i <= chromosome_size_;i++) {
    cout << current_population_[index][i] << (i < chromosome_size_?", ":"]");
  }
}


void GA::ShowLog() {

for (int i = 0; i < population_size_; i++){
   current_population_[i][chromosome_size_] = fabs (current_population_[i][chromosome_size_]);
}
  
  double average = 0.0;
  for (int i = 0; i < population_size_; i++)
    average += current_population_[i][chromosome_size_];
  average /= population_size_;

  double averageA = 0.0;
  for (int i = 0; i < set_a_size_; i++)
    averageA += current_population_[i][chromosome_size_];
  averageA /= set_a_size_;

  cout << "(Generation, Best, A-average, Pop-average) = ("
       << generation_ << ", "
       << current_population_[0][chromosome_size_] << "("
       << current_population_[0][chromosome_size_ + 1] << "), "
       << averageA << ", "
       << average << ")\n";
}


void GA::SortPopulation(double** population) {
  double* aux;
  for (int i = 0;i < population_size_;i++) {
    for (int j = i+1;j < population_size_;j++) {
   if (population[i][chromosome_size_] > population[j][chromosome_size_]) {//original
    //  if (population[i][chromosome_size_] < population[j][chromosome_size_]) {//> soh isso resolveria o prob de min para max, mas alteraria o framework.
          aux  =  population[i];
        population[i] = population[j];
        population[j] = aux;
      }
    }
  }
}

GA::~GA() {
  for (int i = 0;i < population_size_;i++)
    delete [] (current_population_[i]);
  delete [] (current_population_);

  for (int i = 0;i < population_size_;i++)
    delete [] (new_population_[i]);
  delete [] (new_population_);
}


