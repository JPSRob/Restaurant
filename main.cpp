#include "Inventory.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    int userInput = 0;
    bool flag = 0;

    while(flag == 0)
    {
        Inventory restaurant;

        cout << "Please input 1 or 2." << endl;
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
        else if(userInput == 100)
        {
            flag = 1;
        }
    }


    return 0;
}
