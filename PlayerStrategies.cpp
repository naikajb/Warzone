#include "PlayerStrategies.h"

PlayerStrategy::~PlayerStrategy()
{
    delete player;
    player = NULL;
}

Player *PlayerStrategy::getPlayer() { return player; }
void PlayerStrategy::setPlayer(Player *p) { player = p; }

bool PlayerStrategy::contains(vector<Territory *> v, Territory *find)
{
    for (Territory *t : v)
    {
        if (t == find)
            return true;
    }
    return false;
}

string PlayerStrategy::getPlayerType() { return ""; }

void PlayerStrategy::becomeAggressive()
{

    cout << this->getPlayer()->getPlayerName() << " will become an Aggressive Player!" << endl;

    Aggressive *angyBoi = new Aggressive();

    angyBoi->setPlayer(this->getPlayer());

    angyBoi->getPlayer()->setPlayerStrategy(angyBoi);

    for (Territory *t : angyBoi->getPlayer()->getTerritories())
    {
        t->setPlayer(angyBoi->getPlayer());
    }

    removePlayerFromList(this->getPlayer());

    addToPlayerList(angyBoi->getPlayer());
}

void checkNeutralAttack(Territory *t)
{

    Neutral *temp = new Neutral();

    if (t->getPlayer()->getPlayerStrategy()->getPlayerType() == "Neutral")
    {

        cout << "Someone has Attacked a Neutral Player!" << endl;

        t->getPlayer()->getPlayerStrategy()->becomeAggressive();
    }

    delete temp;
    temp = NULL;
}

// HUMAN PLAYER STRATEGY

string Human::getPlayerType() { return "Human"; }

