//Liam Rotchford
//Nov 15 18

/* This file mainly handles the user display menus and prompts for gaining nessessary data from the user about the data for each food items. This file also controls
 * the choices for what the user may want to do with the list to correctly call the class functions. If the user selects to add a new food item to the tree they are
 * prompted first for the shared similar data all units share, and then are taken to speacilized functions to gain the speacilized data. We then send all of those
 * temp varibles and send them into a constructor with args to intilaize that data to a new derived object. That object is then assigned to a derived pointer
 * sent into the insert class function to be added to the tree
 */

#include "Food.h"

using namespace std;

/* This function is the first function the user enters from main and it displays the user menu of options for working with the list, there is a try catch block to 
 * make sure input on the choice is handled at run time. In the event they dont enter a valid input on the choice the program will default to quit and end. If 
 * however the input is valid it will enter the function determine, defined below. Based on the return from define from determine the program will end or 
 * keep looping the menu options prompt until the user quits or enters an invalid input
 */
void user_menu(manager & object)
{
	bool valid = false;
	int choice = 0;
	int * IDlist = NULL;		//int dynamic array that will hold a rand int value where the array will be used to make sure we dont end up with duplicates
	IDlist = new int[20];		//these rand int values is what we will use to insert into the tree and where it will go
	for(int i = 0; i < 20; ++i)	//intialize all indexs to 0
		IDlist[i] = 0;

	do
	{	//user menu options to manipulate the tree
		cout << "\n\nO Food Selection User menu: " << "\n======================================================================================" << endl;	
		cout << "\n\n\t1) Add new food item" << endl;
		cout << "\n\t2) Remove all food items" << endl;	
		cout << "\n\t3) Display all food items" << endl;	
		cout << "\n\t4) Quit " << endl;

		cout << "\n\n\to Selection: ";
		cin >> choice;
		cin.ignore(100, '\n');

		try{	//test to see if input is valid
			if(choice != 1 && choice != 2 && choice != 3 && choice != 4)
				throw choice;
		}
		catch(int)	//non valid input defaults to quit option to end the program
		{			
			cout << "\n\t+ Non valid selection given, defaulting to 4) Quit" << endl;
			choice = 4;
		}

		if(!determine(object, IDlist, choice))		//valid input gets sent into the determine function, if the user choose quit when it returns it will
			valid = true; 				//set valid to true and exit the do while loop and end the program

	}while(!valid);

	delete [] IDlist;	//once we exit this loop the user selected to Quit so lets delete the memory of the array
	IDlist = NULL;
	cout << "\n\n\to Thank you for using the dinner party food menu!!!\n\n\n\n" << endl;
}

/* This funciton takes the choice input from the user in the above function and determines what class member function or support function to call appropriate
 * to the user selection. If the user chose 4) quit then we return 0 and end the program
 */
bool determine(manager & object, int * IDlist, int choice)
{
	switch(choice)		//determine case by the user choice varible
	{
		case 1:
			add_food(object, IDlist);	//send to support function to take in user input into temp varibles to be initialized to new derived object
			break;
		case 2:
			{
				if(!object.remove_all())	//send to remove_all class fucntion
					cout << "\n\n\t+ Not all the food items have been removed from the tree" << endl;
				else
					cout << "\n\n\t+ All food items have been removed from the from the tree" << endl;
			}
			
			break;
		case 3:
			{
				if(!object.display())		//send to the display class member function
					cout << "\n\t\t+ Food item tree is currently empty" << endl;
			}
			break;
		case 4:
			return 0;				//user chose to quit the program
	}
	return 1;
}


/* This function is for when the user has selected to add a new food item to the tree, we first display the list prompt for the type of options we 
 * have availble. then based of the food type they choose we then determine any diet restrictions that will help us determine what food string literal to store
 * into the tree with the derived object that it gets assigned to
 */
