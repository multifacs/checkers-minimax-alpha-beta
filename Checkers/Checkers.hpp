#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::map;
using std::string;
using std::vector;

typedef vector<vector<string>> Table;
typedef std::pair<int, int> pair;

string ansi_black = "\u001b[30m";
string ansi_red = "\u001b[31m";
string ansi_green = "\u001b[32m";
string ansi_yellow = "\u001b[33m";
string ansi_blue = "\u001b[34m";
string ansi_magenta = "\u001b[35m";
string ansi_cyan = "\u001b[36m";
string ansi_white = "\u001b[37m";
string ansi_reset = "\u001b[0m";

vector<string> split_string(const std::string& s, char delim) {
  vector<string> tokens;
  string token;
  for (char c : s) {
    if (c == delim) {
      tokens.push_back(token);
      token.clear();
    } else {
      token += c;
    }
  }
  if (!token.empty()) {
    tokens.push_back(token);
  }
  return tokens;
}

bool check_player_moves(Table board, int old_i, int old_j, int new_i,
                        int new_j) {
  if (new_i > 7 || new_i < 0) {
    return false;
  }
  if (new_j > 7 || new_j < 0) {
    return false;
  }
  if (board[old_i][old_j] == "---") {
    return false;
  }
  if (board[new_i][new_j] != "---") {
    return false;
  }
  if (board[old_i][old_j][0] == 'c' || board[old_i][old_j][0] == 'C') {
    return false;
  }
  if (board[new_i][new_j] == "---") {
    return true;
  }
}

bool check_player_jumps(Table board, int old_i, int old_j, int via_i, int via_j,
                        int new_i, int new_j) {
  if (new_i > 7 || new_i < 0) {
    return false;
  }
  if (new_j > 7 || new_j < 0) {
    return false;
  }
  if (board[via_i][via_j] == "---") {
    return false;
  }
  if (board[via_i][via_j][0] == 'B' || board[via_i][via_j][0] == 'b') {
    return false;
  }
  if (board[new_i][new_j] != "---") {
    return false;
  }
  if (board[old_i][old_j] == "---") {
    return false;
  }
  if (board[old_i][old_j][0] == 'c' || board[old_i][old_j][0] == 'C') {
    return false;
  }
  return true;
}

void make_a_move(Table* board, int old_i, int old_j, int new_i, int new_j,
                 char big_letter, int queen_row) {
  char letter = (*board)[old_i][old_j][0];
  int i_difference = old_i - new_i;
  int j_difference = old_j - new_j;

  if (i_difference == -2 && j_difference == 2) {
    (*board)[old_i + 1][old_j - 1] = "---";

  } else if (i_difference == 2 && j_difference == 2) {
    (*board)[old_i - 1][old_j - 1] = "---";

  } else if (i_difference == 2 && j_difference == -2) {
    (*board)[old_i - 1][old_j + 1] = "---";

  } else if (i_difference == -2 && j_difference == -2) {
    (*board)[old_i + 1][old_j + 1] = "---";
  }

  if (new_i == queen_row) {
    letter = big_letter;
  }

  (*board)[old_i][old_j] = "---";
  (*board)[new_i][new_j] =
      letter + std::to_string(new_i) + std::to_string(new_j);
}

