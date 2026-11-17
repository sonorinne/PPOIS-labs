#include "Menus.h"

#include "Dictionary.h"

#include <fstream>
#include <iomanip>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace {

bool ChangeEntry(Dictionary& dictionary, std::istringstream& args,
                 const std::string& command, std::ostream& output) {
  std::string word;
  std::string translation;
  if (!(args >> std::quoted(word))) return false;
  if (command == "remove") {
    dictionary -= word;
  } else if (command == "find") {
    const auto& result = dictionary[word];
    output << result << '\n';
  } else if (args >> std::quoted(translation)) {
    if (command == "add") dictionary += Dictionary::Entry{word, translation};
    else dictionary[word] = translation;
  } else {
    return false;
  }
  return true;
}

bool UseFile(Dictionary& dictionary, std::istringstream& args,
             const std::string& command) {
  std::string path;
  if (!(args >> std::quoted(path))) return false;
  if (command == "load") return dictionary.LoadFile(path);
  std::ofstream file(path);
  return static_cast<bool>(file << dictionary);
}

bool Execute(Dictionary& dictionary, std::istringstream& args,
             const std::string& command, std::ostream& output) {
  if (command == "list") output << dictionary;
  else if (command == "size") output << dictionary.Size() << '\n';
  else if (command == "load" || command == "save") {
    return UseFile(dictionary, args, command);
  } else if (command == "add" || command == "find" ||
             command == "replace" || command == "remove") {
    return ChangeEntry(dictionary, args, command, output);
  } else {
    return false;
  }
  return true;
}

}  // namespace

void DictionaryMenu(std::istream& input, std::ostream& output) {
  output << "Dictionary menu\n"
         << "add WORD TRANSLATION | find WORD | replace WORD TRANSLATION\n"
         << "remove WORD | size | list | load FILE | save FILE | exit\n";
  Dictionary dictionary;
  std::string line;
  while (output << "> " && std::getline(input, line)) {
    std::istringstream args(line);
    std::string command;
    if (!(args >> command)) continue;
    if (command == "exit") return;
    try {
      if (!Execute(dictionary, args, command, output)) output << "Invalid command or file\n";
    } catch (const std::out_of_range& error) {
      output << error.what() << '\n';
    }
  }
}
