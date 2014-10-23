#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>
#include <fstream>
#include "Menu.h"

using namespace std;

class Inventory
{
public:
    Inventory();
    void addItem();
    void addToExistingCat(); //Add to existing category
    void deleteAllCategories();
    void displayCategories();
    void fillCategoryVector();
    void getIDNumber();
    void initializeVector();
    void printInvoVector();
    void printAllCategories();
    void readInInventoryFile();
    void saveID();
    void updateIDFile();
    void updateInvo();
    void updateInvoTwoDVector();
    void updateInvoDotTxt();
    void printOneDVector(vector <string> input);
    void printTwoDVector(vector <vector <string> > inputTwo);

    vector <vector <string> > returnItemsInCategory(string categoryFileName);

private:
    int counter;
    int numberOfItems;
    int numberOfCategories;

    string inFromFile= "";
    string inFromFileTwo = "";
    string itemIDNumber = "";
    string tempInFromID = "";

    ofstream invFile;
    ifstream categoryFile;
    ifstream idNumber;

    vector <vector <string> > invoVector;//2-d Vector - Format invoVector[row][0]=item# invoVector[row][1]=itemName [row][2]=Quantity [row][3]=CategoryName
    vector <string> invoItemInfo;
    vector <string> categoryVector;
};

#endif // INVENTORY_H
