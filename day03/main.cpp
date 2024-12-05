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
    m,
    mu,
    mul,
    mul_op,  // found mul(
    num1,
    comma,
    num2,
    d,
    do_,
    do_op,  // found do(
    don,
    don_tick,       // found don'
    don_tick_t,     // found don't
    don_tick_t_op,  // found don't(
    dont            // found don't()
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
          state = State::m;
        } else if (next_c == 'd') {
          state = State::d;
        }
        break;
      case State::m:
        if (next_c == 'u') {
          state = State::mu;
        } else if (next_c == 'd') {
          state = State::d;
        } else {
          state = State::base;
        }
        break;
      case State::mu:
        if (next_c == 'l') {
          state = State::mul;
        } else if (next_c == 'd') {
          state = State::d;
        } else {
          state = State::base;
        }
        break;
      case State::mul:
        if (next_c == '(') {
          state = State::mul_op;
        } else if (next_c == 'd') {
          state = State::d;
        } else {
          state = State::base;
        }
        break;
      case State::mul_op:
        // if next_c is a digit, add it to num1_buffer
        if (isdigit(next_c)) {
          num1_buffer += next_c;
          state = State::num1;
        } else if (next_c == 'd') {
          state = State::d;
        }
        break;
      case State::num1:
        // if next_c is a digit, add it to num1_buffer
        if (isdigit(next_c)) {
          num1_buffer += next_c;
        } else if (next_c == ',') {
          state = State::comma;
          num1 = stoi(num1_buffer);
          num1_buffer = "";
        } else if (next_c == 'd') {
          state = State::d;
          num1_buffer = "";
        } else {
          state = State::base;
          num1_buffer = "";
        }
        break;
      case State::comma:
        // if next_c is a digit, add it to num2_buffer
        if (isdigit(next_c)) {
          num2_buffer += next_c;
          state = State::num2;
        } else if (next_c == 'd') {
          state = State::d;
        } else {
          state = State::base;
          num2_buffer = "";
        }
        break;
      case State::num2:
        // if next_c is a digit, add it to num2_buffer
        if (isdigit(next_c)) {
          num2_buffer += next_c;
        } else if (next_c == ')') {
          state = State::base;
          num2 = stoi(num2_buffer);
          total += num1 * num2;
          num2_buffer = "";
        } else if (next_c == 'd') {
          state = State::d;
          num2_buffer = "";
        } else {
          state = State::base;
          num2_buffer = "";
        }
        break;
      case State::d:
        if (next_c == 'o') {
          state = State::do_;
        } else {
          if (state != State::dont) {
            state = State::base;
          }
        }
        break;
      case State::do_:
        if (next_c == 'n') {
          state = State::don;
        } else if (next_c == '(') {
          state = State::do_op;
        } else {
          if (state != State::dont) {
            state = State::base;
          }
        }
        break;
      case State::don:
        if (next_c == '\'') {
          state = State::don_tick;
        } else {
          if (state != State::dont) {
            state = State::base;
          }
        }
        break;
      case State::don_tick:
        if (next_c == 't') {
          state = State::don_tick_t;
        } else {
          if (state != State::dont) {
            state = State::base;
          }
        }
        break;
      case State::don_tick_t:
        if (next_c == '(') {
          state = State::don_tick_t_op;
        } else {
          if (state != State::dont) {
            state = State::base;
          }
        }
        break;
      case State::don_tick_t_op:
        if (next_c == ')') {
          state = State::dont;
        } else {
          if (state != State::dont) {
            state = State::base;
          }
        }
        break;
      case State::dont:
        if (next_c == 'd') {
          state = State::d;
        }
        break;
      case State::do_op:
        if (next_c == ')') {
          state = State::base;
        } else {
          if (state != State::dont) {
            state = State::base;
          }
        }
        break;
    }
  }
  cout << "Total: " << total << endl;

  return 0;
}