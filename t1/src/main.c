#include "Tree.h"
#include "funcqry.h"
#include "path.h"
#include "geo.h"




int main(int argc, char* argv[])
{
    Path path = createPaths();
    readpaths(path,argc,argv);
    XyyTree tree = newXyyTree(0.5);
    Fila q = newQueue();
    Lista l = inicia();
    readgeo(tree,path);
    readQRY(tree,0.001,path,q,l);
    DestroiXyyT(tree);
    freepaths(path);
}
