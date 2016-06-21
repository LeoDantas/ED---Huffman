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
        if(p->dado!=NULL)
            printf("Elemento: %c | Frequencia: %d\n",p->dado, p->freq);
        else
            printf("Elemento: NO | Frequencia: %d\n", p->freq);
		p = p->prox;
	}
	printf("Tamanho: %d\n", F->tam);
}

void printarv(tNo *b){

   if(b == NULL)
        return;

    if(b->dado!=NULL)
    printf("[folha] dado = %c| Frequencia %d| bin %s\n" ,b->dado,b->freq,b->bin);

    else
    printf("[no] Frequencia %d| bin %s\n" ,b->freq,b->bin);


    if(b->dir!=NULL){
        //printf("dir->");
        printarv(b->dir);
    }
    if(b->esq!=NULL){
        //printf("esq->");
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
    int i=0;

    while(F->tam > 1){


            //i++;
            ordena(F);
      //      exibeFila(F);
        //     printf("\n\n");


            novoNo = malloc(sizeof(tNo));
            novaFreq = p->freq;
            novoNo->esq = p;
            retira(F, &x);

            p = p->prox;
            novoNo->dir = p;
            novaFreq += p->freq;
            retira(F, &y);

            p = p->prox;
            novoNo->freq = novaFreq;
            novoNo->prox = NULL;
            novoNo->dado = 0;

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
    printf("arvore criada \n");
   // exibeArvore(*F);
}

void getcodifica(tNo *p){
	int tam=1;
	if (p!=NULL){
			tam = strlen(p->bin);
			if(p->esq!=NULL) {
				p->esq->bin = (char*) malloc((tam+2)*sizeof(char));
				strcpy(p->esq->bin,p->bin);
				strcat(p->esq->bin,"1");
				getcodifica(p->esq);
			}
			if(p->dir!=NULL) {
				p->dir->bin = (char*) malloc((tam+2)*sizeof(char));
				strcpy(p->dir->bin,p->bin);
				strcat(p->dir->bin,"0");
				getcodifica(p->dir);
			}
	}
}

void codificar(tFila *F,char *palavra,char *arr){
    tNo *p;
    p=F->inicio;
    p->bin = (char*) malloc(sizeof(char));
	strcpy(p->bin,"");	// codigo da raiz eh nulo
	getcodifica(p);
    int tm=strlen(palavra),i=0;
    printf("codigo:");
    p=F->inicio;

    for(i=0;i<tm;i++){
    buscar(p,&palavra[i],arr);
    }
    printf("%s\n",arr);
}

char buscar(tNo *p,char *ch,char *arr){

    if(p->dado==*ch){
        strcat(arr,p->bin);
       // printf("%s",p->bin);
    }
    if(p->dir!=NULL){
        buscar(p->dir,ch,arr);
    }
    if(p->esq!=NULL){
        buscar(p->esq,ch,arr);
    }
    return;
}

void decodificar(tFila *F,char *codigo){
    tNo *p;
    p=F->inicio;
    int i=0;
    getdecodifica(p,codigo,F);
    }

void getdecodifica(tNo *p,char *codigo,int i,tFila *F)  {


    while(codigo[i]!=NULL){
        if(p->dir!=NULL&&p->esq!=NULL){
            printf("entrou no &&\n");
            if(codigo[i]=="1"){
                if(p->esq!=NULL){
                    i++;
                    getdecodifica(p->esq,codigo,i,F);
                }
            }
        else{
            if(p->dir!=NULL){
                i++;
                getdecodifica(p->dir,codigo,i,F);
            }
        }
        }
        else{
            i++;
            printf("entrou no else\n");
            printf("%c",p->dado);
            p=F->inicio;
            getdecodifica(p,codigo,i,F);
        }
    }


}

