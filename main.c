#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 10

int main(int argc, char *argv[])
{
    int opc = 1;
    while(opc != 0) {
        printf("\n\n::: Algoritmos :::\n");
        printf("1-Trepa Colinas\n");
        printf("0-Sair\n");
        printf("Opção: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1: {
                char    nome_fich[100];
                int     vert, arest, num_iter, i, runs, custo, best_custo, k;
                int     *grafo, *sol, *best;
                float   mbf = 0.0;

                if(argc == 3)
                {
                    runs = atoi(argv[2]);
                    if(runs <= 0){
                        printf("\n[ERROR] Número de repetições tem de ser igual ou superior a 10!\n");
                        exit(1);
                    }
                    strcpy(nome_fich, argv[1]);
                }
                else
                if(argc == 2)
                {
                    runs = DEFAULT_RUNS;
                    strcpy(nome_fich, argv[1]);
                }
                else
                {
                    printf("\nNome do Ficheiro: ");
                    fflush(stdin);
                    gets(nome_fich);

                    printf("Número de runs: ");
                    scanf("%d", &runs);
                }
                if(runs <= 0){
                    printf("\n[ERROR] Número de repetições tem de ser igual ou superior a 10!\n");
                    exit(1);
                }
                init_rand();
                // Preenche matriz de adjacencias
                grafo = init_dados(nome_fich,&k,&vert,&arest);
                mostra_matriz(grafo, vert);
                sol = malloc(sizeof(int)*vert);
                best = malloc(sizeof(int)*vert);
                if(sol == NULL || best == NULL)
                {
                    printf("[ERRO] Erro na alocacao de memoria");
                    exit(1);
                }
                for(i=0; i<runs; i++)
                {
                    // Gerar solucao inicial
                    gera_sol_inicial(sol, vert, k);
                    escreve_sol(sol, vert, k);
                    // Trepa colinas
//                    custo = trepa_colinas(sol, grafo, vert, num_iter);
		            custo = trepa_colinas_probabilistico(sol, grafo, vert, num_iter);
//                    custo = recristalizacao_simulada(sol, grafo, vert, num_iter);
                    // Escreve resultados da repeticao i
                    printf("\nRepeticao %d:", i);
                    escreve_sol(sol, vert, k);
                    printf("Custo final: %2d\n", custo);
                    mbf += custo;
                    if(i==0 || best_custo <= custo)
                    {
                        best_custo = custo;
                        substitui(best, sol, vert);
                    }
                }
                // Escreve eresultados globais
                printf("\n\nMBF: %f\n", mbf/i);
                printf("\nMelhor solucao encontrada");
                escreve_sol(best, vert, k);
                printf("Custo final: %2d\n", best_custo);
                free(grafo);
                free(sol);
                free(best);
                break;
            }
            case 0:{
                printf("\nA terminar...\n");
                break;
            }
            default: {
                printf("Opção desconhecida!");
                break;
            }
        }
    }
    return 0;
}
