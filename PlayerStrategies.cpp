#pragma once
#include "PlayerStrategies.h"
#include "Player.hpp"


using namespace std;


// HumanPlayerStrategy function definitions : 

// concrete method issue order 
bool HumanPlayerStrategy::issueOrder() {
    cout << "Player : " << *p->m_name << " Turn started  " << endl;
    if (*p->armies > *p->deployed_inTurn) {
        while (true) {
            cout << "Player : " << *p->m_name << " has " << *p->armies - *p->deployed_inTurn << endl;
            cout << "Possible action are  : deploy ( command :deploy territory_name nbr_army)  " << endl;
          
            // getting the command from the user or the file 
            p->currentCommand = p->cP->getCommand();
            if (p->currentCommand->getCommand() == "nullptr")
                return false;
            string command = p->currentCommand->getCommand();
            string com = string(command.substr(0, command.find(" ")));
            string arg = string(command.substr(command.find(" ") + 1));
            string territory_name = string(arg.substr(0, arg.find(" ")));
            string  nbr_armies = string(arg.substr(arg.find(" ") + 1));


            // verifying the possibility for the deploy 
            if (isNumber(nbr_armies) && getTerritory(p->territories, territory_name) != nullptr) {
                int i = std::stoi(nbr_armies);
                *p->deployed_inTurn = *p->deployed_inTurn + i;
                p->orders->addOrder(new Deploy(p, i, getTerritory(p->territories, territory_name), p->currentCommand, p->lo));

                return true;
            }
           p->currentCommand->setEffect("The command written is error either territory does not exist or armies is not digit");
            cout << "The command written is error either territory does not exist or armies is not digit" << endl;
        }
    }

    //checking for other command (not deploy)
    while (true) {
        //Advance(Player* p, Territory* Source, int t, Territory* Destination) : Order(p)
        cout << "Player : " << *p->m_name << " has " << *p->armies - *p->deployed_inTurn << endl;
        cout << "Possible action are  : advance  (command :advance territory_owned nbr_army ter_desti) ";
        // getting the command from the user or the file 
        Card* card = getCard(p->hand->pHandList, "Bomb");
        if (card != nullptr)
            cout << ", bomb  (command :bomb ter_desti) ";

        card = getCard(p->hand->pHandList, "Airlift");
        if (card != nullptr)
            cout << ", airlift  (command :airlift territory_owned nbr_army ter_desti) ";

        card = getCard(p->hand->pHandList, "Blockade");
        if (card != nullptr)
            cout << ", blockade  (command :blockade ter_desti) ";
        card = getCard(p->hand->pHandList, "Diplomacy");
        if (card != nullptr)
            cout << ", blockade  (command :negociate player_NAME) ";;

        cout << ", end (to choose not to make another turn ) ";;

        cout << endl;

        // getting the choice from the user again 
        p->currentCommand = p->cP->getCommand();
        if (p->currentCommand->getCommand() == "nullptr")
            return false;
        string command = p->currentCommand->getCommand();

        string com = string(command.substr(0, command.find(" ")));
        string arg = string(command.substr(command.find(" ") + 1));

        // creating the order after parsing 
        if (com == "advance" || com == "airlift") {

            string territory_name = string(arg.substr(0, arg.find(" ")));
            arg = string(arg.substr(arg.find(" ") + 1));
            string nbr_armies = string(arg.substr(0, arg.find(" ")));
            string destination = string(arg.substr(arg.find(" ") + 1));

     
            if (com == "advance") {
                p->orders->addOrder(new Advance(p, getTerritory(p->getAllTerritories(p->AllPlayers), territory_name), std::stoi(nbr_armies), getTerritory(p->getAllTerritories(p->AllPlayers), destination), p->currentCommand, p->lo));
                return true;;
            }
            if (com == "airlift") {
                p->orders->addOrder(new Airlift(p, getTerritory(p->getAllTerritories(p->AllPlayers), territory_name), std::stoi(nbr_armies), getTerritory(p->getAllTerritories(p->AllPlayers), destination), p->currentCommand, p->lo));
                return true;;
            }
        }

        if (com == "blockade") {
            // checking for cards
            card = getCard(p->hand->pHandList, "blockade");
            if (card != nullptr) {
                p->orders->addOrder(new Blockade(p, getTerritory(p->getAllTerritories(p->AllPlayers), arg), p->currentCommand, p->lo));
                p->hand->removeCard("blockade");
                return true;
            }
        }
        if (com == "negociate") {
            // checking for cards
            card = getCard(p->hand->pHandList, "negociate");
            if (card != nullptr) {
                p->orders->addOrder(new Negotiate(p, p->getplayer(p->AllPlayers, arg), p->currentCommand, p->lo));
                p->hand->removeCard("negociate");
                return true;
            }
        }
        if (com == "bomb") {
            // checking for cards
            card = getCard(p->hand->pHandList, "bomb");
            if (card != nullptr) {
                p->orders->addOrder(new Bomb(p, getTerritory(p->getAllTerritories(p->AllPlayers), arg), p->currentCommand, p->lo));
                p->hand->removeCard("bomb");
                return true;;
            }
        }

        if (com == "end") {

            p->currentCommand->setEffect("ending the issue order phase");
            return false;
        }

    }
    // setting the effect 
    p->currentCommand->setEffect("Player does not own the card he tried to play");
    cout << "Player does not own the card he tried to play" << endl;
    return true;
}

