#include "PlayerStrategies.h"

PlayerStrategy::~PlayerStrategy(){
    delete player;
    player = NULL;
}

Player* PlayerStrategy::getPlayer(){return player;}
void PlayerStrategy::setPlayer(Player* p ){player = p;}

bool PlayerStrategy::contains(vector<Territory*> v, Territory* find){
    for(Territory* t : v){
        if(t==find) return true;
    }
    return false;
}

string PlayerStrategy::getPlayerType(){return "";}


void PlayerStrategy::becomeAggressive(){

    cout << this->getPlayer()->getPlayerName() << " will become an Aggressive Player!" << endl;

    Aggressive* angyBoi = new Aggressive();

    angyBoi->setPlayer(this->getPlayer());

    angyBoi->getPlayer()->setPlayerStrategy(angyBoi);

    for(Territory* t : angyBoi->getPlayer()->getTerritories()){
        t->setPlayer(angyBoi->getPlayer());
    }
    
    removePlayerFromList(this->getPlayer());

    addToPlayerList(angyBoi->getPlayer());
}


void checkNeutralAttack(Territory* t){

    Neutral* temp = new Neutral();

    if(t->getPlayer()->getPlayerStrategy()->getPlayerType() == "Neutral"){

        cout << "Someone has Attacked a Neutral Player!" << endl;

        t->getPlayer()->getPlayerStrategy()->becomeAggressive();

    }

    delete temp;
    temp = NULL;

}

// HUMAN PLAYER STRATEGY

string Human::getPlayerType(){return "Human";}

void Human::issueOrder(Order*) {

    cout << "Which Order would you like to play?:\n1. Deploy\n2. Advance\n3. Airlift\n4. Bomb\n5. Blockade\n6. Negotiate" << endl;
    cout << "Selected an Order:";

    int selectedOrder;

    cin >> selectedOrder;

    vector<Territory*> possibleBomboclat;

        if(selectedOrder == 1){

            int armies;
            int selectedT;

            cout << "To which Territory would you like to Deploy the armies:" << endl;

            int counter = 1;

            for(Territory* t : this->toDefend()){

                cout << counter << ". " << t->getName() << endl;
                counter++;

            }

            cin >> selectedT;

            Territory* t = this->getPlayer()->getTerritories()[selectedT-1];

            cout << "How many armies would you like to deploy: " << endl;

            cin >> armies;

            Order* d = new Deploy(this->getPlayer()->getObserver(),this->getPlayer(),armies,t);

            this->getPlayer()->getOrderList()->addOrder(d);

        }else if(selectedOrder == 2){

            int armies;
            int selectedSource;
            int selectedTarget;

            cout << "From which Territory would you like to Advance the armies:" << endl;

            int counter = 1;

            for(Territory* t : this->getPlayer()->getTerritories()){

                cout << counter << ". " << t->getName() << endl;
                counter++;

            }

            counter = 1;
            cin >> selectedSource;

            cout << "To which Territory would you like to Advance the armies:" << endl;

            for(Territory* t : this->getPlayer()->getTerritories()[selectedSource-1]->getAdjTerritories()){

                cout << counter << ". " << t->getName() << endl;
                counter++;

            }

            cin >> selectedTarget;

            Territory* source = this->getPlayer()->getTerritories()[selectedSource-1];
            Territory* target = this->getPlayer()->getTerritories()[selectedSource-1]->getAdjTerritories()[selectedTarget-1];

            cout << "How many armies would you like to deploy: " << endl;

            cin >> armies;

            Order* a = new Advance(this->getPlayer()->getObserver(),this->getPlayer(),armies,source,target);

            this->getPlayer()->getOrderList()->addOrder(a);


        }else if(selectedOrder == 3){

            int armies;
            int selectedSource;
            int selectedTarget;

            cout << "From which Territory would you like to Airlift the armies:" << endl;

            int counter = 1;

            for(Territory* t : this->getPlayer()->getTerritories()){

                cout << counter << ". " << t->getName() << endl;
                counter++;

            }

            cin >> selectedSource;

            counter = 1;

            cout << "To which Territory would you like to Airlift the armies:" << endl;

            for(Territory* t : this->getPlayer()->getTerritories()){

                cout << counter << ". " << t->getName() << endl;
                counter++;

            }

            cin >> selectedTarget;

            cout << "How many armies would you like to airlift: " << endl;

            cin >> armies;

            Territory* source = this->getPlayer()->getTerritories()[selectedSource-1];

            Territory* target = this->getPlayer()->getTerritories()[selectedTarget-1];

            Order* a = new Airlift(this->getPlayer()->getObserver(),this->getPlayer(),armies,source,target);

            this->getPlayer()->getOrderList()->addOrder(a);

        }else if(selectedOrder == 4){

            cout << "Which Territory would you like to Bomb?: " << endl;

            int counter = 1;

            int selectedTarget;

            for(Territory* t : this->getPlayer()->getTerritories()){

                for(Territory* t2 : t->getAdjTerritories()){

                    if(t2->getPlayer()== this->getPlayer()){
                        continue;
                    }

                    possibleBomboclat.push_back(t2);

                    cout << counter << ". " << t2->getName() << endl;

                    counter++;
                }
            }

            cin >> selectedTarget;

            Order* a = new Bomb(this->getPlayer()->getObserver(),this->getPlayer(),possibleBomboclat.at(selectedTarget-1));

            this->getPlayer()->getOrderList()->addOrder(a);


        }else if(selectedOrder == 5){

            cout << "Which Territory would you like to Blockade?:" << endl;

            int selectedTarget;

            int counter = 1;

            for(Territory* t : this->getPlayer()->getTerritories()){

                cout << counter << ". " << t->getName() << endl;
                counter++;

            }

            cin >> selectedTarget;

            Order* a = new Blockade(this->getPlayer()->getObserver(),this->getPlayer(),this->getPlayer()->getTerritories()[selectedTarget-1]);

            this->getPlayer()->getOrderList()->addOrder(a);

        }else if(selectedOrder == 6){

            cout << "Which Player would you like to Negotiate with?:" << endl;

            int selectedTarget;

            int counter = 1;

            for(Player* p : getPlayerList()){

                cout << counter << ". " << p->getPlayerName() << endl;
                counter++;

            }

            cin >> selectedTarget;

            Order* a = new Negotiate(this->getPlayer()->getObserver(),this->getPlayer(),getPlayerList()[selectedTarget-1]);

            this->getPlayer()->getOrderList()->addOrder(a);

        }
}

