#pragma once
#include "../clsScreen.h"
#include "../../Library/clsGetObjectIfExists.h"
#include "../../Logic Layer/clsBank User.h"

class clsUpdateUserInfoScreen : protected clsScreen
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

    static void ReadNewInfoForUser(clsBankUser & User)
    {
        char choice;
        cout << "\nDo you want to change the password? [y/n] : ";
        if (cin >> choice && (choice == 'y' || choice == 'Y'))
            User.Password(clsInputValidate<string>::Read("Enter a password : "));

        cout << "\nDo you want to change the permissions? [y/n] : ";
        if (cin >> choice && (choice == 'y' || choice == 'Y'))
            User.Permission(ReadPermissions());
    }

    static void _UpdateUserInfo()
    {
        string Username = clsInputValidate<string>::Read("\nEnter the username : ");
        clsBankUser User = clsGetObjectIfExists::GetUserIfExists(Username);
        User.Print();

        if (Username == "Admin")
        {
            cout << "\n\nYou cannot update the admin account.\n";
            return;
        }
        
        char choice;
        cout << "\n\nAre you sure you want to update the information for this user?  [y/n] : ";
        if (cin >> choice && (choice == 'y' || choice == 'Y'))
        {
            ReadNewInfoForUser(User);
            
            if (User.Save() == clsBankUser::svSucceeded)
                cout << "\n\nUser updated successfully.\n";
            else
                cout << "\n\nUser was not saved because no information was provided.\n";
        }
    }

public:
    static void UpdateUserInfoScreen()
    {
        _DrawScreenHeader("UPDATE USER INFO SCREEN");
        _UpdateUserInfo();
    }
};