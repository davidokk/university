#include "Visitor.h"
#include "MVC.h"
#include "Resource.h"

#include <fstream>

void SaveVisitor::Visit(SetModel& m) {
	std::ofstream out("set.txt");
	auto it = m.CreateSmartIterator();
	while (!it->IsDone()) {
		out << it->CurrentItem() << " ";
		it->Next();
	}
}