void Human::issueOrder(Order *)
{
    // add the restraints to make sure the human player has that available card
    cout << "Which Order would you like to play?:\n1. Deploy\n2. Advance\n3. Airlift\n4. Bomb\n5. Blockade\n6. Negotiate" << endl;
    cout << "Select an Order:";

    int selectedOrder;

    cin >> selectedOrder;

    vector<Territory *> possibleBomboclat;

    if (selectedOrder == 1)
    {

        int armies;
        int selectedT;

        cout << "To which Territory would you like to Deploy the armies:" << endl;

        int counter = 1;

        for (Territory *t : this->toDefend())
        {

            cout << counter << ". " << t->getName() << endl;
            counter++;
        }

        cin >> selectedT;

        Territory *t = this->getPlayer()->getTerritories()[selectedT - 1];

        cout << "How many armies would you like to deploy: " << endl;

        cin >> armies;

        Order *d = new Deploy(this->getPlayer()->getObserver(), this->getPlayer(), armies, t);

        this->getPlayer()->getOrderList()->addOrder(d);
    }
    else if (selectedOrder == 2)
    {

        int armies;
        int selectedSource;
        int selectedTarget;

        cout << "From which Territory would you like to Advance the armies:" << endl;

        int counter = 1;

        for (Territory *t : this->getPlayer()->getTerritories())
        {

            cout << counter << ". " << t->getName() << endl;
            counter++;
        }

        counter = 1;
        cin >> selectedSource;

        cout << "To which Territory would you like to Advance the armies:" << endl;

        for (Territory *t : this->getPlayer()->getTerritories()[selectedSource - 1]->getAdjTerritories())
        {

            cout << counter << ". " << t->getName() << endl;
            counter++;
        }

        cin >> selectedTarget;

        Territory *source = this->getPlayer()->getTerritories()[selectedSource - 1];
        Territory *target = this->getPlayer()->getTerritories()[selectedSource - 1]->getAdjTerritories()[selectedTarget - 1];

        cout << "How many armies would you like to deploy: " << endl;

        cin >> armies;

        Order *a = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), armies, source, target);

        this->getPlayer()->getOrderList()->addOrder(a);
    }
    else if (selectedOrder == 3)
    {

        int armies;
        int selectedSource;
        int selectedTarget;

        cout << "From which Territory would you like to Airlift the armies:" << endl;

        int counter = 1;

        for (Territory *t : this->getPlayer()->getTerritories())
        {

            cout << counter << ". " << t->getName() << endl;
            counter++;
        }

        cin >> selectedSource;

        counter = 1;

        cout << "To which Territory would you like to Airlift the armies:" << endl;

        for (Territory *t : this->getPlayer()->getTerritories())
        {

            cout << counter << ". " << t->getName() << endl;
            counter++;
        }

        cin >> selectedTarget;

        cout << "How many armies would you like to airlift: " << endl;

        cin >> armies;

        Territory *source = this->getPlayer()->getTerritories()[selectedSource - 1];

        Territory *target = this->getPlayer()->getTerritories()[selectedTarget - 1];

        Order *a = new Airlift(this->getPlayer()->getObserver(), this->getPlayer(), armies, source, target);

        this->getPlayer()->getOrderList()->addOrder(a);
    }
    else if (selectedOrder == 4)
    {

        cout << "Which Territory would you like to Bomb?: " << endl;

        int counter = 1;

        int selectedTarget;

        for (Territory *t : this->getPlayer()->getTerritories())
        {

            for (Territory *t2 : t->getAdjTerritories())
            {

                if (t2->getPlayer() == this->getPlayer())
                {
                    continue;
                }

                possibleBomboclat.push_back(t2);

                cout << counter << ". " << t2->getName() << endl;

                counter++;
            }
        }

        cin >> selectedTarget;

        Order *a = new Bomb(this->getPlayer()->getObserver(), this->getPlayer(), possibleBomboclat.at(selectedTarget - 1));

        this->getPlayer()->getOrderList()->addOrder(a);
    }
    else if (selectedOrder == 5)
    {

        cout << "Which Territory would you like to Blockade?:" << endl;

        int selectedTarget;

        int counter = 1;

        for (Territory *t : this->getPlayer()->getTerritories())
        {

            cout << counter << ". " << t->getName() << endl;
            counter++;
        }

        cin >> selectedTarget;

        Order *a = new Blockade(this->getPlayer()->getObserver(), this->getPlayer(), this->getPlayer()->getTerritories()[selectedTarget - 1]);

        this->getPlayer()->getOrderList()->addOrder(a);
    }
    else if (selectedOrder == 6)
    {

        cout << "Which Player would you like to Negotiate with?:" << endl;

        int selectedTarget;

        int counter = 1;

        for (Player *p : getPlayerList())
        {

            cout << counter << ". " << p->getPlayerName() << endl;
            counter++;
        }

        cin >> selectedTarget;

        Order *a = new Negotiate(this->getPlayer()->getObserver(), this->getPlayer(), getPlayerList()[selectedTarget - 1]);

        this->getPlayer()->getOrderList()->addOrder(a);
    }
}

vector<Territory *> Human::toAttack()
{

    vector<Territory *> potentialAttack;

    bool alreadyContained = false;

    for (Territory *t : this->getPlayer()->getTerritories())
    {

        for (Territory *t2 : t->getAdjTerritories())
        {

            if (t2->getPlayer() != this->getPlayer())
            {

                if (!this->contains(potentialAttack, t2))
                {

                    potentialAttack.push_back(t2);
                }
            }
        }
    }
    return potentialAttack;
}

vector<Territory *> Human::toDefend()
{

    return this->getPlayer()->getTerritories();
}

// AGGRESSIVE PLAYER STRATEGY

string Aggressive::getPlayerType() { return "Aggressive"; }

// Territory *Aggressive::randomTerritoryToAttack()
// {
//     std::random_device rd;
//     std::mt19937 gen(rd());

//     auto attackableTerritories = toAttack();

//     int min = 0;
//     int max = attackableTerritories.size() - 1;

//     std::uniform_int_distribution<> distRandomIndex(min, max);
//     int randomIndex = distRandomIndex(gen);

//     Territory *selectedTerritorytoAttack = attackableTerritories[randomIndex];
//     return selectedTerritorytoAttack;
// }

