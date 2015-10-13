/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#ifndef _BinRWA_H_
#define _BinRWA_H_

#include "../keyframe/evaluator.h"

#include "./solution.h"

class BinRWA : public Evaluator {
 private:
  // Numero max de comprimentos de onda //maxrwa
  int numWmax;

  // Numero de Vertices
  int numVertices;

  // Numero de Arestas
  int numArcs;

  // Numero de Caminhos
  int numPath;

  // Lista com as conexoes
  Terminals terminals[MAXPATH];

  // Tamanho maximo de um caminho
  int maxSize;

 // Quantidade de bins utilizados
  int numBins; //maxrwa

  // Lista de Bins
  Graph* bins[MAXPATH];

  // lista de caminhos mais curtos de cada conexao
  int spList[MAXPATH];

 public:
  // Construtor
  BinRWA();

  // Calcula o Fitness de um cromossomo
  double Fitness(double* chromo);

  // Destrutor
  ~BinRWA();

  // Codigo comum as heurísticas FF_RWA, BF_RWA, FFD_RWA, BFD_RWA
  int fit(int[MAXPATH], int);

  // Codigo comum as heurísticas RPT_RWA, SPT_RWA e LPT_RWA
  int fit2(int[MAXPATH], int); //maxrwa

  // Define uma permutacao dos caminhos
  // em ordem decrescente de caminho mais curto
  void decreasing(int[MAXPATH], double* tieBreak = NULL);

  // Define uma permutacao dos caminhos
  // em ordem crescente de caminho mais curto
  void creasing(int[MAXPATH], double* tieBreak = NULL);

  // Define uma permutacao dos caminhos
  // em ordem decrescente das chaves aleatorias
  void decreasingkey(int[MAXPATH], double* tieBreak = NULL);

  // Define uma permutacao dos caminhos
  // em ordem crescente das chaves aleatorias
  void creasingkey(int[MAXPATH], double *tieBreak = NULL);

  // Executa a heuristica FF_RWA
  inline int ff(int p[MAXPATH]) {
    return fit(p, 1);
  }

  // Executa a heuristica BF_RWA
  inline int bf(int p[MAXPATH]) {
    return fit(p, 0);
  }

  // Executa a heuristica FFD_RWA
  inline int ffd() {
    int p[MAXPATH];
    decreasing(p);
    return ff(p);
  }

  // Executa a heuristica BFD_RWA
  inline int bfd() {
    int p[MAXPATH];
    decreasing(p);
    return bf(p);
  }

 // Executa a heuristica RPT_RWA
  inline int rpt(int p[MAXPATH]) {
    return fit2(p, 0);
  }  

 // Executa a heuristica LPT_RWA
  inline int lpt() { 
    int p[MAXPATH];
    decreasing(p);
    return fit2(p,0);
  }  

 // Executa a heuristica SPT_RWA
  inline int spt() { 
    int p[MAXPATH];
    creasing(p); //ordem crescente
    return fit2(p,0);
  } 

 // Executa a heuristica BFC_RWA
  inline int bfc() { 
    int p[MAXPATH];
    creasing(p); //ordem crescente
    return fit(p,0);
  } 

 // Executa a heuristica LPT_RWA com ordenacao pelo valor das chaves
  inline int lptkey() { 
    int p[MAXPATH];
    decreasingkey(p); //ordem decrescente das chaves
    return fit2(p,0);
  }  

 // Executa a heuristica SPT_RWA com ordenacao pelo valor das chaves
  inline int sptkey() { 
    int p[MAXPATH];
    creasingkey(p); //ordem crescente das chaves
    return fit2(p,0);
  } 

};

#endif  // _BinRWA_H_
