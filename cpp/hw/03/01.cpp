#include "iostream"
#include <cmath>

// 1. 复数类
class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    friend Complex operator+(const Complex& c1, const Complex& c2);
    friend Complex operator-(const Complex& c1, const Complex& c2);
    friend double modulus(const Complex& c);

    void print() {
        std::cout << real << " + " << imag << "i" << std::endl;
    }
};

// 2. 全局友元函数实现复数相加
Complex operator+(const Complex& c1, const Complex& c2) {
    return Complex(c1.real + c2.real, c1.imag + c2.imag);
}

// 3. 计算类,成员函数都是复数类的友元
class Calculator {
public:
    friend Complex operator-(const Complex& c1, const Complex& c2) {
        return Complex(c1.real - c2.real, c1.imag - c2.imag);
    }

    friend double modulus(const Complex& c) {
        return sqrt(c.real * c.real + c.imag * c.imag);
    }
};

// 测试代码
int main() {
    Complex c1(2.0, 3.0);
    Complex c2(1.0, -2.0);

    std::cout << "Complex number 1: ";
    c1.print();
    std::cout << "Complex number 2: ";
    c2.print();

    Complex c3 = c1 + c2;
    std::cout << "Sum: ";
    c3.print();

    Complex c4 = c1 - c2;
    std::cout << "Difference: ";
    c4.print();

    double mod = modulus(c3);
    std::cout << "Modulus of ";
    c3.print();
    std::cout << "is: " << mod << std::endl;

    return 0;
}