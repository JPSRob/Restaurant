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
    string category = "";
    itemIDNumber = "";

    counter = 0;
    numberOfItems = 0;
    numberOfCategories = 0;
}

void Inventory::updateInvo()
{
    numberOfCategories = 0;
    string category = "";

    fillCategoryVector(); // reads from file
    initializeVector(); // initializes invoVector
    updateInvoTwoDVector(); // opens each category file and reads into the 2-d vector
    updateInvoDotTxt(); //Writes to inventory.txt

    //TEST
    //printOneDVector(categoryVector);
    //TEST
    //printTwoDVector(invoVector);

}
//TEST
void Inventory::printTwoDVector(vector <vector <string> > inputTwo)
{
    for(int l = 0; l < numberOfItems; l++)
    {
        for(int cols = 0; cols < 4; cols++)
        {
            cout << "invoVector " << "[" << l << "]" << "[" << cols << "] = " << invoVector[l][cols] << endl;
        }
    }
}
//TEST
void Inventory::printOneDVector(vector <string> input)
{
    for(int i = 0; i < input.size(); i++)
    {
        cout << "CategoryVector: " << i << " = " << input[i] << endl;
    }
}

void Inventory::updateInvoTwoDVector()
{
    int columnCounter = 0;
    int rowCounter = 0;

    string category = "";
    string tempString = "";

    numberOfItems = 0;

    invoVector.clear();

    initializeVector();

    for(int location = 0; location < numberOfCategories; location++)
    {
        ifstream categoryFileTwo;string

        tempString = "";
        category = "";

        category = categoryVector[location];

        categoryFileTwo.open(category.c_str());

        if(categoryFileTwo.is_open())
        {
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

        }
        else
        {
            cout << "Could not open Inventory file. ERROR. Call Code Talkers Inc. " << endl;
        }

            categoryFileTwo.close();
    }

}

//Read From File Test
void Inventory::readInInventoryFile()
{
    string inFromInventoryFile = "";

    ifstream inventoryFile;

    inventoryFile.open("inventory.txt");

    if(inventoryFile.is_open())
    {

        while(getline(inventoryFile,inFromInventoryFile))
        {
            cout << "Line from file: " << inFromInventoryFile << endl;
        }

    }

}

void Inventory::updateInvoDotTxt()
{

    if(invoVector[0][0] == "")
    {
        //cout << "Inventory is empty." << endl;
    }
    else if(invoVector[0][0] != "")
    {
        ofstream invFile;

        invFile.open("inventory.txt");

        if(invFile.is_open())
        {
            for(int row = 0; row<numberOfItems; row++)
            {
                invFile << endl;

                for(int info=0;info<4;info++)
                {
                    invFile << invoVector[row][info] << ",";
                }
            }
        }
        else
        {
            cout << "The inventory file was not open. Call Code Talkers Inc." << endl;
        }

        invFile.close();
    }

}

void Inventory::saveID()
{
    int Result = 0;

    ifstream idNumber;

    idNumber.open("idnumber.txt");

    if(idNumber.is_open())
    {
        while(getline(idNumber,tempInFromID))
        {
            istringstream convert(tempInFromID);

            if ( !(convert >> Result))
            Result = 0;
        }

        idNumber.close();

    }

    counter = Result;
}

void Inventory::updateIDFile()
{
    saveID();

    counter++;

            // http://www.cplusplus.com/articles/D9j2Nwbp/

    string Result;          // string which will contain the result

    ostringstream convert;   // stream used for the conversion

    convert << counter;      // insert the textual representation of 'Number' in the characters in the stream

    Result = convert.str(); // set 'Result' to the contents of the stream

          // http://www.cplusplus.com/articles/D9j2Nwbp/

    ofstream idNumber;

    idNumber.open("idnumber.txt");

    if(idNumber.is_open())
    {
        idNumber << Result;
    }
    else
    {
        cout << "File did not open. Call Code Talkers Inc." << endl;
    }

    idNumber.close();

}

void Inventory::getIDNumber()
{
    ifstream idNumber;

    string tempItemIDNumber;

    idNumber.open("idnumber.txt");

    if(idNumber.is_open())
    {
        while(getline(idNumber,tempItemIDNumber))
        {
            istringstream( tempItemIDNumber ) >> counter;
        }

        idNumber.close();
    }
    else
    {
        cout << "File did not open. Call Code Talkers Inc." << endl;
    }

            // http://www.cplusplus.com/articles/D9j2Nwbp/

    string Result;          // string which will contain the result

    ostringstream convert;   // stream used for the conversion

    convert << counter;      // insert the textual representation of 'Number' in the characters in the stream

    Result = convert.str(); // set 'Result' to the contents of the stream

            // http://www.cplusplus.com/articles/D9j2Nwbp/

    itemIDNumber = Result;

    updateIDFile();

}

void Inventory::fillCategoryVector()
{
    categoryVector.clear();

    ifstream categoryFile;

    categoryFile.open("categories.txt");

    if(categoryFile.is_open())
    {
        while(getline(categoryFile,inFromFile)) //fill vector with existing contents of file
        {
                categoryVector.push_back(inFromFile);
                numberOfCategories++;
        }

        categoryFile.close();

    }
    else
    {
        //cout << "Error file did not open." << endl;
    }
}