Territory *Aggressive::randomTerritoryToDefend()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    auto defendableTerritories = toDefend();

    vector<double> probabilityToDefend;
    for (int i = 0; i < defendableTerritories.size(); i++)
    {
        probabilityToDefend.push_back(defendableTerritories.size() - i);
    }

    std::discrete_distribution<> distToDefend(probabilityToDefend.begin(), probabilityToDefend.end());
    int randomIndexDefend = distToDefend(gen); // get a random index

    // int min = 0;
    // int max = defendableTerritories.size() - 1;

    // std::uniform_int_distribution<> distRandomIndex(min, max);
    // int randomIndex = distRandomIndex(gen);

    Territory *selectedTerritorytoDefend = defendableTerritories[randomIndexDefend];
    return selectedTerritorytoDefend;
}

void Aggressive::issueOrder(Order *order)
{

    if (Deploy *d = dynamic_cast<Deploy *>(order))
    {
        Territory *t = randomTerritoryToDefend();

        cout << "\nDeploy Order issued for : " << this->getPlayer()->getPlayerName() << " of type " << this->getPlayerType() << " with " << this->getPlayer()->getReinforcementTemp() << " armies in the reinforcement pool !" << endl;
        int min = 1;
        int max = this->getPlayer()->getReinforcementTemp();
        std::uniform_int_distribution<> distRandArmiesDeploy(min, max);
        std::random_device rd;
        std::mt19937 gen(rd());
        int randomNumArmiesDeploy = distRandArmiesDeploy(gen);

        // deploy random number of army units to a random territory to defend

        Order *dep = new Deploy(this->getPlayer()->getObserver(), this->getPlayer(), randomNumArmiesDeploy, t);
        this->getPlayer()->setReinforcementTemp(this->getPlayer()->getReinforcementTemp() - randomNumArmiesDeploy);

        cout << "Deploy to: " << t->getName() << " with " << randomNumArmiesDeploy << " armies\n"
             << this->getPlayer()->getReinforcementTemp() << " armies left in reinforcement pool" << endl;
        this->getPlayer()->getOrderList()->addOrder(dep);

        // add order to order list

        return;
    }
    else if (Advance *d = dynamic_cast<Advance *>(order))
    {
        vector<Territory *> adjT;

        Territory *randoA = randomTerritoryToDefend();
        if (randoA->getNumArmiesTemp() >= 1)
        {
            for (Territory *tadj : randoA->getAdjTerritories())
            {
                if (tadj->getPlayer() != this->getPlayer())
                {
                    adjT.push_back(tadj);
                }
            }
            if (adjT.size() == 0)
            {
                adjT.clear();
            }
            else
            {
                std::sort(adjT.begin(), adjT.end(), compareArmiesBenevolent);
                Territory *target = adjT.at(0);

                int min = 0;
                int max = randoA->getNumArmiesTemp();

                std::uniform_int_distribution<> distRandArmiesDeploy(min, max);
                std::random_device rd;
                std::mt19937 gen(rd());
                int randomNumArmiesDeploy = distRandArmiesDeploy(gen);

                cout << "\n"
                     << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to ATTACK !" << endl;
                cout << randoA->getName() << " sends " << randomNumArmiesDeploy << " armies to " << target->getName() << endl;
                Advance *ad = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), randomNumArmiesDeploy, randoA, target);

                randoA->setNumArmiesTemp(randoA->getNumArmiesTemp() - randomNumArmiesDeploy);

                this->getPlayer()->getOrderList()->addOrder(ad);
                return;
            }
        }

        vector<Territory *> low = toDefend();
        // Territory *target = randomTerritoryToDefend();

        // Territory *target = low.at(0);

        for (Territory *T : low)
        {
            if (T->getNumArmiesTemp() < 1)
            {
                continue;
            }
            for (Territory *tadj : T->getAdjTerritories())
            {
                if (tadj->getPlayer() != this->getPlayer())
                {
                    adjT.push_back(tadj);
                }
            }
            if (adjT.size() == 0)
            {
                adjT.clear();
                continue;
            }

            std::sort(adjT.begin(), adjT.end(), compareArmiesBenevolent);
            Territory *target = adjT.at(0);

            int min = 1;
            int max = T->getNumArmiesTemp();

            std::uniform_int_distribution<> distRandArmiesDeploy(min, max);
            std::random_device rd;
            std::mt19937 gen(rd());
            int randomNumArmiesDeploy = distRandArmiesDeploy(gen);

            cout << "\n"
                 << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to ATTACK !" << endl;
            cout << T->getName() << " sends " << randomNumArmiesDeploy << " armies to " << target->getName() << endl;
            Advance *ad = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), randomNumArmiesDeploy, T, target);

            T->setNumArmiesTemp(T->getNumArmiesTemp() - randomNumArmiesDeploy);

            this->getPlayer()->getOrderList()->addOrder(ad);
            return;
        }

        for (Territory *T : low)
        {
            if (T->getNumArmiesTemp() < 1)
            {
                continue;
            }
            for (Territory *tadj : T->getAdjTerritories())
            {
                if (tadj->getPlayer() == this->getPlayer())
                {
                    adjT.push_back(tadj);
                }
            }
            if (adjT.size() == 0)
            {
                adjT.clear();
                continue;
            }

            std::sort(adjT.begin(), adjT.end(), compareArmiesAggressive);
            Territory *target = adjT.at(0);

            int min = 1;
            int max = T->getNumArmiesTemp();

            std::uniform_int_distribution<> distRandArmiesDeploy(min, max);
            std::random_device rd;
            std::mt19937 gen(rd());
            int randomNumArmiesDeploy = distRandArmiesDeploy(gen);

            cout << "\n"
                 << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to DEFEND !" << endl;
            cout << T->getName() << " sends " << randomNumArmiesDeploy << " armies to " << target->getName() << endl;
            Advance *ad = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), randomNumArmiesDeploy, T, target);

            T->setNumArmiesTemp(T->getNumArmiesTemp() - randomNumArmiesDeploy);

            this->getPlayer()->getOrderList()->addOrder(ad);
            return;
        }

        cout << "\n"
             << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has no territory to defend nor attack !" << endl;
