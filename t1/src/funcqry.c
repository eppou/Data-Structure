#include "funcqry.h"

bool figureRegiao(Info i, double x1, double y1, double x2, double y2)
{

   if (testaCirculo(i) == 1)
   {
      return circleRegiao(i, x1, y1, x2, y2);
   }
   else if (testeRetangulo(i) == 1)
   {
      return rectangleRegiao(i, x1, y1, x2, y2);
   }
   else if (testeline(i) == 1)
   {
      return lineRegiao(i, x1, y1, x2, y2);
   }
   else if (testetext(i) == 1)
   {
      return textRegiao(i, x1, y1, x2, y2);
   }
}

bool figureatingido(Info i, double x, double y)
{

   if (testaCirculo(i) == 1)
   {
      return circleHit(i, x, y);
   }
   else if (testeRetangulo(i) == 1)
   {
      return rectangleHit(i, x, y);
   }
   else if (testeline(i) == 1)
   {
      return lineHit(i, x, y);
   }
   else if (testetext(i) == 1)
   {
      return textHit(i, x, y);
   }
}

void procuraI(Info i, double x, double y, void *aux)
{

   void *Noaux = getBegin(aux);
   Fila qq = getInfo(aux, Noaux);
   Noaux = getNext(aux, Noaux);

   void *floatid = getInfo(aux, Noaux);
   float id = *((float *)floatid);
   Noaux = getNext(aux, Noaux);

   XyyTree t = getInfo(aux, Noaux);
   Noaux = getNext(aux, Noaux);

   FILE *arquivo = (FILE *)getInfo(aux, Noaux);

   void *figura = getInfoXyyT(t, i);

   if (testaCirculo(figura) == 1)
   {

      if (id == getIcircle(figura))
      {
         double auxX, auxY;
         auxX = getXcircle(figura);
         auxY = getYcircle(figura);
         enqueue(qq, auxX, auxY);
         fprintf(arquivo, "\no comando INP inseriu as coordenadas %0.2lf %0.2lf do Circulo %0.2f", auxX, auxY, id);
      }
   }
   if (testeRetangulo(figura) == 1)
   {

      if (id == getIrectangle(figura))
      {
         double auxX, auxY;
         auxX = getXrectangle(figura);
         auxY = getYrectangle(figura);
         enqueue(qq, auxX, auxY);
         fprintf(arquivo, "\no comando INP inseriu as coordenadas %0.2lf %0.2lf do Retangulo %0.2f", auxX, auxY, id);
      }
   }
   if (testeline(figura) == 1)
   {

      if (id == getIline(figura))
      {
         int flag = X1orX2line(figura);
         double auxX, auxY;
         if (flag == 1)
         {
            auxX = getX1line(figura);
            auxY = getY1line(figura);
         }
         if (flag == 2)
         {
            auxX = getX2line(figura);
            auxY = getY2line(figura);
         }
         enqueue(qq, auxX, auxY);
         fprintf(arquivo, "\no comando INP inseriu as coordenadas %0.2lf %0.2lf da Linha %0.2f", auxX, auxY, id);
      }
   }
   if (testetext(figura) == 1)
   {

      if (id == getItext(figura))
      {
         double auxX, auxY;
         auxX = getXtext(figura);
         auxY = getYtext(figura);
         enqueue(qq, auxX, auxY);
         fprintf(arquivo, "\no comando INP inseriu as coordenadas %0.2lf %0.2lf do Texto %0.2f", auxX, auxY, id);
      }
   }
}

void funcINP(float id, XyyTree t, Fila q, FILE *txt)
{
   Lista listaAux = inicia();
   lista_inserenofim(listaAux, q);

   void *IDptr = &id;
   lista_inserenofim(listaAux, IDptr);
   lista_inserenofim(listaAux, t);
   lista_inserenofim(listaAux, txt);

   visitaProfundidadeXyyT(t, procuraI, listaAux);
   freeLISTA(listaAux,0);
}

