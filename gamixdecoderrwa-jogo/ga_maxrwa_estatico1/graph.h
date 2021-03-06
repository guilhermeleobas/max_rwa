#ifndef _GRAPH_H_
#define _GRAPH_H_

#define MAXVERT 104
#define MAXARCS (MAXVERT*20)
#define MAXDEG 15
#define INF 1000000000

#define Graph NRRtGraph

#include<stdlib.h>
#include <assert.h>     /* assert */

//#include<iostream>
//using namespace std;

typedef struct{
	int u; // vertice inicial
	int v; // vertice final
	int weight; // Peso da aresta (INF se a aresta nao existe)
} Arc;

/******************************************************************************************************/
/*                                        SimpleGraph                                                 */
/******************************************************************************************************/

class SimpleGraph{
 protected:
	// Numero de vertices
	int numVertices;

	// Numero de arestas
	int numArcs;

	// Numero de arestas no grafo original (antes de apagar alguma aresta)
	int numArcsBCK;

	// Lista de arestas e pesos do grafo
	Arc listArcs[MAXARCS];

	// Grau de cada vertice no grafo orientado
	int outDegree[MAXVERT];

	// Lista de adjacencias direcionada do grafo
	int outList[MAXVERT][MAXVERT];

	// Indice da aresta na lista de adjacencias
	int outListIndex[MAXVERT][MAXVERT];

	// Matriz de incidencia do grafo orientado
	Arc* adjMat[MAXVERT][MAXVERT];

	// Calcula o caminho mais curto entre dois terminais (usando Reverse Dijkstra)
	int dijkstra(int,int,int*,int&);

	// Calcula o caminho mais curto entre dois terminais (usando BFS)
	int shortestPathBFS(int,int,int*,int&);

 public:

	// Construtor
	SimpleGraph(int,int,int[MAXARCS][2],int* w=0);

	// Costrutor por Copia
	SimpleGraph(SimpleGraph *graph,int* w=0);

	// Cria uma nova copia do grafo original
	void reset(int* w=0);

	// Calcula e retorna o diametro do grafo
	int diameter();

	/* Funcoes INLINE
	********************************************************************************************/

	// Calcula o caminho mais curto entre dois terminais (usando BFS ou Djkistra)
	inline int shortestPath(int u,int v,int* p,int& s){return shortestPathBFS(u,v,p,s);}

	// Retorna soh o valor do SP
	inline int getDistance(int u,int v){int s,p[MAXVERT]; return shortestPathBFS(u,v,p,s);}

	// Retorna o numero de vertices
	inline int getNumVertices(){return numVertices;}

	// Retorna o numero de arestas
	inline int getNumArcs(){return numArcs;}

	// Retorna o original numero de arestas
	inline int getNumArcsBCK(){return numArcsBCK;}

	// Retorna o numero de arestas
	inline Arc getArc(int i){return listArcs[i];}

	// Testa se uma aresta esta no grafo
	inline int in(int u,int v){return (outListIndex[u][v]>=0);}

	// Retorna o i-esimo vizinho de v
	inline int getOutNeighbor(int v, int i){ return outList[v][i];}

	// Retorna o indice de uma aresta na lista de arestas
	inline int getOutListIndex(int u,int v){return (adjMat[u][v]-listArcs);}

	// Retorna um LB do caminho mais curto entre u e v
	inline int getLbDistance(int u,int v){return 0;}

	// Retorna o grau de saida de um vertice
	inline int getOutDegree(int v){return outDegree[v];}

	// Retorna o grau de entrada de um vertice
	inline int getInDegree(int v){
		int degree=0;
		for(int i=0;i<numVertices;i++) degree+=(in(i,v));
		assert(degree==outDegree[v]);
		return degree;
	}

	// Deleta um subconjunto de arestas (o caminho vem invertido. Ex: a<-b<-c<-d=(d,c)+(c,b)+(b,a)
	inline void deleteArcs(int *arcs,int size){for(int i=size;i>0;i--) deleteArc(arcs[i],arcs[i-1]);}

	// Deleta uma unica aresta
	inline void deleteArc(int u,int v){
		int index = outListIndex[u][v];
		int last = outList[u][outDegree[u]-1];
		outList[u][index]=last;
		outListIndex[u][last]=index;
		outDegree[u]--;
		numArcs--;
		outListIndex[u][v]=-1;
	}
};


