#pragma once

#include "Observer.h"
#include "Resource.h"
#include "Visitor.h"
#include "Iterator.h"

#include <stack>
#include <vector>
#include <string>
#include <windows.h>

class Controller;

class SetModel : public Observable {
	friend class Controller;
	friend class SetIterator;
	friend class SmartSetIterator;
public:
	SetModel() : data(NewArray(MIN_CAPACITY)) {}
	int Cardinality();
	void Save() { Accept(&saveVisitor); }

private:
	void Add(int);
	void Expand();

	bool* NewArray(int size);

public:
	Iterator* CreateIterator() { return new SetIterator(*this); }
	Iterator* CreateSmartIterator() { return new SmartSetIterator(*this); }
	void Accept(Visitor*);

private:
	bool* data;
	static const int MIN_CAPACITY = 10;
	int capacity = MIN_CAPACITY;
	int max_elem = -1;

	SaveVisitor saveVisitor;
};

class Controller {
public:
	Controller(SetModel* m) : model(m) {}

	void AddButtonClicked(int val) { model->Add(val); }
	void Save() { model->Save(); }

private:
	SetModel* model;
};

class View : public Observer {
public:
	View(HWND, SetModel*);

	void Update() override;
	void PrintModel();
	void PrintCardinality();

	int GetEditValue() const;

	void ChangeView() { realView = !realView; Update(); }

private:
	HWND hWnd;
	HDC hDc;

	HWND hAddButton;
	HWND hChangeViewButton;
	HWND hSaveButton;
	HWND hEdit;

	SetModel* model;

	bool realView = true;
};
