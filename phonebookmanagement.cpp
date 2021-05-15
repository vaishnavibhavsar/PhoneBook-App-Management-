/*
 * NAME: VAISHNAVI BHAVSAR
 * ROLL NO:2313
 * =============================================================
 * DATA STRUCTURES AND ALGORITHMS-I
 * MINI PROJECT
 * PROBLEM STATEMENT: TO SIMULATE A PHONEBOOK APP MANAGEMENT SYSTEM
 * FEATURES:
 * 1)CREATE NEW CONTACT AND ADD TO EXISTING
 * 2)UPDATE AND DELETE CONTACT
 * 3)DISPLAY CONTACT DETAILS
 * 4)RECOMENDATION OF CONTACTS ACC. TO INPUT SUBSTRING
 * 5)MAKE A PHONE CALL
 * 6)DISPLAY RECENTLY DIALED CONTACT NAMES
 *
 * TEAM MEMBERS:-
 * GROUP-1 : BATCH A1
 * 2301 - SHREYA ABHYANKAR
 * 2304 - AKHILA NORI
 * 2313 - VAISHNAVI BHAVSAR
 * 2321 - GAYATRI CHAUDHARI
 * ==========================================================================
 */
#include <iostream>
#include<cstring>
#include <string>
#include <regex>
#include <iomanip>

using namespace std;
class PhoneNo {      //class to create linked list for Mobile Numbers
	long int contactNo;  //variable declaration
	PhoneNo *link;      //points to next node of PhoneNo class
	friend class list;
public:
	PhoneNo(long int cNo) { //parameterized constructor to initialize the variables
		contactNo = cNo;
		link = NULL;
	}
};

class Mobile {				//class to create linkedlist of name of person
	string name;			//variable declaration
	PhoneNo *phonelink;		//points to head node of PhoneNo class
	Mobile *next;			//points to next node of Mobile class
	friend class PhoneNo;	//friend class to access methods and variable of other class
	friend class list;
public:
	Mobile(string cName) {	 //parameterized constructor to initialize the variables
		name = cName;
		phonelink = NULL;
		next = NULL;
	}
};
class list {
	Mobile *headMobile;
public:
	list() {					//default constructor to initialize to default values
		headMobile = NULL;
	}
	void create();				//function declaration
	void addToExisting();
	void display();
	void newContact();
	void deleteContact();
	void updatecontact();
	void Recommendation();
	void makephonecall();
	void recentlydialed();
};

//function to create to call specific function
//Time Complexity : O(1)
void list::create() {
	int ch;
	cout<<"\n\t\t|===============================================|\n\t\t";
	cout << "|  Enter your choice                            |\n\t\t";
	cout<<"\n\t\t|1:For new contact                              |\n\t\t";
	cout<<"\n\t\t|2:To add to existing contact                   |\n\t\t";
	cout<<"\n\t\t|===============================================|\n\t\t";
	cin >> ch;
	switch (ch) {			//to call specific function according to users choice
	case 1:
		newContact();		//function calling
		break;
	case 2:
		addToExisting();
		break;
	}
}

