#include "Inventory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

Inventory::Inventory()
{
    int lenOfItemVector = 4; // The vector that contains the item info will contain four spaces of information
    string category = "";
    itemIDNumber = "123";
    idNumber.open("idnumber.txt");
    invFile.open("inventory.txt");
    categoryFile.open("categories.txt");
    counter = 0;
    int numberOfCategories = 0;

    if(idNumber.is_open())
    {
        while(getline(idNumber,itemIDNumber))
        {
            int numb;
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

    for(int location = 0; location < numberOfCategories; location++)
    {
        ifstream categoryFileTwo;
        category = "";
        category = categoryVector[location];
        categoryFileTwo.open(category.c_str());

        vector <string> temp;

       if(categoryFileTwo.is_open())
        {
            while(getline(categoryFileTwo,inFromFileTwo))
            {
                    temp.push_back(inFromFileTwo);
                    cout << inFromFileTwo << endl;
            }
            invoVector.push_back(temp);
        }
        else
        {
            categoryFileTwo.close();
        }

        categoryFileTwo.close();
    }

}

void Inventory::addItem()
{
    int categoryCounter = 0;
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

        for(int i=0;i<categoryVector.size(); i++) //Check to see that the category name has been pushed into the vector
        {
            cout << categoryVector[i] << endl;
        }

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

    cout << "Here is the category: " << endl;
    cout << categoryVector[categoryVector.size()-1] << endl;

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

    for(int m=0;m<4;m++)
    {
        categoryOutputFile << invoVector[invoVector.size()-1][m] << endl;
    }

    categoryOutputFile.close();
}


void Inventory::addToExistingCat()
{
    string tempCategory = "";
    string nameOfCategoryFile = "";
    string selectedCategory = "";
    string itemName = "";
    string quantity = "";
    string itemIDNum = "1";
    string categoryName = "";
    int category = 3; //location of category in invoVector
    int categoryCounter = 0;
    int userInput = 0;

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
        ofstream categoryFileToOpen;
        categoryFileToOpen.open(nameOfCategoryFile.c_str(),ios::app); //seeks to file end before each write

        cout << nameOfCategoryFile << endl;
        cout << invoVector[userInput-1][3] << endl;

        selectedCategory = invoVector[userInput-1][3] + ".txt";

        cout << selectedCategory << endl;

        categoryName = invoVector[userInput-1][3];

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

        ofstream idNumber; // This opens the file the id number is in and replaces it with the incremented id number
        idNumber.open("idnumber.txt");//

        if(idNumber.is_open())//
        {
            idNumber << counter;//
        }

        if(categoryFileToOpen.is_open())
        {
            if(nameOfCategoryFile == selectedCategory)
            {
                for(int m=0;m<4;m++)
                {
                    categoryFileToOpen << invoVector[invoVector.size()-1][m] << endl;
                }
            }
            else
            {
                cout << "Nothing was written to file." << endl;
            }
        }

        categoryFileToOpen.close();
    }

}

void Inventory::deleteAllCategories()
{
    ofstream outputFile;
    outputFile.open("categories.txt", ofstream::out | ofstream::trunc);
}
