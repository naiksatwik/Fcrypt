#include <iostream>
#include "IO.hpp"
#include <fstream>

IO::IO(const std::string &file_path)
{

      // here we are checking file is opening or not
      // ios::in-> to read file
      // ios::out -> to write file
      // ios ::binary -> convert in binary
      // combine -> |

      file_stream.open(file_path, std::ios::in | std::ios::out | std::ios::binary);
      if (!file_stream.is_open())
      {
            std::cout << "unable to open file: " << file_path << std::endl;
      }
}

// if file
std::fstream IO::getFileStream()
{
      // returning object of file_stream class to unique pointer
      return std::move(file_stream);
}

IO::~IO()
{
      // if file is opened . close it
      if (file_stream.is_open())
      {
            file_stream.close();
      }
}