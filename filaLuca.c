/******* LUCA DA SILVA ÁVILA - ENGENHARIA DE COMPUTAÇÃO ***********/


#include "filaLuca.h"
#include "amostra.h"
#include <stdio.h>
#include <stdlib.h>

struct cel{
    Amostra* amostra;
    Celula* prox;
};

struct fila{
    Celula* prim;
    Celula* ult;
};

//inicializa uma fila sem nenhum parâmetro
tFila* inicializaFila(void){
    tFila* fila = (tFila*) malloc (sizeof(tFila));

    fila -> prim = NULL;
    fila -> ult  = NULL;
    return fila;
}

//adiciona elemento à fila com prioridade
void pushFila(tFila* fila, Amostra* amostra){
    Celula* nova = (Celula*) malloc (sizeof(Celula));
    nova -> amostra = amostra;
    nova -> prox = NULL;

    if(taVaziaFila(fila)){
        fila->prim = nova;
        fila->ult = nova;
    }
    else{
        //percorre a fila até poder colocar idoso antes dos não idosos (os idosos não estão com qualquer prioridade entre si)
        if(retornaIdade(amostra) >= 60){
            //se houver pelo menos um idoso na lista
            if(retornaIdade(fila -> prim -> amostra) >= 60){
                
                Celula* comecaJovem = fila -> prim;
                Celula* ultimoIdoso = NULL;

                while(comecaJovem != NULL && retornaIdade(comecaJovem -> amostra) >= 60){
                    ultimoIdoso = comecaJovem;
                    comecaJovem = comecaJovem -> prox;
                }

                //insere uma célula entre um idoso e um jovem 
                ultimoIdoso -> prox = nova;
                nova -> prox = comecaJovem;

                
            }
            //quando não há idoso na lista
            else{
                Celula* aux = fila -> prim;
                fila -> prim = nova;
                nova -> prox = aux;
            }
        }
        else{
            fila -> ult -> prox = nova;
            fila -> ult = nova;
            fila -> ult -> prox = NULL;
        }
    }
}

//FIFO, retira elemento do começo da fila
Amostra* popFila(tFila* fila){
    if(!taVaziaFila(fila)){
        Celula* tirando = fila -> prim;
        fila -> prim = fila -> prim -> prox;
        Amostra* analisando = tirando -> amostra;
        free(tirando);
        return analisando;
    } 
    return NULL;
}

//indica se a fila esta vazia
int taVaziaFila(tFila* fila){
    return fila -> prim == NULL;
}

//libera a memória alocada na fila
void liberaFila(tFila* fila){
    //esvazia e libera depois
    if(fila){
        Amostra* analisando = NULL;
        while(!taVaziaFila(fila)){
            analisando = popFila(fila);
            liberaAmostra(analisando);
        }
            

        free(fila);
    }
    
}

//imprime os elementos da fila
void imprimeFila(tFila* fila){
    if(!taVaziaFila(fila)){
        Celula* p = NULL;
        for(p = fila -> prim; p; p = p->prox){
            imprimeAmostra(p -> amostra);
        }
    }
}