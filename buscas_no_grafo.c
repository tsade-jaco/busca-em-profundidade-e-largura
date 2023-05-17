#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define vertices int
int pre[1000];
int num[1000];

struct item{
	vertices v;
	struct item *proximo;
};

struct fila{
	struct item *proximo;
};

typedef struct fila *Fila;

typedef struct item *link;

struct grafo{
	int V;
	int **MatrizDeAdjacencias;
};

typedef struct grafo *Grafo;


static void InicializarGrafo(FILE *arquivo, Grafo G);
void IniciarBuscaEmProfundidade(Grafo G);
static void BuscaEmPofundidade(Grafo G, vertices v);
static void BuscaEmLargura(Grafo G, vertices v);
static void IncluiNaFila(Fila MinhaFila, vertices v);
static void TiraDaFila(Fila MinhaFila);

int main(){
	int i, j, QTDVertices,QTDArestas;
	FILE *arquivo;

	arquivo = fopen("Grafo.txt", "r");
	Grafo MeuGrafo = malloc(sizeof(Grafo *));

    InicializarGrafo(arquivo, MeuGrafo);
	
	fclose(arquivo);
	IniciarBuscaEmProfundidade(MeuGrafo);
	BuscaEmLargura(MeuGrafo, 0);
	return 0;
}

static void InicializarGrafo(FILE *arquivo, Grafo G){

	int i = 0,j,k = 0,tmp, MAX = 1000, ordemDaMatriz;
	int vetorTMP[MAX];

    
	while(!feof(arquivo)){
		fscanf(arquivo,"%d", &vetorTMP[i]);
		i++;
	}

	ordemDaMatriz = sqrt(i);
	G->V = ordemDaMatriz;

	int **m = malloc(ordemDaMatriz * sizeof(int*));
	for(i=0;i< ordemDaMatriz; ++i)
		m[i] = malloc(ordemDaMatriz * sizeof(int*));

    G->MatrizDeAdjacencias = m;

	for(i=0; i < ordemDaMatriz; ++i){
	    for(j=0; j < ordemDaMatriz; ++j){
	        G->MatrizDeAdjacencias[i][j] = vetorTMP[k];
	        k++;
		}
	}
}


void IniciarBuscaEmProfundidade(Grafo G){
	for(int v = 0; v < G->V; ++v)
		pre[v] = -1;

	printf("Busca em profundidade:\n");
	BuscaEmPofundidade(G, 0);
	printf("\n");

}

static void BuscaEmPofundidade(Grafo G, vertices v){
	if(pre[v] == -1){

		printf("%d ",v);
		int i;
		pre[v] = 1;
		for(i=0; i < G->V; ++i){
		   if(G->MatrizDeAdjacencias[v][i] == 1){
		 	 BuscaEmPofundidade(G, i);
		   }
		}
	}
}

static void BuscaEmLargura(Grafo G, vertices v){
	printf("Busca em largura:\n");

	Fila MinhaFila = malloc(sizeof(link*));
    MinhaFila->proximo = NULL;

    for(vertices w = 0; w < G->V; ++w){
		num[w] = -1;
    }

    num[v] = 1;
    printf("%d ", v);
    IncluiNaFila(MinhaFila, v);

	while(MinhaFila->proximo != NULL){
		vertices v = MinhaFila->proximo->v;
		for(vertices i=0; i < G->V; ++i){
			if(G->MatrizDeAdjacencias[v][i] == 1){
				if(num[i] == -1){
				   num[i] = 1;
				   printf("%d ",i);
				   IncluiNaFila(MinhaFila, i);
				}
			}
	    }
	    TiraDaFila(MinhaFila);
	}

	printf("\n");
	
}

static void IncluiNaFila(Fila MinhaFila, vertices v){
	link item = malloc(sizeof(link*));
    item->v = v;
    item->proximo = NULL;
  
    if(MinhaFila->proximo == NULL)
    	MinhaFila->proximo = item;
    else{
    	link a;
    	a = MinhaFila->proximo;
    	while(a->proximo != NULL)
    	    a = a->proximo;

    	a->proximo = item;
    }
    
}

static void TiraDaFila(Fila MinhaFila){
	link remover = MinhaFila->proximo, seguinte;
	seguinte = remover->proximo;
	MinhaFila->proximo = seguinte;
	
	free(remover);
}