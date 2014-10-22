#ifndef MENU_H
#define MENU_H
#include<vector>
#include<string>
#include "Inventory.h"

using namespace std;

class Menu
{
public:
vector<vector<string> > readFileToVector(string filename);
void writeVectorToFile(vector<vector<string> > v, string filename);
void printVector(vector<vector<string> > inputVector, int colsCutOff);
void printVector(vector<string>  inputVector);
string int_to_string(int n);
string double_to_string(double n);
int string_to_int(string s);
void makeMenuItemSingle();
void makeMenuItemCompound();
void takeOrder();
bool payOrder(double total);
void deductInvo(vector<string>  orderList);

private:
    Inventory myInventory;
};

#endif // MENU_H
