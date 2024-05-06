//
// Created by 24398 on 2024/4/11.
//
#include <iostream>
#include <map>

using namespace std;

int main() {
    // 创建map容器
    map<string, string> id_name;

    // 添加数据
    id_name["1234567890"] = "张三";
    id_name["9876543210"] = "李四";
    id_name["0123456789"] = "王五";

    // 查询数据
    cout << "张三的身份证号码：" << id_name["1234567890"] << endl;

    // 修改数据
    id_name["9876543210"] = "李二";
    cout << "修改后李四的姓名：" << id_name["9876543210"] << endl;

    // 删除数据
    id_name.erase("0123456789");

    // 遍历数据
    for (auto it = id_name.begin(); it != id_name.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

    return 0;
}
