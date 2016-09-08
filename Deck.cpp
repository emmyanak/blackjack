#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring>

using namespace std;

// EFFECTS: constructs a "newly opened" deck of cards.  first the
// spades from 2-A, then the hearts, then the clubs, then the
// diamonds.  The first card dealt should be the 2 of Spades.
Deck::Deck() {

 for (int s = 0; s < DECK_SIZE/13; s++) //iterate through the suits 
 {
    for (int r = 0; r < DECK_SIZE/4; r++) //iterate through the ranks
    {
        cards[r + (s*13)] = Card(Card::Rank(r), Card::Suit(s));
    }
 }
 next = cards; //next points to the card on top of the deck 
}//end of the function 

// MODIFIES: this
// EFFECTS: resets the deck to the state of a "newly opened" deck
// of cards:
void Deck::reset() {

 for (int s = 0; s < DECK_SIZE/13; s++) //iterate through the suits 
 {
    for (int r = 0; r < DECK_SIZE/4; r++) //iterate through the ranks
    {
        cards[r + (s*13)] = Card(Card::Rank(r), Card::Suit(s));
    }
 }
 next = cards; //next points to the card on top of the deck 
}//end of the function 

// REQUIRES: n is between 0 and 52, inclusive.
// MODIFIES: this
// EFFECTS: cut the deck into two segments: the first n cards,
// called the "left", and the rest called the "right".  Note that
// either right or left might be empty.  Then, rearrange the deck
// to be the first card of the right, then the first card of the
// left, the 2nd of right, the 2nd of left, and so on.  Once one
// side is exhausted, fill in the remainder of the deck with the
// cards remaining in the othe rside.  Finally, make the first
// card in this shuffled deck the next card to deal.  For example,
// shuffle(26) on a newly-reset() deck results in: 2-clubs,
// 2-spades, 3-clubs, 3-spades ... A-diamonds, A-hearts.
//
// Note: if shuffle is called on a deck that has already had some
// cards dealt, those cards should first be restored to the deck
// in the order in which they were dealt, preserving the most
// recent post-shuffled/post-reset state.
// This function produces no output.
void Deck::shuffle(int n) {

assert(n >= 0 && n <= 52);

next = cards;

Card shuffled[DECK_SIZE];
int k = 0; 

   for (int s = 0; s < 52; s++) 
   {
      shuffled[s] = cards[s]; 
   }

   for (int i = 0; i < n; i++) 
   {
      if(i+n < DECK_SIZE) 
      {
        shuffled[k] = cards[n+i];
        k++;
        shuffled[k] = cards[i];
        k++;
      }
      else 
      {
       shuffled[k] = cards[i];
       k++;
      }
   }

   while (k < DECK_SIZE)
   {
      shuffled[k] = cards[k];
      k++;
   }

   for (int m = 0; m < DECK_SIZE; m++) 
   {
      cards[m] = shuffled[m]; 
   }

next = cards;  //assign next to point to the top of the deck 
}//end of shuffle 

// REQUIRES: deck is not empty
// MODIFIES: this
// EFFECTS: returns the next card to be dealt.
Card Deck::deal() {

  Card c = *next; 
  ++(next); //increment to the next card 
  return c; //deal the current card

}

// EFFECTS: returns the number of cards in the deck that have not
// been dealt since the last reset/shuffle.
int Deck::cards_remaining() const {

   return DECK_SIZE-(next-cards);

}



