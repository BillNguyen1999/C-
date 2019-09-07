/**
 * \file CardStack.h
 * \author Bill Nguyen
 * \brief The gameboard and how it is created
 */
#ifndef A3_GAME_BOARD_H_
#define A3_GAME_BOARD_H_

#include "Stack.h"
#include "CardTypes.h"
#include "CardStack.h"
#include <vector>

//using namespace std;

/**
 * \brief Class that represents the Board of 40 thieves called BoardT
 */
class BoardT
{
    private:
        std::vector<CardStackT> T;
        std::vector<CardStackT> F;
        CardStackT D;
        CardStackT W;
    
        /**
         * \brief checks there is 2 of each card 
         * \param T is a vector<CardStackT> that represents the tableau
         * \param F is a vector<CardStackT> that represents the foundation
         * \param D is type CardStackT that represents the deck
         * \param W is type CardStackT that represents the waste
         * \returns a bool that indicates whether there is 2 of each card
         */
        bool two_decks(std::vector<CardStackT> T, std::vector<CardStackT> F, CardStackT D, CardStackT W);
        /**
         * \brief counts how many cards are in a sequence that have the given suit and rank 
         * \param S is a vector<CardStackT> that represents the given sequence
         * \param suit of type SuitT represents the given suit that the counter checks
         * \param rank of type RankT represents the given rank that the counter checks
         * \returns a natural number that counts all the cards that have the desired suit and rank in the sequence
         */
        unsigned int cnt_cards_seq(std::vector<CardStackT> S, SuitT suit, RankT rank);
        /**
         * \brief counts how many cards are in a stack that have the given suit and rank 
         * \param s of type CardStackT that represents the given stack
         * \param suit of type SuitT represents the given suit that the counter checks
         * \param rank of type RankT represents the given rank that the counter checks
         * \returns a natural number that counts all the cards that have the desired suit and rank in the stack
         */
        unsigned int cnt_cards_stack(CardStackT s, SuitT suit, RankT rank);
        /**
         * \brief counts all the cards in T, F, D and W that have the desired suit and rank
         * \param T is a vector<CardStackT> that represents the tableau
         * \param F is a vector<CardStackT> that represents the foundation
         * \param D is type CardStackT that represents the deck
         * \param W is type CardStackT that represents the waste
         * \param suit of type SuitT represents the given suit that the counter checks
         * \param rank of type RankT represents the given rank that the counter checks
         * \returns a natural number that counts all the cards that have the desired suit and rank in T, F, D and W
         */
        unsigned int cnt_cards(std::vector<CardStackT> T, std::vector<CardStackT> F, CardStackT D, CardStackT W, SuitT suit, RankT rank);
        /** 
         * \brief makes a vector<CardStackT> of length n where each CardStackT is empty
         * \param n is a natural number that represents the desired length of the vector
         * \returns a vector<CardStackT> of length n where each CardStackT is empty
         */
        std::vector<CardStackT> init_seq(unsigned int n);
        /** 
         * \brief initializes that tableau by putting a 4 cards in each of the 10 stacks
         * \param deck is a vector<CardT> that represents the given deck of cards
         * \returns a vector<CardStackT> that represents the tableau with 4 cards in each of the 10 stacks
         */
        std::vector<CardStackT> tab_deck(std::vector<CardT> deck);
        /** 
         * \brief checks if the inputted index is 0 to 9 for tableau and 0 to 7 for foundation
         * \param c of type CategoryT that represents a category
         * \param n is a natural number that represents the index
         * \returns a boolean that checks whether the inputted index is 0 to 9 for tableau and 0 to 7 for foundation
         */
        bool is_valid_pos(CategoryT c, unsigned int n);
        /** 
         * \brief checks a move from tableau to tableau is valid or not
         * \param n0 is a natural number that represents the index of the first tableau
         * \param n1 is a natural number that represents the index of the second tableau
         * \returns a boolean that checks whether a move from tableau to tableau is valid or not
         */
        bool valid_tab_tab(unsigned int n0, unsigned int n1);
        /** 
         * \brief checks whether card c has the same suit and if its rank is one lower than card d
         * \param c of type CardT is a card
         * \param d of type CardT is a card
         * \returns a boolean that checks whether card c has the same suit and if its rank is one lower than card d
         */
        bool tab_placeable(CardT c, CardT d);
        /** 
         * \brief checks a move from tableau to foundation is valid or not
         * \param n0 is a natural number that represents the index of the tableau
         * \param n1 is a natural number that represents the index of the foundation
         * \returns a boolean that checks whether a move from tableau to foundation is valid or not
         */
        bool valid_tab_foundation(unsigned int n0, unsigned int n1);
        /** 
         * \brief checks whether card c has the same suit and if its rank is one lower than card d
         * \param c of type CardT is a card
         * \param d of type CardT is a card
         * \returns a boolean that checks whether card c has the same suit and if its rank is one lower than card d
         */
        bool foundation_placeable(CardT c, CardT d);
        /** 
         * \brief checks a move from waste to tableau is valid or not
         * \param n is a natural number that represents the index of the tableau
         * \returns a boolean that checks whether a move from waste to tableau is valid or not
         */
        bool valid_waste_tab(unsigned int n);
        /** 
         * \brief checks a move from waste to foundation is valid or not
         * \param n is a natural number that represents the index of the foundation
         * \returns a boolean that checks whether a move from waste to foundation is valid or not
         */
        bool valid_waste_foundation(unsigned int n);
    
