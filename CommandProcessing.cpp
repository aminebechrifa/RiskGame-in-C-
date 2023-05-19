using namespace std;
#include <iostream>
#include <utility>
#include "string"
#include "CommandProcessing.h"


// default constructor
Command::Command() {

}

// constructor 
Command::Command(string s,LogObserver* l ) {
    command = s;
    lo = l;
    Attach(lo);
}

// destructor 
Command::~Command()
{
}


;// copy constructor 
Command::Command(const Command& g) {
    command = g.command;
    effect = g.effect;

}

//assugnment operator 
Command& Command::operator=(const Command& g)
{
    command = g.command;
    effect = g.effect;
    return     *this;;
}

// setting the private member command 
void Command::setCommand(std::string command1) {
    command = command1;
}

// setting the effect 
void Command::setEffect(std::string effect1){

    effect = effect1;
    Notify(this);
}

// getters : 

string Command::getCommand(){
    return command;
}

string Command::getEffect(){
    return effect;
}

string Command::stringToLog()
{
    return "the command : <"+getCommand()+"> was set with the following effect <"+getEffect()+">";
}


// output stream operator 

ostream& operator<<(ostream& strm, const Command& a) {
    return strm << "command : " << a.command;
}

/* -----------------------------------------------------------------------------------------------*/
// command processor function definitions 


//validate if the command can be done or not 

string CommandProcessor::stringToLog()
{
    return "this command : <"+commands_vector.back()->getCommand()+"> was saved to the command vector";
}

CommandProcessor::CommandProcessor(LogObserver* l) {   lo = l;
    possible_valid_commands_vector = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" ,"deploy","advance","negotiate","bomb","airlift","issueorders","execorder","end","tournament","continue","notcontinue"};
    valid_commands_and_their_transitions_vector.emplace_back("start", make_pair("loadmap", "maploaded"));
    valid_commands_and_their_transitions_vector.emplace_back("maploaded", make_pair("loadmap", "maploaded"));
    valid_commands_and_their_transitions_vector.emplace_back("maploaded", make_pair("validatemap", "mapvalidated"));
    valid_commands_and_their_transitions_vector.emplace_back("mapvalidated", make_pair("addplayer", "playersadded"));
    valid_commands_and_their_transitions_vector.emplace_back("playersadded", make_pair("addplayer", "playersadded"));
    valid_commands_and_their_transitions_vector.emplace_back("playersadded", make_pair("gamestart", "assignreinforcement"));
    valid_commands_and_their_transitions_vector.emplace_back("assignreinforcement", make_pair("issueorder", "issueorders"));
    valid_commands_and_their_transitions_vector.emplace_back("issueorders", make_pair("issueorder", "issueorders"));
    valid_commands_and_their_transitions_vector.emplace_back("issueorders", make_pair("endissueorders", "executeorders"));
    valid_commands_and_their_transitions_vector.emplace_back("executeorders", make_pair("execorder", "executeorders"));
    valid_commands_and_their_transitions_vector.emplace_back("executeorders", make_pair("endexecorders", "assignreinforcement"));
    valid_commands_and_their_transitions_vector.emplace_back("executeorders", make_pair("win", "win"));
    valid_commands_and_their_transitions_vector.emplace_back("win", make_pair("replay", "start"));
    valid_commands_and_their_transitions_vector.emplace_back("win", make_pair("quit", "exit program"));
    Attach(l);
}

void CommandProcessor::readCommand() {
    
    string temp_str;
    cout << "Please enter commands one after the other" << endl;
    while(true){
 
        std::getline(std::cin, temp_str);


        string com = string(temp_str.substr(0, temp_str.find(" ")));

        // in case the command is tournament , the method tournament is called to fill the command vector 
        if (com == "tournament") {
            tournament(temp_str);
            return;
        }
        if (com == "exit") {
            exit(0);
            return;
        }
        if (find(possible_valid_commands_vector.begin(), possible_valid_commands_vector.end(), com) != possible_valid_commands_vector.end()){
            saveCommand(temp_str);
            cout << "Valid command. Successfully entered." << endl;
            return;
        }
        else {
            cout << "The command that you entered was an invalid command. Please enter another command" << endl;
        }
    }


}

// return the command from the command vector 
Command* CommandProcessor::getCommand(){
    

    if (index == commands_vector.size()) {
        readCommand();
    }
    index++;
    if (index > commands_vector.size())
        return nullptr;
    std::cout <<"COMMAND ENTERED : ------ - "<< commands_vector[index - 1]->getCommand() << "------------"<<endl;
    if (commands_vector[index - 1]->getCommand() == "exit")
        exit(0);
    return commands_vector[index-1];

}

// validate if the command can be done in this state 
std::string CommandProcessor::validate(Command* command1, std::string state )
{
    std::vector<pair<string, string>> value_vector;
    for (auto it = valid_commands_and_their_transitions_vector.begin(); it != valid_commands_and_their_transitions_vector.end(); ++it) {
        if (it->first == state) {
            value_vector.emplace_back(it->second);
        }
    }
    for (auto it = value_vector.begin(); it != value_vector.end(); ++it) {
        if (it->first == command1->getCommand()) {
            cout << "Command " << command1 << " has been validated.\nState has been changed to " << it->second << endl;
            state = it->second;
            return state;
        }
        else {
            cout << "Command" << command1 << " could not be validated, state has not changed" << endl;
            return state;
        }
    }
    cout << "ERROR\nThe command could not be validated. State has not changed. Please try again with a different command" << endl;
    return state;
}


