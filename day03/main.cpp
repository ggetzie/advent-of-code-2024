#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

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

void popN(stack<State>& stateStack, int n) {
  for (int i = 0; i < n; i++) {
    stateStack.pop();
  }
}

int main() {
  ifstream file("input.txt");
  if (!file) {
    cerr << "Error opening file" << endl;
    return 1;
  }

  stack<State> stateStack;
  stateStack.push(State::base);

  string num1_buffer = "";
  string num2_buffer = "";
  int num1, num2;
  int total = 0;
  char next_c;
  while (file >> next_c) {
    switch (stateStack.top()) {
      case State::base:
        if (next_c == 'm') {
          stateStack.push(State::m);
        } else if (next_c == 'd') {
          stateStack.push(State::d);
        }
        break;
      case State::m:
        if (next_c == 'u') {
          stateStack.push(State::mu);
        } else if (next_c == 'd') {
          stateStack.pop();
          stateStack.push(State::d);
        } else {
          stateStack.pop();
        }
        break;
      case State::mu:
        if (next_c == 'l') {
          stateStack.push(State::mul);
        } else if (next_c == 'd') {
          popN(stateStack, 2);
          stateStack.push(State::d);
        } else {
          popN(stateStack, 2);
        }
        break;
      case State::mul:
        if (next_c == '(') {
          stateStack.push(State::mul_op);
        } else if (next_c == 'd') {
          popN(stateStack, 3);
          stateStack.push(State::d);
        } else {
          popN(stateStack, 3);
        }
        break;
      case State::mul_op:
        if (isdigit(next_c)) {
          // start collecting num1
          num1_buffer += next_c;
          stateStack.push(State::num1);
        } else if (next_c == 'd') {
          // possible start of do() or don't()
          popN(stateStack, 4);
          stateStack.push(State::d);
        } else {
          // we got mul( but no digit, so reset
          popN(stateStack, 4);
          num1_buffer = "";
        }
        break;
      case State::num1:
        if (isdigit(next_c)) {
          // more digits
          num1_buffer += next_c;
        } else if (next_c == ',') {
          // finished collecting num1
          stateStack.push(State::comma);
          num1 = stoi(num1_buffer);
          num1_buffer = "";
        } else if (next_c == 'd') {
          // possible start of do() or don't()
          popN(stateStack, 5);
          stateStack.push(State::d);
          num1_buffer = "";
        } else {
          // malformed mul() expression
          popN(stateStack, 5);
          num1_buffer = "";
        }
        break;
      case State::comma:
        if (isdigit(next_c)) {
          // start collecting num2
          num2_buffer += next_c;
          stateStack.push(State::num2);
        } else if (next_c == 'd') {
          // possible start of do() or don't()
          popN(stateStack, 6);
          stateStack.push(State::d);
        } else {
          // malformed mul() expression
          popN(stateStack, 6);
          num2_buffer = "";
        }
        break;
      case State::num2:
        if (isdigit(next_c)) {
          // more digits
          num2_buffer += next_c;
        } else if (next_c == ')') {
          // finished num2. Multiply and add to total
          // return to base state
          popN(stateStack, 7);
          num2 = stoi(num2_buffer);
          total += num1 * num2;
          num2_buffer = "";
        } else if (next_c == 'd') {
          // possible start of do() or don't()
          popN(stateStack, 7);
          stateStack.push(State::d);
          num2_buffer = "";
        } else {
          // malformed mul() expression
          popN(stateStack, 7);
          num2_buffer = "";
        }
        break;
      case State::d:
        if (next_c == 'o') {
          stateStack.push(State::do_);
        } else {
          // not a do() or don't() expression
          // return to the state before d (either base or don't)
          stateStack.pop();
        }
        break;
      case State::do_:
        if (next_c == 'n') {
          stateStack.push(State::don);
        } else if (next_c == '(') {
          stateStack.push(State::do_op);
        } else {
          // not a do() or don't() expression
          // return to the state before d
          popN(stateStack, 2);
        }
        break;
      case State::don:
        if (next_c == '\'') {
          stateStack.push(State::don_tick);
        } else {
          // return to the state before d
          popN(stateStack, 3);
        }
        break;
      case State::don_tick:
        if (next_c == 't') {
          stateStack.push(State::don_tick_t);
        } else {
          // return to the state before d
          popN(stateStack, 4);
        }
        break;
      case State::don_tick_t:
        if (next_c == '(') {
          stateStack.push(State::don_tick_t_op);
        } else {
          // return to the state before d
          popN(stateStack, 5);
        }
        break;
      case State::don_tick_t_op:
        if (next_c == ')') {
          // entered don't() state
          popN(stateStack, stateStack.size());
          stateStack.push(State::dont);
        } else {
          popN(stateStack, 6);
        }
        break;
      case State::dont:
        if (next_c == 'd') {
          // possible start of do() expression to resume computation
          stateStack.push(State::d);
        }
        // otherwise, stay in don't() state
        break;
      case State::do_op:
        if (next_c == ')') {
          popN(stateStack, stateStack.size());
          stateStack.push(State::base);
        } else {
          // return to the state before d (base or don't)
          popN(stateStack, 3);
        }
        break;
    }
  }
  cout << "Total: " << total << endl;

  return 0;
}