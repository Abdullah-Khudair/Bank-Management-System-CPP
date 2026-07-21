#pragma once
#include "../clsScreen.h"
#include "../../Logic Layer/clsBank User.h"

class clsAddNewUserScreen : protected clsScreen
{
private:
    static short ReadPermissions()
    {
        char Answer;
        cout << "\nDo you want to give this user full access of the system? [y/n] : ";
        if (cin >> Answer && (Answer == 'y' || Answer == 'Y'))
            return clsBankUser::All;
    
        else
        {
            short Permission = 0;
            cout << "\nDo you want to give this user access for Show Clients? [y/n] : ";
            if (cin >> Answer && (Answer == 'y' || Answer == 'Y'))
                Permission += clsBankUser::ShowClients;
    
            cout << "Do you want to give this user access for Find Clients? [y/n] : ";
            if (cin >> Answer && (Answer == 'y' || Answer == 'Y'))
                Permission += clsBankUser::FindClient;

            cout << "Do you want to give this user access for Add Client? [y/n] : ";
            if (cin >> Answer && (Answer == 'y' || Answer == 'Y'))
                Permission += clsBankUser::AddClient;
    
            cout << "Do you want to give this user access for Update Clients? [y/n] : ";
            if (cin >> Answer && (Answer == 'y' || Answer == 'Y'))
                Permission += clsBankUser::UpdateClient;
    
            cout << "Do you want to give this user access for Delete Clients? [y/n] : ";
            if (cin >> Answer && (Answer == 'y' || Answer == 'Y'))
                Permission += clsBankUser::DeleteClient;
    
            cout << "Do you want to give this user access for Transactions? [y/n] : ";
            if (cin >> Answer && (Answer == 'y' || Answer == 'Y'))
                Permission += clsBankUser::Transactions;
    
            cout << "Do you want to give this user access for Manage Users? [y/n] : ";
            if (cin >> Answer && (Answer == 'y' || Answer == 'Y'))
                Permission += clsBankUser::ManageUser;

            cout << "Do you want to give this user access for Show Login Registers? [y/n] : ";
            if (cin >> Answer && (Answer == 'y' || Answer == 'Y'))
                Permission += clsBankUser::LoginRegister;
    
            cout << "Do you want to give this user access for Currency Exchange? [y/n] : ";
            if (cin >> Answer && (Answer == 'y' || Answer == 'Y'))
                Permission += clsBankUser::CurrencyExchange;
                
            return Permission;
        }
    }

    static void _AddNewUser()
    {
        string username = clsInputValidate<string>::Read("\nEnter a username : ");

        while(clsBankUser::IsUserExists(username))
        {
            cout << "\nThis account already exists.\n";
            username = clsInputValidate<string>::Read("Please enter a different username : ");
        }

        clsBankUser User = clsBankUser::GetAddNewUserObject(username);
        User.Password(clsInputValidate<string>::Read("\nEnter a password : "));
        User.Permission(ReadPermissions());

        char Choice;
        cout << "\n\nAre you sure you want to add this user?  [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            clsBankUser::enSaveResult Result = User.Save();

            if (Result == clsBankUser::svSucceeded)
                cout << "\n\nThe user has been added successfully!\n";
            else if (Result == clsBankUser::svFailedUsernameExists)
                cout << "\n\nFailed to save. This user already exists.\n";
            else
                cout << "\n\nFailed to save because the username is empty.\n";
    
        }
    }

public:
    static void AddNewUserScreen()
    {
        _DrawScreenHeader("ADD NEW USER SCREEN");
        _AddNewUser();
    }
};