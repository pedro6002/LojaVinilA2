// ============================================================================
// MÓDULO: PERSPECTIVA DE DISCOS E PRATELEIRA DE VINIS
// Tema: Locadora de Discos de Vinil Retrô
// Autor: Felipe Mariano Bueno - RGM: 04831366-1
// ============================================================================

#ifndef DISCOS_H
#define DISCOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/* ===============================================================
   1. ESTRUTURA E VARIÁVEIS GLOBAIS (ACESSO PÚBLICO PARA LOCAÇÕES)
   =============================================================== */

struct Disco {
    int id;               // Identificador único (Chave Primária)
    char titulo[50];      // Título do álbum
    char artista[50];     // Nome do artista ou banda
    float preco_locacao;  // Valor da diária de locação
    int id_genero;        // 0: Rock, 1: Jazz, 2: Pop, 3: MPB
    int status;           // 1 = Disponível, 0 = Alugado / Inativo
};

// Vetor estático e contador global compartilhados com o Módulo de Locações
struct Disco discos[50];
int totalDiscos = 0;

// Grade física do mostruário (4 Gêneros nas linhas x 4 Prateleiras nas colunas)
int matrizPrateleiras[4][4];

/* ===============================================================
   2. DECLARAÇÃO DOS PROTÓTIPOS DAS FUNÇÕES
   =============================================================== */

// Persistência em arquivo
void carregarDiscosCSV();
void salvarDiscosCSV();

// Operações CRUD
void cadastrarDisco();
void listarDiscos();
void buscarDisco();
void editarDisco();
void excluirDisco();

// Controle de estoque físico (Matriz)
void inicializarMatriz();
void gerenciarMatrizEstoque();

// Interface e navegação do módulo
void opcaoMenuDiscos(int opcao);
void menuDiscos();

/* ===============================================================
   3. PERSISTÊNCIA EM DISCO (ARQUIVO CSV)
   =============================================================== */

void carregarDiscosCSV() {
    totalDiscos = 0; // Reinicia o contador para evitar duplicação de registros na RAM

    FILE *arq = fopen("discos.csv", "r");

    if (arq != NULL) {
        // Lê até o limite do vetor (50) e exige o preenchimento exato dos 6 campos (== 6)
        // As máscaras %49[^;] previnem Buffer Overflow e respeitam o delimitador ';'
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
        fclose(arq); // Libera o descritor do arquivo no Sistema Operacional
    }
}

void salvarDiscosCSV() {
    // Modo "w" sobrescreve o arquivo com o retrato atualizado da memória RAM
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
        fclose(arq); // Garante o descarregamento (flush) do buffer no disco físico
    } else {
        printf("\n[ERRO] Não foi possível abrir o arquivo discos.csv para escrita!\n");
    }
}

/* ===============================================================
   4. OPERAÇÕES CRUD DE DISCOS | INTEGRANTE C (FELIPE MARIANO BUENO)
   =============================================================== */

void cadastrarDisco() {
    carregarDiscosCSV(); // Sincroniza a RAM com o arquivo antes de inserir

    // Cláusula de guarda (Fail-Fast): impede estouro do vetor estático discos[50]
    if (totalDiscos >= 50) {
        printf("\n[ALERTA] Capacidade máxima do acervo atingida (50 discos)!\n");
        return;
    }

    struct Disco novo;

    printf("\n--- CADASTRAR NOVO DISCO ---\n");
    printf("Digite o ID do disco: ");
    scanf("%d", &novo.id);

    // Garante unicidade da chave primária (ID)
    for (int i = 0; i < totalDiscos; i++) {
        if (discos[i].id == novo.id) {
            printf("\n[ERRO] Já existe um disco cadastrado com o ID %d!\n", novo.id);
            return;
        }
    }

    // Espaço inicial limpa o '\n' do buffer; %49[^\n] lê nomes compostos com segurança
    printf("Digite o Título do disco: ");
    scanf(" %49[^\n]", novo.titulo);

    printf("Digite o Artista/Banda: ");
    scanf(" %49[^\n]", novo.artista);

    printf("Digite o Preço de Locação: ");
    scanf("%f", &novo.preco_locacao);

    printf("Digite o ID do Gênero (0: Rock, 1: Jazz, 2: Pop, 3: MPB): ");
    scanf("%d", &novo.id_genero);

    novo.status = 1; // Todo disco novo entra como Disponível por padrão

    discos[totalDiscos] = novo;
    totalDiscos++;

    salvarDiscosCSV();
    printf("\n=> Sucesso: Disco '%s' cadastrado com sucesso!\n", novo.titulo);
}

void listarDiscos() {
    carregarDiscosCSV();

    // Cabeçalho tabular alinhado à esquerda (%-Ns) para legibilidade no terminal
    printf("\n%-5s | %-25s | %-20s | %-12s | %-8s | %-13s\n",
           "ID", "TÍTULO", "ARTISTA", "PREÇO (R$)", "GÊNERO", "STATUS");
    printf("==============================================================================================\n");

    if (totalDiscos == 0) {
        printf("Nenhum disco cadastrado no arquivo discos.csv.\n");
        return;
    }

    for (int i = 0; i < totalDiscos; i++) {
        printf("%-5d | %-25s | %-20s | R$ %-9.2f | %-8d | %-13s\n",
               discos[i].id,
               discos[i].titulo,
               discos[i].artista,
               discos[i].preco_locacao,
               discos[i].id_genero,
               discos[i].status == 1 ? "Disponível" : "Indisponível");
    }
}

