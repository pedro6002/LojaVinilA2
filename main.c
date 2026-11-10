#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "clientes.h"
#include "discos.h"
#include "generos.h"
#include "locacoes.h"

int main() {
    setlocale(LC_CTYPE, "Portuguese");

    int opcao_menu;

    void selecionarMenu(int opcao) {
        switch (opcao) {
            case 1:
                menuClientes();
                break;
            case 2:
                menuDiscos();
                break;
            case 3:
                menuGeneros();
                break;
            case 4:
                menuLocacoes();
                break;
            case 0:
                break;
            default:
                printf("\nComando não identificado. Tente novamente.");
                break;

        }
    }

    do {
        printf("\n");
        printf("============================================================\n");
        printf("          LOJA DE DISCOS | SISTEMA DE GERENCIAMENTO         \n");
        printf("============================================================\n\n");

        printf(" 1 - Gerenciar usuários;\n");
        printf(" 2 - Gerenciar discos;\n");
        printf(" 3 - Gerenciar gêneros da discografia;\n");
        printf(" 4 - Gerenciar locações;\n");

        printf("\n 0 - Sair do programa;\n");

        printf("\n============================================================\n");
        printf(" Escolha uma opção: ");
        scanf("%d", &opcao_menu);
        system("cls");

        selecionarMenu(opcao_menu);

    } while (opcao_menu != 0);

    printf("\nENCERRANDO SISTEMA.");
    printf("\nObrigado por usar nosso programa.");
}
