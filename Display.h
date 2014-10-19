#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
using namespace std;

class Display{
public:
    Display();
    bool checkForManagerFile();
    void mainDisplay(string,bool); //pass name of person logged in and bool value true if manager, false if non-manager



    ~Display();
private:

};

#endif // DISPLAY_H