// todefend 
list<Territory*> HumanPlayerStrategy::toDefend()
{
    return list<Territory*>();
}

//toAttack
list<Territory*> HumanPlayerStrategy::toAttack()
{
    return list<Territory*>();
}

//default constructor
HumanPlayerStrategy::HumanPlayerStrategy()
{
}

//destructor
HumanPlayerStrategy::~HumanPlayerStrategy()
{
}

// constructor 
HumanPlayerStrategy::HumanPlayerStrategy(Player* p) : PlayerStrategy(p) {

}

// outpuit stream operator 
ostream& operator<<(ostream& strm, const HumanPlayerStrategy& O) {
    return strm << "Human Strategy" << endl;
}


//assignment operator 
HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& O) {
    PlayerStrategy :: operator = (O);
    return *this;
}

// copy constructor 
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& O) : PlayerStrategy(O) {

}

/*-------------------------------------------------------------------------------------------*/

// Player strategy abstract class 
// constructors 
PlayerStrategy::PlayerStrategy()
{
}
PlayerStrategy::PlayerStrategy(Player* player) {
    p = player;
}
// destructor 
PlayerStrategy::~PlayerStrategy()
{
    // the player pointer should not be freed here , as we need to point to it even after the scope of the strategy
}

// assignment operator 
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& O) {
    p = new Player(*O.p);
    return *this;
}

// copy constructor 
PlayerStrategy::PlayerStrategy(const PlayerStrategy& O) {
    p = new Player(*O.p);
}



/*-------------------------------------------------------------------------------------------*/


