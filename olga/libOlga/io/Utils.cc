#include "Utils.hh"

#include <fstream>
#include <iostream>
#include <sstream>

bool io::ReadFile(String filename, String &contents) {
  std::ifstream input{filename};
  if (!input.is_open())
    return false;

  std::stringstream buf;
  buf << input.rdbuf();
  contents.assign(buf.str());
  return true;
}
