#include "Menus.h"

#include <iostream>
#include <string_view>

int main(int argc, char* argv[]) {
  if (argc == 1) {
    TuringMenu(std::cin, std::cout);
    return 0;
  }
  if (argc == 2 && std::string_view(argv[1]) != "-log") {
    return RunTuringFile(argv[1], false, std::cout, std::cerr);
  }
  if (argc == 3 && std::string_view(argv[2]) == "-log") {
    return RunTuringFile(argv[1], true, std::cout, std::cerr);
  }
  std::cerr << "Usage: turing [file [-log]]\n";
  return 1;
}