// issue order 
bool AggressivePlayerStrategy::issueOrder() {
    cout << "AgressivePlayer : " << *p->m_name << " Turn started  " << endl;
    if (*p->armies > *p->deployed_inTurn) {
        while (true) {
            Territory* t=new Territory();
            t->armies =new int(-1);
                std::list<Territory*>::iterator it;
            
                // the aggressive player is looking for his strongest territory to assign all the army to it 
            for (it = p->territories.begin(); it != p->territories.end(); ++it) {

                if (*t->armies < *(*it)->armies) {
                    t = (*it);
                }
            }
                p->orders->addOrder(new Deploy(p, *p->armies,t, p->currentCommand, p->lo));
                cout << "Agressive player ordered deployed : " << (*p->armies) <<"  to territory "<< (*t->m_name) << endl;
                p->deployed_inTurn = new int(*p->armies);
                return true;
        }
    }

    // getting the command from the user or the file 
        Card* card = getCard(p->hand->pHandList, "Bomb");
        if (card != nullptr) {
            cout << ", bomb   ";

            // the aggressive player checks for a bomb card to play it 
            std::list<Territory*>::iterator it;
            std::list<Territory*>::iterator itAdj;
            Territory* t = new Territory();

            // the aggressive player looks for the strongest territory to bomb 
            t->armies = new int(0);
            for (it = p->territories.begin(); it != p->territories.end(); ++it) {
                for (itAdj = (*it)->m_Connections.begin(); itAdj != (*it)->m_Connections.end(); ++itAdj) {
                    if (*t->armies < *(*itAdj)->armies) {
                        t = (*itAdj);
                    }
                }
            }
            p->orders->addOrder(new Bomb(p,  t ,p->currentCommand, p->lo));
            p->hand->removeCard("bomb");
            cout << "Agressive player ordered Bomb : " << t << " to territory " << (*t->m_name) << endl;
            return true;;
        }
         

        else{
           
        // the aggressive player looks for his strongest territory with the weakest adjacent to advance on 
            std::list<Territory*>::iterator it;
            std::list<Territory*>::iterator itAdj;
            Territory* t = new Territory();
            t->armies = new int(50000000);
            for (it = p->territories.begin(); it != p->territories.end(); ++it) {
                for (itAdj = (*it)->m_Connections.begin(); itAdj != (*it)->m_Connections.end(); ++itAdj) {
                    if (*(*itAdj)->armies < *(t)->armies) {
                        t = (*itAdj);
                    }
                }
            }

            Territory* Attackant = p->territories.front() ;
            for (it = p->territories.begin(); it != p->territories.end(); ++it) {
                if (*(*it)->armies != 0) {
                    if ((*it)->isAdjacent(t)) {
                        if (Attackant->isAdjacent(t)) {
                            if (*Attackant->armies < *(*it)->armies) {
                                Attackant = (*it);
                            }
                        }
                        else {
                            Attackant = (*it);
                        }
                    }
                }
            }
            if (*Attackant->armies != 0) {
                p->orders->addOrder(new Advance(p, Attackant, *Attackant->armies, t, p->currentCommand, p->lo));

                cout << "Agressive player ordered Advanced : " << *Attackant->armies << " to territory " << (*t->m_name) << endl;
            }
            else {
                cout << "Agressive player does not issue orders " << endl;
            }
            return true;;
        }




   
    return true;
}

// to defend 
list<Territory*> AggressivePlayerStrategy::toDefend()
{
    return list<Territory*>();
}

// to attack 
list<Territory*> AggressivePlayerStrategy::toAttack()
{
    return list<Territory*>();
}

// default constuctor 
AggressivePlayerStrategy::AggressivePlayerStrategy()
{
}
// destructor 
AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
}
// constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p) {

}
// output stream operator 
ostream& operator<<(ostream& strm, const AggressivePlayerStrategy& O) {
    return strm << "AggressivePlayerStrategy" << endl;
}
// assignment operator 
AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& O) {
    PlayerStrategy :: operator = (O);
    return *this;
}
// copy constructor 
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& O) : PlayerStrategy(O) {

}






/*-------------------------------------------------------------------------------------------*/
// BenevolentPlayerStrategy functions definitions 


// issue order 

