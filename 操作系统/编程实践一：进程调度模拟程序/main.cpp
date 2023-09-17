/* 使用响应比高者优先算法： W = 1 + 等待时间/运行时间
 * 按照作业调度的先后次序输出结果，输出按照作业调度的先后次序输出结果，每行为一个作业状态，从左到右分别是调度次序，作业号，调度时间，周转时间和带权周转时间
 * 最后一行输出两个数，第一为平均周转时间，第二为平均带权周转时间
 */

/* 作业 进入时刻 运行时间 开始时刻 完成时刻 周转时间 带权周转
 * 0    800    200      800     1000    200     1.0
 * 1    850    50       1010    1060    210     4.2
 * 2    900    10       1000    1010    110     11.0
 * 3    950    20       1060    1080    130     6.5
 */

/* 输入：（输入格式是XXYY，其中XX是时，YY是分）
4
1320 200
1410 50
1500 10
1550 20
 */

/* 输入：（输入格式是以分钟计）
4
800 200
850 50
900 10
950 20
 */

/* 输出：
调度次序  作业号  调度时间(min)  周转时间(min)  带权周转时间(1+W/T)
1        0        800        200        1.000000
2        2        1000        110        11.000000
3        1        1010        210        4.200000
4        3        1060        130        6.500000
平均周转时间：162.5min
平均带权周转时间：5.675
 */

#include <iostream>
using namespace std;

const int INF = 0x3f3f3f3f;

class Homework
{
private:
    int schedulingOrder{};         // 调度次序（1--n）（若还没被调度则为0）
    int arrivalTime{};             // 进入时刻（10点28分->1028->628）
    int finishTime{};              // 完成时刻

    int waitTime{};                // 等待时间
    int runTime{};                 // 运行时间（以分钟计）
    int number{};                  // 作业号
    int dispatchTime{};            // 调度时间（第一次被CPU调度，即开始时刻）（MIN）
    int turnaroundTime{};          // 周转时间（完成时刻 - 进入时刻）
    double weightedTurnaroundTime{};  // 带权周转时间
public:
    int getWaitTime() const {
        return waitTime;
    }

    void setWaitTime(int waitTime) {
        Homework::waitTime = waitTime;
    }

public:
    int getSchedulingOrder() const {
        return schedulingOrder;
    }

    void setSchedulingOrder(int schedulingOrder) {
        Homework::schedulingOrder = schedulingOrder;
    }

    int getArrivalTime() const {
        return arrivalTime;
    }

    void setArrivalTime(int arrivalTime) {
        Homework::arrivalTime = arrivalTime;
    }

    int getFinishTime() const {
        return finishTime;
    }

    void setFinishTime(int finishTime) {
        Homework::finishTime = finishTime;
    }

    int getRunTime() const {
        return runTime;
    }

    void setRunTime(int runTime) {
        Homework::runTime = runTime;
    }

    int getNumber() const {
        return number;
    }

    void setNumber(int number) {
        Homework::number = number;
    }

    int getDispatchTime() const {
        return dispatchTime;
    }

    void setDispatchTime(int dispatchTime) {
        Homework::dispatchTime = dispatchTime;
    }

    int getTurnaroundTime() const {
        return turnaroundTime;
    }

    void setTurnaroundTime(int turnaroundTime) {
        Homework::turnaroundTime = turnaroundTime;
    }

    double getWeightedTurnaroundTime() const {
        return weightedTurnaroundTime;
    }

    void setWeightedTurnaroundTime(double weightedTurnaroundTime) {
        Homework::weightedTurnaroundTime = weightedTurnaroundTime;
    }

    string getInfo ()
    {
        int dispatchTime = { getDispatchTime() };
//        dispatchTime = (dispatchTime / 60 * 100) + (dispatchTime % 60);
        // 调度次序  作业号  调度时间  周转时间  带权周转时间
        return to_string(getSchedulingOrder()) + "        " + to_string(getNumber())
               + "        " + to_string(dispatchTime) + "        " + to_string(getTurnaroundTime())
               + "        " + to_string(getWeightedTurnaroundTime());
    }
};

/*
 * 功能：      计算作业的周转权重
 * 输入参数：  作业 作业数 当前时刻 调度次序
 * 返 回 值：  周转权重最大的作业号
 */
