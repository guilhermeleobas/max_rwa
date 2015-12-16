/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#ifndef _INSTANCE_H_
#define _INSTANCE_H_

#include "./graph.h"

//#define MAXPATH (MAXVERT*(MAXVERT-1))

#define MAXPATH 16000
#define MAXSTR 256

/* Estrutura que representa um par de terminais
*************************************************/

typedef struct {
  int o;
  int d;
  int id;
} Terminals;


/* Classe que armazena todos os dados da instancia
****************************************************/

class Instance {
 private:
  // Construtor independente do singleton.
  Instance();

  // Construtor do singleton.
  Instance(char*, char*);

  // Ponteiro do singleton.
  static Instance *pInstance;

  //Numero maximo de cores - maxrwa

   int numWmax; 

  // Numero de vertices.
  int numVertices;

  // Numero de arestas.
  int numArcs;

  // Numero de caminhos.
  int numPath;

  // Lista com os terminais.
  Terminals terminals[MAXPATH];

  // Nome do arquivo com o grafo.
  char graphFile[MAXSTR];

  // Nome do arquivo com as conexoes.
  char terminalsFile[MAXSTR];

  // Lista de Arestas do grafo.
  int listArcs[MAXARCS][2];

  // Ponteiro para o grafo da instancia.
  Graph* graph;

  // Diametro do grafo da instancia.
  int diameter;

 public:

  // destrutor
  ~Instance() {
    delete graph;
  }

  // Inicializa o singleton
  static void initInstance(char*, char*);

  // Returna um ponteiro para o singleton
  static Instance* getInstance();

  // Retorna o numero máximo de comprimento de ondas
  inline int getNumWmax() { // maxrwa
    return numWmax;
  }

  // Retorna o numero de vertices
  inline int getNumVertices() {
    return numVertices;
  }

  // Retorna o numero de arestas
  inline int getNumArcs() {
    return numArcs;
  }

  // Retorna o numero de Caminhos
  inline int getNumPath() {
    return numPath;
  }

  // Retorna um determinado par de terminais
  inline Terminals getTerminals(int i) {
    return terminals[i];
  }

  // Retorna o ponteiro para o grafo da instancia.
  inline Graph* getGraph() {
    return graph;
  }

  // Retorna o diametro do grafo da instancia.
  inline int getDiameter() {
    return diameter;
  }

  // Retorna o nome do arquivo com as conexoes.
  inline char* getTerminalsFile() {
    return terminalsFile;
  }
};

#endif  // _INSTANCE_H_
