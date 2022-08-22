#include "circle.h"

typedef struct circle
{
    char com;
    float i;
    double x;
    double y;
    double r;
    char corb[30];
    char corp[30];
    float protection_level;
}CIRCULO;

void *createCircle(double i,double x,double y, double r,char corb[30], char corp[30]){
    CIRCULO *cc= (CIRCULO*)malloc(sizeof(CIRCULO));
    //strcpy(cc->com,"c");
    cc->com = 'c';
    cc->i=i;
    cc->x=x;
    cc->y=y;
    cc->r=r;
    strcpy(cc->corb,corb);
    strcpy(cc->corp,corp);
    cc->protection_level = 60;
  
    return(cc);
}

int testaCirculo(void *c){
  CIRCULO *cc= (CIRCULO*)c;
 
  if(cc->com=='c'){
    return (1);
  }
  else{
    return(0);
  }
}

void createSVGcircle(void *dataa, FILE *arquivo){
  double xc,yc,rc;
  char corbc[30],corpc[30];
  xc=((CIRCULO*)dataa)->x;
  yc=((CIRCULO*)dataa)->y;
  rc=((CIRCULO*)dataa)->r;
  strcpy(corbc,((CIRCULO*)dataa)->corb);
  strcpy(corpc,((CIRCULO*)dataa)->corp);
  fprintf(arquivo, "\n\t<circle cx=\"%lf\" cy=\" %lf \" r=\" %lf \" stroke=\" %s \" stroke-width=\" 1 \" fill=\" %s \" opacity=\" 1 \"/>",xc,yc,rc,corbc,corpc);
        
}

char getComcircle ( void *c){
    char com = ((CIRCULO*)c)->com;
    return (com);
}

double getXcircle(void *c){
  double xx=((CIRCULO*)c)->x;
  return(xx);
}

double getYcircle(void *c){
  double yy=((CIRCULO*)c)->y;
  return(yy);
}

double getIcircle(void *c){
  double ii = ((CIRCULO*)c)->i;
  return (ii);
}

double getRcircle(void *c){
  double rr = ((CIRCULO*)c)->r;
  return(rr);
}

char *getCorbcircle(void *c){
    return(((CIRCULO*)c)->corb);
}

char *getCorpcircle(void *c){
    return(((CIRCULO*)c)->corp);
}

float getProtectLevelcircle (void *c){
  float cPL = ((CIRCULO*)c)->protection_level;
  return(cPL); 
}

bool circleRegiao (Info i, double x1, double y1 , double w, double h)
{
    double rc = getRcircle(i);
    double xc = getXcircle(i);
    double yc = getYcircle(i);

    bool interno = ((xc-rc) >= x1) && ((xc+rc) <= x1+w) && (yc-rc) >= y1 && ((yc +rc) <= y1+h);

    return interno;
    
}

bool circleHit (Info i, double x, double y)
{
    double rc = getRcircle(i);
    double xc = getXcircle(i);
    double yc = getYcircle(i);

    bool hit = (xc + rc) >= x && (xc - rc) <= x && (yc + rc) >= y && (yc - rc) <= y;

    return hit;   
}

///////////////////////FUNÇÂO NOVA
void *translatedCircle(void *c, double dx, double dy,double id){

    CIRCULO *p = (CIRCULO*)c;
    createCircle(id,dx,dy, p->r, p->corb, p->corp);
    return(p);
}

double getAreacircle (void *c){
  double raio = ((CIRCULO*)c)->r;

  double area = 3*(int)raio^2;
  return (area);
}

int degradaCircle (void *c,int v,int region){
    int areacirculo = getAreacircle(c);
    int reducao = v*areacirculo/region;
    ((CIRCULO*)c)->protection_level = ((CIRCULO*)c)->protection_level - reducao;

    int report = ((CIRCULO*)c)->protection_level;
    return (report);
}

void changeCircle(void *c,double dx,double dy,char corb[30],char corp[30]){
  ((CIRCULO*)c)->x = ((CIRCULO*)c)->x + dx;
  ((CIRCULO*)c)->y = ((CIRCULO*)c)->y + dy;
  strcpy(((CIRCULO*)c)->corb,corb);
  strcpy(((CIRCULO*)c)->corp,corp);
}