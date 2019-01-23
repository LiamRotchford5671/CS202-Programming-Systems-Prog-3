//Liam Rotchford
//Nov 15 18

#include "Food.h"
using namespace std;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ================== NODE CLASSS =======================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//CONSTRUCTOR
//when a new root or new node is create via a split we intialize a new node with all data food pointers and child pointers set to null
node::node()
{
	for(int i = 0; i < 3; ++i)
	{
		data[i] = NULL;
	}

	for(int j = 0; j < 4; ++j)
	{
		child[j] = NULL;
	}
}

//=============================================================================================================

//CHILD POINTER GETTER
//this function is my getter used to pull the child pointers from the node when we are traversing in the display_all or remove_all function
node *& node::getchild(int index)
{	
	if(index == 0)
		return child[0];
	if(index == 1)
		return child[1];
	if(index == 2)
		return child[2];
	if(index == 3)
		return child[3];
}

//=============================================================================================================
//INSERTION ASSITANCE NODE FUNCTIONS

//INTIAL BASE CASE FUNCTION
//we are a currently empty tree and now we input the first data item
int node::first_item(food * new_item)
{
	data[0] = new_item;            //add our data to middle data location in the node
	return 1;
}

//=============================================================================================================

//NODE SPLITTER
//this function is called when we determine where we need to insert our newest data item is a full node and we need to split it,
//we save the middle data point into median and then create a new node to store the 3rd data item and the child pointers attached to that data sections (child 2 & 3)
//we reset every we saved into our new temp varibles back to NULL in our original root node that we currently are on, now making it not full ready to be attached
//to either the newest root or the parent above
node* node::split_tree(food *& median)
{
	median = data[1];       //data that will be added to the parent
	data[1] = NULL;		//set the root data[1] to now be null since we saved the data

	node * largest = new node;	//create a new node to hold the right most data and the children attached to it in the root node
	largest->data[0] = data[2];
	data[2] = NULL;

	largest->child[0] = child[2];	//save the children attached to the largest node data
	largest->child[1] = child[3];

	child[2] = NULL;		//reset the root child pointers to NULL since we saved their ptrs in largest
	child[3] = NULL;

	return largest;
}

//=============================================================================================================

//INSERT TRAVERSER CHILD DETERMINER
//this function is called when we are recursing through our tree based on the newest data item that we are adding in. we are using the random number assinged
//to each derived object to determine our comparisons on what child we shoudl traverse to next. using a food class getter to pull in the ID value we are able to 
//compare to our newest data and where we should be traversing
node* node::what_path(int number)
{
	if(data[0] != 0 && number < data[0]->pullID())                  //check for left most data point
		return child[0];					//if numberue is less than it send to child 0 left most

	else if(number >= data[0]->pullID() && data[1] == 0)		//if the number is greater or equal to the left most data and we have no mid data
		return child[1];					//return child 1

	else if( (data[0] != 0 && data[1] != 0) && (number >= data[0]->pullID() && number < data[1]->pullID()) ) //if we have both the first and second data points
		return child[1];					//if less than first and greater than second send to child 1

	else if( (data[1] != 0 && data[2] == 0) && (number >= data[1]->pullID()) )          //check if we have both second and third data points
		return child[2];					//if less than second and greater than third then send to child 2

	else if( (data[1] != 0 && data[2] != 0) && (number >= data[1]->pullID() && number < data[2]->pullID()) )
		return child[2];					//if we have the first and second data points and our new data is more or equal to the 
									//first but less than the second return child 2
	else if(data[2] != 0 && number >= data[2]->pullID())            //check if we have the right most data point
		return child[3];					//if greater than right most send to child 3

	return NULL;	//no case hit so return null
}

//=============================================================================================================

//IS OUR CURRENT NODE A LEAF
//this function is used after our tree is split and we are ready to insert our data, we can only insert at a leaf so check if all of our children are null
int node::is_leaf()
{
	if(child[0] == NULL && child[1] == NULL && child[2] == NULL && child[3] == NULL)        //are we a leaf
		return 1;
	return 0;
}

//=============================================================================================================

//IS OUR CURRENT NODE A FULL NODE
//this function determines if the node we are currently on is full, this is called when we are adding new data we need to check if the node where we need to 
//add is a full node, if we are we will need to split the node into a parent node, with 2 children. so check if all the data indexs are not NULL
int node::is_full()
{
	if(data[0] != NULL && data[1] != NULL && data[2] != NULL)		//are we a full node, every index has a food pointer
		return 1;
	return 0;
}

//=============================================================================================================

