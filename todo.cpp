
#include <iostream>
#include <string>
#include <algorithm>
#include "helper.h"
#include "todo.h"
using namespace std;

bool get_cell_input(int& row, int& col, string& input) {
  cout << "Enter the coordinates of the cell:";
  cin >> input;
  if (input.length() != 2)
    {cout << "ERROR: Cell \'" << input << "\' is invalid." << endl; return false;}

  switch (toupper(input[0])) {
    case 'A':
      col = 0; break;
    case 'B':
      col = 1; break;
    case 'C':
      col = 2; break;
    case 'D':
      col = 3; break;
    case 'E':
      col = 4; break;
    case 'F':
      col = 5; break;
    case 'G':
      col = 6; break;
    case 'H':
      col = 7; break;
    case 'I':
      col = 8; break;
    default:
      {cout << "ERROR: Cell \'" << input << "\' is invalid." << endl; return false;}
  }

  row = input[1] - '0' - 1;
  if ((row < 0) || (row > 8))
    {cout << "ERROR: Cell \'" << input << "\' is invalid." << endl; return false;}
  return true;
}

bool number_of_solutions(char grid[][9], int& cnt)
{
  const string s = "123456789";
  if (check_end_game(grid)) {
    cnt++;
    return true;
  }
  bool result = false;
  bool found = false;
  bool double_break = false;
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (grid[row][col] == ' ') {
        found = true;
        for (int i = 0; i < 9; i++) {
          if (input_is_valid(grid, i+1, row, col)) {
            grid[row][col] = s[i];
            result = number_of_solutions(grid, cnt);

            grid[row][col] = ' ';}

        }
      }
      if (found) {double_break = true; break;}
    }
    if (double_break) break;
  }
  return result;
}

/***********************************************************************
 * TODO_1: Check whether the inserted value is compliant
 *         with the rules of Sudoku.
 ***********************************************************************/

bool input_is_valid(const char grid[][9], int value, int row, int col) {
	/// ADD YOUR CODE HERE
  if ((value < 1) || (value) > 9) return false;
  char c_value = '0' + value;
  for (int i = 0; i < 9; i++) {
    if (grid[row][i] == c_value) return false;
    if (grid[i][col] == c_value) return false;
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (grid[row - (row % 3) + i][col - (col % 3) + j] == c_value) return false;
    }
  }
  return true;
}

/***********************************************************************
 * TODO_2: Ask coordinate inputs from the user, and a value to insert.
 *         Check whether the user's input is valid. If the user's input
 *         is valid, insert the value and update the current grid.
 *         Otherwise, print an error message.
 ***********************************************************************/

void edit_cell(const char initial_grid[][9], char grid[][9]) {
	/// ADD YOUR CODE HERE
  string input;
  int row, col, value;
  if (!(get_cell_input(row, col, input))) return;
  if (grid[row][col] != ' ')
    {cout << "ERROR: Cell \'" << input << "\' is read-only." << endl; return;}

  cout << "Enter the value at \'" << input << "\':";
  cin >> value;
  char c_value = '0' + value;
  if (input_is_valid(grid, value, row, col))
    grid[row][col] = c_value;
  else
    cout << "ERROR: Value \'" << value << "\' in cell \'" << input << "\' is invalid." << endl;

}

/***********************************************************************
 * TODO_3: Ask coordinate inputs from the user. Remove the value from
 *         the current grid if the cell has not been filled in the
 *         beginning.
 ***********************************************************************/

void remove_cell(const char initial_grid[][9], char grid[][9]) {
	/// ADD YOUR CODE HERE
  string input;
  int row, col;
  if (!(get_cell_input(row, col, input))) return;
  if (initial_grid[row][col] != ' ')
    {cout << "ERROR: Cell \'" << input << "\' is read-only." << endl; return;}
  grid[row][col] = ' ';
}

/***********************************************************************
 * TODO_4: Check whether all the cells in the grid have been
 *         correctly filled.
 ***********************************************************************/

