#include "Display.h"
#include "Users.h"
#include "Inventory.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
using namespace std;

//!Instantiate global objects for program!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Users login;
Inventory myInventory;
Menu myMenu;

Display::Display(){
    quitProgram = false;
}
/*!
Program will check to see if manager login file has been
created before doing anything else in the program.
*/
void Display::displayStart(){
    //Check to see if user has quit program from login menu
    if(quitProgram == true){
        //Do nothing to exit function
    }
    //Otherwise, continue to login
    else{
        //checkForManagerFile will return false if no file found
        if(checkForManagerFile() == false){
            //Manager file does not exist!
            //Take to manager user creation page
            login.createLogin();
            //Take to login page
            displayLogin();
            //Check to see if user has quit program from login menu
            if(quitProgram == true){
                //Do nothing to exit function
            }
            //Otherwise, continue
            else{
                //Take to main menu after successful login
                displayMain();
            }
        }
        //CheckForManagerFile will return true if file was found
        else if(checkForManagerFile() == true){
            //Manager file exists!
            //Take to login page
            displayLogin();
            //Check to see if user has quit program from login menu
            if(quitProgram == true){
                //Do nothing to exit function
            }
            //Otherwise, continue
            else{
                //Take to main menu after successful login
                displayMain();
            }
        }
    }
}

void Display::displayMain(){
    //Display main menu after successful login
    string choice;
    string dummyChoice;
    cout << string(50, '\n');
    do{
        cout << "User: " << name << endl;
        cout << "--------------------------" << endl;
        cout << "   Restaurant Main Menu   " << endl;
        cout << "--------------------------" << endl << endl;
        cout << "1) Go to setups" << endl;
        cout << "2) Go to Menu" << endl;
        cout << "3) Log Out" << endl;
        cout << string(15, '\n');
        cout << "Please select an option: ";
        cin >> choice;

        if(choice == "1"){
            //Can only access setups if logged in to manager account
            if(isManager == true){
                displaySetups();
            }
            else{
                cout << string(50, '\n');
                cout << "You are not a manager!" << endl;
                cout << "Press any key to return to last screen.";
                cout << string(21, '\n');
                cin >> dummyChoice;
            }
        }
        else if(choice == "2"){
            //displayMenu();
            myMenu.takeOrder();
        }
        else if(choice == "3"){
            displayLogout();
        }
        else{
            cout << string(50, '\n');
            cout << "Invalid choice!" << endl;
        }
        cout << string(50, '\n');
    }
    while(choice != "3");
    displayStart();
}

void Display::displaySetups(){
    //Setups menu
    string choice;
    string dummyChoice;
    cout << string(50, '\n');
    do{
        cout << "User: " << name << endl;
        cout << "-------------------------" << endl;
        cout << "         Setups          " << endl;
        cout << "-------------------------" << endl << endl;
        cout << "1) Setup Users" << endl;
        cout << "2) Setup Inventory" << endl;
        cout << "3) Setup Menu" << endl;
        cout << "4) Setup Register" << endl;
        cout << "5) View Daily Report" << endl;
        cout << "6) Go back to previous menu" << endl;
        cout << string(12, '\n');
        cin >> choice;

        if(choice == "1"){
            displayUsersSetup();
        }
        else if(choice == "2"){
            displayInventorySetup();
        }
        else if(choice == "3"){
            displayMenuSetup();
        }
        else if(choice == "4"){
            cout << string(50, '\n');
            cout << "Register functionality coming soon!" << endl;
            cout << "Press any key to return to last screen.";
            cin >> dummyChoice;
            //!Call register setup function here!
        }
        else if(choice == "5"){
            cout << string(50, '\n');
            cout << "View Daily Report functionality coming soon!" << endl;
            cout << "Press any key to return to last screen.";
            cin >> dummyChoice;
            //!Call view daily report function here!
        }
        else if(choice == "6"){
            //Exit setup menu, go back to main menu
            cout << string(50, '\n');
        }
        else{
            cout << string(50, '\n');
            cout << "Invalid choice!" << endl;
        }
    }
    while(choice != "6");
}

