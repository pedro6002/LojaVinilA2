#include <stdio.h>

#ifndef clientes.h
#define clientes.h

struct Cliente {
    int id;
    char nome_completo[50];
    char email[50];
    int qtd_discos_alugados;
    int status;
};

void listarClientes () {

    FILE *arq = fopen("clientes.csv", "r"); // Comando para iniciar leitura do arquivo .CSV

    if (arq == NULL) {
        printf("Arquivo de usuarios nao encontrado!\n");
        return;
    }
}

#endif
