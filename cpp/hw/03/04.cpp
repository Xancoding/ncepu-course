//
// Created by 24398 on 2024/3/19.
//
// 4. 计算机组成部分的类定义及测试
#include <iostream>

class CPU {
public:
    void run() { std::cout << "CPU is running..." << std::endl; }
};

class Memory {
public:
    void load() { std::cout << "Loading data from memory..." << std::endl; }
};

class HardDisk {
public:
    void read() { std::cout << "Reading data from hard disk..." << std::endl; }
};

int main() {
    CPU cpu;
    Memory mem;
    HardDisk hd;

    cpu.run();
    mem.load();
    hd.read();

    return 0;
}