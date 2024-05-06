#include <iostream>
#include <cstring>

class Country {
private:
    char* name;
    double area;

public:
    // 默认构造函数
    Country(const char* n, double a) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        area = a;
        std::cout << name << "构造函数" << std::endl;
    }

    // 拷贝构造函数
    Country(const Country& c) {
        name = new char[strlen(c.name) + 1];
        strcpy(name, c.name);
        area = c.area;
        std::cout << c.name << "拷贝构造函数" << std::endl;
    }

    // 析构函数
    ~Country() {
        std::cout << name << "析构函数" << std::endl;
        delete[] name;
    }

    const char* getName() const {
        return name;
    }

    double getArea() const {
        return area;
    }

    // 显示信息
    void display() const {
        std::cout << "国家：" << name << " 面积：" << area << std::endl;
    }

    // 比较国土面积
    std::string compareArea(const Country& c) const {
        if (area > c.area) {
            return ">";
        } else if (area < c.area) {
            return "<";
        } else {
            return "=";
        }
    }
};

int main() {
    // 测试
    Country c1("China", 960.0);
    Country c2(c1);
    Country c3("USA", 937.0);

    c1.display();
    c2.display();
    c3.display();

    std::cout << c1.getName() << c1.compareArea(c2) << c2.getName() << std::endl;
    std::cout << c1.getName() << c1.compareArea(c3) << c3.getName() << std::endl;

    return 0;
}