#include <fstream>
#include <iostream>
#include <cmath>
#include "helpers.h"
#include "solid.h"


class Cylinder : public Solid {
    int numSlices;
    float radius;
    float height;
public:
    Cylinder(int numSlices, float radius, float height)
    : Solid("cylinder"), numSlices(numSlices), radius(radius), height(height) {};
    void printTriangles(std::ostream& out) const;
};

void Cylinder::printTriangles(std::ostream& out) const
{
    const float delta_a = 2 * M_PI / static_cast<float>(numSlices);

    Trianglef t(
        Vertex3f(0, 0, 0),
        Vertex3f(radius, 0, 0),
        Vertex3f(cos(delta_a)*radius, sin(delta_a)*radius, 0)
    );

    Vertex3f vertTransl = Vertex3f(0, 0, height);

    for (int i = 1; i <= numSlices; i++) {
        // base
        out << t;

        // roof
        out << Trianglef(
            t.getV1() + vertTransl,
            t.getV2() + vertTransl,
            t.getV3() + vertTransl
        );

        // sides
        out << Trianglef(
            t.getV2(),
            t.getV3(),
            t.getV2() + vertTransl
        );
        out << Trianglef(
            t.getV3(),
            t.getV3() + vertTransl,
            t.getV2() + vertTransl
        );

        t = Trianglef(
            t.getV1(),
            t.getV3(),
            Vertex3f(cos(delta_a * (i+1))*radius, sin(delta_a * (i+1))*radius, 0)
        );
    }
}

void makeCylinder(const std::string& filename) {
    std::ofstream out(filename);

    if(!out) {
        std::cerr << "Failed to open file!\n";
        return;
    }

    Cylinder c(64, 0.5, 2.0);
    out << c;
}