vector<vector<int>> find_available_moves(Table board, bool mandatory_jumping) {
  vector<vector<int>> available_moves;
  vector<vector<int>> available_jumps;
  for (int m = 0; m < 8; m++) {
    for (int n = 0; n < 8; n++) {
      if (board[m][n][0] == 'b') {
        if (check_player_moves(board, m, n, m - 1, n - 1)) {
          available_moves.push_back({m, n, m - 1, n - 1});
        }
        if (check_player_moves(board, m, n, m - 1, n + 1)) {
          available_moves.push_back({m, n, m - 1, n + 1});
        }
        if (check_player_jumps(board, m, n, m - 1, n - 1, m - 2, n - 2)) {
          available_jumps.push_back({m, n, m - 2, n - 2});
        }
        if (check_player_jumps(board, m, n, m - 1, n + 1, m - 2, n + 2)) {
          available_jumps.push_back({m, n, m - 2, n + 2});
        }
      } else if (board[m][n][0] == 'B') {
        if (check_player_moves(board, m, n, m - 1, n - 1)) {
          available_moves.push_back({m, n, m - 1, n - 1});
        }
        if (check_player_moves(board, m, n, m - 1, n + 1)) {
          available_moves.push_back({m, n, m - 1, n + 1});
        }
        if (check_player_jumps(board, m, n, m - 1, n - 1, m - 2, n - 2)) {
          available_jumps.push_back({m, n, m - 2, n - 2});
        }
        if (check_player_jumps(board, m, n, m - 1, n + 1, m - 2, n + 2)) {
          available_jumps.push_back({m, n, m - 2, n + 2});
        }
        if (check_player_moves(board, m, n, m + 1, n - 1)) {
          available_moves.push_back({m, n, m + 1, n - 1});
        }
        if (check_player_jumps(board, m, n, m + 1, n - 1, m + 2, n - 2)) {
          available_jumps.push_back({m, n, m + 2, n - 2});
        }
        if (check_player_moves(board, m, n, m + 1, n + 1)) {
          available_moves.push_back({m, n, m + 1, n + 1});
        }
        if (check_player_jumps(board, m, n, m + 1, n + 1, m + 2, n + 2)) {
          available_jumps.push_back({m, n, m + 2, n + 2});
        }
      }
    }
  }
  if (!mandatory_jumping) {
    // reserve() is optional - just to improve performance
    available_jumps.reserve(
        available_jumps.size() +
        distance(available_moves.begin(), available_moves.end()));
    available_jumps.insert(available_jumps.end(), available_moves.begin(),
                           available_moves.end());
    return available_jumps;
  } else {
    if (available_jumps.size() == 0) {
      return available_moves;
    } else {
      return available_jumps;
    }
  }
}

bool check_jumps(Table board, int old_i, int old_j, int via_i, int via_j,
                 int new_i, int new_j) {
  if (new_i > 7 || new_i < 0) {
    return false;
  }
  if (new_j > 7 || new_j < 0) {
    return false;
  }
  if (board[via_i][via_j] == "---") {
    return false;
  }
  if (board[via_i][via_j][0] == 'C' || board[via_i][via_j][0] == 'c') {
    return false;
  }
  if (board[new_i][new_j] != "---") {
    return false;
  }
  if (board[old_i][old_j] == "---") {
    return false;
  }
  if (board[old_i][old_j][0] == 'b' || board[old_i][old_j][0] == 'B') {
    return false;
  }
  return true;
}

bool check_moves(Table board, int old_i, int old_j, int new_i, int new_j) {
  if (new_i > 7 || new_i < 0) {
    return false;
  }
  if (new_j > 7 || new_j < 0) {
    return false;
  }
  if (board[old_i][old_j] == "---") {
    return false;
  }
  if (board[new_i][new_j] != "---") {
    return false;
  }
  if (board[old_i][old_j][0] == 'b' || board[old_i][old_j][0] == 'B') {
    return false;
  }
  if (board[new_i][new_j] == "---") {
    return true;
  }
}

int calculate_heuristics(Table board) {
  int result = 0;
  int mine = 0;
  int opp = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j][0] == 'c' || board[i][j][0] == 'C') {
        mine += 1;

        if (board[i][j][0] == 'c') {
          result += 5;
        }
        if (board[i][j][0] == 'C') {
          result += 10;
        }
        if (i == 0 || j == 0 || i == 7 || j == 7) {
          result += 7;
        }
        if (i + 1 > 7 || j - 1 < 0 || i - 1 < 0 || j + 1 > 7) {
          continue;
        }
        if ((board[i + 1][j - 1][0] == 'b' || board[i + 1][j - 1][0] == 'B') &&
            board[i - 1][j + 1] == "---") {
          result -= 3;
        }
        if ((board[i + 1][j + 1][0] == 'b' || board[i + 1][j + 1][0] == 'B') &&
            board[i - 1][j - 1] == "---") {
          result -= 3;
        }
        if (board[i - 1][j - 1][0] == 'B' && board[i + 1][j + 1] == "---") {
          result -= 3;
        }
        if (board[i - 1][j + 1][0] == 'B' && board[i + 1][j - 1] == "---") {
          result -= 3;
        }
        if (i + 2 > 7 || i - 2 < 0) {
          continue;
        }
        if ((board[i + 1][j - 1][0] == 'B' || board[i + 1][j - 1][0] == 'b') &&
            board[i + 2][j + 2] == "---") {
          result += 6;
        }
        if (i + 2 > 7 || j + 2 > 7) {
          continue;
        }
        if ((board[i + 1][j + 1][0] == 'B' || board[i + 1][j + 1][0] == 'b') &&
            board[i + 2][j + 2] == "---") {
          result += 6;
        }
      } else if (board[i][j][0] == 'b' || board[i][j][0] == 'B') {
        opp += 1;
      }
    }
  }
  return result + (mine - opp) * 1000;
}

