//Liam Rotchford 
//Nov 15 18

/* The heirarchy of this program is as follow 6 classes. The food class is an abstract base class that acts as a "glue" and similar data holder for the 3 
 * derived classes that represent the food options for the dinner party. The manager class handles the 2-3-4 tree and "has a" node class that contains a 
 * food base class pointer array that gets derived class (dinner item) pointers sent to it to be stored in the tree. The manager / node class
 * are completly separated from the food and derived classes (main_course, beverage, dessert). The Base class food employs dynamic binding to allow
 * for additional functionality when accessing my derived pointers from my tree.
 */

#include <iostream>
#include <cstring>
#include <cctype>
#include <typeinfo>		//allow for the dynamic_cast keyword
#include <stdlib.h>		//for the rand() function

class manager;						//resolve issue with node class no yet knowing what the transportation class is yet for its pointer
class food;
//==============================================================
//++++++++++++++++ NODE CLASS 2-3-4 TREE++++++++++++++++++++++++
//==============================================================

class node						//node container for the 2-3-4 tree in the manager class
{
	public:
		node();					//node constructor for when we need to split and create a new root, intializes all data and children to NULL

		node *& getchild(int index);		//child getter for traversal in remove_all and display_all	
		int node_delete();			//delete the contents of the whatever node is calling it
		int node_display() const;		//for the displays in the derived classes (dynamically bound)

	protected:

		food * data[3];			//base class pointer, (will be used to send derived class pointers to store)
		node * child[4];		//children pointers for the tree

		//adding new data functions
		int first_item(food * new_item);	//intial base case for adding the very first data item to the tree
		node* split_tree(food *& median);  	//split the full node, hold onto the middle data point in median
		node* what_path(int number); 		//determine what path we need to traverse to based on the data we have
		int add_data(node *& below, food *& median, int IDnumber, bool datapoints, bool pointers);	//insert the newest data into a determined node 
		int add_pointers(node *& below, int belowID, bool pointers); 		//re-organize the child ptrs when new data is added or when a node is split
		int is_leaf();				//determine if the node we are at is a leaf (all children NULL) 
		int is_full(); 				//determine if the node we are on is full and ready to split (all data points are not NULL) 
		
		friend class manager;		//now the manager class can access the node class protected functions without denigned accesss error
};

//===============================================================
//+++++++++++++++++++ FOOD BASE CLASS +++++++++++++++++
//===============================================================

class food						//abstract base class, glue of the food type classes	
{
	public:
		food();					//default constructor
		food(const food & source);		//copy constrcutor 
		virtual ~food() = 0;			//virtual destructor (required for dynamic binding, and for virtal pure abstract class)

		virtual int display() const = 0;	//virtual pure implemented in all the derived classes
		int pullID();				//small getter for the manager class to get the ID value

	protected:					//similar data between all the derived classes
		char * name;				//name attached to the meal item	
		int ID;					//int value we randomly assign to each item, this is also the value base on to insert into the tree	
		int calorie_limit;
		int sugar_limit;
};

//===============================================================
//+++++++++++++++++ DERIVED FOOD TYPE CLASSES +++++++++++++++++
//===============================================================

//+++++++++++++++++ MAIN_COURSE CLASS +++++++++++++++++++++++++++++++
class main_course : public food				//food type stored in the 2-3-4 tree nodes
{
	public:
		main_course();							//default constructor
		main_course(char * tempName, char * foodtype, bool non_gluten, int calorie_lim, int sugar_lim, int number);	//constructor with args
		main_course& operator = (const main_course& item);		//OPERATOR OVERLOADED IN DERIVED = used in the constructor with args
		main_course(const main_course & source);			//copy constructor
		~main_course();							//destructor dynamically bound	

		int display() const;						//display this nodes data dynamically bound func
		friend std::ostream& operator << (std::ostream& output, const main_course& m)	//ostream operator overload
		{
			output << "\n\to Number: " << m.ID << "\n\to Name: " << m.name << "\n\to Meal: " << m.item << "\n\to Calorie Count for Meal: ";
			output << m.calorie_course << "\n\to Calorie Limit: " << m.calorie_limit << "\n\to Sugar Count for Meal: " << m.sugar_course;
			output << "\n\to Sugar Limit: " << m.sugar_limit << "\n\to Gluten Free: ";
			if(m.gluten_free == true)
				output << " YES ";
			else 
				output << " NO ";
			output << "\n";
			return output;
		}

	protected:
		char * item;							//food item, in main course these come from string literals 
		bool gluten_free;						//determines what string literal is assigned to item
		int calorie_course;
		int sugar_course;
};

//+++++++++++++++++ BEVERAGE CLASS +++++++++++++++++++++++++++++++
class beverage : public food				//food type stored in the 2-3-4 tree nodes
{
	public:
		beverage();					//default constructor
		beverage(char * tempName, char * foodtype, bool non_alcoholic, int calorie_lim, int sugar_lim, int number);	//constructor with args
		beverage& operator = (const beverage& item);	//OPERATOR OVERLOADED IN DERIVED = used in constructor with args
		beverage(const beverage & source);		//copy constuctor
		~beverage();					//deconstructor dynamically bound	

