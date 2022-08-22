#include "funcqry.h"


float agressividade;
double pontuacao = 0;
int n_agressoes=0;
double maxpont = 0;

FdentroDe figureRegiao (Info i, double x1, double y1,double x2, double y2)
{
    
    if(testaCirculo(i) == 1)
    {
      return circleRegiao(i,x1,y1,x2,y2);
       
    }
    else if(testeRetangulo(i) == 1)
    {
      return rectangleRegiao(i,x1,y1,x2,y2);
    }
    else if(testeline(i) == 1)
    {   
      return lineRegiao(i,x1,y1,x2,y2);
    }
    else if(testetext(i) == 1)
    {
        return textRegiao(i,x1,y1,x2,y2);
    }
   
}

FatingidoPor figureatingido (Info i, double x, double y)
{
    
    if(testaCirculo(i) == 1)
    {
      return circleHit(i,x,y);
       
    }
    else if(testeRetangulo(i) == 1)
    {
      return rectangleHit(i,x,y);
    }
    else if(testeline(i) == 1)
    {   
      return lineHit(i,x,y);
    }
    else if(testetext(i) == 1)
    {
        return textHit(i,x,y);
    }
   
}

void funcNA (int V,Path pathh){
   agressividade = V;
   FILE *arquivo = fopen(gettxtname(pathh),"w");
   fprintf(arquivo,"---------TXT---------\n");   
}

void funcTP(XyyTree t,double x,double y,double epsilon,FILE *svgarquivo,Path pathh)
{
   FILE *txt = fopen(gettxtname(pathh),"a");
   Lista aux = getInfosAtingidoPontoXyyT (t,x,y,figureatingido);
   void* node = getBegin(aux);
   fprintf(txt,"\n\n-------[*] tp %lf %lf--------------",x,y);

   double maxPontAux = 0;

   while (node!=NULL)
   {
      Info i = getInfo(aux,node);
      if(testaCirculo(i)==1){
         double idd = getIcircle(i), x = getXcircle(i) ,y = getYcircle(i) ,r = getRcircle(i);
         char corborda[30],corpreenche[30];
         
         strcpy(corborda,getCorbcircle(i));
         strcpy(corpreenche,getCorpcircle(i));
         
         double NE = getProtectLevelcircle(i);

         fprintf(txt,"\n\nO hovercraft de assalto i=%lf de ancora X=%0.2lf Y=%0.2lf raio=%0.2lf cor de borda=%s cor de preenchimento=%s e nivel de energia=%0.2lf foi atingida e destruida por um torpedo", idd , x, y,r, corborda,corpreenche,NE);
         
         double area = getAreacircle(i)/5;
         pontuacao = pontuacao + 75/area;
         maxPontAux = maxpont + 75/area;
         removeNoXyyT(t,getNodeXyyT(t,getXcircle(i),getYcircle(i),epsilon));
      }
      else if(testeRetangulo(i)==1){
         double idd = getIrectangle(i), x= getXrectangle(i), y= getYrectangle(i), w = getWrectangle(i), h= getHrectangle(i);
         char corborda[30],corpreenche[30];
         
         strcpy(corborda,getCorbrectangle(i));
         strcpy(corpreenche,getCorprectangle(i));

         int NE = getProtectLevelrectangle(i);

         fprintf(txt,"\n\nA embarcação i=%02.lf de ancora em X=%0.2lf Y=%0.2lf altura=%0.2lf largura=%0.2lf cor de borda=%s cor de preenchimento=%s e nivel de energia=%d foi atingida e destruida por um torpedo",idd,x,y,h,w,corborda,corpreenche,NE);
         
         double area = getArearectangle(i)/5;
         pontuacao = pontuacao + 90/area;
         maxPontAux = maxpont + 90/area;
         removeNoXyyT(t,getNodeXyyT(t,getXrectangle(i),getYrectangle(i),epsilon));

      }else if(testetext(i)==1){
         double idd=getItext(i), x=getXtext(i), y=getYtext(i);
         char corborda[30],corpreenche[30],texto[100]; 

         strcpy(corborda,getCorbtext(i));
         strcpy(corpreenche,getCorptext(i)); 
         strcpy(texto,getTextotext(i));
         
         int NE = getProtectLeveltext(i);

         fprintf(txt,"\n\n o RHIB  i=%0.2lf de ancora X=%0.2lf Y=%0.2lf cor de borda=%s cor de preenchimento=%s texto=%s Nivel de energia=%d foi atingido e destruido por um torpedo",idd ,x, y,corborda,corpreenche,texto,NE);
         removeNoXyyT(t,getNodeXyyT(t,getXtext(i),getYtext(i),epsilon));
         pontuacao = pontuacao + 500;
         maxPontAux = maxpont + 500;

      }else if(testeline(i)==1){ 
      int idd=getIline(i);
      double x=getX1line(i);
      double y=getY1line(i);
      char corzinha[30]; 
      strcpy(corzinha,getCorline(i));
      
      double NE = getProtectLevelline(i);
      

      fprintf(txt,"\n\n o Submarino i=%d ancora X=%0.2lf e Y=%0.2lf cor=%s Nivel de energia = %0.2lf foi atingido e destruido por um torpedo ",idd,x,y,corzinha,NE);
    
      removeNoXyyT(t,getNodeXyyT(t,getX1line(i),getY1line(i),epsilon)); ///////////PROBLEMA DA LINHA
      pontuacao = pontuacao + 150;
      maxPontAux = maxpont + 150;
      }
      node = getNext(aux,node);
   }

   if(maxPontAux>maxpont){
      maxpont = maxPontAux;
   }

   char cor[10];
   strcpy(cor,"gray");
   if(returnlistsize(aux)>0)
   {
      strcpy(cor,"red");
   }
   fprintf(svgarquivo,"\n\t<text x=\"%f\" y=\"%f\"  fill=\"%s\" >*%d</text>",x,y,cor,returnlistsize(aux)); 
   freeLISTA(aux,0);
}