static vector<vector<int>> find_player_available_moves(Table board,
                                                       bool mandatory_jumping) {
  vector<vector<int>> available_moves;
  vector<vector<int>> available_jumps;
  for (int m = 0; m < 8; m++) {
    for (int n = 0; n < 8; n++) {
      if (board[m][n][0] == 'b') {
        if (check_player_moves(board, m, n, m - 1, n - 1)) {
          available_moves.push_back({m, n, m - 1, n - 1});
        }
        if (check_player_moves(board, m, n, m - 1, n + 1)) {
          available_moves.push_back({m, n, m - 1, n + 1});
        }
        if (check_player_jumps(board, m, n, m - 1, n - 1, m - 2, n - 2)) {
          available_jumps.push_back({m, n, m - 2, n - 2});
        }
        if (check_player_jumps(board, m, n, m - 1, n + 1, m - 2, n + 2)) {
          available_jumps.push_back({m, n, m - 2, n + 2});
        }
      } else if (board[m][n][0] == 'B') {
        if (check_player_moves(board, m, n, m - 1, n - 1)) {
          available_moves.push_back({m, n, m - 1, n - 1});
        }
        if (check_player_moves(board, m, n, m - 1, n + 1)) {
          available_moves.push_back({m, n, m - 1, n + 1});
        }
        if (check_player_jumps(board, m, n, m - 1, n - 1, m - 2, n - 2)) {
          available_jumps.push_back({m, n, m - 2, n - 2});
        }
        if (check_player_jumps(board, m, n, m - 1, n + 1, m - 2, n + 2)) {
          available_jumps.push_back({m, n, m - 2, n + 2});
        }
        if (check_player_moves(board, m, n, m + 1, n - 1)) {
          available_moves.push_back({m, n, m + 1, n - 1});
        }
        if (check_player_jumps(board, m, n, m + 1, n - 1, m + 2, n - 2)) {
          available_moves.push_back({m, n, m + 2, n - 2});
        }
        if (check_player_moves(board, m, n, m + 1, n + 1)) {
          available_moves.push_back({m, n, m + 1, n + 1});
        }
        if (check_player_jumps(board, m, n, m + 1, n + 1, m + 2, n + 2)) {
          available_moves.push_back({m, n, m + 2, n + 2});
        }
      }
    }
  }
  if (!mandatory_jumping) {
    // reserve() is optional - just to improve performance
    available_jumps.reserve(
        available_jumps.size() +
        distance(available_moves.begin(), available_moves.end()));
    available_jumps.insert(available_jumps.end(), available_moves.begin(),
                           available_moves.end());
    return available_jumps;
  } else {
    if (available_jumps.size() == 0) {
      return available_moves;
    } else {
      return available_jumps;
    }
  }
}

class Node {
 private:
  Table board;
  int value;
  vector<int> move;
  Node* parent;

 public:
  Node() {
    this->board = Table();
    this->move = vector<int>();
    this->parent = nullptr;
    this->value = 0;
  }
  Node(Table board, std::vector<int> move = {}, Node* parent = nullptr,
       int value = 0) {
    this->board = Table(board);
    this->move = move;
    this->parent = parent;
    this->value = value;
  }

  vector<Node> get_children(bool minimizing_player, bool mandatory_jumping) {
    vector<vector<int>> available_moves;
    vector<Node> children_states;
    Table current_state(board);
    string big_letter;
    int queen_row;
    if (minimizing_player == true) {
      available_moves = find_available_moves(current_state, mandatory_jumping);
      big_letter = "C";
      queen_row = 7;
    } else {
      available_moves =
          find_player_available_moves(current_state, mandatory_jumping);
      big_letter = "B";
      queen_row = 0;
    }
    for (int i = 0; i < available_moves.size(); i++) {
      int old_i = available_moves[i][0];
      int old_j = available_moves[i][1];
      int new_i = available_moves[i][2];
      int new_j = available_moves[i][3];
      Table state(current_state);
      make_a_move(&state, old_i, old_j, new_i, new_j, big_letter[0], queen_row);
      vector<int> new_move = {old_i, old_j, new_i, new_j};
      Node child(state, new_move, this);
      children_states.push_back(child);
    }
    return children_states;
  }

  void set_value(int value) { this->value = value; }

  int get_value() { return this->value; }

  vector<int> get_move() { return move; }

  Table get_board() { return this->board; }

  Node* get_parent() { return this->parent; }

  void set_parent(Node* parent) { this->parent = parent; }
};

