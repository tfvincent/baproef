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
    if (!m_Stopped) {
        Stop();
    }
}
void Timer::Stop(){

  auto endTimePoint = chrono::high_resolution_clock::now();

  long long start = chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
  long long stop = chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

  auto duration = (stop - start);
  cout << m_Name << ": " << duration << "ms\n";

  m_Stopped = true;
}
