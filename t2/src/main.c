#include "Tree.h"
#include "funcqry.h"
#include "path.h"
#include "geo.h"




int main(int argc, char* argv[])
{
    void *pathh = createPaths();
    //initializepath(pathh);

    readpaths(pathh,argc,argv);
    

    double epsilon = 0.001;
    XyyTree tree = newXyyTree(0.99);

    readgeo(tree,pathh);
    
    readQRY(tree,epsilon,pathh);
   
   
    DestroiXyyT(tree);
    freepaths(pathh);
}