void funcTR(XyyTree t,double x,double y, double dx, double dy, double id,FILE *svgarquivo,Path pathh)
{
   FILE *txt = fopen(gettxtname(pathh),"a");
   Lista list = getInfosAtingidoPontoXyyT(t,x,y,figureatingido);
   void* aux = getBegin(list);
   fprintf(txt,"\n\n----[*] tr %lf %lf----------------",x,y);
   while (aux!=NULL)
   {
      Info i = getInfo(list,aux);
      if(testaCirculo(i)==1){
         double idd = getIcircle(i), x = getXcircle(i) ,y = getYcircle(i) ,r = getRcircle(i);
         char corborda[30],corpreenche[30];
         strcpy(corborda,getCorbcircle(i)) ,strcpy(corpreenche,getCorpcircle(i));
         double NE = getProtectLevelcircle(i);

         fprintf(txt,"\n\nO hovercraft de assalto i=%lf de ancora X=%0.2lf Y=%0.2lf raio=%0.2lf cor de borda=%s cor de preenchimento=%s e nivel de energia=%0.2lf foi atingida por um torpedo replicante", idd , x, y,r, corborda,corpreenche,NE);
         fprintf(txt,"\n\nO hovercraft de assalto clonado i=%lf de ancora X=%0.2lf Y=%0.2lf raio=%0.2lf cor de borda=%s cor de preenchimento=%s e nivel de energia=%0.2lf é o clone da figura acima", id , dx, dy,r, corpreenche,corborda,NE);
         
         void *c = createCircle(id,dx,dy,getRcircle(i),getCorpcircle(i), getCorbcircle(i));
         insertXyyT(t,dx,dy,c);
 
      }else if(testeRetangulo(i)==1){
         double idd = getIrectangle(i), x= getXrectangle(i), y= getYrectangle(i), w = getWrectangle(i), h= getHrectangle(i);
         char corborda[30] ,corpreenche[30];
         strcpy(corborda,getCorbrectangle(i)) ,strcpy(corpreenche,getCorprectangle(i));
         int NE = getProtectLevelrectangle(i);

         fprintf(txt,"\n\nA embarcação i=%02.lf de ancora em X=%0.2lf Y=%0.2lf altura=%0.2lf largura=%0.2lf cor de borda=%s cor de preenchimento=%s e nivel de energia=%d foi atingida por um torpedo replicante",idd,x,y,h,w,corborda,corpreenche,NE);
         fprintf(txt,"\n\nA embarcação clonada i=%02.lf de ancora em X=%0.2lf Y=%0.2lf altura=%0.2lf largura=%0.2lf cor de borda=%s cor de preenchimento=%s e nivel de energia=%d é o clone da figura acima",id,dx,dy,h,w,corpreenche,corborda,NE);

         void *c = createrectangle(id,dx,dy,getWrectangle(i),getHrectangle(i), getCorprectangle(i),getCorbrectangle(i));
         insertXyyT(t,dx,dy,c);

      }else if(testetext(i)==1){
         double idd=getItext(i), x=getXtext(i), y=getYtext(i);
         char corborda[30],corpreenche[30], texto[100] ;
         strcpy(corborda,getCorbtext(i)) , strcpy(corpreenche,getCorptext(i)), strcpy(texto,getTextotext(i));
         int NE = getProtectLeveltext(i);

         fprintf(txt,"\n\n o RHIB  i=%0.2lf de ancora X=%0.2lf Y=%0.2lf cor de borda=%s cor de preenchimento=%s texto=%s Nivel de energia=%d foi atingido por um torpedo replicante",idd ,x, y,corborda,corpreenche,texto,NE);
         fprintf(txt,"\n\n o RHIB clonado i=%0.2lf de ancora X=%0.2lf Y=%0.2lf cor de borda=%s cor de preenchimento=%s texto=%s Nivel de energia=%d é o clone da figura acima",id ,dx, dy,corpreenche,corborda,texto,NE);

         void *c = createText(id,dx,dy,getCorptext(i),getCorbtext(i),getAtext(i),getTextotext(i)); 
         insertXyyT(t,dx,dy,c);

      }else if(testeline(i)==1){
         double idd=getIline(i),x=getX1line(i),y=getY1line(i);
         char corzinha[30] ;
         strcpy(corzinha,getCorline(i));
         int NE = getProtectLevelline(i);

         fprintf(txt,"\n\n o Submarino i=%0.2lf ancora X=%0.2lf e Y=%0.2lf cor=%s Nivel de energia = %d foi atingido por um torpedo replicante",idd,x,y,corzinha,NE);
         fprintf(txt,"\n\n o Submarino clonado i=%0.2lf ancora X=%0.2lf e Y=%0.2lf cor=%s Nivel de energia = %d é o clone da figura acima",id,dx,dy,corzinha,NE);

         void *c = createline(id,dx,dy,getX2line(i),getY2line(i),getCorline(i));
         insertXyyT(t,dx,dy,c);

      }

      aux = getNext(list,aux);
      id++;

   }
   fprintf(svgarquivo,"\n\t<text x=\"%lf\" y=\"%lf\" fill=\"black\" >@</text>",x,y); 
   freeLISTA(list,0);
 // O torpedo replicante é um bônus que
   //pode aumentar a possibilidade de pontuacao.
}

