#include <stdio.h>

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

    printf("\n\nID buscado: %s", idEncontrado == 1 ? "SIM" : "NAO");

    if (idEncontrado == 1) {
        printf("%-5d | %-25s | %-30s | %-15d | %-10s\n",
               clientes[posicaoId].id,
               clientes[posicaoId].nome_completo,
               clientes[posicaoId].email,
               clientes[posicaoId].qtd_discos_alugados,
               clientes[posicaoId].status == 1 ? "Ativo" : "Inativo");
    } else {
        printf("O ID digitado nao corresponde a nenhum cliente cadastrado!");
    }

    return idBusca, idEncontrado, posicaoId;

}

void editarCliente () {
    lerClientes();

    int idEdicao, idEncontrado ,posicaoId;

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

        printf("\nDigite o novo nome do cliente (Deixe o campo em branco para inalterar): ");
        scanf(" %49[^\n]", clientes[posicaoId].nome_completo);

        printf("\nDigite o novo email do cliente (Deixe o campo em branco para inalterar): ");
        scanf(" %49[^\n]", clientes[posicaoId].email);

        printf("\nDigite a quantidade de discos alugados do cliente (Deixe o campo em branco para inalterar): ");
        scanf(" %d", &clientes[posicaoId].qtd_discos_alugados);

        printf("\nInforme o status de cadastro do cliente (1 para Ativo | 0 para Inativo): ");
        scanf(" %d", &clientes[posicaoId].status);

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

/* ===============================================================
   MENU DO MÓDULO
   =============================================================== */

void opcaoMenuClientes (int opcao) {
    switch (opcao) {
    case 1:
        /* cadastrarCliente();*/
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
        /*excluirCliente();*/
        break;

    case 0:
        /* Volta para o menu principal*/
        break;

    default:
        printf("Opcao desconhecida. Tente novamente.");
        break;
    }
}

int menuClientes() {

    int opcao;

    printf("\n");
    printf("============================================================\n");
    printf("                  GERENCIAMENTO DE CLIENTES                 \n");
    printf("============================================================\n\n");

    printf(" 1 - Cadastrar novo cliente;\n");
    printf(" 2 - Buscar cliente;\n");
    printf(" 3 - Listar todos os clientes;\n");
    printf(" 4 - Editar dados de cliente;\n");
    printf(" 5 - Excluir ou desativar cliente;\n");

    printf("\n 0 - Voltar ao menu principal;\n");

    printf("\n============================================================\n");
    printf(" Escolha uma opcao: ");
    scanf("%d", &opcao);
    system("cls");

    opcaoMenuClientes(opcao);
}

#endif
