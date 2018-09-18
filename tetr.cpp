#include <fstream>
#include <iostream>


void makeSolid() {
    std::ofstream out("/Users/marko/Develop/1.stl");

    if(!out) {
        std::cerr << "Nooo\n";
        std::cerr << "Error: " << strerror(errno);
    }

    float coords[4][3] = {
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 1.0f },
        { 1.0f, 1.0f, 0.0f }
    };

    out << "solid ascii\n";

    out << "facet normal -1 0 0\n";
    out << "outer loop\n";
    out << "vertex " << coords[0][0] << " " << coords[0][1] << " " << coords[0][2] << "\n";
    out << "vertex " << coords[1][0] << " " << coords[1][1] << " " << coords[1][2] << "\n";
    out << "vertex " << coords[2][0] << " " << coords[2][1] << " " << coords[2][2] << "\n";
    out << "endloop\n";
    out << "endfacet\n";

    out << "facet normal -1 0 0\n";
    out << "outer loop\n";
    out << "vertex " << coords[1][0] << " " << coords[1][1] << " " << coords[1][2] << "\n";
    out << "vertex " << coords[2][0] << " " << coords[2][1] << " " << coords[2][2] << "\n";
    out << "vertex " << coords[3][0] << " " << coords[3][1] << " " << coords[3][2] << "\n";
    out << "endloop\n";
    out << "endfacet\n";

    out << "facet normal -1 0 0\n";
    out << "outer loop\n";
    out << "vertex " << coords[2][0] << " " << coords[2][1] << " " << coords[2][2] << "\n";
    out << "vertex " << coords[3][0] << " " << coords[3][1] << " " << coords[3][2] << "\n";
    out << "vertex " << coords[0][0] << " " << coords[0][1] << " " << coords[0][2] << "\n";
    out << "endloop\n";
    out << "endfacet\n";

    out << "facet normal -1 0 0\n";
    out << "outer loop\n";
    out << "vertex " << coords[3][0] << " " << coords[3][1] << " " << coords[3][2] << "\n";
    out << "vertex " << coords[0][0] << " " << coords[0][1] << " " << coords[0][2] << "\n";
    out << "vertex " << coords[1][0] << " " << coords[1][1] << " " << coords[1][2] << "\n";
    out << "endloop\n";
    out << "endfacet\n";

    out << "endsolid\n";

    std::cerr << "Done writting\n";
}