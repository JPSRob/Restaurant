#include "Display.h"
#include "Users.h"
#include <iostream>
#include <fstream>
using namespace std;

/*
Constructor will check to see if manager login has been created
before doing anything else in the program.
*/
Display::Display(){
    //checkForManagerFile will return false if no file found
    if(checkForManagerFile() == false){
        //Manager file does not exist!
        //Take to manager user creation page
        Users newLogin;
        newLogin.createLogin();
        //Take to login page
        displayLogin();
        //Take to main menu after successful login
        displayMain();
    }
    //CheckForManagerFile will return true if file was found
    else if(checkForManagerFile() == true){
        //Manager file exists!
        //Take to login page
        displayLogin();
        //Take to main menu after successful login
        displayMain();
    }
}

void Display::displayMain(){
    char choice;
    char dummyChoice;
    //Display main menu after successful login
    bool keepLooping = true;
    cout << string(50, '\n');
    while(keepLooping == true){
        cout << "       Restaurant        " << endl;
        cout << "-------------------------" << endl << endl;
        cout << "1. Go to setups" << endl;
        cout << "2. Go to Menu" << endl;
        cout << "'q' to quit" << endl;
        cout << string(17, '\n');
        cin >> choice;

        if(choice != '1' && choice != '2' && choice != 'q'){
            cout << string(50, '\n');
            cout << "Invalid choice!" << endl;
        }
        else{
            switch(choice){
            case '1':
                bool keepSetupLooping;
                keepSetupLooping = true;
                while(keepSetupLooping == true){
                    cout << "         Setups          " << endl;
                    cout << "-------------------------" << endl << endl;
                    cout << "1. Setup Users" << endl;
                    cout << "2. Setup Inventory" << endl;
                    cout << "3. Setup Menu" << endl;
                    cout << "4. Setup Register" << endl;
                    cout << "5. View Daily Report" << endl;
                    cout << "'b' to go back to last menu" << endl;
                    cout << string(14, '\n');
                    cin >> choice;
                    if(choice != '1' && choice != '2' && choice != 'b'){
                            cout << string(50, '\n');
                            cout << "Invalid choice!" << endl;
                    }
                    else{
                        switch(choice){
                        case '1':
                            cout << string(50, '\n');
                            cout << "Users functionality coming soon!" << endl;
                            cout << "Press any key to return to last screen." << endl;
                            cin >> dummyChoice;
                            cout << endl;
                            break;
                            //!Call Users setup function here
                        case '2':
                            cout << string(50, '\n');
                            cout << "Inventory functionality coming soon!" << endl;
                            cout << "Press any key to return to last screen." << endl;
                            cin >> dummyChoice;
                            cout << endl;
                            break;
                            //!Call Inventory setup function here!
                        case '3':
                            cout << string(50, '\n');
                            cout << "Menu functionality coming soon!" << endl;
                            cout << "Press any key to return to last screen." << endl;
                            cin >> dummyChoice;
                            cout << endl;
                            break;
                            //!Call menu setup function here!
                        case '4':
                            cout << string(50, '\n');
                            cout << "Register functionality coming soon!" << endl;
                            cout << "Press any key to return to last screen." << endl;
                            cin >> dummyChoice;
                            cout << endl;
                            break;
                            //!Call register setup function here!
                        case '5':
                            cout << string(50, '\n');
                            cout << "View Daily Report functionality coming soon!" << endl;
                            cout << "Press any key to return to last screen." << endl;
                            cin >> dummyChoice;
                            cout << endl;
                            break;
                            //!Call view daily report function here!
                        case 'b':
                            cout << string(50, '\n');
                            keepSetupLooping = false;
                    }
                    }
                }

            case '2':
                cout << string(50, '\n');
                cout << "Menu functionality coming soon!" << endl;
                cout << "Press any key to return to last screen." << endl;
                cin >> dummyChoice;
                cout << endl;
                break;
                //!Call menu function here!
            case 'q':
                cout << string(50, '\n');
                cout << "You have quit the program!";
                cout << string(20, '\n');
                keepLooping = false;
            }
        }
    }
}

void Display::displayLogin(){
    //Prompt for user login
    Users login;
    login.logIn(name,isManager);
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
