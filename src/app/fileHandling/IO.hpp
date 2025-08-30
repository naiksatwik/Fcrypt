#ifndef IO_HPP // if not defined
#define IO_HPP

#include <iostream>
#include <fstream>
#include <string>

class IO
{
public:
      // constructor
      IO(const std::string &file_path);

      // destructor
      ~IO();
      std::fstream getFileStream();

private:
      std::fstream file_stream;
};

#endif