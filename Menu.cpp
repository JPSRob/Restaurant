#include<iostream>
#include<iterator>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include "Menu.h"

using namespace std;

vector<vector<string> > Menu::readFileToVector(string filename)
{
    vector <vector <string> > returnVector;
    //returnVector.resize( 1 );
    ifstream file(filename.c_str());
    string line;
    if (file)
    {
        string dataItem;
        stringstream iss;
        int lineCount =0;
        while ( getline(file, line) )
        {
            iss << line;
            returnVector.resize( returnVector.size()+1 );
            while ( getline(iss, dataItem, ',') )
            {
                returnVector[lineCount].push_back(dataItem);
            }
            iss.clear();
            lineCount++;
        }
    }
    file.close();
    return returnVector;
}

void Menu::writeVectorToFile(vector<vector<string> > v, string filename)
{
    ofstream file_out(filename.c_str());
    for (size_t i=0; i< v.size(); i++)
    {
        for(size_t j = 0; j < v[i].size(); j++)
        {
            file_out << v[i][j] << ',';
        }
        if (i< v.size()-1)
        {
            file_out << endl;
        }
    }
}

void Menu::printVector(vector<vector<string> > inputVector, int colsCutOff)  // will print columns 0 through lastCol - cutoff
{
        // print the input Vector to the screen
        for ( size_t i = 0; i < inputVector.size(); i++ )
        {
            for ( size_t j = 0; j < inputVector[i].size()-colsCutOff; j++ )
            {
                cout << inputVector[i][j] << ' ';
            }
            if (i< inputVector.size()-1)
            {
                cout << endl;
            }
        }
}

void Menu::printVector(vector<string> inputVector)  // will print columns 0 through lastCol - cutoff
{
        // print the input Vector to the screen
        for ( size_t i = 0; i < inputVector.size(); i++ )
        {

                cout << inputVector[i] << ' ';

            if (i< inputVector.size()-1)
            {
                cout << endl;
            }
        }
}

string Menu::int_to_string(int n)  // from big C++ chapter 9
{
    ostringstream outstr;
    outstr << n;
    return outstr.str();
}

string Menu::double_to_string(double n)
{
    ostringstream outstr;
    outstr << n;
    return outstr.str();
}

int Menu::string_to_int(string s)  // from big C++ chapter 9
{
    istringstream instr(s);
    int n;
    instr >> n;
    return n;
}

