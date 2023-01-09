#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define GENERATION_TC 100
#define PROBGERAVIZ 1.0

////TREPA COLINAS START :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

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

////TREPA COLINAS START :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

////EVOLUTIVO START :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

// Calcula a qualidade de uma solu��o
// Par�metros de entrada: solu��o (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de ligacoes (v)
// Par�metros de sa�da: qualidade da solu��o (se a capacidade for excedida devolve 0)
float eval_individual(int sol[], struct info d, int *mat, int *v)
{
    int     i, j;
    float   total;

    total = 0;
    // Percorre todos os objectos
    for (i=0; i < d.numGenes; i++)
    {
        // Verifica se o objecto i tem ligações
        if (sol[i] == 1)
        {
            for(j=0; j<d.numGenes;j++)
                if(sol[j]==1 && *(mat+i*d.numGenes+j)==1)
                    total++;
        }
    }
    if (total/2 > d.ligacoes)
    {
        // Solucao inv�lida
        *v = 0;
        return 0;
    }
    else
    {
        // Solucao v�lida
        *v = 1;
        return total/2;
    }
}

float eval_individual_nao_cega(int sol[], struct info d, int mat[][MAX_OBJ], int *v)
{
    int     i,j;
    float   total;

    total = 0;
    // Percorre todos os objectos
    for (i=0; i < d.numGenes; i++)
    {
        // Verifica se o objecto i tem ligacoes
        if (sol[i] == 1)
        {
            for(j=0; j<d.numGenes;j++)
                if(sol[j]==1 && *(mat+i*d.numGenes+j)==1)
                    total++;

            //Obtem melhor ro
            if(d.ro < (float)mat[i][1]/mat[i][0])
                d.ro = (float)mat[i][1]/mat[i][0];
        }
    }
    if (total/2 > d.ligacoes)
    {
        // Solucao inv�lida
        *v = 0;
        return (total/2)-d.ro; //Solução com personalização
    }
    else
    {
        // Solucao v�lida
        *v = 1;
        return total/2;
    }
}

float eval_individual_reparacao1_aleatoria(int sol[], struct info d, int mat[][2], int *v)
{
    int     i, j;
    float   total;

    total = 0;
    // Percorre todos os objectos
    for (i=0; i < d.numGenes; i++)
    {
        // Verifica se o objecto i esta na mochila
        if (sol[i] == 1)
        {
            for(j=0; j<d.numGenes;j++)
                if(sol[j]==1 && *(mat+i*d.numGenes+j)==1)
                    total++;
        }
    }
    //Processo de reparação
    while(total/2 > d.ligacoes){
        //Ecolhe um objeto aleatoriamente
        i = random_l_h_evol(0, d.numGenes - 1);
        //
        // Se o objeto estiver na mochila, retira-o e ajusta os somatórios do peso e lucro
        if(sol[i] == 1){
            sol[i] = 0;
        }
    }

    *v = 1;
    return total;
}

float eval_individual_reparacao2_heuristica_sofrega(int sol[], struct info d, int mat[][MAX_OBJ], int *v)
{
    int     i,mv,pos;
    float   sum_weight, sum_profit;

    sum_weight = sum_profit = 0;
    // Percorre todos os objectos
    for (i=0; i < d.numGenes; i++)
    {
        // Verifica se o objecto i esta na mochila
        if (sol[i] == 1)
        {
            // Actualiza o peso total
            sum_weight += mat[i][0];
            // Actualiza o lucro total
            sum_profit += mat[i][1];
        }
    }
    //Processo de reparação 2
    while(sum_weight > 0){
        pos = .1;
        for(i=0; i<d.numGenes; i++){
            if(sol[i] == 1){
                if(pos == -1 || mv > mat[i][1]){
                    mv = mat[i][1];
                    pos = i;
                }
            }
        }
        sol[pos] = 0;
        sum_weight -= mat[pos][0];
        sum_profit -= mat[pos][1];
    }

    *v = 1;
    return sum_profit;
}

