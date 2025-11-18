#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

// -------------------- STRUCTS E ENUM --------------------

typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

// -------------------- VARIÁVEIS GLOBAIS --------------------

Item mochila[MAX_ITENS];
int numItens = 0;
long comparacoes = 0;
bool ordenadaPorNome = false;

// -------------------- FUNÇÕES AUXILIARES --------------------

void limparTela() {
    for (int i = 0; i < 40; i++) printf("\n");
}

void exibirMenu() {
    printf("===== MOCHILA - CODIGO DA ILHA (Free Fire) =====\n");
    printf("Itens na mochila: %d/%d\n", numItens, MAX_ITENS);
    printf("Ordenada por nome: %s\n\n", ordenadaPorNome ? "SIM" : "NAO");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar itens\n");
    printf("5. Busca binaria por nome\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

// -------------------- INSERIR ITEM --------------------

void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("Nome do item: ");
    scanf(" %49[^\n]", novo.nome);

    printf("Tipo do item: ");
    scanf(" %49[^\n]", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);

    mochila[numItens++] = novo;
    ordenadaPorNome = false;

    printf("Item adicionado!\n");
}

// -------------------- REMOVER ITEM --------------------

void removerItem() {
    char nome[50];
    printf("Nome do item a remover: ");
    scanf(" %49[^\n]", nome);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < numItens - 1; j++)
                mochila[j] = mochila[j + 1];

            numItens--;
            ordenadaPorNome = false;

            printf("Item removido!\n");
            return;
        }
    }

    printf("Item não encontrado.\n");
}

// -------------------- LISTAR ITENS --------------------

void listarItens() {
    if (numItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\n===== ITENS NA MOCHILA =====\n");
    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");

    for (int i = 0; i < numItens; i++)
        printf("%-20s %-15s %-10d %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
}

// -------------------- INSERTION SORT --------------------

int comparar(Item a, Item b, CriterioOrdenacao c) {
    comparacoes++;

    switch (c) {
        case ORDENAR_NOME:
            return strcmp(a.nome, b.nome);
        case ORDENAR_TIPO:
            return strcmp(a.tipo, b.tipo);
        case ORDENAR_PRIORIDADE:
            return b.prioridade - a.prioridade; // maior prioridade primeiro
    }
    return 0;
}

void insertionSort(CriterioOrdenacao criterio) {
    comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0 && comparar(mochila[j], chave, criterio) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
        }

        mochila[j + 1] = chave;
    }

    if (criterio == ORDENAR_NOME)
        ordenadaPorNome = true;
    else
        ordenadaPorNome = false;
}

// -------------------- MENU DE ORDENAÇÃO --------------------

void menuDeOrdenacao() {
    int op;
    printf("\n===== ORDENAR POR =====\n");
    printf("1. Nome\n");
    printf("2. Tipo\n");
    printf("3. Prioridade\n");
    printf("Escolha: ");
    scanf("%d", &op);

    if (op < 1 || op > 3) {
        printf("Opção inválida.\n");
        return;
    }

    insertionSort((CriterioOrdenacao)op);
    printf("Itens ordenados! Comparações feitas: %ld\n", comparacoes);
}

// -------------------- BUSCA BINÁRIA --------------------

void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("A mochila não está ordenada por nome. Ordene primeiro!\n");
        return;
    }

    char nome[50];
    printf("Nome do item para buscar: ");
    scanf(" %49[^\n]", nome);

    int ini = 0, fim = numItens - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(nome, mochila[meio].nome);

        if (cmp == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQtd: %d\nPrioridade: %d\n",
                   mochila[meio].nome,
                   mochila[meio].tipo,
                   mochila[meio].quantidade,
                   mochila[meio].prioridade);
            return;
        }

        if (cmp > 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    printf("Item não encontrado.\n");
}

// -------------------- MAIN --------------------

int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        limparTela();

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n");
        }

        printf("\n");

    } while (opcao != 0);

    return 0;
}
