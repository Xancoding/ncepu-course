#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    // 打开要复制的源文件
    ifstream source_file("source.jpg", ios::binary);
    if (!source_file) {
        cerr << "无法打开源文件" << endl;
        return 1;
    }

    // 创建目标文件
    ofstream target_file("copy.jpg", ios::binary);
    if (!target_file) {
        cerr << "无法创建目标文件" << endl;
        return 1;
    }

    // 读取源文件内容并写入目标文件
    vector<char> buffer(1024);
    while (!source_file.eof()) {
        source_file.read(buffer.data(), buffer.size());
        target_file.write(buffer.data(), source_file.gcount());
    }

    source_file.close();
    target_file.close();

    cout << "文件复制成功" << endl;

    return 0;
}