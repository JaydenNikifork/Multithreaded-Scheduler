#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <memory>
#include <set>
#include <queue>
#include <thread>
#include <cmath>

#include "task.h"


class PriorityTask : public Task {
public:
  double priority;

  void setRunnable();

  void recomputePrio();
};

class Scheduler {
public:
  Scheduler(int maxThreads);

  void queueTask(Task &task);

  void start();

  void switch();

  void ioSwitch();

  void kill();
};

using PriorityTaskSPtr = std::shared_ptr<PriorityTask>;


#endif
