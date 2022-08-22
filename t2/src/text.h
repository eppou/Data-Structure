#ifndef TEXT_H
#define TEXT_H
#include "Tree.h"

void *createText(double,double,double,char[],char[],char,char[]);
int testetext(void *);
void createSVGtext(void *,FILE *);
double getXtext(void *);
double getYtext(void *);
char getComtext ( void *);
double getItext ( void *);
char *getCorbtext(void *);
char *getCorptext(void *);
char getAtext (void *);
char *getTextotext (void *);
float getProtectLeveltext (void *);
FdentroDe textRegiao (Info , double , double , double , double );
FatingidoPor textHit (Info , double , double );
int degradaText (void *,int ,int );

#endif