void printancora(Lista aux,FILE* svgname)
{
   void* node = getBegin(aux);
   while (node!=NULL)
   {
      Info i = getInfo(aux,node);

      if(testaCirculo(i)==1){
      
         fprintf(svgname, "\n\t<circle cx=\"%lf\" cy=\" %lf \" r=\" 1 \" stroke=\" red \" stroke-width=\" 1 \" fill=\" red \" opacity=\" 10 \"/>",getXcircle(i),getYcircle(i));
      }
      else if(testeRetangulo(i)==1){
      
         fprintf(svgname, "\n\t<circle cx=\"%lf\" cy=\" %lf \" r=\" 1 \" stroke=\" red \" stroke-width=\" 1 \" fill=\" red \" opacity=\" 1 \"/>",getXrectangle(i),getYrectangle(i));
      }
      else if(testetext(i)==1){
         fprintf(svgname, "\n\t<circle cx=\"%lf\" cy=\" %lf \" r=\" 1 \" stroke=\" red \" stroke-width=\" 1 \" fill=\" red \" opacity=\" 1 \"/>",getXtext(i),getYtext(i));
      }
      else if(testeline(i)==1){
         fprintf(svgname, "\n\t<circle cx=\"%lf\" cy=\" %lf \" r=\" 1 \" stroke=\" red \" stroke-width=\" 1 \" fill=\" red \" opacity=\" 1 \"/>",getX1line(i),getY1line(i));
         fprintf(svgname, "\n\t<circle cx=\"%lf\" cy=\" %lf \" r=\" 1 \" stroke=\" red \" stroke-width=\" 1 \" fill=\" red \" opacity=\" 1 \"/>",getX2line(i),getY2line(i));
      }
         node= getNext(aux,node);
   }
}

