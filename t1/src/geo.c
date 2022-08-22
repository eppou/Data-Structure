#include "geo.h"
#include "path.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "text.h"
#include "svg.h"

FatingidoPor figureatingido(Info i, double x, double y);
FvisitaNo printaNodeTree (Info i,double x,double y, void *aux);



void readgeo(XyyTree tree,Path pathh)
{   
    finalgeo(pathh);
    FILE *arquivo = fopen(getgeo(pathh), "r");
   //FILE *arquivo = fopen("comandos.geo", "r");
    char var;
    double x,y,r,w,h,x2,y2;
    double i;
    char a;
    char corb[10];
   // char *corb2;
    char corp[10];
    char texto[300];
    finaloutgeo(pathh);
    finalsvgname(pathh);
    FILE *svggeo = fopen(getsvgname(pathh), "w");
    //FILE *svggeo = fopen("svggeo.svg", "w");
    openTagSVG(svggeo);

   while (fscanf(arquivo,"%c ", &var) != -1)
    {
       
        switch (var)
        { 
            
        case 'c': ;
            
            fscanf(arquivo, "%lf %lf %lf %lf %s %s", &i,&x,&y,&r,corb,corp);
            void *p = createCircle(i,x,y,r,corb,corp);
            insertXyyT(tree,x,y,p);       
            

            break;

        case 'r': ;

            fscanf(arquivo, "%lf %lf %lf %lf %lf %s %s", &i,&x,&y,&w,&h,corb,corp);
            void *P = createrectangle(i,x,y,w,h,corb,corp);
            insertXyyT(tree,x,y,P);
           
            
        break;

         case 'l': ;
            
            fscanf(arquivo,"%lf %lf %lf %lf %lf %s" ,&i,&x,&y,&x2,&y2,corp);
            void *l= createline(i,x,y,x2,y2,corp);
            insertXyyT(tree,x,y,l);
            

        break;

        case 't': ;
            
            void *t;
            fscanf(arquivo, "%lf %lf %lf %s %s %c %[^\n]",&i,&x,&y,corb,corp,&a, texto);
            //fgets(texto,300,arquivo);
            t = createText(i,x,y,corb,corp,a,texto);
            insertXyyT(tree,x,y,t);
           
        break;
    
            default:
            break;

        

        }
    }
    
    writeTree (svggeo,tree);
    closeTagSVG (svggeo);
    fclose(arquivo);
    fclose(svggeo); 
   
}
