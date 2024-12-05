#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream file("input.txt");
  if (!file) {
    cerr << "Error opening file" << endl;
    return 1;
  }
  enum class State {
    base,
    found_m,
    found_mu,
    found_mul,
    found_mul_op,  // found mul(
    found_num1,
    found_comma,
    found_num2,
    found_d,
    found_do,
    found_do_op,  // found do(
    found_don,
    found_don_tick,       // found don'
    found_don_tick_t,     // found don't
    found_don_tick_t_op,  // found don't(
    found_dont            // found don't()
  };
  State state = State::base;
  string num1_buffer = "";
  string num2_buffer = "";
  int num1, num2;
  int total = 0;
  char next_c;
  while (file >> next_c) {
    switch (state) {
      case State::base:
        if (next_c == 'm') {
          state = State::found_m;
        } else if (next_c == 'd') {
          state = State::found_d;
        }
        break;
      case State::found_m:
        if (next_c == 'u') {
          state = State::found_mu;
        } else if (next_c == 'd') {
          state = State::found_d;
        } else {
          state = State::base;
        }
        break;
      case State::found_mu:
        if (next_c == 'l') {
          state = State::found_mul;
        } else if (next_c == 'd') {
          state = State::found_d;
        } else {
          state = State::base;
        }
        break;
      case State::found_mul:
        if (next_c == '(') {
          state = State::found_mul_op;
        } else if (next_c == 'd') {
          state = State::found_d;
        } else {
          state = State::base;
        }
        break;
      case State::found_mul_op:
        // if next_c is a digit, add it to num1_buffer
        if (isdigit(next_c)) {
          num1_buffer += next_c;
          state = State::found_num1;
        } else if (next_c == 'd') {
          state = State::found_d;
        }
        break;
      case State::found_num1:
        // if next_c is a digit, add it to num1_buffer
        if (isdigit(next_c)) {
          num1_buffer += next_c;
        } else if (next_c == ',') {
          state = State::found_comma;
          num1 = stoi(num1_buffer);
          num1_buffer = "";
        } else if (next_c == 'd') {
          state = State::found_d;
          num1_buffer = "";
        } else {
          state = State::base;
          num1_buffer = "";
        }
        break;
      case State::found_comma:
        // if next_c is a digit, add it to num2_buffer
        if (isdigit(next_c)) {
          num2_buffer += next_c;
          state = State::found_num2;
        } else if (next_c == 'd') {
          state = State::found_d;
        } else {
          state = State::base;
          num2_buffer = "";
        }
        break;
      case State::found_num2:
        // if next_c is a digit, add it to num2_buffer
        if (isdigit(next_c)) {
          num2_buffer += next_c;
        } else if (next_c == ')') {
          state = State::base;
          num2 = stoi(num2_buffer);
          total += num1 * num2;
          num2_buffer = "";
        } else if (next_c == 'd') {
          state = State::found_d;
          num2_buffer = "";
        } else {
          state = State::base;
          num2_buffer = "";
        }
        break;
      case State::found_d:
        if (next_c == 'o') {
          state = State::found_do;
        } else {
          if (state != State::found_dont) {
            state = State::base;
          }
        }
        break;
      case State::found_do:
        if (next_c == 'n') {
          state = State::found_don;
        } else if (next_c == '(') {
          state = State::found_do_op;
        } else {
          if (state != State::found_dont) {
            state = State::base;
          }
        }
        break;
      case State::found_don:
        if (next_c == '\'') {
          state = State::found_don_tick;
        } else {
          if (state != State::found_dont) {
            state = State::base;
          }
        }
        break;
      case State::found_don_tick:
        if (next_c == 't') {
          state = State::found_don_tick_t;
        } else {
          if (state != State::found_dont) {
            state = State::base;
          }
        }
        break;
      case State::found_don_tick_t:
        if (next_c == '(') {
          state = State::found_don_tick_t_op;
        } else {
          if (state != State::found_dont) {
            state = State::base;
          }
        }
        break;
      case State::found_don_tick_t_op:
        if (next_c == ')') {
          state = State::found_dont;
        } else {
          if (state != State::found_dont) {
            state = State::base;
          }
        }
        break;
      case State::found_dont:
        if (next_c == 'd') {
          state = State::found_d;
        }
        break;
      case State::found_do_op:
        if (next_c == ')') {
          state = State::base;
        } else {
          if (state != State::found_dont) {
            state = State::base;
          }
        }
        break;
    }
  }
  cout << "Total: " << total << endl;

  return 0;
}