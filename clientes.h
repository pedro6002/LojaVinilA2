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
    printf("ID | NOME COMPLETO | E-MAIL | DISCOS ALUGADOS | STATUS\n");
    for (int i = 0; i < totalClientes; i++) {
                printf("%d | %s | %s | %d | %d\n",
                       clientes[i].id,
                       clientes[i].nome_completo,
                       clientes[i].email,
                       clientes[i].qtd_discos_alugados,
                       clientes[i].status
                       );
            }
}

void buscarCliente() {
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
        printf("%d | %s | %s | %d | %d\n",
               clientes[posicaoId].id,
               clientes[posicaoId].nome_completo,
               clientes[posicaoId].email,
               clientes[posicaoId].qtd_discos_alugados,
               clientes[posicaoId].status
               );
    } else {
        printf("O ID digitado nao corresponde a nenhum cliente cadastrado!");
    }

}
#endif
