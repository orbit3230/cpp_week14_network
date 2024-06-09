#include "simulator.h"

int Schedule::nextOrder_ = 0;
double Simulator::time_ = 0.0;
std::priority_queue<Schedule, std::vector<Schedule>, std::greater<Schedule>> Simulator::schedules_;