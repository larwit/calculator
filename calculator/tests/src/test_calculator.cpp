#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch2/catch.hpp"
#include <calculator.h>

TEST_CASE("Given tests", "[assigned]") {
	calculator::Calculator c;
	REQUIRE(c.Calculate("(4 + 5 * (7 - 3)) - 2") == 22);
	REQUIRE(c.Calculate("4+5+7/2") == 12);
	REQUIRE_THROWS(c.Calculate("10 + 1"));
	REQUIRE_THROWS(c.Calculate("-10"));

}

TEST_CASE("Additional tests", "[additional]") {
	calculator::Calculator c;
	REQUIRE(c.Calculate("7") == 7);
}