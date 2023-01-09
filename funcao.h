#ifndef TP2_FUNCAO_H
#define TP2_FUNCAO_H

////TREPA COLINAS
int calcula_fit(int a[], int *mat, int vert);

////EVOLUTIVO
void evaluate_evol(pchrom pop, struct info d, int *mat);
void gera_vizinho_evol(int sol[], int solViz[], int *mat, int nGenes);
void gera_vizinho2_evol(int sol[], int solViz[], int *mat, int nGenes);
void trepa_colinas_evol(pchrom pop, struct info d, int *mat);

#endif //TP2_FUNCAO_H

