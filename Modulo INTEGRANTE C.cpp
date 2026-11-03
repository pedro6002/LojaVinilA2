#include <stdio.h>
#include <string.h>

// ============================================================================
// PARTE 1: MODELAGEM DE DADOS (ESCOPO GLOBAL - INTEGRANTE C)
// ============================================================================

// Struct do Vinil (Mínimo de 4 campos heterogêneos)
struct Vinil {
    int idVinil;
    char titulo[50];
    char artista[50];
    float preco;
    int anoLancamento;
    int ativo; // 1 = Ativo no catalogo, 0 = Removido/Inativo (Soft Delete)
};

// Vetor global de discos
struct Vinil catalogoVinil[50];
int totalVinil = 0;

// MATRIZ: Grade de Controle do Mostruario da Loja (4 Generos x 4 Prateleiras)
// Representa a quantidade de discos fisicos organizados nos nichos da loja
int matrizPrateleiras[4][4];

// ============================================================================
// PARTE 2: FUNÇÃO DO MÓDULO DO INTEGRANTE C
// Autor: [Felipe Bueno - 48313661]
// ============================================================================

// Funcao auxiliar para zerar a matriz ao iniciar
void inicializarMatriz() {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            matrizPrateleiras[i][j] = 0;
        }
    }
}

// MÓDULO INTEGRANTE C: REMOÇÃO E MATRIZ
void moduloRemocaoEMatriz() {
    int opcao;
    int idRemover;
    int genero, prateleira, quantidade;
    int i, j;
    int encontrado;

    do {
        printf("\n======================================================\n");
        printf("--- [MODULO C: REMOCAO E MATRIZ (LOJA DE VINIL)] ---\n");
        printf("======================================================\n");
        printf("1. Remover / Dar Baixa em um Vinil (Por ID)\n");
        printf("2. Exibir Grade de Prateleiras (Matriz 4x4)\n");
        printf("3. Atualizar Estoque em um Nicho da Matriz\n");
        printf("4. Zerar Toda a Grade de Prateleiras\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n--- REMOCAO / BAIXA DE VINIL ---\n");
                printf("Digite o ID do vinil que deseja remover: ");
                scanf("%d", &idRemover);

                encontrado = 0;
                // Busca o vinil pelo ID no vetor global
                for (i = 0; i < totalVinil; i++) {
                    if (catalogoVinil[i].idVinil == idRemover && catalogoVinil[i].ativo == 1) {
                        // Soft Delete: altera a flag 'ativo' para 0 sem apagar a memoria
                        catalogoVinil[i].ativo = 0;
                        printf("=> Sucesso: Vinil '%s' (ID %d) foi removido do catalogo!\n", 
                               catalogoVinil[i].titulo, idRemover);
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("\n[ALERTA] Vinil com ID %d nao foi encontrado ou ja esta inativo.\n", idRemover);
                }
                break;

            case 2:
                printf("\n--- GRADE DE MOSTRUARIO DA LOJA (MATRIZ 4x4) ---\n");
                printf("Linhas = Generos (0: Rock, 1: Jazz, 2: Pop, 3: MPB)\n");
                printf("Colunas = Prateleiras (0 a 3)\n\n");

                printf("           Prat. 0   Prat. 1   Prat. 2   Prat. 3\n");
                for (i = 0; i < 4; i++) {
                    printf("Genero %d | ", i);
                    for (j = 0; j < 4; j++) {
                        printf("  [%2d]   ", matrizPrateleiras[i][j]);
                    }
                    printf("\n");
                }
                break;

            case 3:
                printf("\n--- ATUALIZAR MOSTRUARIO NA MATRIZ ---\n");
                printf("Digite o Genero (0: Rock, 1: Jazz, 2: Pop, 3: MPB): ");
                scanf("%d", &genero);
                printf("Digite a Prateleira (0 a 3): ");
                scanf("%d", &prateleira);

                // Validacao de limites da matriz
                if (genero >= 0 && genero < 4 && prateleira >= 0 && prateleira < 4) {
                    printf("Digite a quantidade de discos fisicos neste local: ");
                    scanf("%d", &quantidade);
                    
                    matrizPrateleiras[genero][prateleira] = quantidade;
                    printf("=> Sucesso: Prateleira [%d][%d] atualizada para %d discos!\n", 
                           genero, prateleira, quantidade);
                } else {
                    printf("\n[ERRO] Posicao invalida! Escolha valores entre 0 e 3.\n");
                }
                break;

            case 4:
                printf("\n--- ZERAR GRADE DE PRATELEIRAS ---\n");
                inicializarMatriz();
                printf("=> Todos os nichos da matriz foram zerados com sucesso.\n");
                break;

            case 0:
                printf("\nRetornando ao Menu Principal...\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Digite um numero entre 0 e 4.\n");
        }
    } while (opcao != 0);
}

// ============================================================================
// PARTE 3: ESTRUTURA BASE DO MAIN (PARA TESTAR O SEU CÓDIGO)
// ============================================================================
int main() {
    int opcaoPrincipal;

    // Garante que a matriz comece zerada
    inicializarMatriz();

    // Dados de teste ficticios para validar a remocao
    catalogoVinil[0].idVinil = 101;
    strcpy(catalogoVinil[0].titulo, "Abbey Road");
    strcpy(catalogoVinil[0].artista, "The Beatles");
    catalogoVinil[0].preco = 180.00;
    catalogoVinil[0].anoLancamento = 1969;
    catalogoVinil[0].ativo = 1;
    totalVinil = 1;

    do {
        printf("\n======================================================\n");
        printf("    VINYL RETRO STORE - SISTEMA DE GESTAO (1980)      \n");
        printf("======================================================\n");
        printf("1. Modulo de Cadastro (Integrante A)\n");
        printf("2. Modulo de Busca e Edicao (Integrante B)\n");
        printf("3. Modulo de Remocao e Matriz (SEU MÓDULO - Integrante C)\n");
        printf("4. Modulo de Relatorios (Integrante D)\n");
        printf("0. Encerrar Sistema\n");
        printf("------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcaoPrincipal);

        switch (opcaoPrincipal) {
            case 1:
                printf("\n[Modulo do Integrante A chamado]\n");
                break;
            case 2:
                printf("\n[Modulo do Integrante B chamado]\n");
                break;
            case 3:
                moduloRemocaoEMatriz(); // Chama o seu modulo
                break;
            case 4:
                printf("\n[Modulo do Integrante D chamado]\n");
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\n[ALERTA] Opcao invalida!\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}