bool BenevolentPlayerStrategy::issueOrder() {
    cout << "BenevolentPlayer : " << *p->m_name << " Turn started  " << endl;
    if (*p->armies >*p->deployed_inTurn) {
        while (true) {
            Territory* t = new Territory();
            t->armies = new int(5000000);
            std::list<Territory*>::iterator it;
            // benevolant player looks for the weakest territory to put his army on 
            for (it = p->territories.begin(); it != p->territories.end(); ++it) {

                if (*t->armies > *(*it)->armies) {
                    t = (*it);
                }
            }
            p->orders->addOrder(new Deploy(p, *p->armies, t, p->currentCommand, p->lo));
            cout << "Benevolent  player ordered deployed : " << (*p->armies) << "to territory " << (*t->m_name) << endl;
            p->deployed_inTurn = new int(*p->armies);
            return true;
        }
    }

    // getting the command from the user or the file 
    Card* card = getCard(p->hand->pHandList, "airlift");
    if (card != nullptr) {
        cout << ", airlift   ";

   
        std::list<Territory*>::iterator it;  
        Territory* from=new Territory();
        from->armies = new int(-10);
       Territory*  to = new Territory();;
       to->armies = new int(10000000);
       for (it = p->territories.begin(); it != p->territories.end(); ++it) {
          

           if (*to->armies > *(*it)->armies) {
               to = (*it);
           }
           if (*from->armies < *(*it)->armies) {
               from = (*it);
           }

       }

        p->orders->addOrder(new Airlift(p, from, int((*from->armies)/2 ),to,p->currentCommand, p->lo));
        p->hand->removeCard("airlift");
        cout << "BenevolentPlayer player ordered Airlift : " << "to territory " << (*to ->m_name) << endl;
        return true;;
    }
    card = getCard(p->hand->pHandList, "Diplomacy");
    if (card != nullptr) {


        // benevolant player plays diplomacy card if he has it 
        std::list<Player*>::iterator itp;
        Player* pla= p->AllPlayers.front();
        int stop = rand() % p->AllPlayers.size();
            for (itp = p->AllPlayers.begin(); itp != p->AllPlayers.end(); ++itp) {
                stop--;
                if (stop == 0) {
                    pla = (*itp);
                }
            }
        p->orders->addOrder(new Negotiate(p, pla, p->currentCommand, p->lo));
        p->hand->removeCard("diplomacy");
        cout << "BenevolentPlayer player ordered Diplomacy : " << "to territory " << (*pla->m_name) << endl;
        return true;;
    }
    


    else {

        // benevolant player tries to advance from a strong territory he has to a weak territory he has 
        std::list<Territory*>::iterator it;
        std::list<Territory*>::iterator itAdj;
        Territory* from = new Territory();
        Territory* to = new Territory();
            to->armies=new int(10);
            from->armies=new int(10);

        for (it = p->territories.begin(); it != p->territories.end(); ++it) {
            for (itAdj = p->territories.begin(); itAdj != p->territories.end(); ++itAdj) {
                if ((*it)->isAdjacent((*itAdj))) {
                    int diff = *(*itAdj)->armies - *(*it)->armies;
                    if (diff > (to - from)) {
                        if (*(*itAdj)->armies > *(*it)->armies) {
                            to = (*it);
                            from = (*itAdj);
                        }
                        else {
                            to = (*itAdj);
                            from = (*it);
                        }
                    }
                }

              
            
            }
        }

     

        p->orders->addOrder(new Advance(p, from, *from->armies/2, to, p->currentCommand, p->lo));

        cout << "Benevolent  player ordered advance : " << *from->armies / 2 << " to territory " << (*to->m_name) << endl;
        return true;;
    }





    return true;
}

// to defend 
list<Territory*> BenevolentPlayerStrategy::toDefend()
{
    return list<Territory*>();
}

// to attack 
list<Territory*> BenevolentPlayerStrategy::toAttack()
{
    return list<Territory*>();
}

// default constructor 
BenevolentPlayerStrategy::BenevolentPlayerStrategy()
{
}
// destructor 
BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{
}
// constructor 
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) : PlayerStrategy(p) {

}

// output stream operator 
ostream& operator<<(ostream& strm, const BenevolentPlayerStrategy& O) {
    return strm << "BenevolentPlayerStrategy" << endl;
}

// assignment operator 
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& O) {
    PlayerStrategy :: operator = (O);
    return *this;
}

