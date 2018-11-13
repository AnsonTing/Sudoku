//  Filename: todo.h
//

#ifndef TODO_H
#define TODO_H

#include <iostream>
#include <algorithm>
using namespace std;

bool input_is_valid(const char grid[][9], int input, int row, int col);
void edit_cell(const char initial_grid[][9], char grid[][9]);
void remove_cell(const char initial_grid[][9], char grid[][9]);
bool check_end_game(const char grid[][9]);
bool sudoku_solver(char grid[][9]);
bool generate_board(char grid[][9]);
void generate_unique_puzzle(char grid[][9]);

#endif /* TODO_H */
