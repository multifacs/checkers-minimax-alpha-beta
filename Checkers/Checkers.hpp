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
  if (board.at(old_i).at(old_j) == "---") {
    return false;
  }
  if (board.at(new_i).at(new_j) != "---") {
    return false;
  }
  if (board.at(old_i).at(old_j).at(0) == 'c' ||
      board.at(old_i).at(old_j).at(0) == 'C') {
    return false;
  }
  if (board.at(new_i).at(new_j) == "---") {
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
  if (board.at(via_i).at(via_j) == "---") {
    return false;
  }
  if (board.at(via_i).at(via_j).at(0) == 'B' ||
      board.at(via_i).at(via_j).at(0) == 'b') {
    return false;
  }
  if (board.at(new_i).at(new_j) != "---") {
    return false;
  }
  if (board.at(old_i).at(old_j) == "---") {
    return false;
  }
  if (board.at(old_i).at(old_j).at(0) == 'c' ||
      board.at(old_i).at(old_j).at(0) == 'C') {
    return false;
  }
  return true;
}

void make_a_move(Table* board, int old_i, int old_j, int new_i, int new_j,
                 char big_letter, int queen_row) {
  char letter = (*board).at(old_i).at(old_j).at(0);
  int i_difference = old_i - new_i;
  int j_difference = old_j - new_j;

  if (i_difference == -2 && j_difference == 2) {
    (*board).at(old_i + 1).at(old_j - 1) = "---";

  } else if (i_difference == 2 && j_difference == 2) {
    (*board).at(old_i - 1).at(old_j - 1) = "---";

  } else if (i_difference == 2 && j_difference == -2) {
    (*board).at(old_i - 1).at(old_j + 1) = "---";

  } else if (i_difference == -2 && j_difference == -2) {
    (*board).at(old_i + 1).at(old_j + 1) = "---";
  }

  if (new_i == queen_row) {
    letter = big_letter;
  }

  (*board).at(old_i).at(old_j) = "---";
  (*board).at(new_i).at(new_j) =
      letter + std::to_string(new_i) + std::to_string(new_j);
}

