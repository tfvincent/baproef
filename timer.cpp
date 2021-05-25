#include <iostream>
#include <memory>
#include <chrono>
#include <cmath>
#include "timer.h"

using namespace std;

Timer::Timer(const char* name): m_Name(name), m_Stopped(false){
    m_StartTimepoint = chrono::high_resolution_clock::now();
}

Timer::~Timer(){
}
unsigned long long Timer::Stop(){

  auto endTimePoint = chrono::high_resolution_clock::now();

  unsigned long long start = chrono::time_point_cast<std::chrono::nanoseconds>(m_StartTimepoint).time_since_epoch().count();
  unsigned long long stop = chrono::time_point_cast<std::chrono::nanoseconds>(endTimePoint).time_since_epoch().count();

  auto duration = (stop - start);

  m_Stopped = true;
  return duration;
}
