#include <iostream>
#include "Cards.h"
#include "CardDriver.h"

void testCards() {
    Deck deck=Deck();
    Hand hand=Hand();

    // Printing deck contents before drawing
    deck.displayDeck();

    // Draw 5 cards from the deck
    for (int i = 0; i < 5; i++) {
        hand.addCard(deck.draw());
    }

    // Printing deck contents after drawing
    deck.displayDeck();

    // Show the current hand
    hand.displayHand();

    //Play the first card in hand (remove from hand and return to deck)
    for (int i=0; i<5; i++) {
        Card* currentCardPtr = hand.cardsInHand[0]; // Get the pointer to the Card
        Card currentCard = *currentCardPtr; // Dereference the pointer to get the Card object
        currentCard.play(0, hand, deck);
    }

    // Show the hand after playing the five cards that were drawn
    hand.displayHand();
    
    deck.displayDeck();

    deck.~Deck();
    hand.~Hand();
}

// int main() {
//     testCards();
//     return 0;
// }
