/*********************************/
/* Copyright 2009 Thiago Noronha */
/*********************************/

#include "./graph.h"

/********************************************************************/
/*                  CLASSE SIMPLEGRAPH                              */
/********************************************************************/


/* Construtor 1
*****************************************************/

SimpleGraph::SimpleGraph(SimpleGraph *graph, int* w) {
  numVertices = graph->numVertices;
  numArcsBCK = graph->numArcs;

  for (int i = 0;i < numVertices;i++) {
    for (int j = 0;j < numVertices;j++) {
      outListIndex[i][j] = -1;
    }
  }

  for (int i = 0;i < numArcsBCK;i++) {
    listArcs[i] = graph->listArcs[i];
    adjMat[listArcs[i].u][listArcs[i].v] = &listArcs[i];
  }
  reset(w);
}


/* Construtor 2
*****************************************************/

SimpleGraph::SimpleGraph(int nVertices,
                         int nArcs,
                         int lArcs[MAXARCS][2],
                         int* w) {
  numVertices = nVertices;
  numArcsBCK = nArcs;

  for (int i = 0;i < numVertices;i++) {
    for (int j = 0;j < numVertices;j++) {
      outListIndex[i][j] = -1;
    }
  }

  for (int i = 0;i < nArcs;i++) {
    listArcs[i].u = lArcs[i][0];
    listArcs[i].v = lArcs[i][1];
    listArcs[i].weight = 1;
    adjMat[listArcs[i].u][listArcs[i].v] = &listArcs[i];
  }
  reset(w);
}


/* Cria uma nova copia do grafo original
*****************************************************/

void SimpleGraph::reset(int *weight) {
  int u, v;
  numArcs = numArcsBCK;
  for (int i = 0;i < numVertices;i++) {
    outDegree[i] = 0;
  }
  for (int i = 0;i < numArcs;i++) {
    u = listArcs[i].u;
    v = listArcs[i].v;
    outList[u][outDegree[u]] = v;
    outListIndex[u][v] = outDegree[u];
    outDegree[u]++;
  }

  if (weight != NULL) {
    for (int i = 0;i < numArcs;i++) {
      listArcs[i].weight = weight[i];
    }
  }
}

/* Calcula o diametro do grafo
***************************************************/

int SimpleGraph::diameter() {
  int size, diam = 0;
  for (int i = 0;i < numVertices;i++) {
    for (int j = i+1;j < numVertices;j++) {
      size = getDistance(i, j);
      if (size > diam) diam = size;
    }
  }
  return diam;
}

/* Calcula o caminho mais curto entre dois terminais usando BFS
*********************************************************************/

int SimpleGraph::shortestPathBFS(int s, int t, int *path, int &size) {
  int parent[MAXVERT];
  int queue[MAXVERT];
  int first = 0;  // indice do comeco da fila
  int last = 0;  // indice final da fila
  int v, next;

  // Inicializa as variaveis
  size = INF;
  for (int i = 0;i < numVertices;i++) parent[i] = -1;

  // Acha o caminho mais curto
  queue[last++] = s;
  parent[s] = s;
  do {
    v = queue[first];
    for (int i = 0;i < outDegree[v];i++) {
      next = outList[v][i];
      if (parent[next] < 0) {
        parent[next] = v;
        queue[last++] = next;
        // Retorna o caminho quando encontra "t"
        if (next == t) {
          size = 0;
          path[size] = t;
          while (path[size] != s) {
            size++;
            path[size] = parent[path[size-1]];
          }
          return size;
        }
      }
    }
    first++;
  }while (first < last);
  // Se nao chegou em "t" return size = INF
  return size;
}



/*******************************************************************/
/*                    CLASE NRRtGraph                              */
/*******************************************************************/



/* Construtor 1
********************************************************************/

NRRtGraph::NRRtGraph(SimpleGraph *graph, int* w)
  : SimpleGraph(graph, w) {
  initialize(w);
}

/* Construtor 2
**********************************************************************/

NRRtGraph::NRRtGraph(int nVertices, int nArcs, int lArcs[MAXARCS][2], int* w)
  : SimpleGraph(nVertices, nArcs, lArcs, w) {
  initialize(w);
}


/* Cria uma nova copia do grafo original
***********************************************************************/

void NRRtGraph::initialize(int* w) {
  for (int i = 0;i < numVertices;i++) {
    makeBFS(i);
  }
}

/* Calcula a arvore de BFS partindo do no "s"
*********************************************************************/
void NRRtGraph::makeBFS(int s) {
  int queue[MAXVERT][MAXVERT];  // Fila usada na BFS.
  int first = 0;  // Indice do comeco da fila.
  int last = 0;  // Indice do final da fila.
  int u, v;
  int *distanceS = distance[s];
  int *parentS = parent[s];

  // Inicializa as variaveis
  for (int i = 0;i < numVertices;i++) {
    distanceS[i] = INF;
  }

  // Acha o caminho mais curto de s para todos os outros
  queue[s][last++] = s;
  parentS[s] = s;
  distanceS[s] = 0;
  do {
    u = queue[s][first];
    for (int i = 0;i < outDegree[u];i++) {
      v = outList[u][i];
      if (distanceS[v] == INF) {
        parentS[v] = u;
        distanceS[v] = distanceS[u]+1;
        queue[s][last++] = v;
      }
    }
    first++;
  }while (first < last);
}

/* Calcula o caminho mais curto entre dois terminais
*********************************************************************/
int NRRtGraph::shortestPath(int s, int t, int *path, int &size) {
  if (distance[s][t] == INF) {
    size = INF;
  } else {
    size = 0;
    path[size] = t;
    while (path[size] != s) {
      if (in(parent[s][path[size]], path[size])) {
        path[size+1] = parent[s][path[size]];
        size++;
      } else {
        // Caso a aresta tenha sido apagada recalcula a BFS tree
        makeBFS(s);
        return shortestPath(s, t, path, size);
      }
    }
  }
  return size;
}


