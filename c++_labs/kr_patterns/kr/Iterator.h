#pragma once

class Iterator {
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual int CurrentItem() = 0;
};

class SetModel;

class SetIterator : public Iterator {
public:
	SetIterator(const SetModel&);

	int CurrentItem() override;
	void Next() override;
	void First() override;
	bool IsDone() override;

protected:
	const SetModel* model;
	int pos = 0;
};

class SmartSetIterator : public SetIterator {
public:
	SmartSetIterator(const SetModel& m);

	int CurrentItem() override;
	void Next() override;
};
