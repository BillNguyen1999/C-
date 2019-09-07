
#include "Stack.h"
#include "CardTypes.h"
#include "GameBoard.h"
#include "CardStack.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

//using namespace std;



BoardT::BoardT(){

}
	
BoardT::BoardT(std::vector<CardT> deck){
	if(!two_decks(init_seq(10), init_seq(8), CardStackT(deck), CardStackT(std::vector<CardT>()))) throw std::invalid_argument("incorrect deck");

	//std::vector<CardT> tableau = std::vector<CardT>(deck.begin(), deck.begin() + 39);
	std::vector<CardT> tableau;
	for(int i = 0; i < 40; i++){
		tableau.push_back(deck[i]);
	}
	// std::vector<CardT> d2;
	// for(int i = 40; i < 103; i++){
	// 	d2.push_back(deck[i]);
	// }
	this->T = tab_deck(tableau);
	this->F = init_seq(8);
	this->D = CardStackT(std::vector<CardT>(deck.begin()+40, deck.end()));
	this->W = CardStackT(std::vector<CardT>());
}

bool BoardT::is_valid_tab_mv(CategoryT c, unsigned int n0, unsigned int n1) {
	if(c == Tableau && !(is_valid_pos(Tableau, n0) && is_valid_pos(Tableau, n1))) throw std::out_of_range("not valid");
	if(c == Foundation && !(is_valid_pos(Tableau, n0) && is_valid_pos(Foundation, n1))) throw std::out_of_range("not valid");
	if(c == Tableau) {
		return valid_tab_tab(n0, n1);
	} else if(c == Foundation) {
		return valid_tab_foundation(n0, n1);
	}
	return false;
}

bool BoardT::is_valid_waste_mv(CategoryT c, unsigned int n) {
	if(W.size() == 0) throw std::invalid_argument("not valid");
	if(c == Tableau && !is_valid_pos(Tableau, n)) throw std::out_of_range("not valid");
	if(c == Foundation && !is_valid_pos(Foundation, n)) throw std::out_of_range("not valid");
	if(c == Tableau) {
		return valid_waste_tab(n);
	} else if(c == Foundation) {
		return valid_waste_foundation(n);
	}
	return false;
}

bool BoardT::is_valid_deck_mv() {
	return D.size() > 0;
}

void BoardT::tab_mv(CategoryT c, unsigned int n0, unsigned int n1) {
	if(!is_valid_tab_mv(c, n0, n1)) {
		throw std::invalid_argument("not a valid move");
	} else if(c == Tableau) {
		T[n1] = T[n1].push(T[n0].top());
		T[n0] = T[n0].pop();
	} else if(c == Foundation) {
		F[n1] = F[n1].push(T[n0].top());
		T[n0] = T[n0].pop();
	}
}

void BoardT::waste_mv(CategoryT c, unsigned int n) {
	if(!is_valid_waste_mv(c, n)) {
		throw std::invalid_argument("not a valid move");
	} else if(c == Tableau) {
		T[n] = T[n].push(W.top());
		W = W.pop();
	} else if(c == Foundation) {
		F[n] = F[n].push(W.top());
		W = W.pop();
	}
}

void BoardT::deck_mv() {
	if(!is_valid_deck_mv()) {
		throw std::invalid_argument("not a valid move");
	} else {
		W = W.push(D.top());
		D = D.pop();
	}
	
}

CardStackT BoardT::get_tab(unsigned int i) {
	if(!is_valid_pos(Tableau, i)) throw std::out_of_range("not a valid move");
	return T[i];
}


CardStackT BoardT::get_foundation(unsigned int i){
	if(!is_valid_pos(Foundation, i)) throw std::out_of_range("not a valid move");
	return F[i];
}

CardStackT BoardT::get_deck() {
	return D;
}
        
CardStackT BoardT::get_waste() {
	return W;
}

bool BoardT::valid_mv_exists() {
	bool valid_tab_mv = false;
	bool valid_waste_mv = false;
	// if(W.size() == 0) {
	// 	return false;
	// }
	for(unsigned int n0 = 0; is_valid_pos(Tableau, n0) != false; n0++){
		for(unsigned int n1 = 0; is_valid_pos(Tableau, n1) != false; n1++) {
			if(is_valid_tab_mv(Tableau, n0, n1)) {
				valid_tab_mv = true;
				break;
			}
		}
	}

	for(unsigned int n0 = 0; is_valid_pos(Tableau, n0) != false; n0++){
		for(unsigned int n1 = 0; is_valid_pos(Foundation, n1) != false; n1++) {
			if(is_valid_tab_mv(Foundation, n0, n1)) {
				valid_tab_mv = true;
				break;
			}
		}
	}

	for(unsigned int n = 0; is_valid_pos(Tableau, n) != false; n++){
		if(W.size() == 0) {
			valid_waste_mv = false;
			break;
		}
		if(is_valid_waste_mv(Tableau, n)) {
			valid_waste_mv = true;
			break;
		}	
	}

	for(unsigned int n = 0; is_valid_pos(Foundation, n) != false; n++){
		if(W.size() == 0) {
			valid_waste_mv = false;
			break;
		}
		if(is_valid_waste_mv(Foundation, n)) {
			valid_waste_mv = true;
			break;
		}	
	}

	return valid_tab_mv || valid_waste_mv || is_valid_deck_mv();

}

