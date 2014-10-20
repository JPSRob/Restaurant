#include "Users.h"
#include "Display.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Constructor
Users::Users(){
    loginName = "";
}

//!Method to create manager login
void Users::createLogin(){
    //!If file already exists: read into 2d vector, add entry, and overwrite file
    if(fstream("login.txt")){
        ifstream loginFile;
        loginFile.open("login.txt");
        //Create 2d vector, named a
        vector< vector<string> > loginVector;
        //m * n is the size of the matrix
        int m = 1;
        int n = 3;
        //Grow columns by m
        loginVector.resize(m);
        //Use For loop to initialize rows
        for(int i = 0 ; i < m ; ++i)
        {
            //Grow rows by n
            loginVector[i].resize(n);
        }
        //Read lines of file into 2d vector until end of file (eof)
        string tempString = "";
        int columnCounter = 0;
        int rowCounter = 0;
        while(getline(loginFile,tempString)){
            //login.txt will have three comma separated values,
            //so reset rowCounter after 3 entries and increment column
            for(int i = 0; i < tempString.length(); i++){
                if(tempString[i] != ','){
                    loginVector[columnCounter][rowCounter] = loginVector[columnCounter][rowCounter] + tempString[i];
                }
                else{
                    rowCounter++;
                }
            }
            //reset row counter & create new column & row series in 2d vector
            rowCounter = 0;
            loginVector.push_back(vector <string>());
            columnCounter++;
            loginVector[columnCounter].resize(3);
        }
        //Prompt user to enter new username
        bool loopFlag = false;
        bool isOriginal = true;
        string username = "";
        while(loopFlag == false){
            isOriginal = true;
            cout << "Please enter a new username: " << endl;
            cin >> username;
            //Make sure username hasn't been used before
            for(int i = 0; i <= columnCounter; i++){
                if(username == loginVector[i][0]){
                    cout << "That username has already been taken!" << endl;
                    isOriginal = false;
                }
            }
            if(isOriginal == true){
                loopFlag = true;
            }
        }
        //Prompt user to enter new password
        string password = "";
        cout << "Please enter a password: " << endl;
        cin >> password;
        //Ask user if this is manager account
        bool managerFlag = false;
        char managerString = ' ';
        loopFlag = false;
        while(loopFlag == false){
            cout << "Is this a manager account? (enter 'y' or 'n'): " << endl;
            cin >> managerString;
            if(managerString == 'y' || managerString == 'Y'){
                managerFlag = true;
                loopFlag = true;
            }
            else if(managerString == 'n' || managerString == 'N'){
                //managerFlag stays false
                loopFlag = true;
            }
            else{
                cout << "You did not enter 'y' or 'n'!" << endl;
            }
        }
        //Push new data into vector
        //columnCounter++;
        //loginVector.push_back(vector <string>());
        loginVector[columnCounter][0] = username;
        loginVector[columnCounter][1] = password;
        loginVector[columnCounter][2] = (managerFlag ? "1" : "0");
        //Write vector to file
        loginFile.close();
        ofstream loginFileOut;
        loginFileOut.open("login.txt");
        string tempLine = "";
        for(int i = 0; i <= columnCounter; i++){
            for(int j = 0; j < 3; j++){
                if(j >= 2){
                    tempLine = tempLine + loginVector[i][j];
                }
                else{
                    tempLine = tempLine + loginVector[i][j] + ',';
                }
            }
            loginFileOut << tempLine + "\n";
            tempLine = "";
        }
        loginFileOut.close();
    }
    //!If file does not exist: create file, and add user's entry
    else{
        cout << "Login has not been created!" << endl;
        //Create login.txt file
        ofstream loginFile("login.txt");
        //Prompt user for username
        string username;
        cout << "Please enter a new username: " << endl;
        cin >> username;
        //Prompt user to enter new password
        string password = "";
        cout << "Please enter a password: " << endl;
        cin >> password;
        //Ask user if this is manager account
        bool managerFlag = false;
        char managerString = ' ';
        bool loopFlag = false;
        while(loopFlag == false){
            cout << "Is this a manager account? (enter 'y' or 'n'): " << endl;
            cin >> managerString;
            if(managerString == 'y' || managerString == 'Y'){
                managerFlag = true;
                loopFlag = true;
            }
            else if(managerString == 'n' || managerString == 'N'){
                //managerFlag stays false
                loopFlag = true;
            }
            else{
                cout << "You did not enter 'y' or 'n'!" << endl;
            }
        }
        loginFile << username << ',' << password << ',' << (managerFlag ? "1" : "0") << endl;
    }
}

//!Method to log in
bool Users::logIn(string& name, bool& isManager){
    //!open file and load into vector
    if(fstream("login.txt")){
        ifstream loginFile;
        loginFile.open("login.txt");
        //Create 2d vector, named a
        vector< vector<string> > loginVector;
        //m * n is the size of the matrix
        int m = 1;
        int n = 3;
        //Grow columns by m
        loginVector.resize(m);
        //Use For loop to initialize rows
        for(int i = 0 ; i < m ; ++i)
        {
            //Grow rows by n
            loginVector[i].resize(n);
        }
        //Read lines of file into 2d vector until end of file (eof)
        string tempString = "";
        int columnCounter = 0;
        int rowCounter = 0;
        while(getline(loginFile,tempString)){
            //login.txt will have three comma separated values,
            //so reset rowCounter after 3 entries and increment column
            for(int i = 0; i < tempString.length(); i++){
                if(tempString[i] != ','){
                    loginVector[columnCounter][rowCounter] = loginVector[columnCounter][rowCounter] + tempString[i];
                }
                else{
                    rowCounter++;
                }
            }
            //reset row counter & create new column & row series in 2d vector
            rowCounter = 0;
            loginVector.push_back(vector <string>());
            columnCounter++;
            loginVector[columnCounter].resize(3);
        }
    //!Begin login process
    string username;
    string password;
    string managerString;
    bool manager;
    //Prompt for user to enter username
    //cout << "Please login." << endl << "Enter your username: " << endl;
    //cin >> username;
    int userColumn;
    bool loopFlag = false;
    while(loopFlag == false){
            cout << string(50, '\n');
            cout << "    Welcome! Please, login    " << endl;
            cout << "------------------------------" << endl;
            cout << "Please enter your username: " << endl;
            cout << string(20, '\n');
            cin >> username;
            //Make sure username hasn't been used before
            int columnCounter = 0;
            for(int i = 0; i <= columnCounter; i++){
                if(username == loginVector[i][0]){
                    loopFlag = true;
                    userColumn = i;
                }
            }
            if(loopFlag == false){
                cout << "Username does not exist!" << endl;
            }
        }
    //Prompt for user to enter password
    loopFlag = false;
    while(loopFlag == false){
            cout << "Please enter your password: " << endl;
            cin >> password;
            if(password == loginVector[userColumn][1]){
                loopFlag = true;
            }
            else if(loopFlag == false){
                cout << "Password is incorrect!" << endl;
            }
        }
    //Set bool manager if user is a manager or not
    managerString = loginVector[userColumn][2];
    manager = managerString.c_str();
    //assign passed-by-reference variables
    name = username;
    isManager = manager;
}
}

//!Method to log out
void Users::logOut(){

}

//!Destructor
Users::~Users(){
}
