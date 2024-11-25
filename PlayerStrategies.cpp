#include "PlayerStrategies.h"

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
void AggressivePlayerStrategy::issueOrder(Order* order) {

    if (Deploy *d = dynamic_cast<Deploy *>(order))
    {
        vector<Territory*> t = toDefend();

        cout << "\nDeploy Order issued for : " << this->getPlayer()->getPlayerName() << " with " << this->getPlayer()->getReinforcementTemp() << " armies in the reinforcement pool !" << endl;
        //int min = 0;
        int max = this->getPlayer()->getReinforcementTemp();

        // deploy random number of army units to a random territory to defend

        Deploy *dep = new Deploy(this->getPlayer()->getObserver(), this->getPlayer(), max, t.at(t.size()-1));

        this->getPlayer()->getOrderList()->addOrder(dep);


    }else if(Advance *d = dynamic_cast<Advance *>(order)){

        vector<Territory*> list = toDefend();

        Territory* strongest = list.at(list.size()-1);

        bool allFriendly = true;

        for(Territory* t : strongest->getAdjTerritories()){

            if(t->getPlayer() != this->getPlayer()){

                allFriendly = false;
                break;
            }
        }

        if(allFriendly){

            Order* ad = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), strongest->getNumArmies()/2,strongest, strongest->getAdjTerritories()[0]);

            this->getPlayer()->getOrderList()->addOrder(ad);

        }else{

            for(Territory* t: strongest->getAdjTerritories()){

                if(t->getPlayer() != this->getPlayer()){

                    Order* ad = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), strongest->getNumArmies()/1.5,strongest, t);
                    this->getPlayer()->getOrderList()->addOrder(ad);

                }

            }

        }

    }else if(Blockade *d = dynamic_cast<Blockade *>(order)){

        Territory* t = toDefend().at(0);

        Blockade* b = new Blockade(this->getPlayer()->getObserver(), this->getPlayer(), t);

        this->getPlayer()->getOrderList()->addOrder(b);

    }else if(Airlift *d = dynamic_cast<Airlift *>(order)){

        vector<Territory*> list = toDefend();

        Airlift* airlift = new Airlift(this->getPlayer()->getObserver(), this->getPlayer(),list.at(list.size()-1)->getNumArmies()/4, list.at(list.size()-1), list.at(0));

        this->getPlayer()->getOrderList()->addOrder(airlift);

    }else if(Negotiate *d = dynamic_cast<Negotiate *>(order)){

        for(Player* p : getPlayerList()){

            if(p != this->getPlayer()){

                Negotiate* n = new Negotiate(this->getPlayer()->getObserver(), this->getPlayer(),p);
                this->getPlayer()->getOrderList()->addOrder(n);
                break;
            }
        }

    }else if(Bomb *d = dynamic_cast<Bomb *>(order)){

        for(Territory* t : this->getPlayer()->getTerritories()){

             for(Territory* t2 : t->getAdjTerritories()){

                if(t2->getPlayer() != this->getPlayer()){

                    Bomb* bomb = new Bomb(this->getPlayer()->getObserver(), this->getPlayer(), t2);

                    this->getPlayer()->getOrderList()->addOrder(bomb);
                }
             }
        }
    }

}

vector<Territory*> AggressivePlayerStrategy::toAttack() {
    cout << "Aggressive Player Strategy: toAttack" << endl;

    return this->getPlayer()->getTerritories();
}

vector<Territory*> AggressivePlayerStrategy::toDefend() {
    
    vector<Territory*> t_list = this->getPlayer()->getTerritories();

    std::sort(t_list.begin(), t_list.end(), compareArmies);

    return t_list;

}






// BENEVOLENT PLAYER STRATEGY
void BenevolentPlayerStrategy::issueOrder(Order* order) {

    if (Deploy *d = dynamic_cast<Deploy *>(order))
    {
        vector<Territory*> t = toDefend();

        cout << "\nDeploy Order issued for : " << this->getPlayer()->getPlayerName() << " with " << this->getPlayer()->getReinforcementTemp() << " armies in the reinforcement pool !" << endl;
        //int min = 0;
        int max = this->getPlayer()->getReinforcementTemp();

        // deploy random number of army units to a random territory to defend


            Deploy *dep = new Deploy(this->getPlayer()->getObserver(), this->getPlayer(), max, t.at(0));
            //this->getPlayer()->getOrderList()->addOrder(dep);

            //this->getPlayer()->setReinforcementPool(this->getPlayer()->getReinforcementPool()-max/t.size());


            /*cout << "Deploy to: " << t.at(i)->getName() << " with " << max/t.size() << " armies\n"
             << this->getPlayer()->getReinforcementPool() << " armies left in reinforcement pool" << endl;*/

            this->getPlayer()->getOrderList()->addOrder(dep);
        

        // add order to order list
        
        return;

    }else if(Advance *d = dynamic_cast<Advance *>(order)){

        vector<Territory*> low = toDefend();

        Territory* target = low.at(0);

        vector<Territory*> adjT;

        for(Territory* t : target->getAdjTerritories()){

            if(t->getPlayer() == this->getPlayer()){

                adjT.push_back(t);
            }
        }

        std::sort(adjT.begin(), adjT.end(), compareArmies);

        Territory* source = adjT.at(adjT.size()-1);

        Advance* ad = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), source->getNumArmies()/2,source, target);

        this->getPlayer()->getOrderList()->addOrder(ad);

    }else if(Blockade *d = dynamic_cast<Blockade *>(order)){

        Territory* t = toDefend().at(0);

        Blockade* b = new Blockade(this->getPlayer()->getObserver(), this->getPlayer(), t);

        this->getPlayer()->getOrderList()->addOrder(b);

    }else if(Airlift *d = dynamic_cast<Airlift *>(order)){

        vector<Territory*> list = toDefend();

        Airlift* airlift = new Airlift(this->getPlayer()->getObserver(), this->getPlayer(),list.at(list.size()-1)->getNumArmies()/4, list.at(list.size()-1), list.at(0));

        this->getPlayer()->getOrderList()->addOrder(airlift);

    }else if(Negotiate *d = dynamic_cast<Negotiate *>(order)){

        for(Player* p : getPlayerList()){

            if(p != this->getPlayer()){

                Negotiate* n = new Negotiate(this->getPlayer()->getObserver(), this->getPlayer(),p);
                this->getPlayer()->getOrderList()->addOrder(n);
                break;
            }
        }

    }else{
        return;
    }
    




}

vector<Territory*> BenevolentPlayerStrategy::toAttack() {
    cout << "Benevolent Player Strategy: toAttack" << endl;
}

vector<Territory*> BenevolentPlayerStrategy::toDefend() {
    
    vector<Territory*> t_list = this->getPlayer()->getTerritories();

    std::sort(t_list.begin(), t_list.end(), compareArmies);

    int nb = t_list.size();

    if(t_list.size()<4) nb*0.25;

    vector<Territory*> new_t;

    for(int i = 0; i < nb; i++){

        new_t.push_back(t_list.at(i));
        //t_list.at(i)->setNumArmies(t_list.at(i)->getNumArmies()+this->getPlayer()->getReinforcementPool()/nb);

    }

    return new_t;

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
