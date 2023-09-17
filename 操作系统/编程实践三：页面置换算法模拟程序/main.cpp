/* FIFO：先进先出算法
 * 将在进程中驻留时间最久的页面换出到外存
 *
 * LRU：最近最久未使用置换算法
 * 选择最近一段时间最长未被访问的页面淘汰出内存
 */
/* 输入：
页面访问序列长度：
20
内存块长度 && 页表长度：
5 8
 */
#include <list>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

/**
 * @brief 从头到尾依次输出链表的值
 *
 * @param page_in_block 内存中的页面
 * @param flag 是否换页
 */
void print_list(list<int>& page_in_block, bool flag, int page_num)
{
    cout << page_num << ":\t";
    for (auto item : page_in_block)
    {
        cout << item << ' ';
    }
    // 输出换页标志
    if (flag)
    {
        cout << "换页!!!";
    }

    cout << '\n';
}

void FIFO(int len, int block_size, vector<int>& page_access_sequence)
{
    int cnt{ 0 };  // 页面置换次数
    list<int> page_in_block;
    cout << "FIFO算法页面置换过程：\t队头---队尾\n";
    for (auto item : page_access_sequence)
    {
        // 页面预装入
        if (page_in_block.size() < block_size)
        {
            // 当前访问的页面不在内存中
            if (find(page_in_block.begin(), page_in_block.end(), item) == page_in_block.end())
            {
                page_in_block.push_back(item);
            }
            print_list(page_in_block, false, item);
        }
        // 预装入完毕
        else
        {
            auto it = find(page_in_block.begin(), page_in_block.end(), item);
            if (it == page_in_block.end())  // 当前访问的页面不在内存中
            {
                ++cnt;
                page_in_block.pop_front();
                page_in_block.push_back(item);
                print_list(page_in_block, true, item);
            }
            print_list(page_in_block, false, item);
        }
    }

    cout << "FIFO算法缺页率：" << (double)cnt / len * 100 << "%\n";
}

void LRU(int len, int block_size, vector<int>& page_access_sequence)
{
    int cnt{ 0 };  // 页面置换次数
    list<int> page_in_block;
    cout << "LRU算法页面置换过程：\t栈底---栈顶\n";
    for (auto item : page_access_sequence)
    {
        // 页面预装入
        if (page_in_block.size() < block_size)
        {
            auto it = find(page_in_block.begin(), page_in_block.end(), item);
            // 当前访问的页面不在内存中
            if (it == page_in_block.end())
            {
                page_in_block.push_back(item);
            }
            // 当前访问的页面在内存中
            else
            {
                page_in_block.erase(it);
                page_in_block.push_back(item);
            }
            print_list(page_in_block, false, item);
        }
        // 预装入完毕
        else
        {
            auto it = find(page_in_block.begin(), page_in_block.end(), item);
            if (it == page_in_block.end())  // 当前访问的页面不在内存中
            {
                ++cnt;
                page_in_block.pop_front();
                page_in_block.push_back(item);
                print_list(page_in_block, true, item);
            }
            else // 当前访问的页面在内存中
            {
                page_in_block.erase(it);
                page_in_block.push_back(item);
                print_list(page_in_block, false, item);
            }
        }
    }

    cout << "LRU算法缺页率：" << (double)cnt / len * 100 << "%\n";
}

int main()
{
    int len;
    cout << "页面访问序列长度：\n";
    cin >> len;

    int block_size, page_size;
    cout << "内存块长度 && 页表长度：\n";
    cin >> block_size >> page_size;

//    vector<int> page_access_sequence{7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
//    vector<int> page_access_sequence{4, 2, 4, 2, 7, 2, 6, 2, 3,  4};
    vector<int> page_access_sequence;

    // 创建一个随机数生成器
    std::random_device rd; // 用于获取随机种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数

    // 创建一个分布，指定随机数的范围
    std::uniform_int_distribution<> dis(0, page_size-1);

    for (int i = 0; i < len; ++i)
    {
        int random_num = dis(gen);
        page_access_sequence.push_back(random_num);
    }

    cout << "页面访问序列：\n";
    for (auto item : page_access_sequence)
    {
        cout << item << ' ';
    }
    cout << '\n';

    FIFO(len, block_size,  page_access_sequence);
    LRU(len, block_size, page_access_sequence);

    return 0;
}