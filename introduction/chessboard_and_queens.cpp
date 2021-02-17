#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>


#define BOARD_SIZE 8
using namespace std;

using ulli = unsigned long long int;
using lli = long long int;

vector<string> board;

vector<string>* read_board() {
    vector<string>* board = new vector<string>(BOARD_SIZE, "");
    for(int i = 0; i < BOARD_SIZE; ++i)
        cin >> (*board)[i];
    return board;
}

vector<vector<bool>> *create_mark_matrix(const vector<string> &str_board) {
    vector<vector<bool>>* mark_matrix = new vector<vector<bool>>(BOARD_SIZE, vector<bool>());
    transform(
        str_board.cbegin(),
        str_board.cend(),
        mark_matrix->begin(),
        [&](string str_line) {
            vector<bool> mark_line;
            for (char c : str_line)
                mark_line.push_back(c != '.');
            return mark_line;
        }
    );
    return mark_matrix;
}


void _solve(vector<vector<bool>> &mark_matrix,
            vector<bool> &mark_col,
            vector<bool> &mark_diag_pp,
            vector<bool> &mark_diag_pm,
            int row,
            int &res) {

    if (row == BOARD_SIZE) {
        ++res;
        return;
    }

    for (int j = 0; j < BOARD_SIZE; ++j) {
        if (!mark_matrix[row][j] && !mark_diag_pp[BOARD_SIZE + row - j] && !mark_diag_pm[row + j] && !mark_col[j]) {
            mark_matrix[row][j] = mark_diag_pp[BOARD_SIZE + row - j] = mark_diag_pm[row + j] = mark_col[j] = true;
            _solve(mark_matrix, mark_col, mark_diag_pp, mark_diag_pm, row + 1, res);
            mark_matrix[row][j] = mark_diag_pp[BOARD_SIZE + row - j] = mark_diag_pm[row + j] = mark_col[j] = false;
        }
    }
}

int count_possible_configs(const vector<string> &board) {
    auto mark_matrix = create_mark_matrix(board);
    vector<bool> mark_col(BOARD_SIZE, false);
    vector<bool> mark_diag_pp(BOARD_SIZE * 2, false); // row++, col++
    vector<bool> mark_diag_pm(BOARD_SIZE * 2, false); // row++, col--
    int res = 0;
    _solve(*mark_matrix, mark_col, mark_diag_pp, mark_diag_pm, 0, res);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    auto board = read_board();
    cout << count_possible_configs(*board) << endl;
    return 0;
}
