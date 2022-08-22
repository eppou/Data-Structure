#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Tree.h"

void *createrectangle(double,double,double,double,double,char[],char[]);
int testeRetangulo (void *);
void createSVGrectangle(void *,FILE*);
double getXrectangle(void *);
double getYrectangle(void *);
char getComrectangle ( void *);
double getIrectangle(void *);
double getHrectangle(void *);
double getWrectangle(void *);
char *getCorbrectangle(void *);
char *getCorprectangle(void *);
float getProtectLevelrectangle (void *);
bool rectangleRegiao (Info i, double x1, double y1 , double x2, double y2);
bool rectangleHit (Info i, double x, double y);
double getArearectangle (void *);
int degradaRectangle (void *,int ,int);
void changeRectangle(void*,double,double,char[],char[]);

#endif
