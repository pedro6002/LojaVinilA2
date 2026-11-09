#include <stdio.h>
#include <locale.h>

#ifndef clientes_h
#define clientes_h

struct Cliente {
    int id;
    char nome_completo[50];
    char email[50];
    int qtd_discos_alugados;
    int status;
};

struct Cliente clientes[50];
int totalClientes = 0;

/* ===============================================================
   MÓDULO DE LEITURA, LISTAGEM E BUSCA | JOÃO VICTOR ALVES PADILHA
   =============================================================== */

void lerClientes () {
    totalClientes = 0;

    FILE *arq = fopen("clientes.csv", "r"); // Comando para iniciar leitura do arquivo .CSV

    if (arq != NULL) {
        while (totalClientes < 50 &&
               (fscanf(arq, "%d;%49[^;];%49[^;];%d;%d",
                   &clientes[totalClientes].id,
                   clientes[totalClientes].nome_completo,
                   clientes[totalClientes].email,
                   &clientes[totalClientes].qtd_discos_alugados,
                   &clientes[totalClientes].status)) == 5) {
                       totalClientes++;
                   }

        fclose(arq);
    }

    else {
        printf("Arquivo de usuarios nao encontrado!\n");
        return;
    }
}

void cadastrarCliente() {
    lerClientes();

    int idExistente = 0;

    printf("Digite o ID a ser cadastrado: ");
    scanf("%d", &clientes[totalClientes].id);

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[totalClientes].id == clientes[i].id) {
            printf("O ID digitado já está em uso por outro cliente! Tente novamente.");
            idExistente = 1;
            break;
        }
    }

    if (idExistente == 1) {
        return;
    }

    printf("Digite o NOME COMPLETO do cliente a ser cadastrado: ");
    scanf(" %49[^\n]", clientes[totalClientes].nome_completo);

    printf("Digite o EMAIL do cliente a ser cadastrado: ");
    scanf(" %49[^\n]", clientes[totalClientes].email);

    clientes[totalClientes].qtd_discos_alugados = 0; // Definição padrão para conta recém criada.
    clientes[totalClientes].status = 1; // Definição padrão para conta recém criada.

    totalClientes++;

    FILE *arq = fopen("clientes.csv", "w");
    for (int i = 0; i < totalClientes; i++) {
        fprintf(arq, "%d;%s;%s;%d;%d\n",
           clientes[i].id,
           clientes[i].nome_completo,
           clientes[i].email,
           clientes[i].qtd_discos_alugados,
           clientes[i].status);
    }
    fclose(arq);

    printf("\nCliente cadastrado com sucesso!\n");
}

void buscarCliente() {
    lerClientes();

    int idBusca, idEncontrado, posicaoId;

    idEncontrado = 0;

    printf("Digite o ID do cliente: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].id == idBusca) {
            idEncontrado = 1;
            posicaoId = i;
            break;
        }
    }

    if (idEncontrado == 1) {
        printf("%-5d | %-25s | %-30s | %-15d | %-10s\n",
               clientes[posicaoId].id,
               clientes[posicaoId].nome_completo,
               clientes[posicaoId].email,
               clientes[posicaoId].qtd_discos_alugados,
               clientes[posicaoId].status == 1 ? "Ativo" : "Inativo");
    } else {
        printf("O ID digitado não corresponde a nenhum cliente cadastrado!");
    }

    return;
}

void listarClientes() {
    lerClientes();

    printf("%-5s | %-25s | %-30s | %-15s | %-10s\n",
           "ID",
           "NOME COMPLETO",
           "E-MAIL",
           "DISCOS ALUGADOS",
           "STATUS");
    printf("=================================================================================================\n");
    for (int i = 0; i < totalClientes; i++) {
                printf("%-5d | %-25s | %-30s | %-15d | %-10s\n",
                       clientes[i].id,
                       clientes[i].nome_completo,
                       clientes[i].email,
                       clientes[i].qtd_discos_alugados,
                       clientes[i].status == 1 ? "Ativo" : "Inativo");
            }
}

