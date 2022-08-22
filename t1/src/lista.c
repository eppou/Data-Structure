#include "lista.h"


typedef struct node_t {
  void *data;
  struct node_t *prev;
  struct node_t *next;
  char sel[2]; //char para definir se o elemento esta ou não selecioonado
} no_lista;


typedef struct {
  int size;
  no_lista *first;
  no_lista *last;
} lista_deg;

Lista inicia() 
{
  lista_deg *list = (lista_deg *)malloc(sizeof(lista_deg));
  if(list==NULL){
    return NULL;
  }
  list->size = 0;
  list->first = NULL;
  list->last = NULL;
  return list;
}

void *inicia_no(void *data) 
{
  no_lista *node = (no_lista*)malloc(sizeof(no_lista));
  node->data = data;
  node->prev = NULL;
  node->next = NULL;
  strcpy(node->sel,"n");
  return (node);
}


void *procura_no(void *lista, int pos) 
{
  lista_deg *list = (lista_deg*)malloc(sizeof(lista_deg));
  list = (lista_deg*)lista;
  if(pos > list->size)
    return NULL;  

  no_lista *currNode;
  int currPos;
  int reverse; 
 
  if(pos > ((list->size-1) / 2)) {
    reverse  = 1;
    currPos  =  list->size - 1;
    currNode =  list->last;
  } else {
    reverse  = 0;
    currPos  = 0;
    currNode =  list->first;
  }  
  while(currNode != NULL) {
  

    if(currPos==pos){
      break;
    }
    if(reverse==1){
      currNode=currNode->prev;
      currPos= currPos-1;
    }
    if(reverse==0){
      currNode=currNode->next;
      currPos= currPos+1;
    }
  }
  void *ptrCurrNode;
  ptrCurrNode=currNode;
  return (ptrCurrNode);
}

void *aux_remove(void *list, int pos) 
{
  void *currNode = procura_no(list, pos);
  void *data = NULL;

  if(currNode == NULL)
    return NULL;

  data = ((no_lista*)currNode)->data;

  if(((no_lista*)currNode)->prev == NULL) 
     ((lista_deg*)list)->first = ((no_lista*)currNode)->next;
  else {
    ((no_lista*)currNode)->prev->next = ((no_lista*)currNode)->next;
  }
  if(((no_lista*)currNode)->next == NULL)
    ((lista_deg*)list)->last = ((no_lista*)currNode)->prev; 
  else
    ((no_lista*)currNode)->next->prev = ((no_lista*)currNode)->prev;

   ((lista_deg*)list)->size--;
  free(currNode);
  return(data);
}

int lista_inserenofim(void *list, void *data) 
{
  /* inicia um novo nó */
  void *newNode = inicia_no(data);

  /* se a lista está vazia */
  if( ((lista_deg*)list)->size == 0) {
     ((lista_deg*)list)->first = (no_lista*)newNode;
  } 
  else {
  
     ((lista_deg*)list)->last->next = (no_lista*)newNode;
    ((no_lista*)newNode)->prev =  ((lista_deg*)list)->last;
  }
   ((lista_deg*)list)->last = (no_lista*)newNode;
   ((lista_deg*)list)->size++;
  return 0;
}




void *lista_pop(void *list) 
{
  if(!list)
    return NULL;

  no_lista *node = ((lista_deg*)list)->first;
  if(node == NULL)
    return NULL;

  void *data = node->data;

  if(aux_remove(list, 0) == NULL)
    return NULL;

  return data;
}

int returnlistsize(void *lista){
  return(((lista_deg*)lista)->size);
}

void *returnData (void *list,int pos){
  void *ptrCurrNode;
  ptrCurrNode = procura_no(list,pos);
  void *ptrCurrNodeData;
  ptrCurrNodeData= ((no_lista*)ptrCurrNode)->data;
  return (ptrCurrNodeData);
}

void* getBegin(void* listacurrent){
    lista_deg* listAux = (lista_deg*)listacurrent;
    
    if (listAux->size == 0 || listAux->first == NULL)
        return NULL;
    else
    return listAux->first;

}

void* getNext(void* listacurrent, void* current){
    lista_deg* listAux = (lista_deg*)listacurrent;
    no_lista* aux = (no_lista*)current; 

    if(aux == NULL){
        return NULL;
    }else{
        return aux->next;
    }
}

void* getLast(void* lista){
  if(lista!=NULL){
  void *lastnode = ((lista_deg*)lista)->last;
  return lastnode;
  }
  else{
    printf("vc me passou um ponteiro nulo na função getLast");
  }
}

void* getPrev(void* listacurrent, void* current){
  no_lista *aux = (no_lista*)current;

  if(aux==NULL){
    return NULL;
  }
  else{
    return aux->prev;
  }
}

int confereEmpty(void * L)
{
    lista_deg *L1 = (lista_deg*)L;
    if(L1->size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void* getInfo(void* l, void* current){
    if(l == NULL){
        return NULL;
    }
    if(current == NULL){
       return NULL;
    }

    no_lista *NODE = (no_lista*) current;
    return NODE->data;
}

void freeLISTA (void *l, int opt){
  if(((lista_deg*)l)->first !=NULL){
  no_lista *OldNo = ((lista_deg*)l)->first;
  no_lista *currentNo ;
  if(opt==0){
    while(OldNo!=NULL){
      no_lista *currentNo = OldNo->next;
      free(OldNo);
      OldNo = currentNo;
    }
  }
  else if(opt==1){
    while(OldNo!=NULL){
      no_lista *currentNo = OldNo->next;
      free(OldNo->data);
      free(OldNo);
      OldNo = currentNo;
    }
  }
  }
  free(l);  
}