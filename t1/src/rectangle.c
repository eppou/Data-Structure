#include "rectangle.h"

typedef struct 
{
    char com;
    int i;
    double x;
    double y;
    double w;
    double h;
    char corb[30];
    char corp[30];
    float protection_level;
}RETANGULO;

void *createrectangle(double i,double x,double y,double w,double h, char corb[30],char corp[30]){
    RETANGULO *R=(RETANGULO*)malloc(sizeof(RETANGULO));
    //strcpy(R->com,"r");
    R->com = 'r';
    R->i=i;
    R->x=x;
    R->y=y;
    R->w=w;
    R->h=h;
    strcpy(R->corb,corb);
    strcpy(R->corp,corp);
    R->protection_level = 60;
    return(R);
}

int  testeRetangulo (void *r){
    RETANGULO *rr= (RETANGULO*)r;
   // rr=(RETANGULO*)r;
    if(rr->com=='r'){
        return(1);
    }
    else{
        return(0);
    }
}

void createSVGrectangle(void *dataa, FILE *arquivo){
        double xr,yr,wr,hr;
        char corbr[30],corpr[30];
        xr=((RETANGULO*)dataa)->x;
        yr=((RETANGULO*)dataa)->y;
        wr=((RETANGULO*)dataa)->w;
        hr=((RETANGULO*)dataa)->h;
        strcpy(corbr,((RETANGULO*)dataa)->corb);
        strcpy(corpr,((RETANGULO*)dataa)->corp);
        fprintf(arquivo, "\n\t<rect x=\" %lf \" y=\" %lf \" width=\" %lf \" height=\" %lf \" stroke=\" %s \" stroke-width=\" 1px \" fill=\" %s \" opacity=\" 1 \"/>",xr,yr,wr,hr,corbr,corpr);

}

double getXrectangle(void *r){
    double xx=((RETANGULO*)r)->x;
    return(xx);
}

double getYrectangle(void *r){
    double yy=((RETANGULO*)r)->y;
    return(yy);
}

char getComrectangle ( void *r){
    char com = ((RETANGULO*)r)->com;
    return (com);
}

double getIrectangle( void *r){
    double ii = ((RETANGULO*)r)->i;
    return (ii);
}

double getHrectangle(void *r){
    double hh=((RETANGULO*)r)->h;
    return(hh);
}

double getWrectangle(void *r){
    double ww=((RETANGULO*)r)->w;
    return(ww);
}

char *getCorbrectangle(void *r){
    return(((RETANGULO*)r)->corb);
}

char *getCorprectangle(void *r){
    return(((RETANGULO*)r)->corp);
}

float getProtectLevelrectangle (void *r){
  float rPL = ((RETANGULO*)r)->protection_level;
  return(rPL); 
}

bool rectangleRegiao (Info i, double x1, double y1 , double w, double h)
{
    double hr = getHrectangle(i);
    double wr = getWrectangle(i);
    double xr = getXrectangle(i);
    double yr = getYrectangle(i);

    bool interno = x1<=xr && y1<=yr && (xr+wr)<=x1+w && (yr+hr) <= y1+h;
    
    return interno;
    
}

bool rectangleHit (Info i, double x, double y)
{
    double hr = getHrectangle(i);
    double wr = getWrectangle(i);
    double xr = getXrectangle(i);
    double yr = getYrectangle(i);

    bool hit = xr <= x && x <= (xr + wr) && yr <= y && y <= (yr + hr);
    return hit;
}

double getArearectangle (void *r){
    double altura = ((RETANGULO*)r)->h;
    double largura = ((RETANGULO*)r)->w;

    double Area = altura/largura;
    return(Area);
}

int degradaRectangle (void *r,int v,int region){
    int areaR = getArearectangle(r);
    int reducao= v*areaR/region;
    ((RETANGULO*)r)->protection_level = ((RETANGULO*)r)->protection_level - reducao;
    
    int report = ((RETANGULO*)r)->protection_level;
    return(report);
}

void changeRectangle(void *r,double dx,double dy,char corb[30],char corp[30]){
  ((RETANGULO*)r)->x = ((RETANGULO*)r)->x + dx;
  ((RETANGULO*)r)->y = ((RETANGULO*)r)->y + dy;
  strcpy(((RETANGULO*)r)->corb,corb);
  strcpy(((RETANGULO*)r)->corp,corp);
}