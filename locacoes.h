// ============================================================================
// MÓDULO: PERSPECTIVA DE LOCAÇÃO E OPERAÇÃO DE VINIS (VERSÃO FINAL 100%)
// Tema: Locadora de Discos de Vinil Retrô
// Autor: Braian Hladczuk - RGM: 04746379-1
// ============================================================================

#ifndef LOCACOES_H
#define LOCACOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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
        printf("\n[ERRO] Não foi possível abrir o arquivo locacoes.csv para escrita.\n");
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
        printf("\n[AVISO] Arquivo locacoes.csv não encontrado. Um novo será criado ao salvar.\n");
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

// Ordena uma cópia do vetor do aluguel mais caro para o mais barato (Bubble Sort)
// Sem alterar a ordem original de inserção em historicoLocacoes[]
void ordenarLocacoesPorValor(struct LocacaoVinil lista[], int qtd) {
    int i, j;
    struct LocacaoVinil aux;

    for (i = 0; i < qtd - 1; i++) {
        for (j = 0; j < qtd - i - 1; j++) {
            if (lista[j].valorLocacao < lista[j + 1].valorLocacao) {
                aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }
}

void menuLocacoes() {
    // Ativa acentuação em português no console sem alterar o ponto decimal dos CSVs
    setlocale(LC_CTYPE, "Portuguese");

    int opcaoModulo;
    int i;
    int idDiscoDigitado;
    struct LocacaoVinil novaLocacao;

    // [Obrigatório] Sincronização dos arquivos CSV ao iniciar o módulo
    lerClientes();
    carregarDiscosCSV();
    carregarLocacoesCSV();

    // Verifica se é a primeira execução (nenhum cliente ou locação carregados dos arquivos .csv)
    if (totalClientes == 0 || totalLocacoes == 0) {
        printf("\n[INFO - PRIMEIRA EXECUÇÃO] Caso apareçam avisos de arquivos .csv não encontrados acima,\n");
        printf("isso ocorre porque o modo \"r\" do fopen retorna NULL enquanto nenhum registro for salvo.\n");
        printf("Assim que o primeiro cliente e a primeira locação forem cadastrados, os arquivos serão criados!\n");
    }

    do {
        printf("\n======================================================\n");
        printf("     SISTEMA RETRÔ (1985) - MÓDULO DE LOCAÇÕES        \n");
        printf("======================================================\n");
        printf("1. Alugar Novo Vinil (Balcão)\n");
        printf("2. Listar Locações (Ordem de Inserção)\n");
        printf("3. Relatório: Aluguéis Mais Caros até Mais Baratos (Bubble Sort)\n");
        printf("4. Relatório: Receita Total de Locações\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("======================================================\n");
        printf("Escolha uma ação: ");
        scanf("%d", &opcaoModulo);
        system("cls"); // Limpa a tela ao trocar de função (mesmo padrão de discos.h)

        switch (opcaoModulo) {
            case 1:
                if (totalLocacoes >= 50) {
                    printf("\n[ERRO] Vetor cheio na memória RAM!\n");
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
                        printf("\n[ERRO] Cliente ID %d não encontrado ou inativo!\n", novaLocacao.idClienteLocador);
                        break;
                    }

                    printf("ID do Disco: ");
                    scanf("%d", &idDiscoDigitado);

                    int discoDisponivel = 0;
                    float precoDiariaDisco = 0.0;

                    for (i = 0; i < totalDiscos; i++) {
                        if (discos[i].id == idDiscoDigitado && discos[i].status == 1) {
                            discoDisponivel = 1;
                            discos[i].status = 0;
                            precoDiariaDisco = discos[i].preco_locacao; // Campo oficial do discos.h
                            salvarDiscosCSV();

                            // [Obrigatório] Cópia segura do título do vinil com limite de caracteres
                            strncpy(novaLocacao.codigoVinil, discos[i].titulo, 19);
                            novaLocacao.codigoVinil[19] = '\0';
                            break;
                        }
                    }

                    if (!discoDisponivel) {
                        printf("\n[ERRO] Disco ID %d não encontrado ou já está alugado!\n", idDiscoDigitado);
                        break;
                    }

                    printf("Tempo de Empréstimo (Dias): ");
                    scanf("%d", &novaLocacao.diasAlugados);

                    // Multiplica a quantidade de dias pelo preco_locacao cadastrado no discos.h
                    novaLocacao.valorLocacao = novaLocacao.diasAlugados * precoDiariaDisco;
                    printf("\nValor da Diária do Disco: R$ %.2f\n", precoDiariaDisco);
                    printf("Valor Total do Aluguel (%d dias x R$ %.2f): R$ %.2f\n",
                           novaLocacao.diasAlugados, precoDiariaDisco, novaLocacao.valorLocacao);

                    novaLocacao.idLocacao = totalLocacoes + 1;
                    historicoLocacoes[totalLocacoes] = novaLocacao;
                    totalLocacoes++;

                    salvarLocacoesCSV();
                    printf("\nLocação salva com sucesso e persistida em arquivo!\n");
                }
                break;

            case 2:
                printf("\n--- Histórico Geral de Locações (Ordem de Inserção) ---\n");
                if (totalLocacoes == 0) {
                    printf("Nenhuma locação em memória.\n");
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

            case 3: {
                printf("\n--- Relatório Analítico: Aluguéis Mais Caros até Mais Baratos ---\n");
                if (totalLocacoes == 0) {
                    printf("Não há dados para ordenar.\n");
                } else {
                    // Cria uma cópia local para ordenar sem bagunçar o vetor original
                    struct LocacaoVinil copiaLocacoes[50];
                    for (i = 0; i < totalLocacoes; i++) {
                        copiaLocacoes[i] = historicoLocacoes[i];
                    }

                    ordenarLocacoesPorValor(copiaLocacoes, totalLocacoes);

                    for (i = 0; i < totalLocacoes; i++) {
                        printf("[%dº Lugar] Vinil: %s | Valor: R$ %.2f | Dias: %d | Locação ID: %d\n",
                               i + 1,
                               copiaLocacoes[i].codigoVinil,
                               copiaLocacoes[i].valorLocacao,
                               copiaLocacoes[i].diasAlugados,
                               copiaLocacoes[i].idLocacao);
                    }
                }
                break;
            }

            case 4: {
                float receitaTotal = 0.0;
                printf("\n--- Receita Total ---\n");
                for (i = 0; i < totalLocacoes; i++) {
                    receitaTotal += historicoLocacoes[i].valorLocacao;
                }
                printf("Faturamento Geral de Locações: R$ %.2f\n", receitaTotal);
                break;
            }

            case 0:
                printf("\nRetornando ao Menu Principal...\n");
                break;

            default:
                printf("\nOpção incorreta!\n");
                break;
        }
    } while (opcaoModulo != 0);
}

#endif
