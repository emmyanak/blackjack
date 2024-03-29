#ifndef DECK_H
#define DECK_H

#include "Card.h"

const int DECK_SIZE = 52;

class Deck {
public:

  // EFFECTS: constructs a "newly opened" deck of cards.  first the
  // spades from 2-A, then the hearts, then the clubs, then the
  // diamonds.  The first card dealt should be the 2 of Spades.
  Deck();

  // MODIFIES: this
  // EFFECTS: resets the deck to the state of a "newly opened" deck
  // of cards:
  void reset();

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
  void shuffle(int n);

  // REQUIRES: deck is not empty
  // MODIFIES: this
  // EFFECTS: returns the next card to be dealt.
  Card deal();

  // EFFECTS: returns the number of cards in the deck that have not
  // been dealt since the last reset/shuffle.
  int cards_remaining() const;

private:
  // A standard deck of 52 playing cards---no jokers
  Card      cards[DECK_SIZE];  // The deck of cards
  Card      *next;             // The next card to deal

  // Disable copy construction and assignment of Decks.
  Deck(const Deck& other);
  Deck& operator=(const Deck& rhs);
};

#endif
