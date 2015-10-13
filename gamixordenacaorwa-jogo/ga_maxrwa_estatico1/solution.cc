/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#include "./solution.h"

#include <assert.h>

#include <iostream>
#include <fstream>

#include "./graph.h"
#include "./instance.h"

using std::cout;
using std::endl;
using std::ofstream;

/* Adiciona um caminho a solucao
*****************************************************************************/

void Solution::addPath(Terminals& connection,
                       int _color,
                       int* _path,
                       int _pathSize) {
  color[connection.id]= _color;
  pathSize[connection.id] = _pathSize;
  for (int i = 0;i <= _pathSize;i++) {
    path[connection.id][i]= _path[i];
  }
}

/* Grava a solucao em um arquivo
*****************************************************************************/

void Solution::save(char* file) {
  Instance *inst = Instance::getInstance();
  int numPath = inst->getNumPath();
  ofstream fcout(file);
  fcout << "Number of colors: " << numColors << endl;
  for (int k = 1;k <= numColors;k++) {
    fcout << "\nColor: " << k << endl;
    for (int i = 0; i < numPath; i++) {
      if (color[i] == k) {
        fcout << inst->getTerminals(i).id << " - "
              << inst->getTerminals(i).o << " "
              << inst->getTerminals(i).d << " - "
              << color[i] << " - ";
        for (int j = 0;j <= pathSize[i];j++) {
          fcout << path[i][j] << " ";
        }
        fcout << endl;
      }
    }
  }
  fcout.close();
}

/* Verifica se a solucao eh viavel
*********************************************/

int share(int *c1, int n1, int *c2, int n2) {
  for (int i = n1; i > 1; i--) {
    for (int j = n2; j > 1; j--) {
      if (c1[i] == c2[j] && c1[i - 1] == c2[j - 1]) {
        return 1;
      }
    }
  }
  return 0;
}

int Solution::isFeasible() {
  Instance *inst = Instance::getInstance();
  int numPath = inst->getNumPath();
  Graph* graph;
  Terminals term;

  graph = inst->getGraph();

  // Para cada caminho (o,d): (os caminhos sao invertidos)
  for (int i = 0; i < numPath; i++) {
    term = inst->getTerminals(i);
    // Verifica se o caminho eh esse mesmo
    assert(term.id == i);
    // Verifica se o caminho comeca em "o"
    assert(path[i][pathSize[i]] == term.o);
    // Verifica se o caminho termina em "d"
    assert(path[i][0] == term.d);
    // Verifica se todas as arestas do caminho estao no grafo
    for (int j = pathSize[i]; j>1; j--) {
      assert(graph->in(path[i][j], path[i][j-1]));
    }
  }
  // Verifica se a cor de cada caminho esta correta
  // (as cores vao de 1 ate numCores)
  for (int i = 0; i < numPath; i++) {
    assert(color[i] >= 1 && color[i] <= numColors);
  }
  // Verifica se o numero de cores esta correto (as cores vao de 1 ate numCores)
  int colored;
  for (int k = 1;k <= numColors; k++) {
    colored = 0;
    for (int i = 0; i < numPath; i++) {
      if (color[i] == k) {
        colored = 1;
      }
    }
    assert(colored == 1);
  }
  // Verifica se os caminhos que tem a mesma cor nao compartilham arestas
  for (int i = 0; i < numPath; i++) {
    for (int j = 0; j < numPath; j++) {
      if (i != j && color[i] == color[j]) {
        if (share(path[i], pathSize[i], path[j], pathSize[j]))
          cout << "!!!" << i << " " << j << endl;
        assert(!share(path[i], pathSize[i], path[j], pathSize[j]));
      }
    }
  }
  return 1;
}



