#include <iostream>
#include <string>

using namespace std;

class Student {
public:
    string name;
    int score;

    // 构造函数
    Student(string name, int score) {
        this->name = name;
        this->score = score;
    }

    // 赋值运算符重载
    Student& operator=(const Student& other) {
        // 姓名不变
        // this->name = other.name; // 注释掉这行代码，实现只有成绩变化
        this->score = other.score;
        return *this;
    }

    // 友元函数，实现cout<<学生对象
    friend ostream& operator<<(ostream& os, const Student& stu) {
        os << "姓名：" << stu.name << ", 成绩：" << stu.score;
        return os;
    }

    // 运算符重载，以成绩判断两个学生是否相等
    bool operator==(const Student& other) const {
        return this->score == other.score;
    }
};

int main() {
    Student stu1("张三", 90);
    Student stu2("李四", 80);

    // 测试赋值运算符
    stu1 = stu2;
    cout << stu1 << endl; // 输出：姓名：张三, 成绩：80

    // 测试cout<<学生对象
    cout << stu2 << endl; // 输出：姓名：李四, 成绩：80

    // 测试运算符重载
    if (stu1 == stu2) {
        cout << "两个学生成绩相同" << endl;
    } else {
        cout << "两个学生成绩不同" << endl;
    }

    return 0;
}
