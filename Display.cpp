#include "Display.h"
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
        cout << "No manager file!" << endl;
        //take to manager user creation page
    }
    //checkForManagerFile will return true if file was found
    else if(checkForManagerFile() == true){
        cout << "Manger file exists!" << endl;
        //take to login page
    }
}



bool Display::checkForManagerFile(){
    if(ifstream("loginManager.txt")){
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
