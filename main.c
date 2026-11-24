#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Inclusão dos módulos (headers) que gerenciam cada entidade do sistema
#include "clientes.h"
#include "discos.h"
#include "generos.h"
#include "locacoes.h"

// Direciona o fluxo do programa para o submenu correspondente à opção escolhida
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
            // Opção de saída; não executa nenhuma ação e encerra o loop principal
            break;
        default:
            printf("\nComando não identificado. Tente novamente.");
            break;
    }
}

int main() {
    // Configura a codificação de caracteres para suportar acentuação no terminal
    setlocale(LC_CTYPE, "");

    // Carrega todos os dados previamente salvos nos arquivos para a memória
    lerClientes();
    carregarDiscosCSV();
    carregarGenerosCSV();
    carregarLocacoesCSV();

    int opcao_menu;

    // Loop principal do sistema: mantém o menu ativo até que o usuário digite 0
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
        
        // Limpa a tela do terminal antes de exibir o próximo submenu ou mensagem
        system("cls");

        // Chama a função responsável por abrir o módulo selecionado
        selecionarMenu(opcao_menu);

    } while (opcao_menu != 0);

    // Mensagens de encerramento exibidas ao sair do loop principal
    printf("\nENCERRANDO SISTEMA.");
    printf("\nObrigado por usar nosso programa.");

    return 0;
}
