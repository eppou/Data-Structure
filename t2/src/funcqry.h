#ifndef FUNCQRY_H
#define FUNCQRY_H
#include "Tree.h"
#include "circle.h"
#include "rectangle.h"
#include "text.h"
#include "circle.h"
#include "path.h"
#include "line.h"
#include "svg.h"

FdentroDe figureRegiao (Info , double , double ,double , double );

FatingidoPor figureatingido (Info , double , double );

void funcNA (int,Path);

void funcTP(XyyTree ,double ,double ,double,FILE *,Path);

void funcTR(XyyTree ,double ,double , double , double , double, FILE*,Path);

void funcBE(XyyTree ,double ,double ,double , double ,double,FILE *,Path );

void readQRY(XyyTree ,double,Path);

#endif