void funcBE (XyyTree t,double x,double y,double w, double h,double epsilon,FILE *svgarquivo,Path pathh){
   FILE *txt = fopen(gettxtname(pathh),"a");
   Lista aux = getInfosDentroRegiaoXyyT(t,x,y,w,h,figureRegiao);
   void *listnode = getBegin(aux);
   fprintf(txt,"\n\n[*] be %lf %lf %lf %lf",x,y,w,h);

   double maxpontAUX=0;

   while (listnode!=NULL)
   {
      Info i = getInfo(aux,listnode);
      if(testaCirculo(i)==1){
         int region = (int)w*(int)h;
         int NivelProtecaoRemanescente = degradaCircle(i,agressividade,region);

         double idd = getIcircle(i), x = getXcircle(i) ,y = getYcircle(i) ,r = getRcircle(i);
         char corborda[30],corpreenche[30];

         strcpy(corborda,getCorbcircle(i));
         strcpy(corpreenche,getCorpcircle(i));

         float NE = getProtectLevelcircle(i);

         fprintf(txt,"\n\nO hovercraft de assalto i=%lf de ancora X=%0.2lf Y=%0.2lf raio=%0.2lf cor de borda=%s cor de preenchimento=%s e nivel de energia=%f foi atingida por uma bomba de irradiação", idd , x, y,r, corborda,corpreenche,NE);
   

         if(NivelProtecaoRemanescente<=0){
            removeNoXyyT(t,getNodeXyyT(t,getXcircle(i),getYcircle(i),epsilon));
            fprintf(txt,"REMOVIDO");
            pontuacao = pontuacao + 75;
            maxpontAUX = maxpontAUX + 75;
         } 
      }

      else if(testeRetangulo(i)==1){
         int region = (int)w*(int)h;
         int NivelProtecaoRemanescenteR = degradaRectangle(i,agressividade,region);

         double idd = getIrectangle(i), x= getXrectangle(i), y= getYrectangle(i), w = getWrectangle(i), h= getHrectangle(i);
         char corborda[30],corpreenche[30];
         strcpy(corborda,getCorbrectangle(i));
         strcpy(corpreenche,getCorprectangle(i));
         float NE = getProtectLevelrectangle(i);

         fprintf(txt,"\n\nA embarcação i=%02.lf de ancora em X=%0.2lf Y=%0.2lf altura=%0.2lf largura=%0.2lf cor de borda=%s cor de preenchimento=%s e nivel de energia=%f foi atingida por uma bomba de irradiação",idd,x,y,h,w,corborda,corpreenche,NE);


         if(NivelProtecaoRemanescenteR<=0){
            removeNoXyyT(t,getNodeXyyT(t,getXrectangle(i),getYrectangle(i),epsilon));
            fprintf(txt,"REMOVIDO");
            pontuacao = pontuacao + 90;
            maxpontAUX = maxpontAUX + 90;
         }
      }

      else if(testetext(i)==1){
         int region = (int)w*(int)h;
         int NivelProtecaoRemanescenteT = degradaText(i,agressividade,region);
      
         double idd=getItext(i), x=getXtext(i), y=getYtext(i);
         
         char corborda[30]= "";
         char corpreenche[30]= "";
         char texto[100]= "";
         strcpy(corborda,getCorbtext(i)) , strcpy(corpreenche,getCorptext(i)), strcpy(texto,getTextotext(i));
         float NE = getProtectLeveltext(i);
         fprintf(txt,"\n\n o RHIB  i=%0.2lf de ancora X=%0.2lf Y=%0.2lf cor de borda=%s cor de preenchimento=%s texto=%s Nivel de energia=%0.2lf foi atingido por uma bomba de irradiação",idd ,x, y,corborda,corpreenche,texto,NE);

         if(NivelProtecaoRemanescenteT<=0){
            removeNoXyyT(t,getNodeXyyT(t,getXtext(i),getYtext(i),epsilon));
            fprintf(txt,"REMOVIDO");
            pontuacao = pontuacao + 30;
            maxpontAUX = maxpontAUX + 30;
         }
      }

      else if(testeline(i)==1){
         int region = (int)w*(int)h;
         int NivelProtecaoRemanescenteL = degradaLine(i,agressividade,region);

         double idd=getIline(i),x=getX1line(i),y=getY1line(i);
        // char corzinha[10] ;
        // strcpy(corzinha,getCorline(i));
       //  float NE;// = getProtectLevelline(i);
         //;
         fprintf(txt,"\n\n o Submarino i=%0.2lf ancora X=%0.2lf e Y=%0.2lf cor=%s Nivel de energia = %f foi atingido por uma bomba de irradiação",idd,x,y,getCorline(i),getProtectLevelline(i));

         if(NivelProtecaoRemanescenteL <=0){
            removeNoXyyT(t,getNodeXyyT(t,getX1line(i),getY1line(i),epsilon)); ///////////PROBLEMA DA LINHA
            fprintf(txt,"REMOVIDO");
            pontuacao = pontuacao + 50;
            maxpontAUX = maxpontAUX + 50;
         }
      }
      listnode = getNext(aux,listnode);
   }

   if(maxpontAUX>maxpont){
      maxpont = maxpontAUX;
   }

  
   fprintf(svgarquivo, "\n\t<rect x=\" %lf \" y=\" %lf \" width=\" %lf \" height=\" %lf \" stroke=\" red \" stroke-width=\" 1px \" fill-opacity=\"0\" />",x,y,w,h);
   printancora(aux,svgarquivo);

   freeLISTA(aux,0);
}

