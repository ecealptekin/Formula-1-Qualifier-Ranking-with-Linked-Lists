#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//Ece Alptekin
//24156
//Homework 2 – Formula 1 Qualifier Ranking with Linked Lists

struct Node
{
	string driver;
	int laptime;
	Node * next;

	Node::Node()
	{
		driver = "";
		laptime = 0;
		next = NULL;
	}

	Node::Node(string s,int t,Node * n)
		:driver(s),
		laptime(t),
		next(n)
	{}
};

void DeleteList(Node * &head)
{
	//it deletes the all list
	Node * ptr = head;
	Node * temp;

	while(ptr != NULL)
	{
		temp = ptr->next;
		delete ptr;
		ptr = temp;
	}
	head = NULL;
}

int CurrentPosition(string driver,Node * head) 
{
	//gives the current position of the driver
	Node * p = head;
	int position = 1;

	while(p != NULL)
	{
		if(p->driver == driver)
		{
			return position;
		}
		position++;
	    p = p->next;
	}

	return position;
}

void DeleteNode(Node * temp,Node * &head)
{
	//temp is the node to be deleted
	//if temp is the head then head is updated
	/* Begin: code taken from ptrfunc.cpp and updated */
	if(temp == head)
	{
		head = head->next;
		delete temp;
	}

	else
	{
		Node * p = head;
		while(p->next != temp)
		{
			p = p->next;
		}

		p->next = temp->next;
		delete temp; //delete the node
	}
	/* End: code taken from ptrfunc.cpp and updated */
}

void AddInOrder(Node * toBeAdded,Node * &head)
{	
	//list is already sorted
	//add a new node and keep the list sorted
	/* Begin: code taken from ptrfunc.cpp and updated */

	if(toBeAdded->laptime < head->laptime)
	{
		toBeAdded->next = head;
		head = toBeAdded;
	}

	else
	{
	  Node * p = head;

	  while(p->next != NULL && (p->next->laptime < toBeAdded->laptime || p->next->laptime == toBeAdded->laptime))
	   {
		p = p->next;
	   }

	toBeAdded->next = p->next;
	p->next = toBeAdded;
	}
	/* End: code taken from ptrfunc.cpp and updated */
}
 
Node * CheckIfPositionChanges(Node * temp,Node * &head)
{
  Node * p = new Node(temp->driver,temp->laptime,NULL);
  DeleteNode(temp,head); //delete the old node
  AddInOrder(p,head); //add updated node to the list
  return p;
}

bool IfExists(string driver,Node * head,Node * &temp)
{
	//it gives the location of the driver in the list
	while(head != NULL)
	{
		if(head->driver == driver)
		{
			temp = head; //gives the location of the driver in the list
			return true;
		}
		head = head->next;
	}
	return false;
}

void AddList(string driver,int laptime,Node * &head)
{
	//this function adds driver and laptime to the list if it is not in the list 
	//it updates the current laptime if it is necesssary
	if(head == NULL) //if there is not any driver yet
	{
		head = new Node(driver,laptime,NULL);
		cout << driver << " completed the lap in " << laptime << " milliseconds" << endl;
		cout << driver << ": current personal best is " << laptime <<"; current position is " << CurrentPosition(driver,head) << endl;
	}

	else
	{
		Node * temp = NULL;
		if(IfExists(driver,head,temp)) 
		{
			if(temp->laptime > laptime) //new laptime is smaller than the previous one
			{
			   temp->laptime = laptime;
			   Node * a = CheckIfPositionChanges(temp,head);
			   cout << driver << " completed the lap in " << laptime << " milliseconds" << endl;
			   cout << driver << ": current personal best is " << a->laptime <<"; current position is " << CurrentPosition(a->driver,head) << endl;
			}

			else if(temp->laptime < laptime || temp->laptime == laptime) //the list does not change
			{
			cout << driver << " completed the lap in " << laptime << " milliseconds" << endl;
			cout << driver << ": current personal best is " << temp->laptime <<"; current position is " << CurrentPosition(temp->driver,head) << endl;
			}
		}

		else //if the driver is not in the list
		{
			Node * p = new Node(driver,laptime,NULL);
			AddInOrder(p,head);
			cout << driver << " completed the lap in " << laptime << " milliseconds" << endl;
			cout << driver << ": current personal best is " << laptime <<"; current position is " << CurrentPosition(driver,head) << endl;
		}
	}

}

int main()
{
	Node * head = NULL; //to store the linked list

	string filename;
	cout << "Please enter a file name." << endl;
	cin >> filename;

	while(filename != "t1.txt" && filename != "t2.txt" && filename != "t3.txt")
	{
		cout << "Unable to open file " << filename << endl;
		cout << "Please enter a different file name." << endl;
		cin >> filename;
	}

	cout << "Successfully opened file " << filename << endl;
	cout << "\n";
	cout << "###############################" << endl;
	cout << "Qualifying Laps:" << endl;
	cout << "###############################" << endl;

	ifstream in;
	in.open(filename);

	string word;
	string s;
	int t;
	while(!in.eof())
	{
		getline(in,word);
		stringstream ss(word);
	
		ss >> s;
		ss >> t;

		AddList(s,t,head);
	}

	cout << "\n" << endl;
	cout << "###############################" << endl;
	cout << "Results:" << endl;
	cout << "###############################" << endl;

	int count = 1;
	Node * ptr = head;
	while(ptr != NULL)
	{
		cout << count << ". " << ptr->driver << " " << ptr->laptime << endl;
		count++;
		ptr = ptr->next;
	}

	DeleteList(head);

	cin.get();
	cin.ignore();
	return 0;
}