void funcRMP(Fila q, FILE *textoreport)
{
   double XX, YY;
   void *aux = dequeue(q);
   if (aux != NULL)
   {
      XX = pickXfromxyPoint(aux);
      YY = pickYfromxyPoint(aux);
      fprintf(textoreport, "\nas coordenadas retiradas pelo comando RMP foram %0.2lf %0.2lf", XX, YY);
   }
}

void funcCLP(Fila q)
{
   freeQueue(q);
}

Lista funcSEL(double x, double y, double w, double h, XyyTree t, Lista listaSel, FILE *arquivotxt,FILE *svgarquivo)
{
   freeLISTA(listaSel, 0);
   Lista listaSel2 = getNodesDentroRegiaoXyyT(t, x, y, w, h);

   // escreve txt
   void *noLista = getBegin(listaSel2);
   while (noLista != NULL)
   {
      Node noTree = getInfo(listaSel2, noLista);
      void *figura = getInfoXyyT(t, noTree);

      if (testaCirculo(figura) == 1)
      {
         fprintf(arquivotxt, "\nO Circulo %0.2f foi selecionado", getIcircle(figura));
      }

      if (testeRetangulo(figura) == 1)
      {
         fprintf(arquivotxt, "\no Retangulo %0.2f foi selecionado", getIrectangle(figura));
      }

      if (testeline(figura) == 1)
      {
         fprintf(arquivotxt, "\na linha %0.2f foi selecionada", getIline(figura));
      }

      if (testetext(figura) == 1)
      {
         fprintf(arquivotxt, "\no Texto %0.2f foi selecionado", getItext(figura));
      }
      noLista = getNext(listaSel2, noLista);
   }
   fprintf(svgarquivo, "\n\t<rect x=\" %lf \" y=\" %lf \" width=\" %lf \" height=\" %lf \" stroke=\" red \" stroke-width=\" 1px \" fill-opacity=\"0\" />",x,y,w,h);
   return listaSel2;
}

void funcSELplus(double x, double y, double w, double h, XyyTree t, Lista listaSel, FILE *arquivotxt,FILE* svgarquivo)
{
   Lista auxList = getNodesDentroRegiaoXyyT(t, x, y, w, h);
   void *Nodeaux = getBegin(auxList);
   
   //--------------txt---------------//
   int oldSize = returnlistsize(listaSel);
   int Selsize = returnlistsize(auxList);
   fprintf(arquivotxt,"\nhaviam %d previamente selecionados e o SEL+ selecionou + %d",oldSize,Selsize);

   while (Nodeaux != NULL)
   {
      void *treeNode = getInfo(auxList,Nodeaux);
      void *figura = getInfoXyyT(t,treeNode);

      lista_inserenofim(listaSel, treeNode);

      if (testaCirculo(figura) == 1)
      {
         fprintf(arquivotxt, "\nO Circulo %0.2f foi selecionado+", getIcircle(figura));
      }

      if (testeRetangulo(figura) == 1)
      {
         fprintf(arquivotxt, "\no Retangulo %0.2f foi selecionado+", getIrectangle(figura));
      }

      if (testeline(figura) == 1)
      {
         fprintf(arquivotxt, "\na linha %0.2f foi selecionada+", getIline(figura));
      }

      if (testetext(figura) == 1)
      {
         fprintf(arquivotxt, "\no Texto %0.2f foi selecionado+", getItext(figura));
      }

      Nodeaux = getNext(auxList, Nodeaux);
   }
   fprintf(svgarquivo, "\n\t<rect x=\" %lf \" y=\" %lf \" width=\" %lf \" height=\" %lf \" stroke=\" red \" stroke-width=\" 1px \" fill-opacity=\"0\" />",x,y,w,h);
    freeLISTA(auxList, 0);
}