// /////////////////////////////////////////////////////////////////////
        // vector<Territory *> list = toDefend();

        // // Territory *strongest = list.at(list.size() - 1);

        // bool allFriendly = true;

        // for (int i = 0; i < list.size(); i++)
        // {
        //     for (Territory *t : list.at(i)->getAdjTerritories())
        //     {

        //         if (t->getPlayer() != this->getPlayer())
        //         {
        //             cout << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to ATTACK !" << endl;
        //             cout << list.at(i)->getName() << " sends " << list.at(i)->getNumArmies() << " armies to " << list.at(i)->getAdjTerritories()[0]->getName() << endl;
        //             Order *ad = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), list.at(i)->getNumArmies(), list.at(i), list.at(i)->getAdjTerritories()[0]);
        //             this->getPlayer()->getOrderList()->addOrder(ad);
        //             return;
        //             // allFriendly = false;
        //             // break;
        //         }
        //     }

        //     // if (allFriendly == false)
        //     // {

        //     //     Order *ad = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), list[i]->getNumArmies() / 2, list[i], list[i]->getAdjTerritories()[0]);

        //     //     this->getPlayer()->getOrderList()->addOrder(ad);
        //     //     return;
        //     // }

        //     // for (Territory *t : list[i]->getAdjTerritories())
        //     // {

        //     //     if (t->getPlayer() != this->getPlayer())
        //     // {

        //     if (i == 0)
        //     {
        //         if (list.at(list.size() - 1)->getAdjTerritories()[0]->getPlayer() != this->getPlayer())
        //         {
        //             cout << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to ATTACK !" << endl;
        //         }
        //         else
        //         {
        //             cout << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to DEFEND !" << endl;
        //         }

        //         cout << list.at(list.size() - 1)->getName() << " is issued to send " << list.at(list.size() - 1)->getNumArmies() / 2 << " armies to " << list.at(list.size() - 1)->getAdjTerritories()[0]->getName() << endl;
        //         Order *ad = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), list.at(list.size() - 1)->getNumArmies() / 2, list.at(list.size() - 1), list.at(list.size() - 1)->getAdjTerritories()[0]);
        //         this->getPlayer()->getOrderList()->addOrder(ad);
        //         return;
        //     }

        //     // }
        //     // }
        // }
    }
    else if (Blockade *d = dynamic_cast<Blockade *>(order))
    {

        // Territory *t = toDefend().at(0);

        Territory *t = randomTerritoryToDefend();
        cout << "\n"
             << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to BLOCKADE !" << endl;
        cout << t->getName() << " is issued to be blockaded" << endl;
        Blockade *b = new Blockade(this->getPlayer()->getObserver(), this->getPlayer(), t);

        this->getPlayer()->getOrderList()->addOrder(b);
    }
    else if (Airlift *d = dynamic_cast<Airlift *>(order))
    {
        vector<Territory *> list = toDefend();
        std::sort(list.begin(), list.end(), compareArmiesBenevolent);

        vector<Territory *> list2 = toDefend();

        if (list.size() > 1)
        {

            for (Territory *T : list)
            {
                if (T->getNumArmiesTemp() < 1)
                {
                    continue;
                }

                for (Territory *T2 : list2)
                {
                    if (T != T2)
                    {
                        int min = 1;
                        int max = T->getNumArmiesTemp();
                        std::uniform_int_distribution<> distRandArmiesAirlift(min, max);
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        int randomNumArmiesAirlift = distRandArmiesAirlift(gen);

                        cout << "\n"
                             << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to AIRLIFT !" << endl;
                        cout << T->getName() << " is issued to airlift " << randomNumArmiesAirlift << " armies to " << T2->getName() << endl;
                        Airlift *airlift = new Airlift(this->getPlayer()->getObserver(), this->getPlayer(), randomNumArmiesAirlift, T, T2);

                        T->setNumArmiesTemp(T->getNumArmiesTemp() - randomNumArmiesAirlift);

                        this->getPlayer()->getOrderList()->addOrder(airlift);
                        return;
                    }
                }
            }
        }
        cout << "\n"
             << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has no adjacent territories to airlift to " << endl;
    }
    else if (Negotiate *d = dynamic_cast<Negotiate *>(order))
    {
        cout << "\n"
             << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " does NOT want to negotiate !!" << endl;
        return;
        // for (Player *p : getPlayerList())
        // {

        //     if (p != this->getPlayer())
        //     {

        //         Order *n = new Negotiate(this->getPlayer()->getObserver(), this->getPlayer(), p);
        //         this->getPlayer()->getOrderList()->addOrder(n);
        //         break;
        //     }
        // }
    }
    else if (Bomb *d = dynamic_cast<Bomb *>(order))
    {

        for (Territory *t : this->getPlayer()->getTerritories())
        {

            for (Territory *t2 : t->getAdjTerritories())
            {

                if (t2->getPlayer() != this->getPlayer())
                {
                    cout << "\n"
                         << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to BOMB !" << endl;
                    cout << t2->getName() << " is issued to be bombed by " << t->getName() << endl;

                    Order *bomb = new Bomb(this->getPlayer()->getObserver(), this->getPlayer(), t2);

                    this->getPlayer()->getOrderList()->addOrder(bomb);
                    return;
                }
            }
        }
    }
}

