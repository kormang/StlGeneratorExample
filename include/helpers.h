#pragma once
#include <iostream>

template <typename T>
class Point3 {
public:
    T x;
    T y;
    T z;

    Point3(T x, T y, T z): x(x), y(y), z(z) {};
};

typedef Point3<float> Point3f;

template <typename T>
class Vector3 : public Point3<T> {
public:
    Vector3(T x, T y, T z): Point3<T>(x, y, z) {};

    T dot(const Vector3<T>& b) const;
    Vector3<T> cross(const Vector3<T>& b) const;
    static Vector3<T> fromSpherical(T longitude, T latitude, T radius);

    friend std::ostream& operator<<(std::ostream& out, const Vector3<T> v) {
        out << v.x << " " << v.y << " " << v.z;
        return out;
    }
};

typedef Vector3<float> Vector3f;

template <typename T>
using Vertex3 = Vector3<T>;

typedef Vertex3<float> Vertex3f;

typedef Vertex3<float> Vertex3f;

template <typename T>
Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b) {
    return Vector3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template <typename T>
Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b) {
    return Vector3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template <typename T>
Vector3<T> operator*(T a, const Vector3<T>& b) {
    return Vector3<T>(a * b.x, a * b.y, a * b.z);
}

template <typename T>
Vector3<T> operator*(const Vector3<T>& a, T b) {
    return b * a;
}

template <typename T>
T Vector3<T>::dot(const Vector3<T>& b) const {
    return this->x * b.x + this->y * b.y + this->z * b.z;
}

template <typename T>
T dot(const Vector3<T>& a, const Vector3<T>& b) {
    return a.dot(b);
}

template <typename T>
Vector3<T> operator*(const Vector3<T>& a, const Vector3<T>& b) {
    return Vector3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template <typename T>
Vector3<T> operator/(const Vector3<T>& a, T b) {
    return Vector3<T>(a.x / b, a.y / b, a.z / b);
}

template <typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T>& b) const {
    return Vector3<T>(
        this->y * b.z - b.y * this->z,
        b.x * this->z - this->x * b.z,
        this->x * b.y - this->y * b.x
    );
}

template <typename T>
Vector3<T> cross(const Vector3<T>& a, const Vector3<T>& b) {
    return a.cross(b);
}

template <typename T>
Vector3<T> Vector3<T>::fromSpherical(T longitude, T latitude, T radius) {
    const T z = radius * sin(latitude);
    const T xyproj = radius * cos(latitude);
    const T x = xyproj * cos(longitude);
    const T y = xyproj * sin(longitude);
    return Vector3<T>(x, y, z);
}

template <typename T>
Vector3<T> zero() {
    return Vector3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
}

Vector3f zerof() {
    return zero<float>();
}

template <typename T>
T norm2(Vector3<T> v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

template <typename T>
Vector3<T> normalize(Vector3<T> v) {
    T n = norm2(v);
    return n != 0 ? v / n : v;
}

template <typename T>
class Triangle {
private:
    union {
        Vertex3<T> vertices[3];
        struct {
            Vertex3<T> v1;
            Vertex3<T> v2;
            Vertex3<T> v3;
        };
    };

    Vector3<T> normal;
    static unsigned int splitNTimes;
public:
    Triangle(
        const Vertex3<T>& v1,
        const Vertex3<T>& v2,
        const Vertex3<T>& v3,
        const Vertex3<T>& normal)
        : v1(v1), v2(v2), v3(v3)
        {};

    Triangle(
        const Vertex3<T>& v1,
        const Vertex3<T>& v2,
        const Vertex3<T>& v3)
        : v1(v1), v2(v2), v3(v3), normal(calculateRightHandNormal())
        {};

    Vector3<T> calculateRightHandNormal() {
        Vector3<T> va = v2 - v1;
        Vector3<T> vb = v3 - v1;
        Vector3<T> orthogonal = cross(va, vb);
        return normalize(orthogonal);
    }

    void setCalculateRightHandNormal() {
        normal = calculateRightHandNormal();
    }

    const Vertex3<T>& getVertex1() const { return v1; };
    const Vertex3<T>& getVertex2() const { return v2; };
    const Vertex3<T>& getVertex3() const { return v3; };
    const Vertex3<T>& getV1() const { return v1; };
    const Vertex3<T>& getV2() const { return v2; };
    const Vertex3<T>& getV3() const { return v3; };
    const Vector3<T>& getNormal() const { return normal; };

    void printVertices(std::ostream& out, int level) const {
        if (level) {
            Vertex3<T> sv1 = ((vertices[1] - vertices[0]) / 2.0f) + vertices[0];
            Vertex3<T> sv2 = ((vertices[2] - vertices[0]) / 2.0f) + vertices[0];
            Vertex3<T> sv3 = ((vertices[2] - vertices[1]) / 2.0f) + vertices[1];

            Triangle<T> t1(vertices[0], sv1, sv2);
            t1.printVertices(out, level - 1);
            Triangle<T> t2(sv1, vertices[1], sv3);
            t2.printVertices(out, level - 1);
            Triangle<T> t3(sv2, sv3, vertices[2]);
            t3.printVertices(out, level - 1);
            Triangle<T> t4(sv1, sv3, sv2);
            t4.printVertices(out, level - 1);
        } else {
            out << "facet normal " << normal.x << " " << normal.y << " " << normal.z << std::endl;
            out << "\touter loop\n";
            for (int i = 0; i < 3; ++i) {
            out << "\t\tvertex " << vertices[i] << std::endl;
            }
            out << "\tendloop\n";
            out << "endfacet\n";
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const Triangle<T>& triangle) {
        triangle.printVertices(out, Triangle<T>::splitNTimes);
        return out;
    }

    class Split {
        unsigned int times;
        public:
            Split(unsigned int times):times(times) {}
            friend std::ostream& operator<<(std::ostream& out, const Triangle<T>::Split& split) {
                Triangle<T>::splitNTimes = split.times;
                return out;
            }
    };
};


template <typename T> unsigned int Triangle<T>::splitNTimes = 0;

typedef Triangle<float> Trianglef;
