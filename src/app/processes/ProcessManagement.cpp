#include <iostream>
#include "ProcessManagement.hpp"
#include <string>
// used by process
#include <sys/wait.h>
// Encryption and Decryption Algo
#include "../encryptDecrypt/Cryption.hpp"

ProcessManagement::ProcessManagement()
{
}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task)
{
      taskQueue.push(std::move(task));
      return true;
}

// consume
void ProcessManagement::executeTask()
{
      while (!taskQueue.empty())
      {
            std::unique_ptr<Task> taskToExecute = std::move(taskQueue.front());
            taskQueue.pop();

            std::cout << "Execute task : " << taskToExecute->toString() << std::endl;

            executeCryption(taskToExecute->toString());
      }
}