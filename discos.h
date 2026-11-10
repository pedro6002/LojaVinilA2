#ifndef DISCOS_H
#define DISCOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===============================================================
   1. ESTRUTURA E VARIÁVEIS GLOBAIS DO DOMÍNIO (DISCOS)
   =============================================================== */

struct Disco {
    int id;
    char titulo[50];
    char artista[50];
    float preco_locacao;
    int id_genero;
    int status; // 1 - Disponivel, 0 - Alugado / Inativo
};

struct Disco discos[50];
int totalDiscos = 0;

// Matriz do Integrante C: Grade de Controle do Estoque (4 Generos x 4 Prateleiras)
int matrizPrateleiras[4][4];

/* ===============================================================
   2. DECLARAÇÃO DOS PROTÓTIPOS DAS FUNÇÕES
   =============================================================== */

void carregarDiscosCSV();
void salvarDiscosCSV();
void cadastrarDisco();
void listarDiscos();
void buscarDisco();
void editarDisco();
void excluirDisco();

void inicializarMatriz();
void gerenciarMatrizEstoque();

void opcaoMenuDiscos(int opcao);
void menuDiscos();

/* ===============================================================
   3. PERSISTÊNCIA EM DISCO (ARQUIVO CSV)
   =============================================================== */

void carregarDiscosCSV() {
    totalDiscos = 0; // Zera o contador para evitar duplicar registros na RAM

    FILE *arq = fopen("discos.csv", "r");

    if (arq != NULL) {
        while (totalDiscos < 50 &&
               fscanf(arq, "%d;%49[^;];%49[^;];%f;%d;%d\n",
                      &discos[totalDiscos].id,
                      discos[totalDiscos].titulo,
                      discos[totalDiscos].artista,
                      &discos[totalDiscos].preco_locacao,
                      &discos[totalDiscos].id_genero,
                      &discos[totalDiscos].status) == 6) {
            totalDiscos++;
        }
        fclose(arq);
    }
}

void salvarDiscosCSV() {
    FILE *arq = fopen("discos.csv", "w");

    if (arq != NULL) {
        for (int i = 0; i < totalDiscos; i++) {
            fprintf(arq, "%d;%s;%s;%.2f;%d;%d\n",
                    discos[i].id,
                    discos[i].titulo,
                    discos[i].artista,
                    discos[i].preco_locacao,
                    discos[i].id_genero,
                    discos[i].status);
        }
        fclose(arq);
    } else {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo discos.csv para escrita!\n");
    }
}

/* ===============================================================
   4. OPERAÇÕES CRUD DE DISCOS | INTEGRANTE C (FELIPE MARIANO BUENO)
   =============================================================== */

void cadastrarDisco() {
    carregarDiscosCSV();

    if (totalDiscos >= 50) {
        printf("\n[ALERTA] Capacidade maxima do acervo atingida (50 discos)!\n");
        return;
    }

    struct Disco novo;

    printf("\n--- CADASTRAR NOVO DISCO ---\n");
    printf("Digite o ID do disco: ");
    scanf("%d", &novo.id);

    // Valida se o ID ja existe
    for (int i = 0; i < totalDiscos; i++) {
        if (discos[i].id == novo.id) {
            printf("\n[ERRO] Ja existe um disco cadastrado com o ID %d!\n", novo.id);
            return;
        }
    }

    printf("Digite o Titulo do disco: ");
    scanf(" %49[^\n]", novo.titulo);

    printf("Digite o Artista/Banda: ");
    scanf(" %49[^\n]", novo.artista);

    printf("Digite o Preco de Locacao: ");
    scanf("%f", &novo.preco_locacao);

    printf("Digite o ID do Genero (0: Rock, 1: Jazz, 2: Pop, 3: MPB): ");
    scanf("%d", &novo.id_genero);

    novo.status = 1; // Disponivel por padrao

    discos[totalDiscos] = novo;
    totalDiscos++;

    salvarDiscosCSV();
    printf("\n=> Sucesso: Disco '%s' cadastrado com sucesso!\n", novo.titulo);
}

void listarDiscos() {
    carregarDiscosCSV();

    printf("\n%-5s | %-25s | %-20s | %-12s | %-8s | %-12s\n",
           "ID", "TITULO", "ARTISTA", "PRECO (R$)", "GENERO", "STATUS");
    printf("=============================================================================================\n");

    if (totalDiscos == 0) {
        printf("Nenhum disco cadastrado no arquivo discos.csv.\n");
        return;
    }

    for (int i = 0; i < totalDiscos; i++) {
        printf("%-5d | %-25s | %-20s | R$ %-9.2f | %-8d | %-12s\n",
               discos[i].id,
               discos[i].titulo,
               discos[i].artista,
               discos[i].preco_locacao,
               discos[i].id_genero,
               discos[i].status == 1 ? "Disponivel" : "Indisponivel");
    }
}