vector<Territory *> Aggressive::toAttack()
{

    vector<Territory *> potentialAttack;

    bool alreadyContained = false;

    for (Territory *t : this->getPlayer()->getTerritories())
    {

        for (Territory *t2 : t->getAdjTerritories())
        {

            if (t2->getPlayer() != this->getPlayer())
            {

                if (!this->contains(potentialAttack, t2))
                {

                    potentialAttack.push_back(t2);
                }
            }
        }
    }
    return potentialAttack;
}

vector<Territory *> Aggressive::toDefend()
{

    vector<Territory *> t_list = this->getPlayer()->getTerritories();

    std::sort(t_list.begin(), t_list.end(), compareArmiesAggressive);

    return t_list;
}

// BENEVOLENT PLAYER STRATEGY

string Benevolent::getPlayerType() { return "Benevolent"; }

Territory *Benevolent::randomTerritoryToDefend()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    auto defendableTerritories = toDefend();

    vector<double> probabilityToDefend;
    for (int i = 0; i < defendableTerritories.size(); i++)
    {
        probabilityToDefend.push_back(defendableTerritories.size() - i);
    }

    std::discrete_distribution<> distToDefend(probabilityToDefend.begin(), probabilityToDefend.end());
    int randomIndexDefend = distToDefend(gen); // get a random index

    // int min = 0;
    // int max = defendableTerritories.size() - 1;

    // std::uniform_int_distribution<> distRandomIndex(min, max);
    // int randomIndex = distRandomIndex(gen);

    Territory *selectedTerritorytoDefend = defendableTerritories[randomIndexDefend];
    return selectedTerritorytoDefend;
}

