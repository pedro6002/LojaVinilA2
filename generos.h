// ============================================================================
// MÓDULO: PERSPECTIVA DE GÊNEROS DOS VINIS
// Tema: Locadora de Discos de Vinil Retrô
// Autor: Pedro Henrique do Nascimento - RGM: 04792662-4
// ============================================================================

#ifndef GENEROS_H
#define GENEROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Define o limite máximo de gêneros que podem ser armazenados na memória
#define MAX_GENEROS 50

// Estrutura que representa um gênero musical
struct Genero {
    int codigo;
    char nome[40];
    char descricao[60];
};

// Vetor global para armazenar os gêneros em memória e contador de registros
struct Genero listaGeneros[MAX_GENEROS];
int totalGeneros = 0;

// Salva todos os gêneros atualmente na memória para o arquivo CSV
void salvarGenerosCSV() {
    // Abre o arquivo para escrita ("w" sobrescreve o conteúdo anterior)
    FILE *arq = fopen("generos.csv", "w");
    if (arq == NULL) {
        printf("[ERRO] Não foi possível abrir generos.csv para escrita!\n");
        return;
    }

    // Escreve cada registro separado por ponto e vírgula
    for (int i = 0; i < totalGeneros; i++) {
        fprintf(arq, "%d;%s;%s\n", 
                listaGeneros[i].codigo, 
                listaGeneros[i].nome, 
                listaGeneros[i].descricao);
    }

    fclose(arq); // Fecha o arquivo para garantir a gravação
    printf("[SISTEMA] %d gêneros salvos em 'generos.csv'!\n", totalGeneros);
}

// Lê os dados de um novo gênero via teclado, armazena na memória e salva no CSV
void cadastrarGeneroMemoria() {
    // Verifica se o vetor já está cheio
    if (totalGeneros >= MAX_GENEROS) {
        printf("[ERRO] Limite de gêneros atingido!\n");
        return;
    }

    printf("\n--- CADASTRO DE GÊNERO MUSICAL ---\n");

    printf("Código do gênero (int): ");
    scanf("%d", &listaGeneros[totalGeneros].codigo);

    // O espaço antes de %39[^\n] limpa quebras de linha pendentes no buffer e lê strings com espaços
    printf("Nome do gênero (ex: Rock, Jazz): ");
    scanf(" %39[^\n]", listaGeneros[totalGeneros].nome);

    printf("Descrição / Característica: ");
    scanf(" %59[^\n]", listaGeneros[totalGeneros].descricao);

    totalGeneros++; // Incrementa o total de gêneros cadastrados
    printf("Gênero cadastrado com sucesso!\n");
    
    // Atualiza o arquivo CSV imediatamente
    salvarGenerosCSV();
}

// Carrega os gêneros salvos no arquivo CSV para a memória ao iniciar o menu
void carregarGenerosCSV() {
    FILE *arq = fopen("generos.csv", "r");
    // Se o arquivo ainda não existir, apenas retorna sem erro
    if (arq == NULL) {
        return;
    }

    totalGeneros = 0;
    
    // Lê linha por linha enquanto houver espaço no vetor e os 3 campos forem lidos com sucesso
    while (totalGeneros < MAX_GENEROS && 
           fscanf(arq, "%d;%39[^;];%59[^\n]\n", 
                  &listaGeneros[totalGeneros].codigo, 
                  listaGeneros[totalGeneros].nome, 
                  listaGeneros[totalGeneros].descricao) == 3) {
        totalGeneros++;
    }

    fclose(arq);
}

// Exibe na tela todos os gêneros musicais cadastrados
void listarGeneros() {
    printf("\n=== GÊNEROS MUSICAIS CADASTRADOS (%d) ===\n", totalGeneros);
    if (totalGeneros == 0) {
        printf("Nenhum gênero cadastrado no momento.\n");
        return;
    }

    // Imprime cada gênero formatado em colunas
    for (int i = 0; i < totalGeneros; i++) {
        printf("[%d] %-15s | %s\n", 
               listaGeneros[i].codigo, 
               listaGeneros[i].nome, 
               listaGeneros[i].descricao);
    }
}

// Procura e exibe um gênero específico a partir do seu código
void buscarGenero() {
    int cod;
    printf("\nDigite o código do gênero para buscar: ");
    scanf("%d", &cod);
    
    for (int i = 0; i < totalGeneros; i++) {
        if (listaGeneros[i].codigo == cod) {
            printf("\n--- GÊNERO ENCONTRADO ---\n");
            printf("Código: %d\n", listaGeneros[i].codigo);
            printf("Nome: %s\n", listaGeneros[i].nome);
            printf("Descrição: %s\n", listaGeneros[i].descricao);
            return;
        }
    }
    printf("[ERRO] Gênero não encontrado.\n");
}

// Altera o nome e a descrição de um gênero existente
void editarGenero() {
    int cod;
    printf("\nDigite o código do gênero para editar: ");
    scanf("%d", &cod);
    
    for (int i = 0; i < totalGeneros; i++) {
        if (listaGeneros[i].codigo == cod) {
            printf("\n--- EDITANDO: %s ---\n", listaGeneros[i].nome);
            printf("Novo nome do gênero (ex: Rock, Jazz): ");
            scanf(" %39[^\n]", listaGeneros[i].nome);

            printf("Nova descrição / Característica: ");
            scanf(" %59[^\n]", listaGeneros[i].descricao);

            printf("Gênero atualizado com sucesso!\n");
            salvarGenerosCSV(); // Persiste a alteração no CSV
            return;
        }
    }
    printf("[ERRO] Gênero não encontrado para edição.\n");
}

// Remove um gênero da memória reorganizando o vetor e atualiza o CSV
void excluirGenero() {
    int cod;
    printf("\nDigite o código do gênero para excluir: ");
    scanf("%d", &cod);
    
    for (int i = 0; i < totalGeneros; i++) {
        if (listaGeneros[i].codigo == cod) {
            // Desloca os elementos posteriores uma posição para trás para preencher o espaço
            for (int j = i; j < totalGeneros - 1; j++) {
                listaGeneros[j] = listaGeneros[j + 1];
            }
            totalGeneros--; // Reduz o contador total
            printf("Gênero excluído com sucesso!\n");
            salvarGenerosCSV(); // Atualiza o arquivo CSV
            return;
        }
    }
    printf("[ERRO] Gênero não encontrado para exclusão.\n");
}

// Controla a interface de interação com o usuário para o módulo de gêneros
void menuGeneros() {
    carregarGenerosCSV(); // Carrega dados prévios antes de exibir o menu
    int op;

    do {
        // Limpa a tela do terminal de acordo com o sistema operacional
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        printf("============================================================\n");
        printf("                      MENU DE GÊNEROS                       \n");
        printf("============================================================\n");
        printf(" 1. Cadastrar Gênero\n");
        printf(" 2. Listar Gêneros\n");
        printf(" 3. Buscar Gênero\n");
        printf(" 4. Editar Gênero\n");
        printf(" 5. Excluir Gênero\n");
        printf(" 0. Voltar ao Menu Principal\n");
        printf("============================================================\n");
        printf("Escolha uma opção: ");
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
                printf("Opção inválida!\n");
        }
        
        // Pausa a execução para o usuário ler a saída antes de limpar a tela novamente
        if (op != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); // Consome o '\n' deixado pelo scanf anterior
            getchar(); // Aguarda o ENTER do usuário
        }

    } while (op != 0);
}

#endif