void buscarDisco() {
    carregarDiscosCSV();

    // posicaoId inicia com -1 (valor sentinela) para não confundir com o índice 0
    int idBusca, idEncontrado = 0, posicaoId = -1;

    printf("\n--- BUSCAR DISCO POR ID ---\n");
    printf("Digite o ID do disco: ");
    scanf("%d", &idBusca);

    // Busca linear com saída antecipada (break) ao localizar o ID único
    for (int i = 0; i < totalDiscos; i++) {
        if (discos[i].id == idBusca) {
            idEncontrado = 1;
            posicaoId = i;
            break;
        }
    }

    if (idEncontrado == 1) {
        printf("\nID buscado: ENCONTRADO\n");
        printf("\n%-5s | %-25s | %-20s | %-12s | %-8s | %-13s\n",
               "ID", "TÍTULO", "ARTISTA", "PREÇO (R$)", "GÊNERO", "STATUS");
        printf("----------------------------------------------------------------------------------------------\n");
        printf("%-5d | %-25s | %-20s | R$ %-9.2f | %-8d | %-13s\n",
               discos[posicaoId].id,
               discos[posicaoId].titulo,
               discos[posicaoId].artista,
               discos[posicaoId].preco_locacao,
               discos[posicaoId].id_genero,
               discos[posicaoId].status == 1 ? "Disponível" : "Indisponível");
    } else {
        printf("\nID buscado: NÃO ENCONTRADO\n");
        printf("O ID digitado não corresponde a nenhum disco no acervo!\n");
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
        printf("Título: %s | Artista: %s | Preço: R$%.2f | Gênero: %d | Status: %s\n",
               discos[posicaoId].titulo,
               discos[posicaoId].artista,
               discos[posicaoId].preco_locacao,
               discos[posicaoId].id_genero,
               discos[posicaoId].status == 1 ? "Disponível" : "Indisponível");

        printf("\nDigite o novo título do disco: ");
        scanf(" %49[^\n]", discos[posicaoId].titulo);

        printf("Digite o novo artista/banda: ");
        scanf(" %49[^\n]", discos[posicaoId].artista);

        printf("Digite o novo preço de locação: ");
        scanf("%f", &discos[posicaoId].preco_locacao);

        printf("Digite o novo ID do gênero (0 a 3): ");
        scanf("%d", &discos[posicaoId].id_genero);

        printf("Informe o status (1 - Disponível | 0 - Indisponível): ");
        scanf("%d", &discos[posicaoId].status);

        salvarDiscosCSV();
        printf("\n=> Sucesso: Dados do disco atualizados no arquivo CSV!\n");
    } else {
        printf("\n[ALERTA] Disco com ID %d não foi encontrado!\n", idEdicao);
    }
}

void excluirDisco() {
    carregarDiscosCSV();

    int idExcluir, idEncontrado = 0, posicaoId = -1;

    printf("\n--- EXCLUIR / DESATIVAR DISCO ---\n");
    printf("Digite o ID do disco a ser desativado: ");
    scanf("%d", &idExcluir);

    // Só permite desativar discos atualmente disponíveis (status == 1)
    for (int i = 0; i < totalDiscos; i++) {
        if (discos[i].id == idExcluir && discos[i].status == 1) {
            idEncontrado = 1;
            posicaoId = i;
            break;
        }
    }

    if (idEncontrado == 1) {
        // Exclusão Lógica (Soft Delete): preserva o histórico para o módulo de Locações
        discos[posicaoId].status = 0;

        salvarDiscosCSV();
        printf("\n=> Sucesso: Disco '%s' (ID %d) foi desativado do acervo!\n",
               discos[posicaoId].titulo, idExcluir);
    } else {
        printf("\n[ALERTA] Disco com ID %d não foi encontrado ou já está inativo.\n", idExcluir);
    }
}

/* ===============================================================
   5. GERENCIAMENTO DA MATRIZ (PRATELEIRAS / MOSTRUÁRIO)
   =============================================================== */

void inicializarMatriz() {
    // Zera todas as 16 posições (4x4) para eliminar lixo de memória
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
        printf(" Escolha uma opção: ");
        scanf("%d", &opcaoMatriz);

        if (opcaoMatriz == 1) {
            printf("\n--- GRADE DE MOSTRUÁRIO DA LOJA (MATRIZ 4x4) ---\n");
            printf("Linhas = Gêneros (0: Rock, 1: Jazz, 2: Pop, 3: MPB)\n");
            printf("Colunas = Prateleiras (0 a 3)\n\n");
            printf("           Prat. 0   Prat. 1   Prat. 2   Prat. 3\n");
            for (int i = 0; i < 4; i++) {
                printf("Gênero %d | ", i);
                for (int j = 0; j < 4; j++) {
                    printf("  [%2d]   ", matrizPrateleiras[i][j]);
                }
                printf("\n");
            }
        } else if (opcaoMatriz == 2) {
            int g, p, qtd;
            printf("\nDigite o Gênero (0 a 3): ");
            scanf("%d", &g);
            printf("Digite a Prateleira (0 a 3): ");
            scanf("%d", &p);

            // Bounds Checking: evita escrita fora dos limites da matriz (0..3)
            if (g >= 0 && g < 4 && p >= 0 && p < 4) {
                printf("Digite a quantidade de discos neste nicho: ");
                scanf("%d", &qtd);
                matrizPrateleiras[g][p] = qtd; // Acesso direto em tempo O(1)
                printf("=> Sucesso: Nicho [%d][%d] atualizado para %d discos!\n", g, p, qtd);
            } else {
                printf("\n[ERRO] Posição inválida! Digite valores entre 0 e 3.\n");
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
            printf("\nOpção desconhecida. Tente novamente.\n");
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
        printf(" Escolha uma opção: ");
        scanf("%d", &opcao);
        system("cls");

        opcaoMenuDiscos(opcao);
    } while (opcao != 0);
}

#endif
