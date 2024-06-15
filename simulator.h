#ifndef SIMULATOR_H
#define SIMULATOR_H

#define RANDOM_SEED 369369

#include <cstdlib>
#include <functional>
#include <queue>
#include <vector>

class Simulator;

class Schedule {
private:
  double time_;
  std::function<void()> function_;
  int order_;
  static int nextOrder_;

public:

  double time() { return time_; }
  void call() { function_(); }

  Schedule(double time, std::function<void()> function)
      : time_(time), function_(function), order_(nextOrder_++) {}

  bool operator>(const Schedule& other) const {
    if(this->time_ == other.time_) {
      return this->order_ > other.order_;
    }
    else {
      return this->time_ > other.time_;
    } 
  }
};

class Simulator {
private:
  static double time_;

  static std::priority_queue<Schedule, std::vector<Schedule>, std::greater<Schedule>> schedules_;

public:
  static double now() { return time_; }

  static void prepare() { srand(RANDOM_SEED); }

  static void schedule(double time, std::function<void()> function) {
    // 스케줄 큐에 스케줄을 추가한다.
    schedules_.push(Schedule(time, function));
  }

  static void run() {
    // 모든 스케줄을 실행한다.
    while(!schedules_.empty()) {
      Schedule schedule = schedules_.top();
      schedules_.pop();

      time_ = schedule.time();
      schedule.call();
    }
  }
};

#endif