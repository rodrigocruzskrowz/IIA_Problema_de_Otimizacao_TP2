#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo.h"
#include "utils.h"
#include "funcao.h"

////TREPA COLINAS START :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

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
//        gera_vizinho(sol, nova_sol, vert);
        gera_vizinho2(sol, nova_sol, vert);
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

////TREPA COLINAS END :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

////EVOLUTIVO START :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// Preenche uma estrutura com os progenitores da pr�xima gera��o, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Par�metros de entrada: popula��o actual (pop), estrutura com par�metros (d) e popula��o de pais a encher
void tournament_evol(pchrom pop, struct info d, pchrom parents)
{
    int i, x1, x2;

    // Realiza popsize torneios
    for(i=0; i<d.popsize;i++)
    {
        x1 = random_l_h_evol(0, d.popsize - 1);
        do
            x2 = random_l_h_evol(0, d.popsize - 1);
        while(x1==x2);
        if(pop[x1].fitness > pop[x2].fitness)		// Problema de maximizacao
            parents[i]=pop[x1];
        else
            parents[i]=pop[x2];
    }
}

// Operadores geneticos a usar na gera��o dos filhos
// Par�metros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar� os descendentes (offspring)
void genetic_operators_evol(pchrom parents, struct info d, pchrom offspring)
{
    // Recombina��o com um ponto de corte
	crossover_evol(parents, d, offspring);
    if(contaSolsAllPop(offspring, d) != d.popsize)
        printf("DIF");
    //Recombinação com dois pontos de corte
//    crossover_dois_pontos_corte_evol(parents, d, offspring);

    //Recombinação uniforme
//    crossover_uniforme_evol(parents, d, offspring);

    // Muta��o bin�ria
    mutation_evol(offspring, d);
    if(contaSolsAllPop(offspring, d) != d.popsize)
        printf("DIF");
    //Mutação por troca
//    mutacao_por_troca_evol(offspring,d);
}

// Preenche o vector descendentes com o resultado das opera��es de recombina��o
// Par�metros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar� os descendentes (offspring)
void crossover_evol(pchrom parents, struct info d, pchrom offspring)
{
    int i, j, point, solucoes, pos1, pos2;

    for (i=0; i<d.popsize; i+=2)
    {
        if (rand_01_evol() < d.pr)
        {
            point = random_l_h_evol(0, d.numGenes - 1);
            for (j=0; j<point; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i+1].p[j] = parents[i+1].p[j];
            }
            for (j=point; j<d.numGenes; j++)
            {
                offspring[i].p[j]= parents[i+1].p[j];
                offspring[i+1].p[j] = parents[i].p[j];
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i+1];
        }

        //Verifica ksols das solucoes geradas
        if((solucoes= contaSolsPop(offspring,d,i)) != d.ksols) {
            repoeKSols(&solucoes, d, offspring, i);
        }
        if((solucoes= contaSolsPop(offspring,d,i+1)) != d.ksols) {
            repoeKSols(&solucoes, d, offspring, i+1);
        }
    }
}

void crossover_dois_pontos_corte_evol(pchrom parents, struct info d, pchrom offspring)
{
    int i, j, point1, point2;

    for (i=0; i<d.popsize; i+=2)
    {
        if (rand_01_evol() < d.pr)
        {
            point1 = random_l_h_evol(0, d.numGenes - 1);
            point2 = random_l_h_evol(point1 + 1, d.numGenes - 1);
            for (j=0; j<point1; j++) //Igual aos pais
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i+1].p[j] = parents[i+1].p[j];
            }
            for (j=point1; j<point2; j++) //Troca
            {
                offspring[i].p[j]= parents[i+1].p[j];
                offspring[i+1].p[j] = parents[i].p[j];
            }
            for (j=point2; j<d.numGenes; j++) //Igual aos pais
            {
                offspring[i].p[j]= parents[i].p[j];
                offspring[i+1].p[j] = parents[i+1].p[j];
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i+1];
        }
    }
}

void crossover_uniforme_evol(pchrom parents, struct info d, pchrom offspring)
{
    int i, j;

    for (i=0; i<d.popsize; i+=2)
    {
        if (rand_01_evol() < d.pr)
        {
            for(j=0; j<d.numGenes; j++)
            {
                if(flip_evol() == 1)
                {
                    offspring[i].p[j] = parents[i].p[j];
                    offspring[i+1].p[j] = parents[i+1].p[j];
                }
                else
                {
                    offspring[i].p[j] = parents[i+1].p[j];
                    offspring[i+1].p[j] = parents[i].p[j];
                }
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i+1];
        }
    }
}

