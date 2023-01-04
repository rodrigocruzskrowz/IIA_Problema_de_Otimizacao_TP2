#ifndef TP2_ALGORITMO_H
#define TP2_ALGORITMO_H

#define PROB 0.01
#define TMAX 100
#define TMIN 5

int trepa_colinas(int sol[], int *mat, int vert, int num_iter);
int trepa_colinas_probabilistico(int sol[], int *mat, int vert, int num_iter);

int recristalizacao_simulada(int sol[], int *mat, int vert, int num_iter);

#endif //TP2_ALGORITMO_H
