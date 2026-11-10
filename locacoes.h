// ============================================================================
// MÓDULO: PERSPECTIVA DE LOCAÇÃO E OPERAÇÃO DE VINIS (VERSÃO FINAL 100%)
// Tema: Locadora de Discos de Vinil Retrô
// Autor: Braian hladczuk - RGM: 04746379-1
// ============================================================================

#ifndef LOCACOES_H
#define LOCACOES_H

#include <stdio.h>
#include <string.h>

#include "clientes.h"
#include "discos.h"

struct LocacaoVinil {
    int idLocacao;
    int idClienteLocador;
    char codigoVinil[20];
    int diasAlugados;
    float valorLocacao;
};

struct LocacaoVinil historicoLocacoes[50];
int totalLocacoes = 0;

void salvarLocacoesCSV() {
    FILE *arquivo = fopen("locacoes.csv", "w");
    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo locacoes.csv para escrita.\n");
        return;
    }

    for (int i = 0; i < totalLocacoes; i++) {
        fprintf(arquivo, "%d;%d;%s;%d;%.2f\n",
                historicoLocacoes[i].idLocacao,
                historicoLocacoes[i].idClienteLocador,
                historicoLocacoes[i].codigoVinil,
                historicoLocacoes[i].diasAlugados,
                historicoLocacoes[i].valorLocacao);
    }

    fclose(arquivo);
}

void carregarLocacoesCSV() {
    FILE *arquivo = fopen("locacoes.csv", "r");
    if (arquivo == NULL) {
        printf("\n[AVISO] Arquivo locacoes.csv nao encontrado. Um novo sera criado ao salvar.\n");
        totalLocacoes = 0;
        return;
    }

    totalLocacoes = 0;
    while (totalLocacoes < 50 && fscanf(arquivo, "%d;%d;%19[^;];%d;%f\n",
                  &historicoLocacoes[totalLocacoes].idLocacao,
                  &historicoLocacoes[totalLocacoes].idClienteLocador,
                  historicoLocacoes[totalLocacoes].codigoVinil,
                  &historicoLocacoes[totalLocacoes].diasAlugados,
                  &historicoLocacoes[totalLocacoes].valorLocacao) == 5) {
        totalLocacoes++;
    }

    fclose(arquivo);
}

void ordenarLocacoesPorDias() {
    int i, j;
    struct LocacaoVinil aux;

    for (i = 0; i < totalLocacoes - 1; i++) {
        for (j = 0; j < totalLocacoes - i - 1; j++) {
            if (historicoLocacoes[j].diasAlugados < historicoLocacoes[j + 1].diasAlugados) {
                aux = historicoLocacoes[j];
                historicoLocacoes[j] = historicoLocacoes[j + 1];
                historicoLocacoes[j + 1] = aux;
            }
        }
    }
}

void menuLocacoes() {
    int opcaoModulo;
    int i;
    int idDiscoDigitado;
    struct LocacaoVinil novaLocacao;

    do {
        printf("\n======================================================\n");
        printf("     SISTEMA RETRO (1985) - MODULO DE LOCACOES        \n");
        printf("======================================================\n");
        printf("1. Alugar Novo Vinil (Balcao)\n");
        printf("2. Listar Locacoes (Ordem de Insercao)\n");
        printf("3. Relatorio: Alugueis Mais Longos (Bubble Sort)\n");
        printf("4. Relatorio: Receita Total de Locacoes\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("======================================================\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoModulo);

        switch (opcaoModulo) {
            case 1:
                if (totalLocacoes >= 50) {
                    printf("\n[ERRO] Vetor cheio na memoria RAM!\n");
                } else {
                    printf("\n--- Registrar Novo Aluguel ---\n");
                    
                    printf("ID do Cliente: ");
                    scanf("%d", &novaLocacao.idClienteLocador);
                    
                    int clienteExiste = 0;
                    for (i = 0; i < totalClientes; i++) { 
                        if (clientes[i].id == novaLocacao.idClienteLocador && clientes[i].status == 1) {
                            clienteExiste = 1;
                            break;
                        }
                    }
                    
                    if (!clienteExiste) {
                        printf("\n[ERRO] Cliente ID %d nao encontrado ou inativo!\n", novaLocacao.idClienteLocador);
                        break;
                    }

                    printf("ID do Disco do Felipe: ");
                    scanf("%d", &idDiscoDigitado);
                    
                    int discoDisponivel = 0;
                    for (i = 0; i < totalDiscos; i++) { 
                        if (discos[i].id == idDiscoDigitado && discos[i].status == 1) {
                            discoDisponivel = 1;
                            discos[i].status = 0; 
                            salvarDiscosCSV(); 
                            
                            // Copia o código textual do vinil do Felipe para o registro de locação
                            strcpy(novaLocacao.codigoVinil, discos[i].codigo);
                            break;
                        }
                    }

                    if (!discoDisponivel) {
                        printf("\n[ERRO] Disco ID %d nao encontrado ou ja esta alugado!\n", idDiscoDigitado);
                        break;
                    }

                    printf("Tempo de Emprestimo (Dias): ");
                    scanf("%d", &novaLocacao.diasAlugados);
                    
                    printf("Valor Cobrado (R$): ");
                    scanf("%f", &novaLocacao.valorLocacao);

                    novaLocacao.idLocacao = totalLocacoes + 1;
                    historicoLocacoes[totalLocacoes] = novaLocacao;
                    totalLocacoes++;
                    
                    salvarLocacoesCSV(); 
                    printf("\nLocacao salva com sucesso e persistida em arquivo!\n");
                }
                break;

            case 2:
                printf("\n--- Historico Geral de Locacoes ---\n");
                if (totalLocacoes == 0) {
                    printf("Nenhuma locacao em memoria.\n");
                } else {
                    for (i = 0; i < totalLocacoes; i++) {
                        printf("ID: %d | Cliente ID: %d | Vinil: %s | Dias: %d | Valor: R$ %.2f\n",
                               historicoLocacoes[i].idLocacao,
                               historicoLocacoes[i].idClienteLocador,
                               historicoLocacoes[i].codigoVinil,
                               historicoLocacoes[i].diasAlugados,
                               historicoLocacoes[i].valorLocacao);
                    }
                }
                break;

            case 3:
                printf("\n--- Relatorio Analitico: Maiores Tempos de Emprestimo ---\n");
                if (totalLocacoes == 0) {
                    printf("Nao ha dados para ordenar.\n");
                } else {
                    ordenarLocacoesPorDias();
                    for (i = 0; i < totalLocacoes; i++) {
                        printf("[%d Lugar] Vinil: %s | Dias Alugados: %d | Locacao ID: %d\n",
                               i + 1, historicoLocacoes[i].codigoVinil, historicoLocacoes[i].diasAlugados, historicoLocacoes[i].idLocacao);
                    }
                }
                break;

            case 4: {
                float receitaTotal = 0.0;
                printf("\n--- Receita Total ---\n");
                for (i = 0; i < totalLocacoes; i++) {
                    receitaTotal += historicoLocacoes[i].valorLocacao;
                }
                printf("Faturamento Geral de Locacoes: R$ %.2f\n", receitaTotal);
                break;
            }
            case 0:
                printf("\nRetornando ao Menu Principal...\n");
                break;
            default:
                printf("\nOpcao incorreta!\n");
                break;
        }
    } while (opcaoModulo != 0);
}

#endif


