/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#include"./instance.h"

#include<string.h>
#include<assert.h>
#include<math.h>

#include<iostream>
#include<fstream>

using std::cout;
using std::endl;
using std::ifstream;

Instance::Instance(char *gra, char *cam) {
  if (strcmp(gra+(strlen(gra)-4), ".dat") != 0) {
    // Le o arquivo do grafo
    strcpy(graphFile, gra);
    ifstream fcin(gra);
    fcin >> numWmax;
    fcin >> numVertices;
    fcin >> numArcs;
    for (int i = 0;i < numArcs;i++) {
      fcin >> listArcs[i][0] >> listArcs[i][1];
    };
    fcin.close();

    // Le o arquivo de caminhos
    if (strcmp(cam, "all") != 0) {
      strcpy(terminalsFile, cam);
      fcin.open(cam);
      fcin >> numPath;
      for (int i = 0;i < numPath;i++) {
        fcin >> terminals[i].o >> terminals[i].d;
        terminals[i].id = i;
      }
      fcin.close();
    } else {
      numPath = 0;
      for (int i = 0;i < numVertices;i++) {
        for (int j = 0;j < numVertices;j++) if (i != j) {
            terminals[numPath].o = i;
            terminals[numPath].d = j;
            terminals[numPath].id = numPath;
            numPath++;
          }
      }
    }


  } else {
    // Le o arquivo com o grafo e os caminhos
    int numPathAux, start, end, numCopies;
    char aux[MAXSTR];

    strcpy(graphFile, gra);
    strcpy(terminalsFile, "");

    ifstream fcin(gra);
    fcin >> numWmax;
    fcin >> numVertices;
    fcin >> numArcs;
    fcin >> numPathAux;

    // Le as arestas e descarta os outros dados
    for (int i = 0;i < numArcs;i++) {
      fcin >> listArcs[i][0] >> listArcs[i][1] >> aux >> aux >> aux;
      listArcs[i][0]--;
      listArcs[i][1]--;
    };
    // Le os pares de vertices terminais e o numero de comprimentos de onda
    numPath = 0;
    for (int i = 0;i < numPathAux;i++) {
      fcin >> start >> end >> numCopies;
      numCopies = static_cast<int>(ceil(numCopies/10.0));
      for (int j = 0;j < numCopies;j++) {
        terminals[numPath].o = start-1;
        terminals[numPath].d = end-1;
        terminals[numPath].id = numPath;
        numPath++;
      }
    }
    fcin.close();
  }

  // Inicializa o grafo da instancia

  graph = new Graph(numVertices, numArcs, listArcs);
  diameter = graph->diameter();
}


Instance* Instance::pInstance = NULL;
void Instance::initInstance(char* gra, char* cam) {
  assert(pInstance == NULL);
  pInstance =  new Instance(gra, cam);
}


Instance* Instance::getInstance() {
  assert(pInstance != NULL);
  return pInstance;
}


