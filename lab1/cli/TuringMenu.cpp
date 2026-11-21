#include "Menus.h"

#include "TuringMachine.h"

#include <fstream>
#include <iomanip>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace {

bool EditRule(Program& program, std::istringstream& args, const std::string& command) {
  std::string state;
  char read = '\0';
  if (!(args >> state >> read)) return false;
  if (command == "remove") return program.RemoveRule(state, read);
  Rule rule{};
  if (!(args >> rule.next_state >> rule.write >> rule.move)) return false;
  return program.AddRule(state, read, rule);
}

bool Load(TuringMachine& machine, std::istringstream& args) {
  std::string path;
  if (!(args >> std::quoted(path))) return false;
  std::ifstream file(path);
  return static_cast<bool>(file >> machine);
}

bool WriteCell(Tape& tape, std::istringstream& args) {
  Tape::Position position = 0;
  char symbol = Tape::kBlank;
  if (!(args >> position >> symbol)) return false;
  tape.Write(position, symbol);
  return true;
}

bool Execute(TuringMachine& machine, std::istringstream& args,
             const std::string& command, std::ostream& output) {
  if (command == "show") machine.WriteState(output);
  else if (command == "rules") output << machine.GetProgram();
  else if (command == "step") {
    if (!machine.Step()) output << "No applicable rule\n";
    machine.WriteState(output);
  } else if (command == "run" || command == "log") {
    machine.Run(command == "log" ? &output : nullptr);
    machine.WriteState(output);
  } else if (command == "load") return Load(machine, args);
  else if (command == "write") return WriteCell(machine.GetTape(), args);
  else if (command == "add" || command == "remove") {
    return EditRule(machine.GetProgram(), args, command);
  } else return false;
  return true;
}

}  // namespace

void TuringMenu(std::istream& input, std::ostream& output) {
  output << "Turing machine menu\n"
         << "add STATE READ NEXT WRITE L/R/S | remove STATE READ | rules\n"
         << "write POSITION SYMBOL | show | step | run | log | load FILE | exit\n";
  TuringMachine machine;
  std::string line;
  while (output << "> " && std::getline(input, line)) {
    std::istringstream args(line);
    std::string command;
    if (!(args >> command)) continue;
    if (command == "exit") return;
    try {
      if (!Execute(machine, args, command, output)) output << "Invalid command or file\n";
    } catch (const std::overflow_error& error) {
      output << error.what() << '\n';
    }
  }
}

int RunTuringFile(const char* path, bool log, std::ostream& output, std::ostream& errors) {
  std::ifstream file(path);
  TuringMachine machine;
  if (!(file >> machine)) {
    errors << "Cannot load machine: " << path << '\n';
    return 1;
  }
  try {
    machine.Run(log ? &output : nullptr);
    machine.WriteState(output);
  } catch (const std::overflow_error& error) {
    errors << error.what() << '\n';
    return 1;
  }
  return 0;
}