void buscarDisco() {
    carregarDiscosCSV();

    int idBusca, idEncontrado = 0, posicaoId = -1;

    printf("\n--- BUSCAR DISCO POR ID ---\n");
    printf("Digite o ID do disco: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < totalDiscos; i++) {
        if (discos[i].id == idBusca) {
            idEncontrado = 1;
            posicaoId = i;
            break;
        }
    }

    printf("\nID buscado: %s\n", idEncontrado == 1 ? "ENCONTRADO" : "NAO ENCONTRADO");

    if (idEncontrado == 1) {
        printf("\n%-5s | %-25s | %-20s | %-12s | %-8s | %-12s\n",
               "ID", "TITULO", "ARTISTA", "PRECO (R$)", "GENERO", "STATUS");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("%-5d | %-25s | %-20s | R$ %-9.2f | %-8d | %-12s\n",
               discos[posicaoId].id,
               discos[posicaoId].titulo,
               discos[posicaoId].artista,
               discos[posicaoId].preco_locacao,
               discos[posicaoId].id_genero,
               discos[posicaoId].status == 1 ? "Disponivel" : "Indisponivel");
    } else {
        printf("O ID digitado nao corresponde a nenhum disco no acervo!\n");
    }
}

void editarDisco() {
    carregarDiscosCSV();

    int idEdicao, idEncontrado = 0, posicaoId = -1;

    printf("\n--- EDITAR DADOS DO DISCO ---\n");
    printf("Digite o ID do disco a ser editado: ");
    scanf("%d", &idEdicao);

    for (int i = 0; i < totalDiscos; i++) {
        if (discos[i].id == idEdicao) {
            idEncontrado = 1;
            posicaoId = i;
            break;
        }
    }

    if (idEncontrado == 1) {
        printf("\nDADOS ATUAIS DO DISCO:\n");
        printf("Titulo: %s | Artista: %s | Preco: R$%.2f | Genero: %d | Status: %s\n",
               discos[posicaoId].titulo,
               discos[posicaoId].artista,
               discos[posicaoId].preco_locacao,
               discos[posicaoId].id_genero,
               discos[posicaoId].status == 1 ? "Disponivel" : "Indisponivel");

        printf("\nDigite o novo titulo do disco: ");
        scanf(" %49[^\n]", discos[posicaoId].titulo);

        printf("Digite o novo artista/banda: ");
        scanf(" %49[^\n]", discos[posicaoId].artista);

        printf("Digite o novo preco de locacao: ");
        scanf("%f", &discos[posicaoId].preco_locacao);

        printf("Digite o novo ID do genero (0 a 3): ");
        scanf("%d", &discos[posicaoId].id_genero);

        printf("Informe o status (1 - Disponivel | 0 - Indisponivel): ");
        scanf("%d", &discos[posicaoId].status);

        salvarDiscosCSV();
        printf("\n=> Sucesso: Dados do disco atualizados no arquivo CSV!\n");
    } else {
        printf("\n[ALERTA] Disco com ID %d nao foi encontrado!\n", idEdicao);
    }
}

void excluirDisco() {
    carregarDiscosCSV();

    int idExcluir, idEncontrado = 0, posicaoId = -1;

    printf("\n--- EXCLUIR / DESATIVAR DISCO ---\n");
    printf("Digite o ID do disco a ser desativado: ");
    scanf("%d", &idExcluir);

    for (int i = 0; i < totalDiscos; i++) {
        if (discos[i].id == idExcluir && discos[i].status == 1) {
            idEncontrado = 1;
            posicaoId = i;
            break;
        }
    }

    if (idEncontrado == 1) {
        // Soft Delete: altera a flag status para 0
        discos[posicaoId].status = 0;

        salvarDiscosCSV();
        printf("\n=> Sucesso: Disco '%s' (ID %d) foi desativado do acervo!\n",
               discos[posicaoId].titulo, idExcluir);
    } else {
        printf("\n[ALERTA] Disco com ID %d nao foi encontrado ou ja esta inativo.\n", idExcluir);
    }
}

/* ===============================================================
   5. GERENCIAMENTO DA MATRIZ (PRATELEIRAS / MOSTRUÁRIO)
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
        printf("     GRADE DE CONTROLE DE PRATELEIRAS (MATRIZ 4x4)          \n");
        printf("============================================================\n");
        printf(" 1 - Visualizar Grade de Prateleiras\n");
        printf(" 2 - Atualizar Quantidade de Discos num Nicho\n");
        printf(" 0 - Voltar ao Menu de Discos\n");
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

/* ===============================================================
   6. MENU DO MÓDULO (PADRÃO VISUAL DO PROJETO)
   =============================================================== */

void opcaoMenuDiscos(int opcao) {
    switch (opcao) {
        case 1:
            cadastrarDisco();
            break;
        case 2:
            buscarDisco();
            break;
        case 3:
            listarDiscos();
            break;
        case 4:
            editarDisco();
            break;
        case 5:
            excluirDisco();
            break;
        case 6:
            gerenciarMatrizEstoque();
            break;
        case 0:
            printf("\nRetornando ao menu principal...\n");
            break;
        default:
            printf("\nOpcao desconhecida. Tente novamente.\n");
            break;
    }
}

void menuDiscos() {
    int opcao;

    do {
        printf("\n");
        printf("============================================================\n");
        printf("                  GERENCIAMENTO DE DISCOS                   \n");
        printf("============================================================\n\n");

        printf(" 1 - Cadastrar novo disco;\n");
        printf(" 2 - Buscar disco por ID;\n");
        printf(" 3 - Listar todos os discos;\n");
        printf(" 4 - Editar dados do disco;\n");
        printf(" 5 - Excluir ou desativar disco;\n");
        printf(" 6 - Grade de Controle de Prateleiras (Matriz 4x4);\n");

        printf("\n 0 - Voltar ao menu principal;\n");

        printf("\n============================================================\n");
        printf(" Escolha uma opcao: ");
        scanf("%d", &opcao);
        system("cls");

        opcaoMenuDiscos(opcao);
    } while (opcao != 0);
}

#endif
