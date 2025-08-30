#include <iostream>
#include <filesystem>
#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/processes/Task.hpp"

namespace fs = std::filesystem;

int main(int args, char *argv[])
{
      std::string directory;
      std::string action;

      std::cout << "Enter Directory path: " << std::endl;
      std::getline(std::cin, directory);

      std::cout << "Enter action (ENCRYPT / DECRYPT) " << std::endl;
      std::getline(std::cin, action);

      try
      {
            if (fs::exists(directory) && fs::is_directory(directory))
            {
                  ProcessManagement ProcessManagement;
                  for (const auto &entry : fs::recursive_directory_iterator(directory))
                  {
                        if (entry.is_regular_file())
                        {
                              std::string filepath = entry.path().string();
                              IO io(filepath);
                              std::fstream f_stream = std::move(io.getFileStream());

                              if (f_stream.is_open())
                              {
                                    Action taskAction = (action == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT);
                                    auto task = std::make_unique<Task>(std::move(f_stream), taskAction, filepath);
                                    ProcessManagement.submitToQueue(std::move(task));
                              }
                              else
                              {
                                    std::cout << "Unable to open file: " << filepath << std::endl;
                              }
                        }
                  }

                  ProcessManagement.executeTask();
            }
            else
            {
                  std::cout << "Invalid directory path " << std::endl;
            }
      }
      catch (const fs::filesystem_error &error)
      {
            std::cout << "Filesys Error : " << error.what() << std::endl;
      }
}