vector<Territory*> Human::toAttack() {
     
    vector<Territory*> potentialAttack;

    bool alreadyContained = false;

    for(Territory* t : this->getPlayer()->getTerritories()){

        for(Territory* t2 : t->getAdjTerritories()){

            if(t2->getPlayer()!=this->getPlayer()){

                if(!this->contains(potentialAttack,t2)){

                    potentialAttack.push_back(t2);
                }
            }
        }
    }
    return potentialAttack;
}



vector<Territory*> Human::toDefend() {

    return this->getPlayer()->getTerritories();
    
}

// AGGRESSIVE PLAYER STRATEGY

string Aggressive::getPlayerType(){return "Aggressive";}

void Aggressive::issueOrder(Order* order) {

    if (Deploy *d = dynamic_cast<Deploy *>(order))
    {
        vector<Territory*> t = this->toDefend();

        cout << "\nDeploy Order issued for : " << this->getPlayer()->getPlayerName() << " with " << this->getPlayer()->getReinforcementTemp() << " armies in the reinforcement pool !" << endl;
        //int min = 0;
        int max = this->getPlayer()->getReinforcementTemp();

        // deploy random number of army units to a random territory to defend

        Order *dep = new Deploy(this->getPlayer()->getObserver(), this->getPlayer(), max, t.at(t.size()-1));

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
                    break;

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

                Order* n = new Negotiate(this->getPlayer()->getObserver(), this->getPlayer(),p);
                this->getPlayer()->getOrderList()->addOrder(n);
                break;
            }
        }

    }else if(Bomb *d = dynamic_cast<Bomb *>(order)){

        for(Territory* t : this->getPlayer()->getTerritories()){

             for(Territory* t2 : t->getAdjTerritories()){

                if(t2->getPlayer() != this->getPlayer()){

                    Order* bomb = new Bomb(this->getPlayer()->getObserver(), this->getPlayer(), t2);

                    this->getPlayer()->getOrderList()->addOrder(bomb);
                }
             }
        }
    }

}