void Inventory::initializeVector()
{
    int m = 1;
    int n = 4;
    //Grow columns by m
    invoVector.resize(m);

    for(int i = 0; i< m; ++i)
    {
        invoVector[i].resize(n);
    }
}

void Inventory::printInvoVector()
{

    for(int row=0; row<numberOfItems; row++)
    {
        cout << endl;
        for(int col = 0; col < 4; col++)
        {
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
                cout << "ERROR. Call Code Talkers Inc." << endl;
            }

        }

    }

    cout << endl;

}


void Inventory::addItem()
{
    string categoryName = "";
    string inFromFile = "";
    string dotTxtChecker = "";
    string itemName = "";
    int quantity = 0;
    string categoryNameTxtFile = "";

    bool flag = 0;
    cout << string(50, '\n');
    do{
        cout << "Please type in the name of the category for your item:" << endl;
        cout << "Must be at least four characters long." << endl;
        cout << string(21, '\n');
        cin >> categoryName;
        //Error check that user entered value greater than 4 characters
        if(categoryName.size() >= 4){
            //Do nothing to continue
        }
        else{
            cout << "Your entry is less than four characters!" << endl;
        }
    }
    while(categoryName.size() >= 4);

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
    cout << string(50, '\n');
    cout << "Type in the name of your item: " << endl;
    cout << string(22, '\n');
    cin >> itemName;

    cout << string(50, '\n');
    cout << "Type in the quantity of the item." << endl;
    cout << string(22, '\n');
    cin >> quantity;
    while(cin.fail()){
        cout << string(50, '\n');
        cout << "You did not enter a number!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Type in the quantity of the item." << endl;
        cout << string(21, '\n');
        cin >> quantity;
    }

    getIDNumber();

    invoItemInfo.clear();

    invoItemInfo.resize(4);

    invoItemInfo[0]=itemIDNumber;
    invoItemInfo[1]=itemName;
    invoItemInfo[2]=quantity;
    invoItemInfo[3]=categoryName;
    invoVector.push_back(invoItemInfo);

    ofstream categoryOutputFile;

    string categoryFileName = categoryVector[categoryVector.size()-1];

    categoryOutputFile.open(categoryFileName.c_str());

    for(int info=0;info<4;info++)
    {
        categoryOutputFile << invoVector[invoVector.size()-1][info] << ",";
    }

    invoVector.clear();

    categoryOutputFile.close();
}


void Inventory::addToExistingCat()
{
    string tempCategory = "";
    string nameOfCategoryFile = "";
    string selectedCategory = "";
    string itemName = "";
    string quantity = "";
    string categoryName = "";
    string tempCategoryName = "";

    int categoryCounter = 0;
    int userInput = 0;

    if(invoVector[0][0] == "")
    {
        cout << string(50, '\n');
        cout << "There have not been any items created in the system." << endl;
        cout << "Please create a category and an item before adding to an existing category." << endl;
        cout << string(21, '\n');
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

        cout << string(50, '\n');
        cout << "Make a selection by inputting a number that corresponds with a category:" << endl;
        cout << string(22, '\n');
        cin >> userInput;

        if(userInput >= 1)
        {
            nameOfCategoryFile = categoryVector[userInput-1];

            ofstream categoryFileToOpen;

            categoryFileToOpen.open(nameOfCategoryFile.c_str(),ios::app|fstream::ate); //seeks to file end before each write

            tempCategoryName = nameOfCategoryFile;
            tempCategoryName.erase(tempCategoryName.end()-4);
            tempCategoryName.erase(tempCategoryName.end()-3);
            tempCategoryName.erase(tempCategoryName.end()-2);
            tempCategoryName.erase(tempCategoryName.end()-1);

            categoryName = tempCategoryName;

            cout << string(50, '\n');
            cout << "Type in the name of your item. " << endl;
            cout << string(22, '\n');
            cin >> itemName;

            cout << string(50, '\n');
            cout << "Type in the quantity of the item. " << endl;
            cout << string(22, '\n');
            cin >> quantity;
            while(cin.fail()){
                cout << string(50, '\n');
                cout << "You did not enter a number!" << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Type in the quantity of the item." << endl;
                cout << string(21, '\n');
                cin >> quantity;
            }

            getIDNumber();

            invoItemInfo.clear();

            invoItemInfo.resize(4);

            invoItemInfo[0] = itemIDNumber;
            invoItemInfo[1] = itemName;
            invoItemInfo[2] = quantity;
            invoItemInfo[3] = categoryName;
            invoVector.push_back(invoItemInfo);

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

            categoryFileToOpen.close();
        }

    }

}

void Inventory::printAllCategories()
{
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
//For Testing
void Inventory::deleteAllCategories()
{
    ofstream outputFile;

    outputFile.open("categories.txt", ofstream::out | ofstream::trunc);

    outputFile.close();
}

vector <vector <string> > Inventory::returnItemsInCategory(string categoryFileName)
{
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

    fileToOpen.close();

    for(int row = 0; row < itemCounter; row++)
    {
        cout << endl;

        for(int col = 0; col < 2; col++)
        {
            cout << " " << tempCategoryTwoDVector[row][col];
        }
    }

    return tempCategoryTwoDVector;
}
