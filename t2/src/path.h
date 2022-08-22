#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

typedef void *Path;

Path createPaths();

void readpaths(Path , int , char *argv[]);

void initializepath(Path );

void finalgeo(Path p);

void finaloutgeo(Path p);

void finalsvgname(Path p);

void finaloutqry(Path p);

void finalqry(Path p);

void finalsvgqry(Path p);

void finaltxt(Path p);

char *getArqqry(Path p);

char *getgeo(Path p);

char* getqry(Path p);

char *getoutgeo(Path p);

char *getoutqry(Path p);

char *getsvgname(Path p);


char *getsvgqry(Path p);

char *gettxtname(Path p);

void set_Inpath(Path , char *);

void set_Outpath(Path p, char *out);

void set_ArqGeo(Path p, char* setgeo);

void set_ArqQry(Path p, char* setqry);


void freepaths(Path p);
  
#endif