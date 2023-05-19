#include "TournamentDriver.h"

void testTournament()
{
    
        bool fromfile = false;

        cout << "******************** TeESTIGN TORUNEAMENT  fromfile ******************* \n" << endl;;
        cout << "******************** TeESTIGN TORUNEAMENT  fromfile ******************* \n" << endl;;
        cout << "******************** TeESTIGN TORUNEAMENT  fromfile ******************* \n" << endl;;
        cout << "******************** TeESTIGN TORUNEAMENT  fromfile ******************* \n" << endl;;
        cout << "******************** TeESTIGN TORUNEAMENT  fromfile ******************* \n" << endl;;
        GameEngine* ge = new GameEngine(fromfile, "tournament.txt");
        ge->StartupPhase();
        ge->mainGameLoop();
        exit(0);
}
