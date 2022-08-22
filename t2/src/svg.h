#ifndef SVG_H
#define SVG_H
#include "Tree.h"

void openTagSVG (FILE *);
void writeTree (FILE *,XyyTree );
void closeTagSVG (FILE *);

#endif

