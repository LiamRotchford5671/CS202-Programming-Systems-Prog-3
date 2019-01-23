# CS202-Programming-Systems-Prog-3
Program 3 assigned under Karla Fant at Portland State University

Description:

This program implements Dynamic binding (upcasting, downcasting). The specfic heiarchy is decribed in the Food.h file description. Using a 2-3-4 tree, we allow the user to select from 3 food types for a dinner party (derived classes) and we then prompt for general data and then speacilized data based on the food type selected. We store that data intialized to a newly created object pointer of the derived class and then send it to be inserted into the food base class pointer array in our node into the 2-3-4 tree, This program allows insert, remove all, and display options with the tree

Data Structure: 2-3-4 Tree

      Hierarachy 1:
      
         Food           Food           Food
          |               |             |
          |               |             |
          Main_course     Beverage      Dessert
      
      Hierarachy 2:
      
          Manageer -----Node
        
