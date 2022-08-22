#ifndef LISTA_H
#define LISTA_H

#include "bibliotecas.h"

typedef void *Lista;


/*FUNÇÃO INICIA LISTA
     !pre-condição:Memoria disponivel no sistema;
     !retorna: Um void pointer que aponta para a lista;
*/

Lista inicia();

/*FUNÇÃO PARA INICIAR UM NÓ DA LISTA
    !recebe: ponteiro para lista
    !pre-condição:Memoria disponivel no sistema e o ponteiro para lista ser valido
    !retorna: Um ponteiro para o nó criado
*/
void *inicia_no(Lista);

/*FUNÇÃO PARA ACHAR NÓ
    !recebe: ponteiro para lista e um inteiro que é a posição do nó que voce quer achar
    !pre-condição: o valor inteiro ser uma posição existente na lista,e o ponteiro para lista ser valido
    !retorna: um ponteiro para o nó na posição que foi dada
*/
void *procura_no(Lista, int);

/*FUNÇÂO INSEREÇÂO NO FIM
    !recebe: ponteiro para lista e o dado para ser inserido na lista
    !pre-condição: o ponteiro para lista ser valido e haver memoria disponivel para o nó
    !retorna: um inteiro para dizer se a inserção foi completada com sucesso  ou não
*/
int lista_inserenofim(Lista, void *);

/*FUNÇÂO REMOVE
    !recebe: ponteiro para lista e um inteiro que é a posição do nó que deve ser removido
    !pre-condição: o valor inteiro ser uma posição existente na lista,e o ponteiro para lista ser valido
    !retorna: o dado removido;
*/

void *aux_remove(Lista, int);

/*FUNÇÂO REMOVE DO COMEÇO
    !recebe: Ponteiro para lista
    !pre-condição: O ponteiro para lista ser valido, e a lista não estar vazia
    !retorna: O dado removido;
*/
void *lista_pop(Lista);

/*FUNÇÂO TAMANHO DA LISTA
    !recebe: Ponteiro para lista
    !pre-condição: O ponteiro para lista ser valido
    !retorna: Tamanho da lista.
*/
int returnlistsize(Lista);

/*FUNÇÂO GET DADO DA LISTA
    !recebe: ponteiro para lista e um inteiro que é a posição do nó que armazena o dado que voce quer achar na lista
    !pre-condição: o valor inteiro ser uma posição existente na lista,e o ponteiro para lista ser valido
    !retorna: o dado que estava armazenado no nó "int" da lista
*/
void *returnData(Lista,int);

/*FUNÇÃO GET COMEÇO DA LISTA
    !recebe: ponteiro da lista
    !pré-condição: lista existente
    !retorna: primeiro nó da lista
*/
void* getBegin(void* listacurrent);

/*FUNÇÃO GET PROXIMO DA LISTA
    !recebe: ponteiro da lista, node atual
    !pré-condição: lista existente, node atual existente na lista
    !retorna: proximo node referente ao que foi passado no parametro
*/
void* getNext(void* listacurrent, void* current);

/*FUNÇÃO GET FIM DA LISTA
    !recebe: ponteiro pra lista
    !pré-condição: lista existente
    !retorna: ultimo nó da lista.
*/
void* getLast(void* lista);

/*FUNÇÃO GET ANTERIOR NA LISTA
    !recebe: ponteiro da lista, node atual
    !pré-condição: lista existente, node atual existente na lista
    !retorna: anterior node referente ao que foi passado no parametro
*/
void* getPrev(void* listacurrent, void* current);

/*FUNÇÃO CONFERE LISTA VAZIA
    !recebe: ponteiro da lista
    !pré-condição: lista existente
    !retorna: um inteiro para saber se a lista esta vazia - 1 para verdadeiro e 0 para falso
*/
int confereEmpty(void * L);

/*FUNÇÃO GET INFO
    !recebe: ponteiro da lista, node a querer a info
    !pré-condição: lista existente, node atual na lista
    !retorna: info do node atual
*/
void* getInfo(void* l, void* current);

/*FUNÇÃO FREE LISTA
    !recebe: a lista 
    !pre-condição: lista existir
    !retorna: da free na lista, caso opt 1 da free na infromação dentro do Nó; caso opt 0 da free apenas no nó;
*/
void freeLISTA (void *l, int opt);
#endif