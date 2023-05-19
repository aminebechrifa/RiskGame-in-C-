
#include "Player.hpp"
#include "PlayerStrategies.h"


using namespace std;


list<Territory*> Player::toDefend(){
    return this->ps->toAttack();
};


list<Territory*> Player::toAttack(){
    return this->ps->toAttack();
};

Card* getCard(list<Card*>* l, string card_name) {
        std::list<Card*>::iterator it;
        for (it = (*l).begin(); it != (*l).end(); ++it) {

            if (card_name == (*it)->getCardTypeString()) {
                return (*it);
            }
        }
        return nullptr; 
}

void Player::RemoveTerritory( string teri_name) {
    std::list<Territory*>::iterator it;
    for (it = territories.begin(); it != territories.end(); ++it) {

        if (teri_name == *(*it)->m_name) {
            territories.remove(*it);
            return;
        }
    }

}

Player* Player::getplayer(list<Player*> l, string playername) {
    std::list<Player*>::iterator it;
    for (it = l.begin(); it != l.end(); ++it) {

        if (playername == *(*it)->m_name) {
            return (*it);
        }
    }
    return nullptr;
}
std::list<Territory*> Player::getAllTerritories(list<Player*> l) {
    std::list<Player*>::iterator it;
    std::list<Territory*> ter;

    for (it = l.begin(); it != l.end(); ++it) {
        std::list<Territory*>::iterator itTer;
        
        for (itTer = (*it)->territories.begin(); itTer != (*it)->territories.end(); ++itTer)
        ter.insert(ter.begin(), (*itTer));


        for (itTer = Neutral->territories.begin(); itTer != Neutral->territories.end(); ++itTer)
            ter.insert(ter.begin(), (*itTer));
    }
    return ter;
}

bool isNumber(const string& s)
{
    for (char const& ch : s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}
bool Player::issueOrder() {
    return  ps->issueOrder();
}

void Player::execDeploy() {
    std::list<Order*>::iterator it= orders->order_list.begin();

    while (it != orders->order_list.cend())
    {
        list<Order*>::iterator curr = it++;
        if (*(*curr)->get_type() == "deploy") {
            (*curr)->execute();
            orders->order_list.erase(curr);
        }
    }
   
    }
   
   

 Player::Player(const Player& player){
     m_name = new string(*player.m_name);
     territories = list<Territory*>(player.territories);
     cards =  list<Card*>(player.cards);
     orders =new  OrdersList(*player.orders);
     hand = new Hand(*(player.hand));

}

Player::Player(){
    m_name = new string();
    hand = new Hand();
     territories = list<Territory*>();;
     cards = list<Card*>();
     orders= new OrdersList();

}; //default constructor

Player::Player(string name): Player( name,"Human") {}

Player::Player(string name,string strat){
    m_name = new string(name);
    hand = new Hand();
     territories = list<Territory*>();;
     cards = list<Card*>();
     orders=new  OrdersList();
     if (strat == "human") {
         ps = new HumanPlayerStrategy(this);
     }   if (strat == "aggressive") {
         ps = new AggressivePlayerStrategy(this);
     }   if (strat == "benevolent") {
         ps = new BenevolentPlayerStrategy(this);
     }   if (strat == "neutral") {
         ps = new NeutralPlayerStrategy(this);

     } if (strat == "cheater") {
         ps = new CheaterPlayerStrategy(this);

     }

}; // constructor

Player::~Player() {
    delete m_name;//deallocate
    m_name = nullptr; // avoid dangling pointers
    delete hand;
    hand = nullptr;
    for (std::list<Territory*>::iterator it = territories.begin(); it != territories.end(); ++it) {
        delete *it;
        *it= nullptr;
    }
    for (std::list<Card*>::iterator it = cards.begin(); it != cards.end(); ++it) {
        delete *it;
        *it= nullptr;
    }
    for (std::list<Order*>::iterator it = orders->order_list.begin(); it != orders->order_list.end(); ++it) {
        delete *it;
        *it= nullptr;
    }

}

//cout operator
ostream& operator<<(ostream &strm, const Player& player) {
   return strm << "Player Name " << *player.m_name ;};

// assignment operator 
Player& Player::operator=(const Player &player)
 {
  
    this->m_name = new string(*player.m_name);
    this-> territories = list<Territory*>(player.territories);
    this->cards =  list<Card*>(player.cards);
    this->orders =orders;
    this->hand = new Hand(*(player.hand));
   return *this;};


