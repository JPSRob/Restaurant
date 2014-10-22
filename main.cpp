#include "Inventory.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    int userInput = 0;
    bool flag = 0;

    string blah = "Bread.txt";

    Inventory restaurant;

    restaurant.updateInvo();
    restaurant.printInvoVector();
    restaurant.updateInvo();

    vector <vector <string> > result = restaurant.returnItemsInCategory(blah);

    while(flag == 0)
    {
        restaurant.updateInvo();

        cout << endl << endl << "Please input 1 or 2." << endl;
        cin >> userInput;

        if(userInput == 1)
        {
            restaurant.addItem();
        }
        else if(userInput == 2)
        {
            restaurant.addToExistingCat();
        }
        else if(userInput == 3)
        {
            restaurant.deleteAllCategories();
        }
        else if(userInput == 4)
        {
            restaurant.printInvoVector();
        }
        else if(userInput == 5)
        {
            restaurant.printAllCategories();
        }
        else if(userInput == 6)
        {
            restaurant.returnItemsInCategory(blah);
        }
        else if(userInput == 100)
        {
            flag = 1;
        }
    }


    return 0;
}