bool check_jumps(Table board, int old_i, int old_j, int via_i, int via_j,
                 int new_i, int new_j) {
  if (new_i > 7 || new_i < 0) {
    return false;
  }
  if (new_j > 7 || new_j < 0) {
    return false;
  }
  if (board.at(via_i).at(via_j) == "---") {
    return false;
  }
  if (board.at(via_i).at(via_j).at(0) == 'C' ||
      board.at(via_i).at(via_j).at(0) == 'c') {
    return false;
  }
  if (board.at(new_i).at(new_j) != "---") {
    return false;
  }
  if (board.at(old_i).at(old_j) == "---") {
    return false;
  }
  if (board.at(old_i).at(old_j).at(0) == 'b' ||
      board.at(old_i).at(old_j).at(0) == 'B') {
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
  if (board.at(old_i).at(old_j) == "---") {
    return false;
  }
  if (board.at(new_i).at(new_j) != "---") {
    return false;
  }
  if (board.at(old_i).at(old_j).at(0) == 'b' ||
      board.at(old_i).at(old_j).at(0) == 'B') {
    return false;
  }
  if (board.at(new_i).at(new_j) == "---") {
    return true;
  }
}

vector<vector<int>> find_available_moves(Table board, bool mandatory_jumping) {
  vector<vector<int>> available_moves;
  vector<vector<int>> available_jumps;
  for (int m = 0; m < 8; m++) {
    for (int n = 0; n < 8; n++) {
      if (board.at(m).at(n).at(0) == 'c') {
        if (check_moves(board, m, n, m + 1, n + 1)) {
          available_moves.push_back({m, n, m + 1, n + 1});
        }
        if (check_moves(board, m, n, m + 1, n - 1)) {
          available_moves.push_back({m, n, m + 1, n - 1});
        }
        if (check_jumps(board, m, n, m + 1, n - 1, m + 2, n - 2)) {
          available_jumps.push_back({m, n, m + 2, n - 2});
        }
        if (check_jumps(board, m, n, m + 1, n + 1, m + 2, n + 2)) {
          available_jumps.push_back({m, n, m + 2, n + 2});
        }
      } else if (board.at(m).at(n).at(0) == 'C') {
        if (check_moves(board, m, n, m + 1, n + 1)) {
          available_moves.push_back({m, n, m + 1, n + 1});
        }
        if (check_moves(board, m, n, m + 1, n - 1)) {
          available_moves.push_back({m, n, m + 1, n - 1});
        }
        if (check_moves(board, m, n, m - 1, n - 1)) {
          available_moves.push_back({m, n, m - 1, n - 1});
        }
        if (check_moves(board, m, n, m - 1, n + 1)) {
          available_moves.push_back({m, n, m - 1, n + 1});
        }
        if (check_jumps(board, m, n, m + 1, n - 1, m + 2, n - 2)) {
          available_jumps.push_back({m, n, m + 2, n - 2});
        }
        if (check_jumps(board, m, n, m - 1, n - 1, m - 2, n - 2)) {
          available_jumps.push_back({m, n, m - 2, n - 2});
        }
        if (check_jumps(board, m, n, m - 1, n + 1, m - 2, n + 2)) {
          available_jumps.push_back({m, n, m - 2, n + 2});
        }
        if (check_jumps(board, m, n, m + 1, n + 1, m + 2, n + 2)) {
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

int calculate_heuristics(Table board) {
  int result = 0;
  int mine = 0;
  int opp = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board.at(i).at(j).at(0) == 'c' || board.at(i).at(j).at(0) == 'C') {
        mine += 1;

        if (board.at(i).at(j).at(0) == 'c') {
          result += 5;
        }
        if (board.at(i).at(j).at(0) == 'C') {
          result += 10;
        }
        if (i == 0 || j == 0 || i == 7 || j == 7) {
          result += 7;
        }
        if (i + 1 > 7 || j - 1 < 0 || i - 1 < 0 || j + 1 > 7) {
          continue;
        }
        if ((board.at(i + 1).at(j - 1).at(0) == 'b' ||
             board.at(i + 1).at(j - 1).at(0) == 'B') &&
            board.at(i - 1).at(j + 1) == "---") {
          result -= 3;
        }
        if ((board.at(i + 1).at(j + 1).at(0) == 'b' ||
             board.at(i + 1).at(j + 1).at(0) == 'B') &&
            board.at(i - 1).at(j - 1) == "---") {
          result -= 3;
        }
        if (board.at(i - 1).at(j - 1).at(0) == 'B' &&
            board.at(i + 1).at(j + 1) == "---") {
          result -= 3;
        }

        if (board.at(i - 1).at(j + 1).at(0) == 'B' &&
            board.at(i + 1).at(j - 1) == "---") {
          result -= 3;
        }
        if (i + 2 > 7 || j - 2 < 0) {
          continue;
        }
        if ((board.at(i + 1).at(j - 1).at(0) == 'B' ||
             board.at(i + 1).at(j - 1).at(0) == 'b') &&
            board.at(i + 2).at(j - 2) == "---") {
          result += 6;
        }
        if (i + 2 > 7 || j + 2 > 7) {
          continue;
        }
        if ((board.at(i + 1).at(j + 1).at(0) == 'B' ||
             board.at(i + 1).at(j + 1).at(0) == 'b') &&
            board.at(i + 2).at(j + 2) == "---") {
          result += 6;
        }
      } else if (board.at(i).at(j).at(0) == 'b' ||
                 board.at(i).at(j).at(0) == 'B') {
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
      if (board.at(m).at(n).at(0) == 'b') {
        if (check_player_moves(board, m, n, m - 1, n - 1))
          available_moves.push_back({m, n, m - 1, n - 1});
        if (check_player_moves(board, m, n, m - 1, n + 1))
          available_moves.push_back({m, n, m - 1, n + 1});
        if (check_player_jumps(board, m, n, m - 1, n - 1, m - 2, n - 2))
          available_jumps.push_back({m, n, m - 2, n - 2});
        if (check_player_jumps(board, m, n, m - 1, n + 1, m - 2, n + 2))
          available_jumps.push_back({m, n, m - 2, n + 2});
      } else if (board.at(m).at(n).at(0) == 'B') {
        if (check_player_moves(board, m, n, m - 1, n - 1))
          available_moves.push_back({m, n, m - 1, n - 1});
        if (check_player_moves(board, m, n, m - 1, n + 1))
          available_moves.push_back({m, n, m - 1, n + 1});
        if (check_player_jumps(board, m, n, m - 1, n - 1, m - 2, n - 2))
          available_jumps.push_back({m, n, m - 2, n - 2});
        if (check_player_jumps(board, m, n, m - 1, n + 1, m - 2, n + 2))
          available_jumps.push_back({m, n, m - 2, n + 2});
        if (check_player_moves(board, m, n, m + 1, n - 1))
          available_moves.push_back({m, n, m + 1, n - 1});
        if (check_player_jumps(board, m, n, m + 1, n - 1, m + 2, n - 2))
          available_jumps.push_back({m, n, m + 2, n - 2});
        if (check_player_moves(board, m, n, m + 1, n + 1))
          available_moves.push_back({m, n, m + 1, n + 1});
        if (check_player_jumps(board, m, n, m + 1, n + 1, m + 2, n + 2))
          available_jumps.push_back({m, n, m + 2, n + 2});
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
      big_letter = 'C';
      queen_row = 7;
    } else {
      available_moves =
          find_player_available_moves(current_state, mandatory_jumping);
      big_letter = 'B';
      queen_row = 0;
    }
    for (int i = 0; i < available_moves.size(); i++) {
      int old_i = available_moves.at(i).at(0);
      int old_j = available_moves.at(i).at(1);
      int new_i = available_moves.at(i).at(2);
      int new_j = available_moves.at(i).at(3);
      Table state(current_state);
      make_a_move(&state, old_i, old_j, new_i, new_j, big_letter.at(0),
                  queen_row);
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
          matrix.at(i).at(j) = ('c' + std::to_string(i) + std::to_string(j));
        }
      }
    }
  }
  void position_player() {
    for (int i = 5; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if ((i + j) % 2 == 1) {
          matrix.at(i).at(j) = ('b' + std::to_string(i) + std::to_string(j));
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
        if (elem.at(0) == 'c' || elem.at(0) == 'C') {
          std::cout << ansi_red << elem << ansi_reset << " ";
        } else if (elem.at(0) == 'b' || elem.at(0) == 'B') {
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
        return;
      } else if (coord1 == "s") {
        cout << ansi_cyan << "You surrendered.\nCoward." << ansi_reset << endl;
        return;
      }
      cout << "Where to[i,j]:";
      cin >> coord2;
      if (coord2 == "") {
        cout << ansi_cyan << "Game ended!" << ansi_reset << endl;
        return;
      } else if (coord2 == "s") {
        cout << ansi_cyan << "You surrendered.\nCoward." << ansi_reset << endl;
        return;
      }
      vector<string> old_coord = split_string(coord1, ',');
      vector<string> new_coord = split_string(coord2, ',');
      if (old_coord.size() != 2 || new_coord.size() != 2) {
        cout << ansi_red << "Illegal input" << ansi_reset << endl;
        continue;
      }
      try {
        old_i = stoi(old_coord.at(0));
        old_j = stoi(old_coord.at(1));
        new_i = stoi(new_coord.at(0));
        new_j = stoi(new_coord.at(1));
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
          if (matrix.at(m).at(n).at(0) == 'c' ||
              matrix.at(m).at(n).at(0) == 'C') {
            computer_pieces++;
          } else if (matrix.at(m).at(n).at(0) == 'b' ||
                     matrix.at(m).at(n).at(0) == 'B') {
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
      Node child = first_computer_moves.at(i);
      double value = minimax(child.get_board(), 4, -INT_MAX, INT_MAX, false,
                             mandatory_jumping);
      dict.insert(std::pair<double, Node>(value, child));
    }
    if (dict.empty()) {
      cout << ansi_green + "Computer has cornered itself.\nYOU WIN!" +
                  ansi_reset;
      return;
    }
    Table new_board = dict.rbegin()->second.get_board();
    vector<int> move = dict.rbegin()->second.get_move();
    matrix = new_board;
    double t2 = time(NULL);
    double diff = difftime(t2, t1);
    cout << "Computer has moved (" << move.at(0) << "," << move.at(1)
         << ") to (" << move.at(2) << "," << move.at(3) << ").\n";
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
        mandatory_jumping = true;
        break;
      } else if (answer == "N" || answer == "n") {
        mandatory_jumping = false;
        break;
      } else if (answer == "") {
        cout << ansi_cyan << "Game ended!" << ansi_reset << endl;
        return;
      } else if (answer == "s") {
        cout << ansi_cyan
             << "You've surrendered before the game even started.\nPathetic."
             << ansi_reset << endl;
        return;
      } else {
        cout << ansi_red << "Illegal input!" << ansi_reset << endl;
      }
    }
    while (true) {
      print_matrix();
      if (player_turn == true) {
        cout << ansi_cyan << "\nPlayer's turn." << ansi_reset << endl;
        get_player_input();
      } else {
        cout << ansi_cyan << "Computer's turn." << ansi_reset << endl;
        cout << "Thinking..." << endl;
        evaluate_states();
      }
      if (player_pieces == 0) {
        print_matrix();
        cout << ansi_red << "You have no pieces left.\nYOU LOSE!" << ansi_reset
             << endl;
        return;
      } else if (computer_pieces == 0) {
        print_matrix();
        cout << ansi_green << "Computer has no pieces left.\nYOU WIN!"
             << ansi_reset << endl;
        return;
      } else if (computer_pieces - player_pieces == 7) {
        string wish;
        cout << "You have 7 pieces fewer than your opponent.Do you want to "
                "surrender?";
        cin >> wish;
        if (wish == "" || wish == "yes") {
          cout << ansi_cyan << "Coward." << ansi_reset << endl;
          return;
        }
      }
      player_turn = !player_turn;
    }
  }
};