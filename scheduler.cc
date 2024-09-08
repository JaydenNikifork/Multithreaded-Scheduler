#include "scheduler.h"

class PriorityTask : public Task {
  const int UPPER_LIMIT = 100;
  double runningTime = 0;

  PriorityTask(Task &task): Task{Task} {}

public:
  double priority;

  bool isRunnable() { return isWaiting(); }

  void setRunnable() {
    isWaiting = false;
  }

  void recomputePrio() {
    if (isWaiting) priority = 0;

    double x = -runningTime;   // variable of sigmoid fn

    priority = UPPER_LIMIT / (1 + exp(-x));
  }
};

class Scheduler {
  priority_queue<PriorityTaskSPtr> tasks;
  unordered_set<PriorityTaskSPtr> waitingTasks;
  PriorityTaskSPtr currentTask;
  
  int maxThreads; // can probably determine this by the program input

  bool isKilled = false;

  void recomputeTaskPrio(PriorityTaskSPtr pTask) {
    pTask->recomputePrio();
  }
  
  void checkWaitingSet() {
    for (auto &taskPtr : waitingTasks) {
      if (taskPtr->isRunnable) recomputeAndPushTask(taskPtr);
    }
  }

  void run() {
    while (!isKilled) {
      if (tasks.isEmpty()) {
        checkWaitingSet();
      } else if (!currentTask) {
        runNextTask();
      }
    }
  }

  // Runs the highest prio task and returns the old one
  // Note that there may have been no task running (return nullptr)
  PriorityTaskSPtr &runNextTask() {
    PriorityTaskSPtr newCurrent = tasks.top();
    tasks.pop();
    PriorityTaskSPtr oldCurrent = currentTask;
    currentTask = newCurrent;
    return oldCurrent;
  }

  void recomputeAndPushTask(PriorityTaskSPtr pTask) {
    if (!pTask) return;

    pTask->recomputePrio();
    tasks.push(pTask);
  }

public:
  Scheduler(int maxThreads):
    tasks{},
    waitingTasks{},
    currentTask{nullptr},
    maxThreads{maxThreads} {}

  void queueTask(Task &task) {
    PriorityTaskSPtr std::make_shared<PriorityTask>(task);
    
    tasks.push(pTask);
  }

  void start() {
    std::thread(run).detach();
  }

  void switch() {
    checkWaitingSet();

    if (!tasks.empty()) {
      PriorityTaskSPtr prevTask = runNextTask();
      recomputeAndPushTask(prevTask);
    }
  }

  void ioSwitch() {
    checkWaitingSet();

    if (!tasks.empty()) {
      PriorityTaskSPtr prevTask = runNextTask();
      waitingTasks.push(prevTask);
    }
  }

  void kill() { isKilled = true; }
};

#endif
