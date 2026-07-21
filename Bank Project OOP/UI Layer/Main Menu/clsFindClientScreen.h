#pragma once
#include "../clsScreen.h"
#include "../../Logic Layer/clsBank Client.h"

class clsFindClientScreen : protected clsScreen
{
private:
    static void _FindClient()
    {
        char Choice;
        cout << "\nDo you want to search using the account number?  [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            string AccountNumber = clsInputValidate<string>::Read("\nEnter the Account Number : ");
            clsBankClient Client = clsBankClient::Find(AccountNumber);
            Client.Print();
            return;
        }
    
        cout << "\nDo you want to search using the full name and PIN?  [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            string FullName = clsInputValidate<string>::Read("\nEnter a Full Name : ");
            string PIN = clsInputValidate<string>::Read("Enter a PIN Code : ");
            clsBankClient Client = clsBankClient::Find(FullName, PIN);
            Client.Print();
            return;
        }
    
        cout << "\nNo other options are available. Please try again later.n";
    }

public:
    static void FindClientScreen()
    {
        _DrawScreenHeader("FIND CLIENT SCREEN");
        _FindClient();   
    }
};