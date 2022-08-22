#ifndef FUNCTIONSPATH_H_INCLUDED
#define FUNCTIONSPATH_H_INCLUDED
#include "bibliotecas.h"

void readArgv(int , char**,Path );

char* ajustabarra(char* );

char* tiraptipo(char *, char *);

char *concatenageo(char *, char *, char *);

char *concatenaOutGeo(char *, char *, char *);

char *concatenaqry(char *, char *, char *);

char *saidaSvg(char *, char *);

char *concatenaOutQry(char *, char *, char *, char *);

char *makegeo(char *, char *);

char* makeoutgeo(char *,char *);

char *makesvgname(char *);

char *makeqry(char *,char *);

char *makeoutqry(char *, char*,char *);

char* makesvgnameqry(char *outqry);

char *maketxtname(char *);
#endif