#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"

////TREPA COLINAS START :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

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
////TREPA COLINAS END :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

////EVOLUTIVO START :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// Inicializa��o do gerador de n�meros aleat�rios
void init_rand_evol()
{
    srand((unsigned)time(NULL));
}

// Leitura dos par�metros e dos dados do problema
// Par�metros de entrada: Nome do ficheiro e matriz a preencher com os dados dos objectos (peso e valor)
// Par�metros de sa�da: Devolve a estrutura com os par�metros
struct info init_data_evol(char *filename, int *mat)
{
    struct  info x;
    FILE    *f;
    int     i, j, v1, v2;

    f = fopen(filename, "rt");
    if (!f)
    {
        printf("File not found\n");
        exit(1);
    }
    // Leitura dos par�metros do problema
    fscanf(f, "k %d", &x.ksols);
    fscanf(f, " p edge %d %d", &x.numGenes, &x.ligacoes);
    if (x.numGenes > MAX_OBJ)
    {
        printf("Number of itens is superior to MAX_OBJ\n");
        exit(1);
    }
    x.ro = 0.0;

    //Preenche matriz
    for (i=0; i<x.numGenes; i++)
        for (j=0; j<x.numGenes; j++)
            *(mat+(x.numGenes)*i+j)=0;

    for(i=0; i<x.ligacoes;i++){
        fscanf(f, " e %d %d", &v1, &v2);
            *(mat+x.numGenes*(v1-1)+v2-1)=1;
            *(mat+x.numGenes*(v2-1)+v1-1)=1;
    }

    fclose(f);

    x.popsize = 100;
    x.pm = 1;
    x.pr = 0.3;
    x.tsize = 2;
    x.numGenerations = 2500;

    // Devolve a estrutura com os par�metros
    return x;
}

// Simula o lan�amento de uma moeda, retornando o valor 0 ou 1
int flip_evol()
{
    if ((((float)rand()) / RAND_MAX) < 0.5)
        return 0;
    else
        return 1;
}

// Criacao da populacao inicial. O vector e alocado dinamicamente
// Par�metro de entrada: Estrutura com par�metros do problema
// Par�metro de sa�da: Preenche da estrutura da popula��o apenas o vector bin�rio com os elementos que est�o dentro ou fora da mochila
pchrom init_pop_evol(struct info d)
{
    int     i, j, x;
    pchrom  indiv;

    indiv = malloc(sizeof(chrom)*d.popsize);
    if (indiv==NULL)
    {
        printf("[ERROR] Erro na alocacao de memoria\n");
        exit(1);
    }

    for (i=0; i<d.popsize; i++) {
        for(j=0; j<d.numGenes; j++)
            indiv[i].p[j] = 0;

        for (j = 0; j < d.ksols; j++) {
            do
                x = random_l_h(0, d.numGenes-1);
            while(indiv[i].p[x] != 0);
            indiv[i].p[x] = 1;
        }
    }

    return indiv;
}

void print_pop_evol(pchrom pop, struct info d)
{
    printf("\nPop:");
    for (int i = 0; i < d.numGenes; i++) {
        printf("\n");
        for (int j = 0; j < d.numGenes; j++) {
            printf("%d ", pop[i].p[j]);
        }
    }
    printf("\n");
}

// Actualiza a melhor solu��o encontrada
// Par�metro de entrada: populacao actual (pop), estrutura com par�metros (d) e a melhor solucao encontrada at� a gera��oo imediatamente anterior (best)
// Par�metro de sa�da: a melhor solucao encontrada at� a gera��o actual
chrom get_best_evol(pchrom pop, struct info d, chrom best)
{
    int i;

    for (i=0; i<d.popsize; i++)
    {
        if (best.fitness < pop[i].fitness)
            best=pop[i];
    }
    return best;
}

// Devolve um valor inteiro distribuido uniformemente entre min e max
int random_l_h_evol(int min, int max)
{
    return min + rand() % (max-min+1);
}

// Devolve um valor real distribuido uniformemente entre 0 e 1
float rand_01_evol()
{
    return ((float)rand())/RAND_MAX;
}

// Escreve uma solu��o na consola
// Par�metro de entrada: populacao actual (pop) e estrutura com par�metros (d)
void write_best_evol(chrom x, struct info d)
{
    int i;

    printf("\nBest individual: %4.1f\n", x.fitness);
    for (i=0; i<d.numGenes; i++)
        if(x.p[i] == 1)
            printf(" %d", i+1);
    putchar('\n');
}
////EVOLUTIVO END :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int contaSolsAllPop(pchrom pop, struct info d){
    int nsols = 0, cont;
     for(int i=0; i<d.popsize;i++){
         cont=0;
         for(int j=0; j<d.numGenes;j++) {
             if (pop[i].p[j] == 1)
                 cont++;

         }
         if(cont == d.ksols)
             nsols++;
         //else
             //printf("Menor que k-sols: %d",nsols);
     }
     return nsols;
}

int contaSolsPop(pchrom pop, struct info d, int iter){
    int nsols = 0;

    for(int j=0; j<d.numGenes;j++){
        if (pop[iter].p[j] == 1)
            nsols++;
    }

    return nsols;
}

void logtofile(int num_iter,int best ,float mbf){
    FILE *out = fopen("output.txt", "a");

    fprintf(out, "%d\t%d\t%.2f\n",num_iter,best,mbf);
    fclose(out);
}

void logtofile_evol(chrom b, struct  info x,float mbf){
    FILE *out = fopen("output.txt", "a");


    fprintf(out, "%4.1f\t%.2f\t%d\t%.3f\t%.4f\t%d\t%d\t%d\n",b.fitness,mbf, x.popsize,	x.pr,x.pm,x.tsize,x.numGenerations,x.numGenes);
    fclose(out);
}