bool BoardT::is_win_state() {

	for(unsigned int i = 0; i < 8; i++){
		if(F[i].size() <= 0) {
			return false;
		} else if(F[i].top().r != KING) {
			return false;
		}
	}
	return true;
}

unsigned int BoardT::cnt_cards_stack(CardStackT s, SuitT suit, RankT rank){
	unsigned int counter = 0;
	std::vector<CardT> stack_to_vector = s.toSeq();
	for(int i = 0; i < stack_to_vector.size(); i++) {
		if(stack_to_vector[i].r == rank && stack_to_vector[i].s == suit) {
			counter++;
		}
	}
	return counter;
}

unsigned int BoardT::cnt_cards_seq(std::vector<CardStackT> S, SuitT suit, RankT rank){
	unsigned int counter = 0;
	for(int i = 0; i < S.size(); i++) {
		counter = counter + cnt_cards_stack(S[i], suit, rank);
	}
	return counter;
}

unsigned int BoardT::cnt_cards(std::vector<CardStackT> T, std::vector<CardStackT> F, CardStackT D, CardStackT W, SuitT suit, RankT rank){
	unsigned int counter = 0;
	counter = counter + cnt_cards_seq(T, suit, rank);
	counter = counter + cnt_cards_seq(F, suit, rank);
	counter = counter + cnt_cards_stack(D, suit, rank);
	counter = counter + cnt_cards_stack(W, suit ,rank);
	return counter;
}

bool BoardT::two_decks(std::vector<CardStackT> T, std::vector<CardStackT> F, CardStackT D, CardStackT W) {
	bool identifier = true;
	std::vector<SuitT> suit{Heart, Diamond, Club, Spade};
	for(SuitT i : suit) {
		for(RankT j = ACE; j < KING + 1; j++) {
			identifier = identifier && (cnt_cards(T, F, D, W, i, j) == 2);
		}
	}

	return identifier;
}

std::vector<CardStackT> BoardT::tab_deck(std::vector<CardT> deck){
	std::vector<CardStackT> T;
	for(int i = 0; i < 10; i++){
		std::vector<CardT> temp;
		for(int j = 4*i; j <= (4*(i+1)-1); j++) {
			temp.push_back(deck[j]);
		}
		CardStackT temp2(temp);
		T.push_back(temp2);
	}

	return T;

}

std::vector<CardStackT> BoardT::init_seq(unsigned int n){
	std::vector<CardStackT> s;
	for(unsigned int i = 0; i < n; i++){
		std::vector<CardT> temp;
		CardStackT temp2(temp);
		s.push_back(temp2);
	}
	return s;
}

bool BoardT::is_valid_pos(CategoryT c, unsigned int n) {
	if(c == Tableau) {
		for(unsigned int i = 0; i < 10; i++) {
			if(n == i) {
				return true;
			}
		}
	} else if(c == Foundation) {
		for(unsigned int i = 0; i < 8; i++) {
			if(n == i) {
				return true;
			}
		}
	}
	return false;
}

bool BoardT::tab_placeable(CardT c, CardT d) {
	if((c.s == d.s) && (c.r == d.r + 1)) {
		return true;
	}
	return false;
}

bool BoardT::valid_tab_tab(unsigned int n0, unsigned int n1){
	if((T[n0].size() > 0) && (T[n1].size() > 0)) {
		bool value = tab_placeable(T[n0].top(), T[n1].top());
		return value;
		//maybe store tab_placeable in a variable and return the variable
	} else if((T[n0].size() > 0) && (T[n1].size() == 0)) {
		return true;
	}

	return false;

}

bool BoardT::foundation_placeable(CardT c, CardT d) {
	if((c.s == d.s) && (c.r == d.r + 1)) {
		return true;
	}
	return false;
}

bool BoardT::valid_tab_foundation(unsigned int n0, unsigned int n1){
	if((T[n0].size() > 0) && (F[n1].size() > 0)) {
		bool value = foundation_placeable(T[n0].top(), F[n1].top());
		return value;
		//maybe store tab_placeable in a variable and return the variable
	} else if((T[n0].size() > 0) && (F[n1].size() == 0)) {
		return T[n0].top().r == ACE;
	}

	return false;
}

bool BoardT::valid_waste_tab(unsigned int n){
	if(T[n].size() > 0) {
		bool value = tab_placeable(W.top(), T[n].top());
		return value;
	} else if(T[n].size() == 0) {
		return true;
	}
	return false;
}

bool BoardT::valid_waste_foundation(unsigned int n){
	if(F[n].size() > 0) {
		bool value = tab_placeable(W.top(), F[n].top());
		return value;
	} else if(F[n].size() == 0) {
		return W.top().r == ACE;
	}
	return false;
}



