#include "iostream"
class Vector3D {
public:
    Vector3D() {}
    Vector3D(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

    // 成员函数实现运算符 + 重载
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
    }

    void Print() const {
        std::cout << "(" << m_x << ", " << m_y << ", " << m_z << ")" << std::endl;
    }

    friend Vector3D operator-(const Vector3D& v1, const Vector3D& v2);

private:
    double m_x, m_y, m_z;
};

Vector3D operator-(const Vector3D& v1, const Vector3D& v2) {
    return Vector3D(v1.m_x - v2.m_x, v1.m_y - v2.m_y, v1.m_z - v2.m_z);
}

int main() {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);

    Vector3D v3 = v1 + v2;
    v3.Print();  // 输出：(5, 7, 9)

    Vector3D v4 = v1 - v2;
    v4.Print();  // 输出：(-3, -3, -3)

    return 0;
}
