#include <stdio.h>
#include <stdlib.h>

// ----------------------------------------------------------------------------
// PERSPECTIVA: GESTAO DE CLIENTES
// Autor: Pedro Henrique do Nascimento (Integrante A)
// RGM: 47924624
// ----------------------------------------------------------------------------
struct Cliente {
    int idCliente;
    char nome[100];
    char telefone[20];
    char endereco[80];
    float multa;
    int quantidade_discos;
    char nome_discos[300];
    int ativo;
};

struct Cliente listaClientes[50];
int totalClientes = 0;

void cadastrarUsuario() {
    if (totalClientes >= 50) {
        printf("Erro! O limite de usuarios foi atingido!\n");
    } else {
        printf("Digite o nome completo do usuario: ");
        scanf("%s", listaClientes[totalClientes].nome);

        printf("Digite o telefone do usuario: ");
        scanf("%s", listaClientes[totalClientes].telefone);

        printf("Digite o endereco do usuario: ");
        scanf("%s", listaClientes[totalClientes].endereco);

        // Atribui um ID sequencial e marca como ativo
        listaClientes[totalClientes].idCliente = totalClientes + 1;
        listaClientes[totalClientes].ativo = 1;

        totalClientes+=1;
        printf("Usuario cadastrado com sucesso! ID gerado: %d\n", totalClientes);
    }
}

void consultarUsuario() {
    int idBusca;
    
    printf("Digite o id do cliente que deseja identificar: ");
    scanf("%d", &idBusca);

    int encontrado = 0;
    for (int i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente == idBusca && listaClientes[i].ativo == 1) {
            printf("\n--- Dados do Usuario ---\n");
            printf("ID: %d\n", listaClientes[i].idCliente);
            printf("Nome: %s\n", listaClientes[i].nome);
            printf("Telefone: %s\n", listaClientes[i].telefone);
            printf("Endereco: %s\n", listaClientes[i].endereco);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente com ID %d nao encontrado!\n", idBusca);
    }
}

void listarUsuarios() {
    printf("\nListando clientes...\n");
    if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado no momento.\n");
        return;
    }

    for (int i = 0; i < totalClientes; i++) {
        if (listaClientes[i].ativo == 1) {
            printf("ID: %d | Nome: %s | Tel: %s | Endereco: %s\n", 
                   listaClientes[i].idCliente, 
                   listaClientes[i].nome, 
                   listaClientes[i].telefone,
				   listaClientes[i].endereco);
        }
    }
}

void editarUsuario() {
    printf("\n[Em construcao] editando dados do usuario...\n");
}

void excluirUsuario() {
    printf("\n[Em construcao] excluindo de usuario...\n");
}


void menu_usuarios(){
	int opcaoCliente;
	do {
		printf("\n--- [MODULO 1: GESTAO DE CLIENTES (Integrante A)] ---\n");
		printf("1. Cadastrar novo cliente\n");
		printf("2. Consultar cliente especifico\n");
		printf("3. Listar todos os clientes\n");
		printf("4. Editar dados de cliente\n");
		printf("5. Remover cliente\n");
		printf("0. Voltar ao menu principal\n");
		printf("Escolha uma acao: ");
		scanf("%d", &opcaoCliente);
	switch (opcaoCliente) {
		case 1:
			printf("\n[Em construcao] Cadastro de cliente\n");
			printf("Campos previstos: nome, telefone e endereco.\n");
			break;
		case 2:
			printf("\n[Em construcao] Busca de cliente especifico por ID\n");
			break;
		case 3:
			printf("\n[Em construcao] Listagem de todos os clientes\n");
			break;
		case 4:
			printf("\n[Em construcao] Edicao de dados de cliente\n");
		case 5:
			printf("\n[Em construcao] Remocao de cliente\n");
			break;
		case 0:
			printf("\nRetornando ao menu principal...\n");
			break;
		default:
			printf("\n[ERRO] Opcao invalida no modulo de clientes!\n");
		};
	} while(opcaoCliente != 0);
}

int main(int argc, char *argv[]) {
   		
		menu_usuarios();
    return 0;
}