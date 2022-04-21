#pragma once

#include <list>

class Observer {
public:
	virtual void Update() = 0;
};

class Observable {
public:
	void Attach(Observer*);
	void Detach(Observer*);

	void Notify();
private:
	std::list<Observer*> observers;
};
