#include <doctest/doctest.h>

#include "TuringMachine.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

TEST_CASE("Blank cells can be read and restored on both sides of zero") {
  Tape tape;
  CHECK(tape.Read(-4) == Tape::kBlank);
  tape.Write(-4, 'a');
  tape.Write(8, 'b');
  Tape copy = tape;
  CHECK(copy == tape);
  copy.Write(-4, Tape::kBlank);
  CHECK(copy != tape);
  CHECK(copy.Read(-4) == Tape::kBlank);
  CHECK(tape.Read(-4) == 'a');

  std::stringstream text;
  text << tape;
  REQUIRE(static_cast<bool>(text >> copy));
  CHECK(copy == tape);
  for (const char* broken : {"", "-1", "1 -2"}) {
    std::istringstream input(broken);
    CHECK_FALSE(static_cast<bool>(input >> copy));
    CHECK(copy == tape);
  }
}

TEST_CASE("Rules can be added, replaced, found, and deleted") {
  Program rules;
  CHECK_FALSE(rules.AddRule("start", 'a', {"halt", 'a', 'X'}));
  REQUIRE(rules.AddRule("start", 'a', {"halt", 'b', 'L'}));
  const Rule* rule = rules.FindRule("start", 'a');
  REQUIRE(rule != nullptr);
  CHECK(rule->write == 'b');
  CHECK(rules.FindRule("start", 'b') == nullptr);
  Program copy(rules);
  REQUIRE(copy.AddRule("start", 'a', {"other", 'b', 'L'}));
  CHECK(copy != rules);
  REQUIRE(copy.AddRule("start", 'a', {"halt", 'c', 'L'}));
  CHECK(copy != rules);
  REQUIRE(copy.AddRule("start", 'a', {"halt", 'b', 'R'}));
  CHECK(copy != rules);
  std::stringstream text;
  text << rules;
  REQUIRE(static_cast<bool>(text >> copy));
  CHECK(copy == rules);
  CHECK(copy.RemoveRule("start", 'a'));
  CHECK_FALSE(copy.RemoveRule("start", 'a'));

  for (const char* broken : {"", "-1", "1 start a halt", "1 start a halt b X"}) {
    std::istringstream input(broken);
    CHECK_FALSE(static_cast<bool>(input >> rules));
    CHECK(rules.FindRule("start", 'a') != nullptr);
  }
}

TEST_CASE("The example adds one unit with right and stay transitions") {
  std::ifstream file("examples/unary_increment.txt");
  TuringMachine machine;
  REQUIRE(static_cast<bool>(file >> machine));
  TuringMachine copy = machine;
  CHECK(machine == copy);
  REQUIRE(machine.Step());
  CHECK(machine != copy);
  std::ostringstream log;
  machine.Run(&log);
  CHECK(log.str().find("State: start, head: 2") != std::string::npos);
  CHECK(log.str().find("State: halt, head: 3") != std::string::npos);
  CHECK_FALSE(machine.Step());
  CHECK(machine.GetTape().Read(3) == '1');
  CHECK(machine.GetTape().Read(4) == Tape::kBlank);

  std::stringstream text;
  text << machine;
  REQUIRE(static_cast<bool>(text >> copy));
  CHECK(copy == machine);
  std::istringstream broken("start 2 1 0");
  CHECK_FALSE(static_cast<bool>(broken >> copy));
  CHECK(copy == machine);
}

TEST_CASE("The head can move left and can detect integer overflow") {
  TuringMachine machine;
  REQUIRE(machine.GetProgram().AddRule("start", '_', {"next", 'a', 'L'}));
  REQUIRE(machine.GetProgram().AddRule("next", '_', {"halt", 'b', 'S'}));
  machine.Run();
  CHECK(machine.GetTape().Read(-1) == 'b');
  CHECK(machine.GetTape().Read(0) == 'a');

  std::istringstream left("start -9223372036854775808\n0\n1\nstart _ halt a L");
  REQUIRE(static_cast<bool>(left >> machine));
  CHECK_THROWS_AS(machine.Step(), std::overflow_error);
  std::istringstream right("start 9223372036854775807\n0\n1\nstart _ halt a R");
  REQUIRE(static_cast<bool>(right >> machine));
  CHECK_THROWS_AS(machine.Step(), std::overflow_error);
}
