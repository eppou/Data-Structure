#include "path.h"
#include "functionspath.h"
#include <string.h>

typedef struct struc_paths{
    
    char *Inpath;
    char *OutPath;
    char *ArqGeo;
    char *ArqQry;
    char *aux;
    char *geo;
    char *qry;
    char *Outgeo;
    char *Outqry;
    char *Semptipo;
    char *Semptipoqry;
    char *Svgname;
    char *Svgnameqry;
    char *Txtname;

} paths;

Path createPaths(){

    paths* aux =  calloc(1,sizeof(paths));
    return (aux);
}

void initializepath(Path p)
{
    paths* path = (paths*)p;
    path->Inpath = NULL;
    path->OutPath= NULL;
    path->ArqGeo= NULL;
    path->ArqQry= NULL;
    path->aux= NULL;
    path->geo= NULL;
    path->qry= NULL;
    path-> Outgeo= NULL;
    path->Outqry= NULL;
    path->Semptipo= NULL;
    path->Semptipoqry= NULL;
    path->Svgname= NULL;
    path->Svgnameqry= NULL;
    path->Txtname= NULL;
}

void readpaths(Path p, int argc, char *argv[]){
    paths* aux = (paths*)p;
    readArgv(argc, argv,p);
}


void finalgeo(Path p){
    paths* aux = (paths*)p;
    aux->geo = makegeo(aux->Inpath,aux->ArqGeo);
}

void finaloutgeo(Path p){
    paths* aux = (paths*)p;
    aux->Outgeo = makeoutgeo(aux->ArqGeo,aux->OutPath);
}

void finalsvgname(Path p){
    paths* aux = (paths*)p;
    aux->Svgname = makesvgname(aux->Outgeo);
}

void finaloutqry(Path p){
    paths* aux = (paths*)p;
    aux->Outqry = makeoutqry(aux->OutPath,aux->ArqQry,aux->ArqGeo);
}

void finalqry(Path p){
    paths* aux = (paths*)p;
    aux->qry = makeqry(aux->Inpath,aux->ArqQry);
}

void finalsvgqry(Path p){
    paths* aux = (paths*)p;
    aux->Svgnameqry =makesvgnameqry(aux->Outqry);
}

void finaltxt(Path p){
    paths* aux = (paths*)p;
    aux->Txtname = maketxtname(aux->Outqry);
}

char *getArqqry(Path p)
{
    paths* aux= (paths*)p;
    return aux->ArqQry;

}
char *getgeo(Path p){
    paths* aux = (paths*)p;
    return aux->geo;
}
char* getqry(Path p){
    paths* aux = (paths*)p;
    return aux->qry;
}

char *getoutgeo(Path p){
    paths* aux = (paths*)p;
    return aux->Outgeo;
}

char *getoutqry(Path p){
    paths* aux = (paths*)p;
    return aux->Outqry;
}

char *getsvgname(Path p){
    paths* aux = (paths*)p;
    return aux->Svgname;
}

char *getsvgqry(Path p){
    paths* aux = (paths*)p;
    return aux->Svgnameqry;
}

char *gettxtname(Path p){
    paths* aux = (paths*)p;
    return aux->Txtname;
}

void set_Inpath(Path p, char *in)
{
    paths *aux = p;
    aux->Inpath = in;
        
}

void set_Outpath(Path p, char *out)
{
    paths *aux = (paths*)p;
    
    aux->OutPath = out;
}

void set_ArqGeo(Path p, char* setgeo)
{
    paths *aux = (paths*)p;
    aux->ArqGeo = setgeo;
}

void set_ArqQry(Path p, char* setqry)
{
    paths *aux = (paths*)p;
    aux->ArqQry = setqry;
}

void freepaths(Path p){
    paths* path = (paths*)p;
    if(path->Inpath!=NULL){
    free(path->Inpath);}

    if(path->OutPath!=NULL){
    free(path->OutPath);}

    if(path->ArqGeo!=NULL){
    free(path->ArqGeo);}

    if(path->ArqQry!=NULL){
    free(path->ArqQry);
    }


    if(path->geo!=NULL){
    free(path->geo);}

    if(path->qry!=NULL){
    free(path->qry);}

    if(path->Outgeo!=NULL){
    free(path->Outgeo);}

    if(path->Outqry!=NULL){
    free(path->Outqry);}

   // if(path->Semptipo!=NULL){
   // free(path->Semptipo);}

   // if(path->Semptipoqry!=NULL){
    //free(path->Semptipoqry);}

    if(path->Svgname!=NULL){
    free(path->Svgname);}

    if(path->Svgnameqry!=NULL){
    free(path->Svgnameqry);}

    if(path->Txtname!=NULL){
    free(path->Txtname);}
    
    free(path);
}
