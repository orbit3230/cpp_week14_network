#include "simulator.h"
#include "object.h"

int Schedule::nextOrder_ = 0;
double Simulator::time_ = 0.0;
std::priority_queue<Schedule, std::vector<Schedule>, std::greater<Schedule>> Simulator::schedules_;

void Simulator::run() {
  Object::initializeAll();

  // 모든 스케줄을 실행한다.
  while(!schedules_.empty()) {
    Schedule schedule = schedules_.top();
    schedules_.pop();

    time_ = schedule.time();
    schedule.call();
  }

  Object::cleanup();
}