void Menu::makeMenuItemSingle()
{
    cout << "Name your new menu item (Single):"<< endl;
    string itemName;
    getline(cin , itemName);
    string itemFilename = itemName + ".txt";
    vector<vector<string> > itemVector;
    itemVector.resize(1);

    cout << "Enter a price for " + itemName + ":" << endl;
    double price=0;
    cin >> price;
    string junk;
    getline(cin , junk);
    itemVector[0].push_back(double_to_string(price));
    /*
    // add new item name to list of menu items (single)
    vector<vector<string> > MenuItemsSingle = readFileToVector("MenuItemsSingle.txt");
    int listSize = MenuItemsSingle.size();
    MenuItemsSingle.resize(listSize+1);
    MenuItemsSingle[listSize-1].push_back(int_to_string(listSize-1));
    MenuItemsSingle[listSize-1].push_back(itemName);
    MenuItemsSingle[listSize-1].push_back(itemFilename);
    writeVectorToFile(MenuItemsSingle, "MenuItemsSingle.txt");
    */
    // pick an inventory item which comprises the menu item

    myInventory.updateInvo();
    cout << "Pick an inventory category to choose from:" << endl;
    // display inventory categories
    myInventory.printAllCategories();
    int userChoice;
    cin >> userChoice;
    getline(cin, junk);
    vector< vector<string> > Categories = readFileToVector("Categories.txt");
    string invoCategoryFilename = Categories[userChoice-1][0];
    // display chosen category
    vector<vector<string> > Category = myInventory.returnItemsInCategory(invoCategoryFilename);
    // print category items
    //printVector(Category,2);
    /*
    cout << "Pick an inventory category to choose from:" << endl;
    vector<vector<string> > InvoCategoryList;
    InvoCategoryList = readFileToVector("InvoCategoryList.txt");
    printVector(InvoCategoryList, 1);
    int userChoice;
    cin >> userChoice;
    getline(cin , junk);
    string invoCategoryFilename = InvoCategoryList[userChoice][2];
    vector<vector<string> > InvoCategory = readFileToVector(invoCategoryFilename.c_str());
    printVector(InvoCategory, 1);
    */
    cout << endl;
    cout << "Pick an inventory item from this inventory category:" << endl;
    cin >> userChoice;
    getline(cin , junk);
    itemVector.resize(2);
    itemVector[1].push_back(int_to_string(userChoice));

    // save itemVector to itemName.txt: contains: Price / InvoItem#
    writeVectorToFile(itemVector, itemFilename);

    // save item in a custom menu Category
    cout << "Pick a menu category to put " + itemName + " in, or input '99' to create a new menu category." << endl;
    vector< vector< string> > MenuCategoryList = readFileToVector("MenuCategoryList.txt");
    printVector(MenuCategoryList, 1);
    cout << endl;
    cin >> userChoice;
    getline(cin , junk);
    if (userChoice==99)
    {
        cout << "Name the new menu category:" << endl;
        string menuCategoryName;
        getline(cin , menuCategoryName);
        // add the new category to the MenuCategoryList
        int listSize = MenuCategoryList.size();
        MenuCategoryList.resize(listSize+1); // add a new row
        MenuCategoryList[listSize].push_back(int_to_string(listSize));  // first column of MenuCategoryList is Category Number
        MenuCategoryList[listSize].push_back(menuCategoryName); // second column of MenuCategoryList is category name
        string menuCategoryFilename = menuCategoryName + ".txt";
        MenuCategoryList[listSize].push_back(menuCategoryFilename); // third column of MenuCategoryList is category filename (which contains list of category's items)
        writeVectorToFile(MenuCategoryList, "MenuCategoryList.txt");

        // make the new menu category
        vector < vector < string> > MenuCategory;
        MenuCategory.resize(1); // add a first row
        // add the new Menu item to the new menu category
        MenuCategory[0].push_back(int_to_string(0));  // the first column in the category has menu item number;
        MenuCategory[0].push_back(itemName);  //the second column contains itemName
        MenuCategory[0].push_back(itemFilename);  // the third column contains the itemFilename
        writeVectorToFile(MenuCategory, menuCategoryFilename);
    }
    else
    {
        string chosenCategory = MenuCategoryList[userChoice][1];
        vector< vector< string> > MenuCategory = readFileToVector(MenuCategoryList[userChoice][2].c_str());
        int listSize = MenuCategory.size();
        MenuCategory.resize(listSize+1); // add a new row
        // add the new Menu item to the chosen menu category
        MenuCategory[listSize].push_back(int_to_string(listSize));  // the first column in the category has menu item number;
        MenuCategory[listSize].push_back(itemName);  //the second column contains itemName
        MenuCategory[listSize].push_back(itemFilename);  // the third column contains the itemFilename
        string menuCategoryFilename = chosenCategory + ".txt";
        writeVectorToFile(MenuCategory, menuCategoryFilename);
    }
}

