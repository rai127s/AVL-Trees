#include <iomanip>
#include <iostream>
#include "AVLb.h"
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
        cout << "3.\tSearch Tree.\n";
        cout << "4.\tExit.\n";

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
        case 3:
            cout << "Enter a number to search: ";
            cin >> x;
            AVL->SearchItem(x);
            break;
        default:
            break;
        }
    } while (choice != 4);

}
