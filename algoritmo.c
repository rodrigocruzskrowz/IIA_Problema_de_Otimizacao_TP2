#include "algoritmo.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
//swap two vertices
void gera_vizinho(int a[], int b[], int n)
{
    int i, p1, p2;

    for(i=0; i<n; i++)
        b[i]=a[i];
    // Encontra posicao com valor 0
    do
        p1=random_l_h(0, n-1);
    while(b[p1] != 0);
    // Encontra posicao com valor 0
    do
        p2=random_l_h(0, n-1);
    while(b[p2] != 1);
    // Troca
    b[p1] = 1;
    b[p2] = 0;
}

void gera_vizinho2(int a[], int b[], int n)
{
    int i, p1, p2, p3, p4;

    //Copia a solução atual para a solução vizinha
    for(i=0; i<n; i++)
        b[i]=a[i];
    // Encontra posicao com valor 0
    do
        p1=random_l_h(0, n-1);
    while(b[p1] != 0);
    // Encontra posicao com valor 0
    do
        p2=random_l_h(0, n-1);
    while(b[p2] != 1);
    // Troca
    b[p1] = 1;
    b[p2] = 0;

    //Encontra aleatoriamente a posição de um nó, que não seja igual a p2
    do{
        p3 = random_l_h(0,n-1);
    }while(b[p3] != 0 || p3 == p2);

    //Encontra aleatoriamente a posição de um nó, que não seja igual a p1
    do{
        p4 = random_l_h(0,n-1);
    }while(b[p4] != 1 || p4 == p1);

    //Troca os valores dos nós nas posições encontradas
    b[p3] = 1;
    b[p4] = 0;
}

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, custo, custo_viz, i;

    nova_sol = malloc(sizeof(int)*vert);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);
    for(i=0; i<num_iter; i++)
    {
        // Gera vizinho
        gera_vizinho(sol, nova_sol, vert);
        //gera_vizinho2(sol, nova_sol, vert);
        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, mat, vert);
        // Aceita vizinho se o custo diminuir (problema de minimizacao)
        if(custo_viz < custo)
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
    }
    free(nova_sol);
    return custo;
}

int trepa_colinas_probabilistico(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, custo, custo_viz, i;

    nova_sol = malloc(sizeof(int)*vert);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);
    for(i=0; i<num_iter; i++)
    {
        // Gera vizinho
//        gera_vizinho(sol, nova_sol, vert);
        gera_vizinho2(sol, nova_sol, vert);
        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, mat, vert);
        // Aceita vizinho se o custo diminuir (problema de minimizacao)
        if(custo_viz >= custo)
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
        else{
            if(rand_01() < PROB)
            {
                substitui(sol,nova_sol,vert);
                custo = custo_viz;
            }
        }
    }
    free(nova_sol);
    return custo;
}

int recristalizacao_simulada(int sol[], int *mat, int vert, int num_iter){
    int *nova_sol, custo, custo_viz, i, best_custo, *best_sol;
    float t = TMAX, decrementoT;

    //Calculo da decrementação de T para ir de TMAX a TMIN em num_inter
    decrementoT = (TMAX - TMIN) / num_iter;

    //Aloca espaço em memória para guardar a nova solução e a melhor solução
    nova_sol = malloc(sizeof(int) *vert);
    best_sol = malloc(sizeof(int) *vert);

    //Caso não consigo fazer a alocação, envia aviso e termina o programa
    if(nova_sol == NULL || best_sol == NULL){
        printf("Erro na alocação de memória\n");
        exit(1);
    }

    //Avalia solução inicial
    custo = calcula_fit(sol, mat, vert);
    //Guarda essa solução inicial como a melhor
    best_custo = custo;
    substitui(best_sol,sol,vert);
    for(i=0;i<num_iter;i++){
        //Gera solução vizinha
        gera_vizinho(sol,nova_sol,vert);
        //Avalia solução vizinha
        custo_viz = calcula_fit(nova_sol,mat,vert);
        //Se a solução vizinha for melhor que a solução atual, guarda-a como a melhor
        if(custo_viz < best_custo){
            best_custo = custo_viz;
            substitui(best_sol,nova_sol,vert);
        }

        //Fica com a solução vizinha se o custo não aumentar (problema de minimização)
        if(custo_viz <= custo){
            substitui(sol,nova_sol,vert);
            custo = custo_viz;
        }
        else{
            //Fica com a solução vizinha, apesar de pior, se o valor aleatório gerado
            if(rand_01() < exp((custo - custo_viz)/ t)){
                substitui(sol,nova_sol,vert);
                custo = custo_viz;
            }
        }
        t = t - decrementoT;
    }

    //Retorna a melhor solução encontrada
    substitui(sol,best_sol,vert);
    //Liberta a memória utilizada para guardar a nova solução e a melhor solução
    free(nova_sol);
    free(best_sol);

    //Devolve o custo da melhor solução encontrada
    return best_custo;
}