void Menu::makeMenuItemCompound()
{
    cout << "Name your new menu item (Compound):"<< endl;
    string itemName;
    getline(cin , itemName);
    string itemFilename = itemName + ".txt";
    vector<vector<string> > itemVector;
    itemVector.resize(1);
    cout << "Enter a price for " + itemName + ":" << endl;
    double price=0;
    cin >> price;
    string junk;
    getline(cin , junk);
    itemVector[0].push_back(double_to_string(price));

    /*
    // add new item name to list of menu items (compound)
    vector<vector<string> > MenuItemsCompound = readFileToVector("MenuItemsCompound.txt");
    int listSize = MenuItemsCompound.size();
    MenuItemsCompound.resize(listSize+1);
    MenuItemsCompound[listSize-1].push_back(int_to_string(listSize-1));
    MenuItemsCompound[listSize-1].push_back(itemName);
    MenuItemsCompound[listSize-1].push_back(itemFilename);
    writeVectorToFile(MenuItemsCompound, "MenuItemsCompound.txt");
    */

    // add menu constituent items to the compound menu item
    bool quit=false;
    while (!quit)
    {
        cout << "To add an item to this object, pick a menu category, or '99' to finish." << endl;
        vector<vector<string> > MenuCategoryList = readFileToVector("MenuCategoryList.txt");
        printVector(MenuCategoryList, 1);
        cout << endl;
        int userChoice;
        cin >> userChoice;
        string junk;
        getline(cin , junk);

        if (userChoice==99)
        {
            quit = true;
        }
        else
        {
            //itemCount++;
            string categoryFilename = MenuCategoryList[userChoice][2];  //get filename of chosen category
            vector<vector<string> > Category = readFileToVector(categoryFilename.c_str());
            cout << "Pick a menu item from this menu category:" << endl;
            printVector(Category, 1); // display chosen category
            cout << endl;


            cin >> userChoice;
            string junk;
            getline(cin , junk);
            string itemFilename = Category[userChoice][2];
            vector<vector<string> > tempVector = readFileToVector(itemFilename);
            for (size_t i=1; i<tempVector.size(); i++)
            {
                itemVector.resize(itemVector.size()+1); //cout << "yes" << endl;  // make a new row in itemVector to hold the new item numbers
                string invoNumber = tempVector[i][0]; //cout << "yes" << endl;
                itemVector[itemVector.size()-1].push_back(invoNumber); //cout << "yes" << endl;
            }

              //item Vector will have price in first row, then constituent invo item numbers in rest of rows
        }
    }

    // save itemVector to itemFilename.txt: contains: Price / InvoItem#1 / InvoItem#2, etc
    writeVectorToFile(itemVector, itemFilename);

    // save item in a custom menu Category
    cout << "Pick a menu category to put " + itemName + " in, or input '99' to create a new menu category." <<endl;
    vector< vector< string> > MenuCategoryList = readFileToVector("MenuCategoryList.txt");
    printVector(MenuCategoryList, 1);
    cout << endl;
    int userChoice = 0;
    cin >> userChoice;
    getline(cin, junk);
    if (userChoice==99)
    {
        cout << "Name the new menu category:" << endl;
        string menuCategoryName;
        getline(cin , menuCategoryName);
        // add the new category to the MenuCategoryList
        int listSize = MenuCategoryList.size();
        MenuCategoryList.resize(listSize+1); // add a new row
        MenuCategoryList[listSize].push_back(int_to_string(listSize));  // first column of MenuCategoryList is Category Number
        MenuCategoryList[listSize].push_back(menuCategoryName); // second column of MenuCategoryList is category name
        string menuCategoryFilename = menuCategoryName + ".txt";
        MenuCategoryList[listSize].push_back(menuCategoryFilename); // third column of MenuCategoryList is category filename (which contains list of category's items)
        writeVectorToFile(MenuCategoryList, "MenuCategoryList.txt");

        // make the new menu category
        vector < vector < string> > MenuCategory;
        MenuCategory.resize(1); // add a first row
        // add the new Menu item to the new menu category
        MenuCategory[0].push_back(int_to_string(0));  // the first column in the category has menu item number;
        MenuCategory[0].push_back(itemName);  //the second column contains itemName
        MenuCategory[0].push_back(itemFilename);  // the third column contains the itemFilename
        menuCategoryFilename = menuCategoryName + ".txt";
        writeVectorToFile(MenuCategory, menuCategoryFilename);
    }
    else
    {
        string chosenCategory = MenuCategoryList[userChoice][1];
        vector< vector< string> > MenuCategory = readFileToVector(MenuCategoryList[userChoice][2].c_str());
        int listSize = MenuCategory.size();
        MenuCategory.resize(listSize+1); // add a new row
        // add the new compound Menu item to the chosen menu category
        MenuCategory[listSize].push_back(int_to_string(listSize));  // the first column in the category has menu item number;
        MenuCategory[listSize].push_back(itemName);  //the second column contains itemName
        MenuCategory[listSize].push_back(itemFilename);  // the third column contains the itemFilename
        string menuCategoryFilename = chosenCategory + ".txt";
        writeVectorToFile(MenuCategory, menuCategoryFilename);
    }

}