		int display() const;				//display this nodes data dynamically bound
		friend std::ostream& operator << (std::ostream& output, const beverage& b)	//ostream operator overload
		{
			output << "\n\to Number: " << b.ID << "\n\to Name: " << b.name << "\n\to Meal: " << b.item << "\n\to Calorie Count for Meal: ";
			output << b.calorie_beverage << "\n\to Calorie Limit: " << b.calorie_limit << "\n\to Sugar Count for Meal: " << b.sugar_beverage;
			output << "\n\to Sugar Limit: " << b.sugar_limit << "\n\to Alcohol Free: ";
			if(b.alcohol_free == true)
				output << " YES ";
			else 
				output << " NO ";
			output << "\n";
			return output;
		}

	protected:
		char * item;					//food item, in main course these come from string literals 
		bool alcohol_free;				//determines what string literal is assigned to item
		int calorie_beverage;
		int sugar_beverage;
};

//+++++++++++++++++ DESSERT CLASS +++++++++++++++++++++++++++++++
class dessert : public food				//food type stored in the 2-3-4 tree nodes
{
	public:						
		dessert();					//default constructor
		dessert(char * tempName, char * foodtype, bool non_dairy, int calorie_lim, int sugar_lim, int number);	//constructor with args
		dessert& operator = (const dessert& item);	//OPERATOR OVERLOADED IN DERIVED = used in constructor with args
		dessert(const dessert & source);		//copy constructor
		~dessert();					//deconstructor dynamically bound


		int display() const;				//display bike objects data	dynamicallty bound
		friend std::ostream& operator << (std::ostream& output, const dessert& d)	//ostream overload 
		{
			output << "\n\to Number: " << d.ID << "\n\to Name: " << d.name << "\n\to Meal: " << d.item << "\n\to Calorie Count for Meal: ";
			output << d.calorie_dessert << "\n\to Calorie Limit: " << d.calorie_limit << "\n\to Sugar Count for Meal: " << d.sugar_dessert;
			output << "\n\to Sugar Limit: " << d.sugar_limit << "\n\to Dairy Free: ";
			if(d.dairy_free == true)
				output << " YES ";
			else 
				output << " NO ";
			output << "\n";
			return output;
		}

	protected:
		char * item;				//food item, in main course these come from string literals 
		bool dairy_free;			//determines what string literal is assigned to item	
		int calorie_dessert;
		int sugar_dessert;
};

//===============================================================
//+++++++++++++++++++ MANAGER 2-3-4 CLASS +++++++++++++++++
//===============================================================
class manager							//manages the 2-3-4 tree that stores the derived objects in the base class node pointer
{								//	handles tree manipulation
	public:
		manager();					//default constructor
		~manager();					//deconstructor

		int insert(main_course * course_object, int number);			//inserts based on the derived class pointer we are being sent
		int insert(beverage * beverage_object, int number);			//this is where my upcasting occurs
		int insert(dessert * dessert_object, int number);			//these are esstianlly wrappers for the inserter function

		int remove_all();				//remove entire list	
		int display();					//client side display call

		//operator overloading
		manager operator + (const manager&) const;	// +
		manager& operator += (const manager&);		// += 
		manager& operator = (const manager&);		// = 
		bool operator <(const manager& M);		// <
		bool operator >(const manager& M);		// >
		bool operator <=(const manager& M);		// <= 
		bool operator >=(const manager& M);		// >=
		friend std::ostream& operator << (std::ostream& output, const manager& M)	// <<
		{
			output << M.group;
			return output;
		}
		friend std::istream& operator >> (std::istream& input, manager& M)		// >>
		{
			input >> M.group;
			return input;
		}
		bool friend operator == (const manager& M, const manager& M2)			// ==
		{
			if(M.group == M2.group)
				return true;
			return false;
		}
		bool friend operator != (const manager& M, const manager& M2)			// != 
		{
			if(M.group != M2.group)
				return true;
			return false;
		}

	protected:
		node * root;					//root node pointer for the tree

		int group;					//operator overloading value work, the number of people attending the dinner

		int inserter(food * new_item, int number);	// inserter check intial base case, send to the split determine and the place 
		int split_determine(node *& root, node *& parent, food *& new_item, food *& mid, int number);//splits up the tree if where we need to insert is full 
		int place(node *& root, food *& new_item, int number); 	//insert the newest data item into the tree once split 	

		int remove_all(node *& root);				//destory the entire tree
		int display(node * root, int & num) const;		//recursivly move through the list to call the derived class displays via the node_display
};


//=======================================================================================
//+++++++++++++++++++ MAIN SUPPORT FUNCTIONS ++++++++++++++++++++++++++++++++++++++++++++
//=======================================================================================
void user_menu(manager & object);					  //show user program options
bool determine(manager & object, int * IDlist, int choice);		  //take that choice and call the appropriate functions

void add_food(manager & object, int * IDlist);					//display food options
void gather_data(manager & object, int * IDlist, int choice, char option);	//get similar data all the derived classes share
void gather_special_data(manager & object, char option, int * IDlist, int calorie_lim, int sugar_lim, int choice);	//get final data and send to insert function
