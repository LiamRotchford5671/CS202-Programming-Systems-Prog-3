//Liam Rotchford
//Nov 15 18

/* This program implements Dynamic binding (upcasting, downcasting). The specfic heiarchy is decribed in the Food.h file description.
 * Using a 2-3-4 tree, we allow the user to select from 3 food types for a dinner party (derived classes) and we then prompt for general data and then speacilized 
 * data based on the food type selected. We store that data intialized to a newly created object pointer of the derived class and then send it to be inserted
 * into the food base class pointer array in our node into the 2-3-4 tree, This program allows insert, remove all, and display options with the tree
 */

#include "Food.h"
using namespace std;

int main()
{
	manager object, object2, object3;		//2-3-4 tree manager class object

	cout << "\n\no Welcome to the Dinner Party Food Selection Program: " << endl;	
	cout << "\n======================================================================================" << endl;

	cout << "\n\to Before we begin lets make sure how large of a party we will be dealing with for our dinner party:  {Operator Overloading}" << endl;
	cout << "\n\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	cout << "\n\to How many people do you belive will be attending in the FIRST GROUP for the dinner party? ";
	cin >> object2; 					// Input >> operator overloading
	cin.ignore(100, '\n');

	cout << "\n\to How many people do you belive will be attending in the SECOND GROUP for the dinner party? ";
	cin >> object3; 					// Input >> operator overloading
	cin.ignore(100, '\n');

	// OPERATOR OVERLOADING FOR <, >, <=, >=, ==, !=, +, +=, = using the group int values in the manager class objects
	if(object2 < object3)		// <
		cout << "\n\to Group 1 has ( < ) less than Group 2." << endl;

	if(object2 > object3)		// >
		cout << "\n\to Group 1 has ( > ) more than Group 2." << endl;

	if(object2 <= object3)		// <=
		cout << "\n\to Group 1 has ( <= ) less than or equal to Group 2." << endl;
	
	if(object2 >= object3)		// >=
		cout << "\n\to Group 1 has ( >= ) more than or equal to Group 2." << endl;

	if(object2 != object3)		// !=
		cout << "\n\to Group 1 is ( != ) not equal to Group 2." << endl;
	
	if(object2 == object3)		// ==
		cout << "\n\to Group 1 is ( == ) equivalent to Group 2." << endl;

	object = object2 + object3;				// + operator overload
	cout << "\n\to We will now add the 2 groups together for the total of people attending the dinner party. \n\t\t+ Total Group is now: ";
	cout << object;						//Output << operator overloading
	
	object2 += object3; 					// += operator overload
	object += object2;	
	cout << "\n\n\to It seems that a third group has arrived late and we've counted them to be the same number of people as Group 2, we will be adding them to our guest list. \n\t\t+ Total Group is: ";
	cout << object;	
	
	object = object3;					// = operator overloaded
	cout << "\n\n\to It seems that Group 1 and Group 3 have abruptly changed there minds about attending the dinner party, we will remove them from our guest list. \n\t\t+ Total Group is: "; 
	cout << object;

	cout << "\n\to Now that we have the number of people attending lets go through each person and determine what they would like to have at the party." << endl;
	cout << "\n\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	
	user_menu(object);	//begin program, sending it to user menu to learn about the program 
	
	return 0;
}

