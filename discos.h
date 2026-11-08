#ifndef
#define

#include <stdio.h>


/* ===============================================================
   MÓDULO DE REMOÇÃO E MATRIZ | INTEGRANTE C | FELIPE MARIANO BUENO
   =============================================================== */

void inicializarMatriz() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrizPrateleiras[i][j] = 0;
        }
    }
}

// 1. LISTAR / VISUALIZAR DISCOS NA MATRIZ
void listarDiscosMatriz() {
    int totalGeralDiscos = 0;

    printf("\n--- GRADE DE MOSTRUARIO DE DISCOS (MATRIZ 4x4) ---\n");
    printf("Linhas = Generos (0: Rock, 1: Jazz, 2: Pop, 3: MPB)\n");
    printf("Colunas = Prateleiras (0 a 3)\n\n");
    printf("           Prat. 0   Prat. 1   Prat. 2   Prat. 3\n");
    
    for (int i = 0; i < 4; i++) {
        printf("Genero %d | ", i);
        for (int j = 0; j < 4; j++) {
            printf("  [%2d]   ", matrizPrateleiras[i][j]);
            totalGeralDiscos += matrizPrateleiras[i][j];
        }
        printf("\n");
    }
    printf("------------------------------------------------------------\n");
    printf(" TOTAL DE DISCOS EM ESTOQUE NA MATRIZ: %d unidades\n", totalGeralDiscos);
    printf("------------------------------------------------------------\n");
}

// 2. CADASTRAR / ADICIONAR DISCOS NA MATRIZ
void cadastrarDiscoMatriz() {
    int g, p, qtdAdicionar;

    printf("\n--- CADASTRAR / ADICIONAR DISCOS NA MATRIZ ---\n");
    printf("Digite o Genero (0: Rock, 1: Jazz, 2: Pop, 3: MPB): ");
    scanf("%d", &g);
    printf("Digite a Prateleira (0 a 3): ");
    scanf("%d", &p);

    if (g >= 0 && g < 4 && p >= 0 && p < 4) {
        printf("Digite a quantidade de discos a ADICIONAR neste nicho: ");
        scanf("%d", &qtdAdicionar);

        if (qtdAdicionar > 0) {
            matrizPrateleiras[g][p] += qtdAdicionar;
            printf("=> Sucesso: %d disco(s) adicionados ao Nicho [%d][%d]. Total atual: %d discos.\n",
                   qtdAdicionar, g, p, matrizPrateleiras[g][p]);
        } else {
            printf("\n[ALERTA] A quantidade a adicionar deve ser maior que zero!\n");
        }
    } else {
        printf("\n[ERRO] Posicao invalida! Digite generos e prateleiras entre 0 e 3.\n");
    }
}

// 3. EDITAR DADOS / QUANTIDADE DE DISCOS NUM NICHO DA MATRIZ
void editarDiscoMatriz() {
    int g, p, novaQtd;

    printf("\n--- EDITAR QUANTIDADE DE DISCOS NUM NICHO ---\n");
    printf("Digite o Genero (0 a 3): ");
    scanf("%d", &g);
    printf("Digite a Prateleira (0 a 3): ");
    scanf("%d", &p);

    if (g >= 0 && g < 4 && p >= 0 && p < 4) {
        printf("Quantidade atual no Nicho [%d][%d]: %d discos.\n", g, p, matrizPrateleiras[g][p]);
        printf("Digite a NOVA quantidade total de discos para este nicho: ");
        scanf("%d", &novaQtd);

        if (novaQtd >= 0) {
            matrizPrateleiras[g][p] = novaQtd;
            printf("=> Sucesso: Nicho [%d][%d] redefinido para %d discos com sucesso!\n", g, p, novaQtd);
        } else {
            printf("\n[ERRO] A quantidade nao pode ser negativa!\n");
        }
    } else {
        printf("\n[ERRO] Posicao invalida! Digite valores entre 0 e 3.\n");
    }
}

// 4. EXCLUIR / ZERAR DISCOS DE UM NICHO DA MATRIZ
void excluirDiscoMatriz() {
    int g, p, opcaoExcluir;

    printf("\n--- EXCLUIR / DAR BAIXA EM DISCOS NA MATRIZ ---\n");
    printf("Digite o Genero (0 a 3): ");
    scanf("%d", &g);
    printf("Digite a Prateleira (0 a 3): ");
    scanf("%d", &p);

    if (g >= 0 && g < 4 && p >= 0 && p < 4) {
        if (matrizPrateleiras[g][p] == 0) {
            printf("\n[ALERTA] Este nicho ja esta vazio (0 discos).\n");
            return;
        }

        printf("Nicho [%d][%d] possui %d disco(s).\n", g, p, matrizPrateleiras[g][p]);
        printf("1 - Zerar todos os discos deste nicho\n");
        printf("2 - Remover apenas uma quantidade especifica\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoExcluir);

        if (opcaoExcluir == 1) {
            matrizPrateleiras[g][p] = 0;
            printf("=> Sucesso: Todos os discos do Nicho [%d][%d] foram removidos/zerados!\n", g, p);
        } else if (opcaoExcluir == 2) {
            int qtdRemover;
            printf("Digite quantos discos deseja remover: ");
            scanf("%d", &qtdRemover);

            if (qtdRemover > 0 && qtdRemover <= matrizPrateleiras[g][p]) {
                matrizPrateleiras[g][p] -= qtdRemover;
                printf("=> Sucesso: %d disco(s) removidos. Restam %d no Nicho [%d][%d].\n",
                       qtdRemover, matrizPrateleiras[g][p], g, p);
            } else {
                printf("\n[ERRO] Quantidade invalida para remocao!\n");
            }
        } else {
            printf("\n[ERRO] Opcao invalida!\n");
        }
    } else {
        printf("\n[ERRO] Posicao invalida! Digite valores entre 0 e 3.\n");
    }
}

// SUBMENU PRINCIPAL DO CONTROLE DE DISCOS DA MATRIZ
void gerenciarMatrizEstoque() {
    int opcaoMatriz;
    do {
        printf("\n============================================================\n");
        printf("     GRADE DE CONTROLE DE DISCOS/PRATELEIRAS (MATRIZ 4x4)   \n");
        printf("============================================================\n");
        printf(" 1 - Listar / Visualizar Grade de Discos (Matriz 4x4)\n");
        printf(" 2 - Cadastrar / Adicionar Discos numa Prateleira\n");
        printf(" 3 - Editar Quantidade de Discos num Nicho\n");
        printf(" 4 - Excluir / Dar Baixa em Discos de um Nicho\n");
        printf(" 0 - Voltar ao Menu de Clientes\n");
        printf("============================================================\n");
        printf(" Escolha uma opcao: ");
        scanf("%d", &opcaoMatriz);

        switch (opcaoMatriz) {
            case 1:
                listarDiscosMatriz();
                break;
            case 2:
                cadastrarDiscoMatriz();
                break;
            case 3:
                editarDiscoMatriz();
                break;
            case 4:
                excluirDiscoMatriz();
                break;
            case 0:
                printf("\nVoltando ao menu de clientes...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }
    } while (opcaoMatriz != 0);
}


#endif
