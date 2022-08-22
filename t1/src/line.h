#ifndef LINE_H
#define LINE_H
#include "Tree.h"

void *createline(float,double,double,double,double,char[]);
int testeline(void *);
void createSVGline(void *,FILE*);
char getComline (void *);
double getX1line(void *);
double getY1line(void *);
double getX2line (void *);
double getY2line (void *);
float getIline (void *);
char *getCorline (void *);
float getProtectLevelline (void *);
bool  lineRegiao (Info i, double x1, double y1 , double x2, double y2);
bool  lineHit (Info i, double x, double y);
float getComprimentoline (void *);
int degradaLine(void *,int ,int);
int X1orX2line (void *);
void changeLine(void*,double,double,char[],char[]);

#endif
