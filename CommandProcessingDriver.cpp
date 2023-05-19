

#include "CommandProcessingDriver.h"

void CommandProcessorDriver() {
    bool fromfile = false;

        cout << "******************** TestCommandProcessor fromfile ******************* \n" << endl;
        GameEngine* ge = new GameEngine(fromfile,"");
        ge->StartupPhase();
        ge->mainGameLoop();
        exit(0);
        cout << "******************** TestCommandProcessor from command line ******************* \n" << endl;

       ge = new GameEngine(!fromfile,"");
        ge->StartupPhase();
        ge->mainGameLoop();
        return;
}


void CommandProcessorDriver(bool redfromfile,string filename) {


    cout << "******************** TestCommandProcessor according to arg input ******************* \n" << endl;
    GameEngine* ge = new GameEngine(redfromfile,filename);
    
    ge->StartupPhase();
    ge->mainGameLoop();

}