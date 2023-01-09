#ifndef TP2_ALGORITMO_H
#define TP2_ALGORITMO_H

#define PROB 0.01
#define TMAX 100
#define TMIN 5

#define MAX_OBJ 500		// Numero maximo de vertices

////TREPA COLINAS
int trepa_colinas(int sol[], int *mat, int vert, int num_iter);
int trepa_colinas_viz1(int sol[], int *mat, int vert, int num_iter);
int trepa_colinas_viz2(int sol[], int *mat, int vert, int num_iter);
int trepa_colinas_probabilistico(int sol[], int *mat, int vert, int num_iter);
int recristalizacao_simulada(int sol[], int *mat, int vert, int num_iter);

////EVOLUTIVO
// EStrutura para armazenar parametros
struct info
{
    // Tamanho da popula��o
    int     popsize;
    // Probabilidade de muta��o
    float   pm;
    // Probabilidade de recombina��o
    float   pr;
    // Tamanho do torneio para sele��o do pai da pr�xima gera��o
    int     tsize;
    // Constante para avalia��o com penaliza��o
    float   ro;
    // N�mero de objetos que se podem colocar na mochila
    int     numGenes;
    // Numero de k-sols
    int     ksols;
    //Numero ligacoes
    int     ligacoes;
    // N�mero de gera��es
    int     numGenerations;
};

// Individuo (solu��o)
typedef struct individual chrom, *pchrom;
struct individual
{
    // Solu��o (objetos que est�o dentro da mochila)
    int     p[MAX_OBJ];
    // Valor da qualidade da solu��o
    float   fitness;
    // 1 se for uma solu��o v�lida e 0 se n�o for
    int     valido;
};

void tournament_evol(pchrom pop, struct info d, pchrom parents);
void genetic_operators_evol(pchrom parents, struct info d, pchrom offspring);
void crossover_evol(pchrom parents, struct info d, pchrom offspring);
void crossover_dois_pontos_corte_evol(pchrom parents, struct info d, pchrom offspring);
void crossover_uniforme_evol(pchrom parents, struct info d, pchrom offspring);
void mutation_evol(pchrom offspring, struct info d);
void mutacao_por_troca_evol(pchrom offspring, struct info d);

//void repoeKSols(int *solucoes, struct info d, pchrom offspring,int pos1,int pos2, int pontoTroca, int point);
void repoeKSols(int *solucoes, struct info d, pchrom offspring, int iter);

#endif //TP2_ALGORITMO_H