//DATA ADJUSTMENT
/* The function is used for data adjustment when we recently split a full node or are adding our newest data, we send in median that can be the middle data point
 * of a split node or the data of the newest data to add, and IDnumber which is what we use to compare data with to determine the place in the node the data
 * should go is the ID number for either the mid data of the split node or the newest data, it will compare where it should go and move already exsisting
 * data points around the data array in node to insert the data.
*/
int node::add_data(node *& below, food *& median, int IDnumber, bool datapoints, bool pointers)
{
	//data adjustment and placement

	if(datapoints == true)		//if we call the function when we wish to adjust the data in the node
	{
		if(data[0] == NULL && data[1] == NULL && data[2] == NULL)        //new node case, all data is 0
		{
			data[0] = median;					 //median can be the mid data point of a split node or our newest data

		}else if(data[0] != NULL && data[1] == NULL)			 //determine if we only have the first data point
		{
			if(IDnumber < data[0]->pullID())                         //if our data to add in is less then set as data[0]
			{
				data[1] = data[0];				 //move over the old first data point and set new data as the first 
				data[0] = median;
			}
			else
				data[1] = median;				 //if not less then set as the second data point since its bigger than first

		}else if(IDnumber < data[0]->pullID())				 //if our data to add is less than the first data point and we also have the 
		{								 //second data point not null then move all the data over by one and input the 
			data[2] = data[1];					 //newest data as the first data point
			data[1] = data[0];
			data[0] = median;

		}else if(IDnumber < data[1]->pullID())				 //our data to add is less than the second data point
		{								 //only move the second data point over to the right by one index and make new  
			data[2] = data[1];					 //data the second data point
			data[1] = median;

		}else								 //our data to add is larger than the second data point so add it to data point 3
			data[2] = median;                          //set val to right most
	}

	return add_pointers(below, below->data[0]->pullID(), pointers);
}

//=============================================================================================================

//ADJUST POINTERS
/* this function will take in below which can be either largest which we made in the spilt node function, or it will be the old root of a spilt node
 * that holds the smallest data of the spilt node. so this function will use the new parent node of the spilt node to attach the parents children to its new
 * children that it spilt into, it will use the largest or old root ID number to determine what child ptr the parent should set that node as. if the parent 
 * child ptrs need to move to make root for the new child then they will adjust.
*/
int node::add_pointers(node *& below, int belowID, bool pointers)
{
	// ++++++++++++++++pointer adjustment and placement ++++++++++++++++++++++++ //

	if(pointers == true)
	{
		if(belowID < data[0]->pullID())			//the below node ptr can be eiter the largest node that we created when we spilt the node or the  
		{						//old root that go spilt which holds the smallest data of that node
			if(child[0] == NULL)			//using belowID which is the ID number of one of those nodes we compare to the current nodes
				child[0] = below;		//data to determine where the child ptrs should go to attach below "largest or root"
			else					//if the very first child is null and our below ID is less than the first data point then
			{					//set as the first data point moving the old child ptrs to the right if needed
				child[3] = child[2];
				child[2] = child[1];
				child[1] = child[0];
				child[0] = below;
			}
		}
		else if(belowID >= data[0]->pullID() && data[1] == NULL)      //add largest pointer to the inner left
		{							      //if the below ID is greater than the first data point and the second data is null
			if(child[1] == NULL)				      //then add to the first child
				child[1] = below;
			else
			{
				child[3] = child[2];
				child[2] = child[1];
				child[1] = below;
			}
		}
		else if(belowID >= data[0]->pullID() && data[1] != NULL && belowID < data[1]->pullID()) //add largest pointer to the inner left
		{
			if(child[1] == NULL)						//we have both the first and second data points and our
				child[1] = below;					//below ID is between them then make the first data point
			else
			{
				child[3] = child[2];
				child[2] = child[1];
				child[1] = below;
			}
		}
		else if(belowID >= data[1]->pullID() && data[2] == NULL)              //add largest pointer to inner right
		{
			if(child[2] == NULL)						//we are greater than the second data point, and the thrid data point
				child[2] = below;					//doesnt exist so we make it the 3 child point
			else
			{
				child[3] = child[2];
				child[2] = below;
			}
		}
		else if(belowID >= data[1]->pullID() && data[2] != NULL && belowID < data[2]->pullID())  //add largest pointer to inner right
		{
			if(child[2] == NULL)						//if both the second and third data is exists and our 
				child[2] = below;					//below data is inbeteen them then make it the third child
			else
			{
				child[3] = child[2];
				child[2] = below;
			}
		}
		else    //below->data[0] >= data[2]                     //add largest pointer to righter most since we are larger than the thrid data 
			child[3] = below;
	}

	return 1;
}

//=============================================================================================================

//+++++++++++++++++++++++++ NODE CLASS FUNCTIONS +++++++++++++++++++++++

//DELETE DATA IN THE NODE
//delete the contents of the node, of whatever node is calling it, (head->node_delete)
int node::node_delete()
{	
	for(int i = 0; i < 3; ++i)
	{
		delete data[i];
		data[i] = NULL;
	}

return 1;
}

