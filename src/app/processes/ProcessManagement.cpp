#include "ProcessManagement.hpp"
#include <iostream>
#include <cstring>
#include <cstdlib> // for system()

ProcessManagement::ProcessManagement() {}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task) {
    taskQueue.push(std::move(task));
    return true;
}

void ProcessManagement::executeTasks() {
    while (!taskQueue.empty()) {
        std::unique_ptr<Task> taskToExecute = std::move(taskQueue.front());
        taskQueue.pop();

        std::cout << "Executing task: " << taskToExecute->toString() << std::endl;

        // Run the cryption process using system command
        std::string command = "cryption.exe \"" + taskToExecute->toString() + "\"";
        system(command.c_str()); // For Windows
    }
}
