#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Huffman.h"

void cria (tFila *F) {
	F->inicio = NULL;
	F->fim = NULL;
	F->tam = 0;
}

int vazia (tFila F) {
	if (F.tam == 0)
		return 1;
	else
		return 0;
}

int tamanho (tFila F) {
	return F.tam;
}

int primeiro (tFila F, char *elem) {
	if (vazia(F))
		return 0; /*Erro: Fila vazia */

	*elem = (F.inicio)->dado;
	return 1;
}

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

void printarv(tNo *b){

   if(b == NULL)
        return;
    if(b->dado!=NULL)
    printf("[folha] dado = %c| Frequencia %d\n" ,b->dado,b->freq);

    if(b->dir!=NULL){
        printf("dir->");
        printarv(b->dir);
    }
    if(b->esq!=NULL){
        printf("esq->");
        printarv(b->esq);
        }
}

void exibeArvore(tFila F) {
    tNo *p;
    p = F.inicio;
    printarv(p);

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
            p->bin="0";
            novoNo = malloc(sizeof(tNo));
            novaFreq = p->freq;
            novoNo->esq = p;
            retira(F, &x);
            p = p->prox;
            p->bin="1";
            novoNo->dir = p;
            novaFreq += p->freq;
            retira(F, &y);
            p = p->prox;
            novoNo->freq = novaFreq;
            novoNo->prox = NULL;
            novoNo->dado= 0;
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

int codifica(tNo *b,char *ch,int i){

	if (b == NULL)
		return 0;

	if (b->esq != NULL){//todo para esquerda se nao tiver esquerda vai para direita
            printf("0");
            ch[i]='0';
            i++;
            codifica(b->esq,ch,i);

        }

 	else if (b->dir != NULL){
            printf("1");
            ch[i]='1';
            i++;
            codifica(b->dir,ch,i);
		}


	if(b->dir == NULL && b->esq == NULL){
		printf("[folha] dado = %c | Binario: %s\n" ,b->dado,ch);
		b=NULL;//nao esta apagando o ultima folha
	}

	return 1;
}

void exibeCod(tFila *F) {
    tNo *p;
    p = F->inicio;
    char ch[256];
    int i=0,r;
    while(r!=0)// quando nao existir no na arvore encerra
   	r=codifica(p,ch,i);

 }