//creates new contact and inserts alphabetically
//Time Complexity: O(n)
void list::newContact() {
	PhoneNo *vitr;

	Mobile *temp = NULL; //for allocating memory to new node
	string cName;
	long int cNo;
	char ch;

	Mobile *vptr1;

	Mobile *ptr, *previous; //ptr is used for traversing Mobile list and previous to store previous node address
	PhoneNo *ptr1 = NULL;  //ptr1 is used for traversing Phone list
	cout<<"\n\t\t|===============================================|\n\t\t";
	cout<<"\n\t\t|Enter the contact name to be stored in the     |\n\t\t";
	cout<<"\n\t\t|phonebook:                                     |\n\t\t";
	cout<<"\n\t\t|===============================================|\n\t\t";

	cin >> cName;


	vptr1 = headMobile;  //vptr is used for traversing Mobile name for validation
	while (vptr1 != NULL) {
		if (vptr1->name == cName) {
		    cout<<"\n\t\t|===============================================|\n\t\t";
			cout<<"\n\t\t|This Contact name already exists.              |\n\t\t";
			cout<<"\n\t\t|===============================================|\n\t\t";
			cout<<"\n\t\t|Please select 'Add Contact to Phonebook ' from |\n\t\t";
			cout<<"\n\t\t|the main menu                                  |\n\t\t";
            cout<<"\n\t\t|===============================================|\n\t\t";
			goto notvalidcname;  //label for skipping the rest of the code so that invalid names are taken

		}
		vptr1 = vptr1->next;

	}

	temp = new Mobile(cName); //new node created
	do {
	    cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|Enter the contact no for the person            |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
		cin >> cNo;

		vitr = temp->phonelink; //vitr is used to traverse phone list for validation
		while (vitr != NULL) {
			if (vitr->contactNo == cNo) {
			    cout<<"\n\t\t|===============================================|\n\t\t";
				cout<<"\n\t\t|This contact number already exists.            |\n\t\t";
				cout<<"\n\t\t|Please go to the main menu                     |\n\t\t";
				cout<<"\n\t\t|===============================================|\n\t\t";
				goto notvalidcname;
			}
			vitr = vitr->link;
		}

		PhoneNo *mob = new PhoneNo(cNo); //memory allocated to PhoneNo object
		if (temp->phonelink == NULL) {
			temp->phonelink = mob;
		} else {
			ptr1 = temp->phonelink;
			while (ptr1->link != NULL) {
				ptr1 = ptr1->link;

			}
			ptr1->link = mob;
		}
		cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|Want to add more numbers for the same person?  |\n\t\t";
		cout<<"\n\t\t|Type y or Y , else N or n                      |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	if (headMobile == NULL) //if list is empty
	{
		headMobile = temp; //first node will be added
	} else if (strcmp(headMobile->name.c_str(), temp->name.c_str()) > 0) //comparing alphabetically
	{
		//only if first node is present
		temp->next = headMobile;
		headMobile = temp;
	}
	else
	{
		//comparing alphaetically with complete Mobile list
		previous = headMobile;
		ptr = headMobile->next;
		while ((ptr != NULL)
				&& strcmp(ptr->name.c_str(), temp->name.c_str()) < 0) {
			previous = ptr;
			ptr = ptr->next;
		}
		temp->next = previous->next;
		previous->next = temp;
	}

	notvalidcname: cout << "";
}
//adds new contact no to same contact name
//Time Complexity: O(n)
void list::addToExisting() {
	char ch;
	int flag;			//declaration of local variable
	string Name;
	long int cNo;
	Mobile *ptr = headMobile;
	do {
	    cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|Enter name for which you want to add contact   |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
		cin >> Name;
		while (ptr != NULL) {
			if (strcmp(ptr->name.c_str(), Name.c_str()) == 0) {		//comparing the names to find out the given contact
				flag = 1;		//to check if specific node exists or not
				break;
			}
			ptr = ptr->next;
		}
		if (flag == 1) {					//if node found
			PhoneNo *ptr1 = ptr->phonelink;		//initializing ptr1 to head(phonelink) node of PhoneNo list
			while (ptr1->link != NULL) {		//traversing the phonelink until last node
				ptr1 = ptr1->link;
			}
			cout<<"\n\t\t|===============================================|\n\t\t";
			cout<<"\n\t\t|Enter the contact no                           |\n\t\t";
			cout<<"\n\t\t|===============================================|\n\t\t";
			cin >> cNo;
			PhoneNo *mob = new PhoneNo(cNo);

			ptr1->link = mob;		//inserting the contact at last node
		}
		else {						//if contact not found
		    cout<<"\n\t\t|===============================================|\n\t\t";
			cout<<"\n\t\t|Sorry there is no such contact in the phonebook|\n\t\t";
			cout<<"\n\t\t|Please create a new contact                    |\n\t\t";
			cout<<"\n\t\t|===============================================|\n\t\t";

			break;
		}
		//if user wants to add more numbers
		cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|Do you want to continue adding phone nos. to an|\n\t\t";
		cout<<"\n\t\t|existing contact?                              |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
		cin >> ch;
	} while (ch == 'Y' || ch == 'y');

}

//alphabetically updates name and contact number
//Time Complexity: O(n)
void list::updatecontact()
{
	Mobile *ptr;			//variable and ptr declaration
	PhoneNo *itr;
	string old_name, updated_name;
	long old_contact, updated_contact;
	char choice;
	if (headMobile == NULL)
	{
		//list is empty
		cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|The contact List is empty                      |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t";
		return;
	}
	cout<<"\n\t\t|===============================================|\n\t\t";
	cout<<"\n\t\t|Do you want to update contact name? Type y or n|\n\t\t";
	cout<<"\n\t\t|===============================================|\n\t\t";
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|Enter the old name for which you want to update|\n\t\t";
		cout<<"\n\t\t|the name                                       |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
		cin >> old_name;

		ptr = headMobile;
		Mobile *previous, *temp;	//temp to store the address of node which has to update
		if (headMobile->name == old_name) //if first name is equal to the old name in list
		{
			temp = headMobile;
			headMobile = headMobile->next;
		}
		else
		{
			while (ptr != NULL && ptr->name != old_name) //traversing mobile list
			{
				previous = ptr;
				ptr = ptr->next;
			}
			if (ptr == NULL) //name not found in list
			{
				cout<<"\n\t\t|===============================================|\n\t\t";
				cout<<"\n\t\t|NO SUCH RECORD FOUND                           |\n\t\t";
				cout<<"\n\t\t|===============================================|\n\t\t";
				return;
			}
			temp = ptr; //attach ptr value to temp
			previous->next = ptr->next;	//previous next will store the value of ptr's next so that LL will not affect
		}
		if (temp != NULL)	//now according to alphabetical order address of temp will be inserted
		{
			cout<<"\n\t\t|===============================================|\n\t\t";
			cout<<"\n\t\t|Enter updated name                             |\n\t\t";
			cout<<"\n\t\t|===============================================|\n\t\t";
			cin >> updated_name;

			temp->name = updated_name;

			if (strcmp(headMobile->name.c_str(), temp->name.c_str()) > 0)

			{
				//compares first node alphabetically
				//if updated name is before the headmobile e.g abhay akhila gayatri
				temp->next = headMobile;
				headMobile = temp;
			}
			else
			{
				previous = headMobile;
				ptr = headMobile->next;
				while ((ptr != NULL) && strcmp(ptr->name.c_str(), temp->name.c_str()) < 0) //compairing names to store alphabetically
				{
					previous = ptr;
					ptr = ptr->next;
				}
				temp->next = previous->next;	//adding next node of previous to temp next
				previous->next = temp;		//adding temp to prev next
			}
			cout<<"\n\t\t|===============================================|\n\t\t";
			cout<<"\n\t\t|Successfully updated new contact name!         |\n\t\t";
			cout<<"\n\t\t|===============================================|\n\t\t";
		}
	}
	//if now user wants to update number of same or another person
	cout<<"\n\t\t|===============================================|\n\t\t";
	cout<<"\n\t\t|Do you want to update contact number?Type y /n |\n\t\t";
	cout<<"\n\t\t|===============================================|\n\t\t";
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{

		cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|Enter the name from list to change contact no  |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
	    cin>>old_name;
		ptr = headMobile;
		while (ptr != NULL && ptr->name != old_name)	//traversing until ptr becomes null or contact name will find
		{
			ptr = ptr->next;
		}
		if (ptr != NULL)	//if ptr pointing to entered name
		{
            cout<<"\n\t\t|===============================================|\n\t\t";
			cout<<"\n\t\t|Enter the old contact number for which you want|\n\t\t";
			cout<<"\n\t\t|to update the new contact number               |\n\t\t";
			cout<<"\n\t\t|===============================================|\n\t\t";
			cin >> old_contact;
			itr = ptr->phonelink;
			while (itr != NULL && itr->contactNo != old_contact)	//traversing until  the contactNo which have to replace
			{
				itr = itr->link;
			}
			if (itr != NULL) {		//if itr pointing to specific number
				cout<<"\n\t\t|===============================================|\n\t\t";
				cout<<"\n\t\t|Enter the updated contact number               |\n\t\t";
				cout<<"\n\t\t|===============================================|\n\t\t";
				cin >> updated_contact;
				itr->contactNo = updated_contact;
				cout<<"\n\t\t|===============================================|\n\t\t";
				cout<<"\n\t\t|Successfully updated Contact number!            |\n\t\t";
				cout<<"\n\t\t|===============================================|\n\t\t";
			}
			else		 //Contact number not found
			{
				cout<<"\n\t\t|===============================================|\n\t\t";
				cout<<"\n\t\t|No such contact number found for corresponding |\n\t\t";
				cout<<"\n\t\t|name!                                          |\n\t\t";
				cout<<"\n\t\t|===============================================|\n\t\t";
			}
		}
		else		//otherwise no such name found
		{
			cout<<"\n\t\t|===============================================|\n\t\t";
			cout<<"\n\t\t|No such contact name found!                    |\n\t\t";
			cout<<"\n\t\t|===============================================|\n\t\t";
		}
	}
}
//deletes particular contact on basis of contact name
//Time Complexity: O(n)
void list::deleteContact() {
	string str;
	Mobile *cur;
	Mobile *prev = NULL;
	cur = headMobile;
	if (headMobile == NULL) //list is empty
	{
		cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|The contact List is empty                      |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
		return;
	}
	cout<<"\n\t\t|===============================================|\n\t\t";
	cout<<"\n\t\t|Enter the name of the contact to be deleted    |\n\t\t";
	cout<<"\n\t\t|===============================================|\n\t\t";
	cin >> str;
	while (cur != NULL && cur->name.compare(str) != 0) {
		prev = cur;
		cur = cur->next;
	}
	if ((cur == NULL) || (cur != NULL && cur->name.compare(str) != 0)) {	//compairingthe agiven name with the current node
	    cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|"<<str<<" is not found in the contact list     |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
	} else  //cur is the node to be deleted
	{
		if (prev == NULL) //head node to be deleted
		{
			headMobile = cur->next;
			cur->next = NULL;
			delete (cur);
			cout<<"\n\t\t|===============================================|\n\t\t";
			cout<<"\n\t\t|"<<str<<" is successfully deleted from the list|\n\t\t";
			cout<<"\n\t\t|===============================================|\n\t\t";
		}

		else if (prev != NULL && cur->next == NULL) //last node to be deleted
		{
			prev->next = NULL;
			delete (cur);
			cout<<"\n\t\t|===============================================|\n\t\t";
			cout<<"\n\t\t|"<<str<<" is successfully deleted from the list|\n\t\t";
			cout<<"\n\t\t|===============================================|\n\t\t";
		} else  //current node in between
		{
			prev->next = cur->next;
			cur->next = NULL;
			delete (cur);
			cout<<"\n\t\t|===============================================|\n\t\t";
			cout<<"\n\t\t|"<<str<<" is successfully deleted from the list|\n\t\t";
			cout<<"\n\t\t|===============================================|\n\t\t";
		}

	}
}
//displays the contact details
//Time Complexity : O(n^2)
void list::display() {
    if (headMobile == NULL)	//if list is empty
	{
		cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|The contact List is empty                      |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
		return;
	}
	Mobile *ptr = headMobile;
	cout<< "====================================================================="<< endl;
	cout << setw(15) << "CONTACT NAME" << setw(30) << "CONTACT NUMBERS" << endl;
	cout<< "====================================================================="<< endl;

	while (ptr != NULL)	//traversing the outer linkedlist
	{
		PhoneNo *itr = ptr->phonelink;
		cout << setw(15) << ptr->name;
		while (itr != NULL)			//traversing the inner linkedlist
		{
			cout << setw(20) << itr->contactNo;	//fetching one by one Mobile numbers
			itr = itr->link;				//pointing to next address of PhoneNo list
		}
		ptr = ptr->next;			//pointing to next address of Mobile list
		cout << endl;
	}
	cout<< "====================================================================="<< endl;
	Mobile *cur;
	int c=0;
	cur = headMobile;
	while(cur!=NULL)			//to count the number of contacts in PHONEBOOK
	{
	    cur = cur->next;
	    c++;
	}
	cout<<"\nTotal number of contacts stored are : "<<c<<"\n";
	cout<< "========================================================================================================================="<<endl;
}
class Stack {		 //stack ADT