void Benevolent::issueOrder(Order *order)
{

    if (Deploy *d = dynamic_cast<Deploy *>(order))
    {
        Territory *t = randomTerritoryToDefend();

        cout << "\nDeploy Order issued for : " << this->getPlayer()->getPlayerName() << " of type " << this->getPlayerType() << " with " << this->getPlayer()->getReinforcementTemp() << " armies in the reinforcement pool !" << endl;
        int min = 1;
        int max = this->getPlayer()->getReinforcementTemp();
        std::uniform_int_distribution<> distRandArmiesDeploy(min, max);
        std::random_device rd;
        std::mt19937 gen(rd());
        int randomNumArmiesDeploy = distRandArmiesDeploy(gen);

        // deploy random number of army units to a random territory to defend

        Order *dep = new Deploy(this->getPlayer()->getObserver(), this->getPlayer(), randomNumArmiesDeploy, t);
        this->getPlayer()->setReinforcementTemp(this->getPlayer()->getReinforcementTemp() - randomNumArmiesDeploy);

        cout << "Deploy to: " << t->getName() << " with " << randomNumArmiesDeploy << " armies\n"
             << this->getPlayer()->getReinforcementTemp() << " armies left in reinforcement pool" << endl;
        this->getPlayer()->getOrderList()->addOrder(dep);

        // add order to order list

        return;
    }
    else if (Advance *d = dynamic_cast<Advance *>(order))
    {

        vector<Territory *> low = toDefend();
        // Territory *target = randomTerritoryToDefend();

        // Territory *target = low.at(0);

        vector<Territory *> adjT;
        for (Territory *T : low)
        {
            for (Territory *tadj : T->getAdjTerritories())
            {
                if (tadj->getNumArmiesTemp() < 1)
                {
                    continue;
                }
                if (tadj->getPlayer() == this->getPlayer())
                {
                    adjT.push_back(tadj);
                }
            }
            if (adjT.size() == 0)
            {
                adjT.clear();
                continue;
            }

            std::sort(adjT.begin(), adjT.end(), compareArmiesAggressive);
            Territory *source = adjT.at(0);

            int min = 1;
            int max = source->getNumArmiesTemp();
            std::uniform_int_distribution<> distRandArmiesDeploy(min, max);
            std::random_device rd;
            std::mt19937 gen(rd());
            int randomNumArmiesDeploy = distRandArmiesDeploy(gen);

            cout << "\n"
                 << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to DEFEND !" << endl;
            cout << source->getName() << " sends " << randomNumArmiesDeploy << " armies to " << T->getName() << endl;
            Advance *ad = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), randomNumArmiesDeploy, source, T);

            source->setNumArmiesTemp(source->getNumArmiesTemp() - randomNumArmiesDeploy);

            this->getPlayer()->getOrderList()->addOrder(ad);
            return;
        }
        cout << "\n"
             << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has no territory to defend and refuses to attack !" << endl;

        // for (Territory *t : target->getAdjTerritories())
        // {

        //     if (t->getPlayer() == this->getPlayer())
        //     {

        //         adjT.push_back(t);
        //     }
        // }
        // if (adjT.size() == 0)
        // {
        //     cout << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has no adjacent territories to advance for defense ! " << endl;

        //     return;
        // }
        // std::sort(adjT.begin(), adjT.end(), compareArmiesBenevolent);

        // Territory *source = adjT.at(adjT.size() - 1);

        // Advance *ad = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), source->getNumArmies() / 2, source, target);

        // this->getPlayer()->getOrderList()->addOrder(ad);
    }
    else if (Blockade *d = dynamic_cast<Blockade *>(order))
    {

        // Territory *t = toDefend().at(0);
        Territory *t = randomTerritoryToDefend();
        cout << "\n"
             << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to BLOCKADE !" << endl;
        cout << t->getName() << " is issued to be blockaded" << endl;
        Blockade *b = new Blockade(this->getPlayer()->getObserver(), this->getPlayer(), t);

        this->getPlayer()->getOrderList()->addOrder(b);
    }
    else if (Airlift *d = dynamic_cast<Airlift *>(order))
    {

        vector<Territory *> list = toDefend();
        std::sort(list.begin(), list.end(), compareArmiesAggressive);

        vector<Territory *> list2 = toDefend();

        if (list.size() > 1)
        {

            for (Territory *T : list)
            {
                if (T->getNumArmiesTemp() < 1)
                {
                    continue;
                }

                for (Territory *T2 : list2)
                {
                    if (T != T2)
                    {
                        int min = 1;
                        int max = T->getNumArmiesTemp();
                        std::uniform_int_distribution<> distRandArmiesAirlift(min, max);
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        int randomNumArmiesAirlift = distRandArmiesAirlift(gen);

                        cout << "\n"
                             << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to AIRLIFT !" << endl;
                        cout << T->getName() << " is issued to airlift " << randomNumArmiesAirlift << " armies to " << T2->getName() << endl;
                        Airlift *airlift = new Airlift(this->getPlayer()->getObserver(), this->getPlayer(), randomNumArmiesAirlift, T, T2);

                        T->setNumArmiesTemp(T->getNumArmiesTemp() - randomNumArmiesAirlift);

                        this->getPlayer()->getOrderList()->addOrder(airlift);
                        return;
                    }
                }
            }
        }
        cout << "\n"
             << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has no adjacent territories to airlift to " << endl;

        // vector<Territory *> list = toDefend();
        // if (list.size() <= 1)
        // {
        //     cout << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " does not have any adjacent territory to airlift to !" << endl;

        //     return;
        // }
        // cout << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to AIRLIFT !" << endl;
        // cout << list.at(list.size() - 1)->getName() << " is issued to airlift " << list.at(list.size() - 1)->getNumArmies() / 4 << " armies to " << list.at(0)->getName() << endl;
        // Airlift *airlift = new Airlift(this->getPlayer()->getObserver(), this->getPlayer(), list.at(list.size() - 1)->getNumArmies() / 4, list.at(list.size() - 1), list.at(0));

        // this->getPlayer()->getOrderList()->addOrder(airlift);
    }
    else if (Negotiate *d = dynamic_cast<Negotiate *>(order))
    {
        vector<Territory *> list = toAttack();
        for (Territory *t : list)
        {
            if (t->getPlayer() != nullptr && t->getPlayer() != this->getPlayer())
            {
                cout << "\n"
                     << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has chosen to NEGOTIATE !" << endl;
                cout << "negotiation is issued with " << t->getPlayer()->getPlayerName() << endl;
                Negotiate *n = new Negotiate(this->getPlayer()->getObserver(), this->getPlayer(), t->getPlayer());
                this->getPlayer()->getOrderList()->addOrder(n);
                return;
            }
        }
        cout << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " has no one to negotiate with !!" << endl;

        // for (Player *p : getPlayerList())
        // {

        //     if (p != this->getPlayer())
        //     {
        //     }
        // }
    }
    else if (Bomb *b = dynamic_cast<Bomb *>(order))
    {
        cout << "\n"
             << this->getPlayerType() << " " << this->getPlayer()->getPlayerName() << " does NOT want to bomb !!" << endl;
        return;
    }
}

