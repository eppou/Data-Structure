#include "Tree.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "text.h"

typedef struct root_tree{
  double fd;
  struct Node_tree *root;
  int size_tree;
  int size_tree_r;
}tree_struc;

typedef struct Node_tree{
  void *data; 
  double x;
  double y;
  struct Node_tree *parent;
  struct Node_tree *left;
  struct Node_tree *center;
  struct Node_tree *right;
  char targetremoved; //n para não removido e s para removido
}node_tree;


XyyTree newXyyTree(double Fd) 
{
  tree_struc *new_tree = (tree_struc*)malloc(sizeof(tree_struc));
  new_tree->root = NULL;
  new_tree->size_tree = 0;
  new_tree->size_tree_r = 0;
  new_tree->fd = Fd; 
  
  return new_tree;
}


Node insertXyyT(XyyTree tree, double x, double y, Info info)
{
    tree_struc *tree_aux = (tree_struc*)tree;
    node_tree **aux = &tree_aux->root;

    node_tree *node = (node_tree*)malloc(sizeof(node_tree));

      node->data = info;
      node->x= x;
      node->y = y;
      node->parent = NULL;
      node->left = NULL;
      node->right = NULL;
      node->center = NULL;
      node->targetremoved = 'n';

  if(tree_aux->root == NULL) // inserir na raiz
  {
    tree_aux->root = node;
  }
  else{
    while(*aux)
    {
      node->parent = *aux;
      if(y < (*aux)->y)
      {
        aux = &(*aux)->left;
      }
      else if(y >= (*aux)->y)
      {
        if(x < (*aux)->x)
        {
          aux = &(*aux)->center;
        }
        else if(x >= (*aux)->x)
        {
          aux = &(*aux)->right;
        }
       }
      }
     }
    *aux = node;
    tree_aux->size_tree++;

}

Node getNodeXyyT (XyyTree t, double x, double y, double epsilon){

  tree_struc *tree_aux = (tree_struc*)t;
  node_tree **aux = &tree_aux->root;

  while(*aux)
    {
      if(((*aux)->x - x < epsilon && (*aux)->y - y < epsilon && x - (*aux)->x <epsilon && y - (*aux)->y < epsilon)|| aux==NULL)
      {
        return *aux;
      }
      else if(y < (*aux)->y)
      {
        aux = &(*aux)->left;
      }
      else if(y >= (*aux)->y)
      {
        if(x < (*aux)->x)
        {
          aux = &(*aux)->center;
        }
        else if(x >= (*aux)->x)
        {
          aux = &(*aux)->right;
        }
       }
    }
      

  return NULL;
  
}

Info getInfoXyyT (XyyTree t, Node n)
{
  node_tree *aux = (node_tree*)n;
  return aux->data;
}

bool nodeinsideAux (Info i, double x1, double y1,double x2, double y2)
{
    
    if(testaCirculo(i) == 1)
    {
      return circleRegiao(i,x1,y1,x2,y2);
    }
    else if(testeRetangulo(i) == 1)
    {
      return rectangleRegiao(i,x1,y1,x2,y2);
    }
    else if(testeline(i) == 1)
    {   
      return lineRegiao(i,x1,y1,x2,y2);
    }
    else if(testetext(i) == 1)
    {
      return textRegiao(i,x1,y1,x2,y2);
    }
   
}

void nodeinside(node_tree *node,Lista lista,double x1, double y1, double x2, double y2){
  if(node ==NULL)
  {
    return;
  }

  void *figura = node->data;

  if(nodeinsideAux(figura,x1,y1,x2,y2)){
    void *nodeptr = node;
    lista_inserenofim(lista,nodeptr);
  }
  nodeinside(node->left,lista,x1,y1,x2,y2);
  nodeinside(node->center,lista,x1,y1,x2,y2);
  nodeinside(node->right,lista,x1,y1,x2,y2);
  
}

