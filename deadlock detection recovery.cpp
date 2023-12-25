#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Resource {
public:
    int id;
    bool allocated;
};

class Process {
public:
    int id;
    vector<int> allocatedResources;
};

class DeadlockDetector {
private:
    vector<Process> processes;
    vector<Resource> resources;

public:
    DeadlockDetector(vector<Process> p, vector<Resource> r) : processes(p), resources(r) {}

    void detectAndRecover() {
        vector<int> deadlockProcesses = findDeadlockProcesses();
        
        if (!deadlockProcesses.empty()) {
            cout << "Deadlock detected! Deadlock processes: ";
            for (int processId : deadlockProcesses) {
                cout << processId << " ";
            }
            cout << endl;

            // Perform recovery actions, such as releasing resources or killing processes.
            recoverFromDeadlock(deadlockProcesses);
        } else {
            cout << "No deadlock detected." << endl;
        }
    }

private:
    vector<int> findDeadlockProcesses() {
        vector<int> deadlockProcesses;

        for (const Process& process : processes) {
            // Check if the process is in a deadlock by verifying if all its allocated resources are allocated.
            if (all_of(process.allocatedResources.begin(), process.allocatedResources.end(),
                       [this](int resourceId) { return resources[resourceId].allocated; })) {
                deadlockProcesses.push_back(process.id);
            }
        }

        return deadlockProcesses;
    }

    void recoverFromDeadlock(const vector<int>& deadlockProcesses) {
        // Perform recovery actions here, such as releasing resources or terminating processes.
        for (int processId : deadlockProcesses) {
            // Example: Release resources of the deadlock process
            for (int resourceId : processes[processId].allocatedResources) {
                resources[resourceId].allocated = false;
            }

            // Example: Terminate the deadlock process
            processes.erase(remove_if(processes.begin(), processes.end(),
                                      [processId](const Process& process) { return process.id == processId; }),
                             processes.end());
        }

        cout << "Deadlock recovery completed." << endl;
    }
};

int main() {
    // Initialize processes and resources
    vector<Process> processes = {{0, {0, 1}},
                                {1, {1, 2}},
                                {2, {2, 0}}};

    vector<Resource> resources = {{0, false},
                                 {1, false},
                                 {2, false}};

    // Create a deadlock detector
    DeadlockDetector deadlockDetector(processes, resources);

    // Simulate the system and periodically check for deadlocks
    deadlockDetector.detectAndRecover();

    return 0;
}
