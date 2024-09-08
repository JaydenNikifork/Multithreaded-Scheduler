#ifndef TASK_H
#define TASK_H

#include <memory>

class Instruction {
public:
  void run() {

  }
};

using InstrSPtr = std::shared_ptr<Instruction>;

class Task {
  int pc = 0;   // program counter
  vector<InstrSPtr> instrs;
  bool completed = false;


public:
  bool isWaiting = 0;

  Task(vector<InstrSPtr> instrs):
    instrs{instrs} {}

  void run() {
    while (!isWaiting && pc < instrs.size()) {
      instrs[pc].run();
    }

    if (pc >= instrs.size()) completed = true;
  }
};

#endif