vector<Territory*> Aggressive::toAttack() {

    vector<Territory*> potentialAttack;

    bool alreadyContained = false;

    for(Territory* t : this->getPlayer()->getTerritories()){

        for(Territory* t2 : t->getAdjTerritories()){

            if(t2->getPlayer()!=this->getPlayer()){

                if(!this->contains(potentialAttack,t2)){

                    potentialAttack.push_back(t2);
                }
            }
        }
    }
    return potentialAttack;
}

vector<Territory*> Aggressive::toDefend() {
    
    vector<Territory*> t_list = this->getPlayer()->getTerritories();

    std::sort(t_list.begin(), t_list.end(), compareArmies);

    return t_list;

}

// BENEVOLENT PLAYER STRATEGY

string Benevolent::getPlayerType(){return "Benevolent";}

void Benevolent::issueOrder(Order* order) {

    if (Deploy *d = dynamic_cast<Deploy *>(order))
    {
        vector<Territory*> t = toDefend();

        cout << "\nDeploy Order issued for : " << this->getPlayer()->getPlayerName() << " with " << this->getPlayer()->getReinforcementTemp() << " armies in the reinforcement pool !" << endl;
        //int min = 0;
        int max = this->getPlayer()->getReinforcementTemp();

        // deploy random number of army units to a random territory to defend

            Order *dep = new Deploy(this->getPlayer()->getObserver(), this->getPlayer(), max, t.at(0));

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

vector<Territory*> Benevolent::toAttack() {

    cout << "Benevolent Player doesn't Attack." << endl;
    
    vector<Territory*> x;

    return x;
}

vector<Territory*> Benevolent::toDefend() {
    
    vector<Territory*> t_list = this->getPlayer()->getTerritories();

    std::sort(t_list.begin(), t_list.end(), compareArmies);

    return t_list;

}

bool compareArmies(Territory* a, Territory* b) {
    return a->getNumArmies() < b->getNumArmies();
}

string Neutral::getPlayerType(){return "Neutral";}

// NEUTRAL PLAYER STRATEGY

void Neutral::issueOrder(Order*) {
    cout << "Neutral Player doesn't issue orders." << endl;
}

vector<Territory*> Neutral::toAttack() {

    cout << "Neutral Player doesn't Attack." << endl;
    
    vector<Territory*> x;

    return x;

}

vector<Territory*> Neutral::toDefend() {

    cout << "Neutral Player doesn't defend" << endl;

    vector<Territory*> x;

    return x;
    
}



// CHEATER PLAYER STRATEGY

string Cheater::getPlayerType(){return "Cheater";}

void Cheater::issueOrder(Order*) {
    
    Order* placeholder = new Advance(this->getPlayer()->getObserver(),this->getPlayer(),-99,this->getPlayer()->getTerritories()[0],this->getPlayer()->getTerritories()[0]);

    this->getPlayer()->getOrderList()->addOrder(placeholder);

}

vector<Territory*> Cheater::toAttack() {

    vector<Territory*> potentialAttack;

    bool alreadyContained = false;

    for(Territory* t : this->getPlayer()->getTerritories()){

        for(Territory* t2 : t->getAdjTerritories()){

            if(t2->getPlayer()!=this->getPlayer()){

                if(!this->contains(potentialAttack,t2)){

                    potentialAttack.push_back(t2);
                }
            }
        }
    }

    if(this->cheaterCanConquer()){

        for(Territory* t: potentialAttack){

            cout << "Cheater is conquering Territory " << t->getName() << endl;

            t->getPlayer()->removeTerritory(t);
            t->setPlayer(this->getPlayer());
            this->getPlayer()->addTerritory(t);
        }

        this->isConquering();

    }else{

        cout << "Cheater has already conquered this round!" << endl;

    }

    return potentialAttack;
}

vector<Territory*> Cheater::toDefend() {

    return this->getPlayer()->getTerritories();

}

bool Cheater::cheaterCanConquer(){
    return canConquer;
}

void Cheater::isConquering(){
    canConquer = false;
}

void Cheater::resetCheaterConquer(){
    canConquer = true;
}

void PlayerStrategy::assignPlayer(Player* p){
    player = p;
}
// PLAYER STRATEGY
