#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Hand.h"

// A virtual base class, providing the player interface
class Player {
public:
  // REQUIRES: bankroll >= minimum
  //           bankroll >= 0
  //           minimum >= 0
  // EFFECTS: returns the player's bet, between minimum and bankroll
  // inclusive
  virtual int bet(int bankroll, int minimum) = 0;

  // EFFECTS: returns true if the player wishes to be dealt another
  // card, false otherwise.
  virtual bool draw(
                    Card dealer, // Dealer's "up card"
                    const Hand &player // Player's current hand
                    ) = 0;

  // EFFECTS: allows the player to "see" the newly-exposed card c.
  // For example, each card that is dealt "face up" is expose()d.
  // Likewise, if the dealer must show his "hole card", it is also
  // expose()d.  Note: not all cards dealt are expose()d---if the
  // player goes over 21 or is dealt a natural 21, the dealer need
  // not expose his hole card.
  virtual void expose(Card c) = 0;

  // EFFECTS: tells the player that the deck has been re-shuffled.
  virtual void shuffled() = 0;

  // Note: this is here only to suppress a compiler warning.
  //       Destructors are not needed for this project.
  virtual ~Player() { }
};

// REQUIRES: s is a C-string: "simple" "counting" or "competitor"
// EFFECTS: returns a pointer to the specified Player
Player * player_factory(const char * s);

#endif