    public:
        BoardT();
        /**
         * \brief constructor that initializes the board by setting up the tableau, foundation, deck and waste
         * \param vector<CardT> that is a vector of cards that represents the deck
         */
        BoardT(std::vector<CardT> deck);
        /**
         * \brief checks to see if a move is valid from tableau to the selected category
         * \param c of type CategoryT represents the intended category you want to move to
         * \param n0 is natural number that represents the index of selected tableau
         * \param n1 is natural number that represents the index of selected category
         * \returns a boolean value indicating whether the move is valid or not
         */
        bool is_valid_tab_mv(CategoryT c, unsigned int n0, unsigned int n1);
        /**
         * \brief checks to see if a move is valid from waste to the selected category
         * \param c of type CategoryT represents the intended category you want to move to
         * \param n is natural number that represents the index of selected category
         * \returns a boolean value indicating whether the move is valid or not
         */
        bool is_valid_waste_mv(CategoryT c, unsigned int n);
        /**
         * \brief checks to see if a move is valid from deck to waste
         * \details checks to size of deck is greater than zero
         * \returns a boolean value indicating whether the move is valid or not
         */
        bool is_valid_deck_mv();
        /**
         * \brief moves one card from tableau to a stack based on given category and only if move is valid
         * \details doesn't return anything but changes the value of tableau and given category
         * \param n0 is natural number that represents the index of selected tableau
         * \param n1 is natural number that represents the index of selected category
         */
        void tab_mv(CategoryT c, unsigned int n0, unsigned int n1);
        /**
         * \brief moves one card from waste to a stack based on given category and only if move is valid
         * \details doesn't return anything but changes the value of waste and given category
         * \param n is natural number that represents the index of selected category
         */
        void waste_mv(CategoryT c, unsigned int n);
        /**
         * \brief moves one card from deck to waste and only if move is valid
         * \details doesn't return anything but changes the value of deck and waste
         */
        void deck_mv();
        /**
         * \brief gets CardStackT in the vector tableau based on the given index
         * \param natural number i represents index of given CardStackT in tableau
         * \returns CardStackT in vector tableau based on given index
         */
        CardStackT get_tab(unsigned int i);
        /**
         * \brief gets CardStackT in the vector foundation based on the given index
         * \param natural number i represents index of given CardStackT in foundation
         * \returns CardStackT in vector foundation based on given index
         */
        CardStackT get_foundation(unsigned int i);
        /**
         * \brief gets the deck 
         * \returns returns the deck that is type CardStackT
         */
        CardStackT get_deck();
        /**
         * \brief gets the waste
         * \returns returns the waste that is type CardStackT
         */
        CardStackT get_waste();
        /**
         * \brief check to see if any valid move exists
         * \return returns a boolean value, true if valid move exists or false if there is no valid move
         */
        bool valid_mv_exists();
        /**
         * \brief check to see if an individual won the game
         * \detail checks to see if the top card in each stack of foundation is a king
         * \return returns a boolean value, true if an individual won the game or false if an individual has not won the game
         */
        bool is_win_state();
    
    
    
};


#endif
