#include "RunReport.hh"

using namespace std;

int RunReport::Begin(string desc) {
    steps.emplace_back(ReportStep(desc));
    steps[steps.size() - 1].iTime = chrono::steady_clock::now();
    return steps.size() - 1;
}

int64_t RunReport::Stop(RunReport::TimeScale ts) {
    return Stop(steps.size() - 1, ts);
}

int64_t RunReport::Stop(int i, RunReport::TimeScale ts) {
    steps[i].eTime = chrono::steady_clock::now();
    steps[i].time = chrono::duration_cast<chrono::nanoseconds>(steps[i].eTime - steps[i].iTime).count();

    if (ts == RunReport::TimeScale::ns)
        return steps[i].time;
    else
        return steps[i].time / 1000000;
}

void RunReport::Print(RunReport::TimeScale ts) {
    int lDesc = 0;
    double totalTime = 0;
    for (auto step : steps) {
        lDesc = max(lDesc, (int)step.desc.size());
        totalTime += step.time;
    }

    printf("---- Time Taken ----\n");
    string tts = (ts == TimeScale::ns) ? "(ns)" : "(ms)";
    string ttl = "Time Taken " + tts;
    printf("%-*s %-*s %s\n", lDesc, "Description", (int)ttl.size(), ttl.c_str(), "Time Taken (%)");
    for (auto step : steps) {
        if (ts == TimeScale::ns)
            printf("%-*s %-*ld %-3.3f\n", lDesc, step.desc.c_str(), (int)ttl.size(), (long)step.time, step.time / totalTime * 100.0);
        else
            printf("%-*s %-*.3f %-3.3f\n", lDesc, step.desc.c_str(), (int)ttl.size(), step.time / 1000000.0, step.time / totalTime * 100.0);
    }
    if (ts == TimeScale::ns)
        printf("%-*s %ld\n", lDesc, "Total Time", (long)totalTime);
    else
        printf("%-*s %.3f\n", lDesc, "Total Time", totalTime / 1000000.0);
}
