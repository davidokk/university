#include "Observer.h"

void Observable::Attach(Observer* o) { observers.push_back(o); }
void Observable::Detach(Observer* o) { observers.remove(o); }

void Observable::Notify() {
	for (auto& o : observers)
		o->Update();
}
