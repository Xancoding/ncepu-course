//
// Created by 24398 on 2023/6/14.
//
#ifndef OS_COURSE_PROCESS_H
#define OS_COURSE_PROCESS_H

/*进程控制块（PCB）结构定义
 * 进程状态：
 * 0 为可执行态；
 * 1 为等待状态 1，表示输出井满，请求输出的用户进程等待；
 * 2 为等待状态 2，表示请求输出块空，SP00LING输出进程等待；
 * 3 为等待状态 3，表示请求输出块满，请求输出的用户进程等待；
 * 4 为结束态，进程执行完成。
 */
struct PCB {
    int id;      // 进程标识数
    int status;  // 进程状态
    int count;   // 要输出的文件数
    int x;       // 进程输出时的临时变量
};

// 请求输出块（reqblock）结构定义
struct ReqBlock {
    int reqname;  // 请求进程名
    int length;   // 本次输出信息长度
    int addr;     // 信息在输出井的首地址
};

// 进程调度函数声明
void schedule();
// 其他与进程相关的函数声明
void initialize();
void userProcess1();
void userProcess2();
void spoolingProcess();
void spoolingService(int process_number);
int getRandomNumber(int min, int max);

#endif //OS_COURSE_PROCESS_H
