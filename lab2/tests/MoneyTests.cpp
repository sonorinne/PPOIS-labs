#include <doctest/doctest.h>
#include "Money.h"
#include "InvalidAmount.h"
#include <limits>

TEST_CASE("BYN amounts use exact kopecks") {
  CHECK(Money::Parse("29.99").ToKopecks()==2999);
  CHECK(Money::Parse("29,99").ToString()=="29.99 BYN");
  CHECK(Money::Parse("29").ToString()=="29.00 BYN");
  CHECK(Money::Parse("0.1").ToString()=="0.10 BYN");
  CHECK(Money::Parse("0.01").ToString()=="0.01 BYN");
  CHECK(Money::Parse("0").ToKopecks()==0);
  CHECK(Money::FromKopecks(501).ToString()=="5.01 BYN");
}

TEST_CASE("Invalid payment text is rejected") {
  for (const char* text : {"", "-1", "+2", "1.234", "1.", ".99", "1..2", "1,2,3", "1e2", " 2", "2x"}) {
    CHECK_THROWS_AS(Money::Parse(text),InvalidAmount);
  }
  CHECK_THROWS_AS(Money::FromKopecks(-1),InvalidAmount);
}

TEST_CASE("BYN parsing checks integer boundaries") {
  CHECK(Money::Parse("21474836.47").ToKopecks()==std::numeric_limits<int>::max());
  CHECK_THROWS_AS(Money::Parse("21474836.48"),InvalidAmount);
  CHECK_THROWS_AS(Money::Parse("21474837"),InvalidAmount);
  CHECK_THROWS_AS(Money::Parse("99999999999999999"),InvalidAmount);
}
