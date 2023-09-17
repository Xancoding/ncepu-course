//
// Created by 24398 on 2023/6/14.
//
// process.cpp
#include <iostream>
#include <random>
#include "process.h"

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

PCB pcb[NUM_USER_PROCESSES];  // 进程1的PCB、进程2的PCB
PCB spooling_pcb;  // SP00LING进程的PCB
ReqBlock request_blocks[NUM_REQUEST_BLOCKS]; // 请求输出块数组，看成是一个环型数组

// 生成在[min, max]范围内的随机整数
int getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// 用户进程1
void userProcess1() {
    spoolingService(0);
}

// 用户进程2
void userProcess2() {
    spoolingService(1);
}

// 初始化函数
void initialize() {
    // 初始化进程控制块（PCB）
    for (int i = 0; i < NUM_USER_PROCESSES; ++i) {
        // 用户PCB
        pcb[i].id = i;
        pcb[i].status = 0;
        pcb[i].x = 0;
    }
    // 用户PCB的count，文件数
    std::cout << "Process1 file count = ";
    std::cin >> pcb[0].count;
    std::cout << "Process2 file count = ";
    std::cin >> pcb[1].count;
    if (pcb[0].count == 0) {
        pcb[0].status = 4;
    }
    if (pcb[1].count == 0) {
        pcb[1].status = 4;
    }

    // SP00LING PCB
    spooling_pcb.id = NUM_USER_PROCESSES;
    spooling_pcb.status = 2;
    spooling_pcb.count = 0;
    spooling_pcb.x = 0;

    // 初始化请求输出块
    for (auto & request_block : request_blocks) {
        request_block.reqname = 0;
        request_block.length = 0;
        request_block.addr = 0;
    }

    // 初始化输出井
    for (auto & i : buffer) {
        for (int & j : i) {
            j = 0;
        }
    }
}

// 进程调度函数实现
void schedule() {
    // 进程调度逻辑
    while (!(pcb[0].status == 4 && pcb[1].status == 4 && spooling_pcb.status == 4)) {
        double randomNumber = getRandomNumber(0, 100) / 100.0; // 生成随机数
        if (randomNumber > 0.9 && spooling_pcb.status == 0) {
            // 调度SP00LING输出进程
            std::cout << "-----------------------------------SP00LING process is running.-----------------------------------" << std::endl;
            spoolingProcess();
            std::cout << "-----------------------------------SP00LING process is finished.-----------------------------------" << std::endl;
        } else if (randomNumber > 0.45 && randomNumber <= 0.9 && pcb[1].status == 0) {
            // 调度用户进程2
            std::cout << "-----------------------------------User process 2 is running.-----------------------------------" << std::endl;
            userProcess2();
            std::cout << "-----------------------------------User process 2 is finished.-----------------------------------" << std::endl;
        } else if (randomNumber <= 0.45 && pcb[0].status == 0) {
            // 调度用户进程1
            std::cout << "-----------------------------------User process 1 is running.-----------------------------------" << std::endl;
            userProcess1();
            std::cout << "-----------------------------------User process 1 is finished.-----------------------------------" << std::endl;
        } else if (randomNumber > 0.9 && spooling_pcb.status == 2) {
            // 请求输出块空，SPOOLING输出进程等待
            std::cout << "-----------------------------------SP00LING process:TASK-WAITING2.-----------------------------------" << std::endl;
        } else if (randomNumber > 0.45 && randomNumber <= 0.9 && (pcb[1].status == 1 || pcb[1].status == 3)) {
            // 用户进程2等待
            std::cout << "-----------------------------------process 2:TASK-WAITING";
            std::cout << pcb[1].status << ".-----------------------------------" << std::endl;
        } else if (randomNumber <= 0.45 && (pcb[0].status == 1 || pcb[0].status == 3)) {
            // 用户进程1等待
            std::cout << "-----------------------------------process 1:TASK-WAITING";
            std::cout << pcb[0].status << ".-----------------------------------" << std::endl;
        }
    }
    // 输出所有进程已结束
    std::cout << "All processes have completed." << std::endl;
}