	int max;
	string st[50];
	int top;
public:
	Stack(int stacksize) {		//constructor
		top = -1;
		max = stacksize;
	}

	bool is_empty();		//function declaration
	bool is_full();
	void push(string element);
	string pop();
	string get_top();

};
//Time Complexity : O(1)
//checks if Stack is full
bool Stack::is_full() {
	if (top == max - 1) {

		return true;
	} else {

		return false;
	}
}
//Time Complexity : O(1)
//checks if Stack is empty
bool Stack::is_empty() {
	if (top == -1) {

		return true;
	} else {

		return false;
	}
}
//Time Complexity : O(1)
//to push the element in Stack
void Stack::push(string element) {

	if (is_full()) {		//if Stack is full
	    cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|The stack is in overflow condition             |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
	}
	else {		//add the data in Stack

		top++;
		st[top] = element;
	}
}
//Time Complexity : O(1)
//to pop the top element of stack
string Stack::pop() {
	string element;
	if (is_empty()) {		//if stack is empty
	    cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|Stack is in underflow condition                |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
		return NULL;
	} else {
		element = st[top--];
		return element;		//return the popped element

	}

}
//Time Complexity: O(1)
string Stack::get_top() {		//function to show top element of stack
	if (is_empty()) {			//if stack is empty
	    cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|Stack is empty                                 |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
		return NULL;
	} else {
		return (st[top]);		//return top element of stack
	}
}
Stack s1(50);			//objects of stack class
Stack s2(50);

