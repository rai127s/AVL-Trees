#include <iomanip>
#include <iostream>
#include "AVL.h"
using namespace std;

int main()
{
    TreeType<int>* AVL = new TreeType<int>();
    int choice;
    int x;
    cout << "Welcome to your AVL Tree\n";
    cout << "Choose an option from the following:\n";

    do
    {
        cout << "1.\tInsert Node.\n";
        cout << "2.\tPrint Tree.\n";
        cout << "3.\tExit.\n";

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter a number: ";
            cin >> x;
            AVL->InsertItem(x);
            break;
        case 2:
            AVL->PT();
            break;
        default:
            break;
        }
    } while (choice != 3);

}