void add_food(manager & object, int * IDlist)
{
	bool valid = false;
	int choice = 0;
	char option = 0;

	do		//display the types of rental units they user can rent
	{
		cout << "\n\no Food Type Options: " << endl;
		cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "\n\n\t1) Main course " << endl;
		cout << "\n\t2) Beverage " << endl;
		cout << "\n\t3) Dessert " << endl;

		cout << "\n\n\to Please make your selection: ";
		cin >> choice;
		cin.ignore(100, '\n');

		if(choice == 1 || choice == 2 || choice == 3)	//input checker
			valid = true;
		else
		{
			cout << "\n\tO Please only make your selection from the given options above. ";
			cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n" << endl;
		}
	}while(!valid);

	cout << "\no Diet Restrictions: ";	//based on the user choice of what kind of item they want we now determine the diet restrictions if any
	cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n" << endl;

	switch(choice)
	{
		case 1:
			{
				cout << "\n\to Do you need a gluten free dish? (Y - Now / N - Later) : ";
				cin >> option;							//gluten free	
				cin.ignore(100,'\n');
				option = toupper(option);
			}
			break;

		case 2:
			{
				cout << "\n\to Do you need a non-alcoholic drink? (Y / N) : ";		//non alcoholic
				cin >> option;
				cin.ignore(100,'\n');
				option = toupper(option);
			}
			break;

		case 3:
			{
				cout << "\n\to Do you need a dairy free dessert? (Y / N) : ";		//dairy
				cin >> option;
				cin.ignore(100,'\n');
				option = toupper(option);
			}	
			break;	
	}
	try{
		if(option != 'Y' && option != 'N')				//try block to check input
			throw option;
	}
	catch(char){								//if a non valid is received it will default to 'N'
		cout << "\n\t\t+ Non-given option received, auto correcting to 'N'" << endl;
		option = 'N';
	}

	gather_data(object, IDlist, choice, option);		//gather data function call
}

/* this function will use the for loop to cycle through the 2 prompts for the user to now input any calorie or sugar restrictions they may have 
 * this is so we dont have to write the try catch block twice, we also provide the typical measurements of how much has what depending on the item they choose.
 */
void gather_data(manager & object, int * IDlist, int choice, char option)
{
	int calorie_lim = 0, sugar_lim = 0;
	option = 0;	

	for(int i = 1; i < 3; ++i)	//cycle through the 2 prompts
	{
		switch(i)
		{
			case 1:		//calorie prompt
				{
					cout << "\n\n\to If you have a calorie limit please enter the limit" << endl;
					cout << "\n\t\t+ One meal typically has 150 cal, one drink typically has 60 cal, one dessert typically has 200 cal" << endl;
					cout << "\n\t\t+ Selection: ";
					cin >> calorie_lim;
					cin.ignore(100, '\n');
				}
				break;

			case 2:		//sugar prompt
				{
					cout << "\n\n\to If you have a sugar limit please enter the limit" << endl;
					cout << "\n\t\t+ One meal typically has 25 grams, one drink typically has 15 g, one dessert typically has 50 g" << endl;
					cout << "\n\t\t+ Selection: ";
					cin >> sugar_lim;
					cin.ignore(100, '\n');
				}
				break;
		}		
		try{					//if the input is less than 0 default it to 0
			if(calorie_lim < 0)
				throw calorie_lim;
			if(sugar_lim < 0)
				throw sugar_lim;
		}
		catch(int){				//if a negative value is given it will default to 0
			cout << "\n\t\t+ Non-valid limit given, auto correcting to 0" << endl;
			if(calorie_lim < 0)
				calorie_lim = 0;
			if(sugar_lim < 0)
				sugar_lim = 0;
		}
	}

	gather_special_data(object, option, IDlist, calorie_lim, sugar_lim, choice);	//send to the gather speacilized data function to get the food data

}

/* This function is embaressingly large but thats mainly becuase of the switch block that segregates each derived class food type based on what the user choose,
 * we allow the user to attach there name to the food item so its easy to determine who's is who's on the display, and then we determine a random number to attach
 * to the food item as long as we know we dont have a duplicate of the int based in our int* array. We use this value to determine where this new item will go in the * tree and then it takes all of the created temp varibles and creates a new derived object of that rental type class sending it to a constructor with arguments to 
 * intilized the user data into the object, we then set a pointer to it and send that pointer into the insert fuinction to be put into the tree
 */
