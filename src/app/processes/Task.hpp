// we are creating our own datatype . by using struct
#include <string>
#include <iostream>
#include "../fileHandling/IO.hpp"
#include <fstream>
#include <sstream>

#ifndef TASK_HPP
#define TASK_HPP

enum class Action
{
      ENCRYPT,
      DECRYPT
};

struct Task
{
      std::string filePath;
      std::fstream f_stream;
      Action action;

      Task(std::fstream &&stream, Action act, std::string filePath)
      {
            this->filePath = filePath;
            // we are sending temp value && we nee to use move()
            f_stream = std::move(stream);
            action = act;
      }

      // serialize fuction
      std::string toString()
      {
            // converting to this formate "filepath,ENCRYPT or DECRYPT "
            std::ostringstream oss;
            oss << filePath << "," << ((action == Action::ENCRYPT) ? "ENCRYPT" : "DECRYPT");
            return oss.str();
      }

      // deserialize fuction
      static Task formString(const std::string &taskData)
      {
            // convert to normal Task Object
            std::istringstream iss(taskData);
            std::string filePath;
            std::string ActionStr;

            if (std::getline(iss, filePath, ',') && std::getline(iss, ActionStr))
            {
                  Action action = (ActionStr == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT);
                  IO io(filePath);
                  std::fstream f_stream = std::move(io.getFileStream());
                  if (f_stream.is_open())
                  {
                        return Task(std::move(f_stream), action, filePath);
                  }
                  else
                  {
                        throw std::runtime_error("Failed to open file: " + filePath);
                  }
            }
            else
            {
                  // not able to deserialize
                  throw std::runtime_error("Invalid task data formate..");
            }
      }
};

#endif