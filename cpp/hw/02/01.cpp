//
// Created by 24398 on 2024/3/6.
//
#include "iostream"

class Rectangle {
private:
    double width;
    double height;

public:
    // 默认构造函数
    Rectangle(double w, double h) {
        width = w;
        height = h;
        std::cout << "构造函数" << std::endl;
    }

    // 拷贝构造函数
    Rectangle(const Rectangle &r) {
        width = r.width;
        height = r.height;
        std::cout << "拷贝构造函数" << std::endl;
    }

    double getArea() {
        return width * height;
    }

    double getPerimeter() {
        return 2 * (width + height);
    }

    void setWidth(double w) {
        width = w;
    }

    void setHeight(double h) {
        height = h;
    }

    double getWidth() {
        return width;
    }

    double getHeight() {
        return height;
    }

    bool isSquare() {
        return width == height;
    }
};

int main() {
    // 测试
    Rectangle r1(3, 4);
    Rectangle r2(r1);
    Rectangle r3(3, 3);

    std::cout << "面积：" << r1.getArea() << " " << "周长：" << r1.getPerimeter() << std::endl;

    std::cout << "面积：" << r2.getArea() << " " << "周长：" << r2.getPerimeter() << std::endl;

    std::cout << "是否为正方形：" << r3.isSquare() << std::endl;
    std::cout << "是否为正方形：" << r1.isSquare() << std::endl;

    return 0;
}