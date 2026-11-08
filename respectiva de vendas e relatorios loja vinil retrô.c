// ============================================================================
// MÓDULO 4: PERSPECTIVA DE VENDAS E RELATÓRIOS (VERSÃO 50%)
// Tema: Loja de Discos de Vinil Retrô
// Autor: Braian matheus hladczuk - RGM: 47463791
// ============================================================================

#include <stdio.h>
#include <string.h>

struct VendaVinil {
    int idVenda;
    int idClienteComprador;
    char codigoAlfanumerico[10]; 
    int quantidadeDiscos;
    float valorTotalVenda;
};

struct VendaVinil historicoVendas[50];
int totalVendas = 0;

void moduloVendasERelatorios() {
    int opcaoModulo;

    do {
        printf("\n--- [MODULO 4: VENDAS E RELATORIOS DE VINIL (Versao 50%%)] ---\n");
        printf("1. Registrar Nova Venda de Vinil (Prototipe)\n");
        printf("2. Listar Todas as Vendas (Prototipe)\n");
        printf("3. Relatorio: Vendas de Maior Valor (Ordenacao Bubble Sort - Nao Iniciado)\n");
        printf("4. Relatorio: Faturamento Total da Loja (Metricas - Nao Iniciado)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoModulo);

        switch (opcaoModulo) {
            case 1:
                printf("\n[PROTOTIPO] Aqui sera feito o cadastro da venda do vinil.\n");
                break;
            case 2:
                printf("\n[PROTOTIPO] Aqui sera feita a listagem simples das vendas de discos.\n");
                break;
            case 3:
                printf("\n[PROTOTIPO] Aqui entrara o algoritmo de ordenacao Bubble Sort por valor.\n");
                break;
            case 4:
                printf("\n[PROTOTIPO] Aqui entrara a soma do faturamento analitico.\n");
                break;
            case 0:
                printf("\nVoltando ao menu principal da loja...\n");
                break;
            default:
                printf("\n[AVISO] Opcao invalida!\n");
                break;
        }
    } while (opcaoModulo != 0);
}
