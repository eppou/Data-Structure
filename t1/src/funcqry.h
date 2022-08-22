#ifndef FUNCQRY_H
#define FUNCQRY_H
#include "Tree.h"
#include "circle.h"
#include "rectangle.h"
#include "text.h"
#include "path.h"
#include "line.h"
#include "svg.h"
#include "fila.h"

bool figureRegiao (Info , double , double ,double , double );

bool figureatingido (Info , double , double );

void funcINP(float ,XyyTree ,Fila ,FILE *);
void funcRMP(Fila ,FILE *);
void funcCLP (Fila );
Lista funcSEL (double , double , double ,double ,XyyTree ,Lista ,FILE*,FILE*);
void funcSELplus(double , double , double ,double ,XyyTree ,Lista, FILE*,FILE*);
Lista funcDELS(XyyTree ,Lista, FILE* );
void funcPOL(float , float ,float ,char[] ,char[] ,Fila ,XyyTree );
void funcDPS(float ,double , double ,char [],char[] ,XyyTree ,Lista );
void funcUPS(char corb[],char corp[],double ,double ,float ,Lista ,XyyTree );
void readQRY(XyyTree ,double,Path,Fila,Lista);

#endif