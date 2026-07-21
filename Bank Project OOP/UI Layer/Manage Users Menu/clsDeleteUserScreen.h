#pragma once
#include "../clsScreen.h"
#include "../../Library/clsGetObjectIfExists.h"
#include "../../Logic Layer/clsBank User.h"

class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _DeleteUser()
    {
        string Username = clsInputValidate<string>::Read("\nEnter the username : ");
        clsBankUser User = clsGetObjectIfExists::GetUserIfExists(Username);
        User.Print();

        char choice;
        cout << "\n\nAre you sure you want to delete this user?  [y/n] : ";
        if (cin >> choice && (choice == 'y' || choice == 'Y'))
        {
            if (User.Delete())
                cout << "\n\nUser deleted successfully\n";
            else
                cout << "\n\nThe user could not be deleted. Please try again\n";
        }
    }

public:
    static void DeleteUserScreen()
    {
        _DrawScreenHeader("DELETE USER SCREEN");
        _DeleteUser();
    }
};