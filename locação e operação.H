// ============================================================================
// MÓDULO: PERSPECTIVA DE LOCAÇÃO E OPERAÇÃO DE VINIS (VERSÃO FINAL 100%)
// Tema: Locadora de Discos de Vinil Retrô
// Autor: Braian hladczuk - RGM: 04746379-1
// ============================================================================

#include <stdio.h>
#include <string.h>

struct LocacaoVinil {
    int idLocacao;
    int idClienteLocador;
    char codigoVinil[20];
    int diasAlugados;
    float valorLocacao;
};

struct LocacaoVinil historicoLocacoes[50];
int totalLocacoes = 0;

struct Cliente { int id; char nome[50]; }; struct Cliente listaClientes[50];
struct VinilCatalogo { int id; char titulo[50]; }; struct VinilCatalogo estoqueVinis[50];
struct Fornecedor { int id; char empresa[50]; }; struct Fornecedor listaFornecedores[50];

void exibirCabecalho() {
    printf("\n======================================================\n");
    printf("     VINYL PALACE - SISTEMA DE GESTAO RETRO (1985)    \n");
    printf("======================================================\n");
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

void moduloLocacaoEOperacoes() {
    int opcaoModulo;
    int i;
    struct LocacaoVinil novaLocacao;

    do {
        printf("\n--- [MODULO 4: LOCACAO E OPERACOES (Sua Perspectiva)] ---\n");
        printf("1. Alugar Novo Vinil (Balcao)\n");
        printf("2. Listar Locacoes (Ordem de Insercao)\n");
        printf("3. Relatorio: Alugueis Mais Longos (Ordenado por Bubble Sort)\n");
        printf("4. Relatorio: Receita Total de Locacoes\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoModulo);

        switch (opcaoModulo) {
            case 1:
                if (totalLocacoes >= 50) {
                    printf("\n[ERRO] Vetor cheio na memoria RAM!\n");
                } else {
                    printf("\n--- Registrar Novo Aluguel ---\n");
                    novaLocacao.idLocacao = totalLocacoes + 1;
                    
                    printf("ID do Cliente: ");
                    scanf("%d", &novaLocacao.idClienteLocador);
                    
                    printf("Codigo do Vinil (Sem espacos): ");
                    scanf("%s", novaLocacao.codigoVinil);
                    
                    printf("Tempo de Emprestimo (Dias): ");
                    scanf("%d", &novaLocacao.diasAlugados);
                    
                    printf("Valor Cobrado (R$): ");
                    scanf("%f", &novaLocacao.valorLocacao);

                    historicoLocacoes[totalLocacoes] = novaLocacao;
                    totalLocacoes++;
                    printf("\nLocacao salva com sucesso na RAM!\n");
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

void moduloClientes() { printf("\n[MENU] Entrou no modulo do Integrante A (Gestao de Clientes).\n"); }
void moduloCatalogo() { printf("\n[MENU] Entrou no modulo do Integrante B (Catalogo de Vinis).\n"); }
void moduloFornecedores() { printf("\n[MENU] Entrou no modulo do Integrante C (Estoque e Insumos).\n"); }

int main() {
    int opcaoMenuPrincipal;

    do {
        exibirCabecalho();
        printf("1. Gerenciar Clientes (Integrante A)\n");
        printf("2. Catalogo de Discos (Integrante B)\n");
        printf("3. Estoque e Fornecedores (Integrante C)\n");
        printf("4. Locacao e Relatorios Analiticos (Sua Perspectiva - Integrante D)\n");
        printf("0. Encerrar o Sistema\n");
        printf("Escolha o modulo que deseja acessar: ");
        scanf("%d", &opcaoMenuPrincipal);

        switch (opcaoMenuPrincipal) {
            case 1:
                moduloClientes();
                break;
            case 2:
                moduloCatalogo();
                break;
            case 3:
                moduloFornecedores();
                break;
            case 4:
                moduloLocacaoEOperacoes();
                break;
            case 0:
                printf("\n======================================================\n");
                printf("   Sistema Encerrado. Obrigado por utilizar o Vinyl Palace! \n");
                printf("======================================================\n");
                break;
            default:
                printf("\n[AVISO] Opcao invalida no Menu Principal! Tente novamente.\n");
                break;
        }
    } while (opcaoMenuPrincipal != 0);

    return 0;
}