/***********************************************************************************************************
*                                         NRRtGraph                                                    *
************************************************************************************************************/

class NRRtGraph : public SimpleGraph{
 protected:
   // Armazena os caminhos mais curtos de todos para todos.
	int parent[MAXVERT][MAXVERT];

   // Armazena as distancias minimas de  todos para todos.
	int distance[MAXVERT][MAXVERT];

	// Numero de updates
	int updates;

	// Cria uma nova copia do grafo original
	void initialize(int* w=NULL);

 public:

	// Construtor
	NRRtGraph(int,int,int[MAXARCS][2],int* w=0);

	// Construtor por copia
	NRRtGraph(SimpleGraph *graph,int* w=0);

	// Destrutor
	~NRRtGraph(){}//{cout << "Updates: " << updates << endl;}

	// Atualiza uma arvore de BFS
	void makeBFS(int s);

	// Calcula o caminho mais curto entre dois terminais (usando BFS ou Dijkstra)
	int shortestPath(int,int,int*,int&);

	// Retorna soh o valor do caminho mais curto entre u e v
	inline int getDistance(int u,int v){int s,p[MAXVERT]; return shortestPath(u,v,p,s);}

	// Retorna um limite inferior do caminho mais curto entre u e v
	inline int getLbDistance(int u,int v){return distance[u][v];}

	// Retorna o valor do caminho mais curto entre u e v
	inline void setDistance(int u,int v, int val){distance[u][v]=val;}

	// Retorna o vetor de distancias de um vertice "s"
	inline int* getDistances(int u){return distance[u];}

	// Reinicia toda a estrutura de classes
	inline void reset(int* w=NULL){
		SimpleGraph::reset(w);
		initialize(w);
	}

};

/***********************************************************************************************************
*                                       NRRgGraph                                                      *
************************************************************************************************************/

class NRRgGraph : public SimpleGraph{
 protected:
   // Grafo de caminhos mais curtos (possiveis pais de cada vertices)
	int parents[MAXVERT][MAXVERT][MAXDEG];

	// Numero de possiveis pais de cada vertices
	int nbParents[MAXVERT][MAXVERT];

   // Armazena as distancias minimas de  todos para todos.
	int distance[MAXVERT][MAXVERT];

	// Numero de updates
	int updates;

	// Cria uma nova copia do grafo original
	void initialize(int* w=NULL);

 public:

	// Construtor
	NRRgGraph(int,int,int[MAXARCS][2],int* w=0);

	// Construtor por copia
	NRRgGraph(SimpleGraph *graph,int* w=0);

	// Destrutor
	//~NRRgGraph(){cout << "Updates: " << updates << endl;}

	// Atualiza uma arvore de BFS
	void makeBFS(int s, int t=-1);

	// Calcula o caminho mais curto entre dois terminais (usando BFS ou Dijkstra)
	int shortestPath(int,int,int*,int&);

	// Retorna soh o valor do caminho mais curto entre u e v
	inline int getDistance(int u,int v){int s,p[MAXVERT]; return shortestPath(u,v,p,s);}

	// Retorna um limite inferior do caminho mais curto entre u e v
	inline int getLbDistance(int u,int v){return distance[u][v];}

	// Retorna o valor do caminho mais curto entre u e v
	inline void setDistance(int u,int v, int val){distance[u][v]=val;}

	// Retorna o vetor de distancias de um vertice "s"
	inline int* getDistances(int u){return distance[u];}

	// Reinicia toda a estrutura de classes
	inline void reset(int* w=NULL){
		SimpleGraph::reset(w);
		initialize(w);
	}

};

/************************************************************************************************************/
/*                                               RRtGraph                                                   */
/************************************************************************************************************/

class RRtGraph: public NRRtGraph{
 private:

	// Grau de entrada de cada vertice no grafo orientado
	int inDegree[MAXVERT];

	// Lista de arestas que entram no vertice
	int inList[MAXVERT][MAXVERT];

	// Indice da aresta em inList
	int inListIndex[MAXVERT][MAXVERT];

	// Numero de updates
	int updates;

