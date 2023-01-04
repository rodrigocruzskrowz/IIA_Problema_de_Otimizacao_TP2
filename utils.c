#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Calcula a qualidade de uma solu��o
// Recebe:  A solu��o, a, a matriz de adjac�ncias, mat, e o n�mero de v�rtices, vert
// Devolve: O custo que � o n�mero de liga��es que existem na solu��o
int calcula_fit(int a[], int *mat, int vert)
{
    int total=0;
    int i, j;

    for(i=0; i<vert; i++)
        if(a[i]==1)
        {
            for(j=0; j<vert;j++)
                if(a[j]==1 && *(mat+i*vert+j)==1)
                    total++;
        }
    return total/2;
}

// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de soluções (ptr), numero de vertices (ptr), numero de arestas (ptr)
// Devolve a matriz de adjacencias
int* init_dados(char *ficheiro, int *solucoes, int *vertices, int *arestas)
{
    FILE *f;
    int *p, *q;
    int i, j, v1, v2;

    f=fopen(ficheiro, "r");
    if(!f)
    {
        printf("[ERRO] Erro no acesso ao ficheiro dos dados.\n");
        exit(1);
    }
    // Numero de soluções
    fscanf(f, "k %d", solucoes);
    // Numero de verticies e arestas
    fscanf(f, " p edge %d %d", vertices, arestas);
    // Alocacao dinamica da matriz
    p = malloc(sizeof(int)*(*vertices)*(*vertices));
    if(!p)
    {
        printf("[ERRO] Erro na alocacao de memoria.\n");
        exit(1);
    }
    q=p;
    // Preenchimento da matriz
    for(i=0; i<*vertices; i++) {
        for (j = 0; j < *vertices; j++) {
            *(q+(*vertices)*i+j)=0;
        }
    }
    for(i=0; i<*arestas; i++){
        fscanf(f, " e %d %d", &v1, &v2);
        *(q +(*vertices)*(v1 - 1) + v2 - 1)=1;
        *(q +(*vertices)*(v2 - 1) + v1 - 1)=1;
    }
    fclose(f);
    return p;
}

void mostra_matriz(int *grafo, int vert)
{
    printf("\nGrafo:");
    for (int i = 0; i < vert; i++) {
        printf("\n");
        for (int j = 0; j < vert; j++) {
            printf("%d ", grafo[i*vert+j]);
        }
    }
    printf("\n");
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *sol, int v, int k)
{
    int i, x;

    for(i=0; i<v; i++)
        sol[i]=0;
    for(i=0; i<k; i++)
    {
        do
            x = random_l_h(0, v-1);
        while(sol[x] != 0);
        sol[x]=1;
    }
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert, int k)
{
    int i;

    printf("\nConjunto: ");
    for(i=0; i<vert; i++)
        if(sol[i]==1)
            printf("%2d  ", i+1);
    printf("\n");
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
    srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
    return min + rand() % (max-min+1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01()
{
    return ((float)rand())/RAND_MAX;
}