//Time Complexity : O(n)
//function to make a call
void list::makephonecall() {
	if (headMobile == NULL) //if PHONEBOOK is empty
		{
		cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|The contact List is empty                      |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
		return;
		}
	string s_name;	//name to whom want to call
	cout<<"\n\t\t|===============================================|\n\t\t";
	cout<<"\n\t\t|Enter the contact name to whom you want to make|\n\t\t";
	cout<<"\n\t\t|a call                                         |\n\t\t";
	cout<<"\n\t\t|===============================================|\n\t\t";
	cin >> s_name;

	Mobile *ptr;

	ptr = headMobile;
	while (ptr != NULL && ptr->name != s_name) {	 //traversing the PHONEBOOK till get the entered name
		ptr = ptr->next;
	}
	if (ptr != NULL) {  //if ptr pointing to the entered name
        cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|Successfully called "<<ptr->name<<"             |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
		s1.push(ptr->name);
		s2.push(ptr->name);

	} else {
	    cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t| NO SUCH RECORD FOUND                          |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
	}
}
//Time Complexity : O(n)
//Shows the recently dialed contact names
void list::recentlydialed() {

	string str;
    if(!s2.is_empty()){  //checks if stack s2 is empty

	    s1 = s2;		//copy all elements from stack s2 to stack s1
	    cout<<"\n\t\t|===============================================|\n\t\t";
	    cout<<"\n\t\t|Recently dialed numbers are                    |\n\t\t";
    	cout<<"\n\t\t|===============================================|\n\t\t";
	    while (!s1.is_empty()) {	//pop all elements till s1 becomes empty
		str = s1.pop();
		cout << "\n\t\t" << str << endl;
	    }
    }
	else
	{
		//cout<<"\nNo recent dials yet"<<endl;
		cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t| No recent dials yet                           |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
	}

}

