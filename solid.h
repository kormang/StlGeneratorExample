#pragma once
#include <iostream>

class Solid {
    std::string name;
public:
    Solid(const std::string& name): name(name) {}
    virtual ~Solid() {};
    virtual void printTriangles(std::ostream& out) const = 0;

    friend std::ostream& operator<<(std::ostream& out, const Solid& solid);
};

std::ostream& operator<<(std::ostream& out, const Solid& solid) {
    out << "solid " << solid.name << std::endl;
    solid.printTriangles(out);
    out << "endsolid\n";
    return out;
}