int calculateHomeworkWeight(Homework* homeworks, int n, int& presentMonment, int order)
{
    int maxWeightNumber{ 0 };
    int maxWeight{ -INF };
    int earliestHomeworkNumber{ 0 };  // 若当前时刻没有任务到达，记录最早到达的作业的下标
    int earlisetMonment{ INF };       // 若当前时刻没有任务到达，记录最早到达的作业的到达时刻
    for (int i = 0; i < n; ++i)
    {
        // 未被调度 && 已到达
        if(!homeworks[i].getSchedulingOrder() && presentMonment >= homeworks[i].getArrivalTime())
        {
            homeworks[i].setWaitTime(presentMonment - homeworks[i].getArrivalTime());                            // 等待时间 = 当前时刻 - 到达时刻
            homeworks[i].setWeightedTurnaroundTime(1 + 1.0 * homeworks[i].getWaitTime() / homeworks[i].getRunTime());  // W = 1 + 等待时间/运行时间

            if (homeworks[i].getWeightedTurnaroundTime() > maxWeight)  // 周转权重最大的作业号
            {
                maxWeightNumber = i;
                maxWeight = homeworks[i].getWeightedTurnaroundTime();
            }
        }

        // 未被调度 && 未到达 --> 找到其中最早到达的任务
        if (!homeworks[i].getSchedulingOrder() && presentMonment < homeworks[i].getArrivalTime())
        {
            if (earlisetMonment >= homeworks[i].getArrivalTime())
            {
                earlisetMonment = homeworks[i].getArrivalTime();
                earliestHomeworkNumber = i;
            }
        }
    }


    // 当前时刻没有任务到达
    if (maxWeight == -INF)
    {
        presentMonment = earlisetMonment;
        return calculateHomeworkWeight(homeworks, n, presentMonment, order);
    }

    // 更新被调度的作业的属性值
    homeworks[maxWeightNumber].setSchedulingOrder(order);        // 调度次序（1--n）（若还没被调度则为0）
    homeworks[maxWeightNumber].setFinishTime(presentMonment +
                                             homeworks[maxWeightNumber].getRunTime());                    // 完成时刻
    homeworks[maxWeightNumber].setDispatchTime(presentMonment);  // 调度时间（第一次被CPU调度，即开始时刻）
    homeworks[maxWeightNumber].setTurnaroundTime(homeworks[maxWeightNumber].getFinishTime() -
                                                 homeworks[maxWeightNumber].getArrivalTime());                // 周转时间（完成时刻 - 进入时刻）

    presentMonment = homeworks[maxWeightNumber].getFinishTime();

    return maxWeightNumber;
}

int main()
{
    cout << "输入作业数K：\n";
    int n{};   // 作业数（>0）
    cin >> n;
    Homework* homeworks = new Homework[n]{};

    cout << "输入 " << n << " 行提交时间和运行时间：\n";
    int presentMoment{ INF };
    int TJ{};  // 进入时刻 （输入格式是XXYY，其中XX是时，YY是分）
    int YS{};  // 运行时间（以分钟计）
    for (int i = 0; i < n; ++i)
    {
        cin >> TJ;
        homeworks[i].setArrivalTime((TJ / 100 * 60) + (TJ % 100));
        presentMoment = min(presentMoment, homeworks[i].getArrivalTime());  // 获取初始时刻，即最先到达的作业所处时刻

        cin >> YS;
        homeworks[i].setRunTime(YS);
        homeworks[i].setNumber(i);
    }

    cout << "调度次序  作业号  调度时间(min)  周转时间(min)  带权周转时间(1+W/T)\n";
    int number{};                            // 当前被CPU调度的作业号（0~n-1）
    double averageTurnaroundTime{};          // 平均周转时间
    double averageWeightedTurnaroundTime{};  // 平均带权周转时间
    int dispatchTime{};
    for (int i = 0; i < n; ++i)
    {
        number = calculateHomeworkWeight(homeworks, n, presentMoment, i + 1);
        cout << homeworks[number].getInfo() << '\n';
        averageTurnaroundTime += homeworks[number].getTurnaroundTime();
        averageWeightedTurnaroundTime += homeworks[number].getWeightedTurnaroundTime();
    }

    averageWeightedTurnaroundTime /= n;
    averageTurnaroundTime /= n;

    cout << "平均周转时间：" << averageTurnaroundTime << "min" << '\n';
    cout << "平均带权周转时间：" << averageWeightedTurnaroundTime << '\n';

    return 0;
}