void list::Recommendation() {

	if (headMobile == NULL) //if PHONEBOOK is empty
				{
					cout<<"\n\t\t|===============================================|\n\t\t";
					cout<<"\n\t\t|The contact List is empty                      |\n\t\t";
					cout<<"\n\t\t|===============================================|\n\t\t";
					return;
				}

	Mobile *ptr;
	ptr = headMobile;
	PhoneNo *itr = ptr->phonelink;
	std::string cname = ptr->name;
	int flag = 0;
	int count = 0;
	string s;
	 	 cout <<"\t\t===============================================\n\t\t";
	 	 cout<<"|Enter first few characters of the contact to be|\n\t\t";
		 cout<<"|searched                                       |\n\t\t";
		 cout<<"===============================================\n\t\t";
		 cin >> s;
	/*regex class whose object e is created by calling parameterized constructor
		 by passing substring which user has entered*/

	regex e(s + "");


	if (ptr == NULL) {		//if list is empty
	    cout<<"\n\t\t|===============================================|\n\t\t";
		cout<<"\n\t\t|There is no contact in the List currently.     |\n\t\t";
		cout<<"\n\t\t|Select create Contact to create a contact      |\n\t\t";
		cout<<"\n\t\t|===============================================|\n\t\t";
	} else {
		cout<<"======================================================================================================================="<< endl;
		cout<<setw(15) << "CONTACT NAME" << setw(30) << "CONTACT NUMBERS"<< endl;
		cout<<"======================================================================================================================="<< endl;

		while (ptr != NULL) {
			if (std::regex_search(ptr->name, e) == true) {  //regex_search function to check whether the name in LL consists of given substring
				itr = ptr->phonelink;

				cout << setw(15) << ptr->name;
				while (itr != NULL) {	//traversing to show the contactNo of matching name

					cout << setw(20) << itr->contactNo;
					itr = itr->link;
				}
				cout << "\n";
				flag = 1;
				count++;		//to show how many records found
			}
			cname = ptr->name;
			ptr = ptr->next;

		}
		if (flag == 1) {
		    cout<<"\n==================================================================\n";
			cout<<"\nTotal "<<count<<" results were found!          \n";
			cout<<"\n==================================================================\n";
		}
		if (flag == 0) {		 //if contact not found
		    cout<<"\n\t\t|===============================================|\n\t\t";
			cout<<"\n\t\t|No such contact exists                         |\n\t\t";
			cout<<"\n\t\t|===============================================|\n\t\t";
		}
	}

}

