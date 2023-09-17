//
// Created by 24398 on 2023/6/20.
//

#ifndef QT_OS_COURSE_PROCESS_H
#define QT_OS_COURSE_PROCESS_H
#include <iostream>
#include <random>
#include <thread>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <QApplication>

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
    int file_id; // 文件标识数
};

QWidget* mainWindow;
QLabel* user0Label;
QLabel* user1Label;
QLabel* user2Label;
QLabel* user3Label;
QLabel* label1;
QLabel* label2;
QLineEdit* fileCountLineEdit1;
QLineEdit* fileCountLineEdit2;
QPushButton* submitButton;
QTextEdit *outputTextEdit0; // 调度
QTextEdit *outputTextEdit1; // 用户进程1
QTextEdit *outputTextEdit2; // 用户进程2
QTextEdit *outputTextEdit3; // SP00LING进程
QGridLayout *layout;

const int BUFFER_SIZE = 100;
const int NUM_USER_PROCESSES = 2;
const int NUM_REQUEST_BLOCKS = 10;
int buffer[NUM_USER_PROCESSES][BUFFER_SIZE];  // 输出井的缓冲区
int c1[NUM_USER_PROCESSES] = { BUFFER_SIZE, BUFFER_SIZE };  // 输出井可使用的空间
// 输出井使用情况的指针数组，看作是一个环形数组：
// c2[0][0] 表示 buffer[0] 的第一个可用空缓冲指针，c2[0][1] 表示 buffer[0] 的第一个已用缓冲指针
// c2[1][0] 表示 buffer[1] 的第一个可用空缓冲指针，c2[1][1] 表示 buffer[1] 的第一个已用缓冲指针
int c2[NUM_USER_PROCESSES][2] = { {0, 0}, {0, 0} };
int c3 = NUM_REQUEST_BLOCKS;  // 剩余的请求输出块个数
int ptr1 = 0;  // 指向要输出的第一个请求输出块的指针
int ptr2 = 0;  // 指向第一个空闲请求输出块的指针
int last_c2[2] = {0, 0};  // 指向上一次空闲的输出井的指针位置
int file_count[2] = {0, 0};
PCB pcb[NUM_USER_PROCESSES];  // 进程1的PCB、进程2的PCB
PCB spooling_pcb;  // SP00LING进程的PCB
ReqBlock request_blocks[NUM_REQUEST_BLOCKS]; // 请求输出块数组，看成是一个环型数组

// 进程调度函数声明
void schedule();
// 其他与进程相关的函数声明
void initialize();
void userProcess1();
void userProcess2();
void spoolingProcess();
void spoolingService(int process_number);
int getRandomNumber(int min, int max);
// 界面相关函数声明
void showInputWindow();
void showOutputWindow();

#endif //QT_OS_COURSE_PROCESS_H