Lista funcDELS(XyyTree t, Lista l, FILE *arquivotxt)
{
   //------------------------------------txt----------------------------------//
   void *noLista = getBegin(l);
   while (noLista != NULL)
   {
      Node noTree = getInfo(l, noLista);
      void *figura = getInfoXyyT(t, noTree);

      if (testaCirculo(figura) == 1)
      {
         fprintf(arquivotxt, "\nO Circulo %0.2f foi removido pelo DELS", getIcircle(figura));
      }

      if (testeRetangulo(figura) == 1)
      {
         fprintf(arquivotxt, "\no Retangulo %0.2f foi removido pelo DELS", getIrectangle(figura));
      }

      if (testeline(figura) == 1)
      {
         fprintf(arquivotxt, "\na linha %0.2f foi removido pelo DELS", getIline(figura));
      }

      if (testetext(figura) == 1)
      {
         fprintf(arquivotxt, "\no Texto %0.2f foi removido pelo DELS", getItext(figura));
      }
      noLista = getNext(l, noLista);
   }


   Node *auxNode = getBegin(l);
   while (auxNode != NULL)
   {
      removeNoXyyT(t, getInfo(l, auxNode));
      auxNode = getNext(l, auxNode);
   }
   freeLISTA(l,0);
   Lista novaLista = inicia();
   return novaLista;
}

//--------------------------------------function DPS-------------------------------------//

void funcDPS(float i, double dx, double dy, char corb[30], char corp[30], XyyTree t, Lista l)
{
   void *Nolist = getBegin(l);
   while (Nolist != NULL)
   {
      Node NoTree = getInfo(l, Nolist);
      void *figura = getInfoXyyT(t, NoTree);

      if (testaCirculo(figura) == 1)
      {
         double x = getXcircle(figura) + dx;
         double y = getYcircle(figura) + dy;
         void *newcircle = createCircle(i, x, y, getRcircle(figura), corb, corp);
         insertXyyT(t, x, y, newcircle);
      }

      if (testeRetangulo(figura) == 1)
      {
         double x = getXrectangle(figura) + dx;
         double y = getYrectangle(figura) + dy;
         void *newrectangle = createrectangle(i, x, y, getWrectangle(figura), getHrectangle(figura), corb, corp);
         insertXyyT(t, x, y, newrectangle);
      }

      if (testeline(figura) == 1)
      {
         double x = getX1line(figura) + dx;
         double y = getY1line(figura) + dy;
         double x2 = getX2line(figura) + dx;
         double y2 = getY2line(figura) + dy;
         void *newline = createline(i, x, y, x2, y2, corp);
         insertXyyT(t, x, y, newline);
      }

      if (testetext(figura) == 1)
      {
         double x = getXtext(figura) + dx;
         double y = getYtext(figura) + dy;
         void *newtext = createText(i, x, y, corb, corp, getAtext(figura), getTextotext(figura));
         insertXyyT(t, x, y, newtext);
      }
      i++;
      Nolist = getNext(l, Nolist);
   }
}

//------------------------------------function UPS--------------------------------------//

void funcUPS(char corb[30], char corp[30], double dx, double dy, float n, Lista l, XyyTree t)
{
   int listasize = returnlistsize(l);
   void *noLista = getLast(l);
   noLista = getPrev(l, noLista);
   while (noLista!=NULL&&n!=0)
   {
      Node noTree = getInfo(l, noLista);
      void *figura = getInfoXyyT(t, noTree);

      if (testaCirculo(figura) == 1)
      {
         changeCircle(figura, dx, dy, corb, corp);
      }

      if (testeRetangulo(figura) == 1)
      {
         changeRectangle(figura, dx, dy, corb, corp);
      }

      if (testeline(figura) == 1)
      {
         changeLine(figura, dx, dy, corb, corp);
      }

      if (testetext(figura) == 1)
      {
         changeText(figura, dx, dy, corb, corp);
      }

      listasize = listasize - 1;
      n = n + 1;
      noLista = getPrev(l, noLista);
   }
}

//---------------------------------------------determina maiores e menores XY------------------------------------------//

double determinaMaiorY(double Y, double MaxY)
{
   if (Y > MaxY)
   {
      MaxY = Y;
   }
   return MaxY;
}

double determinaMenorY(double y, double MinY)
{
   if (y < MinY)
   {
      MinY = y;
   }
   return MinY;
}

double determinaMaiorX(double X, double MaxX)
{
   if (X > MaxX)
   {
      MaxX = X;
   }
   return MaxX;
}

