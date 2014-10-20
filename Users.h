#ifndef USERS_H
#define USERS_H
#include "Display.h"
#include <iostream>
using namespace std;

class Users{
public:
    string loginName;
    Users();
    void createLogin();
    bool logIn(string&,bool&);
    void logOut();

    ~Users();
private:


};


#endif // USERS_H
