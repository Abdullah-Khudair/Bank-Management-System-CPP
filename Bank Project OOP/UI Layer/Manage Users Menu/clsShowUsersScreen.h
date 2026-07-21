#pragma once
#include "../clsScreen.h"
#include "../../Logic Layer/clsBank User.h"

class clsShowUsersScreen : protected clsScreen
{
private:
    static void _ShowOneUser(const clsBankUser & User)
    {
        cout << "| " << left << setw(20) << User.Username();
        cout << "| " << left << setw(20) << User.Password();
        cout << "| " << left << setw(14) << User.Permission() << "|";
    }

    static void _ShowAllUsers(const vector<clsBankUser> & vUsers)
    {
        SetWidth(61, '=');
        cout << "\n| " << left << setw(20) << "Username";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(14) << "Permission" << "|\n";
        SetWidth(61, '=');
        cout << endl;
    
        if (vUsers.size() == 0)
            cout << "\n\t\t\t\t\t  No Users Available In The System!\n\n";
        
        else
        {
            for (const clsBankUser & U : vUsers)
            {
                _ShowOneUser(U);
                cout << endl;
            }
        }
        
        SetWidth(61, '=');
        cout << endl;
    }

public:
    static void ShowUsersScreen()
    {
        vector<clsBankUser> vUsers = clsBankUser::GetUsersList();

        _DrawScreenHeader("SHOW USERS SCREEN", "\tShow Users List (" + to_string(vUsers.size()) + ") Users");
        _ShowAllUsers(vUsers);
    }
};