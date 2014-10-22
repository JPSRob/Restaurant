#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>
#include <fstream>

using namespace std;

class Inventory
{
public:
    Inventory();
    void addItem();
    void addToExistingCat(); //Add to existing category
    void deleteAllCategories();
    void updateInvo();
    void printInvoVector();
    void printAllCategories();

    vector <vector <string> > returnItemsInCategory(string categoryFileName);

private:
    int counter;
    int numberOfItems;

    string inFromFile= "";
    string inFromFileTwo = "";
    string itemIDNumber = "";

    ofstream invFile;
    ifstream categoryFile;
    ifstream idNumber;

    vector <vector <string> > invoVector;//2-d Vector - Format invoVector[row][0]=item# invoVector[row][1]=itemName [row][2]=Quantity [row][3]=CategoryName
    vector <string> invoItemInfo;
    vector <string> categoryVector;
};

#endif // INVENTORY_H
