/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#include "./binrwa.h"

#include <math.h>
#include <assert.h>

#include "../keyframe/evaluator.h"
#include "../keyframe/bibrand.h"

#include "./graph.h"
#include "./instance.h"
#include "./quicksort.h"
#include "./solution.h"

#include <algorithm>

#include<iostream>
using namespace std;

/* Calcula o Fitness de um cromossomo
*****************************************************/

double BinRWA::Fitness(double *chromo) {
  int permut[MAXPATH];

//========GA-SPT========================
creasing(permut, chromo);
return static_cast<double>(-rpt(permut)); //o sinal de menos eh adaptcao para maxrwa = segundo experimento:2.1
//======================================

//========GA-LPT========================
//decreasing(permut, chromo);
//return static_cast<double>(-rpt(permut)); //o sinal de menos eh adaptcao para maxrwa 
//======================================

}

/* Construtor
*********************************************************************/

BinRWA::BinRWA() {
  // Pega alguns dados da instancia
  Instance* inst = Instance::getInstance();
  numWmax = inst->getNumWmax(); //maxrwa
  numVertices = inst->getNumVertices();
  numArcs = inst->getNumArcs();
  numPath = inst->getNumPath();
  numBins = 0;

  // Inicializa variaveis
  Graph *g = inst->getGraph();

 for (int i = 0; i < numPath;i++) {
    bins[i] = NULL;
    terminals[i] = inst->getTerminals(i);
    spList[i] = g->getDistance(terminals[i].o, terminals[i].d);
  }

  // Calcula o valor de maxSize: tamanho maximo de um caminho
  int diameter = inst->getDiameter();
  maxSize = static_cast<int>(ceil(sqrt((numArcs / 2))));
  maxSize = maxSize > diameter ? maxSize : diameter;
}


// Define uma permutacao com ordem descrescente de caminhos mais curtos
void BinRWA::decreasing(int permutation[MAXPATH], double *tieBreak) {

  Bibrand *rand = Bibrand::GetInstance();
  double key[MAXPATH];
  for (int i = 0; i < numPath; i++) {
    permutation[i] = i;
    if (tieBreak == NULL) {
      key[i] = static_cast<double>(-(spList[i]*1000 +
                                     rand->IntRand(0, 1000 - 1)));
    } else {
      key[i] = static_cast<double>(-(spList[i]*10 +
                                     tieBreak[i]));
    }
  }

  quickSort < int>(key, permutation, 0, numPath-1);

  // for (int i=0; i<numPath; i++){
  //   cout << key[i] << ' ';
  // }
  // cout << endl;
  
  // for (int i = 0; i < numPath; i++){
  //   int pos = permutation[i];
  //   tieBreak[pos] = static_cast<double> (1.0/numPath);
  //   tieBreak[pos] *= (i);
  // }
}

// Define uma permutacao com ordem crescente de caminhos mais curtos
void BinRWA::creasing(int permutation[MAXPATH], double *tieBreak) {
  Bibrand *rand = Bibrand::GetInstance();
  double key[MAXPATH];
  for (int i = 0; i < numPath; i++) {
    permutation[i] = i;
    if (tieBreak == NULL) {
      key[i] = static_cast<double>((spList[i]*1000 +
                                     rand->IntRand(0, 1000 - 1)));
    } else {
      key[i] = static_cast<double>((spList[i]*10 +
                                     tieBreak[i]));
    }
  }

  quickSort < int>(key, permutation, 0, numPath-1);

  for (int i = 0; i < numPath; i++){
    int pos = permutation[i];
    tieBreak[pos] = static_cast<double> (1.0/numPath);
    tieBreak[pos] *= (i);
  }
  
}

/* Destrutor
*********************************************/

BinRWA::~BinRWA() {
  // Desaloca a memoria dos grafos/bins
  for (int i = 0;i < numPath;i++) {
    delete bins[i];
  }
}


/* Algorithm BinRWA
********************************/

int BinRWA::fit(int permutation[MAXPATH], int ff) {
  Instance* inst = Instance::getInstance();
  Terminals t;  // Lista de terminais
  Solution sol;  // Solucao gerada pela heuristica
  int path[MAXVERT];  // Armazena os arcos de um caminho
  int size;  // Tamanho do caminho
  int j;  // Contador

  int best;  // Melhor bin para colocar o caminho
  int bestSize;  // Tamanho do caminho no melhor bin
  
  int demand = 0; //maxrwa


  // Insere um caminho por vez
  numBins = 0;
  for (int i = 0;i < numPath;i++) {
    t = terminals[permutation[i]];
    // Procura o melhor dentre os bins que jah existem
    best = numBins;
    bestSize = maxSize+1;

    for (j = 0;j < numBins;j++) {
      size = bins[j]->getLbDistance(t.o, t.d);
      if (size < bestSize) {
        size = bins[j]->getDistance(t.o, t.d);
        if (size < bestSize) {
          best = j;
          bestSize = size;
          if (ff) break;
        }
      }
    }


    // Se pode inserir nos bins que jah existem
    if (bestSize <= maxSize) {

      bins[best]->shortestPath(t.o, t.d, path, size);
      sol.addPath(t, best+1, path, size);
      bins[best]->deleteArcs(path, size);
      demand++; //maxrwa
    // se nao, cria outro bin
    } else {
       if ( numBins < numWmax){ //maxrwa
        if (bins[numBins] == NULL){
        bins[numBins]= new Graph(inst->getGraph());
        } else {        
        bins[numBins]->reset();
        }
       bins[numBins]->shortestPath(t.o, t.d, path, size);
       sol.addPath(t, numBins+1, path, size);
       bins[numBins]->deleteArcs(path, size);
       numBins++;
       demand++;//maxrwa
     }
   }
  }

  sol.setNumDemand(demand);//maxrwa

  return demand; //maxrwa
}



/* Algorithm BinRWA for RPT, SPT and LPT
********************************/

int BinRWA::fit2(int permutation[MAXPATH], int ff) {
  Instance* inst = Instance::getInstance();
  Terminals t;  // Lista de terminais
  Solution sol;  // Solucao gerada pela heuristica
  int path[MAXVERT];  // Armazena os arcos de um caminho
  int size;  // Tamanho do caminho
  int i, j;  // Contadores

  int best;  // Melhor bin para colocar o caminho
  int bestSize;  // Tamanho do caminho no melhor bin
  
  int demand = 0; //maxrwa
  numBins = numWmax;//maxrwa

  // Inicializa primeiramente todos os bins
   for(i =0; i<numWmax; i++){
     if (bins[i] == NULL){
      bins[i]= new Graph(inst->getGraph());
     }else{        
       bins[i]->reset();
     }    
   }

  // Insere um caminho por vez
  //numBins = 0;
  for (int i = 0;i < numPath;i++) {
    t = terminals[permutation[i]];
    // Procura o melhor dentre os bins que existem
    best = 0;
    bestSize = maxSize+1;

    for (j = 0;j < numBins;j++) {
      size = bins[j]->getLbDistance(t.o, t.d);
      if (size < bestSize) {
        size = bins[j]->getDistance(t.o, t.d);
        if (size < bestSize) {
          best = j;
          bestSize = size;
          if (ff) break;
        }
      }
    }

    // Se pode inserir nos bins que existem
    if (bestSize <= maxSize) {

      bins[best]->shortestPath(t.o, t.d, path, size);
      sol.addPath(t, best+1, path, size);
      bins[best]->deleteArcs(path, size);
      demand++; //maxrwa
    } 
  }
  	sol.setNumDemand(demand);//maxrwa

  	return demand; //maxrwa
}