double determinaMenorX(double X, double MinX)
{
   if (X < MinX)
   {
      MinX = X;
   }
   return MinX;
}

//--------------------------------------------------CRIA BORDAS----------------------------------------------------//

void criaBorda(Lista listaFila, XyyTree t, float i, char corb[30], double *MinX, double *MaxX, double *MinY, double *MaxY, Lista listaLinhas)
{

   double Xnl, Ynl, oldXnl, oldYnl; // nl == new line
   void *nodeAux = getBegin(listaFila);
   void *pontoXY = getInfo(listaFila, nodeAux);
   Xnl = pickXfromxyPoint(pontoXY);
   Ynl = pickYfromxyPoint(pontoXY);

   double firstX = Xnl;
   double firstY = Ynl;
   *MaxX = Xnl;
   *MinX = Xnl;
   *MaxY = Ynl;
   *MinY = Ynl;

   nodeAux = getNext(listaFila, nodeAux);

   while (nodeAux != NULL)
   {
      pontoXY = getInfo(listaFila, nodeAux);
      oldXnl = Xnl;
      oldYnl = Ynl;
      Xnl = pickXfromxyPoint(pontoXY);
      Ynl = pickYfromxyPoint(pontoXY);


      *MaxX = determinaMaiorX(Xnl, *MaxX);
      *MinX = determinaMenorX(Xnl, *MinX);
      *MaxY = determinaMaiorY(Ynl, *MaxY);
      *MinY = determinaMenorY(Ynl, *MinY);

      void *linhaNova = createline(i, oldXnl, oldYnl, Xnl, Ynl, corb);
      insertXyyT(t, oldXnl, oldYnl, linhaNova);

      lista_inserenofim(listaLinhas, linhaNova);
      i++;
      nodeAux = getNext(listaFila, nodeAux);
   }
   void *ultimaLinha = createline(i + 1, Xnl, Ynl, firstX, firstY, corb);

   insertXyyT(t,Xnl,Ynl,ultimaLinha);
   lista_inserenofim(listaLinhas,ultimaLinha);
}

//-----------------------------------------------preenche poligono--------------------------------------------//

double calculaM(double x1, double x2, double y1, double y2)
{
   double m = (y2 - y1) / (x2 - x1);
   return m;
}

double calculaN(double x1, double y1, double m)
{
   double n = y1 - (m * x1);
   return n;
}

void preenchePol(XyyTree t,Lista l, double *MaxY, double *MinY, double *MaxX, double *MinX, int d, int i, char corp[30])
{
   double yatual = *MinY + d;
   int flag = 0;

   while (yatual < *MaxY)
   {
      void *Nodeatual = getBegin(l);
      while (Nodeatual != NULL)
      {
         void *auxline = getInfo(l, Nodeatual);
         double x1,y1,x2,y2,Xaux, Xaux2;
         x1 = getX1line(auxline);
         y1 = getY1line(auxline);
         x2 = getX2line(auxline);
         y2 = getY2line(auxline);
         if(x1!=x2){
            if (determinaMaiorY(y1, y2) > yatual && determinaMenorY(y1,y2) < yatual)
            {
               double m = calculaM(x1,x2,y1,y2);
               double n = calculaN(x1, y1, m);
               flag++;
               if (flag == 2)
               {
                  i++;
                  Xaux2 = (yatual - n) / m;
                  void *linhapreenche = createline(i, Xaux, yatual, Xaux2, yatual, corp);
                  insertXyyT(t,Xaux,yatual,linhapreenche);
                  flag = 0;
               }
               Xaux = (yatual - n) / m;
            }
         }
         else if(x1==x2){
            if (determinaMaiorY(y1, y2) > yatual && determinaMenorY(y1,y2) < yatual)
            {
               flag++;
               if (flag == 2)
               {
                  i++;
                  Xaux2 = x1;
                  void *linhapreenche = createline(i, Xaux, yatual, Xaux2, yatual, corp);
                  insertXyyT(t,Xaux,yatual,linhapreenche);
                  flag = 0;
               }
               Xaux = x1;
            }
         }
         Nodeatual = getNext(l, Nodeatual);
      }
      yatual = yatual + d;
   }
}
//------------------------------------------------FUNÇÂO POL----------------------------------------------------//

