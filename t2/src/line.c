#include "line.h"

typedef struct 
{
    char com;
    int i;
    double x1;
    double y1;
    double x2;
    double y2;
    char cor[30];
    float protection_level;
}RETA;

void *createline(double i,double x1,double y1,double x2,double y2,char cor[30]){
    RETA *l=(RETA*)malloc(sizeof(RETA));
    //strcpy(l->com,"l");
    l->com = 'l';
    l->i=i;
    l->x1=x1;
    l->y1=y1;
    l->x2=x2;
    l->y2=y2;
    strcpy(l->cor,cor);
    l->protection_level = 50;
    printf("i %lf x1 %lf y1 %lf x2 %lf y2 %lf \n\n",i, x1, y1,x2,y2);
    return(l);
    
}

int testeline(void *l){
    RETA *ll = (RETA*)l;
    
    if(ll->com=='l'){
        return(1);
    }
    else{
        return(0);
    }
}

void createSVGline(void *dataa, FILE *arquivo){
    double xl1,xl2,yl1,yl2;
    char corl[30];
    xl1=((RETA*)dataa)->x1;
    xl2=((RETA*)dataa)->x2;
    yl1=((RETA*)dataa)->y1;
    yl2=((RETA*)dataa)->y2;
    strcpy(corl,((RETA*)dataa)->cor);

    fprintf(arquivo, "\n\t<line x1=\" %lf \" x2=\" %lf \" y1=\" %lf \" y2=\" %lf \" stroke=\" %s \" />",xl1,xl2,yl1,yl2,corl);
}

char getComline ( void *l){
    char com = ((RETA*)l)->com;
    return (com);
}

double getX1line(void *l){
    double xx=((RETA*)l)->x1;
    return(xx);
}

double getY1line(void *l){
    double yy=((RETA*)l)->y1;
    return(yy);
}

double getX2line(void *l){
    double xx=((RETA*)l)->x2;
    return(xx);
}

double getY2line(void *l){
    double yy=((RETA*)l)->y2;
    return(yy);
}

double getIline(void *l){
    double ii = ((RETA*)l)->i;
    return(ii);
}

char *getCorline(void *l){
    return(((RETA*)l)->cor);
}

float getProtectLevelline (void *l){
  RETA *li = (RETA*)l;
  
  return(li->protection_level); 
}

FdentroDe lineRegiao (Info i, double x1, double y1 , double w, double h)
{
    double x1l = getX1line(i);
    double x2l = getX2line(i);
    double y1l = getY1line(i);
    double y2l  = getY2line(i);

    bool *interno = x1l>=x1 && x1l<=x1+w && y1l >= y1 && y1l <=y1+h && x2l>=x1 && x2l<=x1+w && y2l >= y1 && y2l <=y1+h; 
    
    return interno;
    
}

FatingidoPor lineHit (Info i, double x, double y)
{
    double x1l = getX1line(i);
    double x2l = getX2line(i);
    double y1l = getY1line(i);
    double y2l  = getY2line(i);
    double m;
    int num;

    if (x1l != x2l){
    m = (y2l - y1l)/(x2l - x1l); 
    }
    else{ 
    m=0;
    }
    double b = y1l - m*x1l;

    bool aux;

    if(x1l<x2l){
      double aux2 = x1l;
      x1l = x2l;
      x2l = aux2;
      aux2 = y1l;
      y1l = y2l;
      y2l = aux2;
    }

    if(x1l != x2l){
    for(num = x1l; num <= x2l; num++){
        aux = (m*num + b) == y;
        bool *ptr = &aux;
        if(aux){
            return ptr;
        }
    }
    }
    else{
      aux = y >= y1l && y <= y2l;
      bool *ptr = &aux;
      if(aux){
        return ptr;
      }
    } 
    bool *ptr;
    return ptr;

}
float getComprimentoline (void *l){
    int comprimentoX = ((RETA*)l)->x2-((RETA*)l)->x1;
    int comprimentoY = ((RETA*)l)->y2-((RETA*)l)->y1;
    float aux = comprimentoX^2 + comprimentoY^2;

    float comprimento = sqrt(aux);
    return(comprimento);
}

int degradaLine(void *l,int v,int region){
    float comprimento = getComprimentoline(l);
    int areaL = 0.1 * comprimento;
    int reducao=v*areaL/region;

    ((RETA*)l)->protection_level = ((RETA*)l)->protection_level - reducao;

    int report = ((RETA*)l)->protection_level;
    return(report);
}