#include <stdio.h>
#include <stdlib.h>
#include "Huffman.h"

/** Cria uma Fila  */
void cria (tFila *F) {
	F->inicio = NULL;
	F->fim = NULL;
	F->tam = 0;
}

/**Verifica se a Fila está vazia */
int vazia (tFila F) {
	if (F.tam == 0)
		return 1;
	else
		return 0;
}

/** Obtém o tamanho da Fila */
int tamanho (tFila F) {
	return F.tam;
}

/** Consulta o elemento do início da fila
    Retorna 0 se a fila estiver vazia, 1 caso contrário
    O parâmetro elem recebe o elemento início */
int primeiro (tFila F, char *elem) {
	if (vazia(F))
		return 0; /*Erro: Fila vazia */

	*elem = (F.inicio)->dado;
	return 1;
}

/** Insere um elemento no fim de uma fila
    Retorna 0 se a mem. for insuficiente, 1 caso contrário*/
int insere (tFila *F, char valor) {
	tNo *novoNo;
	novoNo = malloc(sizeof(tNo));
	if (novoNo == NULL){
		return 0;  /* erro: mem. insuficiente */
	}

	novoNo->dado = valor;
	novoNo->prox = NULL;
        novoNo->dir = NULL;
        novoNo->esq = NULL;

    if (vazia(*F)){    /*Inserção em fila vazia */
        F->inicio = novoNo;
        F->fim = novoNo;
    }
    else {
		(F->fim)->prox = novoNo; /* liga com a fila */
		F->fim = novoNo; /* atualiza o novo fim */
    }

    F->tam++;
    return 1;
}



/**Retira o elemento do início da fila
    Retorna 0 se a fila estiver vazia, 1 caso contrário
    O parâmetro valor irá receber o elemento retirado */
int retira (tFila *F, char *valor) {
	tNo *p;
 	char res;

	if (vazia(*F)) {
        return 0; /*Erro: Fila vazia */
    }

	res = primeiro(*F, valor);
 	if (F->inicio == F->fim){ /* Fila com 1 elemento */
		F->fim = NULL;
    }

	p = F->inicio;
	F->inicio = p->prox;
	F->tam--;
	

	return (1);
}

//LISTA ED

void exibeFila(tFila *F){
	tNo *p;
	int i;
	p = F->inicio;

	for (i = 0; F->tam > i; ++i){
		printf("Elemento: %c | Frequencia: %d\n",p->dado, p->freq);

		p = p->prox;
	}
	printf("Tamanho: %d\n", F->tam);
}

void exibeArvore(tFila F) {
    tNo *p;
    p = F.inicio;

    if (vazia(F))
        return ;

    while(p != NULL){
        printf("Elemento: %c | Frequencia: %d\n",p->dado, p->freq);
        p = p->esq;

    }

    while(p != NULL){
        printf("Elemento: %c | Frequencia: %d\n",p->dado, p->freq);
        p = p->dir;
    }


 }
		



int verificaFila(tFila F, char dado){
	tNo *p;
	int i;

    int n = 1;

    if (F.inicio == NULL) {
            return 0;
    }

    p = F.inicio;
    while ((p != NULL) && (p->dado != dado)){
        p = p->prox;
    }

     if (p == NULL) {
            return 0;
     }

    (p->freq)++;

     return 1;
}

int insertionSortFreq(struct no *V, int N){
        int i, j;
        struct no aux;
        for (i = 1; i < N; ++i)
        {
            aux = V[i];
            for(j = i; (j> 0) && (aux.freq < V[j-1].freq); j--)
                V[j] = V[j - 1];
            V[j] = aux;
        }
}

void ordena(tFila *F){
	int i = 0, x = 0;	
	struct no array[F->tam];
	tNo *p;
	p = F->inicio;
	while(i<=tamanho(*F)-1){
        array[i].freq = p->freq;
        array[i].dado = p->dado;
        p = p->prox;
        i++;
    }

    insertionSortFreq(array, tamanho(*F));
	    
    p = F->inicio;
    while(x < i){
        p->dado = array[x].dado;
        p->freq = array[x].freq;
        p = p->prox;
        x++;
    }
}

void criaArvore(tFila *F){
	tNo *p;
	p = F->inicio;
	int novaFreq;
             char x, y;
             tNo *novoNo;

	while(F->tam > 1){
                         novoNo = malloc(sizeof(tNo));

		novaFreq = p->freq;
                          novoNo->esq = p;
                          //printf("%d\n", p->freq);
		retira(F, &x);
                          p = p->prox;

                          novoNo->dir = p;
		novaFreq += p->freq;
                          //printf("%d\n", p->freq);
		retira(F, &y);
                          p = p->prox;

                          novoNo->freq = novaFreq;
                          novoNo->prox = NULL;
                          printf("%d\n", novoNo->freq);


                            if (vazia(*F)){    /*Inserção em fila vazia */
                                F->inicio = novoNo;
                                F->fim = novoNo;
                            }
                            else {
                                (F->fim)->prox = novoNo; /* liga com a fila */
                                F->fim = novoNo; /* atualiza o novo fim */
                            }
                            F->tam++;
	}
}

