#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

class SimplePlayer: public Player {

   public:

   SimplePlayer() {} //initialize simple player

  // REQUIRES: bankroll >= minimum
  //           bankroll >= 0
  //           minimum >= 0
  // EFFECTS: returns the player's bet, between minimum and bankroll
  // inclusive
   virtual int bet(int bankroll, int minimum)
   {
    return minimum;
   }

   // EFFECTS: returns true if the player wishes to be dealt another
   // card, false otherwise.
   virtual bool draw(Card dealer, const Hand &player)
   {
      if (!player.hand_is_soft())
      {
         //cout << "player's hand is not soft" << endl; 
         if (player.hand_value() <= 11) return true; //players hand is less than or equal to 11
         else if (player.hand_value() == 12) //player's hand is 12
         {    
           // cout << "Player hand vaue is 12" << endl; 
            if (dealer.get_rank() == 2 || dealer.get_rank() == 3 || dealer.get_rank() == 4) 
               return false;
            else 
               return true;
         }
         else if (player.hand_value() >= 13 && player.hand_value() <=16) //player's hand is between 13 and 16
         {
        // cout << "player hand value is bettween 13 and 16" << endl; 
         
            if (dealer.get_rank() >= 0 && dealer.get_rank() <= 4)
               return false;
            else 
               return true; 
         }
         else    //player's hand is 17 or over  
            return false; 
      }
      else //player's hand is soft
      {
      //cout << "player's hand is soft" << endl; 
         if (player.hand_value() <= 17) 
	    return true;
	 else if (player.hand_value() == 18)
	 {
            if (dealer.get_rank() == 0 || dealer.get_rank() == 5 || dealer.get_rank() == 6)
	       return false;
	    else
	       return true;
         }
         else //player's hand is 19 or over
            return false;
      }

   } //end of function 


  // EFFECTS: allows the player to "see" the newly-exposed card c.
  // For example, each card that is dealt "face up" is expose()d.
  // Likewise, if the dealer must show his "hole card", it is also
  // expose()d.  Note: not all cards dealt are expose()d---if the
  // player goes over 21 or is dealt a natural 21, the dealer need
  // not expose his hole card.
   virtual void expose(Card c)
   { 
   return;
   }
     
  // EFFECTS: tells the player that the deck has been re-shuffled.  
   virtual void shuffled() 
  {
   return; 
  }
};//end of simple player

class CountingPlayer: public SimplePlayer {

   public:

   CountingPlayer(): count(0) {} //initialize counting player with a count of zero 

  // EFFECTS: returns the player's bet, between minimum and bankroll
  // inclusive
   virtual int bet(int bankroll, int minimum)
   {
     if (count >= 2)
     {
        if (bankroll >= 2*minimum)
        { 
           return 2*minimum;  
        }
        else 
        {
          return bankroll; 
        }
     }
     else return minimum; 

   } //end of bet function 


   //no difference in play 

  // EFFECTS: allows the player to "see" the newly-exposed card c.
  // For example, each card that is dealt "face up" is expose()d.
  // Likewise, if the dealer must show his "hole card", it is also
  // expose()d.  Note: not all cards dealt are expose()d---if the
  // player goes over 21 or is dealt a natural 21, the dealer need
  // not expose his hole card.
   virtual void expose(Card c)
   { 
      if (c.get_rank() >= 0 && c.get_rank() <= 4) //cards with rank 2 to 6 
      {
         count = count + 1; 
      }
     else if (c.get_rank() >= 8 && c.get_rank() <= 12) //cards with rank 10 to Ace;  
      {
          count = count - 1; 
      }
      //else no change to count 
   }
      
  virtual void shuffled() 
  {
    count = 0; //count goes back to zero after shuffling 
  }

private:
int count; 

};//end of counting player 

class CompetitorPlayer: public SimplePlayer {

   public:

   CompetitorPlayer(): double_bet(false) {} //initialize counting player with a count of zero 

   //EFFECT: returns the player's bet, between minimum and bankroll inclusive,  according to whether double_bet
   //is true or false 
   virtual int bet(int bankroll, int minimum)
   {
     if (double_bet)
     {
        if (bankroll >= 2*minimum)
        {
           return 2*minimum;                
        }
        else 
        {
          return bankroll; 
        }
     }
     else return minimum; 
   }//end of bet

    //MODIFIES: double_bet
    //EFFECTS: returns true if player wishes to be dealt another card, false otherwise. 
    virtual bool draw(Card dealer, const Hand &player) //FOR COMPETITOR
   {
      if (!player.hand_is_soft())
      {
         if (player.hand_value() == 8)
	 {
	    if (dealer.get_rank() >= 3 && dealer.get_rank() <= 4)
	    {
	       double_bet = true; 
            }
	    return true; 
 	 } 
         else if (player.hand_value() == 9)
	 {
	    if (dealer.get_rank() >= 0 && dealer.get_rank() <= 4)
	    {
	       double_bet = true; 
            }
	    return true; 
 	 } 
	 else if (player.hand_value() == 10)
	 {
	    if (dealer.get_rank() >= 0 && dealer.get_rank() <= 7)
	    {
	       double_bet = true; 
            }
	    return true; 
 	 } 	 
         else if (player.hand_value() == 11)
	 {
	    double_bet = true; 
	    return true; 
 	 } 	 
         else if (player.hand_value() == 12) //player's hand is 12
         {    
           // cout << "Player hand vaue is 12" << endl; 
            if (dealer.get_rank() == 2 || dealer.get_rank() == 3 || dealer.get_rank() == 4) 
               return false;
            else 
               return true;
         }
         else if (player.hand_value() >= 13 && player.hand_value() <=16) //player's hand is between 13 and 16
         {
        // cout << "player hand value is bettween 13 and 16" << endl; 
         
            if (dealer.get_rank() >= 0 && dealer.get_rank() <= 4)
               return false;
            else 
               return true; 
         }
         else    //player's hand is 17 or over  
            return false; 
      }
      else //player's hand is soft
      {
      //cout << "player's hand is soft" << endl; 
         if (player.hand_value() >= 13 && player.hand_value() <=16) //player's hand is between 13 and 16
         {
            if (dealer.get_rank() >= 2 && dealer.get_rank() <= 4)
            {
               double_bet = true;
            }
            return true;               
         }
	 else if (player.hand_value() == 18)
	 {
            if (dealer.get_rank() == 0 || dealer.get_rank() == 5 || dealer.get_rank() == 6 || dealer.get_rank() == 12)
	       return false;
	    else
               {
	          if (dealer.get_rank() >= 1 && dealer.get_rank() <= 4)
                  {
		    double_bet = true;
                  }
                  return true;
               }
         }
         else if (player.hand_value() == 19) //player's hand is 19 or over
         {
	     if (dealer.get_rank() == 4) //dealer has a 6
             {
                double_bet = true;
                return true;     
             }
             return false; 
         }
         else return false; 
      }

   } //end of function 

private:
bool double_bet; 

};//end of competitive player 

static SimplePlayer simple_player; 
static CountingPlayer counting_player; 
static CompetitorPlayer competitor_player; 


// REQUIRES: s is a C-string: "simple" "counting" or "competitor"
// EFFECTS: returns a pointer to the specified Player
Player* player_factory(const char *s) {

   if (strcmp(s,"simple") == 0)
   {
      return &simple_player; 
   }
   else if (strcmp(s, "counting") == 0) 
   {
      return &counting_player; 
   }
   else if (strcmp(s,"competitor") == 0)
   {
      return &competitor_player; 
   }
   else 
   {
      cout << "INVALID INPUT" << endl; 
      return NULL; 
   }

}


   
   





































