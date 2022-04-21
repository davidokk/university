#include "Iterator.h"
#include "MVC.h"

SetIterator::SetIterator(const SetModel& sm) : model(&sm) {}

int SetIterator::CurrentItem() { return model->data[pos]; }

void SetIterator::Next() { ++pos; }

void SetIterator::First() { pos = 0; }

bool SetIterator::IsDone() { return pos > model->max_elem; }

SmartSetIterator::SmartSetIterator(const SetModel& m) : SetIterator(m) {
	while (model->data[pos] == false)
		++pos;
}

int SmartSetIterator::CurrentItem() { return pos; }

void SmartSetIterator::Next() {
	++pos;
	while (model->data[pos] == false)
		++pos;
}