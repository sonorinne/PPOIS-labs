#pragma once

#include <iosfwd>

void DictionaryMenu(std::istream& input, std::ostream& output);
void TuringMenu(std::istream& input, std::ostream& output);
int RunTuringFile(const char* path, bool log, std::ostream& output,
                  std::ostream& errors);
