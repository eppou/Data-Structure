#include "functionspath.h"
#include "path.h"

char *ajustabarra(char *path)
{
    printf("\nsalvee");
    int fim = strlen(path);
    printf("END: %d\n", fim);
    if (path[fim - 1] != '/')
    {
        path = realloc(path, strlen(path) + 2);
        strcat(path, "/");
    }
    return path;
}

void readArgv(int argc, char **argv,Path p)
{

    int i = 1;
    while (i < argc)
    {
        printf("\n\noi");
        if (strcmp(argv[i], "-f") == 0)
        {
            i++;
            char *arqGeo = calloc((strlen(argv[i]) + 5) , sizeof(char));
            strcpy(arqGeo, argv[i]);
            printf("Parametro -f: %s\n", arqGeo);
            set_ArqGeo(p,arqGeo);
        }
        else if (strcmp(argv[i], "-e") == 0)
        {
            i++;
            char *in = calloc(strlen(argv[i]) + 10, sizeof(char));
            puts("!");
            strcpy(in, argv[i]);
            printf("Parametro -e: %s\n", in);
            in = ajustabarra(in);
            set_Inpath(p,in);
            printf("Parametroaaaaaaaaaaaaa -e: %s\n", in);
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            i++;
            char *arqQry = calloc((strlen(argv[i]) + 1),sizeof(char));
            strcpy(arqQry, argv[i]);
            printf("Parametro -q: %s\n", arqQry);
            set_ArqQry(p,arqQry);

        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            i++;
            char *outPath = calloc((strlen(argv[i]) + 5), sizeof(char));
            strcpy(outPath, argv[i]);
            printf("Parametro -o: %s\n", outPath);
            if (outPath != NULL)
            {
                outPath = ajustabarra(outPath);
                set_Outpath(p,outPath);
            }
        }
        i++;
    }
   
}

char *concatenageo(char *Inpath, char *filename, char *ArqGeo)
{

    if (Inpath == NULL && ArqGeo[0] == '/')
    {
        strcpy(filename, ArqGeo);
    }
    else
    { // Senão concatena com path
        strcpy(filename, Inpath);
        strcat(filename, ArqGeo);
    }
    return filename;
}

char *makegeo(char *path, char *arqgeo)
{
    int i = strlen(path);
    int j = strlen(arqgeo);
    char *geo = (char *)malloc((i + j + 1) * sizeof(char));
    geo = concatenageo(path, geo, arqgeo);
    return geo;
}

char *tiraptipo(char *nome, char *filename)
{

    char *aux = NULL;
    int i, end;
    aux = strrchr(nome, '/');
    if (aux != NULL)
    {
        i = strlen(aux) - 4;
        filename = (char *)malloc((i + 1) * sizeof(char));
        strncpy(filename, aux, i);
        end = i;
        for (i = 0; i < end - 1; i++)
        {
            filename[i] = filename[i + 1];
        }
        filename[i] = '\0';
    }
    else
    {
        i = strlen(nome) - 4;
        filename = (char *)malloc((i + 1) * sizeof(char));
        strncpy(filename, nome, i);
        filename[i] = '\0';
    }
    return filename;
}

char *concatenaOutGeo(char *OutPath, char *filename, char *ArqGeo)
{

    char *Semptipo = NULL;

    Semptipo = tiraptipo(ArqGeo, Semptipo);
    strcpy(filename, OutPath);
    strcat(filename, Semptipo);
    free(Semptipo);
    return filename;
}

char *makeoutgeo(char *arqgeo, char *outpath)
{

    int i = strlen(outpath);
    int k = strlen(arqgeo);
    char *filename = (char *)malloc((i + k + 1) * sizeof(char));
    filename = concatenaOutGeo(outpath, filename, arqgeo);
    return filename;
}

char *concatenaqry(char *Inpath, char *filename, char *ArqQry)
{

    if (Inpath == NULL && ArqQry[0] == '/')
    {
        strcpy(filename, ArqQry);
    }
    else
    { // Senão concatena com path
        strcpy(filename, Inpath);
        strcat(filename, ArqQry);
    }
    return filename;
}

char *saidaSvg(char *Outpathconc, char *filename)
{

    strcpy(filename, Outpathconc);
    strcat(filename, ".svg");

    return filename;
}

char *makesvgname(char *outgeo)
{

    int i = strlen(outgeo);
    char *filename = (char *)malloc((i + 5) * sizeof(char));
    filename = saidaSvg(outgeo, filename);

    return filename;
}

char *concatenaOutQry(char *OutPath, char *filename, char *ArqQry, char *Sembarrageo)
{

    char *Semptipoqry = NULL;

    Semptipoqry = tiraptipo(ArqQry, Semptipoqry);
    strcpy(filename, OutPath);
    strcat(filename, Sembarrageo);
    strcat(filename, Semptipoqry);
    free(Semptipoqry);
    return filename;
}

char *makeqry(char *inpath, char *arqqry)
{
    int i = strlen(arqqry);
    int j = strlen(inpath);
    char *filename = (char *)malloc((i + j + 1) * sizeof(char));
    filename = concatenaqry(inpath, filename, arqqry);
    return filename;
}

char *makeoutqry(char *outpath, char *arqqry, char *arqgeo)
{
    char *Semptipo = tiraptipo(arqgeo, Semptipo);
    char *Semptipoqry = tiraptipo(arqqry, Semptipoqry);
    int i = strlen(Semptipo);
    int j = strlen(Semptipoqry);
    int k = strlen(outpath);
    char *filename = (char *)malloc((k + j + i + 1) * sizeof(char));

    filename = concatenaOutQry(outpath, filename, arqqry, Semptipo);
    free(Semptipo);
    free(Semptipoqry);
    return filename;
}

char *makesvgnameqry(char *outqry)
{
    int i = strlen(outqry);
    char *filename = (char *)malloc((i + 5) * sizeof(char));
    filename = saidaSvg(outqry, filename);
    return filename;
}

char *maketxtname(char *outqry)
{
    int i = strlen(outqry);
    char *filename = (char *)malloc((i + 5) * sizeof(char));
    strcpy(filename, outqry);
    strcat(filename, ".txt");

    return filename;
}
