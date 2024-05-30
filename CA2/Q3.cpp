#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define FIRST_ROW 0
#define FIRST_COL 0
#define ROCK '#'
#define BAMBOU '*'
const int POSSIBLE_MOVES = 4;
int row_delta[POSSIBLE_MOVES] = { 1 , 0 , -1 , 0 };
int col_delta[POSSIBLE_MOVES] = { 0 ,-1 , 0  , 1 };
vector<vector<char>> get_board(){
    vector<vector<char>> board;
    for (int i = 0; !cin.eof(); i++) {
        string str;
        cin >> str;
        vector<char> row;
        for (int j = 0; j<str.size(); j++) {
            row.push_back(str[j]);
        }
        board.push_back(row);
    }
    return board;
}
vector<vector<vector<int>>> creat_cell_direction(int row,int col) {
    vector<vector<int>> board_copy(col, vector<int>(POSSIBLE_MOVES, 0));
    vector<vector<vector<int>>> cell_direction(row, board_copy);
    return cell_direction;
}
bool cell_direction_check(vector<vector<vector<int>>> requested, int row, int col,int move_num) {
    if (requested[row][col][move_num] == 1)
        return true;
    else
        return false;
}
bool is_possible(vector<vector<char>>board,int current_row,int current_col,int row_count,int col_count){
    if (current_row < 0 || current_row >= row_count || current_col < 0 || current_col >= col_count || board[current_row][current_col] == ROCK)
        return false;
    else
        return true;
}
void update_position(int &tour_len,int move,int current_row,int current_col,vector<vector<vector<int>>> &cell_direction) {
    tour_len++;
    cell_direction[current_row][current_col][move] = 1;
}
bool move_straight(int move,vector<vector<char>> board, int &current_row, int &current_col, int row_count, int col_count, int& tour_len,
        vector<int>& tour_lens, vector<vector<vector<int>>> &cell_direction) {   
    while (1) {
        if (board[current_row][current_col] == BAMBOU)
            return true;
        int new_row = current_row + row_delta[move];
        int new_col = current_col + col_delta[move];
        if (!is_possible(board,new_row,new_col,row_count,col_count)) 
            return true;
        if (cell_direction_check(cell_direction, new_row, new_col, move)) 
            return false;
        update_position(tour_len, move, new_row, new_col, cell_direction);
        current_row = new_row; 
        current_col = new_col;
    }
}
void find_routes(int move_num,int current_row, int current_col, int row_count, int col_count, vector<vector<char>> board,
        const int tour_len,vector<int>&tour_lens,vector<vector<vector<int>>> cell_direction) {
    if (board[current_row][current_col] == BAMBOU) {
        tour_lens.push_back(tour_len);
        return;
    }
    for (int move = 0; move < POSSIBLE_MOVES; move++) {
        int tour_len_copy = tour_len;
        if (move == move_num + 2 || move == move_num - 2)
            continue;
        int new_row = current_row + row_delta[move];
        int new_col = current_col + col_delta[move];
        if (!is_possible(board, new_row, new_col, row_count, col_count))
            continue;
        if (cell_direction_check(cell_direction, new_row, new_col, move)) 
            continue;
        update_position(tour_len_copy, move, new_row, new_col, cell_direction);
        if (!move_straight(move, board, new_row, new_col, row_count, col_count, tour_len_copy, tour_lens, cell_direction)) {
            continue;
        }
        find_routes(move, new_row, new_col, row_count, col_count, board, tour_len_copy, tour_lens, cell_direction);
    }
}
int find_min(vector<int> tour_lens){
    sort(tour_lens.begin(), tour_lens.end());
    return tour_lens[0];
}

void show_result(vector<int> tour_lens) {
    if (tour_lens.size()) 
        cout << find_min(tour_lens) << endl;
    else cout << "No path found" << endl;
}

int main()
{
    vector<vector<char>> board = get_board();
    const int row = board.size()-1;
    const int col = board[0].size();
    vector<vector<vector<int>>> cell_direction = creat_cell_direction(row, col);
    vector<int> tour_lens;
    int first_tour_len = 0;
    find_routes(-3, FIRST_ROW, FIRST_COL, row, col, board, first_tour_len, tour_lens, cell_direction);
    show_result(tour_lens);
}