// Avaliacao da popula��o
// Par�metros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Par�metros de sa�da: Preenche pop com os valores de fitness e de validade para cada solu��o
void evaluate_evol(pchrom pop, struct info d, int *mat)
{
    int i;

    //BASE (Penalização cega)
	for (i=0; i<d.popsize; i++)
		pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido);

    //Penalização não cega
//    for(i=0;i<d.popsize;i++){
//        pop[i].fitness = eval_individual_nao_cega(pop[i].p, d, mat, &pop[i].valido);
//    }

    //Reparação Aleatória
//    for(i=0;i<d.popsize;i++){
//        pop[i].fitness = eval_individual_reparacao1_aleatoria(pop[i].p, d, mat, &pop[i].valido);
//    }

    //Reparação Heuristica Sofrega
//    for(i=0;i<d.popsize;i++){
//        pop[i].fitness = eval_individual_reparacao2_heuristica_sofrega(pop[i].p, d, mat, &pop[i].valido);
//    }
}

void gera_vizinho_evol(int sol[], int solViz[], int *mat, int nGenes)
{
    int i, posTroca;

    //Copia a solução para a solução vizinha
    for (i = 0; i < nGenes; i++)
        solViz[i] = sol[i];

    //POBGERAVIZ de vezes uma solução vizinha é obtida com a troca do estado de um objeto
    if(rand_01_evol() < PROBGERAVIZ)
    {
        //remove um no que faz parte da solucao e adiciona um no que não faz parte da solucao
        do{
            i = random_l_h_evol(0, nGenes - 1);
        }while(solViz[i] != 0);
        solViz[i] = !solViz[i];

        posTroca = i;

        do{
            i = random_l_h_evol(0, nGenes - 1);
        }while(solViz[i] != 1 || i == posTroca);
        solViz[i] = !solViz[i];
    }
}

void gera_vizinho2_evol(int sol[], int solViz[], int *mat, int nGenes)
{
    int i, p1,p2,p3,p4;

    //Copia a solução para a solução vizinha
    for (i = 0; i < nGenes; i++)
        solViz[i] = sol[i];

    //POBGERAVIZ de vezes uma solução vizinha é obtida com a troca do estado de um objeto
    if(rand_01_evol() < PROBGERAVIZ)
    {
        //remove um no que faz parte da solucao e adiciona um no que não faz parte da solucao
        do{
            p1 = random_l_h_evol(0, nGenes - 1);
        }while(solViz[p1] != 0);

        do{
            p2 = random_l_h_evol(0, nGenes - 1);
        }while(solViz[p2] != 1 );

        // Troca
        solViz[p1] = 1;
        solViz[p2] = 0;

        //Volta a encontrar outro no nas mesmas condições
        do{
            p3 = random_l_h_evol(0,nGenes-1);
        }while(solViz[p3] != 0 || p3 == p2);

        //Encontra aleatoriamente a posição de um nó, que não seja igual a p1
        do{
            p4 = random_l_h_evol(0,nGenes-1);
        }while(solViz[p4] != 1 || p4 == p1);

        //Troca os valores dos nós nas posições encontradas
        solViz[p3] = 1;
        solViz[p4] = 0;

    }
}

void trepa_colinas_evol(pchrom pop, struct info d, int *mat)
{
    int i,j;
    chrom vizinho;

    for(i=0;i<d.popsize;i++)
    {
        for(j=0;j<GENERATION_TC;j++)
        {
            gera_vizinho_evol(pop[i].p, vizinho.p, mat, d.numGenes);
            vizinho.fitness = eval_individual(vizinho.p,d,mat,&vizinho.valido);
            if(vizinho.fitness >= pop[i].fitness)
                pop[i] = vizinho;
        }
    }
}


////EVOLUTIVO END :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