// SP00LING 输出服务程序
void spoolingService(int process_number) {
    while(true) {
        int output = getRandomNumber(0, 9); // 生成随机数
        pcb[process_number].x = output;

        // 输出井已满，等待
        if (c1[process_number] == 0) {
            pcb[process_number].status = 1;
            std::cout << "Process" << process_number + 1 << ":TASK-READY -> TASK-WAITING1" << std::endl;
            std::cout << "Output pool for Process" << process_number + 1 << " is full. Waiting..." << std::endl;
            return;
        }
        // 输出井未满，将输出值写入输出井
        buffer[process_number][c2[process_number][0]] = pcb[process_number].x;
        // 修改输出井计数
        c1[process_number]--;
//        std::cout << "Output written to buffer[" << process_number << "][" << c2[process_number][0] << "]: " << pcb[process_number].x << std::endl;
//        std::cout << "Now,there are " << c1[process_number] << " blocks in buffer[" << process_number << "] left." << std::endl;
        c2[process_number][0] = (c2[process_number][0] + 1) % BUFFER_SIZE;
        if (pcb[process_number].x != 0) continue;

        // 没有空闲请求块，等待
        if (c3 == 0) {
            pcb[process_number].status = 3;
            std::cout << "Process" << process_number + 1 << ":TASK-READY -> TASK-WAITING3" << std::endl;
            std::cout << "No available request blocks. Process" << process_number + 1 << " is waiting..." << std::endl;
            return;
        }
        // 有空闲请求块，将输出值写入请求块
        request_blocks[ptr2].reqname = process_number;
        request_blocks[ptr2].length = (c2[process_number][0] - last_c2[process_number] + BUFFER_SIZE) % BUFFER_SIZE;
        request_blocks[ptr2].addr = last_c2[process_number];
        last_c2[process_number] = c2[process_number][0];
        // 修改请求块计数
        c3--;
        ptr2 = (ptr2 + 1) % NUM_REQUEST_BLOCKS;
        std::cout << "Now,there are " << c1[process_number] << " blocks in Process" << process_number+1 << "'s output well left." << std::endl;
        std::cout << "Process" << process_number + 1 << " request block created." << std::endl;
        std::cout << "Now,there are " << c3 << " request blocks left." << std::endl;

        // 进程文件数减一
        pcb[process_number].count--;
        std::cout << "Process" << process_number+1 << " file count decreased to " << pcb[process_number].count << std::endl;
        // SP00LING输出进程状态设置为就绪
        if (spooling_pcb.status == 2) {
            spooling_pcb.status = 0;
            std::cout << "spooling_process:TASK-WAITING -> TASK-READY." << std::endl;
        }
        // 进程文件数为0，进程结束
        if (pcb[process_number].count == 0) {
            // 进程所有文件全部输出完毕
            // 进程状态设置为结束
            pcb[process_number].status = 4;
            std::cout << "Process" << process_number+1 << ":TASK-READY -> TASK-EXIT." << std::endl;
            return;
        }
    }
}

// SP00LING输出进程
void spoolingProcess() {
    while (true) {
        // 检查请求输出块是否为空
        if (c3 == 10) {
            // 检查两个请求输出的进程是否都结束了
            if (pcb[0].status == 4 && pcb[1].status == 4) {
                // 两个请求输出的进程都结束了，SP00LING进程也结束
                spooling_pcb.status = 4; // 设置为结束状态4
                std::cout << "spooling_process:TASK-READY -> TASK-EXIT." << std::endl;
                return;
            }
            // 请求输出块为空，等待
            spooling_pcb.status = 2; // 设置为等待状态2
            std::cout << "spooling_process:TASK-READY -> TASK-WAITING2." << std::endl;
            // 两个请求输出的进程没有都结束，SP00LING进程继续等待
            std::cout << "No available request blocks. SP00LING process is waiting..." << std::endl;
            return;
        }

        // 请求输出块不为空，按请求输出块输出信息
        std::cout << "Process" << request_blocks[ptr1].reqname+1 << " Outputting information: ";
        // 输出请求块中的信息，长度为length
        for (int i = 0; i < request_blocks[ptr1].length; i++) {
            std::cout << buffer[request_blocks[ptr1].reqname][request_blocks[ptr1].addr + i] << " ";
            // 释放相应的输出井位置，修改输出井计数
            c1[request_blocks[ptr1].reqname]++;
            c2[request_blocks[ptr1].reqname][1] = (c2[request_blocks[ptr1].reqname][1] + 1) % BUFFER_SIZE;
        }
        std::cout << std::endl;

        // 判断是否有等待输出井空的进程
        if (pcb[0].status == 1 && request_blocks[ptr1].reqname == 0) {
            pcb[0].status = 0; // 设置为可执行状态
            std::cout << "Process1:TASK-WAITING1 -> TASK-READY." << std::endl;
            std::cout << "Process1 Outputting well is not full. Process1 is ready." << std::endl;
        }
        if (pcb[1].status == 1 && request_blocks[ptr1].reqname == 1) {
            pcb[1].status = 0; // 设置为可执行状态
            std::cout << "Process2:TASK-WAITING1 -> TASK-READY." << std::endl;
            std::cout << "Process2 Outputting well is not full. Process2 is ready." << std::endl;
        }
        // 释放请求输出块，修改请求输出块计数
        ptr1 = (ptr1 + 1) % NUM_REQUEST_BLOCKS; // 请求输出块指针按顺序循环
        c3++; // 请求输出块计数加1

        // 判断是否有等待请求输出块的进程
        if (pcb[0].status == 3) {
            pcb[0].status = 0; // 设置为可执行状态
            std::cout << "Process1:TASK-WAITING3 -> TASK-READY." << std::endl;
            std::cout << "Request block is available. Process1 is ready." << std::endl;
            return;
        }
        if (pcb[1].status == 3) {
            pcb[1].status = 0; // 设置为可执行状态
            std::cout << "Process2:TASK-WAITING3 -> TASK-READY." << std::endl;
            std::cout << "Request block is available. Process1 is ready." << std::endl;
            return;
        }
    }
}