// cpy constructor 
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& O) : PlayerStrategy(O) {

}





/*-------------------------------------------------------------------------------------------*/
// NeutralPlayerStrategy functions definitions 

// issueorder 
bool NeutralPlayerStrategy::issueOrder() {
    cout << "NeutralPlayer : " << *p->m_name << " Turn started  " << endl;


    // neutral player check =s if any of the other player =s issued an attack on him and will transform into an agressive palyer in that case 
    std::list<Player*>::iterator it;
    std::list<Order*>::iterator ito;
    for (it = p->AllPlayers.begin(); it != p->AllPlayers.end(); ++it) {
        
        for (ito = (*it)->orders->order_list.begin(); ito != (*it)->orders->order_list.end(); ++ito) {

            if (*(*ito)->orderName == "advance") {
                if (( *((Advance*)(*ito))->Desti->player_owner == *p->m_name))
                p->ps = new AggressivePlayerStrategy(p);
                return true;
            }
            if (*(*ito)->orderName == "bomb") {
                if ((*((Bomb*)(*ito))->Desti->player_owner == *p->m_name))
                    p->ps = new AggressivePlayerStrategy(p);
                return true;
            }
            // neutral player was not attacked he will do nothing 
            
    }
        cout << "neutral player  : was not attacked then he will do nothing  " << endl;

     
        return true;;
    }





    return true;
}

// to defend 
list<Territory*> NeutralPlayerStrategy::toDefend()
{
    return list<Territory*>();
}

// to attack 
list<Territory*> NeutralPlayerStrategy::toAttack()
{
    return list<Territory*>();
}

// default constructor 
NeutralPlayerStrategy::NeutralPlayerStrategy()
{
}
// destructor 
NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
}
// constructor 
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) : PlayerStrategy(p) {

}

// assignment operator 
NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& O) {
    PlayerStrategy :: operator = (O);
    return *this;
}





/*-------------------------------------------------------------------------------------------*/
// NeutralPlayerStrategy functions definitions 


// issue order 
bool CheaterPlayerStrategy::issueOrder() {
    cout << "CheaterPlayer : " << *p->m_name << " Turn started  " << endl;

    // cheater player will check if he already advanced on a territory , if not he will cheat advance on a territory and conquert it once it is executed 
    if (p->orders->order_list.size() == 0) {
        std::list<Territory*>::iterator it;
        std::list<Territory*>::iterator ito;
        Territory* t = new Territory();
        Territory* src = new Territory();
        t->armies = new int(-1);
        for (it = p->territories.begin(); it != p->territories.end(); ++it) {
            for (ito = (*it)->m_Connections.begin(); ito != (*it)->m_Connections.end(); ++ito) {
                if ((*t->armies < *(*ito)->armies) && (*(*ito)->player_owner != *p->m_name)) {
                    t = (*ito);
                    src = (*it);
                }
            }
        }
        cout << "CheaterPlayer : issued a cheater advance on " << *t->m_name  << endl;

        p->orders->addOrder(new Advance(p, src, 0, t, p->currentCommand, p->lo, true));
    }
    else {
        cout << "CheaterPlayer : already cheating last issueorder wont cheat this issueorder  " << endl;

    }
        return true;;
    }



// to defend 
list<Territory*> CheaterPlayerStrategy::toDefend()
{
    return list<Territory*>();
}

// to attack 
list<Territory*> CheaterPlayerStrategy::toAttack()
{
    return list<Territory*>();
}

// default constructor 
CheaterPlayerStrategy::CheaterPlayerStrategy()
{
}
// destructor 
CheaterPlayerStrategy::~CheaterPlayerStrategy()
{
}

// constructor 
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p) : PlayerStrategy(p) {

}

// assignment operator 
CheaterPlayerStrategy& CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy& O) {
    PlayerStrategy :: operator = (O);
    return *this;
}

// constructor 
CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& O) : PlayerStrategy(O) {

}