void funcPOL(float i, float d, float e, char corb[30], char corp[30], Fila qOriginal, XyyTree t)
{
   void *listaFila = inicia();
   importQueue(listaFila, qOriginal);

   double *maxX, *minX, *maxY, *minY;
   Lista listaLinhas = inicia();


   criaBorda(listaFila, t, i, corb, &minX, &maxX, &minY, &maxY, listaLinhas);
   preenchePol(t,listaLinhas, &maxY, &minY, &maxX, &minX, d, i, corp);
   freeLISTA(listaFila,0);
   freeLISTA(listaLinhas,0);
}

void readQRY(XyyTree t, double epsilon, Path pathh, Fila q, Lista selecionados)
{
   if (getArqqry(pathh) != NULL)
   {

      finalqry(pathh);
      finaloutqry(pathh);
      FILE *arquivo = fopen(getqry(pathh), "r");
      finaltxt(pathh);
      FILE *txtname = fopen(gettxtname(pathh), "w");
      fprintf(txtname,"-------TXT MARCOS VINICIUS PRETTI--------");
      // FILE *txtname = fopen("report.txt","a");
      // FILE *arquivo = fopen("comandos.qry", "r");
      finalsvgqry(pathh);
      FILE *svgname = fopen(getsvgqry(pathh), "w");
      // FILE *svgname = fopen("svgQRY.svg","w");
      openTagSVG(svgname);

      char leitura[50];

      while (fscanf(arquivo, "%s ", leitura) != -1)
      {

         if (strcmp(leitura, "inp") == 0)
         {
            float id;
            fscanf(arquivo, "%f", &id);
            funcINP(id, t, q, txtname);
         }

         else if (strcmp(leitura, "rmp") == 0)
         {
            funcRMP(q, txtname);
         }

         else if (strcmp(leitura, "pol") == 0)
         {
            float i, d, e;
            char corb[30], corp[30];
            fscanf(arquivo, "%f %f %f %s %s", &i, &d, &e, corb, corp);
            // fgets(corb,30,arquivo);
            // fgets(corp,30,arquivo);
            funcPOL(i, d, e, corb, corp, q, t);
         }

         else if (strcmp(leitura, "clp") == 0)
         {
            funcCLP(q);
         }

         else if (strcmp(leitura, "sel") == 0)
         {
            double xon, yon, won, hon;
            fscanf(arquivo, "%lf %lf %lf %lf", &xon, &yon, &won, &hon);
            selecionados = funcSEL(xon, yon, won, hon, t, selecionados, txtname, svgname);
         }

         else if (strcmp(leitura, "sel+") == 0)
         {
            double x, y, w, h;
            fscanf(arquivo, "%lf %lf %lf %lf", &x, &y, &w, &h);

            funcSELplus(x, y, w, h, t, selecionados, txtname, svgname);
         }

         else if (strcmp(leitura, "dels") == 0)
         {
            selecionados = funcDELS(t, selecionados, txtname);
         }

         else if (strcmp(leitura, "dps") == 0)
         {
            float i;
            double dx, dy;
            char corb[30], corp[30];
            fscanf(arquivo, "%f %lf %lf %s %s", &i, &dx, &dy, corb, corp);
            funcDPS(i, dx, dy, corb, corp, t, selecionados);
         }

         else if (strcmp(leitura, "ups") == 0)
         {
            char corb[30], corp[30];
            double dx, dy;
            float n;
            fscanf(arquivo, "%s %s %lf %lf %f", corb, corp, &dx, &dy, &n);
            funcUPS(corb,corp,dx,dy,n,selecionados,t);
         }

         else
         {
            printf("\n o que ocorreu??");
         }
      }
      
      writeTree(svgname, t);
      dumpTree(t,txtname);
      freeLISTA(selecionados,0);
      closeTagSVG(svgname);
      fclose(arquivo);
      fclose(svgname);
      fclose(txtname);
   }
}