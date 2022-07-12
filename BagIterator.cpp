#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)      //IMPROVE: fa lista in constructor cu elementele valide
													// si -> restu operatilor vor fi theta(1) in loc de O(n)
{
	this->counter = 0;
	this->elem = this->bag.keys[this->counter];
	while (this->valid_position() == false and this->valid())
	{
		this->counter++;
		this->elem = this->bag.keys[this->counter];
	}
	
}
//WC: Theta(capcity)
//BC: Theta(1)
//O(cap)


void BagIterator::first() {
	this->counter = 0;
	this->elem = this->bag.keys[this->counter];
	while (this->valid_position() == false and this->valid())
	{
		this->counter++;
		this->elem = this->bag.keys[this->counter];
	}
}
//WC: Theta(capcity)
//BC: Theta(1)
//O(cap)

void BagIterator::next() {
	if (this->valid() == false)
		throw exception();
	this->counter++;
	this->elem = this->bag.keys[this->counter];
	if (this->valid_position() != true)
	{
		while (this->valid_position() == false and this->valid())
		{
			this->counter++;
			this->elem = this->bag.keys[this->counter];
		}
	}
}
//WC: Theta(capcity)
//BC: Theta(1)
//O(cap)

bool BagIterator::valid() const {
	//if (this->elem == -1)
	//	return false;
	/*if (this->counter >= 0 and this->counter < this->bag.cap)
		return true;
	else
		return false;*/

	if (this->counter < 0 or this->counter >= this->bag.cap)
		return false;
	else
		return true;

	
}
//Theta(1)
bool BagIterator::valid_position()const
{
	if (this->bag.keys[this->counter] == -111111 and this->bag.next[this->counter] == -111111)
		return false;
	else
		return true;
}
//Theta(1)


TElem BagIterator::getCurrent() const
{
	if(this->valid())
		return this->elem;
}
//Theta(1)