#include "stopwatch.h"

stopwatch::stopwatch():stopwatch(default_sw_name) {}

stopwatch::stopwatch(const std::string& name) : m_name{ name } {
    reset();
}

void stopwatch::reset() {
    m_start = std::chrono::high_resolution_clock::now();
}

float stopwatch::mark() {
    std::chrono::duration<float, std::milli> elapsed = std::chrono::high_resolution_clock::now() - m_start;
    return elapsed.count();
}

void stopwatch::print(std::ostream& to) {
    float elapsed = mark();
    to << "sw." << m_name << ": " << elapsed << " ms" << std::endl;
}
