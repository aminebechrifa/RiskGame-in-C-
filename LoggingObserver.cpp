#include "LoggingObserver.h"
#include <iostream>

Observer::~Observer()
{
}
Observer::Observer()
{
}
LogObserver::LogObserver() {
}

Subject::Subject() {
	_observers = new list<Observer*>;
}
Subject::~Subject() {
	delete _observers;
}
void Subject::Attach(Observer* o) {
	_observers->push_back(o);
};
void Subject::Detach(Observer* o) {
	_observers->remove(o);
};
#define DEBUG
void Subject::Notify(ILoggable* logit) {
#ifndef DEBUG
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update(logit);
#endif
};

void LogObserver::Update(ILoggable* logit)
{

	ofstream f;
	f.open("example.txt",  fstream::app);
	f << logit->stringToLog() << endl;
	f.close();
}
