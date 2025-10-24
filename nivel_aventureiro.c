#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRINGS 50
#define TAM_MAX 10

int comp_sequencial = 0;
int comp_binaria = 0;

typedef struct{
    char nome[MAX_STRINGS];
    char tipo[MAX_STRINGS];
    int quantidade;
} Item;

typedef struct{
    Item itens[MAX_STRINGS];
    int quantidade;
}Mochila;

typedef struct No{
    Item dado;
    struct No* proximo;
}No;

typedef No* ListaEncadeada;

// Função de limpar o buffer
void limparBufferEntrada();

void exibirCabecalhoTabela();
void exibirItemNaTabela(const Item item);

// prototipos Vetores
void inicializarMochila(Mochila *mochila);
void inserirItemVetor(Mochila *mochila);
void removerItemVetor(Mochila *mochila, const char* nomeBusca);
void listarItensVetor(const Mochila *mochila);
int buscaSequencialVetor(const Mochila *mochila, const char* nomeBusca);
int buscaBinariaVetor(const Mochila *mochila, const char* nomeBusca);
void menuMochilaVetor();

// prototipos da lista Encadeada
void inicializarMochilaEncadeada(ListaEncadeada *lista);
void inserirItemEncadeada(ListaEncadeada *lista);
void removerItemEncadeada(ListaEncadeada *lista, const char* nomeBusca);
void listarItensEncadeada(const ListaEncadeada lista);
No* buscarSequencialEncadeada(const ListaEncadeada lista, const char* nomeBusca);
void liberarListaEncadeada(ListaEncadeada *lista);
void menuMochilaEncadeada();

// Menus

