#ifndef REPORT_HH
#define REPORT_HH

#include <string>
#include <vector>
#include <chrono>

struct ReportStep {
    std::string desc;
    // How long the step took in nano seconds
    int64_t time;
    // Initial time
    std::chrono::_V2::steady_clock::time_point iTime;
    // End time
    std::chrono::_V2::steady_clock::time_point eTime;
    ReportStep(std::string desc) : desc(desc) {}
};

class RunReport {
public:
    enum TimeScale {
        ms,
        ns
    };

    int Begin(std::string desc);

    // Returns time taken
    // Default is in ms
    int64_t Stop(TimeScale ts = TimeScale::ms);

    // Returns time taken
    // Default is in ms
    int64_t Stop(int i, TimeScale ts = TimeScale::ms);

    void Print(TimeScale ts = TimeScale::ms);

private:
    std::vector<ReportStep> steps;
};

#endif