Lista getNodesDentroRegiaoXyyT (XyyTree t, double x1, double y1, double w, double h) // NAO SEI SE FUNCIONA
{
  tree_struc *tree_aux = (tree_struc*)t;
  node_tree *aux = tree_aux->root;
  Lista lista = inicia();
  nodeinside(aux,lista,x1,y1,w,h);
  return lista; 
}

void figureinside(node_tree *node, double x1,double y1,double x2, double y2,FdentroDe f,Lista list)
{ 
  if(node ==NULL)
  {
    return;
  }
    
  else{

    if(f(node->data,x1,y1,x2,y2)){
      lista_inserenofim(list,node->data);
    }
      figureinside(node->left,x1,y1,x2,y2,f,list);
      figureinside(node->center,x1,y1,x2,y2,f,list);
      figureinside(node->right,x1,y1,x2,y2,f,list);
  }

}

Lista getInfosDentroRegiaoXyyT (XyyTree t, double x1, double y1, double x2, double y2, FdentroDe f)
{
  tree_struc *tree_aux = (tree_struc*)t;
  node_tree *aux = tree_aux->root;
  Lista lista = inicia();
  figureinside(aux,x1,y1,x2,y2,f,lista);
  return lista;
}

void figurehit(XyyTree t,node_tree *node , double x, double y, Lista list,FatingidoPor f)
{
  tree_struc *tree = (tree_struc*)t;
   if(node ==NULL)
  {
    return;
  }
    else{

    if(f(node->data,x,y)){
      lista_inserenofim(list,node->data);
   }
    figurehit(tree,node->left,x,y,list,f);
    figurehit(tree,node->center,x,y,list,f);
    figurehit(tree,node->right,x,y,list,f);
   }
}  

Lista getInfosAtingidoPontoXyyT (XyyTree t, double x, double y, FatingidoPor f) 
{
  tree_struc *tree_aux = (tree_struc*)t;
  node_tree *aux = tree_aux->root;
  Lista lista = inicia();
  figurehit(tree_aux,aux,x,y,lista,f);
  return lista;
} 


FvisitaNo contaNoRemovido (Info i,double x,double y,void *aux){
  int *nRemoved= (int*)aux;
  if(((node_tree*)i)->targetremoved=='s'){
    nRemoved++; //incremento
  }
  aux = nRemoved;
  return(aux);
}


FvisitaNo printaNodeTree (Info i,double x,double y, void *aux){
}

void visitaPaux(node_tree *node, FvisitaNo f, void *aux){
  if(node ==NULL)
  {
    return;
  }

  else{
    
    if(node->targetremoved !='s'){
    f(node,node->x,node->y,aux);
    }
    visitaPaux(node->left,f,aux);

    visitaPaux(node->center,f,aux);

    visitaPaux(node->right,f,aux);
    
    

  }
}

void visitaProfundidadeXyyT (XyyTree t, FvisitaNo f, void *aux)
{

  tree_struc *tree= (tree_struc*)t;
  node_tree *auxNode = tree->root;
  visitaPaux(auxNode,f,aux);

}

void visitaLaux(node_tree *node,FvisitaNo f,void *aux){

int ind;
for(ind=0;ind<3;ind++){
  if(ind==0 && node->left!=NULL && node->targetremoved !='s'){
    f(node->left,node->left->x,node->left->y,aux);
  }

  if(ind==1 && node->center!=NULL && node->targetremoved !='s'){
    f(node->center,node->center->x,node->center->y,aux);
  }

  if(ind==2 && node->right!=NULL && node->targetremoved !='s'){
    f(node->right,node->right->x,node->right->y,aux);
  }
}

}

void visitaLaux2(node_tree *node,FvisitaNo f,void *aux){
   if(node->left!=NULL){
    visitaLaux(node->left,f,aux);
  }
  if(node->center!=NULL){
    visitaLaux(node->center,f,aux);
  }
  if(node->right!=NULL){
    visitaLaux(node->right,f,aux);
  }

  if(node->left!=NULL){
    visitaLaux2(node->left,f,aux);
  }
  if(node->center!=NULL){
    visitaLaux2(node->center,f,aux);
  }
  if(node->right!=NULL){
    visitaLaux2(node->right,f,aux);
  }
}

