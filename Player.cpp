/**
 * PLAYER CLASS FEATURES:
 * 1. Player owns collection of Territory objects
 * 2. Player owns a hand of Card objects
 * 3. Player contains methods toDefend(), toAttack() returning abitrary lists of territories to defend/attack
 * 4. Player contains issueOrder() method to creates and Order object and adds it to the list
 * 5. Driver names testPlayers() method to test the Player class
 */

#include "Player.h"
using namespace std;

Player::Player(Observer *o, string playerName)
{
    this->playerName = playerName;
    orders = new OrdersList(o);
    canDrawCard = true;
    reinforcementPool = 50;

    // temp value of the reinforcement pool for the issuing order phase
    hand = new Hand();
    territories = vector<Territory *>();
    // this is so that the values of the reinforcement pool can be manipulated/modfied without the actual execution of it (issue order phase)
    reinforcementTemp = 50;
    observer = o;

    // Initialize strategy to a default strategy
    strategy = new Human();
}

Player::Player(const Player &orig)
{

    // copy every territory from the original player to the new player
    for (Territory *territories : orig.territories)
    {
        this->territories.push_back(territories);
    }

    // copy every card from the original player to the new player
    hand = new Hand(*orig.hand);

    // copy every order from the original player to the new player
    orders = new OrdersList(*orig.orders);

    reinforcementPool = orig.reinforcementPool;
    reinforcementTemp = orig.reinforcementTemp;
}

// Player destructor
Player::~Player()
{
    // for (Order* order: orders->getOrders()){
    //     delete order;
    // }
    delete orders; // TODO: check if i need to delete the orders in the list first

    for (Territory *territory : territories)
    {
        delete territory;
    }
    // TODO: check if i need to delete the cards in the hand first
}

void Player::setReinforcementPool(int armies)
{
    reinforcementPool = armies;
    reinforcementTemp = armies;
}
void Player::setReinforcementTemp(int armies)
{
    reinforcementTemp = armies;
}
int Player::getReinforcementPool()
{
    return reinforcementPool;
}

int Player::getReinforcementTemp()
{
    return reinforcementTemp;
}

Hand *Player::getHand()
{
    return hand;
}

OrdersList *Player::getOrderList()
{
    return orders;
}

Observer *Player::getObserver() { return observer; }

// adds order to the player's list of orders
void Player::issueOrder(Order *order)
{
    strategy->issueOrder(order); //here issue

}

// adds territory to the player's list of territories
void Player::addTerritory(Territory *territory)
{
    territories.push_back(territory);
}

vector<Territory *> Player::getTerritories() { return territories; } // iossue here

// returns list of territories to defend based on priority
vector<Territory *> Player::toDefend()
{

    return this->getPlayerStrategy()->toDefend();

 
}

// returns list of territories to attack based on priority
vector<Territory *> Player::toAttack()
{
    if (!strategy) {
        std::cerr << "Error: PlayerStrategy is null!" << std::endl;
        return {};
    }
    
    return strategy->toAttack();

}

// stream insertion operator to print player's information
ostream &operator<<(ostream &out, const Player &player)
{
    out << "Player name: " << player.playerName << endl;
    out << "Territories owned: " << player.territories.size() << endl;
    for (Territory *territory : player.territories)
    {
        out << "\t" << territory->getName() << endl;
    }
    return out;
}

Player &Player::operator=(const Player &o)
{
    this->playerName = o.playerName;
    this->territories = o.territories;
    this->hand = o.hand;
    this->orders = o.orders;
    this->canDrawCard = o.canDrawCard;
    this->reinforcementPool = o.reinforcementPool;
    this->reinforcementTemp = o.reinforcementTemp;
    this->observer = o.observer;

    return *this;
}

std::string Player::getPlayerName()
{
    return playerName;
}

// adds card to player's Hand
void Player::addCard(Card *card)
{
    hand->addCard(card);
}

// removes territory from player's list of territories
void Player::removeTerritory(Territory *territory)
{
    for (int i = 0; i < territories.size(); i++)
    {
        if (territories[i] == territory)
        {
            territories.erase(territories.begin() + i);
            break;
        }
    }
}

// attach observer to player's order list
void Player::AttachObserver(Observer *observer)
{
    orders->Attach(observer);
}

void Player::drewCard() { canDrawCard = false; }
void Player::roundReset()
{
    canDrawCard = true;

    if (this->getPlayerStrategy()->getPlayerType().compare("Cheater") == 0)
    {

        Cheater *c = dynamic_cast<Cheater *>(this->getPlayerStrategy());

        c->resetCheaterConquer();
    }
}
bool Player::getCanDrawCard() { return canDrawCard; }

PlayerStrategy *Player::getPlayerStrategy() { return strategy; }
void Player::setPlayerStrategy(PlayerStrategy *s) { strategy = s; }

void Player::assignStrategies(std::vector<Player *>& players) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 4); // Five strategies: 0-4

    Benevolent *b = new Benevolent();
    Cheater *c = new Cheater();
    Aggressive *a = new Aggressive();
    Neutral *n = new Neutral();
    Human *h = new Human();
    

    for (Player* player : players) {
        int strategyType = dist(gen);

        switch (strategyType) {
            case 0:
                h->setPlayer(player);
                player->setPlayerStrategy(h);
                break;
            case 1:
                a->setPlayer(player);
                player->setPlayerStrategy(a);
                break;
            case 2:
                b->setPlayer(player);
                player->setPlayerStrategy(b);
                break;
            case 3:
                n->setPlayer(player);
                player->setPlayerStrategy(n);
                break;
            case 4:
                c->setPlayer(player);
                player->setPlayerStrategy(c);
                break;
        }

        std::cout << "Assigned strategy: " 
                  << player->getPlayerStrategy()->getPlayerType() 
                  << " to player." << std::endl;
    }
};
