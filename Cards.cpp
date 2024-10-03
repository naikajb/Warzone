
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "Cards.h"

using namespace std;

//Card class constructor
Card::Card(CardType type) {
    this->type = new CardType(type);
}
//Card destructor
Card::~Card() {
    delete type;
}

//Card copy constructor
Card::Card(const Card& other) {
    this->type = new CardType(*other.type);
}

//Returns the type of the card
string Card::getCardType() const{
    if (type == nullptr) {
        return "Invalid card type";
    }
    switch (*type) {
        case BOMB:
            return "Bomb";
        case REINFORCEMENT:
            return "Reinforcement";
        case BLOCKADE:
            return "Blockade";
        case AIRLIFT:
            return "Airlift";
        case DIPLOMACY:
            return "Diplomacy";
        default:
            return "Invalid card type";
    }
}


//Plays the card at the given index in the hand
void Card::play(int index, Hand& hand, Deck& deck) {
     if (index < 0 || index >= hand.cardsInHand.size()) {
        throw std::out_of_range("Index out of range");
    }
    Card cardToPLay = *hand.cardsInHand[index];
    cout << "Playing " << cardToPLay.getCardType() << " card, creating an order." << endl;
    //Return the card to the deck
    deck.returnCardToDeck(&cardToPLay);
    hand.cardsInHand.erase(hand.cardsInHand.begin() + index);
    
}

//Output stream operator
ostream& operator<<(ostream& out, const Card& card) {
    out << card.getCardType();
    return out;
}

//Deck class constructor
Deck::Deck() {
    //Add 5 of each card type to the deck
    for (int i = 0; i < 5; i++) {
        Card* bomb = new Card(Card::BOMB);
        Card* reinforcement = new Card(Card::REINFORCEMENT);
        Card* blockade = new Card(Card::BLOCKADE);
        Card* airlift = new Card(Card::AIRLIFT);
        Card* diplomacy = new Card(Card::DIPLOMACY);

        cardsInDeck.push_back(bomb);
        cardsInDeck.push_back(reinforcement);
        cardsInDeck.push_back(blockade);
        cardsInDeck.push_back(airlift);
        cardsInDeck.push_back(diplomacy);

    }

    random_device rd;
    //Creates a random number generator to allow shuffling of the deck
    default_random_engine rng(rd());

    //Shuffle the deck
    shuffle(cardsInDeck.begin(), cardsInDeck.end(),rng);
}

vector<Card *> Deck::getCardsInDeck(){
    return cardsInDeck;
}

//Deck destructor
Deck::~Deck() {
    for (Card* card : cardsInDeck) {
        delete card;
    }
}

//Deck copy constructor
Deck::Deck(const Deck& other) {
    for (Card* card : other.cardsInDeck) {
        cardsInDeck.push_back(new Card(*card));
    }
}

// Draw the last card (in the deck) and pop it
Card* Deck::draw() {
    //Get the last card in the deck
    Card* drawnCard = cardsInDeck.back();
    //Remove the last card from the deck
    cardsInDeck.pop_back();
    cout << "Drew " << drawnCard->getCardType() << " card." << endl;
    return drawnCard;
}

//Displays the cards in the deck
void Deck::displayDeck() {
    if (cardsInDeck.empty()) {
        cout << "Deck is empty." << endl;
        return;
    }
    else {
        cout << "Deck: ";
        for (Card *card : cardsInDeck) {
            cout << card->getCardType() << " ";
        }
        cout << endl;
    }
}

//Output stream operator
ostream& operator<<(ostream& out, const Deck& deck) {
    out << "Deck: ";
    for (Card* card : deck.cardsInDeck) {
        out << card->getCardType() << " ";
    }
    return out;
}

void Deck::returnCardToDeck(Card* card) {
    Card* newCard = new Card(*card);
    cardsInDeck.push_back(newCard);
}

// Hand Class
void Hand::addCard(Card* card) {
    cardsInHand.push_back(card); //Adds a card to the hand
}


bool Card::operator==(const Card& other) const {
    return this->type == other.type;
}

//Displays the cards in the hand
void Hand::displayHand() {
    if ((cardsInHand).empty()) {
        cout << "Hand is empty." << endl;
        return;
    }
    else {
        cout << "Hand: ";
        for (Card* card : (cardsInHand)) {
            cout << card->getCardType() << " ";
        }
        cout << endl;
    }
}

//Output stream operator
ostream& operator<<(ostream& out, const Hand& hand) {
    out << "Hand: ";
    for (Card* card : hand.cardsInHand) {
        out << card->getCardType() << " ";
    }
    return out;
}

//Hand class constructor
Hand::Hand() {

}
//Hand destructor
Hand::~Hand() {
    for (Card* card : cardsInHand) {
        delete card;
    }
}

//Hand copy constructor
Hand::Hand(const Hand& other) {
    for (Card* card : other.cardsInHand) {
        cardsInHand.push_back(new Card(*card));
    }
}



