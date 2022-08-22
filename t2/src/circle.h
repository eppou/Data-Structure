#ifndef CIRCLE_H
#define CIRCLE_H
#include "Tree.h"

void *createCircle(double,double,double,double,char[],char[]);
int testaCirculo(void *);
void createSVGcircle(void*,FILE *);
double getXcircle(void *);
double getYcircle(void *);
char getComcircle ( void *);
double getIcircle(void *);
double getRcircle(void *);
char *getCorbcircle(void *);
char *getCorpcircle(void *);
float getProtectLevelcircle (void *);
FdentroDe circleRegiao (Info i, double x1, double y1 , double x2, double y2);
FatingidoPor circleHit (Info i, double x, double y);
double getAreacircle (void *);
int degradaCircle (void *,int ,int );

#endif
