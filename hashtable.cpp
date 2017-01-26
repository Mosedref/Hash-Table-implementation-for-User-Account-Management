#include <cstdlib>
#include <math.h> 
#include <string>
#include <vector>
#include "hashtable.h"
#include "useraccount.h"
#include "slinkedlist.h"
#include "hashtableprivate.h"

// hash function, uses Horner's method
 // Assume input string consists only of lower-case a to z
int HashTable::Hash(string input) const
{
 int hashVal = (input[0]) - 96;
	if(input.length() == 1)
	{
		hashVal = hashVal% this->maxsize;
	}
  for(unsigned int j =1; j <input.length(); j++)
  {
	int nextL = input[j] -96;
    hashVal = (hashVal * 32 + nextL ) % maxsize;
  }
	 return hashVal;
}


int HashTable::SmallestPrime(int n) const
{
	n++;
	
	while(!IsPrime(n))
	{
		n++;
	}
	return n;
}

// helper function to determine whether a number is prime
bool HashTable::IsPrime(int n) const
{
	if((n%2 ==0 || n%3==0 || n%4==0 || n%5==0 || n%6==0 || n%7==0 || n%8==0 || n%9==0) || n < 1 )
	{
		return false;
	}

	return true;
}

// Resizes the hashtable into a larger array.
// Return false if n is smaller than current array size or if n is negative.
// Else, set array size to the smallest prime number larger than n
//   and re-hash all contents into the new array, delete the old array and return true.
bool HashTable::Resize(int n)
{
	HashPrint();
	//int Call = 0;
	//Call=size;
	if( n <= 0 || n < maxsize)
	{
		return false;
	}

	int tempSize = maxsize;

	
	/*
	if(size ==0)
	{
		return false;
	}*/
	this->size = 0;
    this->maxsize = SmallestPrime(n);
	SLinkedList<UserAccount>* temp = table;
	table = new SLinkedList<UserAccount>[maxsize];

	
	vector<UserAccount> items;

	for(int i = 0; i< tempSize; i++)
	{
		items=temp[i].Dump();
		
		for(unsigned int k = 0; k < items.size(); k++)
		{
			Insert(items.at(k));
		}
	}

	//delete all the linked lists
	for( int j = 0; j < tempSize;  j++)
	{
		temp[j].RemoveAll();
	}

	delete [] temp;
	//size =Call;
	return true;
}


// default constructor
	// creates an array of size 101
HashTable::HashTable()
{
	size =0;
	maxsize = 101;
	table = new SLinkedList<UserAccount>[101];

}

// parameterized constructor
// creates an array of size = smallest prime number > 2n
HashTable::HashTable(int n) 
{
	size =0;
	maxsize = SmallestPrime(2*n);
	table = new SLinkedList<UserAccount>[maxsize];
}

//copy constructor
HashTable::HashTable(const HashTable& sourceht)
{
	size = 0;
	maxsize = sourceht.MaxSize();
	table = new SLinkedList<UserAccount>[maxsize];

	//copy the linked lists from source
	vector<UserAccount> items;
	for(int i = 0; i< maxsize; i++)
	{
		//dump the into a vector first then copy from vector
		items = sourceht.table[i].Dump();
		
		//copy to table of this
		for(unsigned int k = 0; k < items.size(); k++)
		{
			Insert(items.at(k));
		}

	}
}


//Destructor
HashTable::~HashTable()
{
	if(size > 0)
	{
		for (int i = 0; i < maxsize; i++)
		{
			table[i].RemoveAll();
		}
	}
	delete [] table;
	table = NULL;
	maxsize = 0;
	size = 0;
}


// overloaded assignment operator
HashTable& HashTable::operator=(const HashTable& sourceht)
{

	if(this != &sourceht)
	{
		//first delete existing table
		if(size > 0)
		{
			for (int i = 0; i < maxsize; i++)
			{
				table[i].RemoveAll();
			}
		}
		delete [] table;

		//make new hashtable
		size =0;
		maxsize = sourceht.MaxSize();
		table = new SLinkedList<UserAccount>[maxsize];

		//copy the linked lists from source
		vector<UserAccount> items;
		for(int i = 0; i< maxsize; i++)
		{
			//dump the into a vector first then copy from vector
			items = sourceht.table[i].Dump();
		
			//copy to table of this
			for(unsigned int k = 0; k < items.size(); k++)
			{
				Insert(items.at(k));
			}

		}
	}

return *this;
}

// Insertion
	// If item does not already exist, inserts at back of hashed list and returns true
	//   otherwise returns false
	// If load factor (before insertion) is above 2/3, expand into a new
	//   table of smallest prime number size at least double the present table size
	//   and then insert the item.
bool HashTable::Insert(UserAccount acct)
{
	if(Search(acct) == true)
	{
		return false;
	}

	if( LoadFactor() > 2.0/3.0)
	{
		Resize(2*maxsize);
	}
	this->size ++;
	int index = Hash(acct.GetUsername());

	table[index].InsertBack(acct);

	return true;
}


// Removal
	// If item exists, removes and returns true
	//   otherwise returns false
bool HashTable::Remove(UserAccount acct)
{
	if(Search(acct) == true)
	{

		int index = Hash(acct.GetUsername());
		size--;
		return table[index].Remove(acct);
	
	}

	return false;

}



 // Search
   // Returns true if item exists, false otherwise
   bool HashTable::Search(UserAccount acct) const
{
	if(size == 0)
	{return false;}

	int  index = Hash(acct.GetUsername());

	return table[index].Contains(acct);
               
 }

 // Retrieval
// Returns a pointer to a UserAccount object inside the hash table (linked list)
//   if a matching parameter is found, otherwise return NULL
UserAccount* HashTable::Retrieve(UserAccount acct)
{
	UserAccount* found = NULL;

	if(size!=0)
	{
		int  index = Hash(acct.GetUsername());
		found = table[index].Retrieve(acct);
	}


	return found;
}



int HashTable::Size() const
{
	return size;
}

int HashTable::MaxSize() const
{
	return maxsize;
}

double HashTable::LoadFactor() const
{
	return double(size)/double(maxsize);
}
