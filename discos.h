
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

void gerenciarMatrizEstoque() {
    int opcaoMatriz;
    do {
        printf("\n============================================================\n");
        printf("     GRADE DE CONTROLE DE DISCOS/PRATELEIRAS (MATRIZ 4x4)   \n");
        printf("============================================================\n");
        printf(" 1 - Visualizar Grade de Prateleiras\n");
        printf(" 2 - Atualizar Quantidade de Discos num Nicho\n");
        printf(" 0 - Voltar ao Menu de Clientes\n");
        printf("============================================================\n");
        printf(" Escolha uma opcao: ");
        scanf("%d", &opcaoMatriz);

        if (opcaoMatriz == 1) {
            printf("\n--- GRADE DE MOSTRUARIO DA LOJA (MATRIZ 4x4) ---\n");
            printf("Linhas = Generos (0: Rock, 1: Jazz, 2: Pop, 3: MPB)\n");
            printf("Colunas = Prateleiras (0 a 3)\n\n");
            printf("           Prat. 0   Prat. 1   Prat. 2   Prat. 3\n");
            for (int i = 0; i < 4; i++) {
                printf("Genero %d | ", i);
                for (int j = 0; j < 4; j++) {
                    printf("  [%2d]   ", matrizPrateleiras[i][j]);
                }
                printf("\n");
            }
        } else if (opcaoMatriz == 2) {
            int g, p, qtd;
            printf("\nDigite o Genero (0 a 3): ");
            scanf("%d", &g);
            printf("Digite a Prateleira (0 a 3): ");
            scanf("%d", &p);

            if (g >= 0 && g < 4 && p >= 0 && p < 4) {
                printf("Digite a quantidade de discos neste nicho: ");
                scanf("%d", &qtd);
                matrizPrateleiras[g][p] = qtd;
                printf("=> Sucesso: Nicho [%d][%d] atualizado para %d discos!\n", g, p, qtd);
            } else {
                printf("\n[ERRO] Posicao invalida! Digite valores entre 0 e 3.\n");
            }
        }
    } while (opcaoMatriz != 0);
}