// Muta��o bin�ria com v�rios pontos de muta��o
// Par�metros de entrada: estrutura com os descendentes (offspring) e estrutura com par�metros (d)
void mutation_evol(pchrom offspring, struct info d)
{
//    int i, j, x, posTroca;
//
//    for (i=0; i<d.popsize; i++)
//        for (j=0; j<d.ksols; j++)
//            if (rand_01_evol() < d.pm){
//                //remove um no que faz parte da solucao e adiciona um no que não faz parte da solucao
//                do{
//                    x = random_l_h_evol(0, d.numGenes - 1);
//                }while(offspring[i].p[x] != 0);
//                offspring[i].p[x] = !(offspring[i].p[x]);
//
//                posTroca = x;
//
//                do{
//                    x = random_l_h_evol(0, d.numGenes - 1);
//                }while(offspring[i].p[x] != 1 || x == posTroca);
//                offspring[i].p[x] = !(offspring[i].p[x]);
//            }

        int i, j, x, solucoes;

        solucoes = d.ksols;
        for (i=0; i<d.popsize; i++) {
            for (j = 0; j < d.ksols; j++) {
                if (rand_01_evol() < d.pm) {
                    x = random_l_h_evol(0, d.numGenes - 1);
                    if(offspring[i].p[x] == 1){
                        solucoes--;
                        offspring[i].p[x] = !(offspring[i].p[x]);
                    }
                    else if(offspring[i].p[x] == 0){
                        solucoes++;
                        offspring[i].p[x] = !(offspring[i].p[x]);
                    }
                    if(solucoes < d.ksols){
                        while(solucoes != d.ksols)
                        {
                            x = random_l_h_evol(0, d.numGenes - 1);
                            if(offspring[i].p[x] == 0) {
                                offspring[i].p[x] = !(offspring[i].p[x]);
                                solucoes++;
                            }
                        }
                    }
                    else if(solucoes > d.ksols){
                        while(solucoes != d.ksols)
                        {
                            x = random_l_h_evol(0, d.numGenes - 1);
                            if(offspring[i].p[x] == 1) {
                                offspring[i].p[x] = !(offspring[i].p[x]);
                                solucoes--;
                            }
                        }
                    }
                }
            }
        }


//    for (i=0; i<d.popsize; i++)
//        for (j=0; j<d.numGenes; j++)
//            if (rand_01_evol() < d.pm)
//                offspring[i].p[j] = !(offspring[i].p[j]);
}

void mutacao_por_troca_evol(pchrom offspring, struct info d){
    int i,pos1,pos2,aux;

    for(i=0;i<d.popsize;i++){
        if(rand_01_evol() < d.pm){
            do
                pos1 = random_l_h_evol(0, d.numGenes - 1);
            while(offspring[i].p[pos1] == 1);
            do
                pos2 = random_l_h_evol(0, d.numGenes - 1);
            while(offspring[i].p[pos2] == 0);
            aux = offspring[i].p[pos1] = offspring[i].p[pos2];
            offspring[i].p[pos2] = aux;
        }
    }
}

void repoeKSols(int *solucoes, struct info d, pchrom offspring, int iter){
    int point = -1;
    while(*solucoes != d.ksols) {
        if (*solucoes < d.ksols) {
            point = random_l_h_evol(0, d.numGenes - 1);
            if (offspring[iter].p[point] == 0) {
                offspring[iter].p[point] = !(offspring[iter].p[point]);
                (*solucoes)++;
            }
        }
        if (*solucoes > d.ksols) {
            point = random_l_h_evol(0, d.numGenes - 1);
            if (offspring[iter].p[point] == 1) {
                offspring[iter].p[point] = !(offspring[iter].p[point]);
                (*solucoes)--;
            }
        }
    }
}

//void repoeKSols(int *solucoes, struct info d, pchrom offspring, int pos1, int pos2, int pontoTroca, int point){
//    if(pos1 != -1 && pos2 != -1 && pontoTroca != -1 && *solucoes != d.ksols) {
//        while(*solucoes != d.ksols) {
//            if (*solucoes < d.ksols) {
//                do{
//                    point = random_l_h_evol(0, d.numGenes - 1);
//                }while(point == pontoTroca);
//                if (offspring[pos1].p[point] == 0) {
//                    offspring[pos1].p[point] = !(offspring[pos2].p[point]);
//                    (*solucoes)++;
//                }
//            }
//            if (*solucoes > d.ksols) {
//                do{
//                    point = random_l_h_evol(0, d.numGenes - 1);
//                }while(point == pontoTroca);
//                if (offspring[pos1].p[point] == 1) {
//                    offspring[pos1].p[point] = !(offspring[pos2].p[point]);
//                    (*solucoes)--;
//                }
//            }
//        }
//    }
//}

////EVOLUTIVO END :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::