#ifndef TP2_UTILS_H
#define TP2_UTILS_H
int calcula_fit(int a[], int *mat, int vert);

int* init_dados(char *ficheiro, int *solucoes, int *vertices, int *arestas);
void mostra_matriz(int *grafo, int vert);
void gera_sol_inicial(int *sol, int v, int k);
void escreve_sol(int *sol, int vert, int k);
void substitui(int a[], int b[], int n);
void init_rand();
int random_l_h(int min, int max);
float rand_01();

#endif //TP2_UTILS_H
