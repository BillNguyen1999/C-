#include "catch.h"
#include "Stack.h"
#include "CardTypes.h"
#include "GameBoard.h"
#include "CardStack.h"
#include <vector>
#include <stdexcept>

TEST_CASE("testing BoardT", "[GameBoard]") {
	std::vector<CardT> d;
	//std::vector<CardT> d2;
    for (RankT rank = ACE; rank <= 5; rank++) {
        for (unsigned int suit = 0; suit < 4; suit++) {
            CardT n = { static_cast<SuitT>(suit), rank };
            d.push_back(n);
            d.push_back(n);
        }
    }

    for (RankT rank = KING; rank >= 6; rank--) {
        for (unsigned int suit = 0; suit < 4; suit++) {
            CardT n = { static_cast<SuitT>(suit), rank };
            d.push_back(n);
            d.push_back(n);
        }
    }
    BoardT board(d);

    SECTION("normal is_valid_tab_mv from tab to tab") {
    	REQUIRE(board.is_valid_tab_mv(Tableau, 3, 1));
    }

    SECTION("normal is_valid_tab_mv from tab to tab but its not valid") {
    	REQUIRE(!board.is_valid_tab_mv(Tableau, 1, 3));
    }

    SECTION("raise exception for is_valid_tab_mv") {
    	REQUIRE_THROWS_AS(board.is_valid_tab_mv(Tableau, 12, 11), std::out_of_range);
    }

    SECTION("normal is_valid_tab_mv from tab to foundation") {
    	REQUIRE(board.is_valid_tab_mv(Foundation, 0, 1));
    }

    SECTION("normal is_valid_tab_mv from tab to foundation but its not valid") {
    	REQUIRE(!board.is_valid_tab_mv(Foundation, 2, 3));
    }

    SECTION("normal is_valid_waste_mv") {
    	board.deck_mv();
    	REQUIRE(board.is_valid_waste_mv(Tableau, 9));
    }

    SECTION("normal is_valid_waste_mv but not valid") {
    	board.deck_mv();
    	board.deck_mv();
    	board.deck_mv();
    	REQUIRE(!board.is_valid_waste_mv(Tableau, 9));
    }

    SECTION("exception for is_valid_waste_mv") {
    	REQUIRE_THROWS_AS(board.is_valid_waste_mv(Tableau, 10), std::invalid_argument);
    }

    SECTION("normal is_valid_deck_mv") {
    	REQUIRE(board.is_valid_deck_mv());
    }

    SECTION("normal tab_mv from tab to tab") {
    	board.tab_mv(Tableau, 3, 1);
    	REQUIRE(board.get_tab(1).top().r == 2);
    }

    SECTION("normal tab_mv from tab to foundation") {
    	board.tab_mv(Foundation, 0, 0);
    	REQUIRE(board.get_foundation(0).top().r == ACE);
    }

    SECTION("exception of tab_mv") {
    	REQUIRE_THROWS_AS(board.tab_mv(Tableau, 3, 4), std::invalid_argument);
    }

    SECTION("normal waste_mv") {
    	board.deck_mv();
    	board.waste_mv(Tableau, 9);
    	REQUIRE(board.get_tab(9).top().r == 6);
    }
    
    SECTION("exception of waste_mv") {
    	REQUIRE_THROWS_AS(board.waste_mv(Tableau, 9), std::invalid_argument);
    }

    SECTION("normal deck_mv") {
    	board.deck_mv();
    	REQUIRE(board.get_waste().top().r == 6);
    }

    SECTION("normal get_tab") {
    	REQUIRE(board.get_tab(0).top().r == ACE);
    }

    SECTION("exception get_tab") {
    	REQUIRE_THROWS_AS(board.get_tab(10).top().r, std::out_of_range);
    }

    SECTION("normal get_foundation") {
    	board.tab_mv(Foundation, 0, 0);
    	board.tab_mv(Foundation, 2, 0);
    	REQUIRE(board.get_foundation(0).top().r == 2);
    }

    SECTION("exception get_foundation") {
    	REQUIRE_THROWS_AS(board.get_foundation(8).top().r, std::out_of_range);
    }

    SECTION("normal get_waste") {
     	board.deck_mv();
    	REQUIRE(board.get_waste().top().r == 6);
    }

    SECTION("normal get_deck") {
    	REQUIRE(board.get_deck().top().r == 6);
    }

    SECTION("normal get_deck but after numerous moves from deck to waste") {
    	board.deck_mv();
	    board.deck_mv();
	    board.deck_mv();
	    board.deck_mv();
	    board.deck_mv();
	    board.deck_mv();
	    board.deck_mv();
	    board.deck_mv();
    	REQUIRE(board.get_deck().top().r == 7);
    }

    SECTION("normal valid_mv_exists") {
    	REQUIRE(board.valid_mv_exists());
    }

    SECTION("normal is_win_state") {
    	REQUIRE(!board.is_win_state());
    }


}