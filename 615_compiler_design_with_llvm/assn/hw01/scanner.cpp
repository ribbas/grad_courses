#include <fstream>
#include <iostream>
#include <string>

std::string read_file(std::fstream &file) {

  std::string temp, line;

  std::getline(file, temp);
  line = temp;
  while (temp.size() != 0) {
    std::getline(file, temp);
    line += temp;
  }
  return line;
}

int main(int, char **argv) {
  std::fstream file = std::fstream(argv[1], std::fstream::in);
  std::cout << read_file(file) << std::endl;
  file.close();
}