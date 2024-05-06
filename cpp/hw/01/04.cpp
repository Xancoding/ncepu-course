//
// Created by 24398 on 2024/2/28.
//
#include "iostream"

// 自定义一个命名空间，将函数放入其中，然后在main函数调用。
namespace my {
    void swap(int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }
}

int main() {
    int a, b;
    std::cin >> a >> b;

    my::swap(a, b);

    std::cout << a << " " << b << std::endl;

    return 0;
}