#include "PlayerStrategiesDriver.h"
#include "PlayerStrategies.h"
#include "Player.hpp"
#include <iostream>


using namespace std;
void TestPlayerAggressive() {

    //setting up 
    cout << "\n******************** Test AgressivePlayer and neutral player  ******************* \n" << endl;

    // creating player 
    Player* a = new Player("a", "neutral");
    Player* b = new Player("b", "aggressive");
    b->hand->addCardHand(new Card("Bomb"));


    // setting up territories and what is needed for the order to execute 
    a->lo = new LogObserver();
    a->currentCommand = new Command();
    a->armies = new int(50);
    a->deployed_inTurn = new int(0);
    b->armies = new int(50);
    b->deployed_inTurn = new int(0);
    a->AllPlayers.insert(a->AllPlayers.begin(), b);
    a->AllPlayers.insert(a->AllPlayers.begin(), a);


    // creating territories and linking them 
    b->AllPlayers = a->AllPlayers;
    Territory* t__1 = new Territory();
    t__1->m_name = new string("t_1");
    Territory* t__2 = new Territory();
    t__2->m_name = new string("t_2");
    t__1->m_Connections.insert(t__1->m_Connections.begin(), t__2);
    t__2->m_Connections.insert(t__2->m_Connections.begin(), t__1);
    a->territories.insert(a->territories.begin(), t__1);
    b->territories.insert(b->territories.begin(), t__2);
    t__1->player_owner = a->m_name;
    t__2->player_owner = b->m_name;

    Territory* t__3 = new Territory();
    t__3->m_name = new string("t_3");
    Territory* t__4 = new Territory();
    t__4->m_name = new string("t_4");
    t__3->m_Connections.insert(t__3->m_Connections.begin(), t__4);
    t__4->m_Connections.insert(t__4->m_Connections.begin(), t__3);
    a->territories.insert(a->territories.begin(), t__3);
    b->territories.insert(b->territories.begin(), t__4);
    t__3->player_owner = a->m_name;
    t__4->player_owner = b->m_name;
    a->armies = new int(60);

    // issuing order for each of the player and execute orders 
    a->issueOrder();
    b->issueOrder();
    a->execDeploy();
    b->execDeploy();
    a->issueOrder();
    b->issueOrder();
    b->orders->order_list.front()->execute();
    a->issueOrder();
    b->issueOrder();
}



void TestPlayerBenevolent() {
    // setting up 
    cout << "\n******************** Test benevolent and neutral player  ******************* \n" << endl;

    //adding players 
    Player* a = new Player("a", "neutral");
    Player* b = new Player("b", "benevolent");

    // setting up territories and what is needed for the order to execute 
    b->hand->addCardHand(new Card("Diplomacy"));
    a->lo = new LogObserver();
    a->currentCommand = new Command();
    a->armies = new int(50);
    a->deployed_inTurn = new int(0);
    b->armies = new int(50);
    b->deployed_inTurn = new int(0);
    a->AllPlayers.insert(a->AllPlayers.begin(), b);
    a->AllPlayers.insert(a->AllPlayers.begin(), a);


    // creating territories and linking them 
    b->AllPlayers = a->AllPlayers;
    Territory* t__1 = new Territory();
    t__1->m_name = new string("t_1");
    Territory* t__2 = new Territory();
    t__2->m_name = new string("t_2");
    t__1->m_Connections.insert(t__1->m_Connections.begin(), t__2);
    t__2->m_Connections.insert(t__2->m_Connections.begin(), t__1);
    a->territories.insert(a->territories.begin(), t__1);
    b->territories.insert(b->territories.begin(), t__2);
    t__1->player_owner = a->m_name;
    t__2->player_owner = b->m_name;

    Territory* t__3 = new Territory();
    t__3->m_name = new string("t_3");
    Territory* t__4 = new Territory();
    t__4->m_name = new string("t_4");
    t__3->m_Connections.insert(t__3->m_Connections.begin(), t__4);
    t__4->m_Connections.insert(t__4->m_Connections.begin(), t__3);
    a->territories.insert(a->territories.begin(), t__3);
    b->territories.insert(b->territories.begin(), t__4);
    t__3->player_owner = a->m_name;
    t__4->player_owner = b->m_name;
    a->armies = new int(60);


    // issuing order for each of the player and execute orders 
    a->issueOrder();
    b->issueOrder();
    a->execDeploy();
    b->execDeploy();
    a->issueOrder();
    b->issueOrder();
    b->orders->order_list.front()->execute();
    a->issueOrder();
    b->issueOrder();
}


void TestPlayerCheater() {
    // setting up 
    cout << "\n******************** Test benevolent and neutral player  ******************* \n" << endl;

    // adding players 
    Player* a = new Player("a", "neutral");
    Player* b = new Player("b", "cheater");

    // setting up territories and what is needed for the order to execute 
    a->lo = new LogObserver();
    a->currentCommand = new Command();
    a->armies = new int(50);
    a->deployed_inTurn = new int(0);
    b->armies = new int(50);
    b->deployed_inTurn = new int(0);
    a->AllPlayers.insert(a->AllPlayers.begin(), b);
    a->AllPlayers.insert(a->AllPlayers.begin(), a);

   
    // creating territories and linking them 
    b->AllPlayers = a->AllPlayers;
    Territory* t__1 = new Territory();
    t__1->m_name = new string("t_1");
    Territory* t__2 = new Territory();
    t__2->m_name = new string("t_2");
    t__1->m_Connections.insert(t__1->m_Connections.begin(), t__2);
    t__2->m_Connections.insert(t__2->m_Connections.begin(), t__1);
    a->territories.insert(a->territories.begin(), t__1);
    b->territories.insert(b->territories.begin(), t__2);
    t__1->player_owner = a->m_name;
    t__2->player_owner = b->m_name;

    Territory* t__3 = new Territory();
    t__3->m_name = new string("t_3");
    Territory* t__4 = new Territory();
    t__4->m_name = new string("t_4");
    t__3->m_Connections.insert(t__3->m_Connections.begin(), t__4);
    t__4->m_Connections.insert(t__4->m_Connections.begin(), t__3);
    a->territories.insert(a->territories.begin(), t__3);
    b->territories.insert(b->territories.begin(), t__4);
    t__3->player_owner = a->m_name;
    t__4->player_owner = b->m_name;
    a->armies = new int(60);

    // issuing order for each of the player and execute orders 
    a->issueOrder();
    b->issueOrder();
    a->execDeploy();
    b->execDeploy();
    a->issueOrder();
    b->issueOrder();
    b->orders->order_list.front()->execute();
    a->issueOrder();
    b->issueOrder();
}