#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Dictionary.h"

#include <sstream>
#include <stdexcept>

TEST_CASE("Insert, search, and change translations") {
  Dictionary dictionary;
  CHECK(dictionary.Size() == 0);
  dictionary += std::make_pair("tree", "дерево");
  dictionary += Dictionary::Entry{"apple", "яблоко"};
  char word[] = "zebra";
  char translation[] = "зебра";
  dictionary += std::make_pair(word, translation);
  dictionary += std::make_pair("tree", "древесина");
  CHECK(dictionary.Size() == 3);
  const Dictionary& view = dictionary;
  CHECK(view["tree"] == "древесина");
  CHECK(view["zebra"] == "зебра");
  dictionary["apple"] = "яблочко";
  CHECK(view["apple"] == "яблочко");
  CHECK_THROWS_AS(view["unknown"], std::out_of_range);
}

TEST_CASE("Delete missing words, leaves and nodes with children") {
  Dictionary dictionary;
  for (const char* word : {"m", "g", "s", "q", "r", "d", "z"}) {
    dictionary += std::make_pair(word, "word");
  }
  dictionary -= "missing";
  CHECK(dictionary.Size() == 7);
  dictionary -= "m";  // Two children, successor q has its own right child.
  CHECK(dictionary["r"] == "word");
  dictionary -= "g";  // Left child only.
  CHECK(dictionary["d"] == "word");
  dictionary -= "z";  // Leaf.
  dictionary -= "s";  // Left child only after z was removed.
  dictionary -= "d";
  dictionary -= "q";  // Right child only.
  CHECK(dictionary.Size() == 1);
  CHECK(dictionary["r"] == "word");
  dictionary -= "r";
  CHECK(dictionary == Dictionary{});
}

TEST_CASE("Copies are independent and equality ignores tree shape") {
  Dictionary first;
  first += std::make_pair("a", "one");
  first += std::make_pair("b", "two");
  Dictionary second(first);
  CHECK(second == first);
  second["a"] = "changed";
  CHECK(second != first);
  CHECK(first["a"] == "one");
  second = first;
  const Dictionary& alias = second;
  second = alias;
  CHECK(second == first);
  Dictionary reversed;
  reversed += std::make_pair("b", "two");
  reversed += std::make_pair("a", "one");
  CHECK(reversed == first);
  reversed -= "a";
  reversed += std::make_pair("c", "one");
  CHECK(reversed != first);
  reversed -= "c";
  CHECK(reversed != first);
}

TEST_CASE("Dictionary stream input is transactional and supports spaces") {
  Dictionary dictionary;
  REQUIRE(dictionary.LoadFile("examples/dictionary.txt"));
  CHECK(dictionary["tree"] == "дерево");
  dictionary += std::make_pair("blue sky", "голубое небо");
  std::stringstream text;
  text << dictionary;
  Dictionary loaded;
  REQUIRE(static_cast<bool>(text >> loaded));
  CHECK(loaded == dictionary);
  CHECK_FALSE(loaded.LoadFile("missing_dictionary.txt"));
  for (const char* broken : {"", "-1", "2\nword translation\nincomplete"}) {
    std::istringstream input(broken);
    CHECK_FALSE(static_cast<bool>(input >> loaded));
    CHECK(loaded == dictionary);
  }
}
