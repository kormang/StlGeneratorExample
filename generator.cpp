#include <fstream>
#include <iostream>
#include <cmath>

void triangle(std::ofstream& out, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
    out << "facet normal -1 0 0\n";
    out << "outer loop\n";
    out << "vertex " << x1 << " " << y1 << " " << z1 << "\n";
    out << "vertex " << x2 << " " << y2 << " " << z2 << "\n";
    out << "vertex " << x3 << " " << y3 << " " << z3 << "\n";
    out << "endloop\n";
    out << "endfacet\n";
}

void makeCilinder(const std::string& filename) {
    std::ofstream out(filename);

    if(!out) {
        std::cerr << "Nooo\n";
        std::cerr << "Error: " << strerror(errno);
    }

    float c[3][3] = {
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f }
    };

    out << "solid ascii\n";

    const float r = 1.0f;
    float a = 0.0f;

    const int num_tri = 8;
    const float delta_a = 2 * M_PI / num_tri;
    
    c[1][1] = 1.0f;
    c[1][0] = 0.0f;
    a += delta_a;
    c[2][1] = r * sinf(a);
    c[2][0] = r * cosf(a);
    triangle(out, c[0][0], c[0][1], c[0][2], c[1][0], c[1][1], c[1][2], c[2][0], c[2][1], c[2][2]);

    c[1][1] = r * sinf(a);
    c[1][0] = r * cosf(a);
    a += delta_a;
    c[2][1] = r * sinf(a);
    c[2][0] = r * cosf(a);
    triangle(out, c[0][0], c[0][1], c[0][2], c[1][0], c[1][1], c[1][2], c[2][0], c[2][1], c[2][2]);


    out << "endsolid\n";

    std::cerr << "Done writting\n";
}