void visitaLarguraXyyT (XyyTree t, FvisitaNo f, void *aux){
  tree_struc *tree= (tree_struc*)t;
  node_tree *auxNode = tree->root;
  
  f(auxNode,auxNode->x,auxNode->y,aux);
  
  visitaLaux(auxNode,f,aux);
  visitaLaux2(auxNode,f,aux);
} 

void freeXyyt(XyyTree tree_ref,Node node)
{
  tree_struc *t = (tree_struc*)tree_ref;
  node_tree *no = (node_tree*)node;
  if(no ==NULL)
  {
    return;
  }
  else{
    freeXyyt(t,no->left);

    freeXyyt(t,no->center);

    freeXyyt(t,no->right);

    free(no);
  }
}

typedef struct RemoveAssistent{
  node_tree vetorN[15];
  tree_struc *oldt;
  tree_struc *t;
  int indiceAUX;
}RA;

int Identificaparentesco(node_tree *n){
  if(n==NULL || n->parent==NULL){
    return -1;
  }
  node_tree *pai = n->parent;
  if(pai->left==n){
    return(1);
  }
  if(pai->center==n){
    return(2);
  }
  if(pai->right==n){
    return(3);
  }

}
//---------------------------------------------------FUNÇÃO QUICK SORT------------------------------------------------------------------------------------
void quick_sort(node_tree a[], int left, int right) {
    int i, j, y;
    int x;
    i = left;
    j = right;
    x = a[(left + right) / 2].x;
    while(i <= j) {
        while(a[i].x < x && i < right) {
            i++;
        }
        while(a[j].x > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i].x;
            a[i].x = a[j].x;
            a[j].x = y;
            i++;
            j--;
        }
    }
    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}

//-------------------------------------------------------------------------------FUNÇÃO VISITA NÓ PARA REMOÇÃO--------------------------------------------------------------------
void OrdenaeInsere (Info i,double x,double y,void *aux){
 RA *ra = (RA*)aux;
 node_tree *auxNode = (node_tree*)i;
 tree_struc *tree = ((RA*)aux)->t;
 int ind,indAux = ra->indiceAUX;

 if(auxNode->targetremoved!='s')
 {

  if(ra->indiceAUX<15){
    ra->vetorN[indAux]= *(node_tree*)i;
    indAux++;
    quick_sort(ra->vetorN,0,indAux);

    if(tree->size_tree<15){
      if(indAux==tree->size_tree){
        for(ind=0;ind<indAux;ind++){
          node_tree element = ra->vetorN[ind];
          insertXyyT(tree,element.x,element.y,element.data);
        }
      }
    }

    else if(indAux==15){
      for (ind=0;ind<15;ind++){
        node_tree element = ra->vetorN[ind];
        insertXyyT(tree,element.x,element.y,element.data);
        indAux++;
      }
    }

  }

  else{
    insertXyyT(tree,auxNode->x,auxNode->y,auxNode->data);
    indAux++;
  }

  ra->indiceAUX = indAux;
 }

  if(indAux-1==ra->oldt->size_tree-ra->oldt->size_tree_r){
    tree_struc *velhaArvore = ra->oldt;
    ra->oldt = ra->t; 
    freeXyyt(velhaArvore,velhaArvore->root);
  }


}