int minimax(Table board, int depth, int alpha, int beta, bool maximizing_player,
            bool mandatory_jumping) {
  if (depth == 0) {
    return calculate_heuristics(board);
  }
  Node current_state(board);
  if (maximizing_player) {
    int max_eval = -INT_MAX;
    for (Node child : current_state.get_children(true, mandatory_jumping)) {
      int ev = minimax(child.get_board(), depth - 1, alpha, beta, false,
                       mandatory_jumping);
      max_eval = std::max(max_eval, ev);
      alpha = std::max(alpha, ev);
      if (beta <= alpha) {
        break;
      }
    }
    current_state.set_value(max_eval);
    return max_eval;
  } else {
    int min_eval = INT_MAX;
    for (Node child : current_state.get_children(false, mandatory_jumping)) {
      int ev = minimax(child.get_board(), depth - 1, alpha, beta, true,
                       mandatory_jumping);
      min_eval = std::min(min_eval, ev);
      beta = std::min(beta, ev);
      if (beta <= alpha) {
        break;
      }
    }
    current_state.set_value(min_eval);
    return min_eval;
  }
}

class Checkers {
 private:
  Table matrix = {{}, {}, {}, {}, {}, {}, {}, {}};
  bool player_turn = true;
  int computer_pieces = 12;
  int player_pieces = 12;
  vector<Table> available_moves;
  bool mandatory_jumping = false;

 public:
  Checkers() {
    for (vector<string>& row : matrix) {
      for (int i = 0; i < 8; i++) {
        row.push_back("---");
      }
    }
    position_computer();
    position_player();
  }

