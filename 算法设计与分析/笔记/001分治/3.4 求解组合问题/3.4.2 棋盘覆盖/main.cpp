/* 问题描述：
 * 有一个 2^k * 2^k 的棋盘，恰好有一个方格与其他方格不同，称之为特殊方格。
 * 现在要用 L 形骨牌覆盖除了特殊方格以外的其他全部方格，骨牌可以任意旋转，并且任何两个骨牌不能重叠
 * 请给出一个覆盖方法。
 */
#include <iostream>
#include <vector>

using namespace std;

int label = 0;

void cover(vector<vector<int>>& board, int special, int tr, int tc, int dr, int dc, int size) {
    if (size == 1) {
        return;
    }
    label++;
    int s = size / 2;
    int offset = label * s * s;
    // 特殊方格在左上子棋盘内
    if (dr < tr + s && dc < tc + s) {
        cover(board, special, tr, tc, dr, dc, s);
    }
    else {
        board[tr + s - 1][tc + s - 1] = offset + s + 1;
        cover(board, special, tr, tc, tr + s - 1, tc + s - 1, s);
    }
    // 特殊方格在右上子棋盘内
    if (dr < tr + s && dc >= tc + s) {
        cover(board, special, tr, tc + s, dr, dc, s);
    }
    else {
        board[tr + s - 1][tc + s] = offset + 1;
        cover(board, special, tr, tc + s, tr + s - 1, tc + s, s);
    }
    // 特殊方格在左下子棋盘内
    if (dr >= tr + s && dc < tc + s) {
        cover(board, special, tr + s, tc, dr, dc, s);
    }
    else {
        board[tr + s][tc + s - 1] = offset + 3;
        cover(board, special, tr + s, tc, tr + s, tc + s - 1, s);
    }
    // 特殊方格在右下子棋盘内
    if (dr >= tr + s && dc >= tc + s) {
        cover(board, special, tr + s, tc + s, dr, dc, s);
    }
    else {
        board[tr + s][tc + s] = offset + 2;
        cover(board, special, tr + s, tc + s, tr + s, tc + s, s);
    }
}

int main() {
    int k = 3; // 棋盘大小为 2^k * 2^k
    int n = 1 << k;
    vector<vector<int>> board(n, vector<int>(n, 0));
    int special_row = 5; // 特殊方格所在行
    int special_col = 2; // 特殊方格所在列
    board[special_row][special_col] = -1;
    cover(board, -1, 0, 0, special_row, special_col, n);
    // 输出棋盘
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] < 0) {
                cout << "* ";
            }
            else {
                printf("%4d", board[i][j]);
            }
        }
        cout << endl;
    }
    return 0;
}
