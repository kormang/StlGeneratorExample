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

class Sphere : public Solid {
    int halfNumVertSlices;
    float radius;
    static const Vertex3f inverseZ;

    void pt(std::ostream& out, const Trianglef& t) const;
public:
    Sphere(int halfNumVertSlices, float radius)
    : Solid("sphere"), halfNumVertSlices(halfNumVertSlices), radius(radius) {};
    void printTriangles(std::ostream& out) const;
};

const Vertex3f Sphere::inverseZ(1, 1, -1);

void Sphere::pt(std::ostream& out, const Trianglef& t) const {
    out << t;
    out << Trianglef(
        t.getV1() * inverseZ,
        t.getV2() * inverseZ,
        t.getV3() * inverseZ
    );
}

void Sphere::printTriangles(std::ostream& out) const
{
    // using some math we get that horizSlices must be > 4 * halfNumVertSlices,
    // for solid to be always convex
    const int horizSlices = 4 * halfNumVertSlices;
    const float delta_h = (2.0f * M_PI) / static_cast<float>(horizSlices);
    const float ndeg = M_PI / 2.0f;
    const float delta_v = ndeg / static_cast<float>(halfNumVertSlices);
    const float delta_hh = delta_h / 2.0f;

    Trianglef t(
        Vertex3f(0, 0, radius),
        Vertex3f::fromSpherical(0, ndeg - delta_v, radius),
        Vertex3f::fromSpherical(delta_h, ndeg - delta_v, radius)
    );

    // cap
    for (int i = 1; i <= horizSlices; ++i) {
        pt(out, t);

        t = Trianglef(
            t.getV1(), // top
            t.getV3(), // 1st bottom
            Vertex3f::fromSpherical(delta_h * (i + 1), ndeg - delta_v * (1), radius) // 2nd bottom
        );
    }

    // rows
    for (int row = 1; row < halfNumVertSlices; ++row) {
        for (int i = 1; i <= horizSlices; ++i) {
            const float topAngle = delta_h * (i - 1)
                + delta_hh * !(row % 2); // add half angle on every even row
            t = Trianglef(
                Vertex3f::fromSpherical(topAngle, ndeg - delta_v * (row), radius), // top
                Vertex3f::fromSpherical(topAngle - delta_hh, ndeg - delta_v * (row+1), radius), // 1st bottom
                Vertex3f::fromSpherical(topAngle + delta_hh, ndeg - delta_v * (row+1), radius) // 2nd bottom
            );
            pt(out, t);
            t = Trianglef(
                Vertex3f::fromSpherical(topAngle, ndeg - delta_v * (row), radius), // 1st top
                Vertex3f::fromSpherical(topAngle + delta_h, ndeg - delta_v * (row), radius), // 2nd top
                Vertex3f::fromSpherical(topAngle + delta_hh, ndeg - delta_v * (row+1), radius) // bottom
            );
            pt(out, t);
        }
    }

}

void makeSphere(const std::string& filename) {
    std::ofstream out(filename);

    if(!out) {
        std::cerr << "Failed to open file!\n";
        return;
    }

    Sphere s(6, 1.0f);
    out << s;
}
