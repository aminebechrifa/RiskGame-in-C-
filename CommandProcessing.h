

#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include "LoggingObserver.h"

// Subject concrete class 
class Command: public ILoggable , public Subject {
private:
    std::string command;
    std::string effect;
public:
    void setCommand(std::string);
    void setEffect(std::string effect1);
    std::string getCommand();
    std::string getEffect();
    string logging;
    string stringToLog() override;
    LogObserver* lo;

    // constructors 
    Command();
    Command(string s,LogObserver* l);
    // destructor 
    ~Command();
    Command(const Command& g);
    // assignment operator 
    Command& operator=(const Command& g);

    // cout operator
    friend ostream& operator<<(ostream& strm, const Command& com);
};

// subject concrete class 
class CommandProcessor :public  ILoggable, public Subject {

public:
    bool ReadFromFile = false;
   virtual void readCommand();
   LogObserver* lo;
    std::vector<std::pair<std::string, std::pair<std::string, std::string>>> valid_commands_and_their_transitions_vector;
    std::vector<std::string> possible_valid_commands_vector;
    std::vector<Command*> commands_vector;
    string stringToLog() override;
    int index = 0;

    Command* getCommand();
    std::string validate(Command*, std::string);
    std::string tournament( std::string);

    // default constructor 
    CommandProcessor();

    // constructor 
    CommandProcessor(LogObserver* lo);

    void saveCommand(string c);
};



class FileLineReader {

public:
    FileLineReader();
    ~FileLineReader();
    FileLineReader(const FileLineReader& O);
    std::vector<Command*> commands;
    void readAllFile(string filename,  LogObserver* l);
    int index = 0;
    Command* getNextCommand(string filename, LogObserver* l);
};

class CommandProcessorAdapter : public  CommandProcessor {
public:
    FileLineReader* Fl;
    string filename;
    CommandProcessorAdapter();
    ~CommandProcessorAdapter();
    CommandProcessorAdapter(const CommandProcessorAdapter& O);
    CommandProcessorAdapter(FileLineReader* f,string fl,LogObserver* l);
    void readCommand() override;

};




#endif




