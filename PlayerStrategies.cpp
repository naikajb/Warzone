#include "PlayerStrategies.h"
#include "Map.h"

// HUMAN PLAYER STRATEGY

Player* PlayerStrategy::getPlayer(){return player;}
void PlayerStrategy::setPlayer(Player* p ){player = p;}


void HumanPlayerStrategy::issueOrder(Order*) {
    cout << "Human Player Strategy: issueOrder" << endl;
}

vector<Territory*> HumanPlayerStrategy::toAttack() {
    cout << "Human Player Strategy: toAttack" << endl;
}

vector<Territory*> HumanPlayerStrategy::toDefend() {
    cout << "Human Player Strategy: toDefend" << endl;
}

// AGGRESSIVE PLAYER STRATEGY
void AggressivePlayerStrategy::issueOrder(Order*) {
    cout << "Aggressive Player Strategy: issueOrder" << endl;
}

vector<Territory*> AggressivePlayerStrategy::toAttack() {
    cout << "Aggressive Player Strategy: toAttack" << endl;


}

vector<Territory*> AggressivePlayerStrategy::toDefend() {
    cout << "Aggressive Player Strategy: toDefend" << endl;
}






// BENEVOLENT PLAYER STRATEGY
void BenevolentPlayerStrategy::issueOrder(Order* order) {
    
     std::random_device rd;
    // generator seeded by rd for random numbers
        std::mt19937 gen(rd());


        Territory *selectedTerritoryToDefend = toDefend()[randomIndexDefend];

    if (Deploy *d = dynamic_cast<Deploy *>(order))
    {
        cout << "\nDeploy Order issued for : " << this->getPlayer()->getPlayerName() << " with " << this->getPlayer()->getReinforcementTemp() << " armies in the reinforcement pool !" << endl;

        // choose a random number of army units to deploy
        // reinforcement temp is used to keep track of the reinforcement pool
        // without actually modifying it until the order execution
        int min = 0;
        int max = this->getPlayer()->getReinforcementTemp();
        std::uniform_int_distribution<> distRandArmiesDeploy(min, max);
        int randomNumArmiesDeploy = distRandArmiesDeploy(gen);

        // deploy random number of army units to a random territory to defend
        Deploy *dep = new Deploy(this->getPlayer()->getObserver(), this, randomNumArmiesDeploy, selectedTerritoryToDefend);

        reinforcementTemp -= randomNumArmiesDeploy;

        cout << "Deploy to: " << selectedTerritoryToDefend->getName() << " with " << randomNumArmiesDeploy << " armies\n"
             << reinforcementTemp << " armies left in reinforcement pool" << endl;
        // add order to order list
        orders->addOrder(dep);
        return;
    }


}

vector<Territory*> BenevolentPlayerStrategy::toAttack() {
    cout << "Benevolent Player Strategy: toAttack" << endl;
}

vector<Territory*> BenevolentPlayerStrategy::toDefend() {
    
    vector<Territory*> t_list = this->getPlayer()->getTerritories();

    std::sort(t_list.begin(), t_list.end(), compareArmies);

    for(Territory* t: t_list){

        cout << t->getName() << endl;

    }

    int nb = t_list.size()*0.25;

    for(int i = 0; i < nb; i++){

        t_list.at(i)->setNumArmies(t_list.at(i)->getNumArmies()+this->getPlayer()->getReinforcementPool()/nb);

    }

    this->getPlayer()->setReinforcementPool(0);

    return t_list;

}

bool compareArmies(Territory* a, Territory* b) {
    return a->getNumArmies() < b->getNumArmies();
}





// NEUTRAL PLAYER STRATEGY

void NeutralPlayerStrategy::issueOrder(Order*) {
    cout << "Neutral Player doesn't issue orders." << endl;

}

vector<Territory*> NeutralPlayerStrategy::toAttack() {
    cout << "A Neutral Player does not attack!" << endl;
    return this->getPlayer()->getTerritories();
}

vector<Territory*> NeutralPlayerStrategy::toDefend() {

    return generalToDefend();
    
}






// CHEATER PLAYER STRATEGY

void CheaterPlayerStrategy::issueOrder(Order*) {
    cout << "Cheater player doesn't issue orders." << endl;
}

vector<Territory*> CheaterPlayerStrategy::toAttack() {
    
    cout << "Cheater toAttack()" << endl;


    vector<Territory*> original = this->getPlayer()->getTerritories();

    for(Territory* t : original){

        for(Territory* adj: t->getAdjTerritories()){

            this->getPlayer()->addTerritory(adj);
        }
    }

    return this->getPlayer()->getTerritories();
}

vector<Territory*> CheaterPlayerStrategy::toDefend() {

    cout << "Cheater toDefend()" << endl; 

    return generalToDefend();

}

void PlayerStrategy::assignPlayer(Player* p){
    player = p;
}

vector<Territory*> PlayerStrategy::generalToDefend(){

    sort(player->getTerritories().begin(), player->getTerritories().end(), [this](Territory *t1, Territory *t2)
         {
        // number of enemy armies for territory 1
        int numArmiesT1 = 0;
        // number of enemy armies for territory 2
        int numArmiesT2 = 0;

        // if both territories have 0 enemy armies
        // priority changes to number of enemy territories OR
        // unowned territories surrounding Territory 1
        int numEnemyAdjT1 = 0;
        // number of enemy territories OR unowned territories
        // surrounding Territory 2
        int numEnemyAdjT2 = 0;

        for (Territory* t : t1->getAdjTerritories()){
            if (t->getPlayer() != player){
                numArmiesT1 += t->getNumArmies(); // add number of enemy armies
                numEnemyAdjT1++; // add adjacent enemy territories
            }
        }

        for (Territory* t : t2->getAdjTerritories()){
            if (t->getPlayer() != player){
                numArmiesT2 += t->getNumArmies(); // add number of enemy armies
                numEnemyAdjT2++; // add adjacent enemy territories
            }
        }    

        if (numArmiesT1 == 0 && numArmiesT2 == 0)
            {   
                // Sort in descending order based on the number of adajcent enemy territories OR 
                // adjacent unnowned territories 
                return numEnemyAdjT1 > numEnemyAdjT2;
            }
        // Sort in descending order based on the number of enemy armies
        return numArmiesT1 > numArmiesT2; });
    return player->getTerritories();

}

void PlayerStrategy::becomeAggressive(){

    AggressivePlayerStrategy* aps = new AggressivePlayerStrategy();

    aps->player = this->player;

    for(Territory* t : aps->getPlayer()->getTerritories()){
        t->setPlayer(aps->player);
    }
    
    removePlayerFromList(this->player);

    addToPlayerList(aps->player);

    // remove previous player
    // add this player to list









}

// PLAYER STRATEGY
