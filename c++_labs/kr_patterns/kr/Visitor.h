#pragma once

class SetModel;

class Visitor {
public:
	virtual void Visit(SetModel&) = 0;
};

class SaveVisitor : public Visitor {
public:
	void Visit(SetModel&) override; 
};
