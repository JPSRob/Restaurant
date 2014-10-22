#ifndef DISPLAY_H
#define DISPLAY_H
#include "Users.h"
#include <iostream>
using namespace std;

class Display{
public:
    Display();

    void displayStart();
    bool checkForManagerFile();
    void displayLogin();
    void displayLogout();
    void displayMain();
    void displaySetups();
    void displayInventorySetup();
    void displayUsersSetup();
    void displayMenuSetup();
    void displayMenu();

    ~Display();
private:

    string name;
    bool isManager;
    bool quitProgram;
};

#endif // DISPLAY_H
