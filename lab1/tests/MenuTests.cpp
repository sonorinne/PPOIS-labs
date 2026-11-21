#include <doctest/doctest.h>

#include "Menus.h"

#include <cstdio>
#include <fstream>
#include <sstream>

TEST_CASE("The dictionary menu exercises entries and file commands") {
  std::istringstream input(
      "\nadd tree oak\nfind tree\nreplace tree ash\nfind tree\n"
      "add apple\nremove tree\nfind tree\nsize\nlist\nunknown\n"
      "add\nload\nload absent.txt\nload examples/dictionary.txt\n"
      "save dictionary_menu_test.txt\nexit\n");
  std::ostringstream output;
  DictionaryMenu(input, output);
  const auto text = output.str();
  CHECK(text.find("oak") != std::string::npos);
  CHECK(text.find("ash") != std::string::npos);
  CHECK(text.find("Unknown word: tree") != std::string::npos);
  CHECK(text.find("Invalid command or file") != std::string::npos);
  std::ifstream saved("dictionary_menu_test.txt");
  int count = 0;
  CHECK(static_cast<bool>(saved >> count));
  CHECK(count == 3);
  saved.close();
  std::remove("dictionary_menu_test.txt");
}

TEST_CASE("The Turing menu edits tape and rules and executes a program") {
  std::istringstream input(
      "\nshow\nwrite\nwrite 0 1\nadd\nadd start 1\n"
      "add start 1 next 1 R\nremove start 1\nstep\n"
      "load\nload missing_machine.txt\nload examples/unary_increment.txt\n"
      "rules\nstep\nlog\nrun\nunknown\nexit\n");
  std::ostringstream output;
  TuringMenu(input, output);
  const auto text = output.str();
  CHECK(text.find("No applicable rule") != std::string::npos);
  CHECK(text.find("Invalid command or file") != std::string::npos);
  CHECK(text.find("State: start, head: 1") != std::string::npos);
  CHECK(text.find("State: halt, head: 3") != std::string::npos);
}

TEST_CASE("File mode and menu report malformed input and head overflow") {
  std::ostringstream output;
  std::ostringstream errors;
  CHECK(RunTuringFile("missing_machine.txt", false, output, errors) == 1);
  const char* path = "overflow_machine_test.txt";
  std::ofstream(path) << "start 9223372036854775807\n0\n1\nstart _ halt a R\n";
  CHECK(RunTuringFile(path, true, output, errors) == 1);
  std::istringstream input("load overflow_machine_test.txt\nstep\n");
  TuringMenu(input, output);
  std::remove(path);
  CHECK(errors.str().find("Cannot load machine") != std::string::npos);
  CHECK(errors.str().find("Head position is out of range") != std::string::npos);
  CHECK(output.str().find("Head position is out of range") != std::string::npos);
}
