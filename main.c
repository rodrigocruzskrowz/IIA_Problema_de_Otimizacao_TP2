#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define DEFAULT_RUNS 10

int main(int argc, char *argv[])
{
    int num_iter = 100;

    int opc = 1;
    while(opc != 0) {
        printf("\n\n::: ALGORITMOS :::\n");
        printf("PESQUISA LOCAL\n");
        printf("1-Algoritmo Pesquisa Local 1 (Trepa Colinas Probabilistico com Vizinhança 1)\n");
        printf("2-Algoritmo Pesquisa Local 2 (Trepa Colinas Probabilistico com Vizinhança 2)\n");
        printf("EVOLUTIVOS\n");
        printf("3-Algoritmo Evolutivo 1 (Recombinação com 1 ponto de corte + Mutação binária)\n");
        printf("4-Algoritmo Evolutivo 2 (Recombinação com 1 ponto de corte + Mutação por troca)\n");
        printf("5-Algoritmo Evolutivo 3 (Recombinação com 2 pontos de corte + Mutação binária)\n");
        printf("6-Algoritmo Evolutivo 4 (Recombinação com 2 pontos de corte + Mutação por troca)\n");
        printf("HÍBRIDOS\n");
        printf("7-Método Híbrido 1 (Pesquisa Local 1 + Evolutivo 1)\n");
        printf("8-Método Híbrido 2 (Pesquisa Local 1 + Evolutivo 3)\n");
        printf("0-Sair\n");
        printf("Opção: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1: {
                //TREPA COLINAS PROBABILÍSTICO - COM VIZINHANÇA 1

                char    nome_fich[100];
                int     vert, arest, i, runs, custo, best_custo, k;
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

                    printf("Número de iterações: ");
                    scanf("%d", &num_iter);

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
//                    custo = trepa_colinas(sol, grafo, vert, vert);
		            custo = trepa_colinas_viz1(sol, grafo, vert, num_iter);
//                    custo = recristalizacao_simulada(sol, grafo, vert, vert);
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
                // Escreve resultados globais
                printf("\n\nMBF: %f\n", mbf/i);
                printf("\nMelhor solucao encontrada");
                escreve_sol(best, vert, k);
                printf("Custo final: %2d\n\n", best_custo);
                logtofile(num_iter,best_custo,mbf/i);
                free(grafo);
                free(sol);
                free(best);
                break;
            }
            case 2: {
                //TREPA COLINAS PROBABILÍSTICO - COM VIZINHANÇA 2

                char    nome_fich[100];
                int     vert, arest, i, runs, custo, best_custo, k;
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

                    printf("Número de iterações: ");
                    scanf("%d", &num_iter);

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
//                    custo = trepa_colinas(sol, grafo, vert, vert);
                    custo = trepa_colinas_viz2(sol, grafo, vert, num_iter);
//                    custo = recristalizacao_simulada(sol, grafo, vert, vert);
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
                // Escreve resultados globais
                printf("\n\nMBF: %f\n", mbf/i);
                printf("\nMelhor solucao encontrada");
                escreve_sol(best, vert, k);
                printf("Custo final: %2d\n\n", best_custo);
                logtofile(num_iter,best_custo,mbf/i);
                free(grafo);
                free(sol);
                free(best);
                break;
            }
            case 3:{
                //ALGORITMO EVOLUTIVO - Recombinação com 1 ponto de corte + Mutação binária

                char        nome_fich[100];
                struct info EA_param;
                pchrom      pop = NULL, parents = NULL;
                chrom       best_run, best_ever;
                int         gen_actual, r, runs, i, inv, mat[MAX_OBJ][MAX_OBJ];
                float       mbf = 0.0;

                // Lê os argumentos de entrada
                if (argc == 3)
                {
                    runs = atoi(argv[2]);
                    if(runs <= 0){
                        printf("\n[ERROR] Número de repetições tem de ser igual ou superior a 10!\n");
                        exit(1);
                    }
                    strcpy(nome_fich, argv[1]);
                }
                else
                    // Se o número de execuções do processo não for colocado nos argumentos de entrada, define-o com um valor por defeito
                if (argc == 2)
                {
                    runs = DEFAULT_RUNS;
                    strcpy(nome_fich, argv[1]);
                }
                    // Se o nome do ficheiro de informações não for colocado nos argumentos de entrada, pede-o novamente
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
                //Inicializa a geração dos números aleatórios
                init_rand_evol();
                // Preenche a matriz com dados dos objectos (peso e valor) e a estrutura EA_param que foram definidos no ficheiro de input
                EA_param = init_data_evol(nome_fich, *mat);
                // Faz um ciclo com o número de execuções definidas
                for (r=0; r<runs; r++)
                {
                    printf("Repeticao %d\n",r+1);
                    // Geração da população inicial
                    pop = init_pop_evol(EA_param);
                    // Avalia a população inicial
                    evaluate_evol(pop, EA_param, *mat);
                    gen_actual = 1;

                    // Como ainda não existe, escolhe-se como melhor solução a primeira da população (poderia ser outra qualquer)
                    best_run = pop[0];
                    // Encontra-se a melhor solução dentro de toda a população
                    best_run = get_best_evol(pop, EA_param, best_run);
                    // Reserva espaço para os pais da população seguinte
                    parents = malloc(sizeof(chrom)*EA_param.popsize);
                    // Caso não consiga fazer a alocação, envia aviso e termina o programa
                    if (parents==NULL)
                    {
                        printf("[ERRO] Erro na alocacao de memoria\n");
                        exit(1);
                    }
                    // Ciclo de optimização
                    while (gen_actual <= EA_param.numGenerations)
                    {
                        // Torneio binário para encontrar os progenitores (ficam armazenados no vector parents)
                        tournament_evol(pop, EA_param, parents);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        // Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
                        genetic_operators_evol_1pcortebin(parents, EA_param, pop);
                        // Avalia a nova população (a dos filhos)
                        evaluate_evol(pop, EA_param, *mat);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");

                        // Actualiza a melhor solução encontrada
                        best_run = get_best_evol(pop, EA_param, best_run);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        gen_actual++;
                    }

                    // Contagem das soluções inválidas
                    for (inv=0, i=0; i<EA_param.popsize; i++)
                        if (pop[i].valido == 0)
                            inv++;
                    // Escreve resultados da repetição que terminou
                    printf("\nRepeticao %d:", r);
                    write_best_evol(best_run, EA_param);
                    printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/EA_param.popsize);
                    mbf += best_run.fitness;
                    if (r==0 || best_run.fitness > best_ever.fitness)
                        best_ever = best_run;
                    // Liberta a memória usada
                    free(parents);
                    free(pop);
                }
                // Escreve resultados globais
                printf("\n\nMBF: %f\n", mbf/r);
                printf("\nMelhor solucao encontrada");
                write_best_evol(best_ever, EA_param);
                logtofile_evol(best_ever,EA_param,mbf/r);
                break;
            }
            case 4:{
                //ALGORITMO EVOLUTIVO - Recombinação com 1 ponto de corte + Mutação por troca

                char        nome_fich[100];
                struct info EA_param;
                pchrom      pop = NULL, parents = NULL;
                chrom       best_run, best_ever;
                int         gen_actual, r, runs, i, inv, mat[MAX_OBJ][MAX_OBJ];
                float       mbf = 0.0;

                // Lê os argumentos de entrada
                if (argc == 3)
                {
                    runs = atoi(argv[2]);
                    if(runs <= 0){
                        printf("\n[ERROR] Número de repetições tem de ser igual ou superior a 10!\n");
                        exit(1);
                    }
                    strcpy(nome_fich, argv[1]);
                }
                else
                    // Se o número de execuções do processo não for colocado nos argumentos de entrada, define-o com um valor por defeito
                if (argc == 2)
                {
                    runs = DEFAULT_RUNS;
                    strcpy(nome_fich, argv[1]);
                }
                    // Se o nome do ficheiro de informações não for colocado nos argumentos de entrada, pede-o novamente
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
                //Inicializa a geração dos números aleatórios
                init_rand_evol();
                // Preenche a matriz com dados dos objectos (peso e valor) e a estrutura EA_param que foram definidos no ficheiro de input
                EA_param = init_data_evol(nome_fich, *mat);
                // Faz um ciclo com o número de execuções definidas
                for (r=0; r<runs; r++)
                {
                    printf("Repeticao %d\n",r+1);
                    // Geração da população inicial
                    pop = init_pop_evol(EA_param);
                    // Avalia a população inicial
                    evaluate_evol(pop, EA_param, *mat);
                    gen_actual = 1;

                    // Como ainda não existe, escolhe-se como melhor solução a primeira da população (poderia ser outra qualquer)
                    best_run = pop[0];
                    // Encontra-se a melhor solução dentro de toda a população
                    best_run = get_best_evol(pop, EA_param, best_run);
                    // Reserva espaço para os pais da população seguinte
                    parents = malloc(sizeof(chrom)*EA_param.popsize);
                    // Caso não consiga fazer a alocação, envia aviso e termina o programa
                    if (parents==NULL)
                    {
                        printf("[ERRO] Erro na alocacao de memoria\n");
                        exit(1);
                    }
                    // Ciclo de optimização
                    while (gen_actual <= EA_param.numGenerations)
                    {
                        // Torneio binário para encontrar os progenitores (ficam armazenados no vector parents)
                        tournament_evol(pop, EA_param, parents);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        // Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
                        genetic_operators_evol_1pcortetroca(parents, EA_param, pop);
                        // Avalia a nova população (a dos filhos)
                        evaluate_evol(pop, EA_param, *mat);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");

                        // Actualiza a melhor solução encontrada
                        best_run = get_best_evol(pop, EA_param, best_run);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        gen_actual++;
                    }

                    // Contagem das soluções inválidas
                    for (inv=0, i=0; i<EA_param.popsize; i++)
                        if (pop[i].valido == 0)
                            inv++;
                    // Escreve resultados da repetição que terminou
                    printf("\nRepeticao %d:", r);
                    write_best_evol(best_run, EA_param);
                    printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/EA_param.popsize);
                    mbf += best_run.fitness;
                    if (r==0 || best_run.fitness > best_ever.fitness)
                        best_ever = best_run;
                    // Liberta a memória usada
                    free(parents);
                    free(pop);
                }
                // Escreve resultados globais
                printf("\n\nMBF: %f\n", mbf/r);
                printf("\nMelhor solucao encontrada");
                write_best_evol(best_ever, EA_param);
                logtofile_evol(best_ever,EA_param,mbf/r);
                break;
            }
            case 5:{
                //ALGORITMO EVOLUTIVO - Recombinação com 2 ponto de corte + Mutação binária

                char        nome_fich[100];
                struct info EA_param;
                pchrom      pop = NULL, parents = NULL;
                chrom       best_run, best_ever;
                int         gen_actual, r, runs, i, inv, mat[MAX_OBJ][MAX_OBJ];
                float       mbf = 0.0;

                // Lê os argumentos de entrada
                if (argc == 3)
                {
                    runs = atoi(argv[2]);
                    if(runs <= 0){
                        printf("\n[ERROR] Número de repetições tem de ser igual ou superior a 10!\n");
                        exit(1);
                    }
                    strcpy(nome_fich, argv[1]);
                }
                else
                    // Se o número de execuções do processo não for colocado nos argumentos de entrada, define-o com um valor por defeito
                if (argc == 2)
                {
                    runs = DEFAULT_RUNS;
                    strcpy(nome_fich, argv[1]);
                }
                    // Se o nome do ficheiro de informações não for colocado nos argumentos de entrada, pede-o novamente
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
                //Inicializa a geração dos números aleatórios
                init_rand_evol();
                // Preenche a matriz com dados dos objectos (peso e valor) e a estrutura EA_param que foram definidos no ficheiro de input
                EA_param = init_data_evol(nome_fich, *mat);
                // Faz um ciclo com o número de execuções definidas
                for (r=0; r<runs; r++)
                {
                    printf("Repeticao %d\n",r+1);
                    // Geração da população inicial
                    pop = init_pop_evol(EA_param);
                    // Avalia a população inicial
                    evaluate_evol(pop, EA_param, *mat);
                    gen_actual = 1;

                    // Como ainda não existe, escolhe-se como melhor solução a primeira da população (poderia ser outra qualquer)
                    best_run = pop[0];
                    // Encontra-se a melhor solução dentro de toda a população
                    best_run = get_best_evol(pop, EA_param, best_run);
                    // Reserva espaço para os pais da população seguinte
                    parents = malloc(sizeof(chrom)*EA_param.popsize);
                    // Caso não consiga fazer a alocação, envia aviso e termina o programa
                    if (parents==NULL)
                    {
                        printf("[ERRO] Erro na alocacao de memoria\n");
                        exit(1);
                    }
                    // Ciclo de optimização
                    while (gen_actual <= EA_param.numGenerations)
                    {
                        // Torneio binário para encontrar os progenitores (ficam armazenados no vector parents)
                        tournament_evol(pop, EA_param, parents);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        // Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
                        genetic_operators_evol_2pcortebin(parents, EA_param, pop);
                        // Avalia a nova população (a dos filhos)
                        evaluate_evol(pop, EA_param, *mat);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");

                        // Actualiza a melhor solução encontrada
                        best_run = get_best_evol(pop, EA_param, best_run);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        gen_actual++;
                    }

                    // Contagem das soluções inválidas
                    for (inv=0, i=0; i<EA_param.popsize; i++)
                        if (pop[i].valido == 0)
                            inv++;
                    // Escreve resultados da repetição que terminou
                    printf("\nRepeticao %d:", r);
                    write_best_evol(best_run, EA_param);
                    printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/EA_param.popsize);
                    mbf += best_run.fitness;
                    if (r==0 || best_run.fitness > best_ever.fitness)
                        best_ever = best_run;
                    // Liberta a memória usada
                    free(parents);
                    free(pop);
                }
                // Escreve resultados globais
                printf("\n\nMBF: %f\n", mbf/r);
                printf("\nMelhor solucao encontrada");
                write_best_evol(best_ever, EA_param);
                logtofile_evol(best_ever,EA_param,mbf/r);
                break;
            }
            case 6:{
                //ALGORITMO EVOLUTIVO - Recombinação com 2 pontos de corte + Mutação por troca

                char        nome_fich[100];
                struct info EA_param;
                pchrom      pop = NULL, parents = NULL;
                chrom       best_run, best_ever;
                int         gen_actual, r, runs, i, inv, mat[MAX_OBJ][MAX_OBJ];
                float       mbf = 0.0;

                // Lê os argumentos de entrada
                if (argc == 3)
                {
                    runs = atoi(argv[2]);
                    if(runs <= 0){
                        printf("\n[ERROR] Número de repetições tem de ser igual ou superior a 10!\n");
                        exit(1);
                    }
                    strcpy(nome_fich, argv[1]);
                }
                else
                    // Se o número de execuções do processo não for colocado nos argumentos de entrada, define-o com um valor por defeito
                if (argc == 2)
                {
                    runs = DEFAULT_RUNS;
                    strcpy(nome_fich, argv[1]);
                }
                    // Se o nome do ficheiro de informações não for colocado nos argumentos de entrada, pede-o novamente
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
                //Inicializa a geração dos números aleatórios
                init_rand_evol();
                // Preenche a matriz com dados dos objectos (peso e valor) e a estrutura EA_param que foram definidos no ficheiro de input
                EA_param = init_data_evol(nome_fich, *mat);
                // Faz um ciclo com o número de execuções definidas
                for (r=0; r<runs; r++)
                {
                    printf("Repeticao %d\n",r+1);
                    // Geração da população inicial
                    pop = init_pop_evol(EA_param);
                    // Avalia a população inicial
                    evaluate_evol(pop, EA_param, *mat);
                    gen_actual = 1;

                    // Como ainda não existe, escolhe-se como melhor solução a primeira da população (poderia ser outra qualquer)
                    best_run = pop[0];
                    // Encontra-se a melhor solução dentro de toda a população
                    best_run = get_best_evol(pop, EA_param, best_run);
                    // Reserva espaço para os pais da população seguinte
                    parents = malloc(sizeof(chrom)*EA_param.popsize);
                    // Caso não consiga fazer a alocação, envia aviso e termina o programa
                    if (parents==NULL)
                    {
                        printf("[ERRO] Erro na alocacao de memoria\n");
                        exit(1);
                    }
                    // Ciclo de optimização
                    while (gen_actual <= EA_param.numGenerations)
                    {
                        // Torneio binário para encontrar os progenitores (ficam armazenados no vector parents)
                        tournament_evol(pop, EA_param, parents);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        // Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
                        genetic_operators_evol_2pcortetroca(parents, EA_param, pop);
                        // Avalia a nova população (a dos filhos)
                        evaluate_evol(pop, EA_param, *mat);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");

                        // Actualiza a melhor solução encontrada
                        best_run = get_best_evol(pop, EA_param, best_run);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        gen_actual++;
                    }

                    // Contagem das soluções inválidas
                    for (inv=0, i=0; i<EA_param.popsize; i++)
                        if (pop[i].valido == 0)
                            inv++;
                    // Escreve resultados da repetição que terminou
                    printf("\nRepeticao %d:", r);
                    write_best_evol(best_run, EA_param);
                    printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/EA_param.popsize);
                    mbf += best_run.fitness;
                    if (r==0 || best_run.fitness > best_ever.fitness)
                        best_ever = best_run;
                    // Liberta a memória usada
                    free(parents);
                    free(pop);
                }
                // Escreve resultados globais
                printf("\n\nMBF: %f\n", mbf/r);
                printf("\nMelhor solucao encontrada");
                write_best_evol(best_ever, EA_param);
                logtofile_evol(best_ever,EA_param,mbf/r);
                break;
            }
            case 7:{
                //MÉTODO HÍBRIDO - Local 1 + Evolutivo 1 (Vizinhança 1 + Recombinação com 1 ponto de corte + Mutação binária)

                char        nome_fich[100];
                struct info EA_param;
                pchrom      pop = NULL, parents = NULL;
                chrom       best_run, best_ever;
                int         gen_actual, r, runs, i, inv, mat[MAX_OBJ][MAX_OBJ];
                float       mbf = 0.0;

                // Lê os argumentos de entrada
                if (argc == 3)
                {
                    runs = atoi(argv[2]);
                    if(runs <= 0){
                        printf("\n[ERROR] Número de repetições tem de ser igual ou superior a 10!\n");
                        exit(1);
                    }
                    strcpy(nome_fich, argv[1]);
                }
                else
                    // Se o número de execuções do processo não for colocado nos argumentos de entrada, define-o com um valor por defeito
                if (argc == 2)
                {
                    runs = DEFAULT_RUNS;
                    strcpy(nome_fich, argv[1]);
                }
                    // Se o nome do ficheiro de informações não for colocado nos argumentos de entrada, pede-o novamente
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
                //Inicializa a geração dos números aleatórios
                init_rand_evol();
                // Preenche a matriz com dados dos objectos (peso e valor) e a estrutura EA_param que foram definidos no ficheiro de input
                EA_param = init_data_evol(nome_fich, *mat);
                // Faz um ciclo com o número de execuções definidas
                for (r=0; r<runs; r++)
                {
                    printf("Repeticao %d\n",r+1);
                    // Geração da população inicial
                    pop = init_pop_evol(EA_param);
                    // Avalia a população inicial
                    evaluate_evol(pop, EA_param, *mat);
                    gen_actual = 1;

                    //Aplicação do algoritmo trepa colinas para refinar a população inicial
                    trepa_colinas_evol(pop, EA_param, *mat);

                    // Como ainda não existe, escolhe-se como melhor solução a primeira da população (poderia ser outra qualquer)
                    best_run = pop[0];
                    // Encontra-se a melhor solução dentro de toda a população
                    best_run = get_best_evol(pop, EA_param, best_run);
                    // Reserva espaço para os pais da população seguinte
                    parents = malloc(sizeof(chrom)*EA_param.popsize);
                    // Caso não consiga fazer a alocação, envia aviso e termina o programa
                    if (parents==NULL)
                    {
                        printf("[ERRO] Erro na alocacao de memoria\n");
                        exit(1);
                    }
                    // Ciclo de optimização
                    while (gen_actual <= EA_param.numGenerations)
                    {
                        // Torneio binário para encontrar os progenitores (ficam armazenados no vector parents)
                        tournament_evol(pop, EA_param, parents);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        // Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
                        genetic_operators_evol_1pcortebin(parents, EA_param, pop);
                        // Avalia a nova população (a dos filhos)
                        evaluate_evol(pop, EA_param, *mat);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        //Aplicação do algoritmo trepa colinas para refinar a população final
//                        trepa_colinas_evol(pop,EA_param,*mat);

                        // Actualiza a melhor solução encontrada
                        best_run = get_best_evol(pop, EA_param, best_run);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        gen_actual++;
                    }

                    //Aplicação do algoritmo trepa colinas para refinar a população final
                    trepa_colinas_evol(pop, EA_param, *mat);

                    // Contagem das soluções inválidas
                    for (inv=0, i=0; i<EA_param.popsize; i++)
                        if (pop[i].valido == 0)
                            inv++;
                    // Escreve resultados da repetição que terminou
                    printf("\nRepeticao %d:", r);
                    write_best_evol(best_run, EA_param);
                    printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/EA_param.popsize);
                    mbf += best_run.fitness;
                    if (r==0 || best_run.fitness > best_ever.fitness)
                        best_ever = best_run;
                    // Liberta a memória usada
                    free(parents);
                    free(pop);
                }
                // Escreve resultados globais
                printf("\n\nMBF: %f\n", mbf/r);
                printf("\nMelhor solucao encontrada");
                write_best_evol(best_ever, EA_param);
                logtofile_evol(best_ever,EA_param,mbf/r);
                break;
            }
            case 8:{
                //MÉTODO HÍBRIDO - Local 1 + Evolutivo 1 (Vizinhança 1 + Recombinação com 2 pontos de corte + Mutação binária)

                char        nome_fich[100];
                struct info EA_param;
                pchrom      pop = NULL, parents = NULL;
                chrom       best_run, best_ever;
                int         gen_actual, r, runs, i, inv, mat[MAX_OBJ][MAX_OBJ];
                float       mbf = 0.0;

                // Lê os argumentos de entrada
                if (argc == 3)
                {
                    runs = atoi(argv[2]);
                    if(runs <= 0){
                        printf("\n[ERROR] Número de repetições tem de ser igual ou superior a 10!\n");
                        exit(1);
                    }
                    strcpy(nome_fich, argv[1]);
                }
                else
                    // Se o número de execuções do processo não for colocado nos argumentos de entrada, define-o com um valor por defeito
                if (argc == 2)
                {
                    runs = DEFAULT_RUNS;
                    strcpy(nome_fich, argv[1]);
                }
                    // Se o nome do ficheiro de informações não for colocado nos argumentos de entrada, pede-o novamente
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
                //Inicializa a geração dos números aleatórios
                init_rand_evol();
                // Preenche a matriz com dados dos objectos (peso e valor) e a estrutura EA_param que foram definidos no ficheiro de input
                EA_param = init_data_evol(nome_fich, *mat);
                // Faz um ciclo com o número de execuções definidas
                for (r=0; r<runs; r++)
                {
                    printf("Repeticao %d\n",r+1);
                    // Geração da população inicial
                    pop = init_pop_evol(EA_param);
                    // Avalia a população inicial
                    evaluate_evol(pop, EA_param, *mat);
                    gen_actual = 1;

                    //Aplicação do algoritmo trepa colinas para refinar a população inicial
                    trepa_colinas_evol(pop, EA_param, *mat);

                    // Como ainda não existe, escolhe-se como melhor solução a primeira da população (poderia ser outra qualquer)
                    best_run = pop[0];
                    // Encontra-se a melhor solução dentro de toda a população
                    best_run = get_best_evol(pop, EA_param, best_run);
                    // Reserva espaço para os pais da população seguinte
                    parents = malloc(sizeof(chrom)*EA_param.popsize);
                    // Caso não consiga fazer a alocação, envia aviso e termina o programa
                    if (parents==NULL)
                    {
                        printf("[ERRO] Erro na alocacao de memoria\n");
                        exit(1);
                    }
                    // Ciclo de optimização
                    while (gen_actual <= EA_param.numGenerations)
                    {
                        // Torneio binário para encontrar os progenitores (ficam armazenados no vector parents)
                        tournament_evol(pop, EA_param, parents);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        // Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
                        genetic_operators_evol_2pcortebin(parents, EA_param, pop);
                        // Avalia a nova população (a dos filhos)
                        evaluate_evol(pop, EA_param, *mat);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        //Aplicação do algoritmo trepa colinas para refinar a população final
//                        trepa_colinas_evol(pop,EA_param,*mat);

                        // Actualiza a melhor solução encontrada
                        best_run = get_best_evol(pop, EA_param, best_run);
                        if(contaSolsAllPop(pop, EA_param) != EA_param.popsize)
                            printf("DIF");
                        gen_actual++;
                    }

                    //Aplicação do algoritmo trepa colinas para refinar a população final
                    trepa_colinas_evol(pop, EA_param, *mat);

                    // Contagem das soluções inválidas
                    for (inv=0, i=0; i<EA_param.popsize; i++)
                        if (pop[i].valido == 0)
                            inv++;
                    // Escreve resultados da repetição que terminou
                    printf("\nRepeticao %d:", r);
                    write_best_evol(best_run, EA_param);
                    printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/EA_param.popsize);
                    mbf += best_run.fitness;
                    if (r==0 || best_run.fitness > best_ever.fitness)
                        best_ever = best_run;
                    // Liberta a memória usada
                    free(parents);
                    free(pop);
                }
                // Escreve resultados globais
                printf("\n\nMBF: %f\n", mbf/r);
                printf("\nMelhor solucao encontrada");
                write_best_evol(best_ever, EA_param);
                logtofile_evol(best_ever,EA_param,mbf/r);
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
