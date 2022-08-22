#ifndef FILA_H
#define FILA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

typedef void *Fila;

/*cria e aloca espaço para uma fila
    pre-condição: haver memoria disponivel.
    retorna: um void pointer para a fila
*/
 Fila newQueue();

/*insere um elemento no fim da fila
    pre-condição: haver espaço disponivel na fila.
    retorna: o tamanho  da fila apos a inserção do novo elemento.
*/
 int enqueue(void *q, double x, double y);

/*retira um elemento do começo da fila
    pre-condição: haver algum elemento na fila.
    retorna: o elemento retirado da fila.
    
*/
 void* dequeue(void *q);

/* limpa a fila e libera a memoria armazenada
    pre-condição: a fila existir.
    retorna: nada, apenas limpa a fila.
*/
 void freeQueue(void *q);

 /*pega o x da struct dentro do ponteiro
    pré-condição: a struct existir
    retorna: o double X
*/

 double pickXfromxyPoint(void *xyptr);

 /*pega o y da struct dentro do ponteiro
    pré-condição: a struct existir
    retorna: o double Y
*/
 double pickYfromxyPoint(void *xyptr);
 
 /*devolve o tamanho da lista
    pré-condição: fila existir
    retorna: tamanho da fila INT
*/
 int returnQueuesize(Fila q);

/*import fila
    pre-condição: a fila existir e a outra data structure tbm
    retorna: um estrutura com os mesmos dados da fila
*/
void importQueue(Lista ,Fila);
#endif
