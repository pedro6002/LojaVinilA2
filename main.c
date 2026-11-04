#include <stdio.h>
#include <stdlib.h>

struct Usuario {
    int id;
    char nome_completo[50];
    char email[100];
    int qtd_discos_emprestados;
    int status_cadastro;
};

struct Disco {
    int id;
    char nome_disco[50];
    char album[50];
    char autor[50];
    char estudio[50];

    int status_emprestimo;
    int id_usuario_responsavel;
    float diaria;
};

struct Usuario listaUsuarios[50];

/* =========================================================
    CÓDIFICAÇÃO DOS MENUS EM TERMINAL
   ========================================================= */

int menu_principal() {
    int opcao;

    printf("\n");
    printf("============================================================\n");
    printf("          LOJA DE DISCOS | SISTEMA DE GERENCIAMENTO         \n");
    printf("============================================================\n\n");

    printf(" 1 - Gerenciar usuarios;\n");
    printf(" 2 - Gerenciar discos;\n");

    printf("\n 0 - Sair do programa;\n");

    printf("\n============================================================\n");
    printf(" Escolha uma opcao: ");
    scanf("%d", &opcao);

    return opcao;
}

int menu_usuarios() {
    int opcao;

    printf("\n");
    printf("============================================================\n");
    printf("                  GERENCIAMENTO DE USUARIOS                 \n");
    printf("============================================================\n\n");

    printf(" 1 - Cadastrar novo usuario;\n");
    printf(" 2 - Consultar usuario;\n");
    printf(" 3 - Listar todos os usuarios;\n");
    printf(" 4 - Editar dados de usuario;\n");
    printf(" 5 - Excluir usuario;\n");

    printf("\n 0 - Voltar ao menu principal;\n");

    printf("\n============================================================\n");
    printf(" Escolha uma opcao: ");
    scanf("%d", &opcao);

    return opcao;
}

int menu_discos() {
    int opcao;

    printf("\n");
    printf("============================================================\n");
    printf("                   GERENCIAMENTO DE DISCOS                  \n");
    printf("============================================================\n\n");

    printf(" 1 - Cadastrar novo disco;\n");
    printf(" 2 - Consultar disco;\n");
    printf(" 3 - Listar todos os discos;\n");
    printf(" 4 - Editar dados de disco;\n");
    printf(" 5 - Excluir disco;\n");

    printf("\n 0 - Voltar ao menu principal;\n");

    printf("\n============================================================\n");
    printf(" Escolha uma opcao: ");
    scanf("%d", &opcao);

    return opcao;
}



void sub_menu_usuarios(int opcao) {
    switch (opcao) {

        case 1:
            printf("\n[CADASTRO DE USUARIO]\n");
            // cadastrarUsuario();
            break;

        case 2:
            printf("\n[CONSULTA DE USUARIO]\n");
            // consultarUsuario();
            break;

        case 3:
            printf("\n[LISTAGEM DE USUARIOS]\n");
            // listarUsuarios();
            break;

        case 4:
            printf("\n[EDICAO DE USUARIO]\n");
            // editarUsuario();
            break;

        case 5:
            printf("\n[EXCLUSAO DE USUARIO]\n");
            // excluirUsuario();
            break;

        case 0:
            printf("\nVoltando ao menu principal.\n");
            break;

        default:
            printf("\nOpcao invalida. Tente novamente!\n");
            break;
    }
}


void sub_menu_discos(int opcao) {

    switch (opcao) {

        case 1:
            printf("\n[CADASTRO DE DISCO]\n");
            // cadastrarDisco();
            break;

        case 2:
            printf("\n[CONSULTA DE DISCO]\n");
            // consultarDisco();
            break;

        case 3:
            printf("\n[LISTAGEM DE DISCOS]\n");
            // listarDiscos();
            break;

        case 4:
            printf("\n[EDICAO DE DISCO]\n");
            // editarDisco();
            break;

        case 5:
            printf("\n[EXCLUSAO DE DISCO]\n");
            // excluirDisco();
            break;

        case 0:
            printf("\nVoltando ao menu principal.\n");
            break;

        default:
            printf("\nOpcao invalida. Tente novamente!\n");
            break;
    }
}

int main() {
    int opcao_principal;
    int opcao_submenu;

    do {

        opcao_principal = menu_principal();

        switch (opcao_principal) {

            case 1:
                do {
                    opcao_submenu = menu_usuarios();

                    sub_menu_usuarios(opcao_submenu);

                } while (opcao_submenu != 0);
                
                break;

            case 2:
                do {
                    opcao_submenu = menu_discos();
                    
                    sub_menu_discos(opcao_submenu);

                } while (opcao_submenu != 0);

                break;

            case 0:
                printf("\nEncerrando. Obrigado por utilizar nosso sistema\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente!\n");
                break;
        }

    } while (opcao_principal != 0);

    return 0;
}
