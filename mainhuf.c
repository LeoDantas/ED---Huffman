#include <stdio.h>
#include <stdlib.h>
#include "Huffman.h"

#define TRUE 1
#define FALSE 0



int main()
{
    tFila minhaFila;
    int i = 0;
    char *dado;
    char ch;
    char x;
    char palavra[256];
    for(i=0;i<256;i++)
        palavra[i]=NULL;

    i=0;

    cria(&minhaFila);

    FILE *arq;
    arq = fopen("texto.txt", "r");

    if(arq == NULL){
        printf("Arquivo nao pode ser aberto.\n");
        return 0;
    }else{
        while((ch=fgetc(arq)) != EOF){
            palavra[i] = ch;
            i++;
            if(!verificaFila(minhaFila, ch)){
                if(!insere(&minhaFila, ch)){
                }
                verificaFila(minhaFila, ch);
            }
        }
    }

    printf("%s\n", palavra);

    //printf("\n");
    //ordena(&minhaFila);
    //exibeFila(&minhaFila);
    //printf("\n");
    criaArvore(&minhaFila);
   // printf("\n");
    char arr[1000];
    int r;
    for(r=0;r<1000;r++)
        arr[r]=NULL;

    codificar(&minhaFila,palavra,arr);

    decodificar(&minhaFila,arr);


    //exibeCod(minhaFila, palavra, i);
}