//-----------------------------------------------------------------------------------------FUNÇÃO REMOVE---------------------------------------------------------------------
void removeNoXyyT (XyyTree t, Node n)
{
  if(n==NULL){
    return;
  }
  
  node_tree *nn = (node_tree*)n;
  tree_struc *tt= (tree_struc*)t;
  node_tree *left = nn->left;
  node_tree *center = nn->center;
  node_tree *right = nn->right;

  int auxint = Identificaparentesco(nn); //ELEEEE NÃO É O PAIII, ratinhooooo


  switch (auxint)
  {
    case 1:;
      if (left==NULL&&center==NULL&&right==NULL){
        nn->parent->left = NULL;
        free(nn->data);
        free(nn);
      } 

      else 
      {
        if(left!=NULL&&center==NULL&&right==NULL){
          nn->left->parent = nn->parent;
          nn->parent->left = nn->left;
          free(nn->data);
          free(nn);
        }
        if(left==NULL&&center!=NULL&&right==NULL){
          nn->center->parent = nn->parent;
          nn->parent->left = nn->center;
          free(nn->data);
          free(nn);
        }
        if(left==NULL&&center==NULL&&right!=NULL){
          nn->right->parent = nn->parent;
          nn->parent->left = nn->right;
          free(nn->data);
          free(nn);
        }

        if(left!=NULL&&right!=NULL||left!=NULL&&center!=NULL||center!=NULL&&right!=NULL){
          nn->targetremoved = 's';
          tt->size_tree_r = tt->size_tree_r + 1;
          int AUXfd = tt->size_tree_r/tt->size_tree;

          if (AUXfd > tt->fd){
            tree_struc *newT = newXyyTree(tt->fd);
            

            RA *ra=(RA*)malloc(sizeof(RA));
            ra->t = newT;
            ra->oldt = tt;
            ra->indiceAUX = 0;
            
            void *voidRa = &ra;
            visitaLarguraXyyT(tt,OrdenaeInsere,voidRa);
          } 
        }
      }

    break;

    case 2:;
      if (left==NULL&&center==NULL&&right==NULL){
        nn->parent->center = NULL;
        free(nn->data);
        free(nn);
      } 

      else 
      {
        if(left!=NULL&&center==NULL&&right==NULL){
          nn->left->parent = nn->parent;
          nn->parent->center = nn->left;
          free(nn->data);
          free(nn);
        }
        if(left==NULL&&center!=NULL&&right==NULL){
          nn->center->parent = nn->parent;
          nn->parent->center = nn->center;
          free(nn->data);
          free(nn);
        }
        if(left==NULL&&center==NULL&&right!=NULL){
          nn->right->parent = nn->parent;
          nn->parent->center = nn->right;
          free(nn->data);
          free(nn);
        }

        if(left!=NULL&&right!=NULL||left!=NULL&&center!=NULL||center!=NULL&&right!=NULL){
          nn->targetremoved = 's';
          tt->size_tree_r = tt->size_tree_r + 1;
          int AUXfd = tt->size_tree_r/tt->size_tree;

          if (AUXfd > tt->fd){
            tree_struc *newT = newXyyTree(tt->fd);
            

            RA *ra=(RA*)malloc(sizeof(RA));
            ra->t = newT;
            ra->oldt = tt;
            ra->indiceAUX = 0;
            
            void *voidRa = &ra;
            visitaLarguraXyyT(tt,OrdenaeInsere,voidRa);
          } 
        }
      }

    break;

    case 3:;
      if (left==NULL&&center==NULL&&right==NULL){
        nn->parent->right = NULL;
        free(nn->data);
        free(nn);
      } 

      else 
      {
        if(left!=NULL&&center==NULL&&right==NULL){
          nn->left->parent = nn->parent;
          nn->parent->right = nn->left;
          free(nn->data);
          free(nn);
        }
        if(left==NULL&&center!=NULL&&right==NULL){
          nn->center->parent = nn->parent;
          nn->parent->right = nn->center;
          free(nn->data);
          free(nn);
        }
        if(left==NULL&&center==NULL&&right!=NULL){
          nn->right->parent = nn->parent;
          nn->parent->right = nn->right;
          free(nn->data);
          free(nn);
        }

        if(left!=NULL&&right!=NULL||left!=NULL&&center!=NULL||center!=NULL&&right!=NULL){
          nn->targetremoved = 's';
          tt->size_tree_r = tt->size_tree_r + 1;
          int AUXfd = tt->size_tree_r/tt->size_tree;

          if (AUXfd > tt->fd){
            tree_struc *newT = newXyyTree(tt->fd);
            

            RA *ra=(RA*)malloc(sizeof(RA));
            ra->t = newT;
            ra->oldt = tt;
            ra->indiceAUX = 0;
            
            void *voidRa = &ra;
            visitaLarguraXyyT(tt,OrdenaeInsere,voidRa);
          } 
        }
      }

    break;

    default:
      nn->targetremoved = 's';
      tt->size_tree_r = tt->size_tree_r + 1;

    break;
  }
}
//-------------------------------------------DESTROI TREEXyyt--------------------------------------------------//

