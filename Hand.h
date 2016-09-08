#ifndef HAND_H
#define HAND_H

#include "Card.h"

class Hand {
    // OVERVIEW: A blackjack hand of zero or more cards

public:
  // EFFECTS: establishes an empty blackjack hand.
  Hand();

  // MODIFIES: this
  // EFFECTS: discards any cards presently held, restoring the state
  // of the hand to that of an empty blackjack hand.
  void discard_all();

  // MODIFIES: this
  // EFFECTS: adds the card "c" to those presently held.
  void add_card(Card c);

  // EFFECTS: returns the present value of the blackjack hand.
  int hand_value() const;

  // EFFECTS: return true if and only if at least one ACE is present, and
  // its value is counted as 11 rather than 1.
  bool hand_is_soft() const;
private:
  // Note: this really is the only private state you need!
  int value;  // value of hand
  bool soft;  // true if hand value is a soft count
};

#endif
