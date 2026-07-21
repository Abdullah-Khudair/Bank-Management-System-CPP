#pragma once
#include "../clsScreen.h"
#include "../../Library/clsGetObjectIfExists.h"
#include "../../Logic Layer/clsBank User.h"

class clsChangePasswordUserScreen : protected clsScreen
{
private:
    static void _ChangePasswordUser()
    {
        string Username = clsInputValidate<string>::Read("\nEnter the username : ");
        clsBankUser User = clsGetObjectIfExists::GetUserIfExists(Username);
        User.Print();

        char choice;
        cout << "\n\nAre you sure you want to change the password for this user?  [y/n] : ";
        if (cin >> choice && (choice == 'y' || choice == 'Y'))
        {
            string OldPasswprd = clsInputValidate<string>::Read("\nEnter the old password : ");
            string NewPasswprd = clsInputValidate<string>::Read("Enter the new password : ");

            if (User.ChangePassword(OldPasswprd, NewPasswprd))
                cout << "\n\nThe password has been changed successfully.\n";
            else
                cout << "\n\nThe password could not be changed. Please check the entered information.\n";
        }
    }

public:
    static void ChangePasswordUser()
    {
        _DrawScreenHeader("CHANGE PASSWORD SCREEN");
        _ChangePasswordUser();
    }
};