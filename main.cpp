#include <iostream>

#include "MapDriver.hpp"
#include "OrderDriver.hpp"
#include "PlayerDriver.hpp"
#include "CardsDriver.hpp"
#include "CommandProcessing.h"
#include "CommandProcessingDriver.h"
#include "OrderDriver.hpp"
#include "PlayerStrategiesDriver.h"
#include "TournamentDriver.h"

int main(int argc, const char * argv[]) {
    /*

    TestDeploy();
    TestAdvance();
    TestNegociate();
    TestBlockade();
   CommandProcessorDriver();
    testGameStates();
    */
    cout << argv[1];
    if (argc == 2) {
    
            TestPlayerAggressive();
            TestPlayerBenevolent();
            TestPlayerCheater();
            testTournament();
            exit(0);
  
    }
    cout << "******************** Game will start ******************* \n" << endl;
    GameEngine* ge = new GameEngine(false, "");
    ge->StartupPhase();
    ge->mainGameLoop();
    exit(0);
    //CommandProcessorDriver();
}
