#include "catch.h"
#include "Conway.h"
#include <vector>
#include <stdexcept>

TEST_CASE("testing Conway", "[Conway]") {
	Conway test("src/input.txt");
	SECTION("checking if the constructor works") {
		REQUIRE(test.get_value(6,0));
	}

	SECTION("checking if the constructor works when point is suppose to be false") {
		REQUIRE(!test.get_value(5,0));
	}

	SECTION("testing for set_value") {
		test.set_value(0,0);
		REQUIRE(test.get_value(0,0));
	}

	SECTION("testing for remove_value") {
		test.remove_value(6,0);
		REQUIRE(!test.get_value(6,0));
	}

	SECTION("testing for set_value exception") {
		REQUIRE_THROWS_AS(test.set_value(10,10), std::out_of_range);
	}

	SECTION("testing for get_value exception") {
		REQUIRE_THROWS_AS(test.get_value(10,10), std::out_of_range);
	}

	SECTION("testing for remove_value exception") {
		REQUIRE_THROWS_AS(test.remove_value(10,10), std::out_of_range);
	}

	SECTION("testing for next") {
		test.next();
		bool result = test.get_value(6,1) && test.get_value(5,1) && test.get_value(0,1);
		REQUIRE(result);
	}

	SECTION("testing for output_graphics") {
		test.next();
		test.output_graphic();
		Conway output_test("src/output.txt");
		bool result = output_test.get_value(6,1) && test.get_value(5,1) && test.get_value(0,1);
		REQUIRE(result);
	}
}