#include "Display.h"
#include "Users.h"
#include "Inventory.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

Inventory::Inventory()
{
    string category = "";
    itemIDNumber = "";

    if(fstream("idnumber.txt")){
        idNumber.open("idnumber.txt");
    }
    if(fstream("inventory.txt")){
        invFile.open("inventory.txt");
    }
    if(fstream("categories.txt")){
        categoryFile.open("categories.txt");
    }

    counter = 0;
    numberOfItems = 0;

    int numberOfCategories = 0;
}

void Inventory::updateInvo()
{
    int numberOfCategories = 0;
    string category = "";

    if(idNumber.is_open())
        {
            while(getline(idNumber,itemIDNumber))
            {
                istringstream( itemIDNumber ) >> counter;
            }
        }

        if(categoryFile.is_open())
        {
            while(getline(categoryFile,inFromFile)) //fill vector with existing contents of file
            {
                    categoryVector.push_back(inFromFile);
                    numberOfCategories++;
            }
        }
        categoryFile.close();

        int m = 1;
        int n = 4;
        //Grow columns by m
        invoVector.resize(m);

        for(int i = 0; i< m; ++i)
        {
            invoVector[i].resize(n);
        }

        //Read lines of file into 2d vector until end of file (eof)

        string tempString = "";
        int columnCounter = 0;
        int rowCounter = 0;

        for(int location = 0; location < numberOfCategories; location++)
        {
            ifstream categoryFileTwo;
            category = "";
            category = categoryVector[location];
            categoryFileTwo.open(category.c_str());

            while(getline(categoryFileTwo,tempString))
            {
                for(int i = 0; i < tempString.length(); i++)
                {
                    if(tempString[i] != ',')
                    {
                        invoVector[columnCounter][rowCounter] = invoVector[columnCounter][rowCounter] + tempString[i];
                    }
                    else
                    {
                        rowCounter++;
                    }
                }
                //reset row counter & create new column & row series in 2d vector
                numberOfItems++;
                rowCounter = 0;
                invoVector.push_back(vector <string>());
                columnCounter++;
                invoVector[columnCounter].resize(4);
            }

            categoryFileTwo.close();
        }

        if(invFile.is_open())
        {
            for(int row = 0; row<numberOfItems; row++)
            {
                invFile << "\n";

                for(int info=0;info<4;info++)
                {
                    invFile << invoVector[row][info] << ",";
                }
            }

            invFile.close();
        }

}

void Inventory::printInvoVector()
{
    updateInvo();
        for(int row=0; row<numberOfItems; row++)
        {
            cout << numberOfItems << endl;
            cout << endl;
            for(int col = 0; col < 4; col++)
            {
                cout << "test" << endl;
                if(col == 0)
                {
                    cout << "ID NUMBER: " << invoVector[row][col] << endl;
                }
                else if(col == 1)
                {
                    cout << "ITEM NAME: " << invoVector[row][col] << endl;
                }
                else if(col == 2)
                {
                    cout << "QUANTITY: " << invoVector[row][col] << endl;
                }
                else if (col == 3)
                {
                    cout << "CATEGORY: " << invoVector[row][col] << endl;
                }
                else
                {
                    cout << "ERROR" << endl;
                }

            }

        }

}


void Inventory::addItem()
{
    updateInvo();
    string categoryName = "";
    string inFromFile = "";
    string dotTxtChecker = "";
    string itemName = "";
    string quantity = "";
    string categoryNameTxtFile = "";
    bool flag = 0;

    cout << "Please type in the name of the category for your item:" << endl;
    cout << "Must be at least four characters long." << endl;
    cin >> categoryName;

    categoryFile.open("categories.txt");

        categoryNameTxtFile = categoryName + ".txt"; // add .txt to the userInput so that we can create a file with it.

        categoryVector.push_back(categoryNameTxtFile); // add new category to vector

    categoryFile.close();

    ofstream outputFile;
    outputFile.open("categories.txt");

    for(int k=0;k<categoryVector.size(); k++)
    {
        dotTxtChecker = categoryVector[k];

        if(dotTxtChecker.at(dotTxtChecker.length()-4) != '.')
        {
            outputFile << categoryVector[k] << ".txt" << endl;
        }
        else
        {
            outputFile << categoryVector[k] << endl; // Update the file with all of its contents
        }
    }

    outputFile.close();

    cout << "Type in the name of your item: " << endl;
    cin >> itemName;

    cout << "Type in the quantity of the item." << endl;
    cin >> quantity;

    invoItemInfo.push_back(itemIDNumber);
    invoItemInfo.push_back(itemName);
    invoItemInfo.push_back(quantity);
    invoItemInfo.push_back(categoryName);
    invoVector.push_back(invoItemInfo);

    counter++; // increment itemIDNumber

    ofstream idNumber; // This opens the file the id number is in and replaces it with the incremented id number

    idNumber.open("idnumber.txt");

        if(idNumber.is_open())
        {
            idNumber << counter;
        }

    ofstream categoryOutputFile;
    string categoryFileName = categoryVector[categoryVector.size()-1];
    categoryOutputFile.open(categoryFileName.c_str());

    for(int info=0;info<4;info++)
    {
        categoryOutputFile << invoVector[invoVector.size()-1][info] << ",";
    }
    updateInvo();
    categoryOutputFile.close();
}


