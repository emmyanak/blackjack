#include <iostream>
#include "Card.h"
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>

using namespace std;


//EEFECTS: intializes card to 2 of Spades 
Card::Card() {
rank = TWO;
suit = SPADES;
}

 //EFFECTS: initializes Card with rank_in and suit_in
Card::Card(Rank rank_in, Suit suit_in): rank(rank_in), suit(suit_in) {}


//EFFECTS: returns rank 
Card::Rank Card::get_rank() const{

   return rank; 
}

//EFFECTs: returns suit
Card::Suit Card::get_suit() const {

   return suit;
} 


//EFFECTS: Writes the Card to the stream
//  for example "Two of Spades"
std::ostream& operator << (std::ostream& os, const Card& c) {

switch(c.get_rank()){
case 0: os << "Two"; break;
case 1: os << "Three"; break;
case 2: os << "Four"; break;
case 3: os << "Five"; break;
case 4: os << "Six"; break;
case 5: os << "Seven"; break;
case 6: os << "Eight"; break;
case 7: os << "Nine"; break;
case 8: os << "Ten"; break;
case 9: os << "Jack"; break;
case 10: os << "Queen"; break;
case 11: os << "King"; break;
case 12: os << "Ace"; break;
}

os << " of ";

switch(c.get_suit()) {
case 0: os << "Spades"; break;
case 1: os << "Hearts"; break;
case 2: os << "Clubs"; break;
case 3: os << "Diamonds"; break;
}

return os; 
}