	// Atualiza uma arvore de BFS
	void updateBFS(int);

	// Atualiza a delecao de um unico arco
	void updateArc(int,int,int);

	// Cria uma nova copia do grafo original
	void initialize(int* w=NULL);

 public:

	// Construtor
	RRtGraph(int,int,int[MAXARCS][2],int* w=0);

	// Construtor por copia
	RRtGraph(SimpleGraph *graph,int* w=0);

	// Destrutor
	//~RRtGraph(){cout << "Updates: " << updates << endl;}

	// Calcula o caminho mais curto entre dois terminais (usando BFS ou Dijkstra)
	int shortestPath(int,int,int*,int&);

	// Deleta um subconjunto de arestas
	void deleteArcs(int*,int);

	/* Funcoes INLINE
	***************************************************************/

	// Retorna soh o valor do caminho mais curto entre u e v
	inline int getDistance(int u,int v){int s,p[MAXVERT]; return shortestPath(u,v,p,s);}
	//int getDistance(int u,int v){return distance[u][v];}

	// Retorna o grau de entrada de um vertice
	inline int getInDegree(int i){return inDegree[i];}

	// Reinicia toda a estrutura de classes
	inline void reset(int* w=NULL){
		NRRtGraph::reset(w);
		initialize(w);
	}

	// Procura um pai para o vertice "v" na bfs-tree de "s" (pode ser o atual)
	void updateParent(int s, int v){
		int u;
		if(!in(parent[s][v],v)){
			for(int j=0;j<inDegree[v];j++){
				u = inList[v][j];
				if(distance[s][v]==(distance[s][u]+1)){
					parent[s][v] = u;
					return;
				}
			}
		}
	}
};

/************************************************************************************************************/
/*                                               RRgGraph                                                   */
/************************************************************************************************************/

class RRgGraph: public NRRtGraph{
 private:

	// Grau de entrada de cada vertice no grafo orientado
	int inDegree[MAXVERT];

	// Lista de arestas que entram no vertice
	int inList[MAXVERT][MAXVERT];

	// Indice da aresta em inList
	int inListIndex[MAXVERT][MAXVERT];

   // Grafo de caminhos mais curtos
	int gSP[MAXVERT][MAXARCS];

	// Numero de arestas alternativas em gSP de cada vertice
	int delta[MAXVERT][MAXVERT];

	// Numero de updates
	int updates;

	// Calcula a arvore de BFS partindo de um dado no
	void makeGSP(int);

	// Atualiza uma arvore de BFS
	void updateArc(int,int,int);

	// Cria uma nova copia do grafo original
	void initialize(int* w=NULL);

 public:

	// Construtor
	RRgGraph(int,int,int[MAXARCS][2],int* w=0);

	// Construtor por copia
	RRgGraph(SimpleGraph *graph,int* w=0);

	// Destrutor
	//~RRgGraph(){cout << "Updates: " << updates << endl;}

	// Calcula o caminho mais curto entre dois terminais (usando BFS)
	int shortestPath(int,int,int*,int&);

	// Deleta um subconjunto de arestas
	void deleteArcs(int*,int);

	// Retorna soh o valor do caminho mais curto entre u e v
	//inline int getDistance(int u,int v){int s,p[MAXVERT]; return shortestPath(u,v,p,s);}
	inline int getDistance(int u,int v){return distance[u][v];}

	// Retorna o grau de entrada de um vertice
	inline int getInDegree(int i){return inDegree[i];}

	// Reinicia toda a estrutura de classes
	inline void reset(int* w=NULL){
		NRRtGraph::reset(w);
		initialize(w);
	}
};

/************************************************************************************************************/
/*                                        Doubled linked List                                               */
/************************************************************************************************************/


class Node{
 public:
	// valor do no
	int key;

	// no anterior
	Node* prev;

	// proximo no
	Node* next;

	// Construtor do nil
	Node(){
		key=-1;
		prev=this;
		next=this;
	}

	// Construtor de um no
	Node(int k, Node* nil){
		key=k;
		next=nil->next;
		prev=nil;
		(nil->next)->prev = this;
		nil->next = this;
	}

	// Destrutor
	~Node(){
		prev->next = next;
		next->prev=prev;
	}
};

#endif





