分治法的关键步骤包括：
1. 分成子问题
2. 递归处理子问题
3. 子问题合并

描述算法时间增长率上限用 **O** 符号，增长率下限用 **Ω** 符号表示。

图灵机模型的基本结构包括 纸带,**读写头**,**有限状态自动机**。

NP问题是指可以在多项式的时间里验证一个解的问题

若一个问题可以找到一个能在多项式的时间里解决它的算法，该问题就属于P问题

NPC 问题不一定是个NP问题，只要保证所有的NP问题都可以约化到它即可。  
NPC问题指的是NP问题中最难的问题之一，同时也是NP问题中的一个子集，因此只要能将所有的NP问题约化为它，它就是NP问题。

所有的P类问题都是NP问题的子集。

所有可计算问题都可以用递归模型和 **图灵机** 模型求解

分治法是一种求解问题的策略，而递归是一种实现求解算法的技术

改进分治算法的途径有 **减少子问题个数** 和 **增加预处理**。

在分治法处理中，实践证明，采用 **平衡子问题** 思想划分子问题总是有较好的结果。

在大整数乘法和矩阵乘中，可以采取降低  **乘法** 的运算次数来降低时间复杂度

虽然动态规划算法通常用于解决具有重叠子问题的问题，但是这并不是动态规划的必要条件。

一个基于BSP模型的并行算法，假设有p台处理器，用于计算整数数组a[0..n-1]的所有元素之和，算法的时间复杂度为 **O(n/p+p)**

分治法的设计思想是将一个难以直接解决的大问题分割成规模较小的子问题，分别解决子问题，最后将子问题的解组合起来形成原问题的解。这要求原问题和子问题 **问题规模不同，问题性质相同**

