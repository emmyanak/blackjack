#include "Card.h"
#include "Hand.h"
#include "Player.h"
#include "Deck.h"
#include "rand.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>

using namespace std;

int main(int argc, char* argv[]) 

{

int bankroll = atoi(argv[1]);
int hands = atoi(argv[2]);
int current_hand = 1; 
int cut; 
int wager; 
Deck deck;
Hand player_hand;
Hand dealer_hand; 
Player * player = player_factory(argv[3]);
Card card;

cout << "Shuffling the deck\n";
for (int i = 0; i < 7; i++) //shuffle deck 7 times 
   {
      cut = get_cut(); 
      deck.shuffle(cut); 
      player->shuffled(); 
      cout << "cut at " << cut << endl; 
   }

while (bankroll >= 5 && current_hand <= hands)
{

cout << "Hand " << current_hand << " bankroll " << bankroll << endl; 

if (deck.cards_remaining() < 20) //if there are less than 20 cards, reshuffle 
   {
      cout << "Shuffling the deck\n";
      for (int i = 0; i < 7; i++) //shuffle deck 7 times 
         {
            cut = get_cut(); 
            deck.shuffle(cut); 
            player->shuffled(); 
            cout << "cut at " << cut << endl; 
         }
   } 

wager = player->bet(bankroll, 5); 
cout << "Player bets " << wager << endl; 

//deal a card to player
Card card_deal = deck.deal(); 
player_hand.add_card(card_deal);
player->expose(card_deal);
 
cout << "Player dealt " << card_deal << endl; 

//deal to the dealer
Card face_up = deck.deal();
dealer_hand.add_card(face_up);
player->expose(face_up);

cout << "Dealer dealt " << face_up << endl; 

//deal again to the player
card_deal = deck.deal();
player_hand.add_card(card_deal);
player->expose(card_deal);

cout << "Player dealt " << card_deal << endl; 

//deal to the dealer, facedown
Card face_down = deck.deal();
dealer_hand.add_card(face_down);

//cout << "Dealer dealt " << face_down << endl; 

if (player_hand.hand_value() == 21) //player deat natural 21
   {
      bankroll = bankroll + (3*wager)/2;
      cout << "Player dealt natural 21\n";
   }
else //player not dealt natural 21 
   {
      while (player->draw(face_up, player_hand))
      {
         card_deal = deck.deal();
         player_hand.add_card(card_deal); 
         player->expose(card_deal); 
         cout << "Player dealt " << card_deal << endl; 
      } //end of while player does not bust 
      
      cout << "Player's total is " << player_hand.hand_value() << endl; 
      if (player_hand.hand_value() > 21) //player busts 
         {
            cout << "Player busts\n";
            bankroll = bankroll - wager; 
         }
      else //player does not bust
         {
         cout << "Dealer's hole card is " << face_down << endl;
         player->expose(face_down);
         while (dealer_hand.hand_value() < 17)
            {
               face_up = deck.deal(); 
               dealer_hand.add_card(face_up);
               player->expose(face_up); 
               cout << "Dealer dealt " << face_up << endl; 
            }
         cout << "Dealer's total is " << dealer_hand.hand_value() << endl; 
         if (dealer_hand.hand_value() > 21) //if dealer busts 
            {
               cout << "Dealer busts\n";
               bankroll = bankroll + wager;
            } 
         else //dealer does not bust, compare hand values 
            {
               if (dealer_hand.hand_value() > player_hand.hand_value()) //dealer wins, subtract from bankroll 
                  {
 		     cout << "Dealer wins\n";
                     bankroll = bankroll - wager; 
                  }
               else if (dealer_hand.hand_value() < player_hand.hand_value()) //player wins, add to bankroll
                  {
 		     cout << "Player wins\n";
                     bankroll = bankroll + wager; 
                  }
               else //push, do not modify bankroll 
                  {
                     cout << "Push\n";
                  }
            }
         }//end of else 
    } 
current_hand++; //increment hand 
player_hand.discard_all();
dealer_hand.discard_all();

}//end of while 

cout << "Player has " << bankroll << " after " << current_hand - 1 << " hands\n";

} //end of main 