vector<Territory *> Benevolent::toAttack()
{

    // cout << "Benevolent Player " << this->getPlayer()->getPlayerName() << " doesn't Attack." << endl;

    // vector<Territory *> x;

    // return x;
    vector<Territory *> potentialAttack;

    bool alreadyContained = false;

    for (Territory *t : this->getPlayer()->getTerritories())
    {

        for (Territory *t2 : t->getAdjTerritories())
        {

            if (t2->getPlayer() != this->getPlayer())
            {

                if (!this->contains(potentialAttack, t2))
                {

                    potentialAttack.push_back(t2);
                }
            }
        }
    }
    return potentialAttack;
}

vector<Territory *> Benevolent::toDefend()
{

    vector<Territory *> t_list = this->getPlayer()->getTerritories();

    std::sort(t_list.begin(), t_list.end(), compareArmiesBenevolent);

    return t_list;
}

bool compareArmiesBenevolent(Territory *a, Territory *b)
{
    return a->getNumArmies() < b->getNumArmies();
}
bool compareArmiesAggressive(Territory *a, Territory *b)
{
    return a->getNumArmies() > b->getNumArmies();
}

string Neutral::getPlayerType() { return "Neutral"; }

// NEUTRAL PLAYER STRATEGY

void Neutral::issueOrder(Order *)
{
    cout << "Neutral Player " << this->getPlayer()->getPlayerName() << " doesn't issue orders." << endl;
}