  void position_computer() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 8; j++) {
        if ((i + j) % 2 == 1) {
          matrix[i][j] = ("c" + std::to_string(i) + std::to_string(j));
        }
      }
    }
  }
  void position_player() {
    for (int i = 5; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if ((i + j) % 2 == 1) {
          matrix[i][j] = ("b" + std::to_string(i) + std::to_string(j));
        }
      }
    }
  }

  void print_matrix() {
    int i = 0;
    std::cout << std::endl;
    for (auto row : this->matrix) {
      std::cout << i << "  |";
      i += 1;
      for (auto elem : row) {
        if (elem[0] == 'c' || elem[0] == 'C') {
          std::cout << ansi_red << elem << ansi_reset << " ";
        } else if (elem[0] == 'b' || elem[0] == 'B') {
          std::cout << ansi_green << elem << ansi_reset << " ";
        } else {
          std::cout << elem << " ";
        }
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int j = 0; j < 8; j++) {
      string temp = std::to_string(j);
      if (j == 0) {
        temp = "     0";
      }
      std::cout << temp << "   ";
    }
    std::cout << std::endl;
  }

  void get_player_input() {
    vector<vector<int>> available_moves =
        find_player_available_moves(matrix, mandatory_jumping);
    if (available_moves.empty()) {
      if (computer_pieces > player_pieces) {
        cout << ansi_red
             << "You have no moves left, and you have fewer pieces than the "
                "computer. YOU LOSE!"
             << ansi_reset << endl;
        return;
      } else {
        cout << ansi_yellow << "You have no available moves.\nGAME ENDED!"
             << ansi_reset << endl;
        return;
      }
    }
    player_pieces = 0;
    computer_pieces = 0;
    while (true) {
      string coord1, coord2;
      int old_i, old_j, new_i, new_j;
      cout << "Which piece[i,j]: ";
      cin >> coord1;
      if (coord1 == "") {
        cout << ansi_cyan << "Game ended!" << ansi_reset << endl;
        exit(0);
      } else if (coord1 == "s") {
        cout << ansi_cyan << "You surrendered.\nCoward." << ansi_reset << endl;
        exit(0);
      }
      cout << "Where to[i,j]:";
      cin >> coord2;
      if (coord2 == "") {
        cout << ansi_cyan << "Game ended!" << ansi_reset << endl;
        exit(0);
      } else if (coord2 == "s") {
        cout << ansi_cyan << "You surrendered.\nCoward." << ansi_reset << endl;
        exit(0);
      }
      vector<string> old_coord = split_string(coord1, ',');
      vector<string> new_coord = split_string(coord2, ',');
      if (old_coord.size() != 2 || new_coord.size() != 2) {
        cout << ansi_red << "Illegal input" << ansi_reset << endl;
        continue;
      }
      try {
        old_i = stoi(old_coord[0]);
        old_j = stoi(old_coord[1]);
        new_i = stoi(new_coord[0]);
        new_j = stoi(new_coord[1]);
      } catch (const std::exception& e) {
        cout << ansi_red << "Illegal input" << ansi_reset << endl;
        continue;
      }

      vector<int> move = {old_i, old_j, new_i, new_j};
      if (find(available_moves.begin(), available_moves.end(), move) ==
          available_moves.end()) {
        cout << ansi_red << "Illegal move!" << ansi_reset << endl;
        continue;
      }
      make_a_move(&matrix, old_i, old_j, new_i, new_j, 'B', 0);
      for (int m = 0; m < 8; m++) {
        for (int n = 0; n < 8; n++) {
          if (matrix[m][n][0] == 'c' || matrix[m][n][0] == 'C') {
            computer_pieces++;
          } else if (matrix[m][n][0] == 'b' || matrix[m][n][0] == 'B') {
            player_pieces++;
          }
        }
      }
      break;
    }
  }

  void evaluate_states() {
    double t1 = time(NULL);
    Node current_state(matrix);

    vector<Node> first_computer_moves =
        current_state.get_children(true, mandatory_jumping);
    if (first_computer_moves.size() == 0) {
      if (player_pieces > computer_pieces) {
        cout << ansi_yellow +
                    "Computer has no available moves left, and you "
                    "have more pieces left.\nYOU WIN!" +
                    ansi_reset;
        return;
      } else {
        cout << ansi_yellow +
                    "Computer has no available moves left.\nGAME ENDED!" +
                    ansi_reset;
        return;
      }
    }
    std::map<double, Node> dict;
    for (int i = 0; i < first_computer_moves.size(); i++) {
      Node child = first_computer_moves[i];
      double value = minimax(child.get_board(), 4, -INFINITY, INFINITY, false,
                             mandatory_jumping);
      dict[value] = child;
    }
    if (dict.empty()) {
      cout << "\033[1;32mComputer has cornered itself.\nYOU WIN!\033[0m\n";
      return;
    }
    Table new_board = dict.rbegin()->second.get_board();
    vector<int> move = dict.rbegin()->second.get_move();
    matrix = new_board;
    double t2 = time(NULL);
    double diff = difftime(t2, t1);
    cout << "Computer has moved (" << move[0] << "," << move[1] << ") to ("
         << move[2] << "," << move[3] << ").\n";
    cout << "It took him " << diff << " seconds.\n";
  }

  void play() {
    cout << ansi_cyan << "##### WELCOME TO CHECKERS ####" << ansi_reset << endl;
    cout << "\nSome basic rules:" << endl;
    cout << "1.You enter the coordinates in the form i,j." << endl;
    cout << "2.You can quit the game at any time by pressing enter." << endl;
    cout << "3.You can surrender at any time by pressing 's'." << endl;
    cout << "Now that you've familiarized yourself with the rules, enjoy!"
         << endl;
    while (true) {
      string answer;
      cout << "\nFirst, we need to know, is jumping mandatory?[Y/n]: ";
      cin >> answer;
      if (answer == "Y" || answer == "y") {
        this->mandatory_jumping = true;
        break;
      } else if (answer == "N" || answer == "n") {
        this->mandatory_jumping = false;
        break;
      } else if (answer == "") {
        cout << ansi_cyan << "Game ended!" << ansi_reset << endl;
        exit(0);
      } else if (answer == "s") {
        cout << ansi_cyan
             << "You've surrendered before the game even started.\nPathetic."
             << ansi_reset << endl;
        exit(0);
      } else {
        cout << ansi_red << "Illegal input!" << ansi_reset << endl;
      }
    }
    while (true) {
      this->print_matrix();
      if (this->player_turn == true) {
        cout << ansi_cyan << "\nPlayer's turn." << ansi_reset << endl;
        this->get_player_input();
      } else {
        cout << ansi_cyan << "Computer's turn." << ansi_reset << endl;
        cout << "Thinking..." << endl;
        this->evaluate_states();
      }
      if (this->player_pieces == 0) {
        this->print_matrix();
        cout << ansi_red << "You have no pieces left.\nYOU LOSE!" << ansi_reset
             << endl;
        exit(0);
      } else if (this->computer_pieces == 0) {
        this->print_matrix();
        cout << ansi_green << "Computer has no pieces left.\nYOU WIN!"
             << ansi_reset << endl;
        exit(0);
      } else if (this->computer_pieces - this->player_pieces == 7) {
        string wish;
        cout << "You have 7 pieces fewer than your opponent.Do you want to "
                "surrender?";
        cin >> wish;
        if (wish == "" || wish == "yes") {
          cout << ansi_cyan << "Coward." << ansi_reset << endl;
          exit(0);
        }
      }
      this->player_turn = !this->player_turn;
    }
  }
};