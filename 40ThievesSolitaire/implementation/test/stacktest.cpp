#include "catch.h"
#include "Stack.h"
#include "CardTypes.h"
#include "GameBoard.h"
#include "CardStack.h"
#include <vector>
#include <stdexcept>


TEST_CASE("testing the stack", "[CardStackT]") {
	std::vector<RankT> rank{ACE, 2, 3, 4, 5, 6, 7, 8, 9, 10, JACK, QUEEN, KING};
	CardT one = {static_cast<SuitT>(Spade), rank[0]};
	CardT two = {static_cast<SuitT>(Spade), rank[1]};
	CardT three = {static_cast<SuitT>(Spade), rank[2]};

	std::vector<CardT> v1{one, two};
	std::vector<CardT> v2{one, two, three};
	

	SECTION("normal push test") {
		CardStackT push_test(v1);
		REQUIRE(push_test.push(three).top().r == three.r);
	}

	SECTION("push to empty stack") {
		CardStackT empty_push;
		REQUIRE(empty_push.push(two).top().r == two.r);
	}

	SECTION("normal pop test") {
		CardStackT pop_test(v2);
		REQUIRE(pop_test.pop().top().r == two.r);
	}

	SECTION("pop to empty stack") {
		CardStackT empty_pop;
		REQUIRE_THROWS_AS(empty_pop.pop(), std::out_of_range);
	}

	SECTION("top to empty stack") {
		CardStackT empty_pop;
		REQUIRE_THROWS_AS(empty_pop.top(), std::out_of_range);
	}

	SECTION("normal size test") {
		CardStackT pop_test(v2);
		REQUIRE(pop_test.size() == 3);
	}

	SECTION("empty size test") {
		CardStackT pop_test;
		REQUIRE(pop_test.size() == 0);
	}

	SECTION("normal toSeq test") {
		CardStackT seq_test(v2);
		REQUIRE(seq_test.toSeq()[0].r == one.r);
	}
}