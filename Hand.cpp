#include <iostream>
#include "Card.h"
#include "Hand.h"
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>

using namespace std;

Hand::Hand(): value(0), soft(false) {}


// MODIFIES: this
// EFFECTS: discards any cards presently held, restoring the state
// of the hand to that of an empty blackjack hand.
void Hand::discard_all() {
value = 0; 
soft = false; 
}

// MODIFIES: this
// EFFECTS: adds the card "c" to those presently held.
void Hand::add_card(Card c) {

//check for soft card
  if (c.get_rank() == Card::Rank(12)) 
  {
    if (value <= 10)
     {
     soft = true;
     value = value + 11; //soft hand 
     }
    else 
     {
     value = value + 1; //hard hand 
     }
  }

  for (int i = 0; i < 9; i++)
  {
   if (c.get_rank() == Card::Rank(i)) value = value + (i+2); 
  }

   if (c.get_rank() == Card::Rank(9) || c.get_rank() == Card::Rank(10) || c.get_rank() == Card::Rank(11)) {value = value + 10;} //face cards 

   if (value > 21 && soft == true)
   {
   //cout << "Value is > 21" << endl; 
   value = value - 10;
   soft = false; 
   }

}//end of add card function 


// EFFECTS: returns the present value of the blackjack hand.
int Hand::hand_value() const 
{
 return value;	
}

// EFFECTS: return true if and only if at least one ACE is present, and
// its value is counted as 11 rather than 1.
bool Hand::hand_is_soft() const
{
 return soft;
}








