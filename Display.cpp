#include "Display.h"
#include "Users.h"
#include <iostream>
#include <fstream>
using namespace std;

/*!
Program runs from constructor
Constructor will check to see if manager login file has been
created before doing anything else in the program.
*/
Display::Display(){
    quitProgram = false;
}

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
            Users newLogin;
            newLogin.createLogin();
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
    int choice;
    int dummyChoice;
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

        if(choice == 1){
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
        else if(choice == 2){
            cout << string(50, '\n');
            cout << "Menu functionality coming soon!" << endl;
            cout << "Press any key to return to last screen.";
            cout << string(21, '\n');
            //!Call Menu.display function here!
        }
        else if(choice == 3){
            displayLogout();
        }
        else{
            cout << string(50, '\n');
            cout << "Invalid choice!" << endl;
        }
    }
    while(choice != 3);
    displayStart();
}

void Display::displaySetups(){
    //Setups menu
    int choice;
    int dummyChoice;
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

        if(choice == 1){
            cout << string(50, '\n');
            cout << "Users functionality coming soon!" << endl;
            cout << "Press any key to return to last screen.";
            cin >> dummyChoice;
            //!Call Users setup function here
        }
        else if(choice == 2){
            cout << string(50, '\n');
            cout << "Inventory functionality coming soon!" << endl;
            cout << "Press any key to return to last screen.";
            cin >> dummyChoice;
            //!Call Inventory setup function here!
        }
        else if(choice == 3){
            cout << string(50, '\n');
            cout << "Menu functionality coming soon!" << endl;
            cout << "Press any key to return to last screen.";
            cin >> dummyChoice;
            //!Call menu setup function here!
        }
        else if(choice == 4){
            cout << string(50, '\n');
            cout << "Register functionality coming soon!" << endl;
            cout << "Press any key to return to last screen.";
            cin >> dummyChoice;
            //!Call register setup function here!
        }
        else if(choice == 5){
            cout << string(50, '\n');
            cout << "View Daily Report functionality coming soon!" << endl;
            cout << "Press any key to return to last screen.";
            cin >> dummyChoice;
            //!Call view daily report function here!
        }
        else if(choice == 6){
            //Exit setup menu, go back to main menu
            cout << string(50, '\n');
        }
        else{
            cout << string(50, '\n');
            cout << "Invalid choice!" << endl;
        }
    }
    while(choice != 6);
}

void Display::displayLogin(){
    //Prompt for user login
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