int main(){
    int opcao;
    do{
        printf("\n--- Manipulacao de Item da Mochila (Nivel Aventureiro) ---\n");
        printf("1. Usar Mochila Estatica (Vetor + Sort/Busca Binaria)\n");
        printf("2. Usar Mochila Encadeada (Alocacao Dinamica)\n");
        printf("0. Sair do Programa\n");
        printf("Opcao: ");
        if(scanf("%d", &opcao) != 1){
            limparBufferEntrada();
            opcao = -1;
        }
        limparBufferEntrada();

        switch(opcao){
            case 1:
                menuMochilaVetor();
                break;

            case 2:
                menuMochilaEncadeada();
                break;
            
            case 0:
                printf("Saindo do Programa.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    return 0;
}


void limparBufferEntrada(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}


void inicializarMochila(Mochila *mochila){
    mochila->quantidade = 0;
}

void exibirCabecalhoTabela(){
    printf("\n--------------------------------------------------------------\n");
    printf("| %-30s | %-10s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("----------------------------------------------------------------\n");
}

void exibirItemNaTabela(const Item item){
    printf("| %-30s | %-10s | %-10d |\n",
        item.nome,
        item.tipo,
        item.quantidade
    );
}

void inserirItemVetor(Mochila *mochila){
    if(mochila->quantidade == TAM_MAX){
        printf("Erro: Mochila cheia! Nao e possivel inserir mais itens.\n");
        return;
    }

    Item novoItem;
    printf("\n--- Novo Item ---\n");

    printf("Nome do Item (Max %d chars): ", MAX_STRINGS -1);
    fgets(novoItem.nome, MAX_STRINGS, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;

    printf("Tipo do Item (ex: Comida, Arma): ");
    fgets(novoItem.tipo, MAX_STRINGS, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;

    printf("Quantidade: ");
    if(scanf("%d", &novoItem.quantidade) != 1){
        printf("Erro: Quantidade invalida. Cancelando insercao.\n");
        limparBufferEntrada();
    }
    limparBufferEntrada();

    mochila->itens[mochila->quantidade] = novoItem;
    mochila->quantidade++;
    printf("\n[Sucesso] Item \"%s\"(x%d) adicionado a mochila.\n", novoItem.nome, novoItem.quantidade);
}

void mochilaVetor(Mochila *mochila){
    if(mochila->quantidade == TAM_MAX){
        printf("Erro: Mochila cheia! Nao e possivel inserir.\n");
        return;
    }

    Item novoItem;
    printf("\n--- Novo Item ---\n");
    printf("Nome do Item (Max %d chars): ", MAX_STRINGS -1);
    fgets(novoItem.nome, MAX_STRINGS, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;

    printf("Tipo do Item (ex: Comida, Arma, etc): ");
    fgets(novoItem.tipo, MAX_STRINGS, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;

    printf("Quantidade: ");
    if(scanf("%d", &novoItem.quantidade) != 1){
        printf("Erro: Qunatidade invalida. Cancelando insercao. \n");
        limparBufferEntrada();
        return;
    }
    limparBufferEntrada();

    mochila->itens[mochila->quantidade] = novoItem;
    mochila->quantidade++;
    printf("\n[Sucesso] Item \"%s\" (x%d) adicionado a mochila.\n", novoItem.nome, novoItem.quantidade);
}

void removerItemVetor(Mochila *mochila, const char* nomeBusca){
    int i, pos = -1;

    for(i = 0; i < mochila->quantidade; i++){
        if(strcmp(mochila->itens[i].nome, nomeBusca) == 0){
            pos = i;
            break;
        }
    }

    if(pos == -1){
        printf("Erro: Item \"%s\"nao encontrado na mochila. \n", nomeBusca);
        return;
    }

    for(i = pos; i < mochila->quantidade -1; i++){
        mochila->itens[i] = mochila->itens[i+1];
    }

    mochila->quantidade--;
    printf("\n[Sucesso] Item \"%s\" removido com sucesso. \n", nomeBusca);

}

void listarItensVetor(const Mochila *mochila){
    if(mochila->quantidade == 0){
        printf("\nA mochila estatica esta vazia. Nao ha itens para listar.\n");
        return;
    }
    exibirCabecalhoTabela();
    for(int i = 0; i < mochila->quantidade; i++){
        exibirItemNaTabela(mochila->itens[i]);
    }
    printf("--------------------------------------------------------------\n");
}

void ordenarVetor(Mochila *mochila){
    if(mochila->quantidade < 2){
        printf("Nao ha itens suficientes para ordenar. \n");
        return;
    }

    Item temp;
    for(int i = 0; i < mochila->quantidade - 1; i++){
        for(int j = 0; j < mochila->quantidade - 1 - i; j++){
            if(strcmp(mochila->itens[j].nome, mochila->itens[j+1].nome) > 0){
                temp = mochila->itens[j];
                mochila->itens[j] = mochila->itens[j+1];
                mochila->itens[j+1] = temp;
            }
        }
    }
    printf("\n[Sucesso] Itens ordenados por nome (Bubble Sort).\n");

}

int buscaSequencialVetor(const Mochila *mochila, const char* nomeBusca){
    comp_sequencial = 0;
    for(int i = 0; i < mochila->quantidade; i++){
        comp_sequencial++;
        if(strcmp(mochila->itens[i].nome, nomeBusca) == 0){
            return i;
        }
    }
    return -1;
}

int buscaBinariaVetor(const Mochila *mochila, const char* nomeBusca){
    comp_binaria = 0;
    int esquerda = 0;
    int direita = mochila->quantidade -1;
    int meio;
    int resultado_comparacao;

    while(esquerda <= direita){
        meio = esquerda + (direita - esquerda) / 2;
        resultado_comparacao = strcmp(mochila->itens[meio].nome, nomeBusca);
        comp_binaria++;

        if(resultado_comparacao == 0){
            return meio;
        }
        else if(resultado_comparacao < 0){
            esquerda = meio + 1;
        }
        else {
            direita = meio - 1;
        }
    }
    return -1;
}

void inicializarMochilaEncadeada(ListaEncadeada *lista){
    *lista = NULL;
}

void inserirItemEncadeada(ListaEncadeada *lista){
    Item novoItemData;
    printf("\n--- Novo Item (Encadeada) ---\n");
    printf("Nome do Item (Max %d chars): ", MAX_STRINGS -1);
    fgets(novoItemData.nome, MAX_STRINGS, stdin);
    novoItemData.nome[strcspn(novoItemData.nome, "\n")] = 0;

    printf("Tipo do Item (ex: Comida, Arma): ");
    fgets(novoItemData.tipo, MAX_STRINGS, stdin);
    novoItemData.tipo[strcspn(novoItemData.tipo , "\n")] = 0;

    printf("Quantidade: ");
    if(scanf("%d", &novoItemData.quantidade) != 1){
        printf("Erro: Quantidade Invalida. Cancelando Insercao.\n");
        limparBufferEntrada();
        return;
    }
    limparBufferEntrada();

    No* novoNo = (No*) malloc(sizeof(No));
    if(novoNo == NULL){
        printf("Erro: Falha na Alocacao de memoria para o no.");
        return;
    }

    novoNo->dado =  novoItemData;

    novoNo->proximo = *lista;
    *lista = novoNo;

    printf("\n[Sucesso] Item \"%s\" (x%d) adicionado a mochila encadeada.\n", novoItemData.nome, novoItemData.quantidade);
}

void removerItemEncadeada(ListaEncadeada *lista, const char* nomeBusca){
    No *atual = *lista;
    No *anterior = NULL;

    while(atual != NULL && strcmp(atual->dado.nome, nomeBusca) != 0){
        anterior = atual;
        atual = atual->proximo;
    }

    if(atual == NULL){
        printf("Erro: Item \"%s\" nao encontrado na lista encadeada. \n", nomeBusca);
        return;
    }

    if(anterior == NULL){
        *lista = atual->proximo;
    } else{
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("\n[Sucesso] Item \"%s\" removido com sucesso da lista encadeada.\n", nomeBusca);

}

void listarItensEncadeada(const ListaEncadeada lista){
    No *temp = lista;
    if(temp == NULL){
        printf("\nA mochila encadeada esta vazia. Nao ha Itens para listar.\n");
        return;
    }

    exibirCabecalhoTabela();
    while(temp != NULL){
        exibirItemNaTabela(temp->dado);
        temp = temp->proximo;
    }
    printf("--------------------------------------------------------------------------\n");
}

No* buscarSequencialEncadeada(const ListaEncadeada lista, const char* nomeBusca){
    comp_sequencial = 0;
    No *atual = lista;

    while(atual != NULL){
        comp_sequencial++;
        if(strcmp(atual->dado.nome, nomeBusca) == 0){
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}
 
void liberarListaEncadeada(ListaEncadeada *lista){
    No *atual = *lista;
    No *proximo;

    while(atual != NULL){
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *lista = NULL;
}


void menuMochilaVetor(){
    Mochila mochila;
    inicializarMochila(&mochila);
    char nomeBusca[MAX_STRINGS];
    int opcao;

    do{
        printf("\n --- Menu Mochila (Vetor) ---\n");
        printf("1. Adicionar Novo Item\n");
        printf("2. Remover Item pelo Nome\n");
        printf("3. Listar Todos os Itens\n");
        printf("4. Ordeanar Itens por Nome\n");
        printf("5. Buscar Item (Sequencial)\n");
        printf("6. Buscar Item (Binaria)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Opcao: ");

        if(scanf("%d", &opcao) != 1){
            limparBufferEntrada();
            opcao = -1;
        }
        limparBufferEntrada();

        switch(opcao){
            case 1:
                inserirItemVetor(&mochila);
                break;

            case 2:
                printf("Digite o Nome do item  a remover: ");
                fgets(nomeBusca, MAX_STRINGS, stdin);
                nomeBusca[strcmp(nomeBusca, "\n")] = 0;
                removerItemVetor(&mochila, nomeBusca);
                break;
            
            case 3:
                listarItensVetor(&mochila);
                break;

            case 4:
                ordenarVetor(&mochila);
                break;

            case 5: {
                printf("Digite o Nome do item para busc a sequencial: ");
                fgets(nomeBusca, MAX_STRINGS, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                int pos = buscaSequencialVetor(&mochila, nomeBusca);
                if(pos != -1){
                    printf("\n[Sucesso] Item \"%s\" encontradp na posicao %d. \n", nomeBusca, pos);
                    printf("Comparacoes realizadas: %d\n", comp_sequencial);
                } else{
                    printf("\n[Erro] Item \"%s\" nao encontrado. \n", nomeBusca);
                    printf("Comparacoes realizadas: %d\n", comp_sequencial);
                }
                break;
            }

            case 6: {
                printf("Digite o Nome do Item para busca binaria: ");
                fgets(nomeBusca, MAX_STRINGS, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;

                printf("\n[Atencao] Para Busca Binaria funcionar, a lista deve estar ordenada!\n");
                int pos = buscaBinariaVetor(&mochila, nomeBusca);
                if(pos != -1){
                    printf("\n[Sucesso] Item \"%s\" encontrado na posicao %d.\n", nomeBusca, pos);
                    printf("Comparacoes realizadas: %d\n", comp_binaria);
                } else{
                    printf("\n[Erro] Item \"%s\" nao encontrado. \n", nomeBusca);
                    printf("Comparacoes realizadas: %d\n", comp_binaria);
                }
                break;
            }

            case 0:
                printf("Voltando.. \n");
                break;
            
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

void menuMochilaEncadeada(){
    ListaEncadeada lista;
    inicializarMochilaEncadeada(&lista);
    char nomeBusca[MAX_STRINGS];
    int opcao;

    do {
        printf("\n --- Menu Mochila (Lista Encadeada) --- \n");
        printf("1. Adicionar Item (loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item por Nome (Sequencial)\n");
        printf("0. Voltar e liberar Memoria\n");
        printf("Opcao: ");
        if(scanf("%d", &opcao) != 1){
            limparBufferEntrada();
            opcao = -1;
        }
        limparBufferEntrada();

        switch(opcao){
            case 1:
                inserirItemEncadeada(&lista);
                break;
            
            case 2:
                printf("Digite o Nome do item a remover: ");
                fgets(nomeBusca, MAX_STRINGS, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                removerItemEncadeada(&lista, nomeBusca);
                break;

            case 3:
                listarItensEncadeada(lista);
                break;

            case 4:{
                printf("Digite o Nome do item para buscar: ");
                fgets(nomeBusca, MAX_STRINGS, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                No* no_encontrado = buscarSequencialEncadeada(lista, nomeBusca);
                if(no_encontrado != NULL){
                    printf("\n[Sucesso] Item \"%s\" encontrado. \n", nomeBusca);
                    printf("Item: %s, Tipo: %s, Quantidade: %d\n", no_encontrado->dado.nome, no_encontrado->dado.tipo, no_encontrado->dado.quantidade);
                    printf("Comparacoes realizadas: %d\n", comp_sequencial);
                } else{
                    printf("\n [Erro] Item \"%s\" nao encontrado.\n", nomeBusca);
                    printf("Comparacoes realizadas: %d\n", comp_sequencial);
                }
                break;
            }

            case 0:
                liberarListaEncadeada(&lista);
                printf("Voltando ao Menu Principal e liberando memoria... \n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}