void gather_special_data(manager & object, char option, int * IDlist, int calorie_lim, int sugar_lim, int choice)
{	
	char * foodtype = NULL;
	char * tempName = NULL;	
	char buffer[20];	
	bool non_gluten = false, non_alcoholic = false, non_dairy = false, validnum = false;
	int number = 0, zeroindex = 0;
	
	//attach tempname to be added to the derived object to be added
	cout <<"\n\n\to Now that we have your data PLEAsE ENTER IN YOUR NAME to be placed with your item. \n\t\t+ Enter Name: ";
	cin.get(buffer, 20, '\n');
	cin.ignore(100, '\n');
	tempName = new char[strlen(buffer)+1];
	strcpy(tempName, buffer);

	do{					//determine a random number to be attached to the new food item, used to sort through the list to 
		validnum = false;		//determine where it should be placed
		number = rand() % 100 + 1;	//select ID number between 1 and 100
		for(int i = 0; i < 20; ++i)	//make sure we dont already have that value
		{
			if(number == IDlist[i])	
				validnum = true;
			if(IDlist[i] == 0)	//when we reach our next 0 save that index
				zeroindex = i;
		}
	}while(validnum);

	IDlist[zeroindex] = number;		//using that 0 index add our newest int value	

	cout << "\n\to You will now also be assigned a randomized number with your meal. \n\t\t+ Meal Number: " << number << endl;

	switch(choice)		//determine what food item they wanted
	{
		case 1:			//MAIN COURSE
			{
				if(non_gluten == true)				//depandant on the diet restrictions the user was asked will determine the 
				{						//food item they will be given
					char main2[15] = "veggie stirfry";
					foodtype = new char[strlen(main2)+1];	//create it dynamic
					strcpy(foodtype, main2);
				}else
				{
					char main1[6] = "pasta";
					foodtype = new char[strlen(main1)+1];
					strcpy(foodtype, main1);
				}

				if(option == 'Y' && choice == 1)			
					non_gluten = true;
				//create the new derived object that will be added to the tree along using all of the temporary data values
				main_course * course_object = new main_course(tempName, foodtype, non_gluten, calorie_lim, sugar_lim, number);	
				cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;	
				cout << "\n\to You are adding the following data to the tree: " << endl;
				cout << "\n\t+ New Data: \n" << *course_object << endl;		//ostream derived class overload
				object.insert(course_object, number);				//insert object pointer into the tree
			}
			break;

		case 2:			//BEVERAGE
			{					
				if(non_alcoholic == true)		//determine what string literal is assigned to the new derived pointer
				{					//based on user inputed diet restricion
					char drink2[5] = "soda";
					foodtype = new char[strlen(drink2)+1];	//create it dynamic
					strcpy(foodtype, drink2);
				}else
				{
					char drink1[5] = "wine";
					foodtype = new char[strlen(drink1)+1];
					strcpy(foodtype, drink1);
				}

				if(option == 'Y' && choice == 2)
					non_alcoholic = true;

				//create the new derived object that will be added to the tree along using all of the temporary data values
				beverage * beverage_object = new beverage(tempName, foodtype, non_alcoholic, calorie_lim, sugar_lim, number);
				cout << "\n\to You are adding the following data to the tree: " << endl;						
				cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;	
				cout << "\n\t+ New Data: \n" << *beverage_object << endl;	//ostream derived class overload
				object.insert(beverage_object, number);				//insert pointer object into the tree
			}
			break;

		case 3:			//DESSERT
			{
				if(non_dairy == true)				//determine what string literal is assigned to the new derived pointer
				{						//based on user inputed diet restriction
					char treat2[14] = "vegan brownie";
					foodtype = new char[strlen(treat2)+1];	//create it dynamic
					strcpy(foodtype, treat2);
				}else
				{
					char treat1[10] = "ice cream";
					foodtype = new char[strlen(treat1)+1];
					strcpy(foodtype, treat1);
				}

				if(option == 'Y' && choice == 3)
					non_dairy = true;							

				//create the new derived object that will be added to the tree along using all of the temporary data values
				dessert * dessert_object = new dessert(tempName, foodtype, non_dairy, calorie_lim, sugar_lim, number);	
				cout << "\n\to You are adding the following data to the tree: " << endl;	
				cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;	
				cout << "\n\t+ New Data: \n" << *dessert_object << endl;	//ostream derived class overload
				object.insert(dessert_object, number);				//insert pointer object into the tree
			}
			break;
	}

	delete [] foodtype;				//all of these will create a dynamic char* of rental type so delete it 
	foodtype = NULL;
	delete [] tempName;				//delete the dynamic temp name now that its been added to the derived pointer and put into the tree
	tempName = NULL;
}

