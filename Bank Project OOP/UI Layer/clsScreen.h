#pragma once
#include <iostream>
#include <iomanip>
#include "Global.h"
using namespace std;

class clsScreen
{
protected:

    static void SetWidth(short Num, char Type)
    {
        cout << setfill(Type) << setw(Num) << "";
        cout << setfill(' ');
    }

    static void _DrawScreenHeader(const string & Title, const string & SubTitle = "")
    {
        cout << "\t\t\t\t"; SetWidth(70, '*');
        cout << "\n\n\t\t\t\t\t\t\t    " << Title;

        if (SubTitle != "")
            cout << "\n\n\t\t\t\t\t\t" << SubTitle;

        cout << "\n\n\t\t\t\t"; SetWidth(70, '*');


        cout << "\n\t\t\t\t\tUser: " << CurrentUser.Username();
        cout << "\n\t\t\t\t\tDate: " << clsDate::GetFullDate(clsDate()) << '\n' << endl;
    }

};