//================================================================================================================

//DOWNCAST TO CALL DERIVED DISPLAY FUNCTIONS
//this funciton is called on each cycle on the manager classes recursive diplay function to call the derived class object personal display so it can disp the 
//speacilized data, this downcasts and then calls the display in the correct derived class 
int node::node_display() const
{	
	for(int i = 0; i < 3; ++ i)
	{	
		main_course * mptr = dynamic_cast<main_course*>(data[i]);		//downcast
		if(mptr)						//determine if we are that type RTTI
			mptr->display();				//call the the correct derived class display function

		dessert * bptr = dynamic_cast<dessert*>(data[i]);		//same for all
		if(bptr)
			bptr->display();

		beverage * cptr = dynamic_cast<beverage*>(data[i]);
		if(cptr)
			cptr->display();
	}

	for(int j = 0; j < 4; ++j)				//print what children the node has and what they attach to so its easy to understand the tree
	{
		if(child[j] == NULL)
			cout << "Child[" << j << "] is X" << endl;
		else
			cout << "Child[" << j << "] is connected to " << child[j]->data[0]->pullID() << endl;
	}

	return 0;
}

//==========================================================
//+++++++++++++++ MANAGER BASE CLASS (DLL MANAGER) +++++++++++++++++++++++
//==========================================================

//CONSTRUCTOR
//default constructor set head and tail to NULL
manager::manager() : root(NULL)
{
}

//DECONSTRUCTOR
//deconstructor for the list, call the recursive deconstruct function to remove all nodes in the list
manager::~manager()
{
	if(!root)
		cout << endl;	
	else
		int hold = remove_all(root);
}

//======================================================================================================================
	
//REMOVE ALL
//user call deconstructor remove all fuction, to remove all nodes from the list, however calling this wont end the program
int manager::remove_all()
{
	if(!root) return 0;

	else
		int hold = remove_all(root);
	
	return 1;
}

//REMOVE ALL RECURSIVE
//move to each leaf and remove the node by using the node delete function in the node class
int manager::remove_all(node *& root)
{
	if(!root) return 0;

	int found = remove_all(root->getchild(0));	//post order traverse
	found = remove_all(root->getchild(1));
	found = remove_all(root->getchild(2));
	found = remove_all(root->getchild(3));	
	
	if(root->is_leaf())				//check if we are a leaf
	{
		root->node_delete();			//call the node delete to remove the leaf data
		delete root;				//remove the node itself
		root = NULL;
	}

	return found;
}

//========================================================================================================================================

//CREATE NEW NODE AND SET DATA BASED ON DERIVED POINTER SENT IN
//These three functions are for when we have created our data stored derived object in the support.cpp and are being sent a derived class pointer
//based on that pointer match on the argument list it will call one of these functions and perform upcasting, it will create a new node and set the 
//new derived pointer to be set onto the base class pointer in the node setter function as the DLL data, it will then send it to the DLL inserter function
//to add it to the list
int manager::insert(main_course * course_object, int number)	
{	
	return inserter(course_object, number);
}

int manager::insert(beverage * beverage_object, int number)	//same as above	
{
	return inserter(beverage_object, number);
}

int manager::insert(dessert * dessert_object, int number)	//same as above	
{
	return inserter(dessert_object, number);
}

//INSERT WRAPPER
//the food * is teh newest derived pointer object containing all of our new data to insert into the tree, it will first check if we have a empty list and if we 
//do then it will call first item and insert our first data point into the newly made root node pointer. after that it will create a median pointer in the event
//we need to spilt the full node where we plan to insert into by assinging the 2nd data point to it. it will also make a parent node pointer that will always 
//be on the parent of the node we are currently on in the tree. we then go into spilt determine to check through the tree traversing to where in the tree we
//need to insert our new data. once we spilt or dont, then we move into the place object to add the new data into the tree
int manager::inserter(food * new_item, int number)
{
	if(!root)                                               //check intial base case to see if we have an emptry tree
	{
		root = new node;				//if we are then create root and send to first_item function to assign the first data
		root->first_item(new_item);	
		return 1;                                       //return 
	}

	food * median = NULL;					//create median to store the mid data when we spilt a full node
	node * parent = NULL;					//create the parent holder node to hold onto the parent node when we move through the tree
	int result = split_determine(root, parent, new_item, median, number);	//of whatever node we are on, now send into spilt determine to check
								//where we are adding the new data and if we need to spilt the node if its full and
	place(root, new_item, number);				//and adjust the tree, and once adjusted then fully add in our data to the tree

	return 1;
}

