#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
	TElem elem;
	TElem counter;

	BagIterator(const Bag& c);
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
	bool valid_position() const;
};
