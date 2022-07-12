#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	
	this->length = 0;
	this->cap = 1;
	this->keys = new TElem[this->cap];
	for (int i = 0; i < this->cap; i++)
	{
		this->keys[i] = NULL_TELEM;
	}
	this->next = new TElem[this->cap];
	for (int i = 0; i < this->cap; i++)
	{
		this->next[i] = NULL_TELEM;
	}
}
//Theta(1)

int Bag::hash(TElem e)
{
	if (e < 0)
		e = -e;
	return e % 307;
	//return floor(this->cap*(double(e) * 0.6180));
}
//Theta(1)


void Bag::add(TElem elem) {
	int pos = this->hash(elem);
	while(this->cap <=pos or this->length==this->cap)   //RESIZE
	{
		int old_cap = this->cap;
		this->cap *= 2;


		TElem* new_keys = new TElem[this->cap];
		TElem* new_next = new TElem[this->cap];
		for (int i = 0; i <old_cap; i++)
		{
			new_keys[i] = this->keys[i];
			new_next[i] = this->next[i];
		}
		for (int i = old_cap ; i < this->cap; i++)
		{
			new_keys[i] = NULL_TELEM;
			new_next[i] = NULL_TELEM;
		}


		delete[] this->keys;
		delete[] this->next;

		this->keys = new_keys;
		this->next = new_next;
	}
	
	
		if (this->keys[pos] == NULL_TELEM)           //the position is free
		{
			this->keys[pos] = elem;
			this->next[pos] = -1;
			this->length++;
		}
		else
		{                                       
			int firstEmpty;
			for (int i = 0; i < this->cap; i++)
			{
				if (this->keys[i] == -111111 and this->next[i] == -111111)
				{
					firstEmpty = i;                                 //find the first empty slot
					break;
				}

			} 
			int current = pos;                        
			while (this->next[current] != -1)                       
				current = this->next[current];
			this->keys[firstEmpty] = elem;
			this->next[firstEmpty] = -1;
			this->next[current] = firstEmpty;
			this->length++;

		}
		
	
}
//O(capacity)


bool Bag::remove(TElem elem) {
	int pos,i,j;
	if (this->search(elem) == false)                 //if we did not found it it maybe in other slot than the one with the hash index
	{
		int position = -1, previous = -1;
		for (int k = 0; k < this->cap; k++)           //so we go an look for it
			if (this->keys[k] == elem)
			{
				position = k;
			}

		if (position == -1)          //if we did not found it => does not exist
			return false;
		else
		{
			for (int k = 0; k < this->cap; k++)
				if (this->next[k] == elem)
				{
					previous = k;        //try finding the previous
				}
			if (previous == -1)  //has no previous(is the last element)
			{
				this->keys[position] = NULL_TELEM;
				this->next[position] = NULL_TELEM;
				this->length--;
				return true;
			}
			else  //has previous 
			{

				if (this->next[position] == -1)          //poition is the las element from that hash
				{
					this->keys[position] = NULL_TELEM;
					this->next[position] = NULL_TELEM;
					this->next[previous] = -1;
					this->length--;
					return true;
				}
				else
				{													//position is between 2 elems in that hash
					j = this->next[position];
					this->keys[position] = this->keys[j];
					this->next[position] = this->next[j];

					this->keys[j] = NULL_TELEM;
					this->next[j] = NULL_TELEM;
					this->length--;
					return true;
				}
			}
		}
	}
	else
	{			

		pos = this->hash(elem);
		if (this->next[pos] == -1)  //check if thath hash if free
		{
			this->keys[pos] = NULL_TELEM;
			this->next[pos] = NULL_TELEM;
			this->length--;
			return true;
		}
		else
		{
			i=0;                               
			pos = this->hash(elem);
			while (this->next[pos] != -1)           //first look if we have it on the last elemnt on that hash
			{
				
				i = pos;
				pos = this->next[pos];
			}
			if (this->keys[pos] == elem)   //if so delete it and put next of previous to -1
			{
				this->keys[pos] = NULL_TELEM;
				this->next[pos] = NULL_TELEM;
				this->next[i] = -1;
				this->length --;
				return true;
			}


			pos = this->hash(elem);
			while (this->next[pos] != -1)    //if not it means is between 2 elems and look for previous and the position of the elem
			{
				
					
				if (this->keys[pos] == elem)
					i = pos;
				pos = this->next[pos];
			}

			//then copy the previous on the element we want to delete
			j = this->next[i];
			this->keys[i] = this->keys[j];
			this->next[i] = this->next[j];

			this->keys[j] = NULL_TELEM;
			this->next[j] = NULL_TELEM;
			this->length--;
			return true;

			

		}

		
	}
}
//WC:Theta(Capcaity)
//BC:Theta(elem)
//O(capacity)

bool Bag::search(TElem elem) {
	TElem e;
	int pos;
	if (elem < 0)
		e = -elem;
	else
		e = elem;
	//if (e >=this->cap)
	//	return false;
	pos = this->hash(e);
	if (this->next[pos] == -111111 and this->keys[pos] == -111111)
		return false;
	while (this->next[pos] != -1)
	{		if (this->keys[pos] == elem)
			return 1;
	pos = this->next[pos];
}
	if (this->keys[pos] == elem)
		return 1;
	return false; 
}
//BC: Theta(1)
// WC:: Theta(capacity)
//O(capacity)

int Bag::nrOccurrences(TElem elem)  {
	int pos = this->hash(elem);
	int k = 0;
	if (this->search(elem) == false)
		return 0;
	while (this->next[pos] != -1)
	{
		if (this->keys[pos] == elem)
			k++;
		pos = this->next[pos];
	}
	if (this->keys[pos] == elem)
		k++;
	return k;
}
//BC: Theta(1)
// WC:: Theta(capacity)
//O(capacity)

int Bag::size() const {
	return this->length;
}
//Theta(1)

bool Bag::isEmpty() const {
	if (this->length == 0)
		return true;
	else
		return false;
}
//Theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	delete[] this->keys;
	delete[] this->next;
}
//Theta(1)

TElem Bag::leastFrequent()
{
	int min = 9999999, pos;
	TElem elem;
	if (this->isEmpty())
	{
		return NULL_TELEM;
	}
	else
	{
		

				BagIterator it = this->iterator();
				it.first();
				while (it.valid()) {
					TElem e = it.getCurrent();
					if (this->nrOccurrences(e) < min)
					{

						min = this->nrOccurrences(e);
						elem = e;
					}
					it.next();
				}
				//pos = i;
			
		
		return elem;
	}

}