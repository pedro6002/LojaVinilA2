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
    int qtd_exemplares;
    int status_emprestimo;
    float diaria;
};

struct Usuario listaUsuarios[50];

void mostrarMenu() {
    printf("\n===================================================================\n");
    printf("*nome da loja* | SISTEMA DE GERENCIAMENTO DE USUÁRIOS E EMPRESTIMOS");
    printf("\n===================================================================\n\n\n");

    printf("1 - Cadastrar novos clientes;\n");
    printf("2 - Consultar dados de cliente;\n");
    printf("3 - Mostrar clientes cadastrados no sistema;\n");
    printf("4 - Editar informações sobre usuários & discos;\n");
    printf("5 - Desativar & excluir usuários;\n");

    printf("\n0 - Sair do programa;");

}

int main() {
    mostrarMenu();
}