//SPLIT TREE
/* this function will move through the tree and traverse to where it needs to go based on the ID number of the data were adding to the tree, we will check if
 * we are a full node and if we are spilt the node, depending on if we are the original root of the tree we will create a new ndoe and set the largest and smallest
 * data nodes to be the mid datas children that are to be attached as now 3 nodes in the tree. if not it will add the mid data to parent node and the children
 * adjust to the parent node. 
*/
int manager::split_determine(node *& root, node *& parent, food *& new_item, food *& median, int number)
{
	if(!root)
		return 0;

	if(root->is_full())					//determine if we are a full node
	{
		node * largest = root->split_tree(median);      //data contains in spilted is greater than median,  

		if(root == this->root)				//if we are still on the original root of the tree
		{
			node * temp = new node;			//create a new node to be the newest root since root needs to spilt into 3 nodes
			temp->add_data(largest, median, median->pullID(),true, true);    //adjust the data and children, add the largest node to the new root
			temp->add_data(root, median, median->pullID(), false, true);	 //adjust the children to add the old root to the new root as a child 

			this->root = temp;			//set the new root to be the newly created node
			return 1;
		}

		if(parent != NULL)				//if our parent isnt NULL then we arent at the orginal node, we have more than one node
		{
			parent->add_data(largest, median, median->pullID(), true, true);  //do both the data placement and adjustment attach the largest node
			return 1;							  //to the parent node i.e set mid data to the parent, and attach the
		}									  //largest node, the current root is already attached to the parent node
	}

	parent = root;						//set the parent to the current node before traversing to the next node
	node * temp = root->what_path(number);                             //what child do we go to next   
	return split_determine(temp, parent, new_item, median, number);              //node function to find correct path based on value trying to add
}

//PLACE...ADD DATA
//once we know the tree is spilted where we need to add our data or determine the node where we need to insert has a open data spot in the array then we can add in 
//our data, we traverse to the correct node using the what path fucntion using our new data ID to compare and move to the correct loaction in the tree
//then we we determine that we are a leaf and then call the add_data function to place our new data into the tree
int manager::place(node *& root, food *& new_item, int number)
{
	if(!root)
		return 0;

	if(root->is_leaf())
	{
		root->add_data(root, new_item, new_item->pullID(), true, false); //node functions determine insert only data is worked on        
		return 1;
	}

	node * temp = root->what_path(number);                             //what child do we go to next   
	return place(temp, new_item, number);               //node function to find correct path based on value trying to add
}

//========================================================================================================================================

//DISPLAY WRAPPER
//client call display function to display the entire tree
int manager::display()
{	
	if(!root)
	{
		cout << "Root is null" << endl;	
		return 0;
	}
	int num = 1;	//to number each item in teh list
	cout << "\nO Dinner Course Tree: " << endl;
	cout << "==========================================" << endl;

	return display(root, num);	//call display recurse
}

//DISPLAY RECURSIVE
//this function will move through the entire tree and call the node display function from the node class with whereever the head is current on in the list
//the node function will downcast and determine what derived pointer is stored in that node and then it will call the derived display function so the 
//speacilized data is displayed
int manager::display(node * root, int & num) const
{
	if(!root)
		return 1;

	cout << "\no Dinner Course #" << num << "\n+++++++++++++++++++++++" << endl;	

	root->node_display();	//call node display to downcast and call derived dynamically bound diaply funciton

	cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	++num;	

	return display(root->getchild(0), num) + display(root->getchild(1), num) + display(root->getchild(2), num) + display(root->getchild(3), num); 
}

//OPERATOR OVERLOADING FOR <, > , <= , >= , +, +=, = (== , != , <<, >> can be found in my Food.h manager class) 
//======================================================================================================================
// RATIONAL OVERLOAD

//determine if group 1 is less than group 2 manager objects in main.cpp
bool manager::operator <(const manager& M)
{
	if(group < M.group)
		return true;
	return false;
}
//determine if group 1 is more than group 2 manager objects in main.cpp
bool manager::operator >(const manager& M)
{
	if(group > M.group)
		return true;
	return false;
}

//determine if group 1 is less than or equal to group 2 manager objects in main.cpp
bool manager::operator <=(const manager& M)
{
	if(group <= M.group)
		return true;
	return false;
}

//determine if group 1 is more than equal to group 2 manager objects in main.cpp
bool manager::operator >=(const manager& M)
{
	if(group >= M.group)
		return true;
	return false;
}

//======================================================================================================================
// + += = over load for manager objects working with the in group value in the manager class  

//add 2 manager objects together into a new third object of manager class
manager manager::operator + (const manager& M) const
{
	manager newest;
	newest.group =  this->group + M.group;

	return newest;
}
//add 2 manager objects together into an already exsisting object of the manager class
manager& manager::operator += (const manager& M)
{
	this->group += M.group;
	return *this;
}
//assign one object to have the same group value as another group object
manager& manager::operator = (const manager& M)
{
	this->group = M.group;
	return *this;
}

//======================================================================================================================