void Display::displayUsersSetup(){
    //Users menu
    //Create Users object
    //Users login;
    string choice;
    string dummyChoice;
    cout << string(50, '\n');
    do{
        cout << "User: " << name << endl;
        cout << "-------------------------" << endl;
        cout << "      Users Setup        " << endl;
        cout << "-------------------------" << endl << endl;
        cout << "1) Add user" << endl;
        cout << "2) Edit user" << endl;
        cout << "3) Delete user" << endl;
        cout << "4) Go back to previous menu" << endl;
        cout << string(14, '\n');
        cin >> choice;

        if(choice == "1"){
            cout << string(50, '\n');
            login.createLogin();
        }
        else if(choice == "2"){
            cout << string(50, '\n');
            cout << "Edit user functionality coming soon!" << endl;
            cout << "Press any key to return to last screen.";
            cin >> dummyChoice;
            //!insert edit user function here
        }
        else if(choice == "3"){
            cout << string(50, '\n');
            cout << "Delete user functionality coming soon!" << endl;
            cout << "Press any key to return to last screen.";
            cin >> dummyChoice;
            //!insert delete user function here
        }
        else if(choice == "4"){
            //Exit user menu, go back to setups menu
            cout << string(50, '\n');
        }
        else{
            cout << string(50, '\n');
            cout << "Invalid choice!" << endl;
        }
    }
    while(choice != "4");
}

void Display::displayInventorySetup(){
    //Inventory menu
    //!Inventory myInventory;
    string choice;
    string dummyChoice;
    cout << string(50, '\n');
    do{
        cout << "User: " << name << endl;
        cout << "-------------------------" << endl;
        cout << "     Inventory Setup      " << endl;
        cout << "-------------------------" << endl << endl;
        cout << "1) Add a new item in new category" << endl;
        cout << "2) Add a new item in an existing category" << endl;
        cout << "3) View entire inventory" << endl;
        cout << "4) Go back to previous menu" << endl;
        cout << string(14, '\n');
        cin >> choice;

        if(choice == "1"){
            myInventory.updateInvo();
            myInventory.addItem();
        }
        else if(choice == "2"){
            myInventory.updateInvo();
            myInventory.addToExistingCat();
        }
        else if(choice == "3"){
            myInventory.updateInvo();
            myInventory.printInvoVector();
        }
        else if(choice == "4"){
            //Exit inventory menu, go back to main menu
            cout << string(50, '\n');
        }
        else{
            cout << string(50, '\n');
            cout << "Invalid choice!" << endl;
        }
    }
    while(choice != "4");
}

void Display::displayMenuSetup(){
    //Menu menu
    string choice;
    string dummyChoice;
    cout << string(50, '\n');
    do{
        cout << "User: " << name << endl;
        cout << "-------------------------" << endl;
        cout << "       Menu Setup        " << endl;
        cout << "-------------------------" << endl << endl;
        cout << "1) Create single item" << endl;
        cout << "2) Create compound/combo item" << endl;
        cout << "3) Go back to previous menu" << endl;
        cout << string(15, '\n');
        cin >> choice;

        if(choice == "1"){
            myMenu.makeMenuItemSingle();
        }
        else if(choice == "2"){
            myMenu.makeMenuItemCompound();
        }
        else if(choice == "3"){
            //Exit inventory menu, go back to main menu
            cout << string(50, '\n');
        }
        else{
            cout << string(50, '\n');
            cout << "Invalid choice!" << endl;
        }
    }
    while(choice != "3");
}

void Display::displayMenu(){

}

void Display::displayLogin(){
    //Prompt for user login
    //Create Users object
    Users login;
    quitProgram = login.logIn(name,isManager);
}

void Display::displayLogout(){
    name = "";
    isManager = false;
    cout << string(50, '\n');
    cout << "You have logged out!";
    cout << string(20, '\n');
}

bool Display::checkForManagerFile(){
    if(ifstream("login.txt")){
        //File exists!
        return true;
    }
    else{
        //File does not exist!
        return false;
    }
}

Display::~Display(){
}
