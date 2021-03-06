/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include "./instance.h"

class Solution {
 private:
  // Numero de cores
  int numColors; 

  // Cor de cada conexao (as cores vao de 1 ate numCores)
  int color[MAXPATH];

  // Caminho de Cada conexao
  int path[MAXPATH][MAXVERT];

  // Numero de vertices no caminho de cada conexao
  int pathSize[MAXPATH];

  // Numero de demandas atendidas
  int numDemand; //maxrwa

 public:
  // Adiciona um caminho a solucao
  void addPath(Terminals& connection, int _color, int* _path, int _pathSize);

  // Grava a solucao em um arquivo
  void save(char* file);

  // Retorna o numero de demandas atendidas pela solucao 
  inline int getNumDemand() { //maxrwa
    return numDemand;
  }

  // Altera o numero de demandas da solucao 
  inline void setNumDemand(int n) { //maxrwa
    numDemand = n;
  }

  // Retorna o numero de cores da solucao (num de comp de onda- maxrwa)
  inline int getNumColors() {
    return numColors;
  }

  // Altera o numero de cores da solucao
  inline void setNumColors(int n) {
    numColors = n;
  }

  // Verifica se a solucao eh viavel
  // Retorna o numero de arestas no caminho de uma conexao
  inline int getPathSize(int i) {
    return pathSize[i];
  }

  // Retorna a i-esima aresta do caminho
  inline int getPathVertex(int p, int i) {
    return path[p][i];
  }

  // Testa se a solucao e viavel
  int isFeasible();

};

#endif  // _SOLUTION_H_