void percorreRemoveAUX(node_tree *node, FvisitaNo f, void *aux){
  if(node ==NULL)
  {
    return;
  }

  else{
    
    percorreRemoveAUX(node->left,f,aux);

    percorreRemoveAUX(node->center,f,aux);

    percorreRemoveAUX(node->right,f,aux);
    

    f(node,node->x,node->y,aux);

  }
}

void percorrePraRemover(XyyTree t, FvisitaNo  f , void *aux)
{

  tree_struc *tree= (tree_struc*)t;
  node_tree *auxNode = tree->root;
  percorreRemoveAUX(auxNode,f,aux);

}

void destroiNOtree (Info i,double x,double y,void *aux){
  free(((node_tree*)i)->data);
  free(i);
}

void DestroiXyyT (XyyTree t){
  void *aux;
  percorrePraRemover(t,destroiNOtree,aux);
  free(t);
}

//-------------------------------------------------DumpTree----------------------------------------//

void PrintFiguraTXT(void *figura,FILE* txt)
{
  if(testaCirculo(figura) == 1)
    {
      fprintf(txt,"[id: %0.2lf] x: %0.2lf y: %0.2lf tipo: CIRCULO cor borda: %s cor preenchimento: %s\n",getIcircle(figura),getXcircle(figura),getYcircle(figura),getCorbcircle(figura),getCorpcircle(figura));
    }
  else if(testeRetangulo(figura) == 1)
    {
      fprintf(txt,"[id: %0.2lf] x: %0.2lf y: %0.2lf tipo: RETANGULO cor borda: %s cor preenchimento: %s\n",getIrectangle(figura),getXrectangle(figura),getYrectangle(figura),getCorbrectangle(figura),getCorprectangle(figura));
    }
  else if(testeline(figura) == 1)
    {   
      fprintf(txt,"[id: %0.2lf] x: %0.2lf y: %0.2lf tipo: LINHA cor: %s\n",getIline(figura),getX1line(figura),getY1line(figura),getCorline(figura));
    }
  else if(testetext(figura) == 1)
    {
      fprintf(txt,"[id: %0.2lf] x: %0.2lf y: %0.2lf tipo: TEXTO cor borda: %s cor preenchimento: %s\n",getItext(figura),getXtext(figura),getYtext(figura),getCorbtext(figura),getCorptext(figura));
    }
}

void printTreeTXT(node_tree *no,FILE *txt,int margem){
    int i;
    for(i=0;i<margem;i++)
    {
      fprintf(txt," ");
    }

    if(no->targetremoved== 's')
    {
      fprintf(txt," REMOVIDO: x = %lf y = %lf",no->x,no->y);
    }
    else
    {
      PrintFiguraTXT(no->data,txt);
    }
}

void dumpTreeAux(node_tree *No,FILE* txt,int m){

    if(No == NULL){
      return;
    }

    printTreeTXT(No,txt,m);

    if (No != NULL){
      dumpTreeAux(No->left, txt, m + 2);
    }

    if (No != NULL) {
      dumpTreeAux(No->center, txt, m + 2);
    }

    if (No != NULL) {
      dumpTreeAux(No->right, txt, m + 2);
    }

}

void dumpTree(XyyTree t,FILE *txt)
{
  tree_struc* tree = (tree_struc*)t;
  node_tree *aux= tree->root;
  int m =0;
  fprintf(txt,"\nNº de nós: %d\nNº marcados como removidos: %d\nFator de degradação: %0.2lf\n",tree->size_tree,tree->size_tree_r,tree->fd);
  dumpTreeAux(aux,txt,m);
}