int main() {
	list l;		//creating object of list class
	int ch;		//local variable declaration
	//string s;
	//menu
	do {
		cout<<"\n";
		cout <<"\t===============================================\n\t";
		cout << "|           PHONEBOOK APP                      |\n\t";
		cout << "===============================================\n\t";
		cout << "|1:To Add contact to Phonebook                 |\n\t";
		cout << "|______________________________________________|\n\t";
		cout << "|2:To Display contacts from Phonebook          |\n\t";
		cout << "|______________________________________________|\n\t";
		cout << "|3:To Edit the contact From Phonebook          |\n\t";
		cout << "|______________________________________________|\n\t";
		cout << "|4:To Delete the contact From Phonebook        |\n\t";
		cout << "|______________________________________________|\n\t";
		cout << "|5:To Recommend the contact From Phonebook     |\n\t";
		cout << "|______________________________________________|\n\t";
		cout << "|6:Make a call from Phonebook                  |\n\t";
		cout << "|______________________________________________|\n\t";
		cout << "|7:To Recently dialed From Phonebook           |\n\t";
		cout << "|______________________________________________|\n\t";
		cout << "|8:Exit                                        |\n\t";
		cout << "|______________________________________________|\n\t";

		cout << "|Enter the choice from above list              |\n\t";
		cout << "===============================================\n\t";
		cin >> ch;
		switch (ch) {		//switch case for specific function calling
		case 1:
			l.create();		 //calling create function
			break;

		case 2:
			l.display();		 //calling display function
			break;

		case 3:
			l.updatecontact();	//calling updatecontact function
			break;

		case 4:
			l.deleteContact();	//calling deleteContact function
			break;

		case 5:
           /* cout <<"\t\t===============================================\n\t\t";
			cout<<"|Enter first few characters of the contact to be|\n\t\t";
			cout<<"|searched                                       |\n\t\t";
			cout<<"===============================================\n\t\t";
			cin >> s;*/
			l.Recommendation();	//calling Recommendation function
			break;

		case 6:
			l.makephonecall();	 //calling makephonecall function
			break;
		case 7:
			l.recentlydialed();	//calling recentlydialed function
			break;
		case 8:	//end of the program
		    cout<<"\t\t===============================================\n\t\t";
			cout<<"Thank you for using our app!                 \n\t\t";
			cout<<"===============================================\n\t\t";
			break;

		default:  //if invalid input is entered
		    cout<<"\t\t===============================================\n\t\t";
			cout<<"Invalid choice!                                 \n\t\t ";
            cout<<"=================================================\n\t\t";
		}
	} while (ch != 8);
}


	