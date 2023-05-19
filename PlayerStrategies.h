#pragma once 

#include <list>
#include <iostream>
#include <stdio.h>
using namespace std;

class Player;
class Territory;
class OrdersList;


// PlayerStartegy class : virtual
class PlayerStrategy {
public :
	// data member pointer to player 
	Player* p;

	// virtual methods 
	virtual list<Territory*> toDefend()=0;
	virtual list<Territory*> toAttack() = 0;
	virtual bool issueOrder() = 0;

	// constructors 
	PlayerStrategy(); 
	PlayerStrategy(Player* p);

	// destructor 
	virtual ~PlayerStrategy();
	
	// output stream operator 
	friend ostream& operator<<(ostream& strm, const PlayerStrategy& order);
	
	//copy constructor
	PlayerStrategy(const PlayerStrategy& O);

	// assignment operator
	PlayerStrategy& operator=(const PlayerStrategy& O);

};


// concrete strategy class 
class HumanPlayerStrategy : public PlayerStrategy {
public :
	// constructors 
	HumanPlayerStrategy();
	HumanPlayerStrategy(Player* p);

	// destructor
	virtual ~HumanPlayerStrategy();

	// overriden methods 
	bool issueOrder() override;
	virtual list<Territory*> toDefend() override;
	virtual list<Territory*> toAttack() override;

	// output stream operator 
	friend ostream& operator<<(ostream& strm, const HumanPlayerStrategy& order);
	//copy constructor
	HumanPlayerStrategy(const HumanPlayerStrategy& O);

	// assignment operator
	HumanPlayerStrategy& operator=(const HumanPlayerStrategy& O);
};


// concrete strategy class 
class AggressivePlayerStrategy : public PlayerStrategy {
public:
	AggressivePlayerStrategy();
	virtual ~AggressivePlayerStrategy();
	AggressivePlayerStrategy(Player* p);
	bool issueOrder() override;
	virtual list<Territory*> toDefend() override;
	virtual list<Territory*> toAttack() override;
	// output stream operator 
	friend ostream& operator<<(ostream& strm, const AggressivePlayerStrategy& order);
	//copy constructor
	AggressivePlayerStrategy(const AggressivePlayerStrategy& O);

	// assignment operator
	AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy& O);
};



// concrete strategy class 
class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	// constructors 
	BenevolentPlayerStrategy();
	BenevolentPlayerStrategy(Player* p);

	// destructor 
	virtual ~BenevolentPlayerStrategy();

// overriden methods
	bool issueOrder() override;
	virtual list<Territory*> toDefend() override;
	virtual list<Territory*> toAttack() override;

	// output stream operator 
	friend ostream& operator<<(ostream& strm, const BenevolentPlayerStrategy& order);
	//copy constructor
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy& O);

	// assignment operator
	BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy& O);
};


// concrete strategy class 
class NeutralPlayerStrategy : public PlayerStrategy {
public:
	// constructors 
	NeutralPlayerStrategy();
	NeutralPlayerStrategy(Player* p);

	// destructor 
	virtual ~NeutralPlayerStrategy();

	// overriden methods
	bool issueOrder() override;
	virtual list<Territory*> toDefend() override;
	virtual list<Territory*> toAttack() override;

	// output stream operator 
	friend ostream& operator<<(ostream& strm, const NeutralPlayerStrategy& order);

	//copy constructor
	NeutralPlayerStrategy(const NeutralPlayerStrategy& O);

	// assignment operator
	NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& O);
};




// concrete strategy class 
class CheaterPlayerStrategy : public PlayerStrategy {
public:
	// constructors 
	CheaterPlayerStrategy();
	CheaterPlayerStrategy(Player* p);

	// destructors 
	virtual ~CheaterPlayerStrategy();

	// overiden methods 
	bool issueOrder() override;
	virtual list<Territory*> toDefend() override;
	virtual list<Territory*> toAttack() override;

	// output stream operator 
	friend ostream& operator<<(ostream& strm, const CheaterPlayerStrategy& order);
	//copy constructor
	CheaterPlayerStrategy(const CheaterPlayerStrategy& O);

	// assignment operator
	CheaterPlayerStrategy& operator=(const CheaterPlayerStrategy& O);
};