#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <iostream>
#include <queue>
#include <memory>

class ProcessManagement
{
public:
      ProcessManagement();

      // we get unique_ptr form "memory"
      bool submitToQueue(std::unique_ptr<Task> task);
      void executeTask();

private:
      std::queue<std::unique_ptr<Task>> taskQueue;
};
#endif