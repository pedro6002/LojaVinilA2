#ifndef generos_h
#define generos_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_generos 50


struct Genero {
    int codigo;
    char nome[40];
    char descricao[60];
};


struct Genero listaGeneros[max_generos];
int totalGeneros = 0;

void cadastrarGeneroMemoria() {
    if (totalGeneros >= MAX_GENEROS) {
        printf("[ERRO] Limite de generos atingido!\n");
        return;
    }

    printf("\n--- CADASTRO DE GENERO MUSICAL ---\n");

    printf("Codigo do genero (int): ");
    scanf("%d", &listaGeneros[totalGeneros].codigo);

    printf("Nome do genero (ex: Rock, Jazz): ");
    scanf(" %39[^\n]", listaGeneros[totalGeneros].nome);

    printf("Descricao / Caracteristica: ");
    scanf(" %59[^\n]", listaGeneros[totalGeneros].descricao);

    totalGeneros++;
    printf("Genero cadastrado com sucesso!\n");
}

void salvarGenerosCSV() {
    FILE *arq = fopen("generos.csv", "w");
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel abrir generos.csv para escrita!\n");
        return;
    }

    for (int i = 0; i < totalGeneros; i++) {
        fprintf(arq, "%d;%s;%s\n", 
                listaGeneros[i].codigo, 
                listaGeneros[i].nome, 
                listaGeneros[i].descricao);
    }

    fclose(arq);
    printf("[DISCO] %d generos salvos em 'generos.csv'!\n", totalGeneros);
}

void carregarGenerosCSV() {
    FILE *arq = fopen("generos.csv", "r");
    if (arq == NULL) {
        
        return;
    }

    totalGeneros = 0;
    
    while (totalGeneros < MAX_GENEROS && 
           fscanf(arq, "%d;%39[^;];%59[^\n]\n", 
                  &listaGeneros[totalGeneros].codigo, 
                  listaGeneros[totalGeneros].nome, 
                  listaGeneros[totalGeneros].descricao) == 3) {
        totalGeneros++;
    }

    fclose(arq);
}

void listarGeneros() {
    printf("\n=== GENEROS MUSICAIS CADASTRADOS (%d) ===\n", totalGeneros);
    if (totalGeneros == 0) {
        printf("Nenhum genero cadastrado no momento.\n");
        return;
    }

    for (int i = 0; i < totalGeneros; i++) {
        printf("[%d] %-15s | %s\n", 
               listaGeneros[i].codigo, 
               listaGeneros[i].nome, 
               listaGeneros[i].descricao);
    }
}

void menuGeneros() {
    int op;
    do {
        printf("\n--- MENU GENEROS ---\n");
        printf("1. Cadastrar Genero\n");
        printf("2. Listar Generos\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                cadastrarGeneroMemoria();
                salvarGenerosCSV();
                break;
            case 2:
                listarGeneros();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (op != 0);
}

#endif