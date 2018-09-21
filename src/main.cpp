#include <iostream>
#include "generator.h"

int main(){
    makeTetrahedron("tetrahedron.stl");
    makeCylinder("./cylinder.stl");
    makeSphere("./sphere.stl");
    return 0;
}
