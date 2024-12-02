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
}

void checkNeutralAttack(Territory *t)
{

    if (t->getPlayer() != nullptr && t->getPlayer()->getPlayerStrategy()->getPlayerType() == "Neutral")
    {

        cout << "Someone has Attacked a Neutral Player!" << endl;

        t->getPlayer()->getPlayerStrategy()->becomeAggressive();
    }
}

// HUMAN PLAYER STRATEGY

string Human::getPlayerType() { return "Human"; }

void Human::issueOrder(Order *order)
{
    // add the restraints to make sure the human player has that available card
    // cout << "Which Order would you like to play?:\n1. Deploy\n2. Advance\n3. Airlift\n4. Bomb\n5. Blockade\n6. Negotiate" << endl;
    // cout << "Select an Order:";

    // int selectedOrder;

    // cin >> selectedOrder;

    vector<Territory *> possibleBomboclat;
    vector<Territory *> possibleBomboclat2;

    if (Deploy *d = dynamic_cast<Deploy *>(order))
    {

        int armies;
        int selectedT;

        cout << "\nA Deploy Order has been initiated !" << endl;
        cout << "To which Territory would you like to Deploy the armies:\n"
             << endl;

        int counter = 1;
        possibleBomboclat2 = this->toDefend();

        for (Territory *t : possibleBomboclat2)
        {
            cout << counter << ". " << t->getName() << endl;
            counter++;
        }

        while (true)
        {
            cout << "Enter the number of the territory: ";
            if (cin >> selectedT)
            {
                if (selectedT >= 1 && selectedT <= possibleBomboclat2.size())
                {
                    break; // Valid selection
                }
                else
                {
                    cout << "Invalid selection. Please choose a number from the list." << endl;
                    continue;
                }
            }
            else
            {
                cout << "Invalid input. Please enter a number: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        }

        Territory *t = possibleBomboclat2[selectedT - 1];

        while (true)
        {
            cout << "\nYou can currently deploy " << this->getPlayer()->getReinforcementTemp() << " armies." << endl;
            cout << "How many armies would you like to deploy: ";
            if (cin >> armies)
            {
                if (armies > 0 && armies <= this->getPlayer()->getReinforcementTemp())
                {
                    break; // Valid number of armies
                }
                else
                {
                    cout << "Invalid number of armies. Please choose between 1 and "
                         << this->getPlayer()->getReinforcementTemp() << "." << endl;
                }
            }
            else
            {
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        }

        Order *dep = new Deploy(this->getPlayer()->getObserver(), this->getPlayer(), armies, t);
        this->getPlayer()->setReinforcementTemp(this->getPlayer()->getReinforcementTemp() - armies);
        cout << "\nDeploy Order Issued ! Deploying " << armies << " armies to " << t->getName() << endl;

        this->getPlayer()->getOrderList()->addOrder(dep);
    }
    else if (Advance *d = dynamic_cast<Advance *>(order))
    {
        int armies;
        int selectedSource;
        int selectedTarget;

        std::cout << "\nAn Advance Order has been initiated!" << std::endl;

        // Select source territory
        while (true)
        {
            std::cout << "\nFrom which territory would you like to advance the armies:" << std::endl;
            int counter = 1;

            // Display only territories with armies
            for (Territory *t : this->getPlayer()->getTerritories())
            {
                if (t->getNumArmiesTemp() > 0)
                {
                    possibleBomboclat.push_back(t);
                    std::cout << counter << ". " << t->getName() << " -> " << t->getNumArmiesTemp() << " armies" << std::endl;
                    counter++;
                }
            }

            if (counter == 1)
            {
                // No available territories to advance from
                std::cout << "Oops! It seems you currently do not have any armies in any territory to advance!\nWait until the next round!" << std::endl;
                return;
            }

            std::cout << "Enter the number of the territory: ";
            if (std::cin >> selectedSource && selectedSource >= 1 && selectedSource < counter)
            {
                break; // Valid input
            }
            else
            {
                std::cout << "Invalid input. Please enter a valid number from the list." << std::endl;
                std::cin.clear();               // Clear the error flags
                std::cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        }
        Territory *source = possibleBomboclat[selectedSource - 1];

        possibleBomboclat2 = source->getAdjTerritories();

        // Select target territory
        while (true)
        {
            std::cout << "\nTo which territory would you like to advance the armies:" << std::endl;
            int counter = 1;

            for (Territory *t : possibleBomboclat2)
            {
                std::cout << counter << ". " << t->getName() << std::endl;
                counter++;
            }

            std::cout << "Enter the number of the territory: ";
            if (std::cin >> selectedTarget && selectedTarget >= 1 && selectedTarget < counter)
            {
                break; // Valid input
            }
            else
            {
                std::cout << "Invalid input. Please enter a valid number from the list." << std::endl;
                std::cin.clear();               // Clear the error flags
                std::cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        }

        // Get source and target territories
        Territory *target = possibleBomboclat2[selectedTarget - 1];

        // Select the number of armies to advance
        while (true)
        {
            std::cout << "\nYou can currently advance " << source->getNumArmiesTemp() << " armies." << std::endl;
            std::cout << "How many armies would you like to advance: ";
            if (std::cin >> armies && armies > 0 && armies <= source->getNumArmiesTemp())
            {
                break; // Valid input
            }
            else
            {
                std::cout << "Invalid input. Please enter a valid number of armies." << std::endl;
                std::cin.clear();               // Clear the error flags
                std::cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        }

        // Create the advance order
        Order *a = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), armies, source, target);

        // Adjust armies in the source territory
        source->setNumArmiesTemp(source->getNumArmiesTemp() - armies);

        // Add the order to the player's order list
        this->getPlayer()->getOrderList()->addOrder(a);

        cout << "\nAdavnce Order Issued ! Advancing " << armies << " armies from " << source->getName() << " to " << target->getName() << endl;
    }
    else if (Airlift *d = dynamic_cast<Airlift *>(order))
    {

        int armies;
        int selectedSource;
        int selectedTarget;
        std::cout << "\nAn Airlift Order has been initiated!" << std::endl;

        std::cout << "From which territory would you like to Airlift the armies:\n"
                  << std::endl;

        // Select source territory
        while (true)
        {
            int counter = 1;

            for (Territory *t : this->getPlayer()->getTerritories())
            {
                if (t->getNumArmiesTemp() > 0)
                {
                    possibleBomboclat.push_back(t);
                    std::cout << counter << ". " << t->getName() << std::endl;
                    counter++;
                }
            }

            if (counter == 1)
            {
                // No available territories to airlift from
                std::cout << "Oops! It seems you currently do not have any armies in any territory to airlift!\nWait until the next round!" << std::endl;
                return;
            }

            std::cout << "Enter the number of the territory: ";
            if (std::cin >> selectedSource && selectedSource >= 1 && selectedSource < counter)
            {
                break; // Valid input
            }
            else
            {
                std::cout << "Invalid input. Please enter a valid number from the list." << std::endl;
                std::cin.clear();               // Clear error flags
                std::cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        }

        Territory *source = possibleBomboclat[selectedSource - 1];

        // Select target territory
        while (true)
        {
            std::cout << "To which territory would you like to Airlift the armies:\n"
                      << std::endl;
            int counter = 1;

            for (Territory *t : this->getPlayer()->getTerritories())
            {
                if (t != source)
                {
                    possibleBomboclat2.push_back(t);
                    std::cout << counter << ". " << t->getName() << std::endl;
                    counter++;
                }
            }

            if (counter == 1)
            {
                // No available territories to airlift to
                std::cout << "Oops! It seems you currently only have one territory! Impossible to airlift!\nWait until the next round!" << std::endl;
                return;
            }

            std::cout << "Enter the number of the territory: ";
            if (std::cin >> selectedTarget && selectedTarget >= 1 && selectedTarget < counter)
            {
                break; // Valid input
            }
            else
            {
                std::cout << "Invalid input. Please enter a valid number from the list." << std::endl;
                std::cin.clear();               // Clear error flags
                std::cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        }

        Territory *target = possibleBomboclat2[selectedTarget - 1];

        // Select the number of armies to airlift
        while (true)
        {
            std::cout << "How many armies would you like to airlift: ";
            if (std::cin >> armies && armies > 0 && armies <= source->getNumArmiesTemp())
            {
                break; // Valid input
            }
            else
            {
                std::cout << "Invalid input. Please enter a valid number of armies (1-" << source->getNumArmiesTemp() << ")." << std::endl;
                std::cin.clear();               // Clear error flags
                std::cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        }

        // Create the airlift order
        Order *a = new Airlift(this->getPlayer()->getObserver(), this->getPlayer(), armies, source, target);

        // Adjust armies in the source territory
        source->setNumArmiesTemp(source->getNumArmiesTemp() - armies);

        // Add the order to the player's order list
        this->getPlayer()->getOrderList()->addOrder(a);

        cout << "\nAirlift Order Issued ! Airlifting " << armies << " armies from " << source->getName() << " to " << target->getName() << endl;
    }
    else if (Bomb *d = dynamic_cast<Bomb *>(order))
    {

        int selectedTarget;
        std::cout << "\nA Bomb Order has been initiated!" << std::endl;

        std::cout << "Which Territory would you like to Bomb?: \n"
                  << std::endl;

        int counter = 1;

        // Display the list of territories available to bomb
        auto possibleBomboclat = this->toAttack();
        if (possibleBomboclat.empty())
        {
            std::cout << "Oops! It seems there are no valid territories to bomb at the moment!" << std::endl;
            return;
        }

        for (Territory *t : possibleBomboclat)
        {
            std::cout << counter << ". " << t->getName() << std::endl;
            counter++;
        }

        // Input validation for territory selection
        while (true)
        {
            std::cout << "Enter the number of the territory you would like to bomb: ";
            if (std::cin >> selectedTarget && selectedTarget >= 1 && selectedTarget <= possibleBomboclat.size())
            {
                break; // Valid input
            }
            else
            {
                std::cout << "Invalid input. Please enter a valid number from the list." << std::endl;
                std::cin.clear();               // Clear error flags
                std::cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        }

        // Create the Bomb order
        Order *a = new Bomb(this->getPlayer()->getObserver(), this->getPlayer(), possibleBomboclat.at(selectedTarget - 1));

        // Add the order to the player's order list
        this->getPlayer()->getOrderList()->addOrder(a);

        cout << "\nBombing Order Issued ! Bombing " << possibleBomboclat.at(selectedTarget - 1)->getName() << endl;
    }
    else if (Blockade *d = dynamic_cast<Blockade *>(order))
    {
        int selectedTarget;
        std::cout << "\nAn Blockade Order has been initiated!" << std::endl;

        std::cout << "Which Territory would you like to Blockade?:\n"
                  << std::endl;

        int counter = 1;
        auto territories = this->getPlayer()->getTerritories();

        // Display available territories to blockade
        if (territories.empty())
        {
            std::cout << "Oops! It seems there are no territories available to blockade!" << std::endl;
            return;
        }

        for (Territory *t : territories)
        {
            std::cout << counter << ". " << t->getName() << std::endl;
            counter++;
        }

        // Input validation for territory selection
        while (true)
        {
            std::cout << "Enter the number of the territory you would like to blockade: ";
            if (std::cin >> selectedTarget && selectedTarget >= 1 && selectedTarget <= territories.size())
            {
                break; // Valid input
            }
            else
            {
                std::cout << "Invalid input. Please enter a valid number from the list." << std::endl;
                std::cin.clear();               // Clear error flags
                std::cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        }

        // Create the Blockade order
        Order *a = new Blockade(this->getPlayer()->getObserver(), this->getPlayer(), territories[selectedTarget - 1]);

        // Add the order to the player's order list
        this->getPlayer()->getOrderList()->addOrder(a);

        std::cout << "\nBlockade Order Issued! Blockading "
                  << territories[selectedTarget - 1]->getName() << std::endl;
    }
    else if (Negotiate *d = dynamic_cast<Negotiate *>(order))
    {

        // cout << "Which Player would you like to Negotiate with?:\n"
        //      << endl;

        // int selectedTarget;

        // int counter = 1;

        // for (Player *p : getPlayerList())
        // {
        //     if (p != this->getPlayer())
        //     {
        //         cout << counter << ". " << p->getPlayerName() << endl;
        //         counter++;
        //     }
        // }

        // cin >> selectedTarget;

        // Order *a = new Negotiate(this->getPlayer()->getObserver(), this->getPlayer(), getPlayerList()[selectedTarget - 1]);

        // this->getPlayer()->getOrderList()->addOrder(a);

        // std::cout << "\nNegotiate Order Issued! Negotiating with "
        //           << getPlayerList()[selectedTarget - 1]->getPlayerName() << std::endl;

        int selectedTarget;
        std::cout << "\nA Negotiate Order has been initiated!" << std::endl;

        std::cout << "Which Player would you like to Negotiate with?:\n"
                  << std::endl;

        int counter = 1;
        auto players = getPlayerList();

        // Display available players to negotiate with
        if (players.size() <= 1)
        {
            std::cout << "Oops! It seems there are no other players available to negotiate with!" << std::endl;
            return;
        }

        for (Player *p : players)
        {
            if (p != this->getPlayer())
            {
                std::cout << counter << ". " << p->getPlayerName() << std::endl;
                counter++;
            }
        }

        // Input validation for player selection
        while (true)
        {
            std::cout << "Enter the number of the player you would like to negotiate with: ";
            if (std::cin >> selectedTarget && selectedTarget >= 1 && selectedTarget < counter)
            {
                break; // Valid input
            }
            else
            {
                std::cout << "Invalid input. Please enter a valid number from the list." << std::endl;
                std::cin.clear();               // Clear error flags
                std::cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        }

        // Create the Negotiate order
        Player *targetPlayer = nullptr;
        counter = 1;
        for (Player *p : players)
        {
            if (p != this->getPlayer())
            {
                if (counter == selectedTarget)
                {
                    targetPlayer = p;
                    break;
                }
                counter++;
            }
        }

        if (targetPlayer)
        {
            Order *a = new Negotiate(this->getPlayer()->getObserver(), this->getPlayer(), targetPlayer);
            this->getPlayer()->getOrderList()->addOrder(a);
            std::cout << "\nNegotiate Order Issued! Negotiating with " << targetPlayer->getPlayerName() << std::endl;
        }
        else
        {
            std::cout << "Error: Selected player is invalid." << std::endl;
        }
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

                int min = 1;
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

// NEUTRAL PLAYER STRATEGY
string Neutral::getPlayerType() { return "Neutral"; }

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

void Cheater::issueOrder(Order *order)
{
    if (Advance *d = dynamic_cast<Advance *>(order))
    {
        Order *placeholder = new Advance(this->getPlayer()->getObserver(), this->getPlayer(), -99, this->getPlayer()->getTerritories()[0], this->getPlayer()->getTerritories()[0]);

        this->getPlayer()->getOrderList()->addOrder(placeholder);
    }
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
        cout << "\n"
             << endl;
        for (Territory *t : potentialAttack)
        {

            cout << "Cheater " << this->getPlayer()->getPlayerName() << " is conquering Territory " << t->getName() << endl;

            t->getPlayer()->removeTerritory(t);
            t->setPlayer(this->getPlayer());
            this->getPlayer()->addTerritory(t);
        }

        // this->isConquering();
    }
    // else
    // {

    //     cout << "Cheater has already conquered this round!" << endl;
    // }

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
