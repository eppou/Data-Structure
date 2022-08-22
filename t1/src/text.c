#include "text.h"

typedef struct
{
    char com;
    int i;
    double x;
    double y;
    char corb[30];
    char corp[30];
    char a;
    char texto[300];
    float protection_level;
}TEXTO;

void *createText(double i, double x,double y,char corb[30],char corp[30],char a,char texto[100]){
    TEXTO *tt=(TEXTO*)malloc(sizeof(TEXTO));
    //strcpy(tt->com,"t");
    tt->com = 't';
    tt->i=i;
    tt->x=x;
    tt->y=y;
    strcpy(tt->corb,corb);
    strcpy(tt->corp,corp);
    tt->a = a;
    strcpy(tt->texto,texto);
    tt->protection_level = 5;

    return(tt);
}

int testetext(void *t){
    TEXTO *tt = (TEXTO*)t;

    if(tt->com=='t'){
        return(1);
    }
    else{
        return(0);
    }

}

void createSVGtext(void *dataa,FILE *arquivo){
    double xt,yt;
    char corbt[30],corpt[30],texto[300];
    xt=((TEXTO*)dataa)->x;
    yt=((TEXTO*)dataa)->y;
    strcpy(corbt,((TEXTO*)dataa)->corb);
    strcpy(corpt,((TEXTO*)dataa)->corp);
    strcpy(texto,((TEXTO*)dataa)->texto);
    fprintf(arquivo, "\n\t<text x=\" %lf \" y=\" %lf \" style=\" font-size: 6px; font-style: normal; font-weight: normal; fill: %s; fill-opacity: 1; stroke: %s; stroke-width: 1px; stroke-opacity: 1; paint-order: stroke fill;\"><tspan x=\"%lf\" y=\"%lf\">%s</tspan></text>",xt,yt,corpt,corbt,xt,yt,texto);
}

double getXtext(void *t){
    double xx= ((TEXTO*)t)->x;
    return(xx);
}

double getYtext(void *t){
    double yy= ((TEXTO*)t)->y;
    return(yy);
}

char getComtext ( void *t){
    char com = ((TEXTO*)t)->com;
    return (com);
}

double getItext ( void *t){
    double ii = ((TEXTO*)t)->i;
    return (ii);
}

char *getCorbtext(void *t){
    return(((TEXTO*)t)->corb);
}

char *getCorptext(void *t){
    return(((TEXTO*)t)->corp);
}

char getAtext (void *t){
    char aa = ((TEXTO*)t)->a;
    return(aa);
}

char *getTextotext (void *t){
    return(((TEXTO*)t)->texto);
}

float getProtectLeveltext (void *t){
  float tPL = ((TEXTO*)t)->protection_level;
  return(tPL); 
}

bool textRegiao (Info i, double x1, double y1 , double w, double h)
{
    double xt = getXtext(i);
    double yt = getYtext(i);

    bool interno = x1<= xt && xt<=x1+w && y1 <= yt && yt<=y1+h;
    
    return interno;
    
} 


bool textHit (Info i, double x, double y)
{
    double xt = getXtext(i);
    double yt = getYtext(i);

    bool hit = xt <= x && x <= (xt + strlen(getTextotext(i))) && yt == y; 

    return hit;
}

int degradaText (void *t,int v,int region){
    float areaT = 0.1;
    float reducao= v*areaT/region;
    ((TEXTO*)t)->protection_level = ((TEXTO*)t)->protection_level - reducao;
    
    int report = ((TEXTO*)t)->protection_level;
    return(report);

}

void changeText(void *t,double dx,double dy,char corb[30],char corp[30]){
  ((TEXTO*)t)->x = ((TEXTO*)t)->x + dx;
  ((TEXTO*)t)->y = ((TEXTO*)t)->y + dy;
  strcpy(((TEXTO*)t)->corb,corb);
  strcpy(((TEXTO*)t)->corp,corp);
}