//Liam Rotchford
//Nov 15 18

/* this file handles all of the functions in the dynamic bind heirarchy, the food abstract base class, and its derived classes. These are functions like the 
 * constructors, constructor with args to set the temp data gained in support.cpp to the new derived class object pointer, the copy constructors, and their
 * = operator overloading used in teh constructor with args, the destructors that are dynamcially bound and the displays called via downcasting from the node
 * function node_diplay
*/

#include "Food.h"
using namespace std;

//==========================================================================
//+++++++++++++++++++++++++ FOOD ABSTRACT BASE CLASS ++++++++++++++
//==========================================================================

//this class acts as the glue for the three derived classes of rental types, it holds all similar data between the three

//CONSTRUCTOR
//set all data to intiliaze to null
food::food() : name(NULL), ID(0), calorie_limit(0), sugar_limit(0)
{
}

//COPY CONSTRUCTOR
//since its derived and both base and derived have dynamic memory then it will use the intialization list to call the base copy constructor
food::food(const food & source) : ID(source.ID), calorie_limit(source.calorie_limit), sugar_limit(source.sugar_limit)
{
	name = new char[strlen(source.name) + 1];
	strcpy(name, source.name);
}

//VIRTUAL DESTRUCTOR 
food::~food()
{
	delete [] name;
	name = NULL;
}

int food::pullID()
{
	return ID;
}

//display virtual function is pure so no need to implement it

//==========================================================================
//+++++++++++++++++++++++++ MAIN COURSE DERIVED CLASS ++++++++++++++++++++++++++
//==========================================================================

//CONSTRUCTOR
main_course::main_course() : item(NULL), gluten_free(false), calorie_course(0), sugar_course(0) 
{
}

//COPY CONSTRUCTOR
//since its derived and both base and derived have dynamic memory then it will use the intialization list to call the base copy constructor
main_course::main_course(const main_course & source) : gluten_free(source.gluten_free), calorie_course(source.calorie_course), sugar_course(source.sugar_course)
{
	item = new char[strlen(source.item) + 1];
	strcpy(item, source.item);
}


//CONSTRUCTOR WITH ARGS
//used for setting temp varibles for the newly created derived class object to set all the data to the new object
main_course::main_course(char * tempName, char * foodtype, bool non_gluten, int calorie_lim, int sugar_lim, int number)
{
	name = new char[strlen(tempName)+1];
	strcpy(name, tempName);

	item = new char[strlen(foodtype)+1];	//set dynamic mem
	strcpy(item, foodtype);

	gluten_free = non_gluten;
	calorie_limit = calorie_lim;
	sugar_limit = sugar_lim;

	if(calorie_limit > 150)
		calorie_course = 150;
	else
		calorie_course = calorie_limit;		// OPERATOR = OVERLOADED AND USED ON THE DERIVED CLASS THAT HAS DYNAMIC MEM 

	if(sugar_limit > 150)
		sugar_course = 150;
	else
		sugar_course = sugar_limit;

	ID = number;				
}

//OPERATOR = OVERLOAD
// = operator overload on derived main_course class used in there copy constructors to assign the calorie value to what the calorie limit is
main_course& main_course::operator = (const main_course& C)
{
	this->calorie_course = C.calorie_limit;
	return *this;
}

//DECONSTRUCTOR
// delete the dynamic mem in the class dynamically bound
main_course::~main_course()
{
	delete [] item;
	item = NULL;
}

//DISPLAY FOR DERIVED DYNAMIC BOUND FUNCTION
//This is called from the node class via downcasting as it determines the type we are and calls the appropriate derived class display to display the 
//speacilized data stored on this derived object
int main_course::display() const
{
		cout << "\to Number: " << ID << endl;	
		cout << "\to Name: " << name << endl;	
		cout << "\to Meal: " << item << endl;
		cout << "\to Calorie Count for Meal: " << calorie_course << endl;
		cout << "\to Calorie Limit: " << calorie_limit << endl;
		cout << "\to Sugar Count for Meal: " << sugar_course << endl;
		cout << "\to Sugar Limit: " << sugar_limit << endl;
		cout << "\to Gluten Free: ";
		if(gluten_free == true)
			cout << " YES " << endl;
		else 
			cout << " NO " << endl;
	cout << "\n";
	return 1;
}


//==========================================================================
//+++++++++++++++++++++++++ BEVERAGE DERIVED CLASS +++++++++++++++++++++++++
//==========================================================================
//CONSTRUCTOR
beverage::beverage() : item(NULL), alcohol_free(false), calorie_beverage(0), sugar_beverage(0)
{
}

//COPY CONSTRUCTOR
//since its derived and both base and derived have dynamic memory then it will use the intialization list to call the base copy constructor
beverage::beverage(const beverage & source) : alcohol_free(source.alcohol_free), calorie_beverage(source.calorie_beverage), sugar_beverage(source.sugar_beverage)
{
	item = new char[strlen(source.item) + 1];
	strcpy(item, source.item);
}

