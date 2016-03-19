/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>

#include <fstream>
#include <iostream>
#include <iomanip>

#include "../keyframe/biased.h"
#include "../keyframe/bibrand.h"
#include "../keyframe/evaluator.h"
#include "../keyframe/ga.h"
#include "../keyframe/random.h"

#include "../keyframe/chronometer.h"

#include "./binrwa.h"
#include "./instance.h"

#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

#include<sstream>
using std::cin;
using std::cout;
using std::endl;
using namespace std;


inline void exchange(int& i, int& j) {
  int aux = i;
  i = j;
  j = aux;
}

int main(int argc, char** argv) {
  int seedd;
  int maxIterations;
  int target;
  char network[256];
  char traffic[256];
  char alg[256];
  double tempo;

  // Le os dados de entrada.
  if (argc != 7){
    cout << "./rwa <network=*.net> <traffic=*.trf> <algorithm= GA|FF|BF|FFD|BFD|RPT|LPT|SPT|LPTK|SPTK> "
         << "<iterations=INT> <target=INT> <seed=INT>\n";
    abort();
  }
  strcpy(network, argv[1]);
  strcpy(traffic, argv[2]);
  strcpy(alg, argv[3]);
  maxIterations = atoi(argv[4]);
  target = atoi(argv[5]);
  seedd = atoi(argv[6]);


 int seed[10] = {1, 7 , 14, 20, 25, 60, 100, 116, 140, 200};
 
  Instance::initInstance(network, traffic);
  Instance* inst = Instance::getInstance();

  Bibrand::Initialize(seed[0]);
  Bibrand *gna = Bibrand::GetInstance();

  BinRWA binRWA;
  int numPath = inst->getNumPath();
	
  int best_it =  0;
  double soma_it =0;
  int worst_it = INT_MAX;
  double tempob_it = -1, tempow_it= -1, tempo_it =0;
  int maxExec = 10;

  double oldutime = 0.0, oldstime = 0.0, oldcputime =0.0, newutime = 0.0, newstime = 0.0, user_time = 0.0, sys_time  = 0.0, cpu_time = 0.0;
  double  cpuw_it, usrw_it, sysw_it, cpub_it, usrb_it, sysb_it, cpuit =0, usrit =0, sysit =0;//cpu time
  struct rusage r;

// Arquivo que guardara os tempos de todas as execucoes
 ofstream result, tempoit, bestsol;
	char fileresult[] = "testes/resultGAMixOrdenacao.out";
        char filesol[] = "testes/bestsolGAMixOrdenacao.xls";
	result.open(fileresult, (ios::out | ios::app));
        bestsol.open(filesol, (ios::out | ios::app));

 result  << setiosflags(ios::fixed) << setprecision(2) << argv[3] << " "<< argv[1] << " "<< argv[2] << endl;
 //bestsol << "Instância" << "\t" << " Máximo "<< "\t" << " TempoMax "<< "\t" <<"Média" << "\t" <<"TempoMédia" << "\t" << "Mínimo" << "\t" <<"TempoMin" << "\t" <<"\n";
 
//maxIterations = 200*inst->getNumVertices(); // para MS
//maxIterations = 200; //para GA

 double cpu_timeit = 0.0;

 for(int it=0;it<maxExec;it++){
  // Executa as heuristicas.
  int  cost, permutation[MAXPATH]; //numPath, cost,
  int best =  0;
  int worst = INT_MAX;
  double soma = 0;
  int i = 1;

  Chronometer c1; //Para calcular o tempo

  if (strcmp(alg, "GA") == 0) {
    maxIterations = 200; //para GA
    int chromoSize = inst->getNumPath()+1; // apenas uma chave adicional para definir como a ordenacao sera realizada
    int popSize = 1*inst->getNumVertices(); 
    int aSize = static_cast<int>(round((popSize*0.25)));
    int bSize = static_cast<int>(round((popSize*0.70)));
    int cSize = static_cast<int>(round((popSize*0.05))); 
    Mutation* mutation = static_cast<Mutation*>(new Random(chromoSize));
    Crossover* crossover = static_cast<Crossover*>(new Biased(chromoSize, 0.7));
    GA ga(chromoSize, aSize, bSize, cSize, mutation, crossover, &binRWA, seed[it]);
    maxIterations = (maxIterations>0?maxIterations:INT_MAX);

    c1.Start();
    getrusage(RUSAGE_SELF, &r); 
    oldutime = (double)(r.ru_utime).tv_sec+(r.ru_utime).tv_usec/1000000.0;
    oldstime = (double)(r.ru_stime).tv_sec+(r.ru_stime).tv_usec/1000000.0;
    oldcputime = oldutime + oldcputime;
 
    best = static_cast<int>(ga.Execute(maxIterations, target, 60)); 
    tempo = static_cast<double>(c1.dValue()); 
   
   getrusage(RUSAGE_SELF, &r);

   newutime = (double)(r.ru_utime).tv_sec+(r.ru_utime).tv_usec/1000000.0;
   newstime = (double)(r.ru_stime).tv_sec+(r.ru_stime).tv_usec/1000000.0;

    user_time = newutime - oldutime;
    sys_time = newstime - oldstime;
    cpu_time = user_time + sys_time;

  }else{
   maxIterations = 200*inst->getNumVertices(); // para MS
   c1.Start();

    getrusage(RUSAGE_SELF, &r); 
    oldutime = (double)(r.ru_utime).tv_sec+(r.ru_utime).tv_usec/1000000.0;
    oldstime = (double)(r.ru_stime).tv_sec+(r.ru_stime).tv_usec/1000000.0;
    oldcputime = oldutime + oldcputime;

       i = 0;
    do {
    if (strcmp(alg, "FF") == 0) {
      for (int j = 0;j < numPath;j++) {
        permutation[j] = j;
      }
      for (int j = 0;j < numPath;j++) {
        exchange(permutation[j],
                 permutation[j+gna->IntRand(0, numPath - j - 1)]);
      }
      cost = binRWA.ff(permutation);
     } else if (strcmp(alg, "BF") == 0) {
      for (int j = 0;j < numPath;j++)
        permutation[j] = j;
      for (int j = 0;j < numPath;j++)
        exchange(permutation[j],
                 permutation[j+gna->IntRand(0, numPath - j - 1)]);
      cost = binRWA.bf(permutation);
      }else if (strcmp(alg, "RPT") == 0) {
      for (int j = 0;j < numPath;j++)
        permutation[j] = j;
      for (int j = 0;j < numPath;j++)
        exchange(permutation[j],
                 permutation[j+gna->IntRand(0, numPath - j - 1)]);
      cost = binRWA.rpt(permutation);
     } else if (strcmp(alg, "FFD") == 0) {
      cost = binRWA.ffd();
    } else if (strcmp(alg, "BFD") == 0) {
      cost = binRWA.bfd();
    } else if (strcmp(alg, "BFC") == 0) {
      cost = binRWA.bfc();
    } else if (strcmp(alg, "LPT") == 0) {
      cost = binRWA.lpt();
    } else if (strcmp(alg, "LPTK") == 0) {
      cost = binRWA.lptkey();
    } else if (strcmp(alg, "SPT") == 0) {
      cost = binRWA.spt();
    } else if (strcmp(alg, "SPTK") == 0) {
      cost = binRWA.sptkey();
  } else {
      cout << "Error: <algorithm> must be "
           << "{GA or FF or BF or FFD or BFD or BFC or RPT or LPT or SPT or LPTK or SPTK}\n";
      abort();
    }
    soma += cost;
 
    if (cost < worst)//maxrwa
      worst = cost;
    if (cost > best)//maxrwa
      best = cost;
    i++;

    tempo = static_cast<double>(c1.dValue());
   
   getrusage(RUSAGE_SELF, &r);

   newutime = (double)(r.ru_utime).tv_sec+(r.ru_utime).tv_usec/1000000.0;
   newstime = (double)(r.ru_stime).tv_sec+(r.ru_stime).tv_usec/1000000.0;

    user_time = newutime - oldutime;
    sys_time = newstime - oldstime;
    cpu_time = user_time + sys_time;

 }while (cpu_time < 600);

	//tempo = static_cast<double>(c1.dValue());  //calcula o tempo de execução do método
 }

        result << best << "   " << cpu_time << " " <<seed[it] <<endl;

    soma_it += best;
    tempo_it += tempo;

    //cpu time
    cpuit +=cpu_time;
    usrit += user_time;
    sysit += sys_time;

    if (best < worst_it){//pior da iteracao
      worst_it = best;
      tempow_it = tempo;
      cpuw_it =cpu_time;
      usrw_it = user_time;
      sysw_it = sys_time;
    }
    if (best > best_it){//melhor da iteracao
      best_it = best;
      tempob_it = tempo;
      cpub_it =cpu_time;
      usrb_it = user_time;
      sysb_it = sys_time;   
    }
 
    gna->SetValue(seed[it+1]);

 }//for


 result  << setiosflags(ios::fixed) << setprecision(2) << " Media = " << soma_it/maxExec << endl;
 result  << setiosflags(ios::fixed) << setprecision(2) << " Tempo Medio = " << tempo_it/maxExec << endl;
 result  << setiosflags(ios::fixed) << setprecision(2) << " Tempo Medio CPU = " << cpuit/maxExec << endl;

 bestsol << setiosflags(ios::fixed) << setprecision(2) << argv[3] <<" " << argv[1] << " "<< argv[2] << "\t" << best_it << "\t" << tempob_it << "\t" << cpub_it << "\t"<<usrb_it << "\t"<< sysb_it << "\t"<<  soma_it/maxExec << "\t"<< tempo_it/maxExec << "\t" << cpuit/maxExec << "\t"<<usrit/maxExec << "\t"<< sysit/maxExec << "\t"<< worst_it<<"\t"<<    tempow_it << "\t" << cpuw_it << "\t"<<usrw_it << "\t"<< sysw_it << "\t" <<"\n";

}