vector<Territory *> Neutral::toAttack()
{

    cout << "Neutral Player doesn't Attack." << endl;

    vector<Territory *> x;

    return x;
}

vector<Territory *> Neutral::toDefend()
{

    cout << "Neutral Player doesn't defend" << endl;

    vector<Territory *> x;

    return x;
}

// CHEATER PLAYER STRATEGY

string Cheater::getPlayerType() { return "Cheater"; }

void Cheater::issueOrder(Order *)
{

    Order *placeholder = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), -99, this->getPlayer()->getTerritories()[0], this->getPlayer()->getTerritories()[0]);

    this->getPlayer()->getOrderList()->addOrder(placeholder);
}

vector<Territory *> Cheater::toAttack()
{

    vector<Territory *> potentialAttack;

    bool alreadyContained = false;

    for (Territory *t : this->getPlayer()->getTerritories())
    {

        for (Territory *t2 : t->getAdjTerritories())
        {

            if (t2->getPlayer() != this->getPlayer())
            {

                if (!this->contains(potentialAttack, t2))
                {

                    potentialAttack.push_back(t2);
                }
            }
        }
    }

    if (this->cheaterCanConquer())
    {

        for (Territory *t : potentialAttack)
        {

            cout << "Cheater is conquering Territory " << t->getName() << endl;

            t->getPlayer()->removeTerritory(t);
            t->setPlayer(this->getPlayer());
            this->getPlayer()->addTerritory(t);
        }

        this->isConquering();
    }
    else
    {

        cout << "Cheater has already conquered this round!" << endl;
    }

    return potentialAttack;
}

vector<Territory *> Cheater::toDefend()
{

    return this->getPlayer()->getTerritories();
}

bool Cheater::cheaterCanConquer()
{
    return canConquer;
}

void Cheater::isConquering()
{
    canConquer = false;
}

void Cheater::resetCheaterConquer()
{
    canConquer = true;
}

void PlayerStrategy::assignPlayer(Player *p)
{
    player = p;
}

// PLAYER STRATEGY
