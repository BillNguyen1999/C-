/**
 * \file CardTypes.h
 * \author Bill Nguyen
 * \brief defining all necessary card types
 */
#ifndef A3_CARD_TYPES_H_
#define A3_CARD_TYPES_H_




/**
 * \brief Describes the rank of a card.
 */
typedef unsigned short int RankT;

/**
 * \brief RankT for an Ace.
 */
#define ACE    1

/**
 * \brief RankT for an Jack.
 */
#define JACK   11

/**
 * \brief RankT for a Queen.
 */
#define QUEEN  12

/**
 * \brief RankT for a King.
 */
#define KING   13

/**
 * \brief defining total number of cards in the game
 */
#define TOTAL_CARDS 104

/**
 * \brief making an enum with four suits called SuitT
 */
enum SuitT {Heart, Diamond, Club, Spade};
/**
 * \brief making an enum with all categories called CategoryT
 */
enum CategoryT {Tableau, Foundation, Deck, Waste};

/**
 * \brief making a struct called CardT that has a suit and a rank to represent a card
 */
struct CardT {
    SuitT s;
    RankT r;
};

#endif
