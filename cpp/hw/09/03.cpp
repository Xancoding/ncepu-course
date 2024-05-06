#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// 函数对象用于统计长度为 specific_length 的名字数量
struct CountLength {
    int specific_length;
    CountLength(int length) : specific_length(length) {}

    bool operator()(const std::string& name) const {
        return name.length() == specific_length;
    }
};

// 函数对象用于统计名字中包含特定字符串的数量
struct CountContains {
    std::string substring;
    CountContains(const std::string& str) : substring(str) {}

    bool operator()(const std::string& name) const {
        return name.find(substring) != std::string::npos;
    }
};

int main() {
    std::vector<std::string> names = {"张三", "李四", "王刚", "陈平", "李刚", "张小飞"};

    // 使用 std::count_if 和函数对象统计长度为4的名字数量
    int count2 = std::count_if(names.begin(), names.end(), CountLength(4));
    std::cout << "2个汉字的人数: " << count2 << std::endl;

    // 使用 std::count_if 和函数对象统计长度为6的名字数量
    int count3 = std::count_if(names.begin(), names.end(), CountLength(6));
    std::cout << "3个汉字的人数: " << count3 << std::endl;

    // 使用 std::count 和函数对象统计包含"刚"的名字数量
    int countContains = std::count_if(names.begin(), names.end(), CountContains("刚"));
    std::cout << "名字带有\"刚\"的人数: " << countContains << std::endl;

    return 0;
}