bool check_end_game(const char grid[][9]) {
	/// ADD YOUR CODE HERE
  string check_string;
  for (int row = 0; row < 9; row++) {
    check_string = "";
    for (int col = 0; col < 9; col++) {
      check_string += grid[row][col];
    }
    sort(check_string.begin(), check_string.end());
    if (check_string != "123456789")
      return false;
  }
  for (int col = 0; col < 9; col++) {
    check_string = "";
    for (int row = 0; row < 9; row++) {
      check_string += grid[row][col];
    }
    sort(check_string.begin(), check_string.end());
    if (check_string != "123456789")
      return false;
  }
  for (int row = 0; row < 9; row += 3) {
    for (int col = 0; col < 9; col += 3) {
      check_string = "";
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          check_string += grid[row+i][col+j];
        }
      }
      sort(check_string.begin(), check_string.end());
      if (check_string != "123456789")
        return false;
    }
  }
  return true;
}

/***********************************************************************
 * TODO_5: Automatic Sudoku solver.
 *         Complete all the empty cells with the
 *         correct solution if it exists.
 ***********************************************************************/

bool sudoku_solver(char grid[][9]) {
	/// ADD YOUR CODE HERE
  const string s = "123456789";
  if (check_end_game(grid)) {
    return true;
  }
  bool result = false;
  bool found = false;
  bool double_break = false;
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (grid[row][col] == ' ') {
        found = true;
        for (int i = 0; i < 9; i++) {
          if (input_is_valid(grid, i+1, row, col)) {
            grid[row][col] = s[i];
            result = sudoku_solver(grid);
            if (!(result)) {
              grid[row][col] = ' ';}
          }
        }
      }
      if (found) {double_break = true; break;}
    }
    if (double_break) break;
  }
  return result;
}




/***********************************************************************
 * TODO_6: Generate a complete valid board.
 ***********************************************************************/

bool generate_board(char grid[][9]) {
	/// ADD YOUR CODE HERE
  srand(time(0));
  const string s = "123456789";
  int value, count;
  char c_value;

  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      grid[row][col] = ' ';
    }
  }
    // Fill the grid randomly
  bool result;
  char grid_copy[9][9];
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      result = false;
      do {
        value = rand() % 9 + 1;
        if (input_is_valid(grid, value, row, col)) {
          grid[row][col] = '0' + value;
          for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
              grid_copy[i][j] = grid[i][j];
            }
          }
          result = sudoku_solver(grid_copy);
          if (!(result)) {
            grid[row][col] = ' ';}
        }
      } while (!(result));
    }
  }
  return true;

}

/***********************************************************************
 * TODO_7: Generate a Sudoku puzzle with unique solution.
 ***********************************************************************/

void generate_unique_puzzle(char grid[][9]) {
	/// ADD YOUR CODE HERE
  srand(time(0));
  // const string s = "123456789";
  // int value, count;
  // char c_value;
  //
  // for (int row = 0; row < 9; row++) {
  //   for (int col = 0; col < 9; col++) {
  //     grid[row][col] = ' ';
  //   }
  // }
  //   // Fill the grid randomly
  // bool result;
  // char grid_copy[9][9];
  // for (int row = 0; row < 9; row++) {
  //   for (int col = 0; col < 9; col++) {
  //     result = true;
  //     do {
  //       value = rand() % 9 + 1;
  //       if (input_is_valid(grid, value, row, col)) {
  //         grid[row][col] = '0' + value;
  //         for (int i = 0; i < 9; i++) {
  //           for (int j = 0; j < 9; j++) {
  //             grid_copy[i][j] = grid[i][j];
  //           }
  //         }
  //         result = sudoku_solver(grid_copy);
  //         if (!(result)) {
  //           grid[row][col] = ' ';}
  //       }
  //     } while (!(result));
  //   }
  // }
  generate_board(grid);
  int row, col, cnt;
  char char_store;
  char grid_copy[9][9];
  while (true) {
    cnt = 0;
    row = rand() % 9;
    col = rand() % 9;
    while (grid[row][col] == ' ') {
      row = rand() % 9;
      col = rand() % 9;
    }
    char_store = grid[row][col];
    grid[row][col] = ' ';
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        grid_copy[i][j] = grid[i][j];
      }
    }
    number_of_solutions(grid_copy, cnt);
    if (cnt > 1) {
      grid[row][col] = char_store;
      break;
    }
  }
}
