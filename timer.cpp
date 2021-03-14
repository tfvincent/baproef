#include <iostream>
#include <memory>
#include <chrono>

using namespace std;

class Timer {
  public:
    Timer(const char* name)
    : m_Name(name), m_Stopped(false){
      m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer(){
        if (!m_Stopped) {
            Stop();
        }
    }

    void Stop(){

      auto endTimePoint = std::chrono::high_resolution_clock::now();

      long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
      long long stop = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

      auto duration = end - start;
      double ms = duration * 0.001;

      std::cout << duration << "us(" << ms << "ms)\n";

      m_Stopped = true;
    }

  private:
    const char* m_Name;
    std::chrono::time_point< std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;
}