void readQRY (XyyTree t,double epsilon,Path pathh)
{
   
   if(getArqqry(pathh)!= NULL){

   finalqry(pathh);
   finaloutqry(pathh);
   FILE *arquivo = fopen(getqry(pathh), "r");
   finaltxt(pathh);
   FILE *txtname = fopen(gettxtname(pathh),"a");
   //FILE *txtname = fopen("report.txt","a");
   //FILE *arquivo = fopen("comandos.qry", "r");
   finalsvgqry(pathh);
   FILE *svgname = fopen(getsvgqry(pathh), "w");
   //FILE *svgname = fopen("svgQRY.svg","w");
   openTagSVG (svgname);
   
   char leitura[50];
    while(fscanf(arquivo," %s ",leitura)!= -1){
      printf("oi");
      if(strcmp(leitura,"na") == 0){
         float V;
         fscanf(arquivo,"%f",&V);
         funcNA(V,pathh);
         n_agressoes++;
      }

      else if(strcmp(leitura, "tp") == 0){
         double x,y;
         fscanf(arquivo,"%lf %lf", &x, &y);
         funcTP(t,x,y,epsilon,svgname,pathh);
         n_agressoes++;
      }

      else if(strcmp(leitura,"tr") == 0){
         double x,y,dx,dy,id;
         fscanf(arquivo,"%lf %lf %lf %lf %lf",&x,&y,&dx,&dy,&id);
         funcTR(t,x,y,dx,dy,id,svgname,pathh);
         n_agressoes++;
      }
      else if(strcmp(leitura,"be") == 0){
         double x,y,w,h;
         fscanf(arquivo,"%lf %lf %lf %lf",&x,&y,&w,&h);
         funcBE(t,x,y,w,h,epsilon,svgname,pathh);
         n_agressoes++;
      }
      
    }
   
   writeTree (svgname,t);
   double proportionPTNA = pontuacao/n_agressoes;
   fprintf(txtname,"\n\nPONTUAÇÂO FINAL=%0.2lf \nPONTUAÇÂO MAXIMA=%0.2lf \nproporção entre pontos obtidos e o número de agressões = %0.2lf",pontuacao,maxpont,proportionPTNA);

   closeTagSVG (svgname);
   fclose(arquivo);
   fclose(svgname);
   }
   
}