#include "svg.h"
#include "circle.h"
#include "rectangle.h"
#include "text.h"
#include "line.h"


FvisitaNo writeSVG (Info i,double x,double y,void *aux){
  
  void *figure = getInfoXyyT(aux,i);

  if(testaCirculo(figure) == 1){
        createSVGcircle(figure,aux);
  }

  if(testeRetangulo(figure) == 1){
        createSVGrectangle(figure,aux);
  }

  if(testeline(figure) == 1){
        createSVGline(figure,aux);
  }

  if(testetext(figure) == 1){
        createSVGtext(figure,aux);
  }
}

void openTagSVG (FILE *arquivo)
{
    fprintf(arquivo,"<svg xmlns=\"http://www.w3.org/2000/svg\">"); 
}

void writeTree (FILE *arquivo,XyyTree t)
{
    void *arq = arquivo;
    visitaProfundidadeXyyT(t,writeSVG,arq);

}

void closeTagSVG (FILE *arquivo)
{
    fprintf(arquivo,"\n</svg>");
}