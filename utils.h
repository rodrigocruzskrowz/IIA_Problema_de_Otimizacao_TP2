#ifndef TP2_UTILS_H
#define TP2_UTILS_H

////TREPA COLINAS
int* init_dados(char *ficheiro, int *solucoes, int *vertices, int *arestas);
void mostra_matriz(int *grafo, int vert);
void gera_sol_inicial(int *sol, int v, int k);
void escreve_sol(int *sol, int vert, int k);
void substitui(int a[], int b[], int n);
void init_rand();
int random_l_h(int min, int max);
float rand_01();

////EVOLUTIVO
struct info init_data_evol(char *s, int *mat);
pchrom init_pop_evol(struct info d);
void print_pop_evol(pchrom pop, struct info d);
chrom get_best_evol(pchrom pop, struct info d, chrom best);
void write_best_evol(chrom x, struct info d);
void init_rand_evol();
int random_l_h_evol(int min, int max);
float rand_01_evol();
int flip_evol();

int contaSolsAllPop(pchrom pop, struct info d);
int contaSolsPop(pchrom pop, struct info d, int iter);

void logtofile(int num_iter,int best ,float mbf);
void logtofile_evol(chrom b, struct  info x,float mbf);

#endif //TP2_UTILS_H