void Inventory::addToExistingCat()
{
    updateInvo();
    string tempCategory = "";
    string nameOfCategoryFile = "";
    string selectedCategory = "";
    string itemName = "";
    string quantity = "";
    string categoryName = "";
    string tempCategoryName = "";
    int category = 3; //location of category in invoVector
    int categoryCounter = 0;
    int userInput = 0;

    if(invoVector[0][0] == "")
    {
        cout << "There have not been any items created in the system." << endl;
        cout << "Please create a category and an item before adding to an existing category." << endl;
    }

    else if(invoVector[0][0] != "")
    {
        for(int o=0;o<categoryVector.size();o++) // prints all of the category names without the file extension
        {
            categoryCounter++;
            tempCategory = categoryVector[o];

            tempCategory.erase(tempCategory.end()-4);
            tempCategory.erase(tempCategory.end()-3);
            tempCategory.erase(tempCategory.end()-2);
            tempCategory.erase(tempCategory.end()-1);

            cout << categoryCounter << ". " << tempCategory << endl;

        }

        cout << "Make a selection by inputting a number that corresponds with a category:" << endl;
        cin >> userInput;

        if(userInput >= 1)
        {
            nameOfCategoryFile = categoryVector[userInput-1];
            cout << "NameOFCategoryFile: " << nameOfCategoryFile << endl;

            ofstream categoryFileToOpen;

            categoryFileToOpen.open(nameOfCategoryFile.c_str(),ios::app|fstream::ate); //seeks to file end before each write

            tempCategoryName = nameOfCategoryFile;
            tempCategoryName.erase(tempCategoryName.end()-4);
            tempCategoryName.erase(tempCategoryName.end()-3);
            tempCategoryName.erase(tempCategoryName.end()-2);
            tempCategoryName.erase(tempCategoryName.end()-1);

            categoryName = tempCategoryName;

            cout << "categoryName:" << categoryName << endl;

            cout << "Type in the name of your item. " << endl;
            cin >> itemName;

            cout << "Type in the quantity of the item. " << endl;
            cin >> quantity;

            invoItemInfo.push_back(itemIDNumber);
            invoItemInfo.push_back(itemName);
            invoItemInfo.push_back(quantity);
            invoItemInfo.push_back(categoryName);
            invoVector.push_back(invoItemInfo);

            counter++; // increment itemIDNumber

            if(categoryFileToOpen.is_open())
            {
                categoryFileToOpen << "\n";

                for(int info=0;info<4;info++)
                {
                    categoryFileToOpen << invoVector[invoVector.size()-1][info] << ",";
                }
            }
            else
            {
                cout << "Nothing was written to file." << endl;
            }
            updateInvo();
            categoryFileToOpen.close();
        }

        ofstream idNumber; // This opens the file the id number is in and replaces it with the incremented id number
        idNumber.open("idnumber.txt");//

        if(idNumber.is_open())//
        {
            idNumber << counter;//
        }
        idNumber.close();
    }

}

void Inventory::printAllCategories()
{
    updateInvo();
    string tempCategory = "";
    int categoryCounter = 0;

    for(int o=0;o<categoryVector.size();o++) // prints all of the category names without the file extension
        {
            categoryCounter++;
            tempCategory = categoryVector[o];

            tempCategory.erase(tempCategory.end()-4);
            tempCategory.erase(tempCategory.end()-3);
            tempCategory.erase(tempCategory.end()-2);
            tempCategory.erase(tempCategory.end()-1);

            cout << categoryCounter << ". " << tempCategory << endl;

        }
}

void Inventory::deleteAllCategories()
{
    updateInvo();
    ofstream outputFile;
    outputFile.open("categories.txt", ofstream::out | ofstream::trunc);
    updateInvo();
    outputFile.close();
}

vector <vector <string> > Inventory::returnItemsInCategory(string categoryFileName)
{
    updateInvo();
    int itemCounter = 0;
    int columnCounter = 0;
    int rowCounter = 0;
    string tempInString = "";

    vector <vector <string> > tempCategoryTwoDVector;

    ifstream fileToOpen;

    int m = 1;
    int n = 4;
        //Grow columns by m
    tempCategoryTwoDVector.resize(m);

    for(int i = 0; i< m; ++i)
    {
            tempCategoryTwoDVector[i].resize(n);
    }

    fileToOpen.open(categoryFileName.c_str());

    while(getline(fileToOpen,tempInString))
    {
        for(int i = 0; i < tempInString.length(); i++)
        {
            if(tempInString[i] != ',')
            {
                tempCategoryTwoDVector[columnCounter][rowCounter] = tempCategoryTwoDVector[columnCounter][rowCounter] + tempInString[i];
            }
            else
            {
                rowCounter++;
            }
        }
        //reset row counter & create new column & row series in 2d vector
        rowCounter = 0;
        tempCategoryTwoDVector.push_back(vector <string>());
        columnCounter++;
        tempCategoryTwoDVector[columnCounter].resize(4);
        itemCounter++;
    }
    updateInvo();
    fileToOpen.close();

    return tempCategoryTwoDVector;
}

Inventory::~Inventory(){
    idNumber.close();
    invFile.close();
    categoryFile.close();
}
