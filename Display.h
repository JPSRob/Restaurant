#ifndef DISPLAY_H
#define DISPLAY_H
#include "Users.h"
#include <iostream>
using namespace std;

class Display{
public:
    Display();
    bool checkForManagerFile();
    void displayLogin();
    void displayMain(); //pass name of person logged in and bool value true if manager, false if non-manager



    ~Display();
private:
    string name;
    bool isManager;
};

#endif // DISPLAY_H
