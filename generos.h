#ifndef GENEROS_H
#define GENEROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GENEROS 50

struct Genero {
    int codigo;
    char nome[40];
    char descricao[60];
};

struct Genero listaGeneros[MAX_GENEROS];
int totalGeneros = 0;

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
    printf("[SISTEMA] %d generos salvos em 'generos.csv'!\n", totalGeneros);
}

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
    
    salvarGenerosCSV();
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

void buscarGenero() {
    int cod;
    printf("\nDigite o codigo do genero para buscar: ");
    scanf("%d", &cod);
    
    for(int i = 0; i < totalGeneros; i++) {
        if(listaGeneros[i].codigo == cod) {
            printf("\n--- GENERO ENCONTRADO ---\n");
            printf("Codigo: %d\n", listaGeneros[i].codigo);
            printf("Nome: %s\n", listaGeneros[i].nome);
            printf("Descricao: %s\n", listaGeneros[i].descricao);
            return;
        }
    }
    printf("[ERRO] Genero nao encontrado.\n");
}

void editarGenero() {
    int cod;
    printf("\nDigite o codigo do genero para editar: ");
    scanf("%d", &cod);
    
    for(int i = 0; i < totalGeneros; i++) {
        if(listaGeneros[i].codigo == cod) {
            printf("\n--- EDITANDO: %s ---\n", listaGeneros[i].nome);
            printf("Novo nome do genero (ex: Rock, Jazz): ");
            scanf(" %39[^\n]", listaGeneros[i].nome);

            printf("Nova descricao / Caracteristica: ");
            scanf(" %59[^\n]", listaGeneros[i].descricao);

            printf("Genero atualizado com sucesso!\n");
            salvarGenerosCSV();
            return;
        }
    }
    printf("[ERRO] Genero nao encontrado para edicao.\n");
}

void excluirGenero() {
    int cod;
    printf("\nDigite o codigo do genero para excluir: ");
    scanf("%d", &cod);
    
    for(int i = 0; i < totalGeneros; i++) {
        if(listaGeneros[i].codigo == cod) {
            for(int j = i; j < totalGeneros - 1; j++) {
                listaGeneros[j] = listaGeneros[j + 1];
            }
            totalGeneros--;
            printf("Genero excluido com sucesso!\n");
            salvarGenerosCSV();
            return;
        }
    }
    printf("[ERRO] Genero nao encontrado para exclusao.\n");
}

void menuGeneros() {
    carregarGenerosCSV();
    int op;

    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        printf("============================================================\n");
        printf("                      MENU DE GENEROS                       \n");
        printf("============================================================\n");
        printf(" 1. Cadastrar Genero\n");
        printf(" 2. Listar Generos\n");
        printf(" 3. Buscar Genero\n");
        printf(" 4. Editar Genero\n");
        printf(" 5. Excluir Genero\n");
        printf(" 0. Voltar ao Menu Principal\n");
        printf("============================================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                cadastrarGeneroMemoria();
                break;
            case 2:
                listarGeneros();
                break;
            case 3:
                buscarGenero();
                break;
            case 4:
                editarGenero();
                break;
            case 5:
                excluirGenero();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
        
        if (op != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (op != 0);
}

#endif