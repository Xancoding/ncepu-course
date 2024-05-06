#include <iostream>
#include <queue>
#include <cmath> // for abs() function

using namespace std;

// 类模板 Compare
template<typename T>
class Compare {
private:
    T var1;
    T var2;
public:
    Compare(T v1, T v2) : var1(v1), var2(v2) {}

    T GetMax() {
        return (var1 > var2) ? var1 : var2;
    }

    T GetMin() {
        return (var1 < var2) ? var1 : var2;
    }
};

// 复数类 Complex
class Complex {
private:
    double real;
    double imag;
public:
    Complex(double r, double i) : real(r), imag(i) {}

    // 获取复数模长
    double modulus() const {
        return sqrt(real * real + imag * imag);
    }

    // 重载 "<" 运算符，按复数模长比较大小
    bool operator<(const Complex &c) const {
        return modulus() < c.modulus();
    }

    // 重载 ">" 运算符，按复数模长比较大小
    bool operator>(const Complex &c) const {
        return modulus() > c.modulus();
    }
};

// 类模板 Queue
template<typename T>
class Queue {
private:
    queue<T> q;
public:
    // 入队
    void enqueue(T item) {
        q.push(item);
    }

    // 出队
    T dequeue() {
        T item = q.front();
        q.pop();
        return item;
    }

    // 判断队列是否为空
    bool isEmpty() {
        return q.empty();
    }

    // 获取队列长度
    int size() {
        return q.size();
    }
};

int main() {
    // 测试类模板 Compare
    Compare<int> intCompare(5, 10);
    cout << "Max: " << intCompare.GetMax() << endl; // Output: Max: 10
    cout << "Min: " << intCompare.GetMin() << endl; // Output: Min: 5

    // 测试复数类 Complex
    Complex c1(3, 4);
    Complex c2(1, -2);

    Compare<Complex> complexCompare(c1, c2);
    cout << "Max modulus: " << complexCompare.GetMax().modulus() << endl; // Output: Max modulus: 5
    cout << "Min modulus: " << complexCompare.GetMin().modulus() << endl; // Output: Min modulus: 2.23607

    // 测试类模板 Queue
    Queue<int> intQueue;
    intQueue.enqueue(10);
    intQueue.enqueue(20);
    intQueue.enqueue(30);

    cout << "Queue size: " << intQueue.size() << endl; // Output: Queue size: 3
    cout << "Dequeue: " << intQueue.dequeue() << endl; // Output: Dequeue: 10
    cout << "Queue size after dequeue: " << intQueue.size() << endl; // Output: Queue size after dequeue: 2

    Queue<string> stringQueue;
    stringQueue.enqueue("Hello");
    stringQueue.enqueue("World");

    cout << "Queue size: " << stringQueue.size() << endl; // Output: Queue size: 2
    cout << "Dequeue: " << stringQueue.dequeue() << endl; // Output: Dequeue: Hello
    cout << "Queue size after dequeue: " << stringQueue.size() << endl; // Output: Queue size after dequeue: 1

    return 0;
}
