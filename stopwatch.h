#pragma once

#include <chrono>
#include <string>
#include <ostream>

const std::string default_sw_name{ "default" };

class stopwatch {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    const std::string m_name;
public:
    stopwatch();
    stopwatch(const std::string& name);
    void reset();
    float mark();
    void print(std::ostream& to);
};

