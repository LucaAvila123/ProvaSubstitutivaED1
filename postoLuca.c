/******* LUCA DA SILVA ÁVILA - ENGENHARIA DE COMPUTAÇÃO ***********/

#include "posto.h"
#include "filaLuca.h"
#include "amostra.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Tipo que define um Posto de Saúde (tipo opaco)
 *Um posto deve ter os seguintes atributos:
 * * Nome do Posto
 * * Uma FILA de amostras para exame não processadas
 * * Uma FILA de amostras processadas com resultado POSITIVO
 * * Uma FILA de amostras processadas com resultado NEGATIVO
 * */
struct posto{
    char* nomePosto;
    tFila* naoProcessadas;
    tFila* resultadosPositivos;
    tFila* resultadosNegativos;
};

/* Cria um posto de saúde, ainda vazio, com as 3 filas, vazias
* inputs: nome do posto de saúde.
* output: posto alocado e vazio, com filas de amostras ainda vazias
* pre-condicao: nao tem
* pos-condicao: posto alocado e vazio, com filas de amostras alocadas e vazias
 */
Posto* inicPosto(char* nome){
    Posto* posto = (Posto*) malloc (sizeof(Posto));

    posto -> nomePosto = strdup(nome);
    
    posto -> naoProcessadas = inicializaFila();
    posto -> resultadosPositivos = inicializaFila();
    posto -> resultadosNegativos = inicializaFila();

    return posto;
}

/* Imprime os dados do Posto no seguinte formato:
 
 Dados do Posto: <nome do posto>
 Amostras não processadas
 <fila de amostras não processadas - do início ao fim>
 
 Amostras com resultados positivos
 <fila de amostras positivas - do início ao fim>
 
 Amostra com resultados negativos
 <fila de amostras negativas - do início ao fim>
 
* inputs: referencia para o posto
* output: nenhum
* pre-condicao: posto alocado
* pos-condicao: dados do posto não são alterados
 */
void imprimePosto(Posto* posto){
    if(posto){
        printf("Dados do Posto: %s\n", posto -> nomePosto);
        printf("Amostras não processadas\n");
        imprimeFila(posto -> naoProcessadas);
        printf("\nAmostras com resultados positivos\n");
        imprimeFila(posto -> resultadosPositivos);
        printf("\nAmostras com resultados negativos\n");
        imprimeFila(posto -> resultadosNegativos);
        printf("\n");
    } 
}

/* Simula a realização de uma coleta de material para teste
 * A função deve criar uma amostra e fazer as devidas atribuições à amostra
 * Deve-se inserir a amostra na fila de "não processados"
 * ATENÇÃO: se a pessoa for idosa (idade>=60), ela deve ir para o início da fila de não processados
* inputs: referência para o posto de saúde, o nome do dono da coleta e a idade da pessa
* output: nenhum
* pre-condicao: posto válido, nome da pessoa válido
* pos-condicao: Amostra alocada e inserida na fila de amostras não processadas
 */
void realizaColeta(Posto* posto, char* pessoa, int idade){
    if(posto && pessoa){
        Amostra* nova = inicAmostra(pessoa, idade);
        pushFila(posto -> naoProcessadas, nova);
    }
}

/* Libera toda a memória alocada para o posto de saúde
* inputs: referência do posto de saúde.
* output: nenhum
* pre-condicao: posto válido
* pos-condicao: Memória para a string nome liberada; memória para as 3 filas liberada, memoria do posto liberada
 */
void liberaPosto(Posto* posto){
    if(posto){  
        liberaFila(posto -> naoProcessadas);
        liberaFila(posto -> resultadosPositivos);
        liberaFila(posto -> resultadosNegativos);
        free(posto -> nomePosto);
        free(posto);
    }
}

/* Essa função simula o processamento (testagem) das amostras e atualiza os resultados nas amostras. Deve-se usar a constante LIMITE_CARGA_VIRAL para definir positivo e negativo.
* inputs: referência do posto de saúde.
* output: nenhum
* pre-condicao: posto válido
* pos-condicao: amostras foram devidamente processadas; fila de amostras não processadas deve ficar vazia; fila de amostras positivas deve conter as amostras que testaram positivo (idosos na frente); fila de amostras negativas deve conter as amostras que testaram negativo (idosos na frente).
 */
void processaLoteAmostras(Posto* posto){
    if(posto){
        Amostra* analisando = NULL;
        while(!taVaziaFila(posto -> naoProcessadas)){
            //retirando da fila de não processadas para análises
            analisando = popFila(posto -> naoProcessadas);
            
            //insere em alguma das outras filas
            if(retornaCargaViral(analisando) > LIMITE_CARGA_VIRAL){
                registraResultado(analisando, 1);
                pushFila(posto -> resultadosPositivos, analisando);
            }
            else{
                registraResultado(analisando, 0);
                pushFila(posto -> resultadosNegativos, analisando);
            }
        }
    }
}