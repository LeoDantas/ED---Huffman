#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

/* Definição da ED Fila Encadeada com Duas Cabeças */
typedef struct no {
	char dado;
	int freq;
	char bin;
	struct  no *prox;
	struct no *dir;
	struct no *esq;
} tNo;

typedef struct fila {
	tNo  *inicio;  /* aponta para o inicio da fila */
	tNo  *fim;   /* aponta para o fim da fila  */
	int tam;
} tFila;       /* tipo fila */

void cria (tFila *F);
void criaArvore(tFila *F);
void exibeArvore(tFila F);
int vazia (tFila F);
int tamanho(tFila F);
int primeiro (tFila F, char *dado);
int insere(tFila *F, char dado);
int retira(tFila *F, char *dado);
//int concatenaAlt(tFila F1, tFila F2 , tFila *F3);
void exibeFila(tFila *F);
int verificaFila(tFila F, char dado);
void ordena(tFila *F);
void exibeArv(tFila F);
void printarv(tNo *b);
//void codifica(tNo *b);
void exibeCod(tFila *F);

#endif // HUFFMAN_H_INCLUDED
