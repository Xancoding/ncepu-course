#include <iostream>

class Animal {
public:
    virtual void move() = 0;  // 纯虚函数，必须在子类中实现
    virtual ~Animal() {}  // 虚析构函数

protected:
    int m_age;
    std::string m_name;
};

class LandAnimal : public virtual Animal {
public:
    LandAnimal() {
        std::cout << "陆地动物创建成功" << std::endl;
    }

    void move() override {
        std::cout << "陆地动物在地上行走" << std::endl;
    }

protected:
    int m_leg_num;
};

class AquaticAnimal : public virtual Animal {
public:
    AquaticAnimal() {
        std::cout << "水生动物创建成功" << std::endl;
    }

    void move() override {
        std::cout << "水生动物在水中游泳" << std::endl;
    }

protected:
    int m_fin_num;
};

class Amphibian : public LandAnimal, public AquaticAnimal {
public:
    Amphibian() {
        std::cout << "两栖动物创建成功" << std::endl;
    }

    void move() override {
        std::cout << "两栖动物既能在陆地上行走，也能在水中游泳" << std::endl;
    }
};

int main() {
    // 创建不同类的对象并进行测试
    Animal* animal = new Amphibian();
    animal->move();  // 输出：两栖动物既能在陆地上行走，也能在水中游泳

    LandAnimal* land_animal = new Amphibian();
    land_animal->move();  // 输出：两栖动物既能在陆地上行走，也能在水中游泳

    AquaticAnimal* aquatic_animal = new Amphibian();
    aquatic_animal->move();  // 输出：两栖动物既能在陆地上行走，也能在水中游泳

    delete animal;
    delete land_animal;
    delete aquatic_animal;

    return 0;
}