void Menu::takeOrder()
{
    vector<string>  orderList;
    vector<string> itemsList;
    double total=0;
    bool done=false;
while (!done)
{
    cout << "Current order:" << endl;
    printVector(orderList);
    cout << endl;
    cout << "Pick a menu category, or '99' to finish order." << endl;
    vector<vector<string> > MenuCategoryList = readFileToVector("MenuCategoryList.txt");
    printVector(MenuCategoryList,1);
    cout << endl;
    int userChoice;
    cin >> userChoice;
    string junk;
    getline(cin, junk);
    if (userChoice==99)
    {
        done = true;
    }
    else
    {
        // display chosen category items
        string categoryFilename = MenuCategoryList[userChoice][2];  //get filename of chosen category
        vector<vector<string> > Category = readFileToVector(categoryFilename.c_str());
        printVector(Category, 1); // display chosen category
        cout << endl;

        cout << "Pick an menu item from this menu category:" << endl;
        cin >> userChoice;
        getline(cin , junk);
        orderList.resize(orderList.size()+1);
        orderList.push_back(Category[userChoice][1] ); // add item to orderList
        string itemFilename = Category[userChoice][2];
        vector<vector<string> > tempVector = readFileToVector(itemFilename);
        total = total + string_to_int(tempVector[0][0]);  // add menu item price to total
        cout << "Total is " << total  << endl;
                for (size_t i=1; i<tempVector.size(); i++)
                {
                    string invoNumber = tempVector[i][0];  // for each constituent invo item in the menu item,
                    itemsList.push_back(invoNumber);   // add invo item number to itemsList
                }
    }
}
    if (this->payOrder(total))
    {
       this->deductInvo(itemsList);
    }
    cout << "Transaction complete." << endl;
}

bool Menu::payOrder(double total)
{
    cout << "Total is " << total << endl;
    cout << "Enter 0 for cash, or 1 for credit." << endl;
    int userChoice;
    cin >> userChoice;
    string junk;
    getline(cin, junk);
    if (userChoice==0)
    {
        cout << "Enter cash amount paid: " << endl;
        double paid =0;
        cin >> paid;
        getline(cin, junk);
        double change = total-paid;
        cout << "Give this much change: " << change << endl;
    }
    // write to dailyreport here
    return true;
}

void Menu::deductInvo(vector<string>  itemsList)
{

    vector<vector<string> > InvoVector = readFileToVector("Inventory.txt");
    printVector(InvoVector,0);
    for ( size_t i=0; i<itemsList.size(); i++)
    {
        int desiredInvoLine = -1;
        string invoNumber = itemsList[i];
        for ( size_t j=0; j<InvoVector.size(); j++) // find the line that has invoNumber
        {
            if (InvoVector[j][0]==invoNumber)
            {
                desiredInvoLine = j;
                cout << desiredInvoLine << endl;
            }
        }
        string quantityString = InvoVector[desiredInvoLine ][2];
        int quantityInt = string_to_int(quantityString);
        quantityInt--;
        quantityString = int_to_string(quantityInt);
        InvoVector[desiredInvoLine  ][2] = quantityString;

    }
    writeVectorToFile(InvoVector, "Inventory.txt");

}

