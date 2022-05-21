#pragma once
#include <iostream>


using namespace std;




template <typename dataType>


class List
{
private:

	size_t size_of_list; //Number of items in the list

	class Element
	{

	public:

		Element* Next, * Previous; //Pointers to the next and previous element.

		dataType member;
		

		Element(dataType member, Element* Next = NULL, Element* Previous = NULL)
		{
			this->member = member;
			this->Next = Next;
			this->Previous = Previous;
		}
	};




	Element* Head; //Pointer to the beginning
	Element* Tail; //Pointer to the end


public:


	List()  //Constructor for creating an empty list
	{

		Head = Tail = NULL;
		size_of_list = 0;

	};

	List(dataType member) //Constructor for creating a list with an element
	{

		Element* newNode = new Element(member);

		Head = Tail = newNode;
		size_of_list = 1;

	};

	~List() //Destructor
	{

		clear();

	};

	void clear()
	{ //Deleting all list members

		Element* temp = Head; // Create temporary node

		while (Head != NULL) //Deleting members
		{
			Element* temp = Head->Next;
			delete Head;
			Head = temp;
		}

		Tail = Head = NULL;

		size_of_list = 0;

	};

	size_t get_size()  //Getting the number of items in the list
	{
		return size_of_list;
	}
	
	dataType at(size_t elem)                                                 //Getting an element by index
	{

		if (elem < get_size()) // If index is in List range
		{
			Element* temp = Head; // Create temporary node
			for (int i = 0; i < elem; i++) {
				temp = temp->Next;
			}
			return temp->member;
		}

		else {
			throw out_of_range("Out of range");
		}


	}


	void push_back(dataType member)  //Adding an item to the end of the list
	{         

		Element* newNode = new Element(member);


		if (isEmpty()) 
		{                       //If the list is empty

			Head = Tail = newNode;
		}


		else 
		{                                //If the list is not empty
			
			newNode->Previous = Tail;
			Tail->Next = newNode;
			Tail = newNode;

		}

		size_of_list++;
	};

	void push_front(dataType newMember)                 //Add a new element forward
	{
		Element* temp = new Element(newMember);

		if (Head != NULL)                             //If List is not empty
		{
			temp->Next = Head;
			Head->Previous = temp;
			Head = temp;
			size_of_list++;
		}

		else                                          //If List is empty
		{
			Head = Tail = temp;
			size_of_list++;
		}
	}


	bool isEmpty()    //Checking for emptiness
	{
		if (Head == NULL)
			return true;
		else
			return false;
	}


	
	void insert(dataType value, size_t elem)                                //Inserting before an element that was previously available by this index
	{

		if (elem > get_size() - 1)
			throw out_of_range("Out of range");

		else
		{
			if ((elem == 0) || (elem = get_size() - 1))                         //Adding to extreme points
			{
				if (elem == 0)
					push_front(value);
				if (elem = get_size() - 1)
					push_back(value);
			}

			else                                                             //Adding to the middle
			{
				Element* temp = Head, * save;

				for (int i = 0; i < elem - 1; i++)
					temp = temp->Next;

				Element* newElement = new Element(value , NULL, NULL);

				newElement->member = value;
				save = temp->Next;
				temp->Next;
				temp->Next = newElement;
				newElement->Next = save;

				size_of_list++;
			}

		}
	}

	int isInList(dataType variable)//Searches for the desired item in the list
	{
		int position = INT_MAX;
		Element* temp = Head;

		for (int i = 0; i < size_of_list; i++)
		{
			
			if (temp->member == variable)
			{
				position = i;
				break;
			}
			temp = temp->Next;
				
		}
		
		return position;
		
	}



	friend std::ostream& operator << (std::ostream& out, List& currentList) //Redefining output
	{
		size_t current_size_of_list = currentList.get_size();

		for (size_t i = 0; i < current_size_of_list; i++)
		{
			cout << currentList.at(i) << endl;
		}
		return out;
	}
};