//CONSTRUCTOR WITH ARGS
//used for setting temp varibles for the newly created derived class object to set all the data to the new object
beverage::beverage(char * tempName, char * foodtype, bool non_alcoholic, int calorie_lim, int sugar_lim, int number)
{	
	name = new char[strlen(tempName)+1];
	strcpy(name, tempName);
	
	item = new char[strlen(foodtype)+1];	//set dynamic mem
	strcpy(item, foodtype);

	alcohol_free = non_alcoholic;
	calorie_limit = calorie_lim;
	sugar_limit = sugar_lim;

	if(calorie_limit > 60)
		calorie_beverage = 60;
	else
		calorie_beverage = calorie_limit;	// OPERATOR = OVERLOADED AND USED ON THE DERIVED CLASS THAT HAS DYNAMIC MEM  

	if(sugar_limit > 15)
		sugar_beverage = 15;
	else
		sugar_beverage = sugar_limit;

	ID = number; 				
}

//OPERATOR = OVERLOAD
// = operator overload on derived class beverage
beverage& beverage::operator = (const beverage& B)
{
	this->calorie_beverage = B.calorie_limit;
	return *this;
}


//DESTRUCTOR
// delete the dynamic mem in the class dynamically bound
beverage::~beverage()
{
	delete [] item;
	item = NULL;
}

//DISPLAY FOR DERIVED DYNAMIC BOUND FUNCTION
//This is called from the node class via downcasting as it determines the type we are and calls the appropriate derived class display to display the 
//speacilized data stored on this derived object
int beverage::display() const
{	
		cout << "\to Number: " << ID << endl;	
		cout << "\to Name: " << name << endl;	
		cout << "\to Drink: " << item << endl;
		cout << "\to Calorie Count for Meal: " << calorie_beverage << endl;
		cout << "\to Calorie Limit: " << calorie_limit << endl;
		cout << "\to Sugar Count for Meal: " << sugar_beverage << endl;
		cout << "\to Sugar Limit: " << sugar_limit << endl;
		cout << "\to Alcohol Free: ";
		if(alcohol_free == true)
			cout << " YES " << endl;
		else 
			cout << " NO " << endl;
	cout << "\n";
	return 1;
}

//==========================================================================
//+++++++++++++++++++++++++ DESSERT DERIVED CLASS +++++++++++++++++++++++++++++
//==========================================================================
//CONSTRUCTOR
dessert::dessert() : item(NULL), dairy_free(false), calorie_dessert(0), sugar_dessert(0)
{
}

//COPY CONSTRUCTOR
//since its derived and both base and derived have dynamic memory then it will use the intialization list to call the base copy constructor
dessert::dessert(const dessert & source) : dairy_free(source.dairy_free), calorie_dessert(source.calorie_dessert), sugar_dessert(source.sugar_dessert)
{
	item = new char[strlen(source.item) + 1];
	strcpy(item, source.item);
}

//CONSTRUCTOR WITH ARGS
//used for setting temp varibles for the newly created derived class object to set all the data to the new object
dessert::dessert(char * tempName, char * foodtype, bool non_dairy, int calorie_lim, int sugar_lim, int number)
{
	name = new char[strlen(tempName)+1];
	strcpy(name, tempName);
	
	item = new char[strlen(foodtype)+1];	//set dynamic mem
	strcpy(item, foodtype);

	dairy_free = non_dairy;
	calorie_limit = calorie_lim;
	sugar_limit = sugar_lim;

	if(calorie_limit > 60)
		calorie_dessert = 60;
	else
		calorie_dessert = calorie_limit;	// OPERATOR = OVERLOADED AND USED ON THE DERIVED CLASS THAT HAS DYNAMIC MEM 

	if(sugar_limit > 15)
		sugar_dessert = 15;
	else
		sugar_dessert = sugar_limit;
	
	ID = number;			
}

//OPERATOR = OVERLOAD
// = operator overload on derived class dessert
dessert& dessert::operator = (const dessert& D)
{
	this->calorie_dessert = D.calorie_limit;	
	return *this;
}

//DESTRUCTOR
// delete the dynamic mem in the class dynamically bound
dessert::~dessert()
{
	delete [] item;
	item = NULL;
}

//DISPLAY FOR DERIVED DYNAMIC BOUND FUNCTION
//This is called from the node class via downcasting as it determines the type we are and calls the appropriate derived class display to display the 
//speacilized data stored on this derived object
int dessert::display() const
{
		cout << "\n\to Number: " << ID << endl;	
		cout << "\to Name: " << name << endl;	
		cout << "\to Dessert: " << item << endl;
		cout << "\to Calorie Count for Meal: " << calorie_dessert << endl;
		cout << "\to Calorie Limit: " << calorie_limit << endl;
		cout << "\to Sugar Count for Meal: " << sugar_dessert << endl;
		cout << "\to Sugar Limit: " << sugar_limit << endl;
		cout << "\to Dairy Free: ";
		if(dairy_free == true)
			cout << " YES " << endl;
		else 
			cout << " NO " << endl;
	cout << "\n";
	return 1;
}

