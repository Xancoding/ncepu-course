#include <iostream>
#include <vector>

using namespace std;

class Student {
public:
    string name;
    int age;

    Student(string name, int age) {
        this->name = name;
        this->age = age;
    }

    bool operator>(const Student& other) const {
        return this->age > other.age;
    }
};

template <typename T>
T max_element(vector<T> arr) {
    T max_value = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    return max_value;
}

int main() {
    // 创建学生对象数组
    vector<Student> students = {
            Student("张三", 20),
            Student("李四", 22),
            Student("王五", 18),
            Student("赵六", 21),
    };

    // 使用函数模板返回年龄最大的学生
    Student max_age_student = max_element(students);
    cout << "年龄最大的学生：" << max_age_student.name << "，年龄：" << max_age_student.age << endl;

    return 0;
}