void editarCliente () {
    lerClientes();

    int idEdicao, idEncontrado ,posicaoId, opcaoAlterar;

    idEncontrado = 0;

    printf("Digite o ID ser editado: ");
    scanf("%d", &idEdicao);

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].id == idEdicao) {
            idEncontrado = 1;
            posicaoId = i;
            break;
        }
    }



    if (idEncontrado == 1) {
        printf("DADOS ATUAIS DO CLIENTE\n");
        printf("%-5d | %-25s | %-30s | %-15d | %-10s\n",
               clientes[posicaoId].id,
               clientes[posicaoId].nome_completo,
               clientes[posicaoId].email,
               clientes[posicaoId].qtd_discos_alugados,
               clientes[posicaoId].status == 1 ? "Ativo" : "Inativo");

        printf("\nDeseja alterar o NOME do cliente? (1 - Sim | 0 - Nao): ");
        scanf("%d", &opcaoAlterar);

            if (opcaoAlterar == 1) {
                printf("\nDigite o novo nome do cliente: ");
                scanf(" %49[^\n]", clientes[posicaoId].nome_completo);
            }

        printf("\nDeseja alterar o E-MAIL do cliente? (1 - Sim | 0 - Nao): ");
        scanf("%d", &opcaoAlterar);

            if (opcaoAlterar == 1) {
                printf("\nDigite o novo e-mail do cliente: ");
                scanf(" %49[^\n]", clientes[posicaoId].email);
            }

        printf("\nDeseja alterar a QUANTIDADE DE DISCOS ALUGADOS do cliente? (1 - Sim | 0 - Nao): ");
        scanf("%d", &opcaoAlterar);

            if (opcaoAlterar == 1) {
                printf("\nDigite a quantidade de discos alugados do cliente: ");
                scanf("%d", &clientes[posicaoId].qtd_discos_alugados);
            }


        printf("\nDeseja alterar a STATUS do cliente? (1 - Sim | 0 - Nao): ");
        scanf("%d", &opcaoAlterar);

            if (opcaoAlterar == 1) {
                printf("\nDigite o status do cliente (1 para Ativo | 0 para Inativo): ");
                scanf("%d", &clientes[posicaoId].status);
            }

        FILE *arq = fopen("clientes.csv", "w");

        for (int i = 0; i < totalClientes; i++) {
            fprintf(arq, "%d;%s;%s;%d;%d\n",
               clientes[i].id,
               clientes[i].nome_completo,
               clientes[i].email,
               clientes[i].qtd_discos_alugados,
               clientes[i].status);
        }

        fclose(arq);

    }
}

void excluirCliente() {
    lerClientes();

    int idExclusao, posicaoId;
    char confirmar;

    posicaoId = -1;

    printf("MOSTRANDO USUÁRIOS INATIVOS\n");
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].status == 0) {
            printf("%-5d | %-25s | %-30s | %-15d | %-10s\n",
                   clientes[i].id,
                   clientes[i].nome_completo,
                   clientes[i].email,
                   clientes[i].qtd_discos_alugados,
                   clientes[i].status == 1 ? "Ativo" : "Inativo");
        }
    }

    printf("Digite o ID do usuario a ser excluido (Digite um numero negativo para cancelar): ");
    scanf("%d", &idExclusao);

    if (idExclusao < 0) {
        printf("Voltando ao menu principal.");
        return;
    }

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].id == idExclusao) {
            posicaoId = i;
            break;
        }
    }
    if (posicaoId != -1) {
        printf("%-5d | %-25s | %-30s | %-15d | %-10s\n",
               clientes[posicaoId].id,
               clientes[posicaoId].nome_completo,
               clientes[posicaoId].email,
               clientes[posicaoId].qtd_discos_alugados,
               clientes[posicaoId].status == 1 ? "Ativo" : "Inativo");
    }

        do {
            printf("\n\nVoce deseja excluir o cliente acima? (s / n)");
            scanf(" %c", &confirmar);

            if (confirmar == 's') {

                for (int j = posicaoId; j < totalClientes - 1; j++) {
                    clientes[j] = clientes[j + 1];
                }

                totalClientes--;

                FILE *arq = fopen("clientes.csv", "w");
                for (int i = 0; i < totalClientes; i++) {
                    fprintf(arq, "%d;%s;%s;%d;%d\n",
                       clientes[i].id,
                       clientes[i].nome_completo,
                       clientes[i].email,
                       clientes[i].qtd_discos_alugados,
                       clientes[i].status);
                }
                fclose(arq);

                printf("O cliente foi excluido com sucesso.");
                return;
            }

            else if (confirmar == 'n') {
                printf("Operacao de exclusao abortada.");
                return;
            }

            else {
                printf("Comando nao reconhecido. Tente novamente.");
            }

        } while (confirmar != 's' && confirmar != 'n');

}

/* ===============================================================
   MENU DO MÓDULO
   =============================================================== */

void opcaoMenuClientes (int opcao) {
    switch (opcao) {
    case 1:
        cadastrarCliente();
        break;

    case 2:
        buscarCliente();
        break;

    case 3:
        listarClientes();
        break;

    case 4:
        editarCliente();
        break;

    case 5:
        excluirCliente();
        break;

    case 0:
        /* Volta para o menu principal*/
        break;

    default:
        printf("Opção desconhecida. Tente novamente.");
        break;
    }
}

void menuClientes() {

    int opcao;

    do {
        printf("\n");
        printf("============================================================\n");
        printf("                  GERENCIAMENTO DE CLIENTES                 \n");
        printf("============================================================\n\n");

        printf(" 1 - Cadastrar novo cliente;\n");
        printf(" 2 - Buscar cliente;\n");
        printf(" 3 - Listar todos os clientes;\n");
        printf(" 4 - Editar dados de cliente;\n");
        printf(" 5 - Excluir cliente;\n");

        printf("\n 0 - Voltar ao menu principal;\n");

        printf("\n============================================================\n");
        printf(" Escolha uma opcao: ");
        scanf("%d", &opcao);
        system("cls");

        opcaoMenuClientes(opcao);

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
            system("cls");
        }

    } while (opcao != 0);

    return;
}

#endif
