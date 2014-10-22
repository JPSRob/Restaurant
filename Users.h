#ifndef USERS_H
#define USERS_H
#include "Display.h"
#include "Inventory.h"
#include "Menu.h"
#include <iostream>
using namespace std;

class Users{
public:
    Users();
    bool logIn(string&,bool&);
    void createLogin();
    void editLogin();
    void deleteLogin();

    ~Users();
private:
    string loginName;
};


#endif // USERS_H
