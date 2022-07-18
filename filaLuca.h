/******* LUCA DA SILVA ÁVILA - ENGENHARIA DE COMPUTAÇÃO ***********/

#ifndef FILA_H
#define FILA_H

#include "amostra.h"

typedef struct cel Celula;
typedef struct fila tFila;

//inicializa uma fila sem nenhum parâmetro
tFila* inicializaFila(void);

//adiciona elemento à fila com prioridade
void pushFila(tFila* fila, Amostra* amostra);

//FIFO com prioridade, retira elemento da fila
Amostra* popFila(tFila* fila);

//indica se a fila esta vazia
int taVaziaFila(tFila* fila);

//imprime os elementos da fila
void imprimeFila(tFila* fila);

//libera a memória alocada na fila
void liberaFila(tFila* fila);

#endif