/* the tornament method will take the argument of the tournament command and generate accordingly a list of commands that will be put in the command vector */
std::string CommandProcessor::tournament(std::string)
{
    string t = "tournament -M Map1 Map2 Map3 -P aggressive benevolent neutral cheater -G 4 -D 30";
    string rest=t.substr(t.find("-M")+3);
    string mapstr = rest.substr(0, rest.find("-P") - 1);
    rest = t.substr(t.find("-P") + 3);
    string playerstr = rest.substr(0,rest.find("-G")-1);
    rest = t.substr(t.find("-G") + 3);
    string nbr_gamesstr = rest.substr(0,rest.find("-D")-1);
    rest = t.substr(t.find("-D") + 3);
    string nbr_turnstr = rest;


    string m=string();
    list<string> maps;
    while (mapstr != m){
         m = mapstr.substr(0, mapstr.find(" "));
            mapstr = mapstr.substr( mapstr.find(" ")+1);
            maps.insert(maps.end(), m);
    }

    // parsing the player part in the argument in the tournament command 
    list<string> Players;
    string p = string();
    while (playerstr != p) {
        p = playerstr.substr(0, playerstr.find(" "));
        playerstr = playerstr.substr(playerstr.find(" ") + 1);
        Players.insert(Players.end(), p);
    }
    int nbr_games=stoi(nbr_gamesstr);
    int nbr_turn=stoi(nbr_turnstr);
    
    // start saving the new commands 
    std::list<string>::iterator itmap;
    for (itmap = maps.begin(); itmap != maps.end(); ++itmap) {
        // for each map we are going to do the following :
        for (int f = 0; f < nbr_games; f++) {
            // witout changng map , we are going to play nbr_ games game 
            saveCommand("loadmap " + (*itmap));
            saveCommand("validatemap");
            std::list<string>::iterator itpla;
            int i = 0;
            for (itpla = Players.begin(); itpla != Players.end(); ++itpla) {
                // we are going to add each player 
                saveCommand("addplayer " + (*itpla) + " " + (*itpla) + "player");    
            }
            saveCommand("gamestart");

            for (int k = 0; k != nbr_turn; k++) {
                // we are going to play this number of turns 
                
                saveCommand("issueorders");
                for (int j = 0; j != 3; j++) {
                    // for simplicity, we keep the nbr of choices per turn to 3
                    saveCommand("continue");
                }
                saveCommand("notcontinue");
            }
            // once the game ends , we call replay to start another game 
            saveCommand("replay");
        }
    }
    // once all the game has been played we call exit to exit the program.
    saveCommand("exit");

    return std::string();
}

void CommandProcessor::saveCommand(string c) {

    commands_vector.insert(commands_vector.end(), new Command(c,lo));
    if(c!="nullptr")
    Notify(this);
}
/*--------------------------------------------------File Line reader --------------------------------------------------*/

FileLineReader::FileLineReader()
{

}

FileLineReader::FileLineReader(const FileLineReader& O) {
    commands = vector<Command*>(O.commands);
    index = O.index;
}

FileLineReader::~FileLineReader()
{

    for (std::vector<Command*>::iterator it = commands.begin(); it != commands.end(); ++it) {
        delete* it;
        *it = nullptr;
    }

}

void FileLineReader::readAllFile(string filename,LogObserver* l) {
    std::vector<Command*> local_commands_vector;
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        
        commands.insert(commands.end(), new Command(line,l));
    }
}

Command* FileLineReader::getNextCommand(string filename, LogObserver* l)
{
    if (index == 0) { 
        readAllFile(filename,l );
    }
    index++;
    if (index == commands.size()) {
        cout << "There are no more commands to play the program will exit" << endl;
        return new Command("nullptr",l);
    }
    return commands[index - 1];
}


CommandProcessorAdapter::~CommandProcessorAdapter() {
    delete  Fl;
    Fl = nullptr;
}


CommandProcessorAdapter::CommandProcessorAdapter(const CommandProcessorAdapter& O) : CommandProcessor(O)
{

 Fl  = new   FileLineReader(*O.Fl);
 filename = O.filename;
 
}

CommandProcessorAdapter::CommandProcessorAdapter(FileLineReader* f,string fl,LogObserver* l):CommandProcessor(l) {
    Fl = f;
    filename = fl;
}
void CommandProcessorAdapter::readCommand()
{
    string temp_str= (*Fl).getNextCommand(filename,lo)->getCommand();
    if (temp_str == "nullptr") {
        saveCommand(temp_str);
    }
    string com = string(temp_str.substr(0, temp_str.find(" ")));
    if (find(possible_valid_commands_vector.begin(), possible_valid_commands_vector.end(), com) != possible_valid_commands_vector.end()) {
        saveCommand(temp_str);
        cout << "Valid command. Successfully entered." << endl;
    }
    else {
        cout << "The command that you entered was an invalid command. Please enter another command or type \"END\